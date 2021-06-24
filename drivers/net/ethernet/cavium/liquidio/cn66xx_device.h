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
/*! \पile  cn66xx_device.h
 *  \मrief Host Driver: Routines that perक्रमm CN66XX specअगरic operations.
 */

#अगर_अघोषित __CN66XX_DEVICE_H__
#घोषणा  __CN66XX_DEVICE_H__

/* Register address and configuration क्रम a CN6XXX devices.
 * If device specअगरic changes need to be made then add a काष्ठा to include
 * device specअगरic fields as shown in the commented section
 */
काष्ठा octeon_cn6xxx अणु
	/** PCI पूर्णांकerrupt summary रेजिस्टर */
	u8 __iomem *पूर्णांकr_sum_reg64;

	/** PCI पूर्णांकerrupt enable रेजिस्टर */
	u8 __iomem *पूर्णांकr_enb_reg64;

	/** The PCI पूर्णांकerrupt mask used by पूर्णांकerrupt handler */
	u64 पूर्णांकr_mask64;

	काष्ठा octeon_config *conf;

	/* Example additional fields - not used currently
	 *  काष्ठा अणु
	 *  पूर्णcn6xyz;
	 */

	/* For the purpose of atomic access to पूर्णांकerrupt enable reg */
	spinlock_t lock_क्रम_droq_पूर्णांक_enb_reg;

पूर्ण;

क्रमागत octeon_pcie_mps अणु
	PCIE_MPS_DEFAULT = -1,	/* Use the शेष setup by BIOS */
	PCIE_MPS_128B = 0,
	PCIE_MPS_256B = 1
पूर्ण;

क्रमागत octeon_pcie_mrrs अणु
	PCIE_MRRS_DEFAULT = -1,	/* Use the शेष setup by BIOS */
	PCIE_MRRS_128B = 0,
	PCIE_MRRS_256B = 1,
	PCIE_MRRS_512B = 2,
	PCIE_MRRS_1024B = 3,
	PCIE_MRRS_2048B = 4,
	PCIE_MRRS_4096B = 5
पूर्ण;

/* Common functions क्रम 66xx and 68xx */
पूर्णांक lio_cn6xxx_soft_reset(काष्ठा octeon_device *oct);
व्योम lio_cn6xxx_enable_error_reporting(काष्ठा octeon_device *oct);
व्योम lio_cn6xxx_setup_pcie_mps(काष्ठा octeon_device *oct,
			       क्रमागत octeon_pcie_mps mps);
व्योम lio_cn6xxx_setup_pcie_mrrs(काष्ठा octeon_device *oct,
				क्रमागत octeon_pcie_mrrs mrrs);
व्योम lio_cn6xxx_setup_global_input_regs(काष्ठा octeon_device *oct);
व्योम lio_cn6xxx_setup_global_output_regs(काष्ठा octeon_device *oct);
व्योम lio_cn6xxx_setup_iq_regs(काष्ठा octeon_device *oct, u32 iq_no);
व्योम lio_cn6xxx_setup_oq_regs(काष्ठा octeon_device *oct, u32 oq_no);
पूर्णांक lio_cn6xxx_enable_io_queues(काष्ठा octeon_device *oct);
व्योम lio_cn6xxx_disable_io_queues(काष्ठा octeon_device *oct);
irqवापस_t lio_cn6xxx_process_पूर्णांकerrupt_regs(व्योम *dev);
व्योम lio_cn6xxx_bar1_idx_setup(काष्ठा octeon_device *oct, u64 core_addr,
			       u32 idx, पूर्णांक valid);
व्योम lio_cn6xxx_bar1_idx_ग_लिखो(काष्ठा octeon_device *oct, u32 idx, u32 mask);
u32 lio_cn6xxx_bar1_idx_पढ़ो(काष्ठा octeon_device *oct, u32 idx);
u32
lio_cn6xxx_update_पढ़ो_index(काष्ठा octeon_instr_queue *iq);
व्योम lio_cn6xxx_enable_पूर्णांकerrupt(काष्ठा octeon_device *oct, u8 unused);
व्योम lio_cn6xxx_disable_पूर्णांकerrupt(काष्ठा octeon_device *oct, u8 unused);
व्योम cn6xxx_get_pcie_qlmport(काष्ठा octeon_device *oct);
व्योम lio_cn6xxx_setup_reg_address(काष्ठा octeon_device *oct, व्योम *chip,
				  काष्ठा octeon_reg_list *reg_list);
u32 lio_cn6xxx_coprocessor_घड़ी(काष्ठा octeon_device *oct);
u32 lio_cn6xxx_get_oq_ticks(काष्ठा octeon_device *oct, u32 समय_पूर्णांकr_in_us);
पूर्णांक lio_setup_cn66xx_octeon_device(काष्ठा octeon_device *oct);
पूर्णांक lio_validate_cn6xxx_config_info(काष्ठा octeon_device *oct,
				    काष्ठा octeon_config *conf6xxx);

#पूर्ण_अगर
