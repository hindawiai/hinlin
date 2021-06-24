<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2005-2014 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_paging_h__
#घोषणा __iwl_fw_api_paging_h__

#घोषणा NUM_OF_FW_PAGING_BLOCKS	33 /* 32 क्रम data and 1 block क्रम CSS */

/**
 * काष्ठा iwl_fw_paging_cmd - paging layout
 *
 * Send to FW the paging layout in the driver.
 *
 * @flags: various flags क्रम the command
 * @block_size: the block size in घातers of 2
 * @block_num: number of blocks specअगरied in the command.
 * @device_phy_addr: भव addresses from device side
 */
काष्ठा iwl_fw_paging_cmd अणु
	__le32 flags;
	__le32 block_size;
	__le32 block_num;
	__le32 device_phy_addr[NUM_OF_FW_PAGING_BLOCKS];
पूर्ण __packed; /* FW_PAGING_BLOCK_CMD_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_paging_h__ */
