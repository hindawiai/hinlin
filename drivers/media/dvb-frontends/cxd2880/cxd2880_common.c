<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cxd2880_common.c
 * Sony CXD2880 DVB-T2/T tuner + demodulator driver
 * common functions
 *
 * Copyright (C) 2016, 2017, 2018 Sony Semiconductor Solutions Corporation
 */

#समावेश "cxd2880_common.h"

पूर्णांक cxd2880_convert2s_complement(u32 value, u32 bitlen)
अणु
	अगर (!bitlen || bitlen >= 32)
		वापस (पूर्णांक)value;

	अगर (value & (u32)(1 << (bitlen - 1)))
		वापस (पूर्णांक)(GENMASK(31, bitlen) | value);
	अन्यथा
		वापस (पूर्णांक)(GENMASK(bitlen - 1, 0) & value);
पूर्ण
