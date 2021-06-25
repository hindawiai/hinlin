<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Tegra124 DFLL FCPU घड़ी source driver
 *
 * Copyright (C) 2012-2019 NVIDIA Corporation.  All rights reserved.
 *
 * Aleksandr Frid <afrid@nvidia.com>
 * Paul Walmsley <pwalmsley@nvidia.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/err.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <soc/tegra/fuse.h>

#समावेश "clk.h"
#समावेश "clk-dfll.h"
#समावेश "cvb.h"

काष्ठा dfll_fcpu_data अणु
	स्थिर अचिन्हित दीर्घ *cpu_max_freq_table;
	अचिन्हित पूर्णांक cpu_max_freq_table_size;
	स्थिर काष्ठा cvb_table *cpu_cvb_tables;
	अचिन्हित पूर्णांक cpu_cvb_tables_size;
पूर्ण;

/* Maximum CPU frequency, indexed by CPU speeकरो id */
अटल स्थिर अचिन्हित दीर्घ tegra124_cpu_max_freq_table[] = अणु
	[0] = 2014500000UL,
	[1] = 2320500000UL,
	[2] = 2116500000UL,
	[3] = 2524500000UL,
पूर्ण;

अटल स्थिर काष्ठा cvb_table tegra124_cpu_cvb_tables[] = अणु
	अणु
		.speeकरो_id = -1,
		.process_id = -1,
		.min_millivolts = 900,
		.max_millivolts = 1260,
		.speeकरो_scale = 100,
		.voltage_scale = 1000,
		.entries = अणु
			अणु  204000000UL, अणु 1112619, -29295, 402 पूर्ण पूर्ण,
			अणु  306000000UL, अणु 1150460, -30585, 402 पूर्ण पूर्ण,
			अणु  408000000UL, अणु 1190122, -31865, 402 पूर्ण पूर्ण,
			अणु  510000000UL, अणु 1231606, -33155, 402 पूर्ण पूर्ण,
			अणु  612000000UL, अणु 1274912, -34435, 402 पूर्ण पूर्ण,
			अणु  714000000UL, अणु 1320040, -35725, 402 पूर्ण पूर्ण,
			अणु  816000000UL, अणु 1366990, -37005, 402 पूर्ण पूर्ण,
			अणु  918000000UL, अणु 1415762, -38295, 402 पूर्ण पूर्ण,
			अणु 1020000000UL, अणु 1466355, -39575, 402 पूर्ण पूर्ण,
			अणु 1122000000UL, अणु 1518771, -40865, 402 पूर्ण पूर्ण,
			अणु 1224000000UL, अणु 1573009, -42145, 402 पूर्ण पूर्ण,
			अणु 1326000000UL, अणु 1629068, -43435, 402 पूर्ण पूर्ण,
			अणु 1428000000UL, अणु 1686950, -44715, 402 पूर्ण पूर्ण,
			अणु 1530000000UL, अणु 1746653, -46005, 402 पूर्ण पूर्ण,
			अणु 1632000000UL, अणु 1808179, -47285, 402 पूर्ण पूर्ण,
			अणु 1734000000UL, अणु 1871526, -48575, 402 पूर्ण पूर्ण,
			अणु 1836000000UL, अणु 1936696, -49855, 402 पूर्ण पूर्ण,
			अणु 1938000000UL, अणु 2003687, -51145, 402 पूर्ण पूर्ण,
			अणु 2014500000UL, अणु 2054787, -52095, 402 पूर्ण पूर्ण,
			अणु 2116500000UL, अणु 2124957, -53385, 402 पूर्ण पूर्ण,
			अणु 2218500000UL, अणु 2196950, -54665, 402 पूर्ण पूर्ण,
			अणु 2320500000UL, अणु 2270765, -55955, 402 पूर्ण पूर्ण,
			अणु 2422500000UL, अणु 2346401, -57235, 402 पूर्ण पूर्ण,
			अणु 2524500000UL, अणु 2437299, -58535, 402 पूर्ण पूर्ण,
			अणु          0UL, अणु       0,      0,   0 पूर्ण पूर्ण,
		पूर्ण,
		.cpu_dfll_data = अणु
			.tune0_low = 0x005020ff,
			.tune0_high = 0x005040ff,
			.tune1 = 0x00000060,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ tegra210_cpu_max_freq_table[] = अणु
	[0] = 1912500000UL,
	[1] = 1912500000UL,
	[2] = 2218500000UL,
	[3] = 1785000000UL,
	[4] = 1632000000UL,
	[5] = 1912500000UL,
	[6] = 2014500000UL,
	[7] = 1734000000UL,
	[8] = 1683000000UL,
	[9] = 1555500000UL,
	[10] = 1504500000UL,
पूर्ण;

#घोषणा CPU_CVB_TABLE \
	.speeकरो_scale = 100,	\
	.voltage_scale = 1000,	\
	.entries = अणु		\
		अणु  204000000UL,	अणु 1007452, -23865, 370 पूर्ण पूर्ण, \
		अणु  306000000UL,	अणु 1052709, -24875, 370 पूर्ण पूर्ण, \
		अणु  408000000UL,	अणु 1099069, -25895, 370 पूर्ण पूर्ण, \
		अणु  510000000UL,	अणु 1146534, -26905, 370 पूर्ण पूर्ण, \
		अणु  612000000UL,	अणु 1195102, -27915, 370 पूर्ण पूर्ण, \
		अणु  714000000UL,	अणु 1244773, -28925, 370 पूर्ण पूर्ण, \
		अणु  816000000UL,	अणु 1295549, -29935, 370 पूर्ण पूर्ण, \
		अणु  918000000UL,	अणु 1347428, -30955, 370 पूर्ण पूर्ण, \
		अणु 1020000000UL,	अणु 1400411, -31965, 370 पूर्ण पूर्ण, \
		अणु 1122000000UL,	अणु 1454497, -32975, 370 पूर्ण पूर्ण, \
		अणु 1224000000UL,	अणु 1509687, -33985, 370 पूर्ण पूर्ण, \
		अणु 1326000000UL,	अणु 1565981, -35005, 370 पूर्ण पूर्ण, \
		अणु 1428000000UL,	अणु 1623379, -36015, 370 पूर्ण पूर्ण, \
		अणु 1530000000UL,	अणु 1681880, -37025, 370 पूर्ण पूर्ण, \
		अणु 1632000000UL,	अणु 1741485, -38035, 370 पूर्ण पूर्ण, \
		अणु 1734000000UL,	अणु 1802194, -39055, 370 पूर्ण पूर्ण, \
		अणु 1836000000UL,	अणु 1864006, -40065, 370 पूर्ण पूर्ण, \
		अणु 1912500000UL,	अणु 1910780, -40815, 370 पूर्ण पूर्ण, \
		अणु 2014500000UL,	अणु 1227000,      0,   0 पूर्ण पूर्ण, \
		अणु 2218500000UL,	अणु 1227000,      0,   0 पूर्ण पूर्ण, \
		अणु          0UL,	अणु       0,      0,   0 पूर्ण पूर्ण, \
	पूर्ण

#घोषणा CPU_CVB_TABLE_XA \
	.speeकरो_scale = 100,	\
	.voltage_scale = 1000,	\
	.entries = अणु		\
		अणु  204000000UL,	अणु 1250024, -39785, 565 पूर्ण पूर्ण, \
		अणु  306000000UL,	अणु 1297556, -41145, 565 पूर्ण पूर्ण, \
		अणु  408000000UL,	अणु 1346718, -42505, 565 पूर्ण पूर्ण, \
		अणु  510000000UL,	अणु 1397511, -43855, 565 पूर्ण पूर्ण, \
		अणु  612000000UL,	अणु 1449933, -45215, 565 पूर्ण पूर्ण, \
		अणु  714000000UL,	अणु 1503986, -46575, 565 पूर्ण पूर्ण, \
		अणु  816000000UL,	अणु 1559669, -47935, 565 पूर्ण पूर्ण, \
		अणु  918000000UL,	अणु 1616982, -49295, 565 पूर्ण पूर्ण, \
		अणु 1020000000UL,	अणु 1675926, -50645, 565 पूर्ण पूर्ण, \
		अणु 1122000000UL,	अणु 1736500, -52005, 565 पूर्ण पूर्ण, \
		अणु 1224000000UL,	अणु 1798704, -53365, 565 पूर्ण पूर्ण, \
		अणु 1326000000UL,	अणु 1862538, -54725, 565 पूर्ण पूर्ण, \
		अणु 1428000000UL,	अणु 1928003, -56085, 565 पूर्ण पूर्ण, \
		अणु 1530000000UL,	अणु 1995097, -57435, 565 पूर्ण पूर्ण, \
		अणु 1606500000UL,	अणु 2046149, -58445, 565 पूर्ण पूर्ण, \
		अणु 1632000000UL,	अणु 2063822, -58795, 565 पूर्ण पूर्ण, \
		अणु          0UL,	अणु       0,      0,   0 पूर्ण पूर्ण, \
	पूर्ण

#घोषणा CPU_CVB_TABLE_EUCM1 \
	.speeकरो_scale = 100,	\
	.voltage_scale = 1000,	\
	.entries = अणु		\
		अणु  204000000UL,	अणु  734429, 0, 0 पूर्ण पूर्ण, \
		अणु  306000000UL,	अणु  768191, 0, 0 पूर्ण पूर्ण, \
		अणु  408000000UL,	अणु  801953, 0, 0 पूर्ण पूर्ण, \
		अणु  510000000UL,	अणु  835715, 0, 0 पूर्ण पूर्ण, \
		अणु  612000000UL,	अणु  869477, 0, 0 पूर्ण पूर्ण, \
		अणु  714000000UL,	अणु  903239, 0, 0 पूर्ण पूर्ण, \
		अणु  816000000UL,	अणु  937001, 0, 0 पूर्ण पूर्ण, \
		अणु  918000000UL,	अणु  970763, 0, 0 पूर्ण पूर्ण, \
		अणु 1020000000UL,	अणु 1004525, 0, 0 पूर्ण पूर्ण, \
		अणु 1122000000UL,	अणु 1038287, 0, 0 पूर्ण पूर्ण, \
		अणु 1224000000UL,	अणु 1072049, 0, 0 पूर्ण पूर्ण, \
		अणु 1326000000UL,	अणु 1105811, 0, 0 पूर्ण पूर्ण, \
		अणु 1428000000UL,	अणु 1130000, 0, 0 पूर्ण पूर्ण, \
		अणु 1555500000UL,	अणु 1130000, 0, 0 पूर्ण पूर्ण, \
		अणु 1632000000UL,	अणु 1170000, 0, 0 पूर्ण पूर्ण, \
		अणु 1734000000UL,	अणु 1227500, 0, 0 पूर्ण पूर्ण, \
		अणु          0UL,	अणु       0, 0, 0 पूर्ण पूर्ण, \
	पूर्ण

#घोषणा CPU_CVB_TABLE_EUCM2 \
	.speeकरो_scale = 100,	\
	.voltage_scale = 1000,	\
	.entries = अणु		\
		अणु  204000000UL,	अणु  742283, 0, 0 पूर्ण पूर्ण, \
		अणु  306000000UL,	अणु  776249, 0, 0 पूर्ण पूर्ण, \
		अणु  408000000UL,	अणु  810215, 0, 0 पूर्ण पूर्ण, \
		अणु  510000000UL,	अणु  844181, 0, 0 पूर्ण पूर्ण, \
		अणु  612000000UL,	अणु  878147, 0, 0 पूर्ण पूर्ण, \
		अणु  714000000UL,	अणु  912113, 0, 0 पूर्ण पूर्ण, \
		अणु  816000000UL,	अणु  946079, 0, 0 पूर्ण पूर्ण, \
		अणु  918000000UL,	अणु  980045, 0, 0 पूर्ण पूर्ण, \
		अणु 1020000000UL,	अणु 1014011, 0, 0 पूर्ण पूर्ण, \
		अणु 1122000000UL,	अणु 1047977, 0, 0 पूर्ण पूर्ण, \
		अणु 1224000000UL,	अणु 1081943, 0, 0 पूर्ण पूर्ण, \
		अणु 1326000000UL,	अणु 1090000, 0, 0 पूर्ण पूर्ण, \
		अणु 1479000000UL,	अणु 1090000, 0, 0 पूर्ण पूर्ण, \
		अणु 1555500000UL,	अणु 1162000, 0, 0 पूर्ण पूर्ण, \
		अणु 1683000000UL,	अणु 1195000, 0, 0 पूर्ण पूर्ण, \
		अणु          0UL,	अणु       0, 0, 0 पूर्ण पूर्ण, \
	पूर्ण

#घोषणा CPU_CVB_TABLE_EUCM2_JOINT_RAIL \
	.speeकरो_scale = 100,	\
	.voltage_scale = 1000,	\
	.entries = अणु		\
		अणु  204000000UL,	अणु  742283, 0, 0 पूर्ण पूर्ण, \
		अणु  306000000UL,	अणु  776249, 0, 0 पूर्ण पूर्ण, \
		अणु  408000000UL,	अणु  810215, 0, 0 पूर्ण पूर्ण, \
		अणु  510000000UL,	अणु  844181, 0, 0 पूर्ण पूर्ण, \
		अणु  612000000UL,	अणु  878147, 0, 0 पूर्ण पूर्ण, \
		अणु  714000000UL,	अणु  912113, 0, 0 पूर्ण पूर्ण, \
		अणु  816000000UL,	अणु  946079, 0, 0 पूर्ण पूर्ण, \
		अणु  918000000UL,	अणु  980045, 0, 0 पूर्ण पूर्ण, \
		अणु 1020000000UL,	अणु 1014011, 0, 0 पूर्ण पूर्ण, \
		अणु 1122000000UL,	अणु 1047977, 0, 0 पूर्ण पूर्ण, \
		अणु 1224000000UL,	अणु 1081943, 0, 0 पूर्ण पूर्ण, \
		अणु 1326000000UL,	अणु 1090000, 0, 0 पूर्ण पूर्ण, \
		अणु 1479000000UL,	अणु 1090000, 0, 0 पूर्ण पूर्ण, \
		अणु 1504500000UL,	अणु 1120000, 0, 0 पूर्ण पूर्ण, \
		अणु          0UL,	अणु       0, 0, 0 पूर्ण पूर्ण, \
	पूर्ण

#घोषणा CPU_CVB_TABLE_ODN \
	.speeकरो_scale = 100,	\
	.voltage_scale = 1000,	\
	.entries = अणु		\
		अणु  204000000UL,	अणु  721094, 0, 0 पूर्ण पूर्ण, \
		अणु  306000000UL,	अणु  754040, 0, 0 पूर्ण पूर्ण, \
		अणु  408000000UL,	अणु  786986, 0, 0 पूर्ण पूर्ण, \
		अणु  510000000UL,	अणु  819932, 0, 0 पूर्ण पूर्ण, \
		अणु  612000000UL,	अणु  852878, 0, 0 पूर्ण पूर्ण, \
		अणु  714000000UL,	अणु  885824, 0, 0 पूर्ण पूर्ण, \
		अणु  816000000UL,	अणु  918770, 0, 0 पूर्ण पूर्ण, \
		अणु  918000000UL,	अणु  915716, 0, 0 पूर्ण पूर्ण, \
		अणु 1020000000UL,	अणु  984662, 0, 0 पूर्ण पूर्ण, \
		अणु 1122000000UL,	अणु 1017608, 0, 0 पूर्ण पूर्ण, \
		अणु 1224000000UL,	अणु 1050554, 0, 0 पूर्ण पूर्ण, \
		अणु 1326000000UL,	अणु 1083500, 0, 0 पूर्ण पूर्ण, \
		अणु 1428000000UL,	अणु 1116446, 0, 0 पूर्ण पूर्ण, \
		अणु 1581000000UL,	अणु 1130000, 0, 0 पूर्ण पूर्ण, \
		अणु 1683000000UL,	अणु 1168000, 0, 0 पूर्ण पूर्ण, \
		अणु 1785000000UL,	अणु 1227500, 0, 0 पूर्ण पूर्ण, \
		अणु          0UL,	अणु       0, 0, 0 पूर्ण पूर्ण, \
	पूर्ण

अटल काष्ठा cvb_table tegra210_cpu_cvb_tables[] = अणु
	अणु
		.speeकरो_id = 10,
		.process_id = 0,
		.min_millivolts = 840,
		.max_millivolts = 1120,
		CPU_CVB_TABLE_EUCM2_JOINT_RAIL,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 10,
		.process_id = 1,
		.min_millivolts = 840,
		.max_millivolts = 1120,
		CPU_CVB_TABLE_EUCM2_JOINT_RAIL,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 9,
		.process_id = 0,
		.min_millivolts = 900,
		.max_millivolts = 1162,
		CPU_CVB_TABLE_EUCM2,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 9,
		.process_id = 1,
		.min_millivolts = 900,
		.max_millivolts = 1162,
		CPU_CVB_TABLE_EUCM2,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 8,
		.process_id = 0,
		.min_millivolts = 900,
		.max_millivolts = 1195,
		CPU_CVB_TABLE_EUCM2,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 8,
		.process_id = 1,
		.min_millivolts = 900,
		.max_millivolts = 1195,
		CPU_CVB_TABLE_EUCM2,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 7,
		.process_id = 0,
		.min_millivolts = 841,
		.max_millivolts = 1227,
		CPU_CVB_TABLE_EUCM1,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 7,
		.process_id = 1,
		.min_millivolts = 841,
		.max_millivolts = 1227,
		CPU_CVB_TABLE_EUCM1,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 6,
		.process_id = 0,
		.min_millivolts = 870,
		.max_millivolts = 1150,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune1 = 0x20091d9,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 6,
		.process_id = 1,
		.min_millivolts = 870,
		.max_millivolts = 1150,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune1 = 0x25501d0,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 5,
		.process_id = 0,
		.min_millivolts = 818,
		.max_millivolts = 1227,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 5,
		.process_id = 1,
		.min_millivolts = 818,
		.max_millivolts = 1227,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x25501d0,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 4,
		.process_id = -1,
		.min_millivolts = 918,
		.max_millivolts = 1113,
		CPU_CVB_TABLE_XA,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune1 = 0x17711BD,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 3,
		.process_id = 0,
		.min_millivolts = 825,
		.max_millivolts = 1227,
		CPU_CVB_TABLE_ODN,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 3,
		.process_id = 1,
		.min_millivolts = 825,
		.max_millivolts = 1227,
		CPU_CVB_TABLE_ODN,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x25501d0,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 2,
		.process_id = 0,
		.min_millivolts = 870,
		.max_millivolts = 1227,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune1 = 0x20091d9,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 2,
		.process_id = 1,
		.min_millivolts = 870,
		.max_millivolts = 1227,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune1 = 0x25501d0,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 1,
		.process_id = 0,
		.min_millivolts = 837,
		.max_millivolts = 1227,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 1,
		.process_id = 1,
		.min_millivolts = 837,
		.max_millivolts = 1227,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x25501d0,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 0,
		.process_id = 0,
		.min_millivolts = 850,
		.max_millivolts = 1170,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x20091d9,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
	अणु
		.speeकरो_id = 0,
		.process_id = 1,
		.min_millivolts = 850,
		.max_millivolts = 1170,
		CPU_CVB_TABLE,
		.cpu_dfll_data = अणु
			.tune0_low = 0xffead0ff,
			.tune0_high = 0xffead0ff,
			.tune1 = 0x25501d0,
			.tune_high_min_millivolts = 864,
		पूर्ण
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा dfll_fcpu_data tegra124_dfll_fcpu_data = अणु
	.cpu_max_freq_table = tegra124_cpu_max_freq_table,
	.cpu_max_freq_table_size = ARRAY_SIZE(tegra124_cpu_max_freq_table),
	.cpu_cvb_tables = tegra124_cpu_cvb_tables,
	.cpu_cvb_tables_size = ARRAY_SIZE(tegra124_cpu_cvb_tables)
पूर्ण;

अटल स्थिर काष्ठा dfll_fcpu_data tegra210_dfll_fcpu_data = अणु
	.cpu_max_freq_table = tegra210_cpu_max_freq_table,
	.cpu_max_freq_table_size = ARRAY_SIZE(tegra210_cpu_max_freq_table),
	.cpu_cvb_tables = tegra210_cpu_cvb_tables,
	.cpu_cvb_tables_size = ARRAY_SIZE(tegra210_cpu_cvb_tables),
पूर्ण;

अटल स्थिर काष्ठा of_device_id tegra124_dfll_fcpu_of_match[] = अणु
	अणु
		.compatible = "nvidia,tegra124-dfll",
		.data = &tegra124_dfll_fcpu_data,
	पूर्ण,
	अणु
		.compatible = "nvidia,tegra210-dfll",
		.data = &tegra210_dfll_fcpu_data
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल व्योम get_alignment_from_dt(काष्ठा device *dev,
				  काष्ठा rail_alignment *align)
अणु
	अगर (of_property_पढ़ो_u32(dev->of_node,
				 "nvidia,pwm-voltage-step-microvolts",
				 &align->step_uv))
		align->step_uv = 0;

	अगर (of_property_पढ़ो_u32(dev->of_node,
				 "nvidia,pwm-min-microvolts",
				 &align->offset_uv))
		align->offset_uv = 0;
पूर्ण

अटल पूर्णांक get_alignment_from_regulator(काष्ठा device *dev,
					 काष्ठा rail_alignment *align)
अणु
	काष्ठा regulator *reg = devm_regulator_get(dev, "vdd-cpu");

	अगर (IS_ERR(reg))
		वापस PTR_ERR(reg);

	align->offset_uv = regulator_list_voltage(reg, 0);
	align->step_uv = regulator_get_linear_step(reg);

	devm_regulator_put(reg);

	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_dfll_fcpu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक process_id, speeकरो_id, speeकरो_value, err;
	काष्ठा tegra_dfll_soc_data *soc;
	स्थिर काष्ठा dfll_fcpu_data *fcpu_data;
	काष्ठा rail_alignment align;

	fcpu_data = of_device_get_match_data(&pdev->dev);
	अगर (!fcpu_data)
		वापस -ENODEV;

	process_id = tegra_sku_info.cpu_process_id;
	speeकरो_id = tegra_sku_info.cpu_speeकरो_id;
	speeकरो_value = tegra_sku_info.cpu_speeकरो_value;

	अगर (speeकरो_id >= fcpu_data->cpu_max_freq_table_size) अणु
		dev_err(&pdev->dev, "unknown max CPU freq for speedo_id=%d\n",
			speeकरो_id);
		वापस -ENODEV;
	पूर्ण

	soc = devm_kzalloc(&pdev->dev, माप(*soc), GFP_KERNEL);
	अगर (!soc)
		वापस -ENOMEM;

	soc->dev = get_cpu_device(0);
	अगर (!soc->dev) अणु
		dev_err(&pdev->dev, "no CPU0 device\n");
		वापस -ENODEV;
	पूर्ण

	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "nvidia,pwm-to-pmic")) अणु
		get_alignment_from_dt(&pdev->dev, &align);
	पूर्ण अन्यथा अणु
		err = get_alignment_from_regulator(&pdev->dev, &align);
		अगर (err)
			वापस err;
	पूर्ण

	soc->max_freq = fcpu_data->cpu_max_freq_table[speeकरो_id];

	soc->cvb = tegra_cvb_add_opp_table(soc->dev, fcpu_data->cpu_cvb_tables,
					   fcpu_data->cpu_cvb_tables_size,
					   &align, process_id, speeकरो_id,
					   speeकरो_value, soc->max_freq);
	soc->alignment = align;

	अगर (IS_ERR(soc->cvb)) अणु
		dev_err(&pdev->dev, "couldn't add OPP table: %ld\n",
			PTR_ERR(soc->cvb));
		वापस PTR_ERR(soc->cvb);
	पूर्ण

	err = tegra_dfll_रेजिस्टर(pdev, soc);
	अगर (err < 0) अणु
		tegra_cvb_हटाओ_opp_table(soc->dev, soc->cvb, soc->max_freq);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक tegra124_dfll_fcpu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा tegra_dfll_soc_data *soc;

	soc = tegra_dfll_unरेजिस्टर(pdev);
	अगर (IS_ERR(soc)) अणु
		dev_err(&pdev->dev, "failed to unregister DFLL: %ld\n",
			PTR_ERR(soc));
		वापस PTR_ERR(soc);
	पूर्ण

	tegra_cvb_हटाओ_opp_table(soc->dev, soc->cvb, soc->max_freq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops tegra124_dfll_pm_ops = अणु
	SET_RUNTIME_PM_OPS(tegra_dfll_runसमय_suspend,
			   tegra_dfll_runसमय_resume, शून्य)
	SET_SYSTEM_SLEEP_PM_OPS(tegra_dfll_suspend, tegra_dfll_resume)
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra124_dfll_fcpu_driver = अणु
	.probe = tegra124_dfll_fcpu_probe,
	.हटाओ = tegra124_dfll_fcpu_हटाओ,
	.driver = अणु
		.name = "tegra124-dfll",
		.of_match_table = tegra124_dfll_fcpu_of_match,
		.pm = &tegra124_dfll_pm_ops,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(tegra124_dfll_fcpu_driver);
