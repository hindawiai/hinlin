<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <यंत्र/पन.स>

#समावेश "early_pin.h"

#घोषणा PPS_BASE 0x1f800000

/* Input PPS Registers */
#घोषणा INT1R 0x1404
#घोषणा INT2R 0x1408
#घोषणा INT3R 0x140C
#घोषणा INT4R 0x1410
#घोषणा T2CKR 0x1418
#घोषणा T3CKR 0x141C
#घोषणा T4CKR 0x1420
#घोषणा T5CKR 0x1424
#घोषणा T6CKR 0x1428
#घोषणा T7CKR 0x142C
#घोषणा T8CKR 0x1430
#घोषणा T9CKR 0x1434
#घोषणा IC1R 0x1438
#घोषणा IC2R 0x143C
#घोषणा IC3R 0x1440
#घोषणा IC4R 0x1444
#घोषणा IC5R 0x1448
#घोषणा IC6R 0x144C
#घोषणा IC7R 0x1450
#घोषणा IC8R 0x1454
#घोषणा IC9R 0x1458
#घोषणा OCFAR 0x1460
#घोषणा U1RXR 0x1468
#घोषणा U1CTSR 0x146C
#घोषणा U2RXR 0x1470
#घोषणा U2CTSR 0x1474
#घोषणा U3RXR 0x1478
#घोषणा U3CTSR 0x147C
#घोषणा U4RXR 0x1480
#घोषणा U4CTSR 0x1484
#घोषणा U5RXR 0x1488
#घोषणा U5CTSR 0x148C
#घोषणा U6RXR 0x1490
#घोषणा U6CTSR 0x1494
#घोषणा SDI1R 0x149C
#घोषणा SS1R 0x14A0
#घोषणा SDI2R 0x14A8
#घोषणा SS2R 0x14AC
#घोषणा SDI3R 0x14B4
#घोषणा SS3R 0x14B8
#घोषणा SDI4R 0x14C0
#घोषणा SS4R 0x14C4
#घोषणा SDI5R 0x14CC
#घोषणा SS5R 0x14D0
#घोषणा SDI6R 0x14D8
#घोषणा SS6R 0x14DC
#घोषणा C1RXR 0x14E0
#घोषणा C2RXR 0x14E4
#घोषणा REFCLKI1R 0x14E8
#घोषणा REFCLKI3R 0x14F0
#घोषणा REFCLKI4R 0x14F4

अटल स्थिर काष्ठा
अणु
	पूर्णांक function;
	पूर्णांक reg;
पूर्ण input_pin_reg[] = अणु
	अणु IN_FUNC_INT3, INT3R पूर्ण,
	अणु IN_FUNC_T2CK, T2CKR पूर्ण,
	अणु IN_FUNC_T6CK, T6CKR पूर्ण,
	अणु IN_FUNC_IC3, IC3R  पूर्ण,
	अणु IN_FUNC_IC7, IC7R पूर्ण,
	अणु IN_FUNC_U1RX, U1RXR पूर्ण,
	अणु IN_FUNC_U2CTS, U2CTSR पूर्ण,
	अणु IN_FUNC_U5RX, U5RXR पूर्ण,
	अणु IN_FUNC_U6CTS, U6CTSR पूर्ण,
	अणु IN_FUNC_SDI1, SDI1R पूर्ण,
	अणु IN_FUNC_SDI3, SDI3R पूर्ण,
	अणु IN_FUNC_SDI5, SDI5R पूर्ण,
	अणु IN_FUNC_SS6, SS6R पूर्ण,
	अणु IN_FUNC_REFCLKI1, REFCLKI1R पूर्ण,
	अणु IN_FUNC_INT4, INT4R पूर्ण,
	अणु IN_FUNC_T5CK, T5CKR पूर्ण,
	अणु IN_FUNC_T7CK, T7CKR पूर्ण,
	अणु IN_FUNC_IC4, IC4R पूर्ण,
	अणु IN_FUNC_IC8, IC8R पूर्ण,
	अणु IN_FUNC_U3RX, U3RXR पूर्ण,
	अणु IN_FUNC_U4CTS, U4CTSR पूर्ण,
	अणु IN_FUNC_SDI2, SDI2R पूर्ण,
	अणु IN_FUNC_SDI4, SDI4R पूर्ण,
	अणु IN_FUNC_C1RX, C1RXR पूर्ण,
	अणु IN_FUNC_REFCLKI4, REFCLKI4R पूर्ण,
	अणु IN_FUNC_INT2, INT2R पूर्ण,
	अणु IN_FUNC_T3CK, T3CKR पूर्ण,
	अणु IN_FUNC_T8CK, T8CKR पूर्ण,
	अणु IN_FUNC_IC2, IC2R पूर्ण,
	अणु IN_FUNC_IC5, IC5R पूर्ण,
	अणु IN_FUNC_IC9, IC9R पूर्ण,
	अणु IN_FUNC_U1CTS, U1CTSR पूर्ण,
	अणु IN_FUNC_U2RX, U2RXR पूर्ण,
	अणु IN_FUNC_U5CTS, U5CTSR पूर्ण,
	अणु IN_FUNC_SS1, SS1R पूर्ण,
	अणु IN_FUNC_SS3, SS3R पूर्ण,
	अणु IN_FUNC_SS4, SS4R पूर्ण,
	अणु IN_FUNC_SS5, SS5R पूर्ण,
	अणु IN_FUNC_C2RX, C2RXR पूर्ण,
	अणु IN_FUNC_INT1, INT1R पूर्ण,
	अणु IN_FUNC_T4CK, T4CKR पूर्ण,
	अणु IN_FUNC_T9CK, T9CKR पूर्ण,
	अणु IN_FUNC_IC1, IC1R पूर्ण,
	अणु IN_FUNC_IC6, IC6R पूर्ण,
	अणु IN_FUNC_U3CTS, U3CTSR पूर्ण,
	अणु IN_FUNC_U4RX, U4RXR पूर्ण,
	अणु IN_FUNC_U6RX, U6RXR पूर्ण,
	अणु IN_FUNC_SS2, SS2R पूर्ण,
	अणु IN_FUNC_SDI6, SDI6R पूर्ण,
	अणु IN_FUNC_OCFA, OCFAR पूर्ण,
	अणु IN_FUNC_REFCLKI3, REFCLKI3R पूर्ण,
पूर्ण;

व्योम pic32_pps_input(पूर्णांक function, पूर्णांक pin)
अणु
	व्योम __iomem *pps_base = ioremap(PPS_BASE, 0xF4);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(input_pin_reg); i++) अणु
		अगर (input_pin_reg[i].function == function) अणु
			__raw_ग_लिखोl(pin, pps_base + input_pin_reg[i].reg);
			वापस;
		पूर्ण
	पूर्ण

	iounmap(pps_base);
पूर्ण

/* Output PPS Registers */
#घोषणा RPA14R 0x1538
#घोषणा RPA15R 0x153C
#घोषणा RPB0R 0x1540
#घोषणा RPB1R 0x1544
#घोषणा RPB2R 0x1548
#घोषणा RPB3R 0x154C
#घोषणा RPB5R 0x1554
#घोषणा RPB6R 0x1558
#घोषणा RPB7R 0x155C
#घोषणा RPB8R 0x1560
#घोषणा RPB9R 0x1564
#घोषणा RPB10R 0x1568
#घोषणा RPB14R 0x1578
#घोषणा RPB15R 0x157C
#घोषणा RPC1R 0x1584
#घोषणा RPC2R 0x1588
#घोषणा RPC3R 0x158C
#घोषणा RPC4R 0x1590
#घोषणा RPC13R 0x15B4
#घोषणा RPC14R 0x15B8
#घोषणा RPD0R 0x15C0
#घोषणा RPD1R 0x15C4
#घोषणा RPD2R 0x15C8
#घोषणा RPD3R 0x15CC
#घोषणा RPD4R 0x15D0
#घोषणा RPD5R 0x15D4
#घोषणा RPD6R 0x15D8
#घोषणा RPD7R 0x15DC
#घोषणा RPD9R 0x15E4
#घोषणा RPD10R 0x15E8
#घोषणा RPD11R 0x15EC
#घोषणा RPD12R 0x15F0
#घोषणा RPD14R 0x15F8
#घोषणा RPD15R 0x15FC
#घोषणा RPE3R 0x160C
#घोषणा RPE5R 0x1614
#घोषणा RPE8R 0x1620
#घोषणा RPE9R 0x1624
#घोषणा RPF0R 0x1640
#घोषणा RPF1R 0x1644
#घोषणा RPF2R 0x1648
#घोषणा RPF3R 0x164C
#घोषणा RPF4R 0x1650
#घोषणा RPF5R 0x1654
#घोषणा RPF8R 0x1660
#घोषणा RPF12R 0x1670
#घोषणा RPF13R 0x1674
#घोषणा RPG0R 0x1680
#घोषणा RPG1R 0x1684
#घोषणा RPG6R 0x1698
#घोषणा RPG7R 0x169C
#घोषणा RPG8R 0x16A0
#घोषणा RPG9R 0x16A4

अटल स्थिर काष्ठा
अणु
	पूर्णांक pin;
	पूर्णांक reg;
पूर्ण output_pin_reg[] = अणु
	अणु OUT_RPD2, RPD2R पूर्ण,
	अणु OUT_RPG8, RPG8R पूर्ण,
	अणु OUT_RPF4, RPF4R पूर्ण,
	अणु OUT_RPD10, RPD10R पूर्ण,
	अणु OUT_RPF1, RPF1R पूर्ण,
	अणु OUT_RPB9, RPB9R पूर्ण,
	अणु OUT_RPB10, RPB10R पूर्ण,
	अणु OUT_RPC14, RPC14R पूर्ण,
	अणु OUT_RPB5, RPB5R पूर्ण,
	अणु OUT_RPC1, RPC1R पूर्ण,
	अणु OUT_RPD14, RPD14R पूर्ण,
	अणु OUT_RPG1, RPG1R पूर्ण,
	अणु OUT_RPA14, RPA14R पूर्ण,
	अणु OUT_RPD6, RPD6R पूर्ण,
	अणु OUT_RPD3, RPD3R पूर्ण,
	अणु OUT_RPG7, RPG7R पूर्ण,
	अणु OUT_RPF5, RPF5R पूर्ण,
	अणु OUT_RPD11, RPD11R पूर्ण,
	अणु OUT_RPF0, RPF0R पूर्ण,
	अणु OUT_RPB1, RPB1R पूर्ण,
	अणु OUT_RPE5, RPE5R पूर्ण,
	अणु OUT_RPC13, RPC13R पूर्ण,
	अणु OUT_RPB3, RPB3R पूर्ण,
	अणु OUT_RPC4, RPC4R पूर्ण,
	अणु OUT_RPD15, RPD15R पूर्ण,
	अणु OUT_RPG0, RPG0R पूर्ण,
	अणु OUT_RPA15, RPA15R पूर्ण,
	अणु OUT_RPD7, RPD7R पूर्ण,
	अणु OUT_RPD9, RPD9R पूर्ण,
	अणु OUT_RPG6, RPG6R पूर्ण,
	अणु OUT_RPB8, RPB8R पूर्ण,
	अणु OUT_RPB15, RPB15R पूर्ण,
	अणु OUT_RPD4, RPD4R पूर्ण,
	अणु OUT_RPB0, RPB0R पूर्ण,
	अणु OUT_RPE3, RPE3R पूर्ण,
	अणु OUT_RPB7, RPB7R पूर्ण,
	अणु OUT_RPF12, RPF12R पूर्ण,
	अणु OUT_RPD12, RPD12R पूर्ण,
	अणु OUT_RPF8, RPF8R पूर्ण,
	अणु OUT_RPC3, RPC3R पूर्ण,
	अणु OUT_RPE9, RPE9R पूर्ण,
	अणु OUT_RPD1, RPD1R पूर्ण,
	अणु OUT_RPG9, RPG9R पूर्ण,
	अणु OUT_RPB14, RPB14R पूर्ण,
	अणु OUT_RPD0, RPD0R पूर्ण,
	अणु OUT_RPB6, RPB6R पूर्ण,
	अणु OUT_RPD5, RPD5R पूर्ण,
	अणु OUT_RPB2, RPB2R पूर्ण,
	अणु OUT_RPF3, RPF3R पूर्ण,
	अणु OUT_RPF13, RPF13R पूर्ण,
	अणु OUT_RPC2, RPC2R पूर्ण,
	अणु OUT_RPE8, RPE8R पूर्ण,
	अणु OUT_RPF2, RPF2R पूर्ण,
पूर्ण;

व्योम pic32_pps_output(पूर्णांक function, पूर्णांक pin)
अणु
	व्योम __iomem *pps_base = ioremap(PPS_BASE, 0x170);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(output_pin_reg); i++) अणु
		अगर (output_pin_reg[i].pin == pin) अणु
			__raw_ग_लिखोl(function,
				pps_base + output_pin_reg[i].reg);
			वापस;
		पूर्ण
	पूर्ण

	iounmap(pps_base);
पूर्ण
