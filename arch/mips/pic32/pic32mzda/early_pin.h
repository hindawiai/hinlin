<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#अगर_अघोषित _PIC32MZDA_EARLY_PIN_H
#घोषणा _PIC32MZDA_EARLY_PIN_H

/*
 * This is a complete, yet overly simplistic and unoptimized, PIC32MZDA PPS
 * configuration only useful beक्रमe we have full pinctrl initialized.
 */

/* Input PPS Functions */
क्रमागत अणु
	IN_FUNC_INT3,
	IN_FUNC_T2CK,
	IN_FUNC_T6CK,
	IN_FUNC_IC3,
	IN_FUNC_IC7,
	IN_FUNC_U1RX,
	IN_FUNC_U2CTS,
	IN_FUNC_U5RX,
	IN_FUNC_U6CTS,
	IN_FUNC_SDI1,
	IN_FUNC_SDI3,
	IN_FUNC_SDI5,
	IN_FUNC_SS6,
	IN_FUNC_REFCLKI1,
	IN_FUNC_INT4,
	IN_FUNC_T5CK,
	IN_FUNC_T7CK,
	IN_FUNC_IC4,
	IN_FUNC_IC8,
	IN_FUNC_U3RX,
	IN_FUNC_U4CTS,
	IN_FUNC_SDI2,
	IN_FUNC_SDI4,
	IN_FUNC_C1RX,
	IN_FUNC_REFCLKI4,
	IN_FUNC_INT2,
	IN_FUNC_T3CK,
	IN_FUNC_T8CK,
	IN_FUNC_IC2,
	IN_FUNC_IC5,
	IN_FUNC_IC9,
	IN_FUNC_U1CTS,
	IN_FUNC_U2RX,
	IN_FUNC_U5CTS,
	IN_FUNC_SS1,
	IN_FUNC_SS3,
	IN_FUNC_SS4,
	IN_FUNC_SS5,
	IN_FUNC_C2RX,
	IN_FUNC_INT1,
	IN_FUNC_T4CK,
	IN_FUNC_T9CK,
	IN_FUNC_IC1,
	IN_FUNC_IC6,
	IN_FUNC_U3CTS,
	IN_FUNC_U4RX,
	IN_FUNC_U6RX,
	IN_FUNC_SS2,
	IN_FUNC_SDI6,
	IN_FUNC_OCFA,
	IN_FUNC_REFCLKI3,
पूर्ण;

/* Input PPS Pins */
#घोषणा IN_RPD2 0x00
#घोषणा IN_RPG8 0x01
#घोषणा IN_RPF4 0x02
#घोषणा IN_RPD10 0x03
#घोषणा IN_RPF1 0x04
#घोषणा IN_RPB9 0x05
#घोषणा IN_RPB10 0x06
#घोषणा IN_RPC14 0x07
#घोषणा IN_RPB5 0x08
#घोषणा IN_RPC1 0x0A
#घोषणा IN_RPD14 0x0B
#घोषणा IN_RPG1 0x0C
#घोषणा IN_RPA14 0x0D
#घोषणा IN_RPD6 0x0E
#घोषणा IN_RPD3 0x00
#घोषणा IN_RPG7 0x01
#घोषणा IN_RPF5 0x02
#घोषणा IN_RPD11 0x03
#घोषणा IN_RPF0 0x04
#घोषणा IN_RPB1 0x05
#घोषणा IN_RPE5 0x06
#घोषणा IN_RPC13 0x07
#घोषणा IN_RPB3 0x08
#घोषणा IN_RPC4 0x0A
#घोषणा IN_RPD15 0x0B
#घोषणा IN_RPG0 0x0C
#घोषणा IN_RPA15 0x0D
#घोषणा IN_RPD7 0x0E
#घोषणा IN_RPD9 0x00
#घोषणा IN_RPG6 0x01
#घोषणा IN_RPB8 0x02
#घोषणा IN_RPB15 0x03
#घोषणा IN_RPD4 0x04
#घोषणा IN_RPB0 0x05
#घोषणा IN_RPE3 0x06
#घोषणा IN_RPB7 0x07
#घोषणा IN_RPF12 0x09
#घोषणा IN_RPD12 0x0A
#घोषणा IN_RPF8 0x0B
#घोषणा IN_RPC3 0x0C
#घोषणा IN_RPE9 0x0D
#घोषणा IN_RPD1 0x00
#घोषणा IN_RPG9 0x01
#घोषणा IN_RPB14 0x02
#घोषणा IN_RPD0 0x03
#घोषणा IN_RPB6 0x05
#घोषणा IN_RPD5 0x06
#घोषणा IN_RPB2 0x07
#घोषणा IN_RPF3 0x08
#घोषणा IN_RPF13 0x09
#घोषणा IN_RPF2 0x0B
#घोषणा IN_RPC2 0x0C
#घोषणा IN_RPE8 0x0D

/* Output PPS Pins */
क्रमागत अणु
	OUT_RPD2,
	OUT_RPG8,
	OUT_RPF4,
	OUT_RPD10,
	OUT_RPF1,
	OUT_RPB9,
	OUT_RPB10,
	OUT_RPC14,
	OUT_RPB5,
	OUT_RPC1,
	OUT_RPD14,
	OUT_RPG1,
	OUT_RPA14,
	OUT_RPD6,
	OUT_RPD3,
	OUT_RPG7,
	OUT_RPF5,
	OUT_RPD11,
	OUT_RPF0,
	OUT_RPB1,
	OUT_RPE5,
	OUT_RPC13,
	OUT_RPB3,
	OUT_RPC4,
	OUT_RPD15,
	OUT_RPG0,
	OUT_RPA15,
	OUT_RPD7,
	OUT_RPD9,
	OUT_RPG6,
	OUT_RPB8,
	OUT_RPB15,
	OUT_RPD4,
	OUT_RPB0,
	OUT_RPE3,
	OUT_RPB7,
	OUT_RPF12,
	OUT_RPD12,
	OUT_RPF8,
	OUT_RPC3,
	OUT_RPE9,
	OUT_RPD1,
	OUT_RPG9,
	OUT_RPB14,
	OUT_RPD0,
	OUT_RPB6,
	OUT_RPD5,
	OUT_RPB2,
	OUT_RPF3,
	OUT_RPF13,
	OUT_RPC2,
	OUT_RPE8,
	OUT_RPF2,
पूर्ण;

/* Output PPS Functions */
#घोषणा OUT_FUNC_U3TX 0x01
#घोषणा OUT_FUNC_U4RTS 0x02
#घोषणा OUT_FUNC_SDO1 0x05
#घोषणा OUT_FUNC_SDO2 0x06
#घोषणा OUT_FUNC_SDO3 0x07
#घोषणा OUT_FUNC_SDO5 0x09
#घोषणा OUT_FUNC_SS6 0x0A
#घोषणा OUT_FUNC_OC3 0x0B
#घोषणा OUT_FUNC_OC6 0x0C
#घोषणा OUT_FUNC_REFCLKO4 0x0D
#घोषणा OUT_FUNC_C2OUT 0x0E
#घोषणा OUT_FUNC_C1TX 0x0F
#घोषणा OUT_FUNC_U1TX 0x01
#घोषणा OUT_FUNC_U2RTS 0x02
#घोषणा OUT_FUNC_U5TX 0x03
#घोषणा OUT_FUNC_U6RTS 0x04
#घोषणा OUT_FUNC_SDO1 0x05
#घोषणा OUT_FUNC_SDO2 0x06
#घोषणा OUT_FUNC_SDO3 0x07
#घोषणा OUT_FUNC_SDO4 0x08
#घोषणा OUT_FUNC_SDO5 0x09
#घोषणा OUT_FUNC_OC4 0x0B
#घोषणा OUT_FUNC_OC7 0x0C
#घोषणा OUT_FUNC_REFCLKO1 0x0F
#घोषणा OUT_FUNC_U3RTS 0x01
#घोषणा OUT_FUNC_U4TX 0x02
#घोषणा OUT_FUNC_U6TX 0x04
#घोषणा OUT_FUNC_SS1 0x05
#घोषणा OUT_FUNC_SS3 0x07
#घोषणा OUT_FUNC_SS4 0x08
#घोषणा OUT_FUNC_SS5 0x09
#घोषणा OUT_FUNC_SDO6 0x0A
#घोषणा OUT_FUNC_OC5 0x0B
#घोषणा OUT_FUNC_OC8 0x0C
#घोषणा OUT_FUNC_C1OUT 0x0E
#घोषणा OUT_FUNC_REFCLKO3 0x0F
#घोषणा OUT_FUNC_U1RTS 0x01
#घोषणा OUT_FUNC_U2TX 0x02
#घोषणा OUT_FUNC_U5RTS 0x03
#घोषणा OUT_FUNC_U6TX 0x04
#घोषणा OUT_FUNC_SS2 0x06
#घोषणा OUT_FUNC_SDO4 0x08
#घोषणा OUT_FUNC_SDO6 0x0A
#घोषणा OUT_FUNC_OC2 0x0B
#घोषणा OUT_FUNC_OC1 0x0C
#घोषणा OUT_FUNC_OC9 0x0D
#घोषणा OUT_FUNC_C2TX 0x0F

व्योम pic32_pps_input(पूर्णांक function, पूर्णांक pin);
व्योम pic32_pps_output(पूर्णांक function, पूर्णांक pin);

#पूर्ण_अगर
