<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * linux/drivers/mmc/core/sdio_irq.c
 *
 * Author:      Nicolas Pitre
 * Created:     June 18, 2007
 * Copyright:   MontaVista Software Inc.
 *
 * Copyright 2008 Pierre Ossman
 */

#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <uapi/linux/sched/types.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/export.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>

#समावेश <linux/mmc/core.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mmc/card.h>
#समावेश <linux/mmc/sdपन.स>
#समावेश <linux/mmc/sdio_func.h>

#समावेश "sdio_ops.h"
#समावेश "core.h"
#समावेश "card.h"

अटल पूर्णांक sdio_get_pending_irqs(काष्ठा mmc_host *host, u8 *pending)
अणु
	काष्ठा mmc_card *card = host->card;
	पूर्णांक ret;

	WARN_ON(!host->claimed);

	ret = mmc_io_rw_direct(card, 0, 0, SDIO_CCCR_INTx, 0, pending);
	अगर (ret) अणु
		pr_debug("%s: error %d reading SDIO_CCCR_INTx\n",
		       mmc_card_id(card), ret);
		वापस ret;
	पूर्ण

	अगर (*pending && mmc_card_broken_irq_polling(card) &&
	    !(host->caps & MMC_CAP_SDIO_IRQ)) अणु
		अचिन्हित अक्षर dummy;

		/* A fake पूर्णांकerrupt could be created when we poll SDIO_CCCR_INTx
		 * रेजिस्टर with a Marvell SD8797 card. A dummy CMD52 पढ़ो to
		 * function 0 रेजिस्टर 0xff can aव्योम this.
		 */
		mmc_io_rw_direct(card, 0, 0, 0xff, 0, &dummy);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक process_sdio_pending_irqs(काष्ठा mmc_host *host)
अणु
	काष्ठा mmc_card *card = host->card;
	पूर्णांक i, ret, count;
	bool sdio_irq_pending = host->sdio_irq_pending;
	अचिन्हित अक्षर pending;
	काष्ठा sdio_func *func;

	/* Don't process SDIO IRQs अगर the card is suspended. */
	अगर (mmc_card_suspended(card))
		वापस 0;

	/* Clear the flag to indicate that we have processed the IRQ. */
	host->sdio_irq_pending = false;

	/*
	 * Optimization, अगर there is only 1 function पूर्णांकerrupt रेजिस्टरed
	 * and we know an IRQ was संकेतed then call irq handler directly.
	 * Otherwise करो the full probe.
	 */
	func = card->sdio_single_irq;
	अगर (func && sdio_irq_pending) अणु
		func->irq_handler(func);
		वापस 1;
	पूर्ण

	ret = sdio_get_pending_irqs(host, &pending);
	अगर (ret)
		वापस ret;

	count = 0;
	क्रम (i = 1; i <= 7; i++) अणु
		अगर (pending & (1 << i)) अणु
			func = card->sdio_func[i - 1];
			अगर (!func) अणु
				pr_warn("%s: pending IRQ for non-existent function\n",
					mmc_card_id(card));
				ret = -EINVAL;
			पूर्ण अन्यथा अगर (func->irq_handler) अणु
				func->irq_handler(func);
				count++;
			पूर्ण अन्यथा अणु
				pr_warn("%s: pending IRQ with no handler\n",
					sdio_func_id(func));
				ret = -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (count)
		वापस count;

	वापस ret;
पूर्ण

अटल व्योम sdio_run_irqs(काष्ठा mmc_host *host)
अणु
	mmc_claim_host(host);
	अगर (host->sdio_irqs) अणु
		process_sdio_pending_irqs(host);
		अगर (!host->sdio_irq_pending)
			host->ops->ack_sdio_irq(host);
	पूर्ण
	mmc_release_host(host);
पूर्ण

व्योम sdio_irq_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mmc_host *host =
		container_of(work, काष्ठा mmc_host, sdio_irq_work.work);

	sdio_run_irqs(host);
पूर्ण

व्योम sdio_संकेत_irq(काष्ठा mmc_host *host)
अणु
	host->sdio_irq_pending = true;
	queue_delayed_work(प्रणाली_wq, &host->sdio_irq_work, 0);
पूर्ण
EXPORT_SYMBOL_GPL(sdio_संकेत_irq);

अटल पूर्णांक sdio_irq_thपढ़ो(व्योम *_host)
अणु
	काष्ठा mmc_host *host = _host;
	अचिन्हित दीर्घ period, idle_period;
	पूर्णांक ret;

	sched_set_fअगरo_low(current);

	/*
	 * We want to allow क्रम SDIO cards to work even on non SDIO
	 * aware hosts.  One thing that non SDIO host cannot करो is
	 * asynchronous notअगरication of pending SDIO card पूर्णांकerrupts
	 * hence we poll क्रम them in that हाल.
	 */
	idle_period = msecs_to_jअगरfies(10);
	period = (host->caps & MMC_CAP_SDIO_IRQ) ?
		MAX_SCHEDULE_TIMEOUT : idle_period;

	pr_debug("%s: IRQ thread started (poll period = %lu jiffies)\n",
		 mmc_hostname(host), period);

	करो अणु
		/*
		 * We claim the host here on drivers behalf क्रम a couple
		 * reasons:
		 *
		 * 1) it is alपढ़ोy needed to retrieve the CCCR_INTx;
		 * 2) we want the driver(s) to clear the IRQ condition ASAP;
		 * 3) we need to control the पात condition locally.
		 *
		 * Just like traditional hard IRQ handlers, we expect SDIO
		 * IRQ handlers to be quick and to the poपूर्णांक, so that the
		 * holding of the host lock करोes not cover too much work
		 * that करोesn't require that lock to be held.
		 */
		ret = __mmc_claim_host(host, शून्य,
				       &host->sdio_irq_thपढ़ो_पात);
		अगर (ret)
			अवरोध;
		ret = process_sdio_pending_irqs(host);
		mmc_release_host(host);

		/*
		 * Give other thपढ़ोs a chance to run in the presence of
		 * errors.
		 */
		अगर (ret < 0) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			अगर (!kthपढ़ो_should_stop())
				schedule_समयout(HZ);
			set_current_state(TASK_RUNNING);
		पूर्ण

		/*
		 * Adaptive polling frequency based on the assumption
		 * that an पूर्णांकerrupt will be बंदly followed by more.
		 * This has a substantial benefit क्रम network devices.
		 */
		अगर (!(host->caps & MMC_CAP_SDIO_IRQ)) अणु
			अगर (ret > 0)
				period /= 2;
			अन्यथा अणु
				period++;
				अगर (period > idle_period)
					period = idle_period;
			पूर्ण
		पूर्ण

		set_current_state(TASK_INTERRUPTIBLE);
		अगर (host->caps & MMC_CAP_SDIO_IRQ)
			host->ops->enable_sdio_irq(host, 1);
		अगर (!kthपढ़ो_should_stop())
			schedule_समयout(period);
		set_current_state(TASK_RUNNING);
	पूर्ण जबतक (!kthपढ़ो_should_stop());

	अगर (host->caps & MMC_CAP_SDIO_IRQ)
		host->ops->enable_sdio_irq(host, 0);

	pr_debug("%s: IRQ thread exiting with code %d\n",
		 mmc_hostname(host), ret);

	वापस ret;
पूर्ण

अटल पूर्णांक sdio_card_irq_get(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;

	WARN_ON(!host->claimed);

	अगर (!host->sdio_irqs++) अणु
		अगर (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD)) अणु
			atomic_set(&host->sdio_irq_thपढ़ो_पात, 0);
			host->sdio_irq_thपढ़ो =
				kthपढ़ो_run(sdio_irq_thपढ़ो, host,
					    "ksdioirqd/%s", mmc_hostname(host));
			अगर (IS_ERR(host->sdio_irq_thपढ़ो)) अणु
				पूर्णांक err = PTR_ERR(host->sdio_irq_thपढ़ो);
				host->sdio_irqs--;
				वापस err;
			पूर्ण
		पूर्ण अन्यथा अगर (host->caps & MMC_CAP_SDIO_IRQ) अणु
			host->ops->enable_sdio_irq(host, 1);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sdio_card_irq_put(काष्ठा mmc_card *card)
अणु
	काष्ठा mmc_host *host = card->host;

	WARN_ON(!host->claimed);

	अगर (host->sdio_irqs < 1)
		वापस -EINVAL;

	अगर (!--host->sdio_irqs) अणु
		अगर (!(host->caps2 & MMC_CAP2_SDIO_IRQ_NOTHREAD)) अणु
			atomic_set(&host->sdio_irq_thपढ़ो_पात, 1);
			kthपढ़ो_stop(host->sdio_irq_thपढ़ो);
		पूर्ण अन्यथा अगर (host->caps & MMC_CAP_SDIO_IRQ) अणु
			host->ops->enable_sdio_irq(host, 0);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* If there is only 1 function रेजिस्टरed set sdio_single_irq */
अटल व्योम sdio_single_irq_set(काष्ठा mmc_card *card)
अणु
	काष्ठा sdio_func *func;
	पूर्णांक i;

	card->sdio_single_irq = शून्य;
	अगर ((card->host->caps & MMC_CAP_SDIO_IRQ) &&
	    card->host->sdio_irqs == 1) अणु
		क्रम (i = 0; i < card->sdio_funcs; i++) अणु
			func = card->sdio_func[i];
			अगर (func && func->irq_handler) अणु
				card->sdio_single_irq = func;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 *	sdio_claim_irq - claim the IRQ क्रम a SDIO function
 *	@func: SDIO function
 *	@handler: IRQ handler callback
 *
 *	Claim and activate the IRQ क्रम the given SDIO function. The provided
 *	handler will be called when that IRQ is निश्चितed.  The host is always
 *	claimed alपढ़ोy when the handler is called so the handler should not
 *	call sdio_claim_host() or sdio_release_host().
 */
पूर्णांक sdio_claim_irq(काष्ठा sdio_func *func, sdio_irq_handler_t *handler)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर reg;

	अगर (!func)
		वापस -EINVAL;

	pr_debug("SDIO: Enabling IRQ for %s...\n", sdio_func_id(func));

	अगर (func->irq_handler) अणु
		pr_debug("SDIO: IRQ for %s already in use.\n", sdio_func_id(func));
		वापस -EBUSY;
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IENx, 0, &reg);
	अगर (ret)
		वापस ret;

	reg |= 1 << func->num;

	reg |= 1; /* Master पूर्णांकerrupt enable */

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IENx, reg, शून्य);
	अगर (ret)
		वापस ret;

	func->irq_handler = handler;
	ret = sdio_card_irq_get(func->card);
	अगर (ret)
		func->irq_handler = शून्य;
	sdio_single_irq_set(func->card);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_claim_irq);

/**
 *	sdio_release_irq - release the IRQ क्रम a SDIO function
 *	@func: SDIO function
 *
 *	Disable and release the IRQ क्रम the given SDIO function.
 */
पूर्णांक sdio_release_irq(काष्ठा sdio_func *func)
अणु
	पूर्णांक ret;
	अचिन्हित अक्षर reg;

	अगर (!func)
		वापस -EINVAL;

	pr_debug("SDIO: Disabling IRQ for %s...\n", sdio_func_id(func));

	अगर (func->irq_handler) अणु
		func->irq_handler = शून्य;
		sdio_card_irq_put(func->card);
		sdio_single_irq_set(func->card);
	पूर्ण

	ret = mmc_io_rw_direct(func->card, 0, 0, SDIO_CCCR_IENx, 0, &reg);
	अगर (ret)
		वापस ret;

	reg &= ~(1 << func->num);

	/* Disable master पूर्णांकerrupt with the last function पूर्णांकerrupt */
	अगर (!(reg & 0xFE))
		reg = 0;

	ret = mmc_io_rw_direct(func->card, 1, 0, SDIO_CCCR_IENx, reg, शून्य);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(sdio_release_irq);

