<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Xilinx Zynq MPSoC Firmware layer
 *
 *  Copyright (C) 2014-2018 Xilinx
 *
 *  Michal Simek <michal.simek@xilinx.com>
 *  Davorin Mista <davorin.mista@aggios.com>
 *  Jolly Shah <jollys@xilinx.com>
 *  Rajan Vaja <rajanv@xilinx.com>
 */

#अगर_अघोषित __FIRMWARE_ZYNQMP_DEBUG_H__
#घोषणा __FIRMWARE_ZYNQMP_DEBUG_H__

#अगर IS_REACHABLE(CONFIG_ZYNQMP_FIRMWARE_DEBUG)
व्योम zynqmp_pm_api_debugfs_init(व्योम);
व्योम zynqmp_pm_api_debugfs_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम zynqmp_pm_api_debugfs_init(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम zynqmp_pm_api_debugfs_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __FIRMWARE_ZYNQMP_DEBUG_H__ */
