<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Qualcomm Peripheral Image Loader क्रम Q6V5
 *
 * Copyright (C) 2016-2018 Linaro Ltd.
 * Copyright (C) 2014 Sony Mobile Communications AB
 * Copyright (c) 2012-2013, The Linux Foundation. All rights reserved.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/soc/qcom/sस्मृति.स>
#समावेश <linux/soc/qcom/smem_state.h>
#समावेश <linux/remoteproc.h>
#समावेश "qcom_common.h"
#समावेश "qcom_q6v5.h"

#घोषणा Q6V5_PANIC_DELAY_MS	200

/**
 * qcom_q6v5_prepare() - reinitialize the qcom_q6v5 context beक्रमe start
 * @q6v5:	reference to qcom_q6v5 context to be reinitialized
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक qcom_q6v5_prepare(काष्ठा qcom_q6v5 *q6v5)
अणु
	reinit_completion(&q6v5->start_करोne);
	reinit_completion(&q6v5->stop_करोne);

	q6v5->running = true;
	q6v5->hanकरोver_issued = false;

	enable_irq(q6v5->hanकरोver_irq);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_q6v5_prepare);

/**
 * qcom_q6v5_unprepare() - unprepare the qcom_q6v5 context after stop
 * @q6v5:	reference to qcom_q6v5 context to be unprepared
 *
 * Return: 0 on success, 1 अगर hanकरोver hasn't yet been called
 */
पूर्णांक qcom_q6v5_unprepare(काष्ठा qcom_q6v5 *q6v5)
अणु
	disable_irq(q6v5->hanकरोver_irq);

	वापस !q6v5->hanकरोver_issued;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_q6v5_unprepare);

अटल irqवापस_t q6v5_wकरोg_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_q6v5 *q6v5 = data;
	माप_प्रकार len;
	अक्षर *msg;

	/* Someबार the stop triggers a watchकरोg rather than a stop-ack */
	अगर (!q6v5->running) अणु
		complete(&q6v5->stop_करोne);
		वापस IRQ_HANDLED;
	पूर्ण

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, q6v5->crash_reason, &len);
	अगर (!IS_ERR(msg) && len > 0 && msg[0])
		dev_err(q6v5->dev, "watchdog received: %s\n", msg);
	अन्यथा
		dev_err(q6v5->dev, "watchdog without message\n");

	rproc_report_crash(q6v5->rproc, RPROC_WATCHDOG);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t q6v5_fatal_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_q6v5 *q6v5 = data;
	माप_प्रकार len;
	अक्षर *msg;

	msg = qcom_smem_get(QCOM_SMEM_HOST_ANY, q6v5->crash_reason, &len);
	अगर (!IS_ERR(msg) && len > 0 && msg[0])
		dev_err(q6v5->dev, "fatal error received: %s\n", msg);
	अन्यथा
		dev_err(q6v5->dev, "fatal error without message\n");

	q6v5->running = false;
	rproc_report_crash(q6v5->rproc, RPROC_FATAL_ERROR);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t q6v5_पढ़ोy_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_q6v5 *q6v5 = data;

	complete(&q6v5->start_करोne);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * qcom_q6v5_रुको_क्रम_start() - रुको क्रम remote processor start संकेत
 * @q6v5:	reference to qcom_q6v5 context
 * @समयout:	समयout to रुको क्रम the event, in jअगरfies
 *
 * qcom_q6v5_unprepare() should not be called when this function fails.
 *
 * Return: 0 on success, -ETIMEDOUT on समयout
 */
पूर्णांक qcom_q6v5_रुको_क्रम_start(काष्ठा qcom_q6v5 *q6v5, पूर्णांक समयout)
अणु
	पूर्णांक ret;

	ret = रुको_क्रम_completion_समयout(&q6v5->start_करोne, समयout);
	अगर (!ret)
		disable_irq(q6v5->hanकरोver_irq);

	वापस !ret ? -ETIMEDOUT : 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_q6v5_रुको_क्रम_start);

अटल irqवापस_t q6v5_hanकरोver_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_q6v5 *q6v5 = data;

	अगर (q6v5->hanकरोver)
		q6v5->hanकरोver(q6v5);

	q6v5->hanकरोver_issued = true;

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t q6v5_stop_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा qcom_q6v5 *q6v5 = data;

	complete(&q6v5->stop_करोne);

	वापस IRQ_HANDLED;
पूर्ण

/**
 * qcom_q6v5_request_stop() - request the remote processor to stop
 * @q6v5:	reference to qcom_q6v5 context
 * @sysmon:	reference to the remote's sysmon instance, or शून्य
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक qcom_q6v5_request_stop(काष्ठा qcom_q6v5 *q6v5, काष्ठा qcom_sysmon *sysmon)
अणु
	पूर्णांक ret;

	q6v5->running = false;

	/* Don't perक्रमm SMP2P dance अगर sysmon alपढ़ोy shut करोwn the remote */
	अगर (qcom_sysmon_shutकरोwn_acked(sysmon))
		वापस 0;

	qcom_smem_state_update_bits(q6v5->state,
				    BIT(q6v5->stop_bit), BIT(q6v5->stop_bit));

	ret = रुको_क्रम_completion_समयout(&q6v5->stop_करोne, 5 * HZ);

	qcom_smem_state_update_bits(q6v5->state, BIT(q6v5->stop_bit), 0);

	वापस ret == 0 ? -ETIMEDOUT : 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_q6v5_request_stop);

/**
 * qcom_q6v5_panic() - panic handler to invoke a stop on the remote
 * @q6v5:	reference to qcom_q6v5 context
 *
 * Set the stop bit and sleep in order to allow the remote processor to flush
 * its caches etc क्रम post mortem debugging.
 *
 * Return: 200ms
 */
अचिन्हित दीर्घ qcom_q6v5_panic(काष्ठा qcom_q6v5 *q6v5)
अणु
	qcom_smem_state_update_bits(q6v5->state,
				    BIT(q6v5->stop_bit), BIT(q6v5->stop_bit));

	वापस Q6V5_PANIC_DELAY_MS;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_q6v5_panic);

/**
 * qcom_q6v5_init() - initializer of the q6v5 common काष्ठा
 * @q6v5:	handle to be initialized
 * @pdev:	platक्रमm_device reference क्रम acquiring resources
 * @rproc:	associated remoteproc instance
 * @crash_reason: SMEM id क्रम crash reason string, or 0 अगर none
 * @hanकरोver:	function to be called when proxy resources should be released
 *
 * Return: 0 on success, negative त्रुटि_सं on failure
 */
पूर्णांक qcom_q6v5_init(काष्ठा qcom_q6v5 *q6v5, काष्ठा platक्रमm_device *pdev,
		   काष्ठा rproc *rproc, पूर्णांक crash_reason,
		   व्योम (*hanकरोver)(काष्ठा qcom_q6v5 *q6v5))
अणु
	पूर्णांक ret;

	q6v5->rproc = rproc;
	q6v5->dev = &pdev->dev;
	q6v5->crash_reason = crash_reason;
	q6v5->hanकरोver = hanकरोver;

	init_completion(&q6v5->start_करोne);
	init_completion(&q6v5->stop_करोne);

	q6v5->wकरोg_irq = platक्रमm_get_irq_byname(pdev, "wdog");
	अगर (q6v5->wकरोg_irq < 0)
		वापस q6v5->wकरोg_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, q6v5->wकरोg_irq,
					शून्य, q6v5_wकरोg_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"q6v5 wdog", q6v5);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to acquire wdog IRQ\n");
		वापस ret;
	पूर्ण

	q6v5->fatal_irq = platक्रमm_get_irq_byname(pdev, "fatal");
	अगर (q6v5->fatal_irq < 0)
		वापस q6v5->fatal_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, q6v5->fatal_irq,
					शून्य, q6v5_fatal_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"q6v5 fatal", q6v5);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to acquire fatal IRQ\n");
		वापस ret;
	पूर्ण

	q6v5->पढ़ोy_irq = platक्रमm_get_irq_byname(pdev, "ready");
	अगर (q6v5->पढ़ोy_irq < 0)
		वापस q6v5->पढ़ोy_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, q6v5->पढ़ोy_irq,
					शून्य, q6v5_पढ़ोy_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"q6v5 ready", q6v5);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to acquire ready IRQ\n");
		वापस ret;
	पूर्ण

	q6v5->hanकरोver_irq = platक्रमm_get_irq_byname(pdev, "handover");
	अगर (q6v5->hanकरोver_irq < 0)
		वापस q6v5->hanकरोver_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, q6v5->hanकरोver_irq,
					शून्य, q6v5_hanकरोver_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"q6v5 handover", q6v5);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to acquire handover IRQ\n");
		वापस ret;
	पूर्ण
	disable_irq(q6v5->hanकरोver_irq);

	q6v5->stop_irq = platक्रमm_get_irq_byname(pdev, "stop-ack");
	अगर (q6v5->stop_irq < 0)
		वापस q6v5->stop_irq;

	ret = devm_request_thपढ़ोed_irq(&pdev->dev, q6v5->stop_irq,
					शून्य, q6v5_stop_पूर्णांकerrupt,
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					"q6v5 stop", q6v5);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to acquire stop-ack IRQ\n");
		वापस ret;
	पूर्ण

	q6v5->state = qcom_smem_state_get(&pdev->dev, "stop", &q6v5->stop_bit);
	अगर (IS_ERR(q6v5->state)) अणु
		dev_err(&pdev->dev, "failed to acquire stop state\n");
		वापस PTR_ERR(q6v5->state);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(qcom_q6v5_init);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Qualcomm Peripheral Image Loader for Q6V5");
