<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause) */
/*
 * Copyright (C) STMicroelectronics 2017 - All Rights Reserved
 * Author: Torgue Alexandre <alexandre.torgue@st.com> क्रम STMicroelectronics.
 */

#अगर_अघोषित _DT_BINDINGS_STM32_PINFUNC_H
#घोषणा _DT_BINDINGS_STM32_PINFUNC_H

/*  define PIN modes */
#घोषणा GPIO	0x0
#घोषणा AF0	0x1
#घोषणा AF1	0x2
#घोषणा AF2	0x3
#घोषणा AF3	0x4
#घोषणा AF4	0x5
#घोषणा AF5	0x6
#घोषणा AF6	0x7
#घोषणा AF7	0x8
#घोषणा AF8	0x9
#घोषणा AF9	0xa
#घोषणा AF10	0xb
#घोषणा AF11	0xc
#घोषणा AF12	0xd
#घोषणा AF13	0xe
#घोषणा AF14	0xf
#घोषणा AF15	0x10
#घोषणा ANALOG	0x11

/* define Pins number*/
#घोषणा PIN_NO(port, line)	(((port) - 'A') * 0x10 + (line))

#घोषणा STM32_PINMUX(port, line, mode) (((PIN_NO(port, line)) << 8) | (mode))

/*  package inक्रमmation */
#घोषणा STM32MP_PKG_AA	0x1
#घोषणा STM32MP_PKG_AB	0x2
#घोषणा STM32MP_PKG_AC	0x4
#घोषणा STM32MP_PKG_AD	0x8

#पूर्ण_अगर /* _DT_BINDINGS_STM32_PINFUNC_H */

