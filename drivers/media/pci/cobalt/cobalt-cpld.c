<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Cobalt CPLD functions
 *
 *  Copyright 2012-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/delay.h>

#समावेश "cobalt-cpld.h"

#घोषणा ADRS(offset) (COBALT_BUS_CPLD_BASE + offset)

अटल u16 cpld_पढ़ो(काष्ठा cobalt *cobalt, u32 offset)
अणु
	वापस cobalt_bus_पढ़ो32(cobalt->bar1, ADRS(offset));
पूर्ण

अटल व्योम cpld_ग_लिखो(काष्ठा cobalt *cobalt, u32 offset, u16 val)
अणु
	वापस cobalt_bus_ग_लिखो32(cobalt->bar1, ADRS(offset), val);
पूर्ण

अटल व्योम cpld_info_ver3(काष्ठा cobalt *cobalt)
अणु
	u32 rd;
	u32 पंचांगp;

	cobalt_info("CPLD System control register (read/write)\n");
	cobalt_info("\t\tSystem control:  0x%04x (0x0f00)\n",
		    cpld_पढ़ो(cobalt, 0));
	cobalt_info("CPLD Clock control register (read/write)\n");
	cobalt_info("\t\tClock control:   0x%04x (0x0000)\n",
		    cpld_पढ़ो(cobalt, 0x04));
	cobalt_info("CPLD HSMA Clk Osc register (read/write) - Must set wr trigger to load default values\n");
	cobalt_info("\t\tRegister #7:\t0x%04x (0x0022)\n",
		    cpld_पढ़ो(cobalt, 0x08));
	cobalt_info("\t\tRegister #8:\t0x%04x (0x0047)\n",
		    cpld_पढ़ो(cobalt, 0x0c));
	cobalt_info("\t\tRegister #9:\t0x%04x (0x00fa)\n",
		    cpld_पढ़ो(cobalt, 0x10));
	cobalt_info("\t\tRegister #10:\t0x%04x (0x0061)\n",
		    cpld_पढ़ो(cobalt, 0x14));
	cobalt_info("\t\tRegister #11:\t0x%04x (0x001e)\n",
		    cpld_पढ़ो(cobalt, 0x18));
	cobalt_info("\t\tRegister #12:\t0x%04x (0x0045)\n",
		    cpld_पढ़ो(cobalt, 0x1c));
	cobalt_info("\t\tRegister #135:\t0x%04x\n",
		    cpld_पढ़ो(cobalt, 0x20));
	cobalt_info("\t\tRegister #137:\t0x%04x\n",
		    cpld_पढ़ो(cobalt, 0x24));
	cobalt_info("CPLD System status register (read only)\n");
	cobalt_info("\t\tSystem status:  0x%04x\n",
		    cpld_पढ़ो(cobalt, 0x28));
	cobalt_info("CPLD MAXII info register (read only)\n");
	cobalt_info("\t\tBoard serial number:     0x%04x\n",
		    cpld_पढ़ो(cobalt, 0x2c));
	cobalt_info("\t\tMAXII program revision:  0x%04x\n",
		    cpld_पढ़ो(cobalt, 0x30));
	cobalt_info("CPLD temp and voltage ADT7411 registers (read only)\n");
	cobalt_info("\t\tBoard temperature:  %u Celsius\n",
		    cpld_पढ़ो(cobalt, 0x34) / 4);
	cobalt_info("\t\tFPGA temperature:   %u Celsius\n",
		    cpld_पढ़ो(cobalt, 0x38) / 4);
	rd = cpld_पढ़ो(cobalt, 0x3c);
	पंचांगp = (rd * 33 * 1000) / (483 * 10);
	cobalt_info("\t\tVDD 3V3:      %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
	rd = cpld_पढ़ो(cobalt, 0x40);
	पंचांगp = (rd * 74 * 2197) / (27 * 1000);
	cobalt_info("\t\tADC ch3 5V:   %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
	rd = cpld_पढ़ो(cobalt, 0x44);
	पंचांगp = (rd * 74 * 2197) / (47 * 1000);
	cobalt_info("\t\tADC ch4 3V:   %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
	rd = cpld_पढ़ो(cobalt, 0x48);
	पंचांगp = (rd * 57 * 2197) / (47 * 1000);
	cobalt_info("\t\tADC ch5 2V5:  %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
	rd = cpld_पढ़ो(cobalt, 0x4c);
	पंचांगp = (rd * 2197) / 1000;
	cobalt_info("\t\tADC ch6 1V8:  %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
	rd = cpld_पढ़ो(cobalt, 0x50);
	पंचांगp = (rd * 2197) / 1000;
	cobalt_info("\t\tADC ch7 1V5:  %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
	rd = cpld_पढ़ो(cobalt, 0x54);
	पंचांगp = (rd * 2197) / 1000;
	cobalt_info("\t\tADC ch8 0V9:  %u,%03uV\n", पंचांगp / 1000, पंचांगp % 1000);
पूर्ण

व्योम cobalt_cpld_status(काष्ठा cobalt *cobalt)
अणु
	u32 rev = cpld_पढ़ो(cobalt, 0x30);

	चयन (rev) अणु
	हाल 3:
	हाल 4:
	हाल 5:
		cpld_info_ver3(cobalt);
		अवरोध;
	शेष:
		cobalt_info("CPLD revision %u is not supported!\n", rev);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा DCO_MIN 4850000000ULL
#घोषणा DCO_MAX 5670000000ULL

#घोषणा SI570_CLOCK_CTRL   0x04
#घोषणा S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_WR_TRIGGER 0x200
#घोषणा S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_RST_TRIGGER 0x100
#घोषणा S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL 0x80
#घोषणा S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN 0x40

#घोषणा SI570_REG7   0x08
#घोषणा SI570_REG8   0x0c
#घोषणा SI570_REG9   0x10
#घोषणा SI570_REG10  0x14
#घोषणा SI570_REG11  0x18
#घोषणा SI570_REG12  0x1c
#घोषणा SI570_REG135 0x20
#घोषणा SI570_REG137 0x24

काष्ठा multiplier अणु
	अचिन्हित mult, hsभाग, n1;
पूर्ण;

/* List all possible multipliers (= hsभाग * n1). There are lots of duplicates,
   which are all हटाओd in this list to keep the list as लघु as possible.
   The values क्रम hsभाग and n1 are the actual values, not the रेजिस्टर values.
 */
अटल स्थिर काष्ठा multiplier multipliers[] = अणु
	अणु    4,  4,   1 पूर्ण, अणु    5,  5,   1 पूर्ण, अणु    6,  6,   1 पूर्ण,
	अणु    7,  7,   1 पूर्ण, अणु    8,  4,   2 पूर्ण, अणु    9,  9,   1 पूर्ण,
	अणु   10,  5,   2 पूर्ण, अणु   11, 11,   1 पूर्ण, अणु   12,  6,   2 पूर्ण,
	अणु   14,  7,   2 पूर्ण, अणु   16,  4,   4 पूर्ण, अणु   18,  9,   2 पूर्ण,
	अणु   20,  5,   4 पूर्ण, अणु   22, 11,   2 पूर्ण, अणु   24,  4,   6 पूर्ण,
	अणु   28,  7,   4 पूर्ण, अणु   30,  5,   6 पूर्ण, अणु   32,  4,   8 पूर्ण,
	अणु   36,  6,   6 पूर्ण, अणु   40,  4,  10 पूर्ण, अणु   42,  7,   6 पूर्ण,
	अणु   44, 11,   4 पूर्ण, अणु   48,  4,  12 पूर्ण, अणु   50,  5,  10 पूर्ण,
	अणु   54,  9,   6 पूर्ण, अणु   56,  4,  14 पूर्ण, अणु   60,  5,  12 पूर्ण,
	अणु   64,  4,  16 पूर्ण, अणु   66, 11,   6 पूर्ण, अणु   70,  5,  14 पूर्ण,
	अणु   72,  4,  18 पूर्ण, अणु   80,  4,  20 पूर्ण, अणु   84,  6,  14 पूर्ण,
	अणु   88, 11,   8 पूर्ण, अणु   90,  5,  18 पूर्ण, अणु   96,  4,  24 पूर्ण,
	अणु   98,  7,  14 पूर्ण, अणु  100,  5,  20 पूर्ण, अणु  104,  4,  26 पूर्ण,
	अणु  108,  6,  18 पूर्ण, अणु  110, 11,  10 पूर्ण, अणु  112,  4,  28 पूर्ण,
	अणु  120,  4,  30 पूर्ण, अणु  126,  7,  18 पूर्ण, अणु  128,  4,  32 पूर्ण,
	अणु  130,  5,  26 पूर्ण, अणु  132, 11,  12 पूर्ण, अणु  136,  4,  34 पूर्ण,
	अणु  140,  5,  28 पूर्ण, अणु  144,  4,  36 पूर्ण, अणु  150,  5,  30 पूर्ण,
	अणु  152,  4,  38 पूर्ण, अणु  154, 11,  14 पूर्ण, अणु  156,  6,  26 पूर्ण,
	अणु  160,  4,  40 पूर्ण, अणु  162,  9,  18 पूर्ण, अणु  168,  4,  42 पूर्ण,
	अणु  170,  5,  34 पूर्ण, अणु  176, 11,  16 पूर्ण, अणु  180,  5,  36 पूर्ण,
	अणु  182,  7,  26 पूर्ण, अणु  184,  4,  46 पूर्ण, अणु  190,  5,  38 पूर्ण,
	अणु  192,  4,  48 पूर्ण, अणु  196,  7,  28 पूर्ण, अणु  198, 11,  18 पूर्ण,
	अणु  198,  9,  22 पूर्ण, अणु  200,  4,  50 पूर्ण, अणु  204,  6,  34 पूर्ण,
	अणु  208,  4,  52 पूर्ण, अणु  210,  5,  42 पूर्ण, अणु  216,  4,  54 पूर्ण,
	अणु  220, 11,  20 पूर्ण, अणु  224,  4,  56 पूर्ण, अणु  228,  6,  38 पूर्ण,
	अणु  230,  5,  46 पूर्ण, अणु  232,  4,  58 पूर्ण, अणु  234,  9,  26 पूर्ण,
	अणु  238,  7,  34 पूर्ण, अणु  240,  4,  60 पूर्ण, अणु  242, 11,  22 पूर्ण,
	अणु  248,  4,  62 पूर्ण, अणु  250,  5,  50 पूर्ण, अणु  252,  6,  42 पूर्ण,
	अणु  256,  4,  64 पूर्ण, अणु  260,  5,  52 पूर्ण, अणु  264, 11,  24 पूर्ण,
	अणु  266,  7,  38 पूर्ण, अणु  270,  5,  54 पूर्ण, अणु  272,  4,  68 पूर्ण,
	अणु  276,  6,  46 पूर्ण, अणु  280,  4,  70 पूर्ण, अणु  286, 11,  26 पूर्ण,
	अणु  288,  4,  72 पूर्ण, अणु  290,  5,  58 पूर्ण, अणु  294,  7,  42 पूर्ण,
	अणु  296,  4,  74 पूर्ण, अणु  300,  5,  60 पूर्ण, अणु  304,  4,  76 पूर्ण,
	अणु  306,  9,  34 पूर्ण, अणु  308, 11,  28 पूर्ण, अणु  310,  5,  62 पूर्ण,
	अणु  312,  4,  78 पूर्ण, अणु  320,  4,  80 पूर्ण, अणु  322,  7,  46 पूर्ण,
	अणु  324,  6,  54 पूर्ण, अणु  328,  4,  82 पूर्ण, अणु  330, 11,  30 पूर्ण,
	अणु  336,  4,  84 पूर्ण, अणु  340,  5,  68 पूर्ण, अणु  342,  9,  38 पूर्ण,
	अणु  344,  4,  86 पूर्ण, अणु  348,  6,  58 पूर्ण, अणु  350,  5,  70 पूर्ण,
	अणु  352, 11,  32 पूर्ण, अणु  360,  4,  90 पूर्ण, अणु  364,  7,  52 पूर्ण,
	अणु  368,  4,  92 पूर्ण, अणु  370,  5,  74 पूर्ण, अणु  372,  6,  62 पूर्ण,
	अणु  374, 11,  34 पूर्ण, अणु  376,  4,  94 पूर्ण, अणु  378,  7,  54 पूर्ण,
	अणु  380,  5,  76 पूर्ण, अणु  384,  4,  96 पूर्ण, अणु  390,  5,  78 पूर्ण,
	अणु  392,  4,  98 पूर्ण, अणु  396, 11,  36 पूर्ण, अणु  400,  4, 100 पूर्ण,
	अणु  406,  7,  58 पूर्ण, अणु  408,  4, 102 पूर्ण, अणु  410,  5,  82 पूर्ण,
	अणु  414,  9,  46 पूर्ण, अणु  416,  4, 104 पूर्ण, अणु  418, 11,  38 पूर्ण,
	अणु  420,  5,  84 पूर्ण, अणु  424,  4, 106 पूर्ण, अणु  430,  5,  86 पूर्ण,
	अणु  432,  4, 108 पूर्ण, अणु  434,  7,  62 पूर्ण, अणु  440, 11,  40 पूर्ण,
	अणु  444,  6,  74 पूर्ण, अणु  448,  4, 112 पूर्ण, अणु  450,  5,  90 पूर्ण,
	अणु  456,  4, 114 पूर्ण, अणु  460,  5,  92 पूर्ण, अणु  462, 11,  42 पूर्ण,
	अणु  464,  4, 116 पूर्ण, अणु  468,  6,  78 पूर्ण, अणु  470,  5,  94 पूर्ण,
	अणु  472,  4, 118 पूर्ण, अणु  476,  7,  68 पूर्ण, अणु  480,  4, 120 पूर्ण,
	अणु  484, 11,  44 पूर्ण, अणु  486,  9,  54 पूर्ण, अणु  488,  4, 122 पूर्ण,
	अणु  490,  5,  98 पूर्ण, अणु  492,  6,  82 पूर्ण, अणु  496,  4, 124 पूर्ण,
	अणु  500,  5, 100 पूर्ण, अणु  504,  4, 126 पूर्ण, अणु  506, 11,  46 पूर्ण,
	अणु  510,  5, 102 पूर्ण, अणु  512,  4, 128 पूर्ण, अणु  516,  6,  86 पूर्ण,
	अणु  518,  7,  74 पूर्ण, अणु  520,  5, 104 पूर्ण, अणु  522,  9,  58 पूर्ण,
	अणु  528, 11,  48 पूर्ण, अणु  530,  5, 106 पूर्ण, अणु  532,  7,  76 पूर्ण,
	अणु  540,  5, 108 पूर्ण, अणु  546,  7,  78 पूर्ण, अणु  550, 11,  50 पूर्ण,
	अणु  552,  6,  92 पूर्ण, अणु  558,  9,  62 पूर्ण, अणु  560,  5, 112 पूर्ण,
	अणु  564,  6,  94 पूर्ण, अणु  570,  5, 114 पूर्ण, अणु  572, 11,  52 पूर्ण,
	अणु  574,  7,  82 पूर्ण, अणु  576,  6,  96 पूर्ण, अणु  580,  5, 116 पूर्ण,
	अणु  588,  6,  98 पूर्ण, अणु  590,  5, 118 पूर्ण, अणु  594, 11,  54 पूर्ण,
	अणु  600,  5, 120 पूर्ण, अणु  602,  7,  86 पूर्ण, अणु  610,  5, 122 पूर्ण,
	अणु  612,  6, 102 पूर्ण, अणु  616, 11,  56 पूर्ण, अणु  620,  5, 124 पूर्ण,
	अणु  624,  6, 104 पूर्ण, अणु  630,  5, 126 पूर्ण, अणु  636,  6, 106 पूर्ण,
	अणु  638, 11,  58 पूर्ण, अणु  640,  5, 128 पूर्ण, अणु  644,  7,  92 पूर्ण,
	अणु  648,  6, 108 पूर्ण, अणु  658,  7,  94 पूर्ण, अणु  660, 11,  60 पूर्ण,
	अणु  666,  9,  74 पूर्ण, अणु  672,  6, 112 पूर्ण, अणु  682, 11,  62 पूर्ण,
	अणु  684,  6, 114 पूर्ण, अणु  686,  7,  98 पूर्ण, अणु  696,  6, 116 पूर्ण,
	अणु  700,  7, 100 पूर्ण, अणु  702,  9,  78 पूर्ण, अणु  704, 11,  64 पूर्ण,
	अणु  708,  6, 118 पूर्ण, अणु  714,  7, 102 पूर्ण, अणु  720,  6, 120 पूर्ण,
	अणु  726, 11,  66 पूर्ण, अणु  728,  7, 104 पूर्ण, अणु  732,  6, 122 पूर्ण,
	अणु  738,  9,  82 पूर्ण, अणु  742,  7, 106 पूर्ण, अणु  744,  6, 124 पूर्ण,
	अणु  748, 11,  68 पूर्ण, अणु  756,  6, 126 पूर्ण, अणु  768,  6, 128 पूर्ण,
	अणु  770, 11,  70 पूर्ण, अणु  774,  9,  86 पूर्ण, अणु  784,  7, 112 पूर्ण,
	अणु  792, 11,  72 पूर्ण, अणु  798,  7, 114 पूर्ण, अणु  810,  9,  90 पूर्ण,
	अणु  812,  7, 116 पूर्ण, अणु  814, 11,  74 पूर्ण, अणु  826,  7, 118 पूर्ण,
	अणु  828,  9,  92 पूर्ण, अणु  836, 11,  76 पूर्ण, अणु  840,  7, 120 पूर्ण,
	अणु  846,  9,  94 पूर्ण, अणु  854,  7, 122 पूर्ण, अणु  858, 11,  78 पूर्ण,
	अणु  864,  9,  96 पूर्ण, अणु  868,  7, 124 पूर्ण, अणु  880, 11,  80 पूर्ण,
	अणु  882,  7, 126 पूर्ण, अणु  896,  7, 128 पूर्ण, अणु  900,  9, 100 पूर्ण,
	अणु  902, 11,  82 पूर्ण, अणु  918,  9, 102 पूर्ण, अणु  924, 11,  84 पूर्ण,
	अणु  936,  9, 104 पूर्ण, अणु  946, 11,  86 पूर्ण, अणु  954,  9, 106 पूर्ण,
	अणु  968, 11,  88 पूर्ण, अणु  972,  9, 108 पूर्ण, अणु  990, 11,  90 पूर्ण,
	अणु 1008,  9, 112 पूर्ण, अणु 1012, 11,  92 पूर्ण, अणु 1026,  9, 114 पूर्ण,
	अणु 1034, 11,  94 पूर्ण, अणु 1044,  9, 116 पूर्ण, अणु 1056, 11,  96 पूर्ण,
	अणु 1062,  9, 118 पूर्ण, अणु 1078, 11,  98 पूर्ण, अणु 1080,  9, 120 पूर्ण,
	अणु 1098,  9, 122 पूर्ण, अणु 1100, 11, 100 पूर्ण, अणु 1116,  9, 124 पूर्ण,
	अणु 1122, 11, 102 पूर्ण, अणु 1134,  9, 126 पूर्ण, अणु 1144, 11, 104 पूर्ण,
	अणु 1152,  9, 128 पूर्ण, अणु 1166, 11, 106 पूर्ण, अणु 1188, 11, 108 पूर्ण,
	अणु 1210, 11, 110 पूर्ण, अणु 1232, 11, 112 पूर्ण, अणु 1254, 11, 114 पूर्ण,
	अणु 1276, 11, 116 पूर्ण, अणु 1298, 11, 118 पूर्ण, अणु 1320, 11, 120 पूर्ण,
	अणु 1342, 11, 122 पूर्ण, अणु 1364, 11, 124 पूर्ण, अणु 1386, 11, 126 पूर्ण,
	अणु 1408, 11, 128 पूर्ण,
पूर्ण;

bool cobalt_cpld_set_freq(काष्ठा cobalt *cobalt, अचिन्हित f_out)
अणु
	स्थिर अचिन्हित f_xtal = 39170000;	/* xtal क्रम si598 */
	u64 dco;
	u64 rfreq;
	अचिन्हित delta = 0xffffffff;
	अचिन्हित i_best = 0;
	अचिन्हित i;
	u8 n1, hsभाग;
	u8 regs[6];
	पूर्णांक found = 0;
	u16 घड़ी_ctrl;
	पूर्णांक retries = 3;

	क्रम (i = 0; i < ARRAY_SIZE(multipliers); i++) अणु
		अचिन्हित mult = multipliers[i].mult;
		u32 d;

		dco = (u64)f_out * mult;
		अगर (dco < DCO_MIN || dco > DCO_MAX)
			जारी;
		भाग_u64_rem((dco << 28) + f_xtal / 2, f_xtal, &d);
		अगर (d < delta) अणु
			found = 1;
			i_best = i;
			delta = d;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस false;
	dco = (u64)f_out * multipliers[i_best].mult;
	n1 = multipliers[i_best].n1 - 1;
	hsभाग = multipliers[i_best].hsभाग - 4;
	rfreq = भाग_u64(dco << 28, f_xtal);

	घड़ी_ctrl = cpld_पढ़ो(cobalt, SI570_CLOCK_CTRL);
	घड़ी_ctrl |= S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL;
	घड़ी_ctrl |= S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN;

	regs[0] = (hsभाग << 5) | (n1 >> 2);
	regs[1] = ((n1 & 0x3) << 6) | (rfreq >> 32);
	regs[2] = (rfreq >> 24) & 0xff;
	regs[3] = (rfreq >> 16) & 0xff;
	regs[4] = (rfreq >> 8) & 0xff;
	regs[5] = rfreq & 0xff;

	/* The sequence of घड़ी_ctrl flags to set is very weird. It looks
	   like I have to reset it, then set the new frequency and reset it
	   again. It shouldn't be necessary to do a reset, but if I don't,
	   then a strange frequency is set (156.412034 MHz, or रेजिस्टर values
	   0x01, 0xc7, 0xfc, 0x7f, 0x53, 0x62).
	 */

	cobalt_dbg(1, "%u: %6ph\n", f_out, regs);

	जबतक (retries--) अणु
		u8 पढ़ो_regs[6];

		cpld_ग_लिखो(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL);
		usleep_range(10000, 15000);
		cpld_ग_लिखो(cobalt, SI570_REG7, regs[0]);
		cpld_ग_लिखो(cobalt, SI570_REG8, regs[1]);
		cpld_ग_लिखो(cobalt, SI570_REG9, regs[2]);
		cpld_ग_लिखो(cobalt, SI570_REG10, regs[3]);
		cpld_ग_लिखो(cobalt, SI570_REG11, regs[4]);
		cpld_ग_लिखो(cobalt, SI570_REG12, regs[5]);
		cpld_ग_लिखो(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_WR_TRIGGER);
		usleep_range(10000, 15000);
		cpld_ग_लिखो(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL);
		usleep_range(10000, 15000);
		पढ़ो_regs[0] = cpld_पढ़ो(cobalt, SI570_REG7);
		पढ़ो_regs[1] = cpld_पढ़ो(cobalt, SI570_REG8);
		पढ़ो_regs[2] = cpld_पढ़ो(cobalt, SI570_REG9);
		पढ़ो_regs[3] = cpld_पढ़ो(cobalt, SI570_REG10);
		पढ़ो_regs[4] = cpld_पढ़ो(cobalt, SI570_REG11);
		पढ़ो_regs[5] = cpld_पढ़ो(cobalt, SI570_REG12);
		cpld_ग_लिखो(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_FPGA_CTRL |
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_RST_TRIGGER);
		usleep_range(10000, 15000);
		cpld_ग_लिखो(cobalt, SI570_CLOCK_CTRL,
			S01755_REG_CLOCK_CTRL_BITMAP_CLKHSMA_EN);
		usleep_range(10000, 15000);

		अगर (!स_भेद(पढ़ो_regs, regs, माप(पढ़ो_regs)))
			अवरोध;
		cobalt_dbg(1, "retry: %6ph\n", पढ़ो_regs);
	पूर्ण
	अगर (2 - retries)
		cobalt_info("Needed %d retries\n", 2 - retries);

	वापस true;
पूर्ण
