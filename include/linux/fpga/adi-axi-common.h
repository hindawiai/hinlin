<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Analog Devices AXI common रेजिस्टरs & definitions
 *
 * Copyright 2019 Analog Devices Inc.
 *
 * https://wiki.analog.com/resources/fpga/करोcs/axi_ip
 * https://wiki.analog.com/resources/fpga/करोcs/hdl/regmap
 */

#अगर_अघोषित ADI_AXI_COMMON_H_
#घोषणा ADI_AXI_COMMON_H_

#घोषणा ADI_AXI_REG_VERSION			0x0000

#घोषणा ADI_AXI_PCORE_VER(major, minor, patch)	\
	(((major) << 16) | ((minor) << 8) | (patch))

#घोषणा ADI_AXI_PCORE_VER_MAJOR(version)	(((version) >> 16) & 0xff)
#घोषणा ADI_AXI_PCORE_VER_MINOR(version)	(((version) >> 8) & 0xff)
#घोषणा ADI_AXI_PCORE_VER_PATCH(version)	((version) & 0xff)

#पूर्ण_अगर /* ADI_AXI_COMMON_H_ */
