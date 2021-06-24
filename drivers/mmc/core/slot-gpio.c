<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic GPIO card-detect helper
 *
 * Copyright (C) 2011, Guennadi Liakhovetski <g.liakhovetski@gmx.de>
 */

#समावेश <linux/err.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/slot-gpपन.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश "slot-gpio.h"

काष्ठा mmc_gpio अणु
	काष्ठा gpio_desc *ro_gpio;
	काष्ठा gpio_desc *cd_gpio;
	irqवापस_t (*cd_gpio_isr)(पूर्णांक irq, व्योम *dev_id);
	अक्षर *ro_label;
	अक्षर *cd_label;
	u32 cd_debounce_delay_ms;
पूर्ण;

अटल irqवापस_t mmc_gpio_cd_irqt(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Schedule a card detection after a debounce समयout */
	काष्ठा mmc_host *host = dev_id;
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;

	host->trigger_card_event = true;
	mmc_detect_change(host, msecs_to_jअगरfies(ctx->cd_debounce_delay_ms));

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mmc_gpio_alloc(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_gpio *ctx = devm_kzalloc(host->parent,
					    माप(*ctx), GFP_KERNEL);

	अगर (ctx) अणु
		ctx->cd_debounce_delay_ms = 200;
		ctx->cd_label = devm_kaप्र_लिखो(host->parent, GFP_KERNEL,
				"%s cd", dev_name(host->parent));
		अगर (!ctx->cd_label)
			वापस -ENOMEM;
		ctx->ro_label = devm_kaप्र_लिखो(host->parent, GFP_KERNEL,
				"%s ro", dev_name(host->parent));
		अगर (!ctx->ro_label)
			वापस -ENOMEM;
		host->slot.handler_priv = ctx;
		host->slot.cd_irq = -EINVAL;
	पूर्ण

	वापस ctx ? 0 : -ENOMEM;
पूर्ण

पूर्णांक mmc_gpio_get_ro(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;

	अगर (!ctx || !ctx->ro_gpio)
		वापस -ENOSYS;

	वापस gpiod_get_value_cansleep(ctx->ro_gpio);
पूर्ण
EXPORT_SYMBOL(mmc_gpio_get_ro);

पूर्णांक mmc_gpio_get_cd(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;
	पूर्णांक cansleep;

	अगर (!ctx || !ctx->cd_gpio)
		वापस -ENOSYS;

	cansleep = gpiod_cansleep(ctx->cd_gpio);
	वापस cansleep ?
		gpiod_get_value_cansleep(ctx->cd_gpio) :
		gpiod_get_value(ctx->cd_gpio);
पूर्ण
EXPORT_SYMBOL(mmc_gpio_get_cd);

व्योम mmc_gpiod_request_cd_irq(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;
	पूर्णांक irq = -EINVAL;
	पूर्णांक ret;

	अगर (host->slot.cd_irq >= 0 || !ctx || !ctx->cd_gpio)
		वापस;

	/*
	 * Do not use IRQ अगर the platक्रमm prefers to poll, e.g., because that
	 * IRQ number is alपढ़ोy used by another unit and cannot be shared.
	 */
	अगर (!(host->caps & MMC_CAP_NEEDS_POLL))
		irq = gpiod_to_irq(ctx->cd_gpio);

	अगर (irq >= 0) अणु
		अगर (!ctx->cd_gpio_isr)
			ctx->cd_gpio_isr = mmc_gpio_cd_irqt;
		ret = devm_request_thपढ़ोed_irq(host->parent, irq,
			शून्य, ctx->cd_gpio_isr,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
			ctx->cd_label, host);
		अगर (ret < 0)
			irq = ret;
	पूर्ण

	host->slot.cd_irq = irq;

	अगर (irq < 0)
		host->caps |= MMC_CAP_NEEDS_POLL;
पूर्ण
EXPORT_SYMBOL(mmc_gpiod_request_cd_irq);

पूर्णांक mmc_gpio_set_cd_wake(काष्ठा mmc_host *host, bool on)
अणु
	पूर्णांक ret = 0;

	अगर (!(host->caps & MMC_CAP_CD_WAKE) ||
	    host->slot.cd_irq < 0 ||
	    on == host->slot.cd_wake_enabled)
		वापस 0;

	अगर (on) अणु
		ret = enable_irq_wake(host->slot.cd_irq);
		host->slot.cd_wake_enabled = !ret;
	पूर्ण अन्यथा अणु
		disable_irq_wake(host->slot.cd_irq);
		host->slot.cd_wake_enabled = false;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mmc_gpio_set_cd_wake);

/* Register an alternate पूर्णांकerrupt service routine क्रम
 * the card-detect GPIO.
 */
व्योम mmc_gpio_set_cd_isr(काष्ठा mmc_host *host,
			 irqवापस_t (*isr)(पूर्णांक irq, व्योम *dev_id))
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;

	WARN_ON(ctx->cd_gpio_isr);
	ctx->cd_gpio_isr = isr;
पूर्ण
EXPORT_SYMBOL(mmc_gpio_set_cd_isr);

/**
 * mmc_gpiod_request_cd - request a gpio descriptor क्रम card-detection
 * @host: mmc host
 * @con_id: function within the GPIO consumer
 * @idx: index of the GPIO to obtain in the consumer
 * @override_active_level: ignore %GPIO_ACTIVE_LOW flag
 * @debounce: debounce समय in microseconds
 *
 * Note that this must be called prior to mmc_add_host()
 * otherwise the caller must also call mmc_gpiod_request_cd_irq().
 *
 * Returns zero on success, अन्यथा an error.
 */
पूर्णांक mmc_gpiod_request_cd(काष्ठा mmc_host *host, स्थिर अक्षर *con_id,
			 अचिन्हित पूर्णांक idx, bool override_active_level,
			 अचिन्हित पूर्णांक debounce)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;
	काष्ठा gpio_desc *desc;
	पूर्णांक ret;

	desc = devm_gpiod_get_index(host->parent, con_id, idx, GPIOD_IN);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	अगर (debounce) अणु
		ret = gpiod_set_debounce(desc, debounce);
		अगर (ret < 0)
			ctx->cd_debounce_delay_ms = debounce / 1000;
	पूर्ण

	/* override क्रमces शेष (active-low) polarity ... */
	अगर (override_active_level && !gpiod_is_active_low(desc))
		gpiod_toggle_active_low(desc);

	/* ... or active-high */
	अगर (host->caps2 & MMC_CAP2_CD_ACTIVE_HIGH)
		gpiod_toggle_active_low(desc);

	ctx->cd_gpio = desc;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_gpiod_request_cd);

bool mmc_can_gpio_cd(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;

	वापस ctx->cd_gpio ? true : false;
पूर्ण
EXPORT_SYMBOL(mmc_can_gpio_cd);

/**
 * mmc_gpiod_request_ro - request a gpio descriptor क्रम ग_लिखो protection
 * @host: mmc host
 * @con_id: function within the GPIO consumer
 * @idx: index of the GPIO to obtain in the consumer
 * @debounce: debounce समय in microseconds
 *
 * Returns zero on success, अन्यथा an error.
 */
पूर्णांक mmc_gpiod_request_ro(काष्ठा mmc_host *host, स्थिर अक्षर *con_id,
			 अचिन्हित पूर्णांक idx, अचिन्हित पूर्णांक debounce)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;
	काष्ठा gpio_desc *desc;
	पूर्णांक ret;

	desc = devm_gpiod_get_index(host->parent, con_id, idx, GPIOD_IN);
	अगर (IS_ERR(desc))
		वापस PTR_ERR(desc);

	अगर (debounce) अणु
		ret = gpiod_set_debounce(desc, debounce);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (host->caps2 & MMC_CAP2_RO_ACTIVE_HIGH)
		gpiod_toggle_active_low(desc);

	ctx->ro_gpio = desc;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(mmc_gpiod_request_ro);

bool mmc_can_gpio_ro(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_gpio *ctx = host->slot.handler_priv;

	वापस ctx->ro_gpio ? true : false;
पूर्ण
EXPORT_SYMBOL(mmc_can_gpio_ro);
