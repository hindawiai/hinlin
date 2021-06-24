<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#घोषणा DSS_SUBSYS_NAME "DSI"

#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/regmap.h>
#समावेश <linux/पन.स>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/रुको.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/of.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/component.h>
#समावेश <linux/sys_soc.h>

#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_mipi_dsi.h>
#समावेश <drm/drm_panel.h>
#समावेश <video/mipi_display.h>

#समावेश "omapdss.h"
#समावेश "dss.h"

#घोषणा DSI_CATCH_MISSING_TE

#समावेश "dsi.h"

#घोषणा REG_GET(dsi, idx, start, end) \
	FLD_GET(dsi_पढ़ो_reg(dsi, idx), start, end)

#घोषणा REG_FLD_MOD(dsi, idx, val, start, end) \
	dsi_ग_लिखो_reg(dsi, idx, FLD_MOD(dsi_पढ़ो_reg(dsi, idx), val, start, end))

अटल पूर्णांक dsi_init_dispc(काष्ठा dsi_data *dsi);
अटल व्योम dsi_uninit_dispc(काष्ठा dsi_data *dsi);

अटल पूर्णांक dsi_vc_send_null(काष्ठा dsi_data *dsi, पूर्णांक vc, पूर्णांक channel);

अटल sमाप_प्रकार _omap_dsi_host_transfer(काष्ठा dsi_data *dsi, पूर्णांक vc,
				       स्थिर काष्ठा mipi_dsi_msg *msg);

#अगर_घोषित DSI_PERF_MEASURE
अटल bool dsi_perf;
module_param(dsi_perf, bool, 0644);
#पूर्ण_अगर

/* Note: क्रम some reason video mode seems to work only अगर VC_VIDEO is 0 */
#घोषणा VC_VIDEO	0
#घोषणा VC_CMD		1

#घोषणा drm_bridge_to_dsi(bridge) \
	container_of(bridge, काष्ठा dsi_data, bridge)

अटल अंतरभूत काष्ठा dsi_data *to_dsi_data(काष्ठा omap_dss_device *dssdev)
अणु
	वापस dev_get_drvdata(dssdev->dev);
पूर्ण

अटल अंतरभूत काष्ठा dsi_data *host_to_omap(काष्ठा mipi_dsi_host *host)
अणु
	वापस container_of(host, काष्ठा dsi_data, host);
पूर्ण

अटल अंतरभूत व्योम dsi_ग_लिखो_reg(काष्ठा dsi_data *dsi,
				 स्थिर काष्ठा dsi_reg idx, u32 val)
अणु
	व्योम __iomem *base;

	चयन(idx.module) अणु
		हाल DSI_PROTO: base = dsi->proto_base; अवरोध;
		हाल DSI_PHY: base = dsi->phy_base; अवरोध;
		हाल DSI_PLL: base = dsi->pll_base; अवरोध;
		शेष: वापस;
	पूर्ण

	__raw_ग_लिखोl(val, base + idx.idx);
पूर्ण

अटल अंतरभूत u32 dsi_पढ़ो_reg(काष्ठा dsi_data *dsi, स्थिर काष्ठा dsi_reg idx)
अणु
	व्योम __iomem *base;

	चयन(idx.module) अणु
		हाल DSI_PROTO: base = dsi->proto_base; अवरोध;
		हाल DSI_PHY: base = dsi->phy_base; अवरोध;
		हाल DSI_PLL: base = dsi->pll_base; अवरोध;
		शेष: वापस 0;
	पूर्ण

	वापस __raw_पढ़ोl(base + idx.idx);
पूर्ण

अटल व्योम dsi_bus_lock(काष्ठा dsi_data *dsi)
अणु
	करोwn(&dsi->bus_lock);
पूर्ण

अटल व्योम dsi_bus_unlock(काष्ठा dsi_data *dsi)
अणु
	up(&dsi->bus_lock);
पूर्ण

अटल bool dsi_bus_is_locked(काष्ठा dsi_data *dsi)
अणु
	वापस dsi->bus_lock.count == 0;
पूर्ण

अटल व्योम dsi_completion_handler(व्योम *data, u32 mask)
अणु
	complete((काष्ठा completion *)data);
पूर्ण

अटल अंतरभूत bool रुको_क्रम_bit_change(काष्ठा dsi_data *dsi,
				       स्थिर काष्ठा dsi_reg idx,
				       पूर्णांक bitnum, पूर्णांक value)
अणु
	अचिन्हित दीर्घ समयout;
	kसमय_प्रकार रुको;
	पूर्णांक t;

	/* first busyloop to see अगर the bit changes right away */
	t = 100;
	जबतक (t-- > 0) अणु
		अगर (REG_GET(dsi, idx, bitnum, bitnum) == value)
			वापस true;
	पूर्ण

	/* then loop क्रम 500ms, sleeping क्रम 1ms in between */
	समयout = jअगरfies + msecs_to_jअगरfies(500);
	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		अगर (REG_GET(dsi, idx, bitnum, bitnum) == value)
			वापस true;

		रुको = ns_to_kसमय(1000 * 1000);
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_hrसमयout(&रुको, HRTIMER_MODE_REL);
	पूर्ण

	वापस false;
पूर्ण

#अगर_घोषित DSI_PERF_MEASURE
अटल व्योम dsi_perf_mark_setup(काष्ठा dsi_data *dsi)
अणु
	dsi->perf_setup_समय = kसमय_get();
पूर्ण

अटल व्योम dsi_perf_mark_start(काष्ठा dsi_data *dsi)
अणु
	dsi->perf_start_समय = kसमय_get();
पूर्ण

अटल व्योम dsi_perf_show(काष्ठा dsi_data *dsi, स्थिर अक्षर *name)
अणु
	kसमय_प्रकार t, setup_समय, trans_समय;
	u32 total_bytes;
	u32 setup_us, trans_us, total_us;

	अगर (!dsi_perf)
		वापस;

	t = kसमय_get();

	setup_समय = kसमय_sub(dsi->perf_start_समय, dsi->perf_setup_समय);
	setup_us = (u32)kसमय_प्रकारo_us(setup_समय);
	अगर (setup_us == 0)
		setup_us = 1;

	trans_समय = kसमय_sub(t, dsi->perf_start_समय);
	trans_us = (u32)kसमय_प्रकारo_us(trans_समय);
	अगर (trans_us == 0)
		trans_us = 1;

	total_us = setup_us + trans_us;

	total_bytes = dsi->update_bytes;

	pr_info("DSI(%s): %u us + %u us = %u us (%uHz), %u bytes, %u kbytes/sec\n",
		name,
		setup_us,
		trans_us,
		total_us,
		1000 * 1000 / total_us,
		total_bytes,
		total_bytes * 1000 / total_us);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम dsi_perf_mark_setup(काष्ठा dsi_data *dsi)
अणु
पूर्ण

अटल अंतरभूत व्योम dsi_perf_mark_start(काष्ठा dsi_data *dsi)
अणु
पूर्ण

अटल अंतरभूत व्योम dsi_perf_show(काष्ठा dsi_data *dsi, स्थिर अक्षर *name)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक verbose_irq;

अटल व्योम prपूर्णांक_irq_status(u32 status)
अणु
	अगर (status == 0)
		वापस;

	अगर (!verbose_irq && (status & ~DSI_IRQ_CHANNEL_MASK) == 0)
		वापस;

#घोषणा PIS(x) (status & DSI_IRQ_##x) ? (#x " ") : ""

	pr_debug("DSI IRQ: 0x%x: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		status,
		verbose_irq ? PIS(VC0) : "",
		verbose_irq ? PIS(VC1) : "",
		verbose_irq ? PIS(VC2) : "",
		verbose_irq ? PIS(VC3) : "",
		PIS(WAKEUP),
		PIS(RESYNC),
		PIS(PLL_LOCK),
		PIS(PLL_UNLOCK),
		PIS(PLL_RECALL),
		PIS(COMPLEXIO_ERR),
		PIS(HS_TX_TIMEOUT),
		PIS(LP_RX_TIMEOUT),
		PIS(TE_TRIGGER),
		PIS(ACK_TRIGGER),
		PIS(SYNC_LOST),
		PIS(LDO_POWER_GOOD),
		PIS(TA_TIMEOUT));
#अघोषित PIS
पूर्ण

अटल व्योम prपूर्णांक_irq_status_vc(पूर्णांक vc, u32 status)
अणु
	अगर (status == 0)
		वापस;

	अगर (!verbose_irq && (status & ~DSI_VC_IRQ_PACKET_SENT) == 0)
		वापस;

#घोषणा PIS(x) (status & DSI_VC_IRQ_##x) ? (#x " ") : ""

	pr_debug("DSI VC(%d) IRQ 0x%x: %s%s%s%s%s%s%s%s%s\n",
		vc,
		status,
		PIS(CS),
		PIS(ECC_CORR),
		PIS(ECC_NO_CORR),
		verbose_irq ? PIS(PACKET_SENT) : "",
		PIS(BTA),
		PIS(FIFO_TX_OVF),
		PIS(FIFO_RX_OVF),
		PIS(FIFO_TX_UDF),
		PIS(PP_BUSY_CHANGE));
#अघोषित PIS
पूर्ण

अटल व्योम prपूर्णांक_irq_status_cio(u32 status)
अणु
	अगर (status == 0)
		वापस;

#घोषणा PIS(x) (status & DSI_CIO_IRQ_##x) ? (#x " ") : ""

	pr_debug("DSI CIO IRQ 0x%x: %s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s%s\n",
		status,
		PIS(ERRSYNCESC1),
		PIS(ERRSYNCESC2),
		PIS(ERRSYNCESC3),
		PIS(ERRESC1),
		PIS(ERRESC2),
		PIS(ERRESC3),
		PIS(ERRCONTROL1),
		PIS(ERRCONTROL2),
		PIS(ERRCONTROL3),
		PIS(STATEULPS1),
		PIS(STATEULPS2),
		PIS(STATEULPS3),
		PIS(ERRCONTENTIONLP0_1),
		PIS(ERRCONTENTIONLP1_1),
		PIS(ERRCONTENTIONLP0_2),
		PIS(ERRCONTENTIONLP1_2),
		PIS(ERRCONTENTIONLP0_3),
		PIS(ERRCONTENTIONLP1_3),
		PIS(ULPSACTIVENOT_ALL0),
		PIS(ULPSACTIVENOT_ALL1));
#अघोषित PIS
पूर्ण

#अगर_घोषित CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
अटल व्योम dsi_collect_irq_stats(काष्ठा dsi_data *dsi, u32 irqstatus,
				  u32 *vcstatus, u32 ciostatus)
अणु
	पूर्णांक i;

	spin_lock(&dsi->irq_stats_lock);

	dsi->irq_stats.irq_count++;
	dss_collect_irq_stats(irqstatus, dsi->irq_stats.dsi_irqs);

	क्रम (i = 0; i < 4; ++i)
		dss_collect_irq_stats(vcstatus[i], dsi->irq_stats.vc_irqs[i]);

	dss_collect_irq_stats(ciostatus, dsi->irq_stats.cio_irqs);

	spin_unlock(&dsi->irq_stats_lock);
पूर्ण
#अन्यथा
#घोषणा dsi_collect_irq_stats(dsi, irqstatus, vcstatus, ciostatus)
#पूर्ण_अगर

अटल पूर्णांक debug_irq;

अटल व्योम dsi_handle_irq_errors(काष्ठा dsi_data *dsi, u32 irqstatus,
				  u32 *vcstatus, u32 ciostatus)
अणु
	पूर्णांक i;

	अगर (irqstatus & DSI_IRQ_ERROR_MASK) अणु
		DSSERR("DSI error, irqstatus %x\n", irqstatus);
		prपूर्णांक_irq_status(irqstatus);
		spin_lock(&dsi->errors_lock);
		dsi->errors |= irqstatus & DSI_IRQ_ERROR_MASK;
		spin_unlock(&dsi->errors_lock);
	पूर्ण अन्यथा अगर (debug_irq) अणु
		prपूर्णांक_irq_status(irqstatus);
	पूर्ण

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (vcstatus[i] & DSI_VC_IRQ_ERROR_MASK) अणु
			DSSERR("DSI VC(%d) error, vc irqstatus %x\n",
				       i, vcstatus[i]);
			prपूर्णांक_irq_status_vc(i, vcstatus[i]);
		पूर्ण अन्यथा अगर (debug_irq) अणु
			prपूर्णांक_irq_status_vc(i, vcstatus[i]);
		पूर्ण
	पूर्ण

	अगर (ciostatus & DSI_CIO_IRQ_ERROR_MASK) अणु
		DSSERR("DSI CIO error, cio irqstatus %x\n", ciostatus);
		prपूर्णांक_irq_status_cio(ciostatus);
	पूर्ण अन्यथा अगर (debug_irq) अणु
		prपूर्णांक_irq_status_cio(ciostatus);
	पूर्ण
पूर्ण

अटल व्योम dsi_call_isrs(काष्ठा dsi_isr_data *isr_array,
		अचिन्हित पूर्णांक isr_array_size, u32 irqstatus)
अणु
	काष्ठा dsi_isr_data *isr_data;
	पूर्णांक i;

	क्रम (i = 0; i < isr_array_size; i++) अणु
		isr_data = &isr_array[i];
		अगर (isr_data->isr && isr_data->mask & irqstatus)
			isr_data->isr(isr_data->arg, irqstatus);
	पूर्ण
पूर्ण

अटल व्योम dsi_handle_isrs(काष्ठा dsi_isr_tables *isr_tables,
		u32 irqstatus, u32 *vcstatus, u32 ciostatus)
अणु
	पूर्णांक i;

	dsi_call_isrs(isr_tables->isr_table,
			ARRAY_SIZE(isr_tables->isr_table),
			irqstatus);

	क्रम (i = 0; i < 4; ++i) अणु
		अगर (vcstatus[i] == 0)
			जारी;
		dsi_call_isrs(isr_tables->isr_table_vc[i],
				ARRAY_SIZE(isr_tables->isr_table_vc[i]),
				vcstatus[i]);
	पूर्ण

	अगर (ciostatus != 0)
		dsi_call_isrs(isr_tables->isr_table_cio,
				ARRAY_SIZE(isr_tables->isr_table_cio),
				ciostatus);
पूर्ण

अटल irqवापस_t omap_dsi_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा dsi_data *dsi = arg;
	u32 irqstatus, vcstatus[4], ciostatus;
	पूर्णांक i;

	अगर (!dsi->is_enabled)
		वापस IRQ_NONE;

	spin_lock(&dsi->irq_lock);

	irqstatus = dsi_पढ़ो_reg(dsi, DSI_IRQSTATUS);

	/* IRQ is not क्रम us */
	अगर (!irqstatus) अणु
		spin_unlock(&dsi->irq_lock);
		वापस IRQ_NONE;
	पूर्ण

	dsi_ग_लिखो_reg(dsi, DSI_IRQSTATUS, irqstatus & ~DSI_IRQ_CHANNEL_MASK);
	/* flush posted ग_लिखो */
	dsi_पढ़ो_reg(dsi, DSI_IRQSTATUS);

	क्रम (i = 0; i < 4; ++i) अणु
		अगर ((irqstatus & (1 << i)) == 0) अणु
			vcstatus[i] = 0;
			जारी;
		पूर्ण

		vcstatus[i] = dsi_पढ़ो_reg(dsi, DSI_VC_IRQSTATUS(i));

		dsi_ग_लिखो_reg(dsi, DSI_VC_IRQSTATUS(i), vcstatus[i]);
		/* flush posted ग_लिखो */
		dsi_पढ़ो_reg(dsi, DSI_VC_IRQSTATUS(i));
	पूर्ण

	अगर (irqstatus & DSI_IRQ_COMPLEXIO_ERR) अणु
		ciostatus = dsi_पढ़ो_reg(dsi, DSI_COMPLEXIO_IRQ_STATUS);

		dsi_ग_लिखो_reg(dsi, DSI_COMPLEXIO_IRQ_STATUS, ciostatus);
		/* flush posted ग_लिखो */
		dsi_पढ़ो_reg(dsi, DSI_COMPLEXIO_IRQ_STATUS);
	पूर्ण अन्यथा अणु
		ciostatus = 0;
	पूर्ण

#अगर_घोषित DSI_CATCH_MISSING_TE
	अगर (irqstatus & DSI_IRQ_TE_TRIGGER)
		del_समयr(&dsi->te_समयr);
#पूर्ण_अगर

	/* make a copy and unlock, so that isrs can unरेजिस्टर
	 * themselves */
	स_नकल(&dsi->isr_tables_copy, &dsi->isr_tables,
		माप(dsi->isr_tables));

	spin_unlock(&dsi->irq_lock);

	dsi_handle_isrs(&dsi->isr_tables_copy, irqstatus, vcstatus, ciostatus);

	dsi_handle_irq_errors(dsi, irqstatus, vcstatus, ciostatus);

	dsi_collect_irq_stats(dsi, irqstatus, vcstatus, ciostatus);

	वापस IRQ_HANDLED;
पूर्ण

/* dsi->irq_lock has to be locked by the caller */
अटल व्योम _omap_dsi_configure_irqs(काष्ठा dsi_data *dsi,
				     काष्ठा dsi_isr_data *isr_array,
				     अचिन्हित पूर्णांक isr_array_size,
				     u32 शेष_mask,
				     स्थिर काष्ठा dsi_reg enable_reg,
				     स्थिर काष्ठा dsi_reg status_reg)
अणु
	काष्ठा dsi_isr_data *isr_data;
	u32 mask;
	u32 old_mask;
	पूर्णांक i;

	mask = शेष_mask;

	क्रम (i = 0; i < isr_array_size; i++) अणु
		isr_data = &isr_array[i];

		अगर (isr_data->isr == शून्य)
			जारी;

		mask |= isr_data->mask;
	पूर्ण

	old_mask = dsi_पढ़ो_reg(dsi, enable_reg);
	/* clear the irqstatus क्रम newly enabled irqs */
	dsi_ग_लिखो_reg(dsi, status_reg, (mask ^ old_mask) & mask);
	dsi_ग_लिखो_reg(dsi, enable_reg, mask);

	/* flush posted ग_लिखोs */
	dsi_पढ़ो_reg(dsi, enable_reg);
	dsi_पढ़ो_reg(dsi, status_reg);
पूर्ण

/* dsi->irq_lock has to be locked by the caller */
अटल व्योम _omap_dsi_set_irqs(काष्ठा dsi_data *dsi)
अणु
	u32 mask = DSI_IRQ_ERROR_MASK;
#अगर_घोषित DSI_CATCH_MISSING_TE
	mask |= DSI_IRQ_TE_TRIGGER;
#पूर्ण_अगर
	_omap_dsi_configure_irqs(dsi, dsi->isr_tables.isr_table,
			ARRAY_SIZE(dsi->isr_tables.isr_table), mask,
			DSI_IRQENABLE, DSI_IRQSTATUS);
पूर्ण

/* dsi->irq_lock has to be locked by the caller */
अटल व्योम _omap_dsi_set_irqs_vc(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	_omap_dsi_configure_irqs(dsi, dsi->isr_tables.isr_table_vc[vc],
			ARRAY_SIZE(dsi->isr_tables.isr_table_vc[vc]),
			DSI_VC_IRQ_ERROR_MASK,
			DSI_VC_IRQENABLE(vc), DSI_VC_IRQSTATUS(vc));
पूर्ण

/* dsi->irq_lock has to be locked by the caller */
अटल व्योम _omap_dsi_set_irqs_cio(काष्ठा dsi_data *dsi)
अणु
	_omap_dsi_configure_irqs(dsi, dsi->isr_tables.isr_table_cio,
			ARRAY_SIZE(dsi->isr_tables.isr_table_cio),
			DSI_CIO_IRQ_ERROR_MASK,
			DSI_COMPLEXIO_IRQ_ENABLE, DSI_COMPLEXIO_IRQ_STATUS);
पूर्ण

अटल व्योम _dsi_initialize_irq(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक vc;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	स_रखो(&dsi->isr_tables, 0, माप(dsi->isr_tables));

	_omap_dsi_set_irqs(dsi);
	क्रम (vc = 0; vc < 4; ++vc)
		_omap_dsi_set_irqs_vc(dsi, vc);
	_omap_dsi_set_irqs_cio(dsi);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);
पूर्ण

अटल पूर्णांक _dsi_रेजिस्टर_isr(omap_dsi_isr_t isr, व्योम *arg, u32 mask,
		काष्ठा dsi_isr_data *isr_array, अचिन्हित पूर्णांक isr_array_size)
अणु
	काष्ठा dsi_isr_data *isr_data;
	पूर्णांक मुक्त_idx;
	पूर्णांक i;

	BUG_ON(isr == शून्य);

	/* check क्रम duplicate entry and find a मुक्त slot */
	मुक्त_idx = -1;
	क्रम (i = 0; i < isr_array_size; i++) अणु
		isr_data = &isr_array[i];

		अगर (isr_data->isr == isr && isr_data->arg == arg &&
				isr_data->mask == mask) अणु
			वापस -EINVAL;
		पूर्ण

		अगर (isr_data->isr == शून्य && मुक्त_idx == -1)
			मुक्त_idx = i;
	पूर्ण

	अगर (मुक्त_idx == -1)
		वापस -EBUSY;

	isr_data = &isr_array[मुक्त_idx];
	isr_data->isr = isr;
	isr_data->arg = arg;
	isr_data->mask = mask;

	वापस 0;
पूर्ण

अटल पूर्णांक _dsi_unरेजिस्टर_isr(omap_dsi_isr_t isr, व्योम *arg, u32 mask,
		काष्ठा dsi_isr_data *isr_array, अचिन्हित पूर्णांक isr_array_size)
अणु
	काष्ठा dsi_isr_data *isr_data;
	पूर्णांक i;

	क्रम (i = 0; i < isr_array_size; i++) अणु
		isr_data = &isr_array[i];
		अगर (isr_data->isr != isr || isr_data->arg != arg ||
				isr_data->mask != mask)
			जारी;

		isr_data->isr = शून्य;
		isr_data->arg = शून्य;
		isr_data->mask = 0;

		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक dsi_रेजिस्टर_isr(काष्ठा dsi_data *dsi, omap_dsi_isr_t isr,
			    व्योम *arg, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	r = _dsi_रेजिस्टर_isr(isr, arg, mask, dsi->isr_tables.isr_table,
			ARRAY_SIZE(dsi->isr_tables.isr_table));

	अगर (r == 0)
		_omap_dsi_set_irqs(dsi);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);

	वापस r;
पूर्ण

अटल पूर्णांक dsi_unरेजिस्टर_isr(काष्ठा dsi_data *dsi, omap_dsi_isr_t isr,
			      व्योम *arg, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	r = _dsi_unरेजिस्टर_isr(isr, arg, mask, dsi->isr_tables.isr_table,
			ARRAY_SIZE(dsi->isr_tables.isr_table));

	अगर (r == 0)
		_omap_dsi_set_irqs(dsi);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);

	वापस r;
पूर्ण

अटल पूर्णांक dsi_रेजिस्टर_isr_vc(काष्ठा dsi_data *dsi, पूर्णांक vc,
			       omap_dsi_isr_t isr, व्योम *arg, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	r = _dsi_रेजिस्टर_isr(isr, arg, mask,
			dsi->isr_tables.isr_table_vc[vc],
			ARRAY_SIZE(dsi->isr_tables.isr_table_vc[vc]));

	अगर (r == 0)
		_omap_dsi_set_irqs_vc(dsi, vc);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);

	वापस r;
पूर्ण

अटल पूर्णांक dsi_unरेजिस्टर_isr_vc(काष्ठा dsi_data *dsi, पूर्णांक vc,
				 omap_dsi_isr_t isr, व्योम *arg, u32 mask)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&dsi->irq_lock, flags);

	r = _dsi_unरेजिस्टर_isr(isr, arg, mask,
			dsi->isr_tables.isr_table_vc[vc],
			ARRAY_SIZE(dsi->isr_tables.isr_table_vc[vc]));

	अगर (r == 0)
		_omap_dsi_set_irqs_vc(dsi, vc);

	spin_unlock_irqrestore(&dsi->irq_lock, flags);

	वापस r;
पूर्ण

अटल u32 dsi_get_errors(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित दीर्घ flags;
	u32 e;

	spin_lock_irqsave(&dsi->errors_lock, flags);
	e = dsi->errors;
	dsi->errors = 0;
	spin_unlock_irqrestore(&dsi->errors_lock, flags);
	वापस e;
पूर्ण

अटल पूर्णांक dsi_runसमय_get(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक r;

	DSSDBG("dsi_runtime_get\n");

	r = pm_runसमय_get_sync(dsi->dev);
	अगर (WARN_ON(r < 0)) अणु
		pm_runसमय_put_noidle(dsi->dev);
		वापस r;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम dsi_runसमय_put(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक r;

	DSSDBG("dsi_runtime_put\n");

	r = pm_runसमय_put_sync(dsi->dev);
	WARN_ON(r < 0 && r != -ENOSYS);
पूर्ण

अटल व्योम _dsi_prपूर्णांक_reset_status(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक b0, b1, b2;

	/* A dummy पढ़ो using the SCP पूर्णांकerface to any DSIPHY रेजिस्टर is
	 * required after DSIPHY reset to complete the reset of the DSI complex
	 * I/O. */
	dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG5);

	अगर (dsi->data->quirks & DSI_QUIRK_REVERSE_TXCLKESC) अणु
		b0 = 28;
		b1 = 27;
		b2 = 26;
	पूर्ण अन्यथा अणु
		b0 = 24;
		b1 = 25;
		b2 = 26;
	पूर्ण

#घोषणा DSI_FLD_GET(fld, start, end)\
	FLD_GET(dsi_पढ़ो_reg(dsi, DSI_##fld), start, end)

	pr_debug("DSI resets: PLL (%d) CIO (%d) PHY (%x%x%x, %d, %d, %d)\n",
		DSI_FLD_GET(PLL_STATUS, 0, 0),
		DSI_FLD_GET(COMPLEXIO_CFG1, 29, 29),
		DSI_FLD_GET(DSIPHY_CFG5, b0, b0),
		DSI_FLD_GET(DSIPHY_CFG5, b1, b1),
		DSI_FLD_GET(DSIPHY_CFG5, b2, b2),
		DSI_FLD_GET(DSIPHY_CFG5, 29, 29),
		DSI_FLD_GET(DSIPHY_CFG5, 30, 30),
		DSI_FLD_GET(DSIPHY_CFG5, 31, 31));

#अघोषित DSI_FLD_GET
पूर्ण

अटल अंतरभूत पूर्णांक dsi_अगर_enable(काष्ठा dsi_data *dsi, bool enable)
अणु
	DSSDBG("dsi_if_enable(%d)\n", enable);

	enable = enable ? 1 : 0;
	REG_FLD_MOD(dsi, DSI_CTRL, enable, 0, 0); /* IF_EN */

	अगर (!रुको_क्रम_bit_change(dsi, DSI_CTRL, 0, enable)) अणु
		DSSERR("Failed to set dsi_if_enable to %d\n", enable);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित दीर्घ dsi_get_pll_hsभाग_dispc_rate(काष्ठा dsi_data *dsi)
अणु
	वापस dsi->pll.cinfo.clkout[HSDIV_DISPC];
पूर्ण

अटल अचिन्हित दीर्घ dsi_get_pll_hsभाग_dsi_rate(काष्ठा dsi_data *dsi)
अणु
	वापस dsi->pll.cinfo.clkout[HSDIV_DSI];
पूर्ण

अटल अचिन्हित दीर्घ dsi_get_txbyteclkhs(काष्ठा dsi_data *dsi)
अणु
	वापस dsi->pll.cinfo.clkdco / 16;
पूर्ण

अटल अचिन्हित दीर्घ dsi_fclk_rate(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित दीर्घ r;
	क्रमागत dss_clk_source source;

	source = dss_get_dsi_clk_source(dsi->dss, dsi->module_id);
	अगर (source == DSS_CLK_SRC_FCK) अणु
		/* DSI FCLK source is DSS_CLK_FCK */
		r = clk_get_rate(dsi->dss_clk);
	पूर्ण अन्यथा अणु
		/* DSI FCLK source is dsi_pll_hsभाग_dsi_clk */
		r = dsi_get_pll_hsभाग_dsi_rate(dsi);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक dsi_lp_घड़ी_calc(अचिन्हित दीर्घ dsi_fclk,
		अचिन्हित दीर्घ lp_clk_min, अचिन्हित दीर्घ lp_clk_max,
		काष्ठा dsi_lp_घड़ी_info *lp_cinfo)
अणु
	अचिन्हित पूर्णांक lp_clk_भाग;
	अचिन्हित दीर्घ lp_clk;

	lp_clk_भाग = DIV_ROUND_UP(dsi_fclk, lp_clk_max * 2);
	lp_clk = dsi_fclk / 2 / lp_clk_भाग;

	अगर (lp_clk < lp_clk_min || lp_clk > lp_clk_max)
		वापस -EINVAL;

	lp_cinfo->lp_clk_भाग = lp_clk_भाग;
	lp_cinfo->lp_clk = lp_clk;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_set_lp_clk_भागisor(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित दीर्घ dsi_fclk;
	अचिन्हित पूर्णांक lp_clk_भाग;
	अचिन्हित दीर्घ lp_clk;
	अचिन्हित पूर्णांक lpभाग_max = dsi->data->max_pll_lpभाग;


	lp_clk_भाग = dsi->user_lp_cinfo.lp_clk_भाग;

	अगर (lp_clk_भाग == 0 || lp_clk_भाग > lpभाग_max)
		वापस -EINVAL;

	dsi_fclk = dsi_fclk_rate(dsi);

	lp_clk = dsi_fclk / 2 / lp_clk_भाग;

	DSSDBG("LP_CLK_DIV %u, LP_CLK %lu\n", lp_clk_भाग, lp_clk);
	dsi->current_lp_cinfo.lp_clk = lp_clk;
	dsi->current_lp_cinfo.lp_clk_भाग = lp_clk_भाग;

	/* LP_CLK_DIVISOR */
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, lp_clk_भाग, 12, 0);

	/* LP_RX_SYNCHRO_ENABLE */
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, dsi_fclk > 30000000 ? 1 : 0, 21, 21);

	वापस 0;
पूर्ण

अटल व्योम dsi_enable_scp_clk(काष्ठा dsi_data *dsi)
अणु
	अगर (dsi->scp_clk_refcount++ == 0)
		REG_FLD_MOD(dsi, DSI_CLK_CTRL, 1, 14, 14); /* CIO_CLK_ICG */
पूर्ण

अटल व्योम dsi_disable_scp_clk(काष्ठा dsi_data *dsi)
अणु
	WARN_ON(dsi->scp_clk_refcount == 0);
	अगर (--dsi->scp_clk_refcount == 0)
		REG_FLD_MOD(dsi, DSI_CLK_CTRL, 0, 14, 14); /* CIO_CLK_ICG */
पूर्ण

क्रमागत dsi_pll_घातer_state अणु
	DSI_PLL_POWER_OFF	= 0x0,
	DSI_PLL_POWER_ON_HSCLK	= 0x1,
	DSI_PLL_POWER_ON_ALL	= 0x2,
	DSI_PLL_POWER_ON_DIV	= 0x3,
पूर्ण;

अटल पूर्णांक dsi_pll_घातer(काष्ठा dsi_data *dsi, क्रमागत dsi_pll_घातer_state state)
अणु
	पूर्णांक t = 0;

	/* DSI-PLL घातer command 0x3 is not working */
	अगर ((dsi->data->quirks & DSI_QUIRK_PLL_PWR_BUG) &&
	    state == DSI_PLL_POWER_ON_DIV)
		state = DSI_PLL_POWER_ON_ALL;

	/* PLL_PWR_CMD */
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, state, 31, 30);

	/* PLL_PWR_STATUS */
	जबतक (FLD_GET(dsi_पढ़ो_reg(dsi, DSI_CLK_CTRL), 29, 28) != state) अणु
		अगर (++t > 1000) अणु
			DSSERR("Failed to set DSI PLL power mode to %d\n",
					state);
			वापस -ENODEV;
		पूर्ण
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण


अटल व्योम dsi_pll_calc_dsi_fck(काष्ठा dsi_data *dsi,
				 काष्ठा dss_pll_घड़ी_info *cinfo)
अणु
	अचिन्हित दीर्घ max_dsi_fck;

	max_dsi_fck = dsi->data->max_fck_freq;

	cinfo->mX[HSDIV_DSI] = DIV_ROUND_UP(cinfo->clkdco, max_dsi_fck);
	cinfo->clkout[HSDIV_DSI] = cinfo->clkdco / cinfo->mX[HSDIV_DSI];
पूर्ण

अटल पूर्णांक dsi_pll_enable(काष्ठा dss_pll *pll)
अणु
	काष्ठा dsi_data *dsi = container_of(pll, काष्ठा dsi_data, pll);
	पूर्णांक r = 0;

	DSSDBG("PLL init\n");

	r = dsi_runसमय_get(dsi);
	अगर (r)
		वापस r;

	/*
	 * Note: SCP CLK is not required on OMAP3, but it is required on OMAP4.
	 */
	dsi_enable_scp_clk(dsi);

	r = regulator_enable(dsi->vdds_dsi_reg);
	अगर (r)
		जाओ err0;

	/* XXX PLL करोes not come out of reset without this... */
	dispc_pck_मुक्त_enable(dsi->dss->dispc, 1);

	अगर (!रुको_क्रम_bit_change(dsi, DSI_PLL_STATUS, 0, 1)) अणु
		DSSERR("PLL not coming out of reset.\n");
		r = -ENODEV;
		dispc_pck_मुक्त_enable(dsi->dss->dispc, 0);
		जाओ err1;
	पूर्ण

	/* XXX ... but अगर left on, we get problems when planes करो not
	 * fill the whole display. No idea about this */
	dispc_pck_मुक्त_enable(dsi->dss->dispc, 0);

	r = dsi_pll_घातer(dsi, DSI_PLL_POWER_ON_ALL);

	अगर (r)
		जाओ err1;

	DSSDBG("PLL init done\n");

	वापस 0;
err1:
	regulator_disable(dsi->vdds_dsi_reg);
err0:
	dsi_disable_scp_clk(dsi);
	dsi_runसमय_put(dsi);
	वापस r;
पूर्ण

अटल व्योम dsi_pll_disable(काष्ठा dss_pll *pll)
अणु
	काष्ठा dsi_data *dsi = container_of(pll, काष्ठा dsi_data, pll);

	dsi_pll_घातer(dsi, DSI_PLL_POWER_OFF);

	regulator_disable(dsi->vdds_dsi_reg);

	dsi_disable_scp_clk(dsi);
	dsi_runसमय_put(dsi);

	DSSDBG("PLL disable done\n");
पूर्ण

अटल पूर्णांक dsi_dump_dsi_घड़ीs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा dsi_data *dsi = s->निजी;
	काष्ठा dss_pll_घड़ी_info *cinfo = &dsi->pll.cinfo;
	क्रमागत dss_clk_source dispc_clk_src, dsi_clk_src;
	पूर्णांक dsi_module = dsi->module_id;
	काष्ठा dss_pll *pll = &dsi->pll;

	dispc_clk_src = dss_get_dispc_clk_source(dsi->dss);
	dsi_clk_src = dss_get_dsi_clk_source(dsi->dss, dsi_module);

	अगर (dsi_runसमय_get(dsi))
		वापस 0;

	seq_म_लिखो(s,	"- DSI%d PLL -\n", dsi_module + 1);

	seq_म_लिखो(s,	"dsi pll clkin\t%lu\n", clk_get_rate(pll->clkin));

	seq_म_लिखो(s,	"Fint\t\t%-16lun %u\n", cinfo->fपूर्णांक, cinfo->n);

	seq_म_लिखो(s,	"CLKIN4DDR\t%-16lum %u\n",
			cinfo->clkdco, cinfo->m);

	seq_म_लिखो(s,	"DSI_PLL_HSDIV_DISPC (%s)\t%-16lum_dispc %u\t(%s)\n",
			dss_get_clk_source_name(dsi_module == 0 ?
				DSS_CLK_SRC_PLL1_1 :
				DSS_CLK_SRC_PLL2_1),
			cinfo->clkout[HSDIV_DISPC],
			cinfo->mX[HSDIV_DISPC],
			dispc_clk_src == DSS_CLK_SRC_FCK ?
			"off" : "on");

	seq_म_लिखो(s,	"DSI_PLL_HSDIV_DSI (%s)\t%-16lum_dsi %u\t(%s)\n",
			dss_get_clk_source_name(dsi_module == 0 ?
				DSS_CLK_SRC_PLL1_2 :
				DSS_CLK_SRC_PLL2_2),
			cinfo->clkout[HSDIV_DSI],
			cinfo->mX[HSDIV_DSI],
			dsi_clk_src == DSS_CLK_SRC_FCK ?
			"off" : "on");

	seq_म_लिखो(s,	"- DSI%d -\n", dsi_module + 1);

	seq_म_लिखो(s,	"dsi fclk source = %s\n",
			dss_get_clk_source_name(dsi_clk_src));

	seq_म_लिखो(s,	"DSI_FCLK\t%lu\n", dsi_fclk_rate(dsi));

	seq_म_लिखो(s,	"DDR_CLK\t\t%lu\n",
			cinfo->clkdco / 4);

	seq_म_लिखो(s,	"TxByteClkHS\t%lu\n", dsi_get_txbyteclkhs(dsi));

	seq_म_लिखो(s,	"LP_CLK\t\t%lu\n", dsi->current_lp_cinfo.lp_clk);

	dsi_runसमय_put(dsi);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
अटल पूर्णांक dsi_dump_dsi_irqs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा dsi_data *dsi = s->निजी;
	अचिन्हित दीर्घ flags;
	काष्ठा dsi_irq_stats stats;

	spin_lock_irqsave(&dsi->irq_stats_lock, flags);

	stats = dsi->irq_stats;
	स_रखो(&dsi->irq_stats, 0, माप(dsi->irq_stats));
	dsi->irq_stats.last_reset = jअगरfies;

	spin_unlock_irqrestore(&dsi->irq_stats_lock, flags);

	seq_म_लिखो(s, "period %u ms\n",
			jअगरfies_to_msecs(jअगरfies - stats.last_reset));

	seq_म_लिखो(s, "irqs %d\n", stats.irq_count);
#घोषणा PIS(x) \
	seq_म_लिखो(s, "%-20s %10d\n", #x, stats.dsi_irqs[ffs(DSI_IRQ_##x)-1]);

	seq_म_लिखो(s, "-- DSI%d interrupts --\n", dsi->module_id + 1);
	PIS(VC0);
	PIS(VC1);
	PIS(VC2);
	PIS(VC3);
	PIS(WAKEUP);
	PIS(RESYNC);
	PIS(PLL_LOCK);
	PIS(PLL_UNLOCK);
	PIS(PLL_RECALL);
	PIS(COMPLEXIO_ERR);
	PIS(HS_TX_TIMEOUT);
	PIS(LP_RX_TIMEOUT);
	PIS(TE_TRIGGER);
	PIS(ACK_TRIGGER);
	PIS(SYNC_LOST);
	PIS(LDO_POWER_GOOD);
	PIS(TA_TIMEOUT);
#अघोषित PIS

#घोषणा PIS(x) \
	seq_म_लिखो(s, "%-20s %10d %10d %10d %10d\n", #x, \
			stats.vc_irqs[0][ffs(DSI_VC_IRQ_##x)-1], \
			stats.vc_irqs[1][ffs(DSI_VC_IRQ_##x)-1], \
			stats.vc_irqs[2][ffs(DSI_VC_IRQ_##x)-1], \
			stats.vc_irqs[3][ffs(DSI_VC_IRQ_##x)-1]);

	seq_म_लिखो(s, "-- VC interrupts --\n");
	PIS(CS);
	PIS(ECC_CORR);
	PIS(PACKET_SENT);
	PIS(FIFO_TX_OVF);
	PIS(FIFO_RX_OVF);
	PIS(BTA);
	PIS(ECC_NO_CORR);
	PIS(FIFO_TX_UDF);
	PIS(PP_BUSY_CHANGE);
#अघोषित PIS

#घोषणा PIS(x) \
	seq_म_लिखो(s, "%-20s %10d\n", #x, \
			stats.cio_irqs[ffs(DSI_CIO_IRQ_##x)-1]);

	seq_म_लिखो(s, "-- CIO interrupts --\n");
	PIS(ERRSYNCESC1);
	PIS(ERRSYNCESC2);
	PIS(ERRSYNCESC3);
	PIS(ERRESC1);
	PIS(ERRESC2);
	PIS(ERRESC3);
	PIS(ERRCONTROL1);
	PIS(ERRCONTROL2);
	PIS(ERRCONTROL3);
	PIS(STATEULPS1);
	PIS(STATEULPS2);
	PIS(STATEULPS3);
	PIS(ERRCONTENTIONLP0_1);
	PIS(ERRCONTENTIONLP1_1);
	PIS(ERRCONTENTIONLP0_2);
	PIS(ERRCONTENTIONLP1_2);
	PIS(ERRCONTENTIONLP0_3);
	PIS(ERRCONTENTIONLP1_3);
	PIS(ULPSACTIVENOT_ALL0);
	PIS(ULPSACTIVENOT_ALL1);
#अघोषित PIS

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dsi_dump_dsi_regs(काष्ठा seq_file *s, व्योम *p)
अणु
	काष्ठा dsi_data *dsi = s->निजी;

	अगर (dsi_runसमय_get(dsi))
		वापस 0;
	dsi_enable_scp_clk(dsi);

#घोषणा DUMPREG(r) seq_म_लिखो(s, "%-35s %08x\n", #r, dsi_पढ़ो_reg(dsi, r))
	DUMPREG(DSI_REVISION);
	DUMPREG(DSI_SYSCONFIG);
	DUMPREG(DSI_SYSSTATUS);
	DUMPREG(DSI_IRQSTATUS);
	DUMPREG(DSI_IRQENABLE);
	DUMPREG(DSI_CTRL);
	DUMPREG(DSI_COMPLEXIO_CFG1);
	DUMPREG(DSI_COMPLEXIO_IRQ_STATUS);
	DUMPREG(DSI_COMPLEXIO_IRQ_ENABLE);
	DUMPREG(DSI_CLK_CTRL);
	DUMPREG(DSI_TIMING1);
	DUMPREG(DSI_TIMING2);
	DUMPREG(DSI_VM_TIMING1);
	DUMPREG(DSI_VM_TIMING2);
	DUMPREG(DSI_VM_TIMING3);
	DUMPREG(DSI_CLK_TIMING);
	DUMPREG(DSI_TX_FIFO_VC_SIZE);
	DUMPREG(DSI_RX_FIFO_VC_SIZE);
	DUMPREG(DSI_COMPLEXIO_CFG2);
	DUMPREG(DSI_RX_FIFO_VC_FULLNESS);
	DUMPREG(DSI_VM_TIMING4);
	DUMPREG(DSI_TX_FIFO_VC_EMPTINESS);
	DUMPREG(DSI_VM_TIMING5);
	DUMPREG(DSI_VM_TIMING6);
	DUMPREG(DSI_VM_TIMING7);
	DUMPREG(DSI_STOPCLK_TIMING);

	DUMPREG(DSI_VC_CTRL(0));
	DUMPREG(DSI_VC_TE(0));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(0));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(0));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(0));
	DUMPREG(DSI_VC_IRQSTATUS(0));
	DUMPREG(DSI_VC_IRQENABLE(0));

	DUMPREG(DSI_VC_CTRL(1));
	DUMPREG(DSI_VC_TE(1));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(1));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(1));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(1));
	DUMPREG(DSI_VC_IRQSTATUS(1));
	DUMPREG(DSI_VC_IRQENABLE(1));

	DUMPREG(DSI_VC_CTRL(2));
	DUMPREG(DSI_VC_TE(2));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(2));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(2));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(2));
	DUMPREG(DSI_VC_IRQSTATUS(2));
	DUMPREG(DSI_VC_IRQENABLE(2));

	DUMPREG(DSI_VC_CTRL(3));
	DUMPREG(DSI_VC_TE(3));
	DUMPREG(DSI_VC_LONG_PACKET_HEADER(3));
	DUMPREG(DSI_VC_LONG_PACKET_PAYLOAD(3));
	DUMPREG(DSI_VC_SHORT_PACKET_HEADER(3));
	DUMPREG(DSI_VC_IRQSTATUS(3));
	DUMPREG(DSI_VC_IRQENABLE(3));

	DUMPREG(DSI_DSIPHY_CFG0);
	DUMPREG(DSI_DSIPHY_CFG1);
	DUMPREG(DSI_DSIPHY_CFG2);
	DUMPREG(DSI_DSIPHY_CFG5);

	DUMPREG(DSI_PLL_CONTROL);
	DUMPREG(DSI_PLL_STATUS);
	DUMPREG(DSI_PLL_GO);
	DUMPREG(DSI_PLL_CONFIGURATION1);
	DUMPREG(DSI_PLL_CONFIGURATION2);
#अघोषित DUMPREG

	dsi_disable_scp_clk(dsi);
	dsi_runसमय_put(dsi);

	वापस 0;
पूर्ण

क्रमागत dsi_cio_घातer_state अणु
	DSI_COMPLEXIO_POWER_OFF		= 0x0,
	DSI_COMPLEXIO_POWER_ON		= 0x1,
	DSI_COMPLEXIO_POWER_ULPS	= 0x2,
पूर्ण;

अटल पूर्णांक dsi_cio_घातer(काष्ठा dsi_data *dsi, क्रमागत dsi_cio_घातer_state state)
अणु
	पूर्णांक t = 0;

	/* PWR_CMD */
	REG_FLD_MOD(dsi, DSI_COMPLEXIO_CFG1, state, 28, 27);

	/* PWR_STATUS */
	जबतक (FLD_GET(dsi_पढ़ो_reg(dsi, DSI_COMPLEXIO_CFG1),
			26, 25) != state) अणु
		अगर (++t > 1000) अणु
			DSSERR("failed to set complexio power state to "
					"%d\n", state);
			वापस -ENODEV;
		पूर्ण
		udelay(1);
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक dsi_get_line_buf_size(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक val;

	/* line buffer on OMAP3 is 1024 x 24bits */
	/* XXX: क्रम some reason using full buffer size causes
	 * considerable TX slowकरोwn with update sizes that fill the
	 * whole buffer */
	अगर (!(dsi->data->quirks & DSI_QUIRK_GNQ))
		वापस 1023 * 3;

	val = REG_GET(dsi, DSI_GNQ, 14, 12); /* VP1_LINE_BUFFER_SIZE */

	चयन (val) अणु
	हाल 1:
		वापस 512 * 3;		/* 512x24 bits */
	हाल 2:
		वापस 682 * 3;		/* 682x24 bits */
	हाल 3:
		वापस 853 * 3;		/* 853x24 bits */
	हाल 4:
		वापस 1024 * 3;	/* 1024x24 bits */
	हाल 5:
		वापस 1194 * 3;	/* 1194x24 bits */
	हाल 6:
		वापस 1365 * 3;	/* 1365x24 bits */
	हाल 7:
		वापस 1920 * 3;	/* 1920x24 bits */
	शेष:
		BUG();
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक dsi_set_lane_config(काष्ठा dsi_data *dsi)
अणु
	अटल स्थिर u8 offsets[] = अणु 0, 4, 8, 12, 16 पूर्ण;
	अटल स्थिर क्रमागत dsi_lane_function functions[] = अणु
		DSI_LANE_CLK,
		DSI_LANE_DATA1,
		DSI_LANE_DATA2,
		DSI_LANE_DATA3,
		DSI_LANE_DATA4,
	पूर्ण;
	u32 r;
	पूर्णांक i;

	r = dsi_पढ़ो_reg(dsi, DSI_COMPLEXIO_CFG1);

	क्रम (i = 0; i < dsi->num_lanes_used; ++i) अणु
		अचिन्हित पूर्णांक offset = offsets[i];
		अचिन्हित पूर्णांक polarity, lane_number;
		अचिन्हित पूर्णांक t;

		क्रम (t = 0; t < dsi->num_lanes_supported; ++t)
			अगर (dsi->lanes[t].function == functions[i])
				अवरोध;

		अगर (t == dsi->num_lanes_supported)
			वापस -EINVAL;

		lane_number = t;
		polarity = dsi->lanes[t].polarity;

		r = FLD_MOD(r, lane_number + 1, offset + 2, offset);
		r = FLD_MOD(r, polarity, offset + 3, offset + 3);
	पूर्ण

	/* clear the unused lanes */
	क्रम (; i < dsi->num_lanes_supported; ++i) अणु
		अचिन्हित पूर्णांक offset = offsets[i];

		r = FLD_MOD(r, 0, offset + 2, offset);
		r = FLD_MOD(r, 0, offset + 3, offset + 3);
	पूर्ण

	dsi_ग_लिखो_reg(dsi, DSI_COMPLEXIO_CFG1, r);

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ns2ddr(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक ns)
अणु
	/* convert समय in ns to ddr ticks, rounding up */
	अचिन्हित दीर्घ ddr_clk = dsi->pll.cinfo.clkdco / 4;

	वापस (ns * (ddr_clk / 1000 / 1000) + 999) / 1000;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ddr2ns(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक ddr)
अणु
	अचिन्हित दीर्घ ddr_clk = dsi->pll.cinfo.clkdco / 4;

	वापस ddr * 1000 * 1000 / (ddr_clk / 1000);
पूर्ण

अटल व्योम dsi_cio_timings(काष्ठा dsi_data *dsi)
अणु
	u32 r;
	u32 ths_prepare, ths_prepare_ths_zero, ths_trail, ths_निकास;
	u32 tlpx_half, tclk_trail, tclk_zero;
	u32 tclk_prepare;

	/* calculate timings */

	/* 1 * DDR_CLK = 2 * UI */

	/* min 40ns + 4*UI	max 85ns + 6*UI */
	ths_prepare = ns2ddr(dsi, 70) + 2;

	/* min 145ns + 10*UI */
	ths_prepare_ths_zero = ns2ddr(dsi, 175) + 2;

	/* min max(8*UI, 60ns+4*UI) */
	ths_trail = ns2ddr(dsi, 60) + 5;

	/* min 100ns */
	ths_निकास = ns2ddr(dsi, 145);

	/* tlpx min 50n */
	tlpx_half = ns2ddr(dsi, 25);

	/* min 60ns */
	tclk_trail = ns2ddr(dsi, 60) + 2;

	/* min 38ns, max 95ns */
	tclk_prepare = ns2ddr(dsi, 65);

	/* min tclk-prepare + tclk-zero = 300ns */
	tclk_zero = ns2ddr(dsi, 260);

	DSSDBG("ths_prepare %u (%uns), ths_prepare_ths_zero %u (%uns)\n",
		ths_prepare, ddr2ns(dsi, ths_prepare),
		ths_prepare_ths_zero, ddr2ns(dsi, ths_prepare_ths_zero));
	DSSDBG("ths_trail %u (%uns), ths_exit %u (%uns)\n",
			ths_trail, ddr2ns(dsi, ths_trail),
			ths_निकास, ddr2ns(dsi, ths_निकास));

	DSSDBG("tlpx_half %u (%uns), tclk_trail %u (%uns), "
			"tclk_zero %u (%uns)\n",
			tlpx_half, ddr2ns(dsi, tlpx_half),
			tclk_trail, ddr2ns(dsi, tclk_trail),
			tclk_zero, ddr2ns(dsi, tclk_zero));
	DSSDBG("tclk_prepare %u (%uns)\n",
			tclk_prepare, ddr2ns(dsi, tclk_prepare));

	/* program timings */

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG0);
	r = FLD_MOD(r, ths_prepare, 31, 24);
	r = FLD_MOD(r, ths_prepare_ths_zero, 23, 16);
	r = FLD_MOD(r, ths_trail, 15, 8);
	r = FLD_MOD(r, ths_निकास, 7, 0);
	dsi_ग_लिखो_reg(dsi, DSI_DSIPHY_CFG0, r);

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG1);
	r = FLD_MOD(r, tlpx_half, 20, 16);
	r = FLD_MOD(r, tclk_trail, 15, 8);
	r = FLD_MOD(r, tclk_zero, 7, 0);

	अगर (dsi->data->quirks & DSI_QUIRK_PHY_DCC) अणु
		r = FLD_MOD(r, 0, 21, 21);	/* DCCEN = disable */
		r = FLD_MOD(r, 1, 22, 22);	/* CLKINP_DIVBY2EN = enable */
		r = FLD_MOD(r, 1, 23, 23);	/* CLKINP_SEL = enable */
	पूर्ण

	dsi_ग_लिखो_reg(dsi, DSI_DSIPHY_CFG1, r);

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG2);
	r = FLD_MOD(r, tclk_prepare, 7, 0);
	dsi_ग_लिखो_reg(dsi, DSI_DSIPHY_CFG2, r);
पूर्ण

अटल पूर्णांक dsi_cio_रुको_tx_clk_esc_reset(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक t, i;
	bool in_use[DSI_MAX_NR_LANES];
	अटल स्थिर u8 offsets_old[] = अणु 28, 27, 26 पूर्ण;
	अटल स्थिर u8 offsets_new[] = अणु 24, 25, 26, 27, 28 पूर्ण;
	स्थिर u8 *offsets;

	अगर (dsi->data->quirks & DSI_QUIRK_REVERSE_TXCLKESC)
		offsets = offsets_old;
	अन्यथा
		offsets = offsets_new;

	क्रम (i = 0; i < dsi->num_lanes_supported; ++i)
		in_use[i] = dsi->lanes[i].function != DSI_LANE_UNUSED;

	t = 100000;
	जबतक (true) अणु
		u32 l;
		पूर्णांक ok;

		l = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG5);

		ok = 0;
		क्रम (i = 0; i < dsi->num_lanes_supported; ++i) अणु
			अगर (!in_use[i] || (l & (1 << offsets[i])))
				ok++;
		पूर्ण

		अगर (ok == dsi->num_lanes_supported)
			अवरोध;

		अगर (--t == 0) अणु
			क्रम (i = 0; i < dsi->num_lanes_supported; ++i) अणु
				अगर (!in_use[i] || (l & (1 << offsets[i])))
					जारी;

				DSSERR("CIO TXCLKESC%d domain not coming " \
						"out of reset\n", i);
			पूर्ण
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* वापस biपंचांगask of enabled lanes, lane0 being the lsb */
अटल अचिन्हित पूर्णांक dsi_get_lane_mask(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित पूर्णांक mask = 0;
	पूर्णांक i;

	क्रम (i = 0; i < dsi->num_lanes_supported; ++i) अणु
		अगर (dsi->lanes[i].function != DSI_LANE_UNUSED)
			mask |= 1 << i;
	पूर्ण

	वापस mask;
पूर्ण

/* OMAP4 CONTROL_DSIPHY */
#घोषणा OMAP4_DSIPHY_SYSCON_OFFSET			0x78

#घोषणा OMAP4_DSI2_LANEENABLE_SHIFT			29
#घोषणा OMAP4_DSI2_LANEENABLE_MASK			(0x7 << 29)
#घोषणा OMAP4_DSI1_LANEENABLE_SHIFT			24
#घोषणा OMAP4_DSI1_LANEENABLE_MASK			(0x1f << 24)
#घोषणा OMAP4_DSI1_PIPD_SHIFT				19
#घोषणा OMAP4_DSI1_PIPD_MASK				(0x1f << 19)
#घोषणा OMAP4_DSI2_PIPD_SHIFT				14
#घोषणा OMAP4_DSI2_PIPD_MASK				(0x1f << 14)

अटल पूर्णांक dsi_omap4_mux_pads(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक lanes)
अणु
	u32 enable_mask, enable_shअगरt;
	u32 pipd_mask, pipd_shअगरt;

	अगर (dsi->module_id == 0) अणु
		enable_mask = OMAP4_DSI1_LANEENABLE_MASK;
		enable_shअगरt = OMAP4_DSI1_LANEENABLE_SHIFT;
		pipd_mask = OMAP4_DSI1_PIPD_MASK;
		pipd_shअगरt = OMAP4_DSI1_PIPD_SHIFT;
	पूर्ण अन्यथा अगर (dsi->module_id == 1) अणु
		enable_mask = OMAP4_DSI2_LANEENABLE_MASK;
		enable_shअगरt = OMAP4_DSI2_LANEENABLE_SHIFT;
		pipd_mask = OMAP4_DSI2_PIPD_MASK;
		pipd_shअगरt = OMAP4_DSI2_PIPD_SHIFT;
	पूर्ण अन्यथा अणु
		वापस -ENODEV;
	पूर्ण

	वापस regmap_update_bits(dsi->syscon, OMAP4_DSIPHY_SYSCON_OFFSET,
		enable_mask | pipd_mask,
		(lanes << enable_shअगरt) | (lanes << pipd_shअगरt));
पूर्ण

/* OMAP5 CONTROL_DSIPHY */

#घोषणा OMAP5_DSIPHY_SYSCON_OFFSET	0x74

#घोषणा OMAP5_DSI1_LANEENABLE_SHIFT	24
#घोषणा OMAP5_DSI2_LANEENABLE_SHIFT	19
#घोषणा OMAP5_DSI_LANEENABLE_MASK	0x1f

अटल पूर्णांक dsi_omap5_mux_pads(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक lanes)
अणु
	u32 enable_shअगरt;

	अगर (dsi->module_id == 0)
		enable_shअगरt = OMAP5_DSI1_LANEENABLE_SHIFT;
	अन्यथा अगर (dsi->module_id == 1)
		enable_shअगरt = OMAP5_DSI2_LANEENABLE_SHIFT;
	अन्यथा
		वापस -ENODEV;

	वापस regmap_update_bits(dsi->syscon, OMAP5_DSIPHY_SYSCON_OFFSET,
		OMAP5_DSI_LANEENABLE_MASK << enable_shअगरt,
		lanes << enable_shअगरt);
पूर्ण

अटल पूर्णांक dsi_enable_pads(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक lane_mask)
अणु
	अगर (dsi->data->model == DSI_MODEL_OMAP4)
		वापस dsi_omap4_mux_pads(dsi, lane_mask);
	अगर (dsi->data->model == DSI_MODEL_OMAP5)
		वापस dsi_omap5_mux_pads(dsi, lane_mask);
	वापस 0;
पूर्ण

अटल व्योम dsi_disable_pads(काष्ठा dsi_data *dsi)
अणु
	अगर (dsi->data->model == DSI_MODEL_OMAP4)
		dsi_omap4_mux_pads(dsi, 0);
	अन्यथा अगर (dsi->data->model == DSI_MODEL_OMAP5)
		dsi_omap5_mux_pads(dsi, 0);
पूर्ण

अटल पूर्णांक dsi_cio_init(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक r;
	u32 l;

	DSSDBG("DSI CIO init starts");

	r = dsi_enable_pads(dsi, dsi_get_lane_mask(dsi));
	अगर (r)
		वापस r;

	dsi_enable_scp_clk(dsi);

	/* A dummy पढ़ो using the SCP पूर्णांकerface to any DSIPHY रेजिस्टर is
	 * required after DSIPHY reset to complete the reset of the DSI complex
	 * I/O. */
	dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG5);

	अगर (!रुको_क्रम_bit_change(dsi, DSI_DSIPHY_CFG5, 30, 1)) अणु
		DSSERR("CIO SCP Clock domain not coming out of reset.\n");
		r = -EIO;
		जाओ err_scp_clk_करोm;
	पूर्ण

	r = dsi_set_lane_config(dsi);
	अगर (r)
		जाओ err_scp_clk_करोm;

	/* set TX STOP MODE समयr to maximum क्रम this operation */
	l = dsi_पढ़ो_reg(dsi, DSI_TIMING1);
	l = FLD_MOD(l, 1, 15, 15);	/* FORCE_TX_STOP_MODE_IO */
	l = FLD_MOD(l, 1, 14, 14);	/* STOP_STATE_X16_IO */
	l = FLD_MOD(l, 1, 13, 13);	/* STOP_STATE_X4_IO */
	l = FLD_MOD(l, 0x1fff, 12, 0);	/* STOP_STATE_COUNTER_IO */
	dsi_ग_लिखो_reg(dsi, DSI_TIMING1, l);

	r = dsi_cio_घातer(dsi, DSI_COMPLEXIO_POWER_ON);
	अगर (r)
		जाओ err_cio_pwr;

	अगर (!रुको_क्रम_bit_change(dsi, DSI_COMPLEXIO_CFG1, 29, 1)) अणु
		DSSERR("CIO PWR clock domain not coming out of reset.\n");
		r = -ENODEV;
		जाओ err_cio_pwr_करोm;
	पूर्ण

	dsi_अगर_enable(dsi, true);
	dsi_अगर_enable(dsi, false);
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, 1, 20, 20); /* LP_CLK_ENABLE */

	r = dsi_cio_रुको_tx_clk_esc_reset(dsi);
	अगर (r)
		जाओ err_tx_clk_esc_rst;

	/* FORCE_TX_STOP_MODE_IO */
	REG_FLD_MOD(dsi, DSI_TIMING1, 0, 15, 15);

	dsi_cio_timings(dsi);

	/* DDR_CLK_ALWAYS_ON */
	REG_FLD_MOD(dsi, DSI_CLK_CTRL,
		    !(dsi->dsidev->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS),
		    13, 13);

	DSSDBG("CIO init done\n");

	वापस 0;

err_tx_clk_esc_rst:
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, 0, 20, 20); /* LP_CLK_ENABLE */
err_cio_pwr_करोm:
	dsi_cio_घातer(dsi, DSI_COMPLEXIO_POWER_OFF);
err_cio_pwr:
err_scp_clk_करोm:
	dsi_disable_scp_clk(dsi);
	dsi_disable_pads(dsi);
	वापस r;
पूर्ण

अटल व्योम dsi_cio_uninit(काष्ठा dsi_data *dsi)
अणु
	/* DDR_CLK_ALWAYS_ON */
	REG_FLD_MOD(dsi, DSI_CLK_CTRL, 0, 13, 13);

	dsi_cio_घातer(dsi, DSI_COMPLEXIO_POWER_OFF);
	dsi_disable_scp_clk(dsi);
	dsi_disable_pads(dsi);
पूर्ण

अटल व्योम dsi_config_tx_fअगरo(काष्ठा dsi_data *dsi,
			       क्रमागत fअगरo_size size1, क्रमागत fअगरo_size size2,
			       क्रमागत fअगरo_size size3, क्रमागत fअगरo_size size4)
अणु
	u32 r = 0;
	पूर्णांक add = 0;
	पूर्णांक i;

	dsi->vc[0].tx_fअगरo_size = size1;
	dsi->vc[1].tx_fअगरo_size = size2;
	dsi->vc[2].tx_fअगरo_size = size3;
	dsi->vc[3].tx_fअगरo_size = size4;

	क्रम (i = 0; i < 4; i++) अणु
		u8 v;
		पूर्णांक size = dsi->vc[i].tx_fअगरo_size;

		अगर (add + size > 4) अणु
			DSSERR("Illegal FIFO configuration\n");
			BUG();
			वापस;
		पूर्ण

		v = FLD_VAL(add, 2, 0) | FLD_VAL(size, 7, 4);
		r |= v << (8 * i);
		/*DSSDBG("TX FIFO vc %d: size %d, add %d\n", i, size, add); */
		add += size;
	पूर्ण

	dsi_ग_लिखो_reg(dsi, DSI_TX_FIFO_VC_SIZE, r);
पूर्ण

अटल व्योम dsi_config_rx_fअगरo(काष्ठा dsi_data *dsi,
		क्रमागत fअगरo_size size1, क्रमागत fअगरo_size size2,
		क्रमागत fअगरo_size size3, क्रमागत fअगरo_size size4)
अणु
	u32 r = 0;
	पूर्णांक add = 0;
	पूर्णांक i;

	dsi->vc[0].rx_fअगरo_size = size1;
	dsi->vc[1].rx_fअगरo_size = size2;
	dsi->vc[2].rx_fअगरo_size = size3;
	dsi->vc[3].rx_fअगरo_size = size4;

	क्रम (i = 0; i < 4; i++) अणु
		u8 v;
		पूर्णांक size = dsi->vc[i].rx_fअगरo_size;

		अगर (add + size > 4) अणु
			DSSERR("Illegal FIFO configuration\n");
			BUG();
			वापस;
		पूर्ण

		v = FLD_VAL(add, 2, 0) | FLD_VAL(size, 7, 4);
		r |= v << (8 * i);
		/*DSSDBG("RX FIFO vc %d: size %d, add %d\n", i, size, add); */
		add += size;
	पूर्ण

	dsi_ग_लिखो_reg(dsi, DSI_RX_FIFO_VC_SIZE, r);
पूर्ण

अटल पूर्णांक dsi_क्रमce_tx_stop_mode_io(काष्ठा dsi_data *dsi)
अणु
	u32 r;

	r = dsi_पढ़ो_reg(dsi, DSI_TIMING1);
	r = FLD_MOD(r, 1, 15, 15);	/* FORCE_TX_STOP_MODE_IO */
	dsi_ग_लिखो_reg(dsi, DSI_TIMING1, r);

	अगर (!रुको_क्रम_bit_change(dsi, DSI_TIMING1, 15, 0)) अणु
		DSSERR("TX_STOP bit not going down\n");
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool dsi_vc_is_enabled(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	वापस REG_GET(dsi, DSI_VC_CTRL(vc), 0, 0);
पूर्ण

अटल व्योम dsi_packet_sent_handler_vp(व्योम *data, u32 mask)
अणु
	काष्ठा dsi_packet_sent_handler_data *vp_data =
		(काष्ठा dsi_packet_sent_handler_data *) data;
	काष्ठा dsi_data *dsi = vp_data->dsi;
	स्थिर पूर्णांक vc = dsi->update_vc;
	u8 bit = dsi->te_enabled ? 30 : 31;

	अगर (REG_GET(dsi, DSI_VC_TE(vc), bit, bit) == 0)
		complete(vp_data->completion);
पूर्ण

अटल पूर्णांक dsi_sync_vc_vp(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा dsi_packet_sent_handler_data vp_data = अणु
		.dsi = dsi,
		.completion = &completion
	पूर्ण;
	पूर्णांक r = 0;
	u8 bit;

	bit = dsi->te_enabled ? 30 : 31;

	r = dsi_रेजिस्टर_isr_vc(dsi, vc, dsi_packet_sent_handler_vp,
		&vp_data, DSI_VC_IRQ_PACKET_SENT);
	अगर (r)
		जाओ err0;

	/* Wait क्रम completion only अगर TE_EN/TE_START is still set */
	अगर (REG_GET(dsi, DSI_VC_TE(vc), bit, bit)) अणु
		अगर (रुको_क्रम_completion_समयout(&completion,
				msecs_to_jअगरfies(10)) == 0) अणु
			DSSERR("Failed to complete previous frame transfer\n");
			r = -EIO;
			जाओ err1;
		पूर्ण
	पूर्ण

	dsi_unरेजिस्टर_isr_vc(dsi, vc, dsi_packet_sent_handler_vp,
		&vp_data, DSI_VC_IRQ_PACKET_SENT);

	वापस 0;
err1:
	dsi_unरेजिस्टर_isr_vc(dsi, vc, dsi_packet_sent_handler_vp,
		&vp_data, DSI_VC_IRQ_PACKET_SENT);
err0:
	वापस r;
पूर्ण

अटल व्योम dsi_packet_sent_handler_l4(व्योम *data, u32 mask)
अणु
	काष्ठा dsi_packet_sent_handler_data *l4_data =
		(काष्ठा dsi_packet_sent_handler_data *) data;
	काष्ठा dsi_data *dsi = l4_data->dsi;
	स्थिर पूर्णांक vc = dsi->update_vc;

	अगर (REG_GET(dsi, DSI_VC_CTRL(vc), 5, 5) == 0)
		complete(l4_data->completion);
पूर्ण

अटल पूर्णांक dsi_sync_vc_l4(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	DECLARE_COMPLETION_ONSTACK(completion);
	काष्ठा dsi_packet_sent_handler_data l4_data = अणु
		.dsi = dsi,
		.completion = &completion
	पूर्ण;
	पूर्णांक r = 0;

	r = dsi_रेजिस्टर_isr_vc(dsi, vc, dsi_packet_sent_handler_l4,
		&l4_data, DSI_VC_IRQ_PACKET_SENT);
	अगर (r)
		जाओ err0;

	/* Wait क्रम completion only अगर TX_FIFO_NOT_EMPTY is still set */
	अगर (REG_GET(dsi, DSI_VC_CTRL(vc), 5, 5)) अणु
		अगर (रुको_क्रम_completion_समयout(&completion,
				msecs_to_jअगरfies(10)) == 0) अणु
			DSSERR("Failed to complete previous l4 transfer\n");
			r = -EIO;
			जाओ err1;
		पूर्ण
	पूर्ण

	dsi_unरेजिस्टर_isr_vc(dsi, vc, dsi_packet_sent_handler_l4,
		&l4_data, DSI_VC_IRQ_PACKET_SENT);

	वापस 0;
err1:
	dsi_unरेजिस्टर_isr_vc(dsi, vc, dsi_packet_sent_handler_l4,
		&l4_data, DSI_VC_IRQ_PACKET_SENT);
err0:
	वापस r;
पूर्ण

अटल पूर्णांक dsi_sync_vc(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	WARN_ON(!dsi_bus_is_locked(dsi));

	WARN_ON(in_पूर्णांकerrupt());

	अगर (!dsi_vc_is_enabled(dsi, vc))
		वापस 0;

	चयन (dsi->vc[vc].source) अणु
	हाल DSI_VC_SOURCE_VP:
		वापस dsi_sync_vc_vp(dsi, vc);
	हाल DSI_VC_SOURCE_L4:
		वापस dsi_sync_vc_l4(dsi, vc);
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक dsi_vc_enable(काष्ठा dsi_data *dsi, पूर्णांक vc, bool enable)
अणु
	DSSDBG("dsi_vc_enable vc %d, enable %d\n",
			vc, enable);

	enable = enable ? 1 : 0;

	REG_FLD_MOD(dsi, DSI_VC_CTRL(vc), enable, 0, 0);

	अगर (!रुको_क्रम_bit_change(dsi, DSI_VC_CTRL(vc), 0, enable)) अणु
		DSSERR("Failed to set dsi_vc_enable to %d\n", enable);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dsi_vc_initial_config(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	u32 r;

	DSSDBG("Initial config of VC %d", vc);

	r = dsi_पढ़ो_reg(dsi, DSI_VC_CTRL(vc));

	अगर (FLD_GET(r, 15, 15)) /* VC_BUSY */
		DSSERR("VC(%d) busy when trying to configure it!\n",
				vc);

	r = FLD_MOD(r, 0, 1, 1); /* SOURCE, 0 = L4 */
	r = FLD_MOD(r, 0, 2, 2); /* BTA_SHORT_EN  */
	r = FLD_MOD(r, 0, 3, 3); /* BTA_LONG_EN */
	r = FLD_MOD(r, 0, 4, 4); /* MODE, 0 = command */
	r = FLD_MOD(r, 1, 7, 7); /* CS_TX_EN */
	r = FLD_MOD(r, 1, 8, 8); /* ECC_TX_EN */
	r = FLD_MOD(r, 0, 9, 9); /* MODE_SPEED, high speed on/off */
	अगर (dsi->data->quirks & DSI_QUIRK_VC_OCP_WIDTH)
		r = FLD_MOD(r, 3, 11, 10);	/* OCP_WIDTH = 32 bit */

	r = FLD_MOD(r, 4, 29, 27); /* DMA_RX_REQ_NB = no dma */
	r = FLD_MOD(r, 4, 23, 21); /* DMA_TX_REQ_NB = no dma */

	dsi_ग_लिखो_reg(dsi, DSI_VC_CTRL(vc), r);

	dsi->vc[vc].source = DSI_VC_SOURCE_L4;
पूर्ण

अटल व्योम dsi_vc_enable_hs(काष्ठा omap_dss_device *dssdev, पूर्णांक vc,
		bool enable)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);

	DSSDBG("dsi_vc_enable_hs(%d, %d)\n", vc, enable);

	अगर (REG_GET(dsi, DSI_VC_CTRL(vc), 9, 9) == enable)
		वापस;

	WARN_ON(!dsi_bus_is_locked(dsi));

	dsi_vc_enable(dsi, vc, 0);
	dsi_अगर_enable(dsi, 0);

	REG_FLD_MOD(dsi, DSI_VC_CTRL(vc), enable, 9, 9);

	dsi_vc_enable(dsi, vc, 1);
	dsi_अगर_enable(dsi, 1);

	dsi_क्रमce_tx_stop_mode_io(dsi);
पूर्ण

अटल व्योम dsi_vc_flush_दीर्घ_data(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	जबतक (REG_GET(dsi, DSI_VC_CTRL(vc), 20, 20)) अणु
		u32 val;
		val = dsi_पढ़ो_reg(dsi, DSI_VC_SHORT_PACKET_HEADER(vc));
		DSSDBG("\t\tb1 %#02x b2 %#02x b3 %#02x b4 %#02x\n",
				(val >> 0) & 0xff,
				(val >> 8) & 0xff,
				(val >> 16) & 0xff,
				(val >> 24) & 0xff);
	पूर्ण
पूर्ण

अटल व्योम dsi_show_rx_ack_with_err(u16 err)
अणु
	DSSERR("\tACK with ERROR (%#x):\n", err);
	अगर (err & (1 << 0))
		DSSERR("\t\tSoT Error\n");
	अगर (err & (1 << 1))
		DSSERR("\t\tSoT Sync Error\n");
	अगर (err & (1 << 2))
		DSSERR("\t\tEoT Sync Error\n");
	अगर (err & (1 << 3))
		DSSERR("\t\tEscape Mode Entry Command Error\n");
	अगर (err & (1 << 4))
		DSSERR("\t\tLP Transmit Sync Error\n");
	अगर (err & (1 << 5))
		DSSERR("\t\tHS Receive Timeout Error\n");
	अगर (err & (1 << 6))
		DSSERR("\t\tFalse Control Error\n");
	अगर (err & (1 << 7))
		DSSERR("\t\t(reserved7)\n");
	अगर (err & (1 << 8))
		DSSERR("\t\tECC Error, single-bit (corrected)\n");
	अगर (err & (1 << 9))
		DSSERR("\t\tECC Error, multi-bit (not corrected)\n");
	अगर (err & (1 << 10))
		DSSERR("\t\tChecksum Error\n");
	अगर (err & (1 << 11))
		DSSERR("\t\tData type not recognized\n");
	अगर (err & (1 << 12))
		DSSERR("\t\tInvalid VC ID\n");
	अगर (err & (1 << 13))
		DSSERR("\t\tInvalid Transmission Length\n");
	अगर (err & (1 << 14))
		DSSERR("\t\t(reserved14)\n");
	अगर (err & (1 << 15))
		DSSERR("\t\tDSI Protocol Violation\n");
पूर्ण

अटल u16 dsi_vc_flush_receive_data(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	/* RX_FIFO_NOT_EMPTY */
	जबतक (REG_GET(dsi, DSI_VC_CTRL(vc), 20, 20)) अणु
		u32 val;
		u8 dt;
		val = dsi_पढ़ो_reg(dsi, DSI_VC_SHORT_PACKET_HEADER(vc));
		DSSERR("\trawval %#08x\n", val);
		dt = FLD_GET(val, 5, 0);
		अगर (dt == MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT) अणु
			u16 err = FLD_GET(val, 23, 8);
			dsi_show_rx_ack_with_err(err);
		पूर्ण अन्यथा अगर (dt == MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE) अणु
			DSSERR("\tDCS short response, 1 byte: %#x\n",
					FLD_GET(val, 23, 8));
		पूर्ण अन्यथा अगर (dt == MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE) अणु
			DSSERR("\tDCS short response, 2 byte: %#x\n",
					FLD_GET(val, 23, 8));
		पूर्ण अन्यथा अगर (dt == MIPI_DSI_RX_DCS_LONG_READ_RESPONSE) अणु
			DSSERR("\tDCS long response, len %d\n",
					FLD_GET(val, 23, 8));
			dsi_vc_flush_दीर्घ_data(dsi, vc);
		पूर्ण अन्यथा अणु
			DSSERR("\tunknown datatype 0x%02x\n", dt);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dsi_vc_send_bta(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	अगर (dsi->debug_ग_लिखो || dsi->debug_पढ़ो)
		DSSDBG("dsi_vc_send_bta %d\n", vc);

	WARN_ON(!dsi_bus_is_locked(dsi));

	/* RX_FIFO_NOT_EMPTY */
	अगर (REG_GET(dsi, DSI_VC_CTRL(vc), 20, 20)) अणु
		DSSERR("rx fifo not empty when sending BTA, dumping data:\n");
		dsi_vc_flush_receive_data(dsi, vc);
	पूर्ण

	REG_FLD_MOD(dsi, DSI_VC_CTRL(vc), 1, 6, 6); /* BTA_EN */

	/* flush posted ग_लिखो */
	dsi_पढ़ो_reg(dsi, DSI_VC_CTRL(vc));

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_vc_send_bta_sync(काष्ठा omap_dss_device *dssdev, पूर्णांक vc)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	DECLARE_COMPLETION_ONSTACK(completion);
	पूर्णांक r = 0;
	u32 err;

	r = dsi_रेजिस्टर_isr_vc(dsi, vc, dsi_completion_handler,
			&completion, DSI_VC_IRQ_BTA);
	अगर (r)
		जाओ err0;

	r = dsi_रेजिस्टर_isr(dsi, dsi_completion_handler, &completion,
			DSI_IRQ_ERROR_MASK);
	अगर (r)
		जाओ err1;

	r = dsi_vc_send_bta(dsi, vc);
	अगर (r)
		जाओ err2;

	अगर (रुको_क्रम_completion_समयout(&completion,
				msecs_to_jअगरfies(500)) == 0) अणु
		DSSERR("Failed to receive BTA\n");
		r = -EIO;
		जाओ err2;
	पूर्ण

	err = dsi_get_errors(dsi);
	अगर (err) अणु
		DSSERR("Error while sending BTA: %x\n", err);
		r = -EIO;
		जाओ err2;
	पूर्ण
err2:
	dsi_unरेजिस्टर_isr(dsi, dsi_completion_handler, &completion,
			DSI_IRQ_ERROR_MASK);
err1:
	dsi_unरेजिस्टर_isr_vc(dsi, vc, dsi_completion_handler,
			&completion, DSI_VC_IRQ_BTA);
err0:
	वापस r;
पूर्ण

अटल अंतरभूत व्योम dsi_vc_ग_लिखो_दीर्घ_header(काष्ठा dsi_data *dsi, पूर्णांक vc,
					    पूर्णांक channel, u8 data_type, u16 len,
					    u8 ecc)
अणु
	u32 val;
	u8 data_id;

	WARN_ON(!dsi_bus_is_locked(dsi));

	data_id = data_type | channel << 6;

	val = FLD_VAL(data_id, 7, 0) | FLD_VAL(len, 23, 8) |
		FLD_VAL(ecc, 31, 24);

	dsi_ग_लिखो_reg(dsi, DSI_VC_LONG_PACKET_HEADER(vc), val);
पूर्ण

अटल अंतरभूत व्योम dsi_vc_ग_लिखो_दीर्घ_payload(काष्ठा dsi_data *dsi, पूर्णांक vc,
					     u8 b1, u8 b2, u8 b3, u8 b4)
अणु
	u32 val;

	val = b4 << 24 | b3 << 16 | b2 << 8  | b1 << 0;

/*	DSSDBG("\twriting %02x, %02x, %02x, %02x (%#010x)\n",
			b1, b2, b3, b4, val); */

	dsi_ग_लिखो_reg(dsi, DSI_VC_LONG_PACKET_PAYLOAD(vc), val);
पूर्ण

अटल पूर्णांक dsi_vc_send_दीर्घ(काष्ठा dsi_data *dsi, पूर्णांक vc,
			    स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	/*u32 val; */
	पूर्णांक i;
	स्थिर u8 *p;
	पूर्णांक r = 0;
	u8 b1, b2, b3, b4;

	अगर (dsi->debug_ग_लिखो)
		DSSDBG("dsi_vc_send_long, %d bytes\n", msg->tx_len);

	/* len + header */
	अगर (dsi->vc[vc].tx_fअगरo_size * 32 * 4 < msg->tx_len + 4) अणु
		DSSERR("unable to send long packet: packet too long.\n");
		वापस -EINVAL;
	पूर्ण

	dsi_vc_ग_लिखो_दीर्घ_header(dsi, vc, msg->channel, msg->type, msg->tx_len, 0);

	p = msg->tx_buf;
	क्रम (i = 0; i < msg->tx_len >> 2; i++) अणु
		अगर (dsi->debug_ग_लिखो)
			DSSDBG("\tsending full packet %d\n", i);

		b1 = *p++;
		b2 = *p++;
		b3 = *p++;
		b4 = *p++;

		dsi_vc_ग_लिखो_दीर्घ_payload(dsi, vc, b1, b2, b3, b4);
	पूर्ण

	i = msg->tx_len % 4;
	अगर (i) अणु
		b1 = 0; b2 = 0; b3 = 0;

		अगर (dsi->debug_ग_लिखो)
			DSSDBG("\tsending remainder bytes %d\n", i);

		चयन (i) अणु
		हाल 3:
			b1 = *p++;
			b2 = *p++;
			b3 = *p++;
			अवरोध;
		हाल 2:
			b1 = *p++;
			b2 = *p++;
			अवरोध;
		हाल 1:
			b1 = *p++;
			अवरोध;
		पूर्ण

		dsi_vc_ग_लिखो_दीर्घ_payload(dsi, vc, b1, b2, b3, 0);
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक dsi_vc_send_लघु(काष्ठा dsi_data *dsi, पूर्णांक vc,
			     स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा mipi_dsi_packet pkt;
	पूर्णांक ret;
	u32 r;

	ret = mipi_dsi_create_packet(&pkt, msg);
	अगर (ret < 0)
		वापस ret;

	WARN_ON(!dsi_bus_is_locked(dsi));

	अगर (dsi->debug_ग_लिखो)
		DSSDBG("dsi_vc_send_short(vc%d, dt %#x, b1 %#x, b2 %#x)\n",
		       vc, msg->type, pkt.header[1], pkt.header[2]);

	अगर (FLD_GET(dsi_पढ़ो_reg(dsi, DSI_VC_CTRL(vc)), 16, 16)) अणु
		DSSERR("ERROR FIFO FULL, aborting transfer\n");
		वापस -EINVAL;
	पूर्ण

	r = pkt.header[3] << 24 | pkt.header[2] << 16 | pkt.header[1] << 8 |
	    pkt.header[0];

	dsi_ग_लिखो_reg(dsi, DSI_VC_SHORT_PACKET_HEADER(vc), r);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_vc_send_null(काष्ठा dsi_data *dsi, पूर्णांक vc, पूर्णांक channel)
अणु
	स्थिर काष्ठा mipi_dsi_msg msg = अणु
		.channel = channel,
		.type = MIPI_DSI_शून्य_PACKET,
	पूर्ण;

	वापस dsi_vc_send_दीर्घ(dsi, vc, &msg);
पूर्ण

अटल पूर्णांक dsi_vc_ग_लिखो_common(काष्ठा omap_dss_device *dssdev, पूर्णांक vc,
			       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	पूर्णांक r;

	अगर (mipi_dsi_packet_क्रमmat_is_लघु(msg->type))
		r = dsi_vc_send_लघु(dsi, vc, msg);
	अन्यथा
		r = dsi_vc_send_दीर्घ(dsi, vc, msg);

	अगर (r < 0)
		वापस r;

	/*
	 * TODO: we करो not always have to करो the BTA sync, क्रम example
	 * we can improve perक्रमmance by setting the update winकरोw
	 * inक्रमmation without sending BTA sync between the commands.
	 * In that हाल we can वापस early.
	 */

	r = dsi_vc_send_bta_sync(dssdev, vc);
	अगर (r) अणु
		DSSERR("bta sync failed\n");
		वापस r;
	पूर्ण

	/* RX_FIFO_NOT_EMPTY */
	अगर (REG_GET(dsi, DSI_VC_CTRL(vc), 20, 20)) अणु
		DSSERR("rx fifo not empty after write, dumping data:\n");
		dsi_vc_flush_receive_data(dsi, vc);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_vc_पढ़ो_rx_fअगरo(काष्ठा dsi_data *dsi, पूर्णांक vc, u8 *buf,
			       पूर्णांक buflen, क्रमागत dss_dsi_content_type type)
अणु
	u32 val;
	u8 dt;
	पूर्णांक r;

	/* RX_FIFO_NOT_EMPTY */
	अगर (REG_GET(dsi, DSI_VC_CTRL(vc), 20, 20) == 0) अणु
		DSSERR("RX fifo empty when trying to read.\n");
		r = -EIO;
		जाओ err;
	पूर्ण

	val = dsi_पढ़ो_reg(dsi, DSI_VC_SHORT_PACKET_HEADER(vc));
	अगर (dsi->debug_पढ़ो)
		DSSDBG("\theader: %08x\n", val);
	dt = FLD_GET(val, 5, 0);
	अगर (dt == MIPI_DSI_RX_ACKNOWLEDGE_AND_ERROR_REPORT) अणु
		u16 err = FLD_GET(val, 23, 8);
		dsi_show_rx_ack_with_err(err);
		r = -EIO;
		जाओ err;

	पूर्ण अन्यथा अगर (dt == (type == DSS_DSI_CONTENT_GENERIC ?
			MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_1BYTE :
			MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_1BYTE)) अणु
		u8 data = FLD_GET(val, 15, 8);
		अगर (dsi->debug_पढ़ो)
			DSSDBG("\t%s short response, 1 byte: %02x\n",
				type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" :
				"DCS", data);

		अगर (buflen < 1) अणु
			r = -EIO;
			जाओ err;
		पूर्ण

		buf[0] = data;

		वापस 1;
	पूर्ण अन्यथा अगर (dt == (type == DSS_DSI_CONTENT_GENERIC ?
			MIPI_DSI_RX_GENERIC_SHORT_READ_RESPONSE_2BYTE :
			MIPI_DSI_RX_DCS_SHORT_READ_RESPONSE_2BYTE)) अणु
		u16 data = FLD_GET(val, 23, 8);
		अगर (dsi->debug_पढ़ो)
			DSSDBG("\t%s short response, 2 byte: %04x\n",
				type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" :
				"DCS", data);

		अगर (buflen < 2) अणु
			r = -EIO;
			जाओ err;
		पूर्ण

		buf[0] = data & 0xff;
		buf[1] = (data >> 8) & 0xff;

		वापस 2;
	पूर्ण अन्यथा अगर (dt == (type == DSS_DSI_CONTENT_GENERIC ?
			MIPI_DSI_RX_GENERIC_LONG_READ_RESPONSE :
			MIPI_DSI_RX_DCS_LONG_READ_RESPONSE)) अणु
		पूर्णांक w;
		पूर्णांक len = FLD_GET(val, 23, 8);
		अगर (dsi->debug_पढ़ो)
			DSSDBG("\t%s long response, len %d\n",
				type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" :
				"DCS", len);

		अगर (len > buflen) अणु
			r = -EIO;
			जाओ err;
		पूर्ण

		/* two byte checksum ends the packet, not included in len */
		क्रम (w = 0; w < len + 2;) अणु
			पूर्णांक b;
			val = dsi_पढ़ो_reg(dsi,
				DSI_VC_SHORT_PACKET_HEADER(vc));
			अगर (dsi->debug_पढ़ो)
				DSSDBG("\t\t%02x %02x %02x %02x\n",
						(val >> 0) & 0xff,
						(val >> 8) & 0xff,
						(val >> 16) & 0xff,
						(val >> 24) & 0xff);

			क्रम (b = 0; b < 4; ++b) अणु
				अगर (w < len)
					buf[w] = (val >> (b * 8)) & 0xff;
				/* we discard the 2 byte checksum */
				++w;
			पूर्ण
		पूर्ण

		वापस len;
	पूर्ण अन्यथा अणु
		DSSERR("\tunknown datatype 0x%02x\n", dt);
		r = -EIO;
		जाओ err;
	पूर्ण

err:
	DSSERR("dsi_vc_read_rx_fifo(vc %d type %s) failed\n", vc,
		type == DSS_DSI_CONTENT_GENERIC ? "GENERIC" : "DCS");

	वापस r;
पूर्ण

अटल पूर्णांक dsi_vc_dcs_पढ़ो(काष्ठा omap_dss_device *dssdev, पूर्णांक vc,
			   स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	u8 cmd = ((u8 *)msg->tx_buf)[0];
	पूर्णांक r;

	अगर (dsi->debug_पढ़ो)
		DSSDBG("%s(vc %d, cmd %x)\n", __func__, vc, cmd);

	r = dsi_vc_send_लघु(dsi, vc, msg);
	अगर (r)
		जाओ err;

	r = dsi_vc_send_bta_sync(dssdev, vc);
	अगर (r)
		जाओ err;

	r = dsi_vc_पढ़ो_rx_fअगरo(dsi, vc, msg->rx_buf, msg->rx_len,
		DSS_DSI_CONTENT_DCS);
	अगर (r < 0)
		जाओ err;

	अगर (r != msg->rx_len) अणु
		r = -EIO;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	DSSERR("%s(vc %d, cmd 0x%02x) failed\n", __func__,  vc, cmd);
	वापस r;
पूर्ण

अटल पूर्णांक dsi_vc_generic_पढ़ो(काष्ठा omap_dss_device *dssdev, पूर्णांक vc,
			       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	पूर्णांक r;

	r = dsi_vc_send_लघु(dsi, vc, msg);
	अगर (r)
		जाओ err;

	r = dsi_vc_send_bta_sync(dssdev, vc);
	अगर (r)
		जाओ err;

	r = dsi_vc_पढ़ो_rx_fअगरo(dsi, vc, msg->rx_buf, msg->rx_len,
		DSS_DSI_CONTENT_GENERIC);
	अगर (r < 0)
		जाओ err;

	अगर (r != msg->rx_len) अणु
		r = -EIO;
		जाओ err;
	पूर्ण

	वापस 0;
err:
	DSSERR("%s(vc %d, reqlen %d) failed\n", __func__,  vc, msg->tx_len);
	वापस r;
पूर्ण

अटल व्योम dsi_set_lp_rx_समयout(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक ticks,
				  bool x4, bool x16)
अणु
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ total_ticks;
	u32 r;

	BUG_ON(ticks > 0x1fff);

	/* ticks in DSI_FCK */
	fck = dsi_fclk_rate(dsi);

	r = dsi_पढ़ो_reg(dsi, DSI_TIMING2);
	r = FLD_MOD(r, 1, 15, 15);	/* LP_RX_TO */
	r = FLD_MOD(r, x16 ? 1 : 0, 14, 14);	/* LP_RX_TO_X16 */
	r = FLD_MOD(r, x4 ? 1 : 0, 13, 13);	/* LP_RX_TO_X4 */
	r = FLD_MOD(r, ticks, 12, 0);	/* LP_RX_COUNTER */
	dsi_ग_लिखो_reg(dsi, DSI_TIMING2, r);

	total_ticks = ticks * (x16 ? 16 : 1) * (x4 ? 4 : 1);

	DSSDBG("LP_RX_TO %lu ticks (%#x%s%s) = %lu ns\n",
			total_ticks,
			ticks, x4 ? " x4" : "", x16 ? " x16" : "",
			(total_ticks * 1000) / (fck / 1000 / 1000));
पूर्ण

अटल व्योम dsi_set_ta_समयout(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक ticks,
			       bool x8, bool x16)
अणु
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ total_ticks;
	u32 r;

	BUG_ON(ticks > 0x1fff);

	/* ticks in DSI_FCK */
	fck = dsi_fclk_rate(dsi);

	r = dsi_पढ़ो_reg(dsi, DSI_TIMING1);
	r = FLD_MOD(r, 1, 31, 31);	/* TA_TO */
	r = FLD_MOD(r, x16 ? 1 : 0, 30, 30);	/* TA_TO_X16 */
	r = FLD_MOD(r, x8 ? 1 : 0, 29, 29);	/* TA_TO_X8 */
	r = FLD_MOD(r, ticks, 28, 16);	/* TA_TO_COUNTER */
	dsi_ग_लिखो_reg(dsi, DSI_TIMING1, r);

	total_ticks = ticks * (x16 ? 16 : 1) * (x8 ? 8 : 1);

	DSSDBG("TA_TO %lu ticks (%#x%s%s) = %lu ns\n",
			total_ticks,
			ticks, x8 ? " x8" : "", x16 ? " x16" : "",
			(total_ticks * 1000) / (fck / 1000 / 1000));
पूर्ण

अटल व्योम dsi_set_stop_state_counter(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक ticks,
				       bool x4, bool x16)
अणु
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ total_ticks;
	u32 r;

	BUG_ON(ticks > 0x1fff);

	/* ticks in DSI_FCK */
	fck = dsi_fclk_rate(dsi);

	r = dsi_पढ़ो_reg(dsi, DSI_TIMING1);
	r = FLD_MOD(r, 1, 15, 15);	/* FORCE_TX_STOP_MODE_IO */
	r = FLD_MOD(r, x16 ? 1 : 0, 14, 14);	/* STOP_STATE_X16_IO */
	r = FLD_MOD(r, x4 ? 1 : 0, 13, 13);	/* STOP_STATE_X4_IO */
	r = FLD_MOD(r, ticks, 12, 0);	/* STOP_STATE_COUNTER_IO */
	dsi_ग_लिखो_reg(dsi, DSI_TIMING1, r);

	total_ticks = ticks * (x16 ? 16 : 1) * (x4 ? 4 : 1);

	DSSDBG("STOP_STATE_COUNTER %lu ticks (%#x%s%s) = %lu ns\n",
			total_ticks,
			ticks, x4 ? " x4" : "", x16 ? " x16" : "",
			(total_ticks * 1000) / (fck / 1000 / 1000));
पूर्ण

अटल व्योम dsi_set_hs_tx_समयout(काष्ठा dsi_data *dsi, अचिन्हित पूर्णांक ticks,
				  bool x4, bool x16)
अणु
	अचिन्हित दीर्घ fck;
	अचिन्हित दीर्घ total_ticks;
	u32 r;

	BUG_ON(ticks > 0x1fff);

	/* ticks in TxByteClkHS */
	fck = dsi_get_txbyteclkhs(dsi);

	r = dsi_पढ़ो_reg(dsi, DSI_TIMING2);
	r = FLD_MOD(r, 1, 31, 31);	/* HS_TX_TO */
	r = FLD_MOD(r, x16 ? 1 : 0, 30, 30);	/* HS_TX_TO_X16 */
	r = FLD_MOD(r, x4 ? 1 : 0, 29, 29);	/* HS_TX_TO_X8 (4 really) */
	r = FLD_MOD(r, ticks, 28, 16);	/* HS_TX_TO_COUNTER */
	dsi_ग_लिखो_reg(dsi, DSI_TIMING2, r);

	total_ticks = ticks * (x16 ? 16 : 1) * (x4 ? 4 : 1);

	DSSDBG("HS_TX_TO %lu ticks (%#x%s%s) = %lu ns\n",
			total_ticks,
			ticks, x4 ? " x4" : "", x16 ? " x16" : "",
			(total_ticks * 1000) / (fck / 1000 / 1000));
पूर्ण

अटल व्योम dsi_config_vp_num_line_buffers(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक num_line_buffers;

	अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) अणु
		पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt);
		स्थिर काष्ठा videomode *vm = &dsi->vm;
		/*
		 * Don't use line buffers अगर width is greater than the video
		 * port's line buffer size
		 */
		अगर (dsi->line_buffer_size <= vm->hactive * bpp / 8)
			num_line_buffers = 0;
		अन्यथा
			num_line_buffers = 2;
	पूर्ण अन्यथा अणु
		/* Use maximum number of line buffers in command mode */
		num_line_buffers = 2;
	पूर्ण

	/* LINE_BUFFER */
	REG_FLD_MOD(dsi, DSI_CTRL, num_line_buffers, 13, 12);
पूर्ण

अटल व्योम dsi_config_vp_sync_events(काष्ठा dsi_data *dsi)
अणु
	bool sync_end;
	u32 r;

	अगर (dsi->vm_timings.trans_mode == OMAP_DSS_DSI_PULSE_MODE)
		sync_end = true;
	अन्यथा
		sync_end = false;

	r = dsi_पढ़ो_reg(dsi, DSI_CTRL);
	r = FLD_MOD(r, 1, 9, 9);		/* VP_DE_POL */
	r = FLD_MOD(r, 1, 10, 10);		/* VP_HSYNC_POL */
	r = FLD_MOD(r, 1, 11, 11);		/* VP_VSYNC_POL */
	r = FLD_MOD(r, 1, 15, 15);		/* VP_VSYNC_START */
	r = FLD_MOD(r, sync_end, 16, 16);	/* VP_VSYNC_END */
	r = FLD_MOD(r, 1, 17, 17);		/* VP_HSYNC_START */
	r = FLD_MOD(r, sync_end, 18, 18);	/* VP_HSYNC_END */
	dsi_ग_लिखो_reg(dsi, DSI_CTRL, r);
पूर्ण

अटल व्योम dsi_config_blanking_modes(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक blanking_mode = dsi->vm_timings.blanking_mode;
	पूर्णांक hfp_blanking_mode = dsi->vm_timings.hfp_blanking_mode;
	पूर्णांक hbp_blanking_mode = dsi->vm_timings.hbp_blanking_mode;
	पूर्णांक hsa_blanking_mode = dsi->vm_timings.hsa_blanking_mode;
	u32 r;

	/*
	 * 0 = TX FIFO packets sent or LPS in corresponding blanking periods
	 * 1 = Long blanking packets are sent in corresponding blanking periods
	 */
	r = dsi_पढ़ो_reg(dsi, DSI_CTRL);
	r = FLD_MOD(r, blanking_mode, 20, 20);		/* BLANKING_MODE */
	r = FLD_MOD(r, hfp_blanking_mode, 21, 21);	/* HFP_BLANKING */
	r = FLD_MOD(r, hbp_blanking_mode, 22, 22);	/* HBP_BLANKING */
	r = FLD_MOD(r, hsa_blanking_mode, 23, 23);	/* HSA_BLANKING */
	dsi_ग_लिखो_reg(dsi, DSI_CTRL, r);
पूर्ण

/*
 * According to section 'HS Command Mode Interleaving' in OMAP TRM, Scenario 3
 * results in maximum transition समय क्रम data and घड़ी lanes to enter and
 * निकास HS mode. Hence, this is the scenario where the least amount of command
 * mode data can be पूर्णांकerleaved. We program the minimum amount of TXBYTECLKHS
 * घड़ी cycles that can be used to पूर्णांकerleave command mode data in HS so that
 * all scenarios are satisfied.
 */
अटल पूर्णांक dsi_compute_पूर्णांकerleave_hs(पूर्णांक blank, bool ddr_alwon, पूर्णांक enter_hs,
		पूर्णांक निकास_hs, पूर्णांक निकासhs_clk, पूर्णांक ddr_pre, पूर्णांक ddr_post)
अणु
	पूर्णांक transition;

	/*
	 * If DDR_CLK_ALWAYS_ON is set, we need to consider HS mode transition
	 * समय of data lanes only, अगर it isn't set, we need to consider HS
	 * transition समय of both data and घड़ी lanes. HS transition समय
	 * of Scenario 3 is considered.
	 */
	अगर (ddr_alwon) अणु
		transition = enter_hs + निकास_hs + max(enter_hs, 2) + 1;
	पूर्ण अन्यथा अणु
		पूर्णांक trans1, trans2;
		trans1 = ddr_pre + enter_hs + निकास_hs + max(enter_hs, 2) + 1;
		trans2 = ddr_pre + enter_hs + निकासhs_clk + ddr_post + ddr_pre +
				enter_hs + 1;
		transition = max(trans1, trans2);
	पूर्ण

	वापस blank > transition ? blank - transition : 0;
पूर्ण

/*
 * According to section 'LP Command Mode Interleaving' in OMAP TRM, Scenario 1
 * results in maximum transition समय क्रम data lanes to enter and निकास LP mode.
 * Hence, this is the scenario where the least amount of command mode data can
 * be पूर्णांकerleaved. We program the minimum amount of bytes that can be
 * पूर्णांकerleaved in LP so that all scenarios are satisfied.
 */
अटल पूर्णांक dsi_compute_पूर्णांकerleave_lp(पूर्णांक blank, पूर्णांक enter_hs, पूर्णांक निकास_hs,
		पूर्णांक lp_clk_भाग, पूर्णांक tdsi_fclk)
अणु
	पूर्णांक trans_lp;	/* समय required क्रम a LP transition, in TXBYTECLKHS */
	पूर्णांक tlp_avail;	/* समय left क्रम पूर्णांकerleaving commands, in CLKIN4DDR */
	पूर्णांक ttxclkesc;	/* period of LP transmit escape घड़ी, in CLKIN4DDR */
	पूर्णांक thsbyte_clk = 16;	/* Period of TXBYTECLKHS घड़ी, in CLKIN4DDR */
	पूर्णांक lp_पूर्णांकer;	/* cmd mode data that can be पूर्णांकerleaved, in bytes */

	/* maximum LP transition समय according to Scenario 1 */
	trans_lp = निकास_hs + max(enter_hs, 2) + 1;

	/* CLKIN4DDR = 16 * TXBYTECLKHS */
	tlp_avail = thsbyte_clk * (blank - trans_lp);

	ttxclkesc = tdsi_fclk * lp_clk_भाग;

	lp_पूर्णांकer = ((tlp_avail - 8 * thsbyte_clk - 5 * tdsi_fclk) / ttxclkesc -
			26) / 16;

	वापस max(lp_पूर्णांकer, 0);
पूर्ण

अटल व्योम dsi_config_cmd_mode_पूर्णांकerleaving(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक blanking_mode;
	पूर्णांक hfp_blanking_mode, hbp_blanking_mode, hsa_blanking_mode;
	पूर्णांक hsa, hfp, hbp, width_bytes, bllp, lp_clk_भाग;
	पूर्णांक ddr_clk_pre, ddr_clk_post, enter_hs_mode_lat, निकास_hs_mode_lat;
	पूर्णांक tclk_trail, ths_निकास, निकासhs_clk;
	bool ddr_alwon;
	स्थिर काष्ठा videomode *vm = &dsi->vm;
	पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt);
	पूर्णांक ndl = dsi->num_lanes_used - 1;
	पूर्णांक dsi_fclk_hsभाग = dsi->user_dsi_cinfo.mX[HSDIV_DSI] + 1;
	पूर्णांक hsa_पूर्णांकerleave_hs = 0, hsa_पूर्णांकerleave_lp = 0;
	पूर्णांक hfp_पूर्णांकerleave_hs = 0, hfp_पूर्णांकerleave_lp = 0;
	पूर्णांक hbp_पूर्णांकerleave_hs = 0, hbp_पूर्णांकerleave_lp = 0;
	पूर्णांक bl_पूर्णांकerleave_hs = 0, bl_पूर्णांकerleave_lp = 0;
	u32 r;

	r = dsi_पढ़ो_reg(dsi, DSI_CTRL);
	blanking_mode = FLD_GET(r, 20, 20);
	hfp_blanking_mode = FLD_GET(r, 21, 21);
	hbp_blanking_mode = FLD_GET(r, 22, 22);
	hsa_blanking_mode = FLD_GET(r, 23, 23);

	r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING1);
	hbp = FLD_GET(r, 11, 0);
	hfp = FLD_GET(r, 23, 12);
	hsa = FLD_GET(r, 31, 24);

	r = dsi_पढ़ो_reg(dsi, DSI_CLK_TIMING);
	ddr_clk_post = FLD_GET(r, 7, 0);
	ddr_clk_pre = FLD_GET(r, 15, 8);

	r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING7);
	निकास_hs_mode_lat = FLD_GET(r, 15, 0);
	enter_hs_mode_lat = FLD_GET(r, 31, 16);

	r = dsi_पढ़ो_reg(dsi, DSI_CLK_CTRL);
	lp_clk_भाग = FLD_GET(r, 12, 0);
	ddr_alwon = FLD_GET(r, 13, 13);

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG0);
	ths_निकास = FLD_GET(r, 7, 0);

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG1);
	tclk_trail = FLD_GET(r, 15, 8);

	निकासhs_clk = ths_निकास + tclk_trail;

	width_bytes = DIV_ROUND_UP(vm->hactive * bpp, 8);
	bllp = hbp + hfp + hsa + DIV_ROUND_UP(width_bytes + 6, ndl);

	अगर (!hsa_blanking_mode) अणु
		hsa_पूर्णांकerleave_hs = dsi_compute_पूर्णांकerleave_hs(hsa, ddr_alwon,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					निकासhs_clk, ddr_clk_pre, ddr_clk_post);
		hsa_पूर्णांकerleave_lp = dsi_compute_पूर्णांकerleave_lp(hsa,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					lp_clk_भाग, dsi_fclk_hsभाग);
	पूर्ण

	अगर (!hfp_blanking_mode) अणु
		hfp_पूर्णांकerleave_hs = dsi_compute_पूर्णांकerleave_hs(hfp, ddr_alwon,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					निकासhs_clk, ddr_clk_pre, ddr_clk_post);
		hfp_पूर्णांकerleave_lp = dsi_compute_पूर्णांकerleave_lp(hfp,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					lp_clk_भाग, dsi_fclk_hsभाग);
	पूर्ण

	अगर (!hbp_blanking_mode) अणु
		hbp_पूर्णांकerleave_hs = dsi_compute_पूर्णांकerleave_hs(hbp, ddr_alwon,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					निकासhs_clk, ddr_clk_pre, ddr_clk_post);

		hbp_पूर्णांकerleave_lp = dsi_compute_पूर्णांकerleave_lp(hbp,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					lp_clk_भाग, dsi_fclk_hsभाग);
	पूर्ण

	अगर (!blanking_mode) अणु
		bl_पूर्णांकerleave_hs = dsi_compute_पूर्णांकerleave_hs(bllp, ddr_alwon,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					निकासhs_clk, ddr_clk_pre, ddr_clk_post);

		bl_पूर्णांकerleave_lp = dsi_compute_पूर्णांकerleave_lp(bllp,
					enter_hs_mode_lat, निकास_hs_mode_lat,
					lp_clk_भाग, dsi_fclk_hsभाग);
	पूर्ण

	DSSDBG("DSI HS interleaving(TXBYTECLKHS) HSA %d, HFP %d, HBP %d, BLLP %d\n",
		hsa_पूर्णांकerleave_hs, hfp_पूर्णांकerleave_hs, hbp_पूर्णांकerleave_hs,
		bl_पूर्णांकerleave_hs);

	DSSDBG("DSI LP interleaving(bytes) HSA %d, HFP %d, HBP %d, BLLP %d\n",
		hsa_पूर्णांकerleave_lp, hfp_पूर्णांकerleave_lp, hbp_पूर्णांकerleave_lp,
		bl_पूर्णांकerleave_lp);

	r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING4);
	r = FLD_MOD(r, hsa_पूर्णांकerleave_hs, 23, 16);
	r = FLD_MOD(r, hfp_पूर्णांकerleave_hs, 15, 8);
	r = FLD_MOD(r, hbp_पूर्णांकerleave_hs, 7, 0);
	dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING4, r);

	r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING5);
	r = FLD_MOD(r, hsa_पूर्णांकerleave_lp, 23, 16);
	r = FLD_MOD(r, hfp_पूर्णांकerleave_lp, 15, 8);
	r = FLD_MOD(r, hbp_पूर्णांकerleave_lp, 7, 0);
	dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING5, r);

	r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING6);
	r = FLD_MOD(r, bl_पूर्णांकerleave_hs, 31, 15);
	r = FLD_MOD(r, bl_पूर्णांकerleave_lp, 16, 0);
	dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING6, r);
पूर्ण

अटल पूर्णांक dsi_proto_config(काष्ठा dsi_data *dsi)
अणु
	u32 r;
	पूर्णांक buswidth = 0;

	dsi_config_tx_fअगरo(dsi, DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32);

	dsi_config_rx_fअगरo(dsi, DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32,
			DSI_FIFO_SIZE_32);

	/* XXX what values क्रम the समयouts? */
	dsi_set_stop_state_counter(dsi, 0x1000, false, false);
	dsi_set_ta_समयout(dsi, 0x1fff, true, true);
	dsi_set_lp_rx_समयout(dsi, 0x1fff, true, true);
	dsi_set_hs_tx_समयout(dsi, 0x1fff, true, true);

	चयन (mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt)) अणु
	हाल 16:
		buswidth = 0;
		अवरोध;
	हाल 18:
		buswidth = 1;
		अवरोध;
	हाल 24:
		buswidth = 2;
		अवरोध;
	शेष:
		BUG();
		वापस -EINVAL;
	पूर्ण

	r = dsi_पढ़ो_reg(dsi, DSI_CTRL);
	r = FLD_MOD(r, 1, 1, 1);	/* CS_RX_EN */
	r = FLD_MOD(r, 1, 2, 2);	/* ECC_RX_EN */
	r = FLD_MOD(r, 1, 3, 3);	/* TX_FIFO_ARBITRATION */
	r = FLD_MOD(r, 1, 4, 4);	/* VP_CLK_RATIO, always 1, see errata*/
	r = FLD_MOD(r, buswidth, 7, 6); /* VP_DATA_BUS_WIDTH */
	r = FLD_MOD(r, 0, 8, 8);	/* VP_CLK_POL */
	r = FLD_MOD(r, 1, 14, 14);	/* TRIGGER_RESET_MODE */
	r = FLD_MOD(r, 1, 19, 19);	/* EOT_ENABLE */
	अगर (!(dsi->data->quirks & DSI_QUIRK_DCS_CMD_CONFIG_VC)) अणु
		r = FLD_MOD(r, 1, 24, 24);	/* DCS_CMD_ENABLE */
		/* DCS_CMD_CODE, 1=start, 0=जारी */
		r = FLD_MOD(r, 0, 25, 25);
	पूर्ण

	dsi_ग_लिखो_reg(dsi, DSI_CTRL, r);

	dsi_config_vp_num_line_buffers(dsi);

	अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) अणु
		dsi_config_vp_sync_events(dsi);
		dsi_config_blanking_modes(dsi);
		dsi_config_cmd_mode_पूर्णांकerleaving(dsi);
	पूर्ण

	dsi_vc_initial_config(dsi, 0);
	dsi_vc_initial_config(dsi, 1);
	dsi_vc_initial_config(dsi, 2);
	dsi_vc_initial_config(dsi, 3);

	वापस 0;
पूर्ण

अटल व्योम dsi_proto_timings(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित पूर्णांक tlpx, tclk_zero, tclk_prepare;
	अचिन्हित पूर्णांक tclk_pre, tclk_post;
	अचिन्हित पूर्णांक ths_prepare, ths_prepare_ths_zero, ths_zero;
	अचिन्हित पूर्णांक ths_trail, ths_निकास;
	अचिन्हित पूर्णांक ddr_clk_pre, ddr_clk_post;
	अचिन्हित पूर्णांक enter_hs_mode_lat, निकास_hs_mode_lat;
	अचिन्हित पूर्णांक ths_eot;
	पूर्णांक ndl = dsi->num_lanes_used - 1;
	u32 r;

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG0);
	ths_prepare = FLD_GET(r, 31, 24);
	ths_prepare_ths_zero = FLD_GET(r, 23, 16);
	ths_zero = ths_prepare_ths_zero - ths_prepare;
	ths_trail = FLD_GET(r, 15, 8);
	ths_निकास = FLD_GET(r, 7, 0);

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG1);
	tlpx = FLD_GET(r, 20, 16) * 2;
	tclk_zero = FLD_GET(r, 7, 0);

	r = dsi_पढ़ो_reg(dsi, DSI_DSIPHY_CFG2);
	tclk_prepare = FLD_GET(r, 7, 0);

	/* min 8*UI */
	tclk_pre = 20;
	/* min 60ns + 52*UI */
	tclk_post = ns2ddr(dsi, 60) + 26;

	ths_eot = DIV_ROUND_UP(4, ndl);

	ddr_clk_pre = DIV_ROUND_UP(tclk_pre + tlpx + tclk_zero + tclk_prepare,
			4);
	ddr_clk_post = DIV_ROUND_UP(tclk_post + ths_trail, 4) + ths_eot;

	BUG_ON(ddr_clk_pre == 0 || ddr_clk_pre > 255);
	BUG_ON(ddr_clk_post == 0 || ddr_clk_post > 255);

	r = dsi_पढ़ो_reg(dsi, DSI_CLK_TIMING);
	r = FLD_MOD(r, ddr_clk_pre, 15, 8);
	r = FLD_MOD(r, ddr_clk_post, 7, 0);
	dsi_ग_लिखो_reg(dsi, DSI_CLK_TIMING, r);

	DSSDBG("ddr_clk_pre %u, ddr_clk_post %u\n",
			ddr_clk_pre,
			ddr_clk_post);

	enter_hs_mode_lat = 1 + DIV_ROUND_UP(tlpx, 4) +
		DIV_ROUND_UP(ths_prepare, 4) +
		DIV_ROUND_UP(ths_zero + 3, 4);

	निकास_hs_mode_lat = DIV_ROUND_UP(ths_trail + ths_निकास, 4) + 1 + ths_eot;

	r = FLD_VAL(enter_hs_mode_lat, 31, 16) |
		FLD_VAL(निकास_hs_mode_lat, 15, 0);
	dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING7, r);

	DSSDBG("enter_hs_mode_lat %u, exit_hs_mode_lat %u\n",
			enter_hs_mode_lat, निकास_hs_mode_lat);

	 अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) अणु
		/* TODO: Implement a video mode check_timings function */
		पूर्णांक hsa = dsi->vm_timings.hsa;
		पूर्णांक hfp = dsi->vm_timings.hfp;
		पूर्णांक hbp = dsi->vm_timings.hbp;
		पूर्णांक vsa = dsi->vm_timings.vsa;
		पूर्णांक vfp = dsi->vm_timings.vfp;
		पूर्णांक vbp = dsi->vm_timings.vbp;
		पूर्णांक winकरोw_sync = dsi->vm_timings.winकरोw_sync;
		bool hsync_end;
		स्थिर काष्ठा videomode *vm = &dsi->vm;
		पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt);
		पूर्णांक tl, t_he, width_bytes;

		hsync_end = dsi->vm_timings.trans_mode == OMAP_DSS_DSI_PULSE_MODE;
		t_he = hsync_end ?
			((hsa == 0 && ndl == 3) ? 1 : DIV_ROUND_UP(4, ndl)) : 0;

		width_bytes = DIV_ROUND_UP(vm->hactive * bpp, 8);

		/* TL = t_HS + HSA + t_HE + HFP + उच्चमान((WC + 6) / NDL) + HBP */
		tl = DIV_ROUND_UP(4, ndl) + (hsync_end ? hsa : 0) + t_he + hfp +
			DIV_ROUND_UP(width_bytes + 6, ndl) + hbp;

		DSSDBG("HBP: %d, HFP: %d, HSA: %d, TL: %d TXBYTECLKHS\n", hbp,
			hfp, hsync_end ? hsa : 0, tl);
		DSSDBG("VBP: %d, VFP: %d, VSA: %d, VACT: %d lines\n", vbp, vfp,
			vsa, vm->vactive);

		r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING1);
		r = FLD_MOD(r, hbp, 11, 0);	/* HBP */
		r = FLD_MOD(r, hfp, 23, 12);	/* HFP */
		r = FLD_MOD(r, hsync_end ? hsa : 0, 31, 24);	/* HSA */
		dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING1, r);

		r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING2);
		r = FLD_MOD(r, vbp, 7, 0);	/* VBP */
		r = FLD_MOD(r, vfp, 15, 8);	/* VFP */
		r = FLD_MOD(r, vsa, 23, 16);	/* VSA */
		r = FLD_MOD(r, winकरोw_sync, 27, 24);	/* WINDOW_SYNC */
		dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING2, r);

		r = dsi_पढ़ो_reg(dsi, DSI_VM_TIMING3);
		r = FLD_MOD(r, vm->vactive, 14, 0);	/* VACT */
		r = FLD_MOD(r, tl, 31, 16);		/* TL */
		dsi_ग_लिखो_reg(dsi, DSI_VM_TIMING3, r);
	पूर्ण
पूर्ण

अटल पूर्णांक dsi_configure_pins(काष्ठा dsi_data *dsi,
		पूर्णांक num_pins, स्थिर u32 *pins)
अणु
	काष्ठा dsi_lane_config lanes[DSI_MAX_NR_LANES];
	पूर्णांक num_lanes;
	पूर्णांक i;

	अटल स्थिर क्रमागत dsi_lane_function functions[] = अणु
		DSI_LANE_CLK,
		DSI_LANE_DATA1,
		DSI_LANE_DATA2,
		DSI_LANE_DATA3,
		DSI_LANE_DATA4,
	पूर्ण;

	अगर (num_pins < 4 || num_pins > dsi->num_lanes_supported * 2
			|| num_pins % 2 != 0)
		वापस -EINVAL;

	क्रम (i = 0; i < DSI_MAX_NR_LANES; ++i)
		lanes[i].function = DSI_LANE_UNUSED;

	num_lanes = 0;

	क्रम (i = 0; i < num_pins; i += 2) अणु
		u8 lane, pol;
		u32 dx, dy;

		dx = pins[i];
		dy = pins[i + 1];

		अगर (dx >= dsi->num_lanes_supported * 2)
			वापस -EINVAL;

		अगर (dy >= dsi->num_lanes_supported * 2)
			वापस -EINVAL;

		अगर (dx & 1) अणु
			अगर (dy != dx - 1)
				वापस -EINVAL;
			pol = 1;
		पूर्ण अन्यथा अणु
			अगर (dy != dx + 1)
				वापस -EINVAL;
			pol = 0;
		पूर्ण

		lane = dx / 2;

		lanes[lane].function = functions[i / 2];
		lanes[lane].polarity = pol;
		num_lanes++;
	पूर्ण

	स_नकल(dsi->lanes, lanes, माप(dsi->lanes));
	dsi->num_lanes_used = num_lanes;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_enable_video_mode(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	पूर्णांक bpp = mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt);
	u8 data_type;
	u16 word_count;

	चयन (dsi->pix_fmt) अणु
	हाल MIPI_DSI_FMT_RGB888:
		data_type = MIPI_DSI_PACKED_PIXEL_STREAM_24;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666:
		data_type = MIPI_DSI_PIXEL_STREAM_3BYTE_18;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB666_PACKED:
		data_type = MIPI_DSI_PACKED_PIXEL_STREAM_18;
		अवरोध;
	हाल MIPI_DSI_FMT_RGB565:
		data_type = MIPI_DSI_PACKED_PIXEL_STREAM_16;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	dsi_अगर_enable(dsi, false);
	dsi_vc_enable(dsi, vc, false);

	/* MODE, 1 = video mode */
	REG_FLD_MOD(dsi, DSI_VC_CTRL(vc), 1, 4, 4);

	word_count = DIV_ROUND_UP(dsi->vm.hactive * bpp, 8);

	dsi_vc_ग_लिखो_दीर्घ_header(dsi, vc, dsi->dsidev->channel, data_type,
			word_count, 0);

	dsi_vc_enable(dsi, vc, true);
	dsi_अगर_enable(dsi, true);

	वापस 0;
पूर्ण

अटल व्योम dsi_disable_video_mode(काष्ठा dsi_data *dsi, पूर्णांक vc)
अणु
	dsi_अगर_enable(dsi, false);
	dsi_vc_enable(dsi, vc, false);

	/* MODE, 0 = command mode */
	REG_FLD_MOD(dsi, DSI_VC_CTRL(vc), 0, 4, 4);

	dsi_vc_enable(dsi, vc, true);
	dsi_अगर_enable(dsi, true);
पूर्ण

अटल व्योम dsi_enable_video_output(काष्ठा omap_dss_device *dssdev, पूर्णांक vc)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	पूर्णांक r;

	r = dsi_init_dispc(dsi);
	अगर (r) अणु
		dev_err(dsi->dev, "failed to init dispc!\n");
		वापस;
	पूर्ण

	अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) अणु
		r = dsi_enable_video_mode(dsi, vc);
		अगर (r)
			जाओ err_video_mode;
	पूर्ण

	r = dss_mgr_enable(&dsi->output);
	अगर (r)
		जाओ err_mgr_enable;

	वापस;

err_mgr_enable:
	अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE) अणु
		dsi_अगर_enable(dsi, false);
		dsi_vc_enable(dsi, vc, false);
	पूर्ण
err_video_mode:
	dsi_uninit_dispc(dsi);
	dev_err(dsi->dev, "failed to enable DSI encoder!\n");
	वापस;
पूर्ण

अटल व्योम dsi_disable_video_output(काष्ठा omap_dss_device *dssdev, पूर्णांक vc)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);

	अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE)
		dsi_disable_video_mode(dsi, vc);

	dss_mgr_disable(&dsi->output);

	dsi_uninit_dispc(dsi);
पूर्ण

अटल व्योम dsi_update_screen_dispc(काष्ठा dsi_data *dsi)
अणु
	अचिन्हित पूर्णांक bytespp;
	अचिन्हित पूर्णांक bytespl;
	अचिन्हित पूर्णांक bytespf;
	अचिन्हित पूर्णांक total_len;
	अचिन्हित पूर्णांक packet_payload;
	अचिन्हित पूर्णांक packet_len;
	u32 l;
	पूर्णांक r;
	स्थिर अचिन्हित vc = dsi->update_vc;
	स्थिर अचिन्हित पूर्णांक line_buf_size = dsi->line_buffer_size;
	u16 w = dsi->vm.hactive;
	u16 h = dsi->vm.vactive;

	DSSDBG("dsi_update_screen_dispc(%dx%d)\n", w, h);

	bytespp	= mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt) / 8;
	bytespl = w * bytespp;
	bytespf = bytespl * h;

	/* NOTE: packet_payload has to be equal to N * bytespl, where N is
	 * number of lines in a packet.  See errata about VP_CLK_RATIO */

	अगर (bytespf < line_buf_size)
		packet_payload = bytespf;
	अन्यथा
		packet_payload = (line_buf_size) / bytespl * bytespl;

	packet_len = packet_payload + 1;	/* 1 byte क्रम DCS cmd */
	total_len = (bytespf / packet_payload) * packet_len;

	अगर (bytespf % packet_payload)
		total_len += (bytespf % packet_payload) + 1;

	l = FLD_VAL(total_len, 23, 0); /* TE_SIZE */
	dsi_ग_लिखो_reg(dsi, DSI_VC_TE(vc), l);

	dsi_vc_ग_लिखो_दीर्घ_header(dsi, vc, dsi->dsidev->channel, MIPI_DSI_DCS_LONG_WRITE,
		packet_len, 0);

	अगर (dsi->te_enabled)
		l = FLD_MOD(l, 1, 30, 30); /* TE_EN */
	अन्यथा
		l = FLD_MOD(l, 1, 31, 31); /* TE_START */
	dsi_ग_लिखो_reg(dsi, DSI_VC_TE(vc), l);

	/* We put SIDLEMODE to no-idle क्रम the duration of the transfer,
	 * because DSS पूर्णांकerrupts are not capable of waking up the CPU and the
	 * frameकरोne पूर्णांकerrupt could be delayed क्रम quite a दीर्घ समय. I think
	 * the same goes क्रम any DSS पूर्णांकerrupts, but क्रम some reason I have not
	 * seen the problem anywhere अन्यथा than here.
	 */
	dispc_disable_sidle(dsi->dss->dispc);

	dsi_perf_mark_start(dsi);

	r = schedule_delayed_work(&dsi->frameकरोne_समयout_work,
		msecs_to_jअगरfies(250));
	BUG_ON(r == 0);

	dss_mgr_start_update(&dsi->output);

	अगर (dsi->te_enabled) अणु
		/* disable LP_RX_TO, so that we can receive TE.  Time to रुको
		 * क्रम TE is दीर्घer than the समयr allows */
		REG_FLD_MOD(dsi, DSI_TIMING2, 0, 15, 15); /* LP_RX_TO */

		dsi_vc_send_bta(dsi, vc);

#अगर_घोषित DSI_CATCH_MISSING_TE
		mod_समयr(&dsi->te_समयr, jअगरfies + msecs_to_jअगरfies(250));
#पूर्ण_अगर
	पूर्ण
पूर्ण

#अगर_घोषित DSI_CATCH_MISSING_TE
अटल व्योम dsi_te_समयout(काष्ठा समयr_list *unused)
अणु
	DSSERR("TE not received for 250ms!\n");
पूर्ण
#पूर्ण_अगर

अटल व्योम dsi_handle_frameकरोne(काष्ठा dsi_data *dsi, पूर्णांक error)
अणु
	/* SIDLEMODE back to smart-idle */
	dispc_enable_sidle(dsi->dss->dispc);

	अगर (dsi->te_enabled) अणु
		/* enable LP_RX_TO again after the TE */
		REG_FLD_MOD(dsi, DSI_TIMING2, 1, 15, 15); /* LP_RX_TO */
	पूर्ण

	dsi_bus_unlock(dsi);

	अगर (!error)
		dsi_perf_show(dsi, "DISPC");
पूर्ण

अटल व्योम dsi_frameकरोne_समयout_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dsi_data *dsi = container_of(work, काष्ठा dsi_data,
			frameकरोne_समयout_work.work);
	/* XXX While extremely unlikely, we could get FRAMEDONE पूर्णांकerrupt after
	 * 250ms which would conflict with this समयout work. What should be
	 * करोne is first cancel the transfer on the HW, and then cancel the
	 * possibly scheduled frameकरोne work. However, cancelling the transfer
	 * on the HW is buggy, and would probably require resetting the whole
	 * DSI */

	DSSERR("Framedone not received for 250ms!\n");

	dsi_handle_frameकरोne(dsi, -ETIMEDOUT);
पूर्ण

अटल व्योम dsi_frameकरोne_irq_callback(व्योम *data)
अणु
	काष्ठा dsi_data *dsi = data;

	/* Note: We get FRAMEDONE when DISPC has finished sending pixels and
	 * turns itself off. However, DSI still has the pixels in its buffers,
	 * and is sending the data.
	 */

	cancel_delayed_work(&dsi->frameकरोne_समयout_work);

	DSSDBG("Framedone received!\n");

	dsi_handle_frameकरोne(dsi, 0);
पूर्ण

अटल पूर्णांक _dsi_update(काष्ठा dsi_data *dsi)
अणु
	dsi_perf_mark_setup(dsi);

#अगर_घोषित DSI_PERF_MEASURE
	dsi->update_bytes = dsi->vm.hactive * dsi->vm.vactive *
		mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt) / 8;
#पूर्ण_अगर
	dsi_update_screen_dispc(dsi);

	वापस 0;
पूर्ण

अटल पूर्णांक _dsi_send_nop(काष्ठा dsi_data *dsi, पूर्णांक vc, पूर्णांक channel)
अणु
	स्थिर u8 payload[] = अणु MIPI_DCS_NOP पूर्ण;
	स्थिर काष्ठा mipi_dsi_msg msg = अणु
		.channel = channel,
		.type = MIPI_DSI_DCS_SHORT_WRITE,
		.tx_len = 1,
		.tx_buf = payload,
	पूर्ण;

	WARN_ON(!dsi_bus_is_locked(dsi));

	वापस _omap_dsi_host_transfer(dsi, vc, &msg);
पूर्ण

अटल पूर्णांक dsi_update_channel(काष्ठा omap_dss_device *dssdev, पूर्णांक vc)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	पूर्णांक r;

	dsi_bus_lock(dsi);

	अगर (!dsi->video_enabled) अणु
		r = -EIO;
		जाओ err;
	पूर्ण

	अगर (dsi->vm.hactive == 0 || dsi->vm.vactive == 0) अणु
		r = -EINVAL;
		जाओ err;
	पूर्ण

	DSSDBG("dsi_update_channel: %d", vc);

	/*
	 * Send NOP between the frames. If we करोn't send something here, the
	 * updates stop working. This is probably related to DSI spec stating
	 * that the DSI host should transition to LP at least once per frame.
	 */
	r = _dsi_send_nop(dsi, VC_CMD, dsi->dsidev->channel);
	अगर (r < 0) अणु
		DSSWARN("failed to send nop between frames: %d\n", r);
		जाओ err;
	पूर्ण

	dsi->update_vc = vc;

	अगर (dsi->te_enabled && dsi->te_gpio) अणु
		schedule_delayed_work(&dsi->te_समयout_work,
				      msecs_to_jअगरfies(250));
		atomic_set(&dsi->करो_ext_te_update, 1);
	पूर्ण अन्यथा अणु
		_dsi_update(dsi);
	पूर्ण

	वापस 0;

err:
	dsi_bus_unlock(dsi);
	वापस r;
पूर्ण

अटल पूर्णांक dsi_update_all(काष्ठा omap_dss_device *dssdev)
अणु
	वापस dsi_update_channel(dssdev, VC_VIDEO);
पूर्ण

/* Display funcs */

अटल पूर्णांक dsi_configure_dispc_घड़ीs(काष्ठा dsi_data *dsi)
अणु
	काष्ठा dispc_घड़ी_info dispc_cinfo;
	पूर्णांक r;
	अचिन्हित दीर्घ fck;

	fck = dsi_get_pll_hsभाग_dispc_rate(dsi);

	dispc_cinfo.lck_भाग = dsi->user_dispc_cinfo.lck_भाग;
	dispc_cinfo.pck_भाग = dsi->user_dispc_cinfo.pck_भाग;

	r = dispc_calc_घड़ी_rates(dsi->dss->dispc, fck, &dispc_cinfo);
	अगर (r) अणु
		DSSERR("Failed to calc dispc clocks\n");
		वापस r;
	पूर्ण

	dsi->mgr_config.घड़ी_info = dispc_cinfo;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_init_dispc(काष्ठा dsi_data *dsi)
अणु
	क्रमागत omap_channel dispc_channel = dsi->output.dispc_channel;
	पूर्णांक r;

	dss_select_lcd_clk_source(dsi->dss, dispc_channel, dsi->module_id == 0 ?
			DSS_CLK_SRC_PLL1_1 :
			DSS_CLK_SRC_PLL2_1);

	अगर (dsi->mode == OMAP_DSS_DSI_CMD_MODE) अणु
		r = dss_mgr_रेजिस्टर_frameकरोne_handler(&dsi->output,
				dsi_frameकरोne_irq_callback, dsi);
		अगर (r) अणु
			DSSERR("can't register FRAMEDONE handler\n");
			जाओ err;
		पूर्ण

		dsi->mgr_config.stallmode = true;
		dsi->mgr_config.fअगरohandcheck = true;
	पूर्ण अन्यथा अणु
		dsi->mgr_config.stallmode = false;
		dsi->mgr_config.fअगरohandcheck = false;
	पूर्ण

	r = dsi_configure_dispc_घड़ीs(dsi);
	अगर (r)
		जाओ err1;

	dsi->mgr_config.io_pad_mode = DSS_IO_PAD_MODE_BYPASS;
	dsi->mgr_config.video_port_width =
			mipi_dsi_pixel_क्रमmat_to_bpp(dsi->pix_fmt);
	dsi->mgr_config.lcden_sig_polarity = 0;

	dss_mgr_set_lcd_config(&dsi->output, &dsi->mgr_config);

	वापस 0;
err1:
	अगर (dsi->mode == OMAP_DSS_DSI_CMD_MODE)
		dss_mgr_unरेजिस्टर_frameकरोne_handler(&dsi->output,
				dsi_frameकरोne_irq_callback, dsi);
err:
	dss_select_lcd_clk_source(dsi->dss, dispc_channel, DSS_CLK_SRC_FCK);
	वापस r;
पूर्ण

अटल व्योम dsi_uninit_dispc(काष्ठा dsi_data *dsi)
अणु
	क्रमागत omap_channel dispc_channel = dsi->output.dispc_channel;

	अगर (dsi->mode == OMAP_DSS_DSI_CMD_MODE)
		dss_mgr_unरेजिस्टर_frameकरोne_handler(&dsi->output,
				dsi_frameकरोne_irq_callback, dsi);

	dss_select_lcd_clk_source(dsi->dss, dispc_channel, DSS_CLK_SRC_FCK);
पूर्ण

अटल पूर्णांक dsi_configure_dsi_घड़ीs(काष्ठा dsi_data *dsi)
अणु
	काष्ठा dss_pll_घड़ी_info cinfo;
	पूर्णांक r;

	cinfo = dsi->user_dsi_cinfo;

	r = dss_pll_set_config(&dsi->pll, &cinfo);
	अगर (r) अणु
		DSSERR("Failed to set dsi clocks\n");
		वापस r;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dsi_setup_dsi_vcs(काष्ठा dsi_data *dsi)
अणु
	/* Setup VC_CMD क्रम LP and cpu transfers */
	REG_FLD_MOD(dsi, DSI_VC_CTRL(VC_CMD), 0, 9, 9); /* LP */

	REG_FLD_MOD(dsi, DSI_VC_CTRL(VC_CMD), 0, 1, 1); /* SOURCE_L4 */
	dsi->vc[VC_CMD].source = DSI_VC_SOURCE_L4;

	/* Setup VC_VIDEO क्रम HS and dispc transfers */
	REG_FLD_MOD(dsi, DSI_VC_CTRL(VC_VIDEO), 1, 9, 9); /* HS */

	REG_FLD_MOD(dsi, DSI_VC_CTRL(VC_VIDEO), 1, 1, 1); /* SOURCE_VP */
	dsi->vc[VC_VIDEO].source = DSI_VC_SOURCE_VP;

	अगर ((dsi->data->quirks & DSI_QUIRK_DCS_CMD_CONFIG_VC) &&
	    !(dsi->dsidev->mode_flags & MIPI_DSI_MODE_VIDEO))
		REG_FLD_MOD(dsi, DSI_VC_CTRL(VC_VIDEO), 1, 30, 30); /* DCS_CMD_ENABLE */

	dsi_vc_enable(dsi, VC_CMD, 1);
	dsi_vc_enable(dsi, VC_VIDEO, 1);

	dsi_अगर_enable(dsi, 1);

	dsi_क्रमce_tx_stop_mode_io(dsi);

	/* start the DDR घड़ी by sending a शून्य packet */
	अगर (!(dsi->dsidev->mode_flags & MIPI_DSI_CLOCK_NON_CONTINUOUS))
		dsi_vc_send_null(dsi, VC_CMD, dsi->dsidev->channel);
पूर्ण

अटल पूर्णांक dsi_init_dsi(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक r;

	r = dss_pll_enable(&dsi->pll);
	अगर (r)
		वापस r;

	r = dsi_configure_dsi_घड़ीs(dsi);
	अगर (r)
		जाओ err0;

	dss_select_dsi_clk_source(dsi->dss, dsi->module_id,
				  dsi->module_id == 0 ?
				  DSS_CLK_SRC_PLL1_2 : DSS_CLK_SRC_PLL2_2);

	DSSDBG("PLL OK\n");

	अगर (!dsi->vdds_dsi_enabled) अणु
		r = regulator_enable(dsi->vdds_dsi_reg);
		अगर (r)
			जाओ err1;

		dsi->vdds_dsi_enabled = true;
	पूर्ण

	r = dsi_cio_init(dsi);
	अगर (r)
		जाओ err2;

	_dsi_prपूर्णांक_reset_status(dsi);

	dsi_proto_timings(dsi);
	dsi_set_lp_clk_भागisor(dsi);

	अगर (1)
		_dsi_prपूर्णांक_reset_status(dsi);

	r = dsi_proto_config(dsi);
	अगर (r)
		जाओ err3;

	dsi_setup_dsi_vcs(dsi);

	वापस 0;
err3:
	dsi_cio_uninit(dsi);
err2:
	regulator_disable(dsi->vdds_dsi_reg);
	dsi->vdds_dsi_enabled = false;
err1:
	dss_select_dsi_clk_source(dsi->dss, dsi->module_id, DSS_CLK_SRC_FCK);
err0:
	dss_pll_disable(&dsi->pll);

	वापस r;
पूर्ण

अटल व्योम dsi_uninit_dsi(काष्ठा dsi_data *dsi)
अणु
	/* disable पूर्णांकerface */
	dsi_अगर_enable(dsi, 0);
	dsi_vc_enable(dsi, 0, 0);
	dsi_vc_enable(dsi, 1, 0);
	dsi_vc_enable(dsi, 2, 0);
	dsi_vc_enable(dsi, 3, 0);

	dss_select_dsi_clk_source(dsi->dss, dsi->module_id, DSS_CLK_SRC_FCK);
	dsi_cio_uninit(dsi);
	dss_pll_disable(&dsi->pll);

	regulator_disable(dsi->vdds_dsi_reg);
	dsi->vdds_dsi_enabled = false;
पूर्ण

अटल व्योम dsi_enable(काष्ठा dsi_data *dsi)
अणु
	पूर्णांक r;

	WARN_ON(!dsi_bus_is_locked(dsi));

	अगर (WARN_ON(dsi->अगरace_enabled))
		वापस;

	mutex_lock(&dsi->lock);

	r = dsi_runसमय_get(dsi);
	अगर (r)
		जाओ err_get_dsi;

	_dsi_initialize_irq(dsi);

	r = dsi_init_dsi(dsi);
	अगर (r)
		जाओ err_init_dsi;

	dsi->अगरace_enabled = true;

	mutex_unlock(&dsi->lock);

	वापस;

err_init_dsi:
	dsi_runसमय_put(dsi);
err_get_dsi:
	mutex_unlock(&dsi->lock);
	DSSDBG("dsi_enable FAILED\n");
पूर्ण

अटल व्योम dsi_disable(काष्ठा dsi_data *dsi)
अणु
	WARN_ON(!dsi_bus_is_locked(dsi));

	अगर (WARN_ON(!dsi->अगरace_enabled))
		वापस;

	mutex_lock(&dsi->lock);

	dsi_sync_vc(dsi, 0);
	dsi_sync_vc(dsi, 1);
	dsi_sync_vc(dsi, 2);
	dsi_sync_vc(dsi, 3);

	dsi_uninit_dsi(dsi);

	dsi_runसमय_put(dsi);

	dsi->अगरace_enabled = false;

	mutex_unlock(&dsi->lock);
पूर्ण

अटल पूर्णांक dsi_enable_te(काष्ठा dsi_data *dsi, bool enable)
अणु
	dsi->te_enabled = enable;

	अगर (dsi->te_gpio) अणु
		अगर (enable)
			enable_irq(dsi->te_irq);
		अन्यथा
			disable_irq(dsi->te_irq);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित PRINT_VERBOSE_VM_TIMINGS
अटल व्योम prपूर्णांक_dsi_vm(स्थिर अक्षर *str,
		स्थिर काष्ठा omap_dss_dsi_videomode_timings *t)
अणु
	अचिन्हित दीर्घ byteclk = t->hsclk / 4;
	पूर्णांक bl, wc, pps, tot;

	wc = DIV_ROUND_UP(t->hact * t->bitspp, 8);
	pps = DIV_ROUND_UP(wc + 6, t->ndl); /* pixel packet size */
	bl = t->hss + t->hsa + t->hse + t->hbp + t->hfp;
	tot = bl + pps;

#घोषणा TO_DSI_T(x) ((u32)भाग64_u64((u64)x * 1000000000llu, byteclk))

	pr_debug("%s bck %lu, %u/%u/%u/%u/%u/%u = %u+%u = %u, "
			"%u/%u/%u/%u/%u/%u = %u + %u = %u\n",
			str,
			byteclk,
			t->hss, t->hsa, t->hse, t->hbp, pps, t->hfp,
			bl, pps, tot,
			TO_DSI_T(t->hss),
			TO_DSI_T(t->hsa),
			TO_DSI_T(t->hse),
			TO_DSI_T(t->hbp),
			TO_DSI_T(pps),
			TO_DSI_T(t->hfp),

			TO_DSI_T(bl),
			TO_DSI_T(pps),

			TO_DSI_T(tot));
#अघोषित TO_DSI_T
पूर्ण

अटल व्योम prपूर्णांक_dispc_vm(स्थिर अक्षर *str, स्थिर काष्ठा videomode *vm)
अणु
	अचिन्हित दीर्घ pck = vm->pixelघड़ी;
	पूर्णांक hact, bl, tot;

	hact = vm->hactive;
	bl = vm->hsync_len + vm->hback_porch + vm->hfront_porch;
	tot = hact + bl;

#घोषणा TO_DISPC_T(x) ((u32)भाग64_u64((u64)x * 1000000000llu, pck))

	pr_debug("%s pck %lu, %u/%u/%u/%u = %u+%u = %u, "
			"%u/%u/%u/%u = %u + %u = %u\n",
			str,
			pck,
			vm->hsync_len, vm->hback_porch, hact, vm->hfront_porch,
			bl, hact, tot,
			TO_DISPC_T(vm->hsync_len),
			TO_DISPC_T(vm->hback_porch),
			TO_DISPC_T(hact),
			TO_DISPC_T(vm->hfront_porch),
			TO_DISPC_T(bl),
			TO_DISPC_T(hact),
			TO_DISPC_T(tot));
#अघोषित TO_DISPC_T
पूर्ण

/* note: this is not quite accurate */
अटल व्योम prपूर्णांक_dsi_dispc_vm(स्थिर अक्षर *str,
		स्थिर काष्ठा omap_dss_dsi_videomode_timings *t)
अणु
	काष्ठा videomode vm = अणु 0 पूर्ण;
	अचिन्हित दीर्घ byteclk = t->hsclk / 4;
	अचिन्हित दीर्घ pck;
	u64 dsi_tput;
	पूर्णांक dsi_hact, dsi_htot;

	dsi_tput = (u64)byteclk * t->ndl * 8;
	pck = (u32)भाग64_u64(dsi_tput, t->bitspp);
	dsi_hact = DIV_ROUND_UP(DIV_ROUND_UP(t->hact * t->bitspp, 8) + 6, t->ndl);
	dsi_htot = t->hss + t->hsa + t->hse + t->hbp + dsi_hact + t->hfp;

	vm.pixelघड़ी = pck;
	vm.hsync_len = भाग64_u64((u64)(t->hsa + t->hse) * pck, byteclk);
	vm.hback_porch = भाग64_u64((u64)t->hbp * pck, byteclk);
	vm.hfront_porch = भाग64_u64((u64)t->hfp * pck, byteclk);
	vm.hactive = t->hact;

	prपूर्णांक_dispc_vm(str, &vm);
पूर्ण
#पूर्ण_अगर /* PRINT_VERBOSE_VM_TIMINGS */

अटल bool dsi_cm_calc_dispc_cb(पूर्णांक lckd, पूर्णांक pckd, अचिन्हित दीर्घ lck,
		अचिन्हित दीर्घ pck, व्योम *data)
अणु
	काष्ठा dsi_clk_calc_ctx *ctx = data;
	काष्ठा videomode *vm = &ctx->vm;

	ctx->dispc_cinfo.lck_भाग = lckd;
	ctx->dispc_cinfo.pck_भाग = pckd;
	ctx->dispc_cinfo.lck = lck;
	ctx->dispc_cinfo.pck = pck;

	*vm = *ctx->config->vm;
	vm->pixelघड़ी = pck;
	vm->hactive = ctx->config->vm->hactive;
	vm->vactive = ctx->config->vm->vactive;
	vm->hsync_len = vm->hfront_porch = vm->hback_porch = vm->vsync_len = 1;
	vm->vfront_porch = vm->vback_porch = 0;

	वापस true;
पूर्ण

अटल bool dsi_cm_calc_hsभाग_cb(पूर्णांक m_dispc, अचिन्हित दीर्घ dispc,
		व्योम *data)
अणु
	काष्ठा dsi_clk_calc_ctx *ctx = data;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.clkout[HSDIV_DISPC] = dispc;

	वापस dispc_भाग_calc(ctx->dsi->dss->dispc, dispc,
			      ctx->req_pck_min, ctx->req_pck_max,
			      dsi_cm_calc_dispc_cb, ctx);
पूर्ण

अटल bool dsi_cm_calc_pll_cb(पूर्णांक n, पूर्णांक m, अचिन्हित दीर्घ fपूर्णांक,
		अचिन्हित दीर्घ clkdco, व्योम *data)
अणु
	काष्ठा dsi_clk_calc_ctx *ctx = data;
	काष्ठा dsi_data *dsi = ctx->dsi;

	ctx->dsi_cinfo.n = n;
	ctx->dsi_cinfo.m = m;
	ctx->dsi_cinfo.fपूर्णांक = fपूर्णांक;
	ctx->dsi_cinfo.clkdco = clkdco;

	वापस dss_pll_hsभाग_calc_a(ctx->pll, clkdco, ctx->req_pck_min,
			dsi->data->max_fck_freq,
			dsi_cm_calc_hsभाग_cb, ctx);
पूर्ण

अटल bool dsi_cm_calc(काष्ठा dsi_data *dsi,
		स्थिर काष्ठा omap_dss_dsi_config *cfg,
		काष्ठा dsi_clk_calc_ctx *ctx)
अणु
	अचिन्हित दीर्घ clkin;
	पूर्णांक bitspp, ndl;
	अचिन्हित दीर्घ pll_min, pll_max;
	अचिन्हित दीर्घ pck, txbyteclk;

	clkin = clk_get_rate(dsi->pll.clkin);
	bitspp = mipi_dsi_pixel_क्रमmat_to_bpp(cfg->pixel_क्रमmat);
	ndl = dsi->num_lanes_used - 1;

	/*
	 * Here we should calculate minimum txbyteclk to be able to send the
	 * frame in समय, and also to handle TE. That's not very simple, though,
	 * especially as we go to LP between each pixel packet due to HW
	 * "feature". So let's just estimate very roughly and multiply by 1.5.
	 */
	pck = cfg->vm->pixelघड़ी;
	pck = pck * 3 / 2;
	txbyteclk = pck * bitspp / 8 / ndl;

	स_रखो(ctx, 0, माप(*ctx));
	ctx->dsi = dsi;
	ctx->pll = &dsi->pll;
	ctx->config = cfg;
	ctx->req_pck_min = pck;
	ctx->req_pck_nom = pck;
	ctx->req_pck_max = pck * 3 / 2;

	pll_min = max(cfg->hs_clk_min * 4, txbyteclk * 4 * 4);
	pll_max = cfg->hs_clk_max * 4;

	वापस dss_pll_calc_a(ctx->pll, clkin,
			pll_min, pll_max,
			dsi_cm_calc_pll_cb, ctx);
पूर्ण

अटल bool dsi_vm_calc_blanking(काष्ठा dsi_clk_calc_ctx *ctx)
अणु
	काष्ठा dsi_data *dsi = ctx->dsi;
	स्थिर काष्ठा omap_dss_dsi_config *cfg = ctx->config;
	पूर्णांक bitspp = mipi_dsi_pixel_क्रमmat_to_bpp(cfg->pixel_क्रमmat);
	पूर्णांक ndl = dsi->num_lanes_used - 1;
	अचिन्हित दीर्घ hsclk = ctx->dsi_cinfo.clkdco / 4;
	अचिन्हित दीर्घ byteclk = hsclk / 4;

	अचिन्हित दीर्घ dispc_pck, req_pck_min, req_pck_nom, req_pck_max;
	पूर्णांक xres;
	पूर्णांक panel_htot, panel_hbl; /* pixels */
	पूर्णांक dispc_htot, dispc_hbl; /* pixels */
	पूर्णांक dsi_htot, dsi_hact, dsi_hbl, hss, hse; /* byteclks */
	पूर्णांक hfp, hsa, hbp;
	स्थिर काष्ठा videomode *req_vm;
	काष्ठा videomode *dispc_vm;
	काष्ठा omap_dss_dsi_videomode_timings *dsi_vm;
	u64 dsi_tput, dispc_tput;

	dsi_tput = (u64)byteclk * ndl * 8;

	req_vm = cfg->vm;
	req_pck_min = ctx->req_pck_min;
	req_pck_max = ctx->req_pck_max;
	req_pck_nom = ctx->req_pck_nom;

	dispc_pck = ctx->dispc_cinfo.pck;
	dispc_tput = (u64)dispc_pck * bitspp;

	xres = req_vm->hactive;

	panel_hbl = req_vm->hfront_porch + req_vm->hback_porch +
		    req_vm->hsync_len;
	panel_htot = xres + panel_hbl;

	dsi_hact = DIV_ROUND_UP(DIV_ROUND_UP(xres * bitspp, 8) + 6, ndl);

	/*
	 * When there are no line buffers, DISPC and DSI must have the
	 * same tput. Otherwise DISPC tput needs to be higher than DSI's.
	 */
	अगर (dsi->line_buffer_size < xres * bitspp / 8) अणु
		अगर (dispc_tput != dsi_tput)
			वापस false;
	पूर्ण अन्यथा अणु
		अगर (dispc_tput < dsi_tput)
			वापस false;
	पूर्ण

	/* DSI tput must be over the min requirement */
	अगर (dsi_tput < (u64)bitspp * req_pck_min)
		वापस false;

	/* When non-burst mode, DSI tput must be below max requirement. */
	अगर (cfg->trans_mode != OMAP_DSS_DSI_BURST_MODE) अणु
		अगर (dsi_tput > (u64)bitspp * req_pck_max)
			वापस false;
	पूर्ण

	hss = DIV_ROUND_UP(4, ndl);

	अगर (cfg->trans_mode == OMAP_DSS_DSI_PULSE_MODE) अणु
		अगर (ndl == 3 && req_vm->hsync_len == 0)
			hse = 1;
		अन्यथा
			hse = DIV_ROUND_UP(4, ndl);
	पूर्ण अन्यथा अणु
		hse = 0;
	पूर्ण

	/* DSI htot to match the panel's nominal pck */
	dsi_htot = भाग64_u64((u64)panel_htot * byteclk, req_pck_nom);

	/* fail अगर there would be no समय क्रम blanking */
	अगर (dsi_htot < hss + hse + dsi_hact)
		वापस false;

	/* total DSI blanking needed to achieve panel's TL */
	dsi_hbl = dsi_htot - dsi_hact;

	/* DISPC htot to match the DSI TL */
	dispc_htot = भाग64_u64((u64)dsi_htot * dispc_pck, byteclk);

	/* verअगरy that the DSI and DISPC TLs are the same */
	अगर ((u64)dsi_htot * dispc_pck != (u64)dispc_htot * byteclk)
		वापस false;

	dispc_hbl = dispc_htot - xres;

	/* setup DSI videomode */

	dsi_vm = &ctx->dsi_vm;
	स_रखो(dsi_vm, 0, माप(*dsi_vm));

	dsi_vm->hsclk = hsclk;

	dsi_vm->ndl = ndl;
	dsi_vm->bitspp = bitspp;

	अगर (cfg->trans_mode != OMAP_DSS_DSI_PULSE_MODE) अणु
		hsa = 0;
	पूर्ण अन्यथा अगर (ndl == 3 && req_vm->hsync_len == 0) अणु
		hsa = 0;
	पूर्ण अन्यथा अणु
		hsa = भाग64_u64((u64)req_vm->hsync_len * byteclk, req_pck_nom);
		hsa = max(hsa - hse, 1);
	पूर्ण

	hbp = भाग64_u64((u64)req_vm->hback_porch * byteclk, req_pck_nom);
	hbp = max(hbp, 1);

	hfp = dsi_hbl - (hss + hsa + hse + hbp);
	अगर (hfp < 1) अणु
		पूर्णांक t;
		/* we need to take cycles from hbp */

		t = 1 - hfp;
		hbp = max(hbp - t, 1);
		hfp = dsi_hbl - (hss + hsa + hse + hbp);

		अगर (hfp < 1 && hsa > 0) अणु
			/* we need to take cycles from hsa */
			t = 1 - hfp;
			hsa = max(hsa - t, 1);
			hfp = dsi_hbl - (hss + hsa + hse + hbp);
		पूर्ण
	पूर्ण

	अगर (hfp < 1)
		वापस false;

	dsi_vm->hss = hss;
	dsi_vm->hsa = hsa;
	dsi_vm->hse = hse;
	dsi_vm->hbp = hbp;
	dsi_vm->hact = xres;
	dsi_vm->hfp = hfp;

	dsi_vm->vsa = req_vm->vsync_len;
	dsi_vm->vbp = req_vm->vback_porch;
	dsi_vm->vact = req_vm->vactive;
	dsi_vm->vfp = req_vm->vfront_porch;

	dsi_vm->trans_mode = cfg->trans_mode;

	dsi_vm->blanking_mode = 0;
	dsi_vm->hsa_blanking_mode = 1;
	dsi_vm->hfp_blanking_mode = 1;
	dsi_vm->hbp_blanking_mode = 1;

	dsi_vm->winकरोw_sync = 4;

	/* setup DISPC videomode */

	dispc_vm = &ctx->vm;
	*dispc_vm = *req_vm;
	dispc_vm->pixelघड़ी = dispc_pck;

	अगर (cfg->trans_mode == OMAP_DSS_DSI_PULSE_MODE) अणु
		hsa = भाग64_u64((u64)req_vm->hsync_len * dispc_pck,
				req_pck_nom);
		hsa = max(hsa, 1);
	पूर्ण अन्यथा अणु
		hsa = 1;
	पूर्ण

	hbp = भाग64_u64((u64)req_vm->hback_porch * dispc_pck, req_pck_nom);
	hbp = max(hbp, 1);

	hfp = dispc_hbl - hsa - hbp;
	अगर (hfp < 1) अणु
		पूर्णांक t;
		/* we need to take cycles from hbp */

		t = 1 - hfp;
		hbp = max(hbp - t, 1);
		hfp = dispc_hbl - hsa - hbp;

		अगर (hfp < 1) अणु
			/* we need to take cycles from hsa */
			t = 1 - hfp;
			hsa = max(hsa - t, 1);
			hfp = dispc_hbl - hsa - hbp;
		पूर्ण
	पूर्ण

	अगर (hfp < 1)
		वापस false;

	dispc_vm->hfront_porch = hfp;
	dispc_vm->hsync_len = hsa;
	dispc_vm->hback_porch = hbp;

	वापस true;
पूर्ण


अटल bool dsi_vm_calc_dispc_cb(पूर्णांक lckd, पूर्णांक pckd, अचिन्हित दीर्घ lck,
		अचिन्हित दीर्घ pck, व्योम *data)
अणु
	काष्ठा dsi_clk_calc_ctx *ctx = data;

	ctx->dispc_cinfo.lck_भाग = lckd;
	ctx->dispc_cinfo.pck_भाग = pckd;
	ctx->dispc_cinfo.lck = lck;
	ctx->dispc_cinfo.pck = pck;

	अगर (dsi_vm_calc_blanking(ctx) == false)
		वापस false;

#अगर_घोषित PRINT_VERBOSE_VM_TIMINGS
	prपूर्णांक_dispc_vm("dispc", &ctx->vm);
	prपूर्णांक_dsi_vm("dsi  ", &ctx->dsi_vm);
	prपूर्णांक_dispc_vm("req  ", ctx->config->vm);
	prपूर्णांक_dsi_dispc_vm("act  ", &ctx->dsi_vm);
#पूर्ण_अगर

	वापस true;
पूर्ण

अटल bool dsi_vm_calc_hsभाग_cb(पूर्णांक m_dispc, अचिन्हित दीर्घ dispc,
		व्योम *data)
अणु
	काष्ठा dsi_clk_calc_ctx *ctx = data;
	अचिन्हित दीर्घ pck_max;

	ctx->dsi_cinfo.mX[HSDIV_DISPC] = m_dispc;
	ctx->dsi_cinfo.clkout[HSDIV_DISPC] = dispc;

	/*
	 * In burst mode we can let the dispc pck be arbitrarily high, but it
	 * limits our scaling abilities. So क्रम now, करोn't aim too high.
	 */

	अगर (ctx->config->trans_mode == OMAP_DSS_DSI_BURST_MODE)
		pck_max = ctx->req_pck_max + 10000000;
	अन्यथा
		pck_max = ctx->req_pck_max;

	वापस dispc_भाग_calc(ctx->dsi->dss->dispc, dispc,
			      ctx->req_pck_min, pck_max,
			      dsi_vm_calc_dispc_cb, ctx);
पूर्ण

अटल bool dsi_vm_calc_pll_cb(पूर्णांक n, पूर्णांक m, अचिन्हित दीर्घ fपूर्णांक,
		अचिन्हित दीर्घ clkdco, व्योम *data)
अणु
	काष्ठा dsi_clk_calc_ctx *ctx = data;
	काष्ठा dsi_data *dsi = ctx->dsi;

	ctx->dsi_cinfo.n = n;
	ctx->dsi_cinfo.m = m;
	ctx->dsi_cinfo.fपूर्णांक = fपूर्णांक;
	ctx->dsi_cinfo.clkdco = clkdco;

	वापस dss_pll_hsभाग_calc_a(ctx->pll, clkdco, ctx->req_pck_min,
			dsi->data->max_fck_freq,
			dsi_vm_calc_hsभाग_cb, ctx);
पूर्ण

अटल bool dsi_vm_calc(काष्ठा dsi_data *dsi,
		स्थिर काष्ठा omap_dss_dsi_config *cfg,
		काष्ठा dsi_clk_calc_ctx *ctx)
अणु
	स्थिर काष्ठा videomode *vm = cfg->vm;
	अचिन्हित दीर्घ clkin;
	अचिन्हित दीर्घ pll_min;
	अचिन्हित दीर्घ pll_max;
	पूर्णांक ndl = dsi->num_lanes_used - 1;
	पूर्णांक bitspp = mipi_dsi_pixel_क्रमmat_to_bpp(cfg->pixel_क्रमmat);
	अचिन्हित दीर्घ byteclk_min;

	clkin = clk_get_rate(dsi->pll.clkin);

	स_रखो(ctx, 0, माप(*ctx));
	ctx->dsi = dsi;
	ctx->pll = &dsi->pll;
	ctx->config = cfg;

	/* these limits should come from the panel driver */
	ctx->req_pck_min = vm->pixelघड़ी - 1000;
	ctx->req_pck_nom = vm->pixelघड़ी;
	ctx->req_pck_max = vm->pixelघड़ी + 1000;

	byteclk_min = भाग64_u64((u64)ctx->req_pck_min * bitspp, ndl * 8);
	pll_min = max(cfg->hs_clk_min * 4, byteclk_min * 4 * 4);

	अगर (cfg->trans_mode == OMAP_DSS_DSI_BURST_MODE) अणु
		pll_max = cfg->hs_clk_max * 4;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ byteclk_max;
		byteclk_max = भाग64_u64((u64)ctx->req_pck_max * bitspp,
				ndl * 8);

		pll_max = byteclk_max * 4 * 4;
	पूर्ण

	वापस dss_pll_calc_a(ctx->pll, clkin,
			pll_min, pll_max,
			dsi_vm_calc_pll_cb, ctx);
पूर्ण

अटल bool dsi_is_video_mode(काष्ठा omap_dss_device *dssdev)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);

	वापस dsi->mode == OMAP_DSS_DSI_VIDEO_MODE;
पूर्ण

अटल पूर्णांक __dsi_calc_config(काष्ठा dsi_data *dsi,
		स्थिर काष्ठा drm_display_mode *mode,
		काष्ठा dsi_clk_calc_ctx *ctx)
अणु
	काष्ठा omap_dss_dsi_config cfg = dsi->config;
	काष्ठा videomode vm;
	bool ok;
	पूर्णांक r;

	drm_display_mode_to_videomode(mode, &vm);

	cfg.vm = &vm;
	cfg.mode = dsi->mode;
	cfg.pixel_क्रमmat = dsi->pix_fmt;

	अगर (dsi->mode == OMAP_DSS_DSI_VIDEO_MODE)
		ok = dsi_vm_calc(dsi, &cfg, ctx);
	अन्यथा
		ok = dsi_cm_calc(dsi, &cfg, ctx);

	अगर (!ok)
		वापस -EINVAL;

	dsi_pll_calc_dsi_fck(dsi, &ctx->dsi_cinfo);

	r = dsi_lp_घड़ी_calc(ctx->dsi_cinfo.clkout[HSDIV_DSI],
		cfg.lp_clk_min, cfg.lp_clk_max, &ctx->lp_cinfo);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_set_config(काष्ठा omap_dss_device *dssdev,
		स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dsi_data *dsi = to_dsi_data(dssdev);
	काष्ठा dsi_clk_calc_ctx ctx;
	पूर्णांक r;

	mutex_lock(&dsi->lock);

	r = __dsi_calc_config(dsi, mode, &ctx);
	अगर (r) अणु
		DSSERR("failed to find suitable DSI clock settings\n");
		जाओ err;
	पूर्ण

	dsi->user_lp_cinfo = ctx.lp_cinfo;
	dsi->user_dsi_cinfo = ctx.dsi_cinfo;
	dsi->user_dispc_cinfo = ctx.dispc_cinfo;

	dsi->vm = ctx.vm;

	/*
	 * override पूर्णांकerlace, logic level and edge related parameters in
	 * videomode with शेष values
	 */
	dsi->vm.flags &= ~DISPLAY_FLAGS_INTERLACED;
	dsi->vm.flags &= ~DISPLAY_FLAGS_HSYNC_LOW;
	dsi->vm.flags |= DISPLAY_FLAGS_HSYNC_HIGH;
	dsi->vm.flags &= ~DISPLAY_FLAGS_VSYNC_LOW;
	dsi->vm.flags |= DISPLAY_FLAGS_VSYNC_HIGH;
	/*
	 * HACK: These flags should be handled through the omap_dss_device bus
	 * flags, but this will only be possible when the DSI encoder will be
	 * converted to the omapdrm-managed encoder model.
	 */
	dsi->vm.flags &= ~DISPLAY_FLAGS_PIXDATA_NEGEDGE;
	dsi->vm.flags |= DISPLAY_FLAGS_PIXDATA_POSEDGE;
	dsi->vm.flags &= ~DISPLAY_FLAGS_DE_LOW;
	dsi->vm.flags |= DISPLAY_FLAGS_DE_HIGH;
	dsi->vm.flags &= ~DISPLAY_FLAGS_SYNC_POSEDGE;
	dsi->vm.flags |= DISPLAY_FLAGS_SYNC_NEGEDGE;

	dss_mgr_set_timings(&dsi->output, &dsi->vm);

	dsi->vm_timings = ctx.dsi_vm;

	mutex_unlock(&dsi->lock);

	वापस 0;
err:
	mutex_unlock(&dsi->lock);

	वापस r;
पूर्ण

/*
 * Return a hardcoded dispc channel क्रम the DSI output. This should work क्रम
 * current use हालs, but this can be later expanded to either resolve
 * the channel in some more dynamic manner, or get the channel as a user
 * parameter.
 */
अटल क्रमागत omap_channel dsi_get_dispc_channel(काष्ठा dsi_data *dsi)
अणु
	चयन (dsi->data->model) अणु
	हाल DSI_MODEL_OMAP3:
		वापस OMAP_DSS_CHANNEL_LCD;

	हाल DSI_MODEL_OMAP4:
		चयन (dsi->module_id) अणु
		हाल 0:
			वापस OMAP_DSS_CHANNEL_LCD;
		हाल 1:
			वापस OMAP_DSS_CHANNEL_LCD2;
		शेष:
			DSSWARN("unsupported module id\n");
			वापस OMAP_DSS_CHANNEL_LCD;
		पूर्ण

	हाल DSI_MODEL_OMAP5:
		चयन (dsi->module_id) अणु
		हाल 0:
			वापस OMAP_DSS_CHANNEL_LCD;
		हाल 1:
			वापस OMAP_DSS_CHANNEL_LCD3;
		शेष:
			DSSWARN("unsupported module id\n");
			वापस OMAP_DSS_CHANNEL_LCD;
		पूर्ण

	शेष:
		DSSWARN("unsupported DSS version\n");
		वापस OMAP_DSS_CHANNEL_LCD;
	पूर्ण
पूर्ण

अटल sमाप_प्रकार _omap_dsi_host_transfer(काष्ठा dsi_data *dsi, पूर्णांक vc,
				       स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा omap_dss_device *dssdev = &dsi->output;
	पूर्णांक r;

	dsi_vc_enable_hs(dssdev, vc, !(msg->flags & MIPI_DSI_MSG_USE_LPM));

	चयन (msg->type) अणु
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_0_PARAM:
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_1_PARAM:
	हाल MIPI_DSI_GENERIC_SHORT_WRITE_2_PARAM:
	हाल MIPI_DSI_GENERIC_LONG_WRITE:
	हाल MIPI_DSI_DCS_SHORT_WRITE:
	हाल MIPI_DSI_DCS_SHORT_WRITE_PARAM:
	हाल MIPI_DSI_DCS_LONG_WRITE:
	हाल MIPI_DSI_SET_MAXIMUM_RETURN_PACKET_SIZE:
	हाल MIPI_DSI_शून्य_PACKET:
		r = dsi_vc_ग_लिखो_common(dssdev, vc, msg);
		अवरोध;
	हाल MIPI_DSI_GENERIC_READ_REQUEST_0_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_1_PARAM:
	हाल MIPI_DSI_GENERIC_READ_REQUEST_2_PARAM:
		r = dsi_vc_generic_पढ़ो(dssdev, vc, msg);
		अवरोध;
	हाल MIPI_DSI_DCS_READ:
		r = dsi_vc_dcs_पढ़ो(dssdev, vc, msg);
		अवरोध;
	शेष:
		r = -EINVAL;
		अवरोध;
	पूर्ण

	अगर (r < 0)
		वापस r;

	अगर (msg->type == MIPI_DSI_DCS_SHORT_WRITE ||
	    msg->type == MIPI_DSI_DCS_SHORT_WRITE_PARAM) अणु
		u8 cmd = ((u8 *)msg->tx_buf)[0];

		अगर (cmd == MIPI_DCS_SET_TEAR_OFF)
			dsi_enable_te(dsi, false);
		अन्यथा अगर (cmd == MIPI_DCS_SET_TEAR_ON)
			dsi_enable_te(dsi, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार omap_dsi_host_transfer(काष्ठा mipi_dsi_host *host,
				      स्थिर काष्ठा mipi_dsi_msg *msg)
अणु
	काष्ठा dsi_data *dsi = host_to_omap(host);
	पूर्णांक r;
	पूर्णांक vc = VC_CMD;

	dsi_bus_lock(dsi);

	अगर (!dsi->अगरace_enabled) अणु
		dsi_enable(dsi);
		schedule_delayed_work(&dsi->dsi_disable_work, msecs_to_jअगरfies(2000));
	पूर्ण

	r = _omap_dsi_host_transfer(dsi, vc, msg);

	dsi_bus_unlock(dsi);

	वापस r;
पूर्ण

अटल पूर्णांक dsi_get_घड़ीs(काष्ठा dsi_data *dsi)
अणु
	काष्ठा clk *clk;

	clk = devm_clk_get(dsi->dev, "fck");
	अगर (IS_ERR(clk)) अणु
		DSSERR("can't get fck\n");
		वापस PTR_ERR(clk);
	पूर्ण

	dsi->dss_clk = clk;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा omapdss_dsi_ops dsi_ops = अणु
	.update = dsi_update_all,
	.is_video_mode = dsi_is_video_mode,
पूर्ण;

अटल irqवापस_t omap_dsi_te_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा dsi_data *dsi = (काष्ठा dsi_data *)dev_id;
	पूर्णांक old;

	old = atomic_cmpxchg(&dsi->करो_ext_te_update, 1, 0);
	अगर (old) अणु
		cancel_delayed_work(&dsi->te_समयout_work);
		_dsi_update(dsi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम omap_dsi_te_समयout_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dsi_data *dsi =
		container_of(work, काष्ठा dsi_data, te_समयout_work.work);
	पूर्णांक old;

	old = atomic_cmpxchg(&dsi->करो_ext_te_update, 1, 0);
	अगर (old) अणु
		dev_err(dsi->dev, "TE not received for 250ms!\n");
		_dsi_update(dsi);
	पूर्ण
पूर्ण

अटल पूर्णांक omap_dsi_रेजिस्टर_te_irq(काष्ठा dsi_data *dsi,
				    काष्ठा mipi_dsi_device *client)
अणु
	पूर्णांक err;
	पूर्णांक te_irq;

	dsi->te_gpio = gpiod_get(&client->dev, "te-gpios", GPIOD_IN);
	अगर (IS_ERR(dsi->te_gpio)) अणु
		err = PTR_ERR(dsi->te_gpio);

		अगर (err == -ENOENT) अणु
			dsi->te_gpio = शून्य;
			वापस 0;
		पूर्ण

		dev_err(dsi->dev, "Could not get TE gpio: %d\n", err);
		वापस err;
	पूर्ण

	te_irq = gpiod_to_irq(dsi->te_gpio);
	अगर (te_irq < 0) अणु
		gpiod_put(dsi->te_gpio);
		dsi->te_gpio = शून्य;
		वापस -EINVAL;
	पूर्ण

	dsi->te_irq = te_irq;

	irq_set_status_flags(te_irq, IRQ_NOAUTOEN);

	err = request_thपढ़ोed_irq(te_irq, शून्य, omap_dsi_te_irq_handler,
				   IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				   "TE", dsi);
	अगर (err) अणु
		dev_err(dsi->dev, "request irq failed with %d\n", err);
		gpiod_put(dsi->te_gpio);
		dsi->te_gpio = शून्य;
		वापस err;
	पूर्ण

	INIT_DEFERRABLE_WORK(&dsi->te_समयout_work,
			     omap_dsi_te_समयout_work_callback);

	dev_dbg(dsi->dev, "Using GPIO TE\n");

	वापस 0;
पूर्ण

अटल व्योम omap_dsi_unरेजिस्टर_te_irq(काष्ठा dsi_data *dsi)
अणु
	अगर (dsi->te_gpio) अणु
		मुक्त_irq(dsi->te_irq, dsi);
		cancel_delayed_work(&dsi->te_समयout_work);
		gpiod_put(dsi->te_gpio);
		dsi->te_gpio = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक omap_dsi_host_attach(काष्ठा mipi_dsi_host *host,
				काष्ठा mipi_dsi_device *client)
अणु
	काष्ठा dsi_data *dsi = host_to_omap(host);
	पूर्णांक r;

	अगर (dsi->dsidev) अणु
		DSSERR("dsi client already attached\n");
		वापस -EBUSY;
	पूर्ण

	अगर (mipi_dsi_pixel_क्रमmat_to_bpp(client->क्रमmat) < 0) अणु
		DSSERR("invalid pixel format\n");
		वापस -EINVAL;
	पूर्ण

	atomic_set(&dsi->करो_ext_te_update, 0);

	अगर (client->mode_flags & MIPI_DSI_MODE_VIDEO) अणु
		dsi->mode = OMAP_DSS_DSI_VIDEO_MODE;
	पूर्ण अन्यथा अणु
		r = omap_dsi_रेजिस्टर_te_irq(dsi, client);
		अगर (r)
			वापस r;

		dsi->mode = OMAP_DSS_DSI_CMD_MODE;
	पूर्ण

	dsi->dsidev = client;
	dsi->pix_fmt = client->क्रमmat;

	dsi->config.hs_clk_min = 150000000; // TODO: get from client?
	dsi->config.hs_clk_max = client->hs_rate;
	dsi->config.lp_clk_min = 7000000; // TODO: get from client?
	dsi->config.lp_clk_max = client->lp_rate;

	अगर (client->mode_flags & MIPI_DSI_MODE_VIDEO_BURST)
		dsi->config.trans_mode = OMAP_DSS_DSI_BURST_MODE;
	अन्यथा अगर (client->mode_flags & MIPI_DSI_MODE_VIDEO_SYNC_PULSE)
		dsi->config.trans_mode = OMAP_DSS_DSI_PULSE_MODE;
	अन्यथा
		dsi->config.trans_mode = OMAP_DSS_DSI_EVENT_MODE;

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dsi_host_detach(काष्ठा mipi_dsi_host *host,
				काष्ठा mipi_dsi_device *client)
अणु
	काष्ठा dsi_data *dsi = host_to_omap(host);

	अगर (WARN_ON(dsi->dsidev != client))
		वापस -EINVAL;

	cancel_delayed_work_sync(&dsi->dsi_disable_work);

	dsi_bus_lock(dsi);

	अगर (dsi->अगरace_enabled)
		dsi_disable(dsi);

	dsi_bus_unlock(dsi);

	omap_dsi_unरेजिस्टर_te_irq(dsi);
	dsi->dsidev = शून्य;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mipi_dsi_host_ops omap_dsi_host_ops = अणु
	.attach = omap_dsi_host_attach,
	.detach = omap_dsi_host_detach,
	.transfer = omap_dsi_host_transfer,
पूर्ण;

/* -----------------------------------------------------------------------------
 * PLL
 */

अटल स्थिर काष्ठा dss_pll_ops dsi_pll_ops = अणु
	.enable = dsi_pll_enable,
	.disable = dsi_pll_disable,
	.set_config = dss_pll_ग_लिखो_config_type_a,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_omap3_dsi_pll_hw = अणु
	.type = DSS_PLL_TYPE_A,

	.n_max = (1 << 7) - 1,
	.m_max = (1 << 11) - 1,
	.mX_max = (1 << 4) - 1,
	.fपूर्णांक_min = 750000,
	.fपूर्णांक_max = 2100000,
	.clkdco_low = 1000000000,
	.clkdco_max = 1800000000,

	.n_msb = 7,
	.n_lsb = 1,
	.m_msb = 18,
	.m_lsb = 8,

	.mX_msb[0] = 22,
	.mX_lsb[0] = 19,
	.mX_msb[1] = 26,
	.mX_lsb[1] = 23,

	.has_stopmode = true,
	.has_freqsel = true,
	.has_selfreqdco = false,
	.has_refsel = false,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_omap4_dsi_pll_hw = अणु
	.type = DSS_PLL_TYPE_A,

	.n_max = (1 << 8) - 1,
	.m_max = (1 << 12) - 1,
	.mX_max = (1 << 5) - 1,
	.fपूर्णांक_min = 500000,
	.fपूर्णांक_max = 2500000,
	.clkdco_low = 1000000000,
	.clkdco_max = 1800000000,

	.n_msb = 8,
	.n_lsb = 1,
	.m_msb = 20,
	.m_lsb = 9,

	.mX_msb[0] = 25,
	.mX_lsb[0] = 21,
	.mX_msb[1] = 30,
	.mX_lsb[1] = 26,

	.has_stopmode = true,
	.has_freqsel = false,
	.has_selfreqdco = false,
	.has_refsel = false,
पूर्ण;

अटल स्थिर काष्ठा dss_pll_hw dss_omap5_dsi_pll_hw = अणु
	.type = DSS_PLL_TYPE_A,

	.n_max = (1 << 8) - 1,
	.m_max = (1 << 12) - 1,
	.mX_max = (1 << 5) - 1,
	.fपूर्णांक_min = 150000,
	.fपूर्णांक_max = 52000000,
	.clkdco_low = 1000000000,
	.clkdco_max = 1800000000,

	.n_msb = 8,
	.n_lsb = 1,
	.m_msb = 20,
	.m_lsb = 9,

	.mX_msb[0] = 25,
	.mX_lsb[0] = 21,
	.mX_msb[1] = 30,
	.mX_lsb[1] = 26,

	.has_stopmode = true,
	.has_freqsel = false,
	.has_selfreqdco = true,
	.has_refsel = true,
पूर्ण;

अटल पूर्णांक dsi_init_pll_data(काष्ठा dss_device *dss, काष्ठा dsi_data *dsi)
अणु
	काष्ठा dss_pll *pll = &dsi->pll;
	काष्ठा clk *clk;
	पूर्णांक r;

	clk = devm_clk_get(dsi->dev, "sys_clk");
	अगर (IS_ERR(clk)) अणु
		DSSERR("can't get sys_clk\n");
		वापस PTR_ERR(clk);
	पूर्ण

	pll->name = dsi->module_id == 0 ? "dsi0" : "dsi1";
	pll->id = dsi->module_id == 0 ? DSS_PLL_DSI1 : DSS_PLL_DSI2;
	pll->clkin = clk;
	pll->base = dsi->pll_base;
	pll->hw = dsi->data->pll_hw;
	pll->ops = &dsi_pll_ops;

	r = dss_pll_रेजिस्टर(dss, pll);
	अगर (r)
		वापस r;

	वापस 0;
पूर्ण

/* -----------------------------------------------------------------------------
 * Component Bind & Unbind
 */

अटल पूर्णांक dsi_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा dss_device *dss = dss_get_device(master);
	काष्ठा dsi_data *dsi = dev_get_drvdata(dev);
	अक्षर name[10];
	u32 rev;
	पूर्णांक r;

	dsi->dss = dss;

	dsi_init_pll_data(dss, dsi);

	r = dsi_runसमय_get(dsi);
	अगर (r)
		वापस r;

	rev = dsi_पढ़ो_reg(dsi, DSI_REVISION);
	dev_dbg(dev, "OMAP DSI rev %d.%d\n",
	       FLD_GET(rev, 7, 4), FLD_GET(rev, 3, 0));

	dsi->line_buffer_size = dsi_get_line_buf_size(dsi);

	dsi_runसमय_put(dsi);

	snम_लिखो(name, माप(name), "dsi%u_regs", dsi->module_id + 1);
	dsi->debugfs.regs = dss_debugfs_create_file(dss, name,
						    dsi_dump_dsi_regs, dsi);
#अगर_घोषित CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
	snम_लिखो(name, माप(name), "dsi%u_irqs", dsi->module_id + 1);
	dsi->debugfs.irqs = dss_debugfs_create_file(dss, name,
						    dsi_dump_dsi_irqs, dsi);
#पूर्ण_अगर
	snम_लिखो(name, माप(name), "dsi%u_clks", dsi->module_id + 1);
	dsi->debugfs.clks = dss_debugfs_create_file(dss, name,
						    dsi_dump_dsi_घड़ीs, dsi);

	वापस 0;
पूर्ण

अटल व्योम dsi_unbind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा dsi_data *dsi = dev_get_drvdata(dev);

	dss_debugfs_हटाओ_file(dsi->debugfs.clks);
	dss_debugfs_हटाओ_file(dsi->debugfs.irqs);
	dss_debugfs_हटाओ_file(dsi->debugfs.regs);

	WARN_ON(dsi->scp_clk_refcount > 0);

	dss_pll_unरेजिस्टर(&dsi->pll);
पूर्ण

अटल स्थिर काष्ठा component_ops dsi_component_ops = अणु
	.bind	= dsi_bind,
	.unbind	= dsi_unbind,
पूर्ण;

/* -----------------------------------------------------------------------------
 * DRM Bridge Operations
 */

अटल पूर्णांक dsi_bridge_attach(काष्ठा drm_bridge *bridge,
			     क्रमागत drm_bridge_attach_flags flags)
अणु
	काष्ठा dsi_data *dsi = drm_bridge_to_dsi(bridge);

	अगर (!(flags & DRM_BRIDGE_ATTACH_NO_CONNECTOR))
		वापस -EINVAL;

	वापस drm_bridge_attach(bridge->encoder, dsi->output.next_bridge,
				 bridge, flags);
पूर्ण

अटल क्रमागत drm_mode_status
dsi_bridge_mode_valid(काष्ठा drm_bridge *bridge,
		      स्थिर काष्ठा drm_display_info *info,
		      स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा dsi_data *dsi = drm_bridge_to_dsi(bridge);
	काष्ठा dsi_clk_calc_ctx ctx;
	पूर्णांक r;

	mutex_lock(&dsi->lock);
	r = __dsi_calc_config(dsi, mode, &ctx);
	mutex_unlock(&dsi->lock);

	वापस r ? MODE_CLOCK_RANGE : MODE_OK;
पूर्ण

अटल व्योम dsi_bridge_mode_set(काष्ठा drm_bridge *bridge,
				स्थिर काष्ठा drm_display_mode *mode,
				स्थिर काष्ठा drm_display_mode *adjusted_mode)
अणु
	काष्ठा dsi_data *dsi = drm_bridge_to_dsi(bridge);

	dsi_set_config(&dsi->output, adjusted_mode);
पूर्ण

अटल व्योम dsi_bridge_enable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dsi_data *dsi = drm_bridge_to_dsi(bridge);
	काष्ठा omap_dss_device *dssdev = &dsi->output;

	cancel_delayed_work_sync(&dsi->dsi_disable_work);

	dsi_bus_lock(dsi);

	अगर (!dsi->अगरace_enabled)
		dsi_enable(dsi);

	dsi_enable_video_output(dssdev, VC_VIDEO);

	dsi->video_enabled = true;

	dsi_bus_unlock(dsi);
पूर्ण

अटल व्योम dsi_bridge_disable(काष्ठा drm_bridge *bridge)
अणु
	काष्ठा dsi_data *dsi = drm_bridge_to_dsi(bridge);
	काष्ठा omap_dss_device *dssdev = &dsi->output;

	cancel_delayed_work_sync(&dsi->dsi_disable_work);

	dsi_bus_lock(dsi);

	dsi->video_enabled = false;

	dsi_disable_video_output(dssdev, VC_VIDEO);

	dsi_disable(dsi);

	dsi_bus_unlock(dsi);
पूर्ण

अटल स्थिर काष्ठा drm_bridge_funcs dsi_bridge_funcs = अणु
	.attach = dsi_bridge_attach,
	.mode_valid = dsi_bridge_mode_valid,
	.mode_set = dsi_bridge_mode_set,
	.enable = dsi_bridge_enable,
	.disable = dsi_bridge_disable,
पूर्ण;

अटल व्योम dsi_bridge_init(काष्ठा dsi_data *dsi)
अणु
	dsi->bridge.funcs = &dsi_bridge_funcs;
	dsi->bridge.of_node = dsi->host.dev->of_node;
	dsi->bridge.type = DRM_MODE_CONNECTOR_DSI;

	drm_bridge_add(&dsi->bridge);
पूर्ण

अटल व्योम dsi_bridge_cleanup(काष्ठा dsi_data *dsi)
अणु
	drm_bridge_हटाओ(&dsi->bridge);
पूर्ण

/* -----------------------------------------------------------------------------
 * Probe & Remove, Suspend & Resume
 */

अटल पूर्णांक dsi_init_output(काष्ठा dsi_data *dsi)
अणु
	काष्ठा omap_dss_device *out = &dsi->output;
	पूर्णांक r;

	dsi_bridge_init(dsi);

	out->dev = dsi->dev;
	out->id = dsi->module_id == 0 ?
			OMAP_DSS_OUTPUT_DSI1 : OMAP_DSS_OUTPUT_DSI2;

	out->type = OMAP_DISPLAY_TYPE_DSI;
	out->name = dsi->module_id == 0 ? "dsi.0" : "dsi.1";
	out->dispc_channel = dsi_get_dispc_channel(dsi);
	out->dsi_ops = &dsi_ops;
	out->of_port = 0;
	out->bus_flags = DRM_BUS_FLAG_PIXDATA_DRIVE_POSEDGE
		       | DRM_BUS_FLAG_DE_HIGH
		       | DRM_BUS_FLAG_SYNC_DRIVE_NEGEDGE;

	r = omapdss_device_init_output(out, &dsi->bridge);
	अगर (r < 0) अणु
		dsi_bridge_cleanup(dsi);
		वापस r;
	पूर्ण

	omapdss_device_रेजिस्टर(out);

	वापस 0;
पूर्ण

अटल व्योम dsi_uninit_output(काष्ठा dsi_data *dsi)
अणु
	काष्ठा omap_dss_device *out = &dsi->output;

	omapdss_device_unरेजिस्टर(out);
	omapdss_device_cleanup_output(out);
	dsi_bridge_cleanup(dsi);
पूर्ण

अटल पूर्णांक dsi_probe_of(काष्ठा dsi_data *dsi)
अणु
	काष्ठा device_node *node = dsi->dev->of_node;
	काष्ठा property *prop;
	u32 lane_arr[10];
	पूर्णांक len, num_pins;
	पूर्णांक r;
	काष्ठा device_node *ep;

	ep = of_graph_get_endpoपूर्णांक_by_regs(node, 0, 0);
	अगर (!ep)
		वापस 0;

	prop = of_find_property(ep, "lanes", &len);
	अगर (prop == शून्य) अणु
		dev_err(dsi->dev, "failed to find lane data\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	num_pins = len / माप(u32);

	अगर (num_pins < 4 || num_pins % 2 != 0 ||
		num_pins > dsi->num_lanes_supported * 2) अणु
		dev_err(dsi->dev, "bad number of lanes\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	r = of_property_पढ़ो_u32_array(ep, "lanes", lane_arr, num_pins);
	अगर (r) अणु
		dev_err(dsi->dev, "failed to read lane data\n");
		जाओ err;
	पूर्ण

	r = dsi_configure_pins(dsi, num_pins, lane_arr);
	अगर (r) अणु
		dev_err(dsi->dev, "failed to configure pins");
		जाओ err;
	पूर्ण

	of_node_put(ep);

	वापस 0;

err:
	of_node_put(ep);
	वापस r;
पूर्ण

अटल स्थिर काष्ठा dsi_of_data dsi_of_data_omap34xx = अणु
	.model = DSI_MODEL_OMAP3,
	.pll_hw = &dss_omap3_dsi_pll_hw,
	.modules = (स्थिर काष्ठा dsi_module_id_data[]) अणु
		अणु .address = 0x4804fc00, .id = 0, पूर्ण,
		अणु पूर्ण,
	पूर्ण,
	.max_fck_freq = 173000000,
	.max_pll_lpभाग = (1 << 13) - 1,
	.quirks = DSI_QUIRK_REVERSE_TXCLKESC,
पूर्ण;

अटल स्थिर काष्ठा dsi_of_data dsi_of_data_omap36xx = अणु
	.model = DSI_MODEL_OMAP3,
	.pll_hw = &dss_omap3_dsi_pll_hw,
	.modules = (स्थिर काष्ठा dsi_module_id_data[]) अणु
		अणु .address = 0x4804fc00, .id = 0, पूर्ण,
		अणु पूर्ण,
	पूर्ण,
	.max_fck_freq = 173000000,
	.max_pll_lpभाग = (1 << 13) - 1,
	.quirks = DSI_QUIRK_PLL_PWR_BUG,
पूर्ण;

अटल स्थिर काष्ठा dsi_of_data dsi_of_data_omap4 = अणु
	.model = DSI_MODEL_OMAP4,
	.pll_hw = &dss_omap4_dsi_pll_hw,
	.modules = (स्थिर काष्ठा dsi_module_id_data[]) अणु
		अणु .address = 0x58004000, .id = 0, पूर्ण,
		अणु .address = 0x58005000, .id = 1, पूर्ण,
		अणु पूर्ण,
	पूर्ण,
	.max_fck_freq = 170000000,
	.max_pll_lpभाग = (1 << 13) - 1,
	.quirks = DSI_QUIRK_DCS_CMD_CONFIG_VC | DSI_QUIRK_VC_OCP_WIDTH
		| DSI_QUIRK_GNQ,
पूर्ण;

अटल स्थिर काष्ठा dsi_of_data dsi_of_data_omap5 = अणु
	.model = DSI_MODEL_OMAP5,
	.pll_hw = &dss_omap5_dsi_pll_hw,
	.modules = (स्थिर काष्ठा dsi_module_id_data[]) अणु
		अणु .address = 0x58004000, .id = 0, पूर्ण,
		अणु .address = 0x58009000, .id = 1, पूर्ण,
		अणु पूर्ण,
	पूर्ण,
	.max_fck_freq = 209250000,
	.max_pll_lpभाग = (1 << 13) - 1,
	.quirks = DSI_QUIRK_DCS_CMD_CONFIG_VC | DSI_QUIRK_VC_OCP_WIDTH
		| DSI_QUIRK_GNQ | DSI_QUIRK_PHY_DCC,
पूर्ण;

अटल स्थिर काष्ठा of_device_id dsi_of_match[] = अणु
	अणु .compatible = "ti,omap3-dsi", .data = &dsi_of_data_omap36xx, पूर्ण,
	अणु .compatible = "ti,omap4-dsi", .data = &dsi_of_data_omap4, पूर्ण,
	अणु .compatible = "ti,omap5-dsi", .data = &dsi_of_data_omap5, पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल स्थिर काष्ठा soc_device_attribute dsi_soc_devices[] = अणु
	अणु .machine = "OMAP3[45]*",	.data = &dsi_of_data_omap34xx पूर्ण,
	अणु .machine = "AM35*",		.data = &dsi_of_data_omap34xx पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;

अटल व्योम omap_dsi_disable_work_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dsi_data *dsi = container_of(work, काष्ठा dsi_data, dsi_disable_work.work);

	dsi_bus_lock(dsi);

	अगर (dsi->अगरace_enabled && !dsi->video_enabled)
		dsi_disable(dsi);

	dsi_bus_unlock(dsi);
पूर्ण

अटल पूर्णांक dsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा soc_device_attribute *soc;
	स्थिर काष्ठा dsi_module_id_data *d;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा dsi_data *dsi;
	काष्ठा resource *dsi_mem;
	काष्ठा resource *res;
	अचिन्हित पूर्णांक i;
	पूर्णांक r;

	dsi = devm_kzalloc(dev, माप(*dsi), GFP_KERNEL);
	अगर (!dsi)
		वापस -ENOMEM;

	dsi->dev = dev;
	dev_set_drvdata(dev, dsi);

	spin_lock_init(&dsi->irq_lock);
	spin_lock_init(&dsi->errors_lock);
	dsi->errors = 0;

#अगर_घोषित CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
	spin_lock_init(&dsi->irq_stats_lock);
	dsi->irq_stats.last_reset = jअगरfies;
#पूर्ण_अगर

	mutex_init(&dsi->lock);
	sema_init(&dsi->bus_lock, 1);

	INIT_DEFERRABLE_WORK(&dsi->frameकरोne_समयout_work,
			     dsi_frameकरोne_समयout_work_callback);

	INIT_DEFERRABLE_WORK(&dsi->dsi_disable_work, omap_dsi_disable_work_callback);

#अगर_घोषित DSI_CATCH_MISSING_TE
	समयr_setup(&dsi->te_समयr, dsi_te_समयout, 0);
#पूर्ण_अगर

	dsi_mem = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "proto");
	dsi->proto_base = devm_ioremap_resource(dev, dsi_mem);
	अगर (IS_ERR(dsi->proto_base))
		वापस PTR_ERR(dsi->proto_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "phy");
	dsi->phy_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dsi->phy_base))
		वापस PTR_ERR(dsi->phy_base);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "pll");
	dsi->pll_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(dsi->pll_base))
		वापस PTR_ERR(dsi->pll_base);

	dsi->irq = platक्रमm_get_irq(pdev, 0);
	अगर (dsi->irq < 0) अणु
		DSSERR("platform_get_irq failed\n");
		वापस -ENODEV;
	पूर्ण

	r = devm_request_irq(dev, dsi->irq, omap_dsi_irq_handler,
			     IRQF_SHARED, dev_name(dev), dsi);
	अगर (r < 0) अणु
		DSSERR("request_irq failed\n");
		वापस r;
	पूर्ण

	dsi->vdds_dsi_reg = devm_regulator_get(dev, "vdd");
	अगर (IS_ERR(dsi->vdds_dsi_reg)) अणु
		अगर (PTR_ERR(dsi->vdds_dsi_reg) != -EPROBE_DEFER)
			DSSERR("can't get DSI VDD regulator\n");
		वापस PTR_ERR(dsi->vdds_dsi_reg);
	पूर्ण

	soc = soc_device_match(dsi_soc_devices);
	अगर (soc)
		dsi->data = soc->data;
	अन्यथा
		dsi->data = of_match_node(dsi_of_match, dev->of_node)->data;

	d = dsi->data->modules;
	जबतक (d->address != 0 && d->address != dsi_mem->start)
		d++;

	अगर (d->address == 0) अणु
		DSSERR("unsupported DSI module\n");
		वापस -ENODEV;
	पूर्ण

	dsi->module_id = d->id;

	अगर (dsi->data->model == DSI_MODEL_OMAP4 ||
	    dsi->data->model == DSI_MODEL_OMAP5) अणु
		काष्ठा device_node *np;

		/*
		 * The OMAP4/5 display DT bindings करोn't reference the padconf
		 * syscon. Our only option to retrieve it is to find it by name.
		 */
		np = of_find_node_by_name(शून्य,
			dsi->data->model == DSI_MODEL_OMAP4 ?
			"omap4_padconf_global" : "omap5_padconf_global");
		अगर (!np)
			वापस -ENODEV;

		dsi->syscon = syscon_node_to_regmap(np);
		of_node_put(np);
	पूर्ण

	/* DSI VCs initialization */
	क्रम (i = 0; i < ARRAY_SIZE(dsi->vc); i++)
		dsi->vc[i].source = DSI_VC_SOURCE_L4;

	r = dsi_get_घड़ीs(dsi);
	अगर (r)
		वापस r;

	pm_runसमय_enable(dev);

	/* DSI on OMAP3 करोesn't have रेजिस्टर DSI_GNQ, set number
	 * of data to 3 by शेष */
	अगर (dsi->data->quirks & DSI_QUIRK_GNQ) अणु
		dsi_runसमय_get(dsi);
		/* NB_DATA_LANES */
		dsi->num_lanes_supported = 1 + REG_GET(dsi, DSI_GNQ, 11, 9);
		dsi_runसमय_put(dsi);
	पूर्ण अन्यथा अणु
		dsi->num_lanes_supported = 3;
	पूर्ण

	dsi->host.ops = &omap_dsi_host_ops;
	dsi->host.dev = &pdev->dev;

	r = dsi_probe_of(dsi);
	अगर (r) अणु
		DSSERR("Invalid DSI DT data\n");
		जाओ err_pm_disable;
	पूर्ण

	r = mipi_dsi_host_रेजिस्टर(&dsi->host);
	अगर (r < 0) अणु
		dev_err(&pdev->dev, "failed to register DSI host: %d\n", r);
		जाओ err_pm_disable;
	पूर्ण

	r = dsi_init_output(dsi);
	अगर (r)
		जाओ err_dsi_host_unरेजिस्टर;

	r = component_add(&pdev->dev, &dsi_component_ops);
	अगर (r)
		जाओ err_uninit_output;

	वापस 0;

err_uninit_output:
	dsi_uninit_output(dsi);
err_dsi_host_unरेजिस्टर:
	mipi_dsi_host_unरेजिस्टर(&dsi->host);
err_pm_disable:
	pm_runसमय_disable(dev);
	वापस r;
पूर्ण

अटल पूर्णांक dsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा dsi_data *dsi = platक्रमm_get_drvdata(pdev);

	component_del(&pdev->dev, &dsi_component_ops);

	dsi_uninit_output(dsi);

	mipi_dsi_host_unरेजिस्टर(&dsi->host);

	pm_runसमय_disable(&pdev->dev);

	अगर (dsi->vdds_dsi_reg != शून्य && dsi->vdds_dsi_enabled) अणु
		regulator_disable(dsi->vdds_dsi_reg);
		dsi->vdds_dsi_enabled = false;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा dsi_data *dsi = dev_get_drvdata(dev);

	dsi->is_enabled = false;
	/* ensure the irq handler sees the is_enabled value */
	smp_wmb();
	/* रुको क्रम current handler to finish beक्रमe turning the DSI off */
	synchronize_irq(dsi->irq);

	वापस 0;
पूर्ण

अटल पूर्णांक dsi_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा dsi_data *dsi = dev_get_drvdata(dev);

	dsi->is_enabled = true;
	/* ensure the irq handler sees the is_enabled value */
	smp_wmb();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops dsi_pm_ops = अणु
	.runसमय_suspend = dsi_runसमय_suspend,
	.runसमय_resume = dsi_runसमय_resume,
	SET_LATE_SYSTEM_SLEEP_PM_OPS(pm_runसमय_क्रमce_suspend, pm_runसमय_क्रमce_resume)
पूर्ण;

काष्ठा platक्रमm_driver omap_dsihw_driver = अणु
	.probe		= dsi_probe,
	.हटाओ		= dsi_हटाओ,
	.driver         = अणु
		.name   = "omapdss_dsi",
		.pm	= &dsi_pm_ops,
		.of_match_table = dsi_of_match,
		.suppress_bind_attrs = true,
	पूर्ण,
पूर्ण;
