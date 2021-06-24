<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2012 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#घोषणा DSS_SUBSYS_NAME "APPLY"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/seq_file.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"
#समावेश "dispc-compat.h"

#घोषणा DISPC_IRQ_MASK_ERROR            (DISPC_IRQ_GFX_FIFO_UNDERFLOW | \
					 DISPC_IRQ_OCP_ERR | \
					 DISPC_IRQ_VID1_FIFO_UNDERFLOW | \
					 DISPC_IRQ_VID2_FIFO_UNDERFLOW | \
					 DISPC_IRQ_SYNC_LOST | \
					 DISPC_IRQ_SYNC_LOST_DIGIT)

#घोषणा DISPC_MAX_NR_ISRS		8

काष्ठा omap_dispc_isr_data अणु
	omap_dispc_isr_t	isr;
	व्योम			*arg;
	u32			mask;
पूर्ण;

काष्ठा dispc_irq_stats अणु
	अचिन्हित दीर्घ last_reset;
	अचिन्हित irq_count;
	अचिन्हित irqs[32];
पूर्ण;

अटल काष्ठा अणु
	spinlock_t irq_lock;
	u32 irq_error_mask;
	काष्ठा omap_dispc_isr_data रेजिस्टरed_isr[DISPC_MAX_NR_ISRS];
	u32 error_irqs;
	काष्ठा work_काष्ठा error_work;

#अगर_घोषित CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	spinlock_t irq_stats_lock;
	काष्ठा dispc_irq_stats irq_stats;
#पूर्ण_अगर
पूर्ण dispc_compat;


#अगर_घोषित CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
अटल व्योम dispc_dump_irqs(काष्ठा seq_file *s)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा dispc_irq_stats stats;

	spin_lock_irqsave(&dispc_compat.irq_stats_lock, flags);

	stats = dispc_compat.irq_stats;
	स_रखो(&dispc_compat.irq_stats, 0, माप(dispc_compat.irq_stats));
	dispc_compat.irq_stats.last_reset = jअगरfies;

	spin_unlock_irqrestore(&dispc_compat.irq_stats_lock, flags);

	seq_म_लिखो(s, "period %u ms\n",
			jअगरfies_to_msecs(jअगरfies - stats.last_reset));

	seq_म_लिखो(s, "irqs %d\n", stats.irq_count);
#घोषणा PIS(x) \
	seq_म_लिखो(s, "%-20s %10d\n", #x, stats.irqs[ffs(DISPC_IRQ_##x)-1])

	PIS(FRAMEDONE);
	PIS(VSYNC);
	PIS(EVSYNC_EVEN);
	PIS(EVSYNC_ODD);
	PIS(ACBIAS_COUNT_STAT);
	PIS(PROG_LINE_NUM);
	PIS(GFX_FIFO_UNDERFLOW);
	PIS(GFX_END_WIN);
	PIS(PAL_GAMMA_MASK);
	PIS(OCP_ERR);
	PIS(VID1_FIFO_UNDERFLOW);
	PIS(VID1_END_WIN);
	PIS(VID2_FIFO_UNDERFLOW);
	PIS(VID2_END_WIN);
	अगर (dss_feat_get_num_ovls() > 3) अणु
		PIS(VID3_FIFO_UNDERFLOW);
		PIS(VID3_END_WIN);
	पूर्ण
	PIS(SYNC_LOST);
	PIS(SYNC_LOST_DIGIT);
	PIS(WAKEUP);
	अगर (dss_has_feature(FEAT_MGR_LCD2)) अणु
		PIS(FRAMEDONE2);
		PIS(VSYNC2);
		PIS(ACBIAS_COUNT_STAT2);
		PIS(SYNC_LOST2);
	पूर्ण
	अगर (dss_has_feature(FEAT_MGR_LCD3)) अणु
		PIS(FRAMEDONE3);
		PIS(VSYNC3);
		PIS(ACBIAS_COUNT_STAT3);
		PIS(SYNC_LOST3);
	पूर्ण
#अघोषित PIS
पूर्ण
#पूर्ण_अगर

/* dispc.irq_lock has to be locked by the caller */
अटल व्योम _omap_dispc_set_irqs(व्योम)
अणु
	u32 mask;
	पूर्णांक i;
	काष्ठा omap_dispc_isr_data *isr_data;

	mask = dispc_compat.irq_error_mask;

	क्रम (i = 0; i < DISPC_MAX_NR_ISRS; i++) अणु
		isr_data = &dispc_compat.रेजिस्टरed_isr[i];

		अगर (isr_data->isr == शून्य)
			जारी;

		mask |= isr_data->mask;
	पूर्ण

	dispc_ग_लिखो_irqenable(mask);
पूर्ण

पूर्णांक omap_dispc_रेजिस्टर_isr(omap_dispc_isr_t isr, व्योम *arg, u32 mask)
अणु
	पूर्णांक i;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	काष्ठा omap_dispc_isr_data *isr_data;

	अगर (isr == शून्य)
		वापस -EINVAL;

	spin_lock_irqsave(&dispc_compat.irq_lock, flags);

	/* check क्रम duplicate entry */
	क्रम (i = 0; i < DISPC_MAX_NR_ISRS; i++) अणु
		isr_data = &dispc_compat.रेजिस्टरed_isr[i];
		अगर (isr_data->isr == isr && isr_data->arg == arg &&
				isr_data->mask == mask) अणु
			ret = -EINVAL;
			जाओ err;
		पूर्ण
	पूर्ण

	isr_data = शून्य;
	ret = -EBUSY;

	क्रम (i = 0; i < DISPC_MAX_NR_ISRS; i++) अणु
		isr_data = &dispc_compat.रेजिस्टरed_isr[i];

		अगर (isr_data->isr != शून्य)
			जारी;

		isr_data->isr = isr;
		isr_data->arg = arg;
		isr_data->mask = mask;
		ret = 0;

		अवरोध;
	पूर्ण

	अगर (ret)
		जाओ err;

	_omap_dispc_set_irqs();

	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	वापस 0;
err:
	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(omap_dispc_रेजिस्टर_isr);

पूर्णांक omap_dispc_unरेजिस्टर_isr(omap_dispc_isr_t isr, व्योम *arg, u32 mask)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = -EINVAL;
	काष्ठा omap_dispc_isr_data *isr_data;

	spin_lock_irqsave(&dispc_compat.irq_lock, flags);

	क्रम (i = 0; i < DISPC_MAX_NR_ISRS; i++) अणु
		isr_data = &dispc_compat.रेजिस्टरed_isr[i];
		अगर (isr_data->isr != isr || isr_data->arg != arg ||
				isr_data->mask != mask)
			जारी;

		/* found the correct isr */

		isr_data->isr = शून्य;
		isr_data->arg = शून्य;
		isr_data->mask = 0;

		ret = 0;
		अवरोध;
	पूर्ण

	अगर (ret == 0)
		_omap_dispc_set_irqs();

	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(omap_dispc_unरेजिस्टर_isr);

अटल व्योम prपूर्णांक_irq_status(u32 status)
अणु
	अगर ((status & dispc_compat.irq_error_mask) == 0)
		वापस;

#घोषणा PIS(x) (status & DISPC_IRQ_##x) ? (#x " ") : ""

	pr_debug("DISPC IRQ: 0x%x: %s%s%s%s%s%s%s%s%s\n",
		status,
		PIS(OCP_ERR),
		PIS(GFX_FIFO_UNDERFLOW),
		PIS(VID1_FIFO_UNDERFLOW),
		PIS(VID2_FIFO_UNDERFLOW),
		dss_feat_get_num_ovls() > 3 ? PIS(VID3_FIFO_UNDERFLOW) : "",
		PIS(SYNC_LOST),
		PIS(SYNC_LOST_DIGIT),
		dss_has_feature(FEAT_MGR_LCD2) ? PIS(SYNC_LOST2) : "",
		dss_has_feature(FEAT_MGR_LCD3) ? PIS(SYNC_LOST3) : "");
#अघोषित PIS
पूर्ण

/* Called from dss.c. Note that we करोn't touch घड़ीs here,
 * but we presume they are on because we got an IRQ. However,
 * an irq handler may turn the घड़ीs off, so we may not have
 * घड़ी later in the function. */
अटल irqवापस_t omap_dispc_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	पूर्णांक i;
	u32 irqstatus, irqenable;
	u32 handledirqs = 0;
	u32 unhandled_errors;
	काष्ठा omap_dispc_isr_data *isr_data;
	काष्ठा omap_dispc_isr_data रेजिस्टरed_isr[DISPC_MAX_NR_ISRS];

	spin_lock(&dispc_compat.irq_lock);

	irqstatus = dispc_पढ़ो_irqstatus();
	irqenable = dispc_पढ़ो_irqenable();

	/* IRQ is not क्रम us */
	अगर (!(irqstatus & irqenable)) अणु
		spin_unlock(&dispc_compat.irq_lock);
		वापस IRQ_NONE;
	पूर्ण

#अगर_घोषित CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	spin_lock(&dispc_compat.irq_stats_lock);
	dispc_compat.irq_stats.irq_count++;
	dss_collect_irq_stats(irqstatus, dispc_compat.irq_stats.irqs);
	spin_unlock(&dispc_compat.irq_stats_lock);
#पूर्ण_अगर

	prपूर्णांक_irq_status(irqstatus);

	/* Ack the पूर्णांकerrupt. Do it here beक्रमe घड़ीs are possibly turned
	 * off */
	dispc_clear_irqstatus(irqstatus);
	/* flush posted ग_लिखो */
	dispc_पढ़ो_irqstatus();

	/* make a copy and unlock, so that isrs can unरेजिस्टर
	 * themselves */
	स_नकल(रेजिस्टरed_isr, dispc_compat.रेजिस्टरed_isr,
			माप(रेजिस्टरed_isr));

	spin_unlock(&dispc_compat.irq_lock);

	क्रम (i = 0; i < DISPC_MAX_NR_ISRS; i++) अणु
		isr_data = &रेजिस्टरed_isr[i];

		अगर (!isr_data->isr)
			जारी;

		अगर (isr_data->mask & irqstatus) अणु
			isr_data->isr(isr_data->arg, irqstatus);
			handledirqs |= isr_data->mask;
		पूर्ण
	पूर्ण

	spin_lock(&dispc_compat.irq_lock);

	unhandled_errors = irqstatus & ~handledirqs & dispc_compat.irq_error_mask;

	अगर (unhandled_errors) अणु
		dispc_compat.error_irqs |= unhandled_errors;

		dispc_compat.irq_error_mask &= ~unhandled_errors;
		_omap_dispc_set_irqs();

		schedule_work(&dispc_compat.error_work);
	पूर्ण

	spin_unlock(&dispc_compat.irq_lock);

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम dispc_error_worker(काष्ठा work_काष्ठा *work)
अणु
	पूर्णांक i;
	u32 errors;
	अचिन्हित दीर्घ flags;
	अटल स्थिर अचिन्हित fअगरo_underflow_bits[] = अणु
		DISPC_IRQ_GFX_FIFO_UNDERFLOW,
		DISPC_IRQ_VID1_FIFO_UNDERFLOW,
		DISPC_IRQ_VID2_FIFO_UNDERFLOW,
		DISPC_IRQ_VID3_FIFO_UNDERFLOW,
	पूर्ण;

	spin_lock_irqsave(&dispc_compat.irq_lock, flags);
	errors = dispc_compat.error_irqs;
	dispc_compat.error_irqs = 0;
	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	dispc_runसमय_get();

	क्रम (i = 0; i < omap_dss_get_num_overlays(); ++i) अणु
		काष्ठा omap_overlay *ovl;
		अचिन्हित bit;

		ovl = omap_dss_get_overlay(i);
		bit = fअगरo_underflow_bits[i];

		अगर (bit & errors) अणु
			DSSERR("FIFO UNDERFLOW on %s, disabling the overlay\n",
					ovl->name);
			ovl->disable(ovl);
			msleep(50);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < omap_dss_get_num_overlay_managers(); ++i) अणु
		काष्ठा omap_overlay_manager *mgr;
		अचिन्हित bit;

		mgr = omap_dss_get_overlay_manager(i);
		bit = dispc_mgr_get_sync_lost_irq(i);

		अगर (bit & errors) अणु
			पूर्णांक j;

			DSSERR("SYNC_LOST on channel %s, restarting the output "
					"with video overlays disabled\n",
					mgr->name);

			dss_mgr_disable(mgr);

			क्रम (j = 0; j < omap_dss_get_num_overlays(); ++j) अणु
				काष्ठा omap_overlay *ovl;
				ovl = omap_dss_get_overlay(j);

				अगर (ovl->id != OMAP_DSS_GFX &&
						ovl->manager == mgr)
					ovl->disable(ovl);
			पूर्ण

			dss_mgr_enable(mgr);
		पूर्ण
	पूर्ण

	अगर (errors & DISPC_IRQ_OCP_ERR) अणु
		DSSERR("OCP_ERR\n");
		क्रम (i = 0; i < omap_dss_get_num_overlay_managers(); ++i) अणु
			काष्ठा omap_overlay_manager *mgr;

			mgr = omap_dss_get_overlay_manager(i);
			dss_mgr_disable(mgr);
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&dispc_compat.irq_lock, flags);
	dispc_compat.irq_error_mask |= errors;
	_omap_dispc_set_irqs();
	spin_unlock_irqrestore(&dispc_compat.irq_lock, flags);

	dispc_runसमय_put();
पूर्ण

पूर्णांक dss_dispc_initialize_irq(व्योम)
अणु
	पूर्णांक r;

#अगर_घोषित CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
	spin_lock_init(&dispc_compat.irq_stats_lock);
	dispc_compat.irq_stats.last_reset = jअगरfies;
	dss_debugfs_create_file("dispc_irq", dispc_dump_irqs);
#पूर्ण_अगर

	spin_lock_init(&dispc_compat.irq_lock);

	स_रखो(dispc_compat.रेजिस्टरed_isr, 0,
			माप(dispc_compat.रेजिस्टरed_isr));

	dispc_compat.irq_error_mask = DISPC_IRQ_MASK_ERROR;
	अगर (dss_has_feature(FEAT_MGR_LCD2))
		dispc_compat.irq_error_mask |= DISPC_IRQ_SYNC_LOST2;
	अगर (dss_has_feature(FEAT_MGR_LCD3))
		dispc_compat.irq_error_mask |= DISPC_IRQ_SYNC_LOST3;
	अगर (dss_feat_get_num_ovls() > 3)
		dispc_compat.irq_error_mask |= DISPC_IRQ_VID3_FIFO_UNDERFLOW;

	/*
	 * there's SYNC_LOST_DIGIT रुकोing after enabling the DSS,
	 * so clear it
	 */
	dispc_clear_irqstatus(dispc_पढ़ो_irqstatus());

	INIT_WORK(&dispc_compat.error_work, dispc_error_worker);

	_omap_dispc_set_irqs();

	r = dispc_request_irq(omap_dispc_irq_handler, &dispc_compat);
	अगर (r) अणु
		DSSERR("dispc_request_irq failed\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

व्योम dss_dispc_uninitialize_irq(व्योम)
अणु
	dispc_मुक्त_irq(&dispc_compat);
पूर्ण

अटल व्योम dispc_mgr_disable_isr(व्योम *data, u32 mask)
अणु
	काष्ठा completion *compl = data;
	complete(compl);
पूर्ण

अटल व्योम dispc_mgr_enable_lcd_out(क्रमागत omap_channel channel)
अणु
	dispc_mgr_enable(channel, true);
पूर्ण

अटल व्योम dispc_mgr_disable_lcd_out(क्रमागत omap_channel channel)
अणु
	DECLARE_COMPLETION_ONSTACK(frameकरोne_compl);
	पूर्णांक r;
	u32 irq;

	अगर (!dispc_mgr_is_enabled(channel))
		वापस;

	/*
	 * When we disable LCD output, we need to रुको क्रम FRAMEDONE to know
	 * that DISPC has finished with the LCD output.
	 */

	irq = dispc_mgr_get_frameकरोne_irq(channel);

	r = omap_dispc_रेजिस्टर_isr(dispc_mgr_disable_isr, &frameकरोne_compl,
			irq);
	अगर (r)
		DSSERR("failed to register FRAMEDONE isr\n");

	dispc_mgr_enable(channel, false);

	/* अगर we couldn't रेजिस्टर क्रम frameकरोne, just sleep and निकास */
	अगर (r) अणु
		msleep(100);
		वापस;
	पूर्ण

	अगर (!रुको_क्रम_completion_समयout(&frameकरोne_compl,
				msecs_to_jअगरfies(100)))
		DSSERR("timeout waiting for FRAME DONE\n");

	r = omap_dispc_unरेजिस्टर_isr(dispc_mgr_disable_isr, &frameकरोne_compl,
			irq);
	अगर (r)
		DSSERR("failed to unregister FRAMEDONE isr\n");
पूर्ण

अटल व्योम dispc_digit_out_enable_isr(व्योम *data, u32 mask)
अणु
	काष्ठा completion *compl = data;

	/* ignore any sync lost पूर्णांकerrupts */
	अगर (mask & (DISPC_IRQ_EVSYNC_EVEN | DISPC_IRQ_EVSYNC_ODD))
		complete(compl);
पूर्ण

अटल व्योम dispc_mgr_enable_digit_out(व्योम)
अणु
	DECLARE_COMPLETION_ONSTACK(vsync_compl);
	पूर्णांक r;
	u32 irq_mask;

	अगर (dispc_mgr_is_enabled(OMAP_DSS_CHANNEL_DIGIT))
		वापस;

	/*
	 * Digit output produces some sync lost पूर्णांकerrupts during the first
	 * frame when enabling. Those need to be ignored, so we रेजिस्टर क्रम the
	 * sync lost irq to prevent the error handler from triggering.
	 */

	irq_mask = dispc_mgr_get_vsync_irq(OMAP_DSS_CHANNEL_DIGIT) |
		dispc_mgr_get_sync_lost_irq(OMAP_DSS_CHANNEL_DIGIT);

	r = omap_dispc_रेजिस्टर_isr(dispc_digit_out_enable_isr, &vsync_compl,
			irq_mask);
	अगर (r) अणु
		DSSERR("failed to register %x isr\n", irq_mask);
		वापस;
	पूर्ण

	dispc_mgr_enable(OMAP_DSS_CHANNEL_DIGIT, true);

	/* रुको क्रम the first evsync */
	अगर (!रुको_क्रम_completion_समयout(&vsync_compl, msecs_to_jअगरfies(100)))
		DSSERR("timeout waiting for digit out to start\n");

	r = omap_dispc_unरेजिस्टर_isr(dispc_digit_out_enable_isr, &vsync_compl,
			irq_mask);
	अगर (r)
		DSSERR("failed to unregister %x isr\n", irq_mask);
पूर्ण

अटल व्योम dispc_mgr_disable_digit_out(व्योम)
अणु
	DECLARE_COMPLETION_ONSTACK(frameकरोne_compl);
	पूर्णांक r, i;
	u32 irq_mask;
	पूर्णांक num_irqs;

	अगर (!dispc_mgr_is_enabled(OMAP_DSS_CHANNEL_DIGIT))
		वापस;

	/*
	 * When we disable the digit output, we need to रुको क्रम FRAMEDONE to
	 * know that DISPC has finished with the output.
	 */

	irq_mask = dispc_mgr_get_frameकरोne_irq(OMAP_DSS_CHANNEL_DIGIT);
	num_irqs = 1;

	अगर (!irq_mask) अणु
		/*
		 * omap 2/3 करोn't have frameकरोne irq क्रम TV, so we need to use
		 * vsyncs क्रम this.
		 */

		irq_mask = dispc_mgr_get_vsync_irq(OMAP_DSS_CHANNEL_DIGIT);
		/*
		 * We need to रुको क्रम both even and odd vsyncs. Note that this
		 * is not totally reliable, as we could get a vsync पूर्णांकerrupt
		 * beक्रमe we disable the output, which leads to समयout in the
		 * रुको_क्रम_completion.
		 */
		num_irqs = 2;
	पूर्ण

	r = omap_dispc_रेजिस्टर_isr(dispc_mgr_disable_isr, &frameकरोne_compl,
			irq_mask);
	अगर (r)
		DSSERR("failed to register %x isr\n", irq_mask);

	dispc_mgr_enable(OMAP_DSS_CHANNEL_DIGIT, false);

	/* अगर we couldn't रेजिस्टर the irq, just sleep and निकास */
	अगर (r) अणु
		msleep(100);
		वापस;
	पूर्ण

	क्रम (i = 0; i < num_irqs; ++i) अणु
		अगर (!रुको_क्रम_completion_समयout(&frameकरोne_compl,
					msecs_to_jअगरfies(100)))
			DSSERR("timeout waiting for digit out to stop\n");
	पूर्ण

	r = omap_dispc_unरेजिस्टर_isr(dispc_mgr_disable_isr, &frameकरोne_compl,
			irq_mask);
	अगर (r)
		DSSERR("failed to unregister %x isr\n", irq_mask);
पूर्ण

व्योम dispc_mgr_enable_sync(क्रमागत omap_channel channel)
अणु
	अगर (dss_mgr_is_lcd(channel))
		dispc_mgr_enable_lcd_out(channel);
	अन्यथा अगर (channel == OMAP_DSS_CHANNEL_DIGIT)
		dispc_mgr_enable_digit_out();
	अन्यथा
		WARN_ON(1);
पूर्ण

व्योम dispc_mgr_disable_sync(क्रमागत omap_channel channel)
अणु
	अगर (dss_mgr_is_lcd(channel))
		dispc_mgr_disable_lcd_out(channel);
	अन्यथा अगर (channel == OMAP_DSS_CHANNEL_DIGIT)
		dispc_mgr_disable_digit_out();
	अन्यथा
		WARN_ON(1);
पूर्ण

अटल अंतरभूत व्योम dispc_irq_रुको_handler(व्योम *data, u32 mask)
अणु
	complete((काष्ठा completion *)data);
पूर्ण

पूर्णांक omap_dispc_रुको_क्रम_irq_पूर्णांकerruptible_समयout(u32 irqmask,
		अचिन्हित दीर्घ समयout)
अणु

	पूर्णांक r;
	दीर्घ समय_left;
	DECLARE_COMPLETION_ONSTACK(completion);

	r = omap_dispc_रेजिस्टर_isr(dispc_irq_रुको_handler, &completion,
			irqmask);

	अगर (r)
		वापस r;

	समय_left = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&completion,
			समयout);

	omap_dispc_unरेजिस्टर_isr(dispc_irq_रुको_handler, &completion, irqmask);

	अगर (समय_left == 0)
		वापस -ETIMEDOUT;

	अगर (समय_left == -ERESTARTSYS)
		वापस -ERESTARTSYS;

	वापस 0;
पूर्ण
