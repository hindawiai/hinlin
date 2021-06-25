<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more details.
 ***********************************************************************/
/*! \पile  cn23xx_device.h
 * \मrief Host Driver: Routines that perक्रमm CN23XX specअगरic operations.
 */

#अगर_अघोषित __CN23XX_PF_DEVICE_H__
#घोषणा __CN23XX_PF_DEVICE_H__

#समावेश "cn23xx_pf_regs.h"

/* Register address and configuration क्रम a CN23XX devices.
 * If device specअगरic changes need to be made then add a काष्ठा to include
 * device specअगरic fields as shown in the commented section
 */
काष्ठा octeon_cn23xx_pf अणु
	/** PCI पूर्णांकerrupt summary रेजिस्टर */
	u8 __iomem *पूर्णांकr_sum_reg64;

	/** PCI पूर्णांकerrupt enable रेजिस्टर */
	u8 __iomem *पूर्णांकr_enb_reg64;

	/** The PCI पूर्णांकerrupt mask used by पूर्णांकerrupt handler */
	u64 पूर्णांकr_mask64;

	काष्ठा octeon_config *conf;
पूर्ण;

#घोषणा CN23XX_SLI_DEF_BP			0x40

काष्ठा oct_vf_stats अणु
	u64 rx_packets;
	u64 tx_packets;
	u64 rx_bytes;
	u64 tx_bytes;
	u64 broadcast;
	u64 multicast;
पूर्ण;

पूर्णांक setup_cn23xx_octeon_pf_device(काष्ठा octeon_device *oct);

पूर्णांक validate_cn23xx_pf_config_info(काष्ठा octeon_device *oct,
				   काष्ठा octeon_config *conf23xx);

u32 cn23xx_pf_get_oq_ticks(काष्ठा octeon_device *oct, u32 समय_पूर्णांकr_in_us);

व्योम cn23xx_dump_pf_initialized_regs(काष्ठा octeon_device *oct);

पूर्णांक cn23xx_sriov_config(काष्ठा octeon_device *oct);

पूर्णांक cn23xx_fw_loaded(काष्ठा octeon_device *oct);

व्योम cn23xx_tell_vf_its_macaddr_changed(काष्ठा octeon_device *oct, पूर्णांक vfidx,
					u8 *mac);

पूर्णांक cn23xx_get_vf_stats(काष्ठा octeon_device *oct, पूर्णांक अगरidx,
			काष्ठा oct_vf_stats *stats);
#पूर्ण_अगर
