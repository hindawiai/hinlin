<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  NXP (Philips) SCC+++(SCN+++) serial driver
 *
 *  Copyright (C) 2012 Alexander Shiyan <shc_work@mail.ru>
 *
 *  Based on sc26xx.c, by Thomas Bogendथघrfer (tsbogend@alpha.franken.de)
 */

#अगर_अघोषित _PLATFORM_DATA_SERIAL_SCCNXP_H_
#घोषणा _PLATFORM_DATA_SERIAL_SCCNXP_H_

#घोषणा SCCNXP_MAX_UARTS	2

/* Output lines */
#घोषणा LINE_OP0		1
#घोषणा LINE_OP1		2
#घोषणा LINE_OP2		3
#घोषणा LINE_OP3		4
#घोषणा LINE_OP4		5
#घोषणा LINE_OP5		6
#घोषणा LINE_OP6		7
#घोषणा LINE_OP7		8

/* Input lines */
#घोषणा LINE_IP0		9
#घोषणा LINE_IP1		10
#घोषणा LINE_IP2		11
#घोषणा LINE_IP3		12
#घोषणा LINE_IP4		13
#घोषणा LINE_IP5		14
#घोषणा LINE_IP6		15

/* Signals */
#घोषणा DTR_OP			0	/* DTR */
#घोषणा RTS_OP			4	/* RTS */
#घोषणा DSR_IP			8	/* DSR */
#घोषणा CTS_IP			12	/* CTS */
#घोषणा DCD_IP			16	/* DCD */
#घोषणा RNG_IP			20	/* RNG */

#घोषणा सूची_OP			24	/* Special संकेत क्रम control RS-485.
					 * Goes high when transmit,
					 * then goes low.
					 */

/* Routing control संकेत 'sig' to line 'line' */
#घोषणा MCTRL_SIG(sig, line)	((line) << (sig))

/*
 * Example board initialization data:
 *
 * अटल काष्ठा resource sc2892_resources[] = अणु
 *	DEFINE_RES_MEM(UART_PHYS_START, 0x10),
 *	DEFINE_RES_IRQ(IRQ_EXT2),
 * पूर्ण;
 *
 * अटल काष्ठा sccnxp_pdata sc2892_info = अणु
 *	.mctrl_cfg[0]	= MCTRL_SIG(सूची_OP, LINE_OP0),
 *	.mctrl_cfg[1]	= MCTRL_SIG(सूची_OP, LINE_OP1),
 * पूर्ण;
 *
 * अटल काष्ठा platक्रमm_device sc2892 = अणु
 *	.name		= "sc2892",
 *	.id		= -1,
 *	.resource	= sc2892_resources,
 *	.num_resources	= ARRAY_SIZE(sc2892_resources),
 *	.dev = अणु
 *		.platक्रमm_data	= &sc2892_info,
 *	पूर्ण,
 * पूर्ण;
 */

/* SCCNXP platक्रमm data काष्ठाure */
काष्ठा sccnxp_pdata अणु
	/* Shअगरt क्रम A0 line */
	स्थिर u8		reg_shअगरt;
	/* Modem control lines configuration */
	स्थिर u32		mctrl_cfg[SCCNXP_MAX_UARTS];
	/* Timer value क्रम polling mode (usecs) */
	स्थिर अचिन्हित पूर्णांक	poll_समय_us;
पूर्ण;

#पूर्ण_अगर
