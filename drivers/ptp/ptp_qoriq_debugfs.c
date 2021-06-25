<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright 2019 NXP
 */
#समावेश <linux/device.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/fsl/ptp_qoriq.h>

अटल पूर्णांक ptp_qoriq_fiper1_lpbk_get(व्योम *data, u64 *val)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = data;
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u32 ctrl;

	ctrl = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_ctrl);
	*val = ctrl & PP1L ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_qoriq_fiper1_lpbk_set(व्योम *data, u64 val)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = data;
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u32 ctrl;

	ctrl = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_ctrl);
	अगर (val == 0)
		ctrl &= ~PP1L;
	अन्यथा
		ctrl |= PP1L;

	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_ctrl, ctrl);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ptp_qoriq_fiper1_fops, ptp_qoriq_fiper1_lpbk_get,
			 ptp_qoriq_fiper1_lpbk_set, "%llu\n");

अटल पूर्णांक ptp_qoriq_fiper2_lpbk_get(व्योम *data, u64 *val)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = data;
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u32 ctrl;

	ctrl = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_ctrl);
	*val = ctrl & PP2L ? 1 : 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ptp_qoriq_fiper2_lpbk_set(व्योम *data, u64 val)
अणु
	काष्ठा ptp_qoriq *ptp_qoriq = data;
	काष्ठा ptp_qoriq_रेजिस्टरs *regs = &ptp_qoriq->regs;
	u32 ctrl;

	ctrl = ptp_qoriq->पढ़ो(&regs->ctrl_regs->पंचांगr_ctrl);
	अगर (val == 0)
		ctrl &= ~PP2L;
	अन्यथा
		ctrl |= PP2L;

	ptp_qoriq->ग_लिखो(&regs->ctrl_regs->पंचांगr_ctrl, ctrl);
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(ptp_qoriq_fiper2_fops, ptp_qoriq_fiper2_lpbk_get,
			 ptp_qoriq_fiper2_lpbk_set, "%llu\n");

व्योम ptp_qoriq_create_debugfs(काष्ठा ptp_qoriq *ptp_qoriq)
अणु
	काष्ठा dentry *root;

	root = debugfs_create_dir(dev_name(ptp_qoriq->dev), शून्य);
	अगर (IS_ERR(root))
		वापस;
	अगर (!root)
		जाओ err_root;

	ptp_qoriq->debugfs_root = root;

	अगर (!debugfs_create_file_unsafe("fiper1-loopback", 0600, root,
					ptp_qoriq, &ptp_qoriq_fiper1_fops))
		जाओ err_node;
	अगर (!debugfs_create_file_unsafe("fiper2-loopback", 0600, root,
					ptp_qoriq, &ptp_qoriq_fiper2_fops))
		जाओ err_node;
	वापस;

err_node:
	debugfs_हटाओ_recursive(root);
	ptp_qoriq->debugfs_root = शून्य;
err_root:
	dev_err(ptp_qoriq->dev, "failed to initialize debugfs\n");
पूर्ण

व्योम ptp_qoriq_हटाओ_debugfs(काष्ठा ptp_qoriq *ptp_qoriq)
अणु
	debugfs_हटाओ_recursive(ptp_qoriq->debugfs_root);
	ptp_qoriq->debugfs_root = शून्य;
पूर्ण
