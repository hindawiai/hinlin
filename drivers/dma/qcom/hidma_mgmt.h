<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Qualcomm Technologies HIDMA Management common header
 *
 * Copyright (c) 2015, The Linux Foundation. All rights reserved.
 */

काष्ठा hidma_mgmt_dev अणु
	u8 hw_version_major;
	u8 hw_version_minor;

	u32 max_wr_xactions;
	u32 max_rd_xactions;
	u32 max_ग_लिखो_request;
	u32 max_पढ़ो_request;
	u32 dma_channels;
	u32 chreset_समयout_cycles;
	u32 hw_version;
	u32 *priority;
	u32 *weight;

	/* Hardware device स्थिरants */
	व्योम __iomem *virtaddr;
	resource_माप_प्रकार addrsize;

	काष्ठा kobject **chroots;
	काष्ठा platक्रमm_device *pdev;
पूर्ण;

पूर्णांक hidma_mgmt_init_sys(काष्ठा hidma_mgmt_dev *dev);
पूर्णांक hidma_mgmt_setup(काष्ठा hidma_mgmt_dev *mgmtdev);
