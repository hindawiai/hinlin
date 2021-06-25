<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) Microsoft Corporation.
 *
 * Author:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *
 * This small module is a helper driver allows other drivers to
 * have a common पूर्णांकerface with the Hyper-V PCI frontend driver.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/hyperv.h>

काष्ठा hyperv_pci_block_ops hvpci_block_ops;
EXPORT_SYMBOL_GPL(hvpci_block_ops);

पूर्णांक hyperv_पढ़ो_cfg_blk(काष्ठा pci_dev *dev, व्योम *buf, अचिन्हित पूर्णांक buf_len,
			अचिन्हित पूर्णांक block_id, अचिन्हित पूर्णांक *bytes_वापसed)
अणु
	अगर (!hvpci_block_ops.पढ़ो_block)
		वापस -EOPNOTSUPP;

	वापस hvpci_block_ops.पढ़ो_block(dev, buf, buf_len, block_id,
					  bytes_वापसed);
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_पढ़ो_cfg_blk);

पूर्णांक hyperv_ग_लिखो_cfg_blk(काष्ठा pci_dev *dev, व्योम *buf, अचिन्हित पूर्णांक len,
			 अचिन्हित पूर्णांक block_id)
अणु
	अगर (!hvpci_block_ops.ग_लिखो_block)
		वापस -EOPNOTSUPP;

	वापस hvpci_block_ops.ग_लिखो_block(dev, buf, len, block_id);
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_ग_लिखो_cfg_blk);

पूर्णांक hyperv_reg_block_invalidate(काष्ठा pci_dev *dev, व्योम *context,
				व्योम (*block_invalidate)(व्योम *context,
							 u64 block_mask))
अणु
	अगर (!hvpci_block_ops.reg_blk_invalidate)
		वापस -EOPNOTSUPP;

	वापस hvpci_block_ops.reg_blk_invalidate(dev, context,
						  block_invalidate);
पूर्ण
EXPORT_SYMBOL_GPL(hyperv_reg_block_invalidate);

अटल व्योम __निकास निकास_hv_pci_पूर्णांकf(व्योम)
अणु
पूर्ण

अटल पूर्णांक __init init_hv_pci_पूर्णांकf(व्योम)
अणु
	वापस 0;
पूर्ण

module_init(init_hv_pci_पूर्णांकf);
module_निकास(निकास_hv_pci_पूर्णांकf);

MODULE_DESCRIPTION("Hyper-V PCI Interface");
MODULE_LICENSE("GPL v2");
