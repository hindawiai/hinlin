<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * NHI specअगरic operations
 *
 * Copyright (C) 2019, Intel Corporation
 * Author: Mika Westerberg <mika.westerberg@linux.पूर्णांकel.com>
 */

#समावेश <linux/delay.h>
#समावेश <linux/suspend.h>

#समावेश "nhi.h"
#समावेश "nhi_regs.h"
#समावेश "tb.h"

/* Ice Lake specअगरic NHI operations */

#घोषणा ICL_LC_MAILBOX_TIMEOUT	500 /* ms */

अटल पूर्णांक check_क्रम_device(काष्ठा device *dev, व्योम *data)
अणु
	वापस tb_is_चयन(dev);
पूर्ण

अटल bool icl_nhi_is_device_connected(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा tb *tb = pci_get_drvdata(nhi->pdev);
	पूर्णांक ret;

	ret = device_क्रम_each_child(&tb->root_चयन->dev, शून्य,
				    check_क्रम_device);
	वापस ret > 0;
पूर्ण

अटल पूर्णांक icl_nhi_क्रमce_घातer(काष्ठा tb_nhi *nhi, bool घातer)
अणु
	u32 vs_cap;

	/*
	 * The Thunderbolt host controller is present always in Ice Lake
	 * but the firmware may not be loaded and running (depending
	 * whether there is device connected and so on). Each समय the
	 * controller is used we need to "Force Power" it first and रुको
	 * क्रम the firmware to indicate it is up and running. This "Force
	 * Power" is really not about actually घातering on/off the
	 * controller so it is accessible even अगर "Force Power" is off.
	 *
	 * The actual घातer management happens inside shared ACPI घातer
	 * resources using standard ACPI methods.
	 */
	pci_पढ़ो_config_dword(nhi->pdev, VS_CAP_22, &vs_cap);
	अगर (घातer) अणु
		vs_cap &= ~VS_CAP_22_DMA_DELAY_MASK;
		vs_cap |= 0x22 << VS_CAP_22_DMA_DELAY_SHIFT;
		vs_cap |= VS_CAP_22_FORCE_POWER;
	पूर्ण अन्यथा अणु
		vs_cap &= ~VS_CAP_22_FORCE_POWER;
	पूर्ण
	pci_ग_लिखो_config_dword(nhi->pdev, VS_CAP_22, vs_cap);

	अगर (घातer) अणु
		अचिन्हित पूर्णांक retries = 350;
		u32 val;

		/* Wait until the firmware tells it is up and running */
		करो अणु
			pci_पढ़ो_config_dword(nhi->pdev, VS_CAP_9, &val);
			अगर (val & VS_CAP_9_FW_READY)
				वापस 0;
			usleep_range(3000, 3100);
		पूर्ण जबतक (--retries);

		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम icl_nhi_lc_mailbox_cmd(काष्ठा tb_nhi *nhi, क्रमागत icl_lc_mailbox_cmd cmd)
अणु
	u32 data;

	data = (cmd << VS_CAP_19_CMD_SHIFT) & VS_CAP_19_CMD_MASK;
	pci_ग_लिखो_config_dword(nhi->pdev, VS_CAP_19, data | VS_CAP_19_VALID);
पूर्ण

अटल पूर्णांक icl_nhi_lc_mailbox_cmd_complete(काष्ठा tb_nhi *nhi, पूर्णांक समयout)
अणु
	अचिन्हित दीर्घ end;
	u32 data;

	अगर (!समयout)
		जाओ clear;

	end = jअगरfies + msecs_to_jअगरfies(समयout);
	करो अणु
		pci_पढ़ो_config_dword(nhi->pdev, VS_CAP_18, &data);
		अगर (data & VS_CAP_18_DONE)
			जाओ clear;
		usleep_range(1000, 1100);
	पूर्ण जबतक (समय_beक्रमe(jअगरfies, end));

	वापस -ETIMEDOUT;

clear:
	/* Clear the valid bit */
	pci_ग_लिखो_config_dword(nhi->pdev, VS_CAP_19, 0);
	वापस 0;
पूर्ण

अटल व्योम icl_nhi_set_ltr(काष्ठा tb_nhi *nhi)
अणु
	u32 max_ltr, ltr;

	pci_पढ़ो_config_dword(nhi->pdev, VS_CAP_16, &max_ltr);
	max_ltr &= 0xffff;
	/* Program the same value क्रम both snoop and no-snoop */
	ltr = max_ltr << 16 | max_ltr;
	pci_ग_लिखो_config_dword(nhi->pdev, VS_CAP_15, ltr);
पूर्ण

अटल पूर्णांक icl_nhi_suspend(काष्ठा tb_nhi *nhi)
अणु
	काष्ठा tb *tb = pci_get_drvdata(nhi->pdev);
	पूर्णांक ret;

	अगर (icl_nhi_is_device_connected(nhi))
		वापस 0;

	अगर (tb_चयन_is_icm(tb->root_चयन)) अणु
		/*
		 * If there is no device connected we need to perक्रमm
		 * both: a handshake through LC mailbox and क्रमce घातer
		 * करोwn beक्रमe entering D3.
		 */
		icl_nhi_lc_mailbox_cmd(nhi, ICL_LC_PREPARE_FOR_RESET);
		ret = icl_nhi_lc_mailbox_cmd_complete(nhi, ICL_LC_MAILBOX_TIMEOUT);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस icl_nhi_क्रमce_घातer(nhi, false);
पूर्ण

अटल पूर्णांक icl_nhi_suspend_noirq(काष्ठा tb_nhi *nhi, bool wakeup)
अणु
	काष्ठा tb *tb = pci_get_drvdata(nhi->pdev);
	क्रमागत icl_lc_mailbox_cmd cmd;

	अगर (!pm_suspend_via_firmware())
		वापस icl_nhi_suspend(nhi);

	अगर (!tb_चयन_is_icm(tb->root_चयन))
		वापस 0;

	cmd = wakeup ? ICL_LC_GO2SX : ICL_LC_GO2SX_NO_WAKE;
	icl_nhi_lc_mailbox_cmd(nhi, cmd);
	वापस icl_nhi_lc_mailbox_cmd_complete(nhi, ICL_LC_MAILBOX_TIMEOUT);
पूर्ण

अटल पूर्णांक icl_nhi_resume(काष्ठा tb_nhi *nhi)
अणु
	पूर्णांक ret;

	ret = icl_nhi_क्रमce_घातer(nhi, true);
	अगर (ret)
		वापस ret;

	icl_nhi_set_ltr(nhi);
	वापस 0;
पूर्ण

अटल व्योम icl_nhi_shutकरोwn(काष्ठा tb_nhi *nhi)
अणु
	icl_nhi_क्रमce_घातer(nhi, false);
पूर्ण

स्थिर काष्ठा tb_nhi_ops icl_nhi_ops = अणु
	.init = icl_nhi_resume,
	.suspend_noirq = icl_nhi_suspend_noirq,
	.resume_noirq = icl_nhi_resume,
	.runसमय_suspend = icl_nhi_suspend,
	.runसमय_resume = icl_nhi_resume,
	.shutकरोwn = icl_nhi_shutकरोwn,
पूर्ण;
