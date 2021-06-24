<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra host1x Interrupt Management
 *
 * Copyright (C) 2010 Google, Inc.
 * Copyright (c) 2010-2013, NVIDIA Corporation.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/पन.स>

#समावेश "../intr.h"
#समावेश "../dev.h"

/*
 * Sync poपूर्णांक threshold पूर्णांकerrupt service function
 * Handles sync poपूर्णांक threshold triggers, in पूर्णांकerrupt context
 */
अटल व्योम host1x_पूर्णांकr_syncpt_handle(काष्ठा host1x_syncpt *syncpt)
अणु
	अचिन्हित पूर्णांक id = syncpt->id;
	काष्ठा host1x *host = syncpt->host;

	host1x_sync_ग_लिखोl(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE(id / 32));
	host1x_sync_ग_लिखोl(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(id / 32));

	schedule_work(&syncpt->पूर्णांकr.work);
पूर्ण

अटल irqवापस_t syncpt_thresh_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा host1x *host = dev_id;
	अचिन्हित दीर्घ reg;
	अचिन्हित पूर्णांक i, id;

	क्रम (i = 0; i < DIV_ROUND_UP(host->info->nb_pts, 32); i++) अणु
		reg = host1x_sync_पढ़ोl(host,
			HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(i));
		क्रम_each_set_bit(id, &reg, 32) अणु
			काष्ठा host1x_syncpt *syncpt =
				host->syncpt + (i * 32 + id);
			host1x_पूर्णांकr_syncpt_handle(syncpt);
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम _host1x_पूर्णांकr_disable_all_syncpt_पूर्णांकrs(काष्ठा host1x *host)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < DIV_ROUND_UP(host->info->nb_pts, 32); ++i) अणु
		host1x_sync_ग_लिखोl(host, 0xffffffffu,
			HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE(i));
		host1x_sync_ग_लिखोl(host, 0xffffffffu,
			HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(i));
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकr_hw_init(काष्ठा host1x *host, u32 cpm)
अणु
#अगर HOST1X_HW < 6
	/* disable the ip_busy_समयout. this prevents ग_लिखो drops */
	host1x_sync_ग_लिखोl(host, 0, HOST1X_SYNC_IP_BUSY_TIMEOUT);

	/*
	 * increase the स्वतः-ack timout to the maximum value. 2d will hang
	 * otherwise on Tegra2.
	 */
	host1x_sync_ग_लिखोl(host, 0xff, HOST1X_SYNC_CTXSW_TIMEOUT_CFG);

	/* update host घड़ीs per usec */
	host1x_sync_ग_लिखोl(host, cpm, HOST1X_SYNC_USEC_CLK);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक
_host1x_पूर्णांकr_init_host_sync(काष्ठा host1x *host, u32 cpm,
			    व्योम (*syncpt_thresh_work)(काष्ठा work_काष्ठा *))
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक err;

	host1x_hw_पूर्णांकr_disable_all_syncpt_पूर्णांकrs(host);

	क्रम (i = 0; i < host->info->nb_pts; i++)
		INIT_WORK(&host->syncpt[i].पूर्णांकr.work, syncpt_thresh_work);

	err = devm_request_irq(host->dev, host->पूर्णांकr_syncpt_irq,
			       syncpt_thresh_isr, IRQF_SHARED,
			       "host1x_syncpt", host);
	अगर (err < 0) अणु
		WARN_ON(1);
		वापस err;
	पूर्ण

	पूर्णांकr_hw_init(host, cpm);

	वापस 0;
पूर्ण

अटल व्योम _host1x_पूर्णांकr_set_syncpt_threshold(काष्ठा host1x *host,
					      अचिन्हित पूर्णांक id,
					      u32 thresh)
अणु
	host1x_sync_ग_लिखोl(host, thresh, HOST1X_SYNC_SYNCPT_INT_THRESH(id));
पूर्ण

अटल व्योम _host1x_पूर्णांकr_enable_syncpt_पूर्णांकr(काष्ठा host1x *host,
					    अचिन्हित पूर्णांक id)
अणु
	host1x_sync_ग_लिखोl(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_INT_ENABLE_CPU0(id / 32));
पूर्ण

अटल व्योम _host1x_पूर्णांकr_disable_syncpt_पूर्णांकr(काष्ठा host1x *host,
					     अचिन्हित पूर्णांक id)
अणु
	host1x_sync_ग_लिखोl(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_INT_DISABLE(id / 32));
	host1x_sync_ग_लिखोl(host, BIT(id % 32),
		HOST1X_SYNC_SYNCPT_THRESH_CPU0_INT_STATUS(id / 32));
पूर्ण

अटल पूर्णांक _host1x_मुक्त_syncpt_irq(काष्ठा host1x *host)
अणु
	अचिन्हित पूर्णांक i;

	devm_मुक्त_irq(host->dev, host->पूर्णांकr_syncpt_irq, host);

	क्रम (i = 0; i < host->info->nb_pts; i++)
		cancel_work_sync(&host->syncpt[i].पूर्णांकr.work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा host1x_पूर्णांकr_ops host1x_पूर्णांकr_ops = अणु
	.init_host_sync = _host1x_पूर्णांकr_init_host_sync,
	.set_syncpt_threshold = _host1x_पूर्णांकr_set_syncpt_threshold,
	.enable_syncpt_पूर्णांकr = _host1x_पूर्णांकr_enable_syncpt_पूर्णांकr,
	.disable_syncpt_पूर्णांकr = _host1x_पूर्णांकr_disable_syncpt_पूर्णांकr,
	.disable_all_syncpt_पूर्णांकrs = _host1x_पूर्णांकr_disable_all_syncpt_पूर्णांकrs,
	.मुक्त_syncpt_irq = _host1x_मुक्त_syncpt_irq,
पूर्ण;
