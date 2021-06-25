<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __QCOM_Q6V5_H__
#घोषणा __QCOM_Q6V5_H__

#समावेश <linux/kernel.h>
#समावेश <linux/completion.h>

काष्ठा rproc;
काष्ठा qcom_smem_state;
काष्ठा qcom_sysmon;

काष्ठा qcom_q6v5 अणु
	काष्ठा device *dev;
	काष्ठा rproc *rproc;

	काष्ठा qcom_smem_state *state;
	अचिन्हित stop_bit;

	पूर्णांक wकरोg_irq;
	पूर्णांक fatal_irq;
	पूर्णांक पढ़ोy_irq;
	पूर्णांक hanकरोver_irq;
	पूर्णांक stop_irq;

	bool hanकरोver_issued;

	काष्ठा completion start_करोne;
	काष्ठा completion stop_करोne;

	पूर्णांक crash_reason;

	bool running;

	व्योम (*hanकरोver)(काष्ठा qcom_q6v5 *q6v5);
पूर्ण;

पूर्णांक qcom_q6v5_init(काष्ठा qcom_q6v5 *q6v5, काष्ठा platक्रमm_device *pdev,
		   काष्ठा rproc *rproc, पूर्णांक crash_reason,
		   व्योम (*hanकरोver)(काष्ठा qcom_q6v5 *q6v5));

पूर्णांक qcom_q6v5_prepare(काष्ठा qcom_q6v5 *q6v5);
पूर्णांक qcom_q6v5_unprepare(काष्ठा qcom_q6v5 *q6v5);
पूर्णांक qcom_q6v5_request_stop(काष्ठा qcom_q6v5 *q6v5, काष्ठा qcom_sysmon *sysmon);
पूर्णांक qcom_q6v5_रुको_क्रम_start(काष्ठा qcom_q6v5 *q6v5, पूर्णांक समयout);
अचिन्हित दीर्घ qcom_q6v5_panic(काष्ठा qcom_q6v5 *q6v5);

#पूर्ण_अगर
