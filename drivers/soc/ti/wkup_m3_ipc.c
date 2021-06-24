<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AMx3 Wkup M3 IPC driver
 *
 * Copyright (C) 2015 Texas Instruments, Inc.
 *
 * Dave Gerlach <d-gerlach@ti.com>
 */

#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/omap-mailbox.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/remoteproc.h>
#समावेश <linux/suspend.h>
#समावेश <linux/wkup_m3_ipc.h>

#घोषणा AM33XX_CTRL_IPC_REG_COUNT	0x8
#घोषणा AM33XX_CTRL_IPC_REG_OFFSET(m)	(0x4 + 4 * (m))

/* AM33XX M3_TXEV_EOI रेजिस्टर */
#घोषणा AM33XX_CONTROL_M3_TXEV_EOI	0x00

#घोषणा AM33XX_M3_TXEV_ACK		(0x1 << 0)
#घोषणा AM33XX_M3_TXEV_ENABLE		(0x0 << 0)

#घोषणा IPC_CMD_DS0			0x4
#घोषणा IPC_CMD_STANDBY			0xc
#घोषणा IPC_CMD_IDLE			0x10
#घोषणा IPC_CMD_RESET			0xe
#घोषणा DS_IPC_DEFAULT			0xffffffff
#घोषणा M3_VERSION_UNKNOWN		0x0000ffff
#घोषणा M3_BASELINE_VERSION		0x191
#घोषणा M3_STATUS_RESP_MASK		(0xffff << 16)
#घोषणा M3_FW_VERSION_MASK		0xffff
#घोषणा M3_WAKE_SRC_MASK		0xff

#घोषणा M3_STATE_UNKNOWN		0
#घोषणा M3_STATE_RESET			1
#घोषणा M3_STATE_INITED			2
#घोषणा M3_STATE_MSG_FOR_LP		3
#घोषणा M3_STATE_MSG_FOR_RESET		4

अटल काष्ठा wkup_m3_ipc *m3_ipc_state;

अटल स्थिर काष्ठा wkup_m3_wakeup_src wakeups[] = अणु
	अणु.irq_nr = 16,	.src = "PRCM"पूर्ण,
	अणु.irq_nr = 35,	.src = "USB0_PHY"पूर्ण,
	अणु.irq_nr = 36,	.src = "USB1_PHY"पूर्ण,
	अणु.irq_nr = 40,	.src = "I2C0"पूर्ण,
	अणु.irq_nr = 41,	.src = "RTC Timer"पूर्ण,
	अणु.irq_nr = 42,	.src = "RTC Alarm"पूर्ण,
	अणु.irq_nr = 43,	.src = "Timer0"पूर्ण,
	अणु.irq_nr = 44,	.src = "Timer1"पूर्ण,
	अणु.irq_nr = 45,	.src = "UART"पूर्ण,
	अणु.irq_nr = 46,	.src = "GPIO0"पूर्ण,
	अणु.irq_nr = 48,	.src = "MPU_WAKE"पूर्ण,
	अणु.irq_nr = 49,	.src = "WDT0"पूर्ण,
	अणु.irq_nr = 50,	.src = "WDT1"पूर्ण,
	अणु.irq_nr = 51,	.src = "ADC_TSC"पूर्ण,
	अणु.irq_nr = 0,	.src = "Unknown"पूर्ण,
पूर्ण;

अटल व्योम am33xx_txev_eoi(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	ग_लिखोl(AM33XX_M3_TXEV_ACK,
	       m3_ipc->ipc_mem_base + AM33XX_CONTROL_M3_TXEV_EOI);
पूर्ण

अटल व्योम am33xx_txev_enable(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	ग_लिखोl(AM33XX_M3_TXEV_ENABLE,
	       m3_ipc->ipc_mem_base + AM33XX_CONTROL_M3_TXEV_EOI);
पूर्ण

अटल व्योम wkup_m3_ctrl_ipc_ग_लिखो(काष्ठा wkup_m3_ipc *m3_ipc,
				   u32 val, पूर्णांक ipc_reg_num)
अणु
	अगर (WARN(ipc_reg_num < 0 || ipc_reg_num > AM33XX_CTRL_IPC_REG_COUNT,
		 "ipc register operation out of range"))
		वापस;

	ग_लिखोl(val, m3_ipc->ipc_mem_base +
	       AM33XX_CTRL_IPC_REG_OFFSET(ipc_reg_num));
पूर्ण

अटल अचिन्हित पूर्णांक wkup_m3_ctrl_ipc_पढ़ो(काष्ठा wkup_m3_ipc *m3_ipc,
					  पूर्णांक ipc_reg_num)
अणु
	अगर (WARN(ipc_reg_num < 0 || ipc_reg_num > AM33XX_CTRL_IPC_REG_COUNT,
		 "ipc register operation out of range"))
		वापस 0;

	वापस पढ़ोl(m3_ipc->ipc_mem_base +
		     AM33XX_CTRL_IPC_REG_OFFSET(ipc_reg_num));
पूर्ण

अटल पूर्णांक wkup_m3_fw_version_पढ़ो(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	पूर्णांक val;

	val = wkup_m3_ctrl_ipc_पढ़ो(m3_ipc, 2);

	वापस val & M3_FW_VERSION_MASK;
पूर्ण

अटल irqवापस_t wkup_m3_txev_handler(पूर्णांक irq, व्योम *ipc_data)
अणु
	काष्ठा wkup_m3_ipc *m3_ipc = ipc_data;
	काष्ठा device *dev = m3_ipc->dev;
	पूर्णांक ver = 0;

	am33xx_txev_eoi(m3_ipc);

	चयन (m3_ipc->state) अणु
	हाल M3_STATE_RESET:
		ver = wkup_m3_fw_version_पढ़ो(m3_ipc);

		अगर (ver == M3_VERSION_UNKNOWN ||
		    ver < M3_BASELINE_VERSION) अणु
			dev_warn(dev, "CM3 Firmware Version %x not supported\n",
				 ver);
		पूर्ण अन्यथा अणु
			dev_info(dev, "CM3 Firmware Version = 0x%x\n", ver);
		पूर्ण

		m3_ipc->state = M3_STATE_INITED;
		complete(&m3_ipc->sync_complete);
		अवरोध;
	हाल M3_STATE_MSG_FOR_RESET:
		m3_ipc->state = M3_STATE_INITED;
		complete(&m3_ipc->sync_complete);
		अवरोध;
	हाल M3_STATE_MSG_FOR_LP:
		complete(&m3_ipc->sync_complete);
		अवरोध;
	हाल M3_STATE_UNKNOWN:
		dev_warn(dev, "Unknown CM3 State\n");
	पूर्ण

	am33xx_txev_enable(m3_ipc);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक wkup_m3_ping(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	काष्ठा device *dev = m3_ipc->dev;
	mbox_msg_t dummy_msg = 0;
	पूर्णांक ret;

	अगर (!m3_ipc->mbox) अणु
		dev_err(dev,
			"No IPC channel to communicate with wkup_m3!\n");
		वापस -EIO;
	पूर्ण

	/*
	 * Write a dummy message to the mailbox in order to trigger the RX
	 * पूर्णांकerrupt to alert the M3 that data is available in the IPC
	 * रेजिस्टरs. We must enable the IRQ here and disable it after in
	 * the RX callback to aव्योम multiple पूर्णांकerrupts being received
	 * by the CM3.
	 */
	ret = mbox_send_message(m3_ipc->mbox, &dummy_msg);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: mbox_send_message() failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	ret = रुको_क्रम_completion_समयout(&m3_ipc->sync_complete,
					  msecs_to_jअगरfies(500));
	अगर (!ret) अणु
		dev_err(dev, "MPU<->CM3 sync failure\n");
		m3_ipc->state = M3_STATE_UNKNOWN;
		वापस -EIO;
	पूर्ण

	mbox_client_txकरोne(m3_ipc->mbox, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक wkup_m3_ping_noirq(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	काष्ठा device *dev = m3_ipc->dev;
	mbox_msg_t dummy_msg = 0;
	पूर्णांक ret;

	अगर (!m3_ipc->mbox) अणु
		dev_err(dev,
			"No IPC channel to communicate with wkup_m3!\n");
		वापस -EIO;
	पूर्ण

	ret = mbox_send_message(m3_ipc->mbox, &dummy_msg);
	अगर (ret < 0) अणु
		dev_err(dev, "%s: mbox_send_message() failed: %d\n",
			__func__, ret);
		वापस ret;
	पूर्ण

	mbox_client_txकरोne(m3_ipc->mbox, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक wkup_m3_is_available(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	वापस ((m3_ipc->state != M3_STATE_RESET) &&
		(m3_ipc->state != M3_STATE_UNKNOWN));
पूर्ण

/* Public functions */
/**
 * wkup_m3_set_mem_type - Pass wkup_m3 which type of memory is in use
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 * @mem_type: memory type value पढ़ो directly from emअगर
 *
 * wkup_m3 must know what memory type is in use to properly suspend
 * and resume.
 */
अटल व्योम wkup_m3_set_mem_type(काष्ठा wkup_m3_ipc *m3_ipc, पूर्णांक mem_type)
अणु
	m3_ipc->mem_type = mem_type;
पूर्ण

/**
 * wkup_m3_set_resume_address - Pass wkup_m3 resume address
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 * @addr: Physical address from which resume code should execute
 */
अटल व्योम wkup_m3_set_resume_address(काष्ठा wkup_m3_ipc *m3_ipc, व्योम *addr)
अणु
	m3_ipc->resume_addr = (अचिन्हित दीर्घ)addr;
पूर्ण

/**
 * wkup_m3_request_pm_status - Retrieve wkup_m3 status code after suspend
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 *
 * Returns code representing the status of a low घातer mode transition.
 *	0 - Successful transition
 *	1 - Failure to transition to low घातer state
 */
अटल पूर्णांक wkup_m3_request_pm_status(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	अचिन्हित पूर्णांक i;
	पूर्णांक val;

	val = wkup_m3_ctrl_ipc_पढ़ो(m3_ipc, 1);

	i = M3_STATUS_RESP_MASK & val;
	i >>= __ffs(M3_STATUS_RESP_MASK);

	वापस i;
पूर्ण

/**
 * wkup_m3_prepare_low_घातer - Request preparation क्रम transition to
 *			       low घातer state
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 * @state: A kernel suspend state to enter, either MEM or STANDBY
 *
 * Returns 0 अगर preparation was successful, otherwise वापसs error code
 */
अटल पूर्णांक wkup_m3_prepare_low_घातer(काष्ठा wkup_m3_ipc *m3_ipc, पूर्णांक state)
अणु
	काष्ठा device *dev = m3_ipc->dev;
	पूर्णांक m3_घातer_state;
	पूर्णांक ret = 0;

	अगर (!wkup_m3_is_available(m3_ipc))
		वापस -ENODEV;

	चयन (state) अणु
	हाल WKUP_M3_DEEPSLEEP:
		m3_घातer_state = IPC_CMD_DS0;
		अवरोध;
	हाल WKUP_M3_STANDBY:
		m3_घातer_state = IPC_CMD_STANDBY;
		अवरोध;
	हाल WKUP_M3_IDLE:
		m3_घातer_state = IPC_CMD_IDLE;
		अवरोध;
	शेष:
		वापस 1;
	पूर्ण

	/* Program each required IPC रेजिस्टर then ग_लिखो शेषs to others */
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, m3_ipc->resume_addr, 0);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, m3_घातer_state, 1);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, m3_ipc->mem_type, 4);

	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, DS_IPC_DEFAULT, 2);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, DS_IPC_DEFAULT, 3);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, DS_IPC_DEFAULT, 5);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, DS_IPC_DEFAULT, 6);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, DS_IPC_DEFAULT, 7);

	m3_ipc->state = M3_STATE_MSG_FOR_LP;

	अगर (state == WKUP_M3_IDLE)
		ret = wkup_m3_ping_noirq(m3_ipc);
	अन्यथा
		ret = wkup_m3_ping(m3_ipc);

	अगर (ret) अणु
		dev_err(dev, "Unable to ping CM3\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wkup_m3_finish_low_घातer - Return m3 to reset state
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 *
 * Returns 0 अगर reset was successful, otherwise वापसs error code
 */
अटल पूर्णांक wkup_m3_finish_low_घातer(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	काष्ठा device *dev = m3_ipc->dev;
	पूर्णांक ret = 0;

	अगर (!wkup_m3_is_available(m3_ipc))
		वापस -ENODEV;

	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, IPC_CMD_RESET, 1);
	wkup_m3_ctrl_ipc_ग_लिखो(m3_ipc, DS_IPC_DEFAULT, 2);

	m3_ipc->state = M3_STATE_MSG_FOR_RESET;

	ret = wkup_m3_ping(m3_ipc);
	अगर (ret) अणु
		dev_err(dev, "Unable to ping CM3\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * wkup_m3_request_wake_src - Get the wakeup source info passed from wkup_m3
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 */
अटल स्थिर अक्षर *wkup_m3_request_wake_src(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	अचिन्हित पूर्णांक wakeup_src_idx;
	पूर्णांक j, val;

	val = wkup_m3_ctrl_ipc_पढ़ो(m3_ipc, 6);

	wakeup_src_idx = val & M3_WAKE_SRC_MASK;

	क्रम (j = 0; j < ARRAY_SIZE(wakeups) - 1; j++) अणु
		अगर (wakeups[j].irq_nr == wakeup_src_idx)
			वापस wakeups[j].src;
	पूर्ण
	वापस wakeups[j].src;
पूर्ण

/**
 * wkup_m3_set_rtc_only - Set the rtc_only flag
 * @m3_ipc: Poपूर्णांकer to wkup_m3_ipc context
 */
अटल व्योम wkup_m3_set_rtc_only(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	अगर (m3_ipc_state)
		m3_ipc_state->is_rtc_only = true;
पूर्ण

अटल काष्ठा wkup_m3_ipc_ops ipc_ops = अणु
	.set_mem_type = wkup_m3_set_mem_type,
	.set_resume_address = wkup_m3_set_resume_address,
	.prepare_low_घातer = wkup_m3_prepare_low_घातer,
	.finish_low_घातer = wkup_m3_finish_low_घातer,
	.request_pm_status = wkup_m3_request_pm_status,
	.request_wake_src = wkup_m3_request_wake_src,
	.set_rtc_only = wkup_m3_set_rtc_only,
पूर्ण;

/**
 * wkup_m3_ipc_get - Return handle to wkup_m3_ipc
 *
 * Returns शून्य अगर the wkup_m3 is not yet available, otherwise वापसs
 * poपूर्णांकer to wkup_m3_ipc काष्ठा.
 */
काष्ठा wkup_m3_ipc *wkup_m3_ipc_get(व्योम)
अणु
	अगर (m3_ipc_state)
		get_device(m3_ipc_state->dev);
	अन्यथा
		वापस शून्य;

	वापस m3_ipc_state;
पूर्ण
EXPORT_SYMBOL_GPL(wkup_m3_ipc_get);

/**
 * wkup_m3_ipc_put - Free handle to wkup_m3_ipc वापसed from wkup_m3_ipc_get
 * @m3_ipc: A poपूर्णांकer to wkup_m3_ipc काष्ठा वापसed by wkup_m3_ipc_get
 */
व्योम wkup_m3_ipc_put(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	अगर (m3_ipc_state)
		put_device(m3_ipc_state->dev);
पूर्ण
EXPORT_SYMBOL_GPL(wkup_m3_ipc_put);

अटल व्योम wkup_m3_rproc_boot_thपढ़ो(काष्ठा wkup_m3_ipc *m3_ipc)
अणु
	काष्ठा device *dev = m3_ipc->dev;
	पूर्णांक ret;

	init_completion(&m3_ipc->sync_complete);

	ret = rproc_boot(m3_ipc->rproc);
	अगर (ret)
		dev_err(dev, "rproc_boot failed\n");
	अन्यथा
		m3_ipc_state = m3_ipc;

	करो_निकास(0);
पूर्ण

अटल पूर्णांक wkup_m3_ipc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	पूर्णांक irq, ret;
	phandle rproc_phandle;
	काष्ठा rproc *m3_rproc;
	काष्ठा resource *res;
	काष्ठा task_काष्ठा *task;
	काष्ठा wkup_m3_ipc *m3_ipc;

	m3_ipc = devm_kzalloc(dev, माप(*m3_ipc), GFP_KERNEL);
	अगर (!m3_ipc)
		वापस -ENOMEM;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	m3_ipc->ipc_mem_base = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(m3_ipc->ipc_mem_base)) अणु
		dev_err(dev, "could not ioremap ipc_mem\n");
		वापस PTR_ERR(m3_ipc->ipc_mem_base);
	पूर्ण

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (!irq) अणु
		dev_err(&pdev->dev, "no irq resource\n");
		वापस -ENXIO;
	पूर्ण

	ret = devm_request_irq(dev, irq, wkup_m3_txev_handler,
			       0, "wkup_m3_txev", m3_ipc);
	अगर (ret) अणु
		dev_err(dev, "request_irq failed\n");
		वापस ret;
	पूर्ण

	m3_ipc->mbox_client.dev = dev;
	m3_ipc->mbox_client.tx_करोne = शून्य;
	m3_ipc->mbox_client.tx_prepare = शून्य;
	m3_ipc->mbox_client.rx_callback = शून्य;
	m3_ipc->mbox_client.tx_block = false;
	m3_ipc->mbox_client.knows_txकरोne = false;

	m3_ipc->mbox = mbox_request_channel(&m3_ipc->mbox_client, 0);

	अगर (IS_ERR(m3_ipc->mbox)) अणु
		dev_err(dev, "IPC Request for A8->M3 Channel failed! %ld\n",
			PTR_ERR(m3_ipc->mbox));
		वापस PTR_ERR(m3_ipc->mbox);
	पूर्ण

	अगर (of_property_पढ़ो_u32(dev->of_node, "ti,rproc", &rproc_phandle)) अणु
		dev_err(&pdev->dev, "could not get rproc phandle\n");
		ret = -ENODEV;
		जाओ err_मुक्त_mbox;
	पूर्ण

	m3_rproc = rproc_get_by_phandle(rproc_phandle);
	अगर (!m3_rproc) अणु
		dev_err(&pdev->dev, "could not get rproc handle\n");
		ret = -EPROBE_DEFER;
		जाओ err_मुक्त_mbox;
	पूर्ण

	m3_ipc->rproc = m3_rproc;
	m3_ipc->dev = dev;
	m3_ipc->state = M3_STATE_RESET;

	m3_ipc->ops = &ipc_ops;

	/*
	 * Wait क्रम firmware loading completion in a thपढ़ो so we
	 * can boot the wkup_m3 as soon as it's पढ़ोy without holding
	 * up kernel boot
	 */
	task = kthपढ़ो_run((व्योम *)wkup_m3_rproc_boot_thपढ़ो, m3_ipc,
			   "wkup_m3_rproc_loader");

	अगर (IS_ERR(task)) अणु
		dev_err(dev, "can't create rproc_boot thread\n");
		ret = PTR_ERR(task);
		जाओ err_put_rproc;
	पूर्ण

	वापस 0;

err_put_rproc:
	rproc_put(m3_rproc);
err_मुक्त_mbox:
	mbox_मुक्त_channel(m3_ipc->mbox);
	वापस ret;
पूर्ण

अटल पूर्णांक wkup_m3_ipc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	mbox_मुक्त_channel(m3_ipc_state->mbox);

	rproc_shutकरोwn(m3_ipc_state->rproc);
	rproc_put(m3_ipc_state->rproc);

	m3_ipc_state = शून्य;

	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wkup_m3_ipc_suspend(काष्ठा device *dev)
अणु
	/*
	 * Nothing needs to be करोne on suspend even with rtc_only flag set
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused wkup_m3_ipc_resume(काष्ठा device *dev)
अणु
	अगर (m3_ipc_state->is_rtc_only) अणु
		rproc_shutकरोwn(m3_ipc_state->rproc);
		rproc_boot(m3_ipc_state->rproc);
	पूर्ण

	m3_ipc_state->is_rtc_only = false;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops wkup_m3_ipc_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(wkup_m3_ipc_suspend, wkup_m3_ipc_resume)
पूर्ण;

अटल स्थिर काष्ठा of_device_id wkup_m3_ipc_of_match[] = अणु
	अणु .compatible = "ti,am3352-wkup-m3-ipc", पूर्ण,
	अणु .compatible = "ti,am4372-wkup-m3-ipc", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, wkup_m3_ipc_of_match);

अटल काष्ठा platक्रमm_driver wkup_m3_ipc_driver = अणु
	.probe = wkup_m3_ipc_probe,
	.हटाओ = wkup_m3_ipc_हटाओ,
	.driver = अणु
		.name = "wkup_m3_ipc",
		.of_match_table = wkup_m3_ipc_of_match,
		.pm = &wkup_m3_ipc_pm_ops,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wkup_m3_ipc_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("wkup m3 remote processor ipc driver");
MODULE_AUTHOR("Dave Gerlach <d-gerlach@ti.com>");
