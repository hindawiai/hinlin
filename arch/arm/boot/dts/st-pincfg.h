<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ST_PINCFG_H_
#घोषणा _ST_PINCFG_H_

/* Alternate functions */
#घोषणा ALT1	1
#घोषणा ALT2	2
#घोषणा ALT3	3
#घोषणा ALT4	4
#घोषणा ALT5	5
#घोषणा ALT6	6
#घोषणा ALT7	7

/* Output enable */
#घोषणा OE			(1 << 27)
/* Pull Up */
#घोषणा PU			(1 << 26)
/* Open Drain */
#घोषणा OD			(1 << 25)
#घोषणा RT			(1 << 23)
#घोषणा INVERTCLK		(1 << 22)
#घोषणा CLKNOTDATA		(1 << 21)
#घोषणा DOUBLE_EDGE		(1 << 20)
#घोषणा CLK_A			(0 << 18)
#घोषणा CLK_B			(1 << 18)
#घोषणा CLK_C			(2 << 18)
#घोषणा CLK_D			(3 << 18)

/* User-frendly defines क्रम Pin Direction */
		/* oe = 0, pu = 0, od = 0 */
#घोषणा IN			(0)
		/* oe = 0, pu = 1, od = 0 */
#घोषणा IN_PU			(PU)
		/* oe = 1, pu = 0, od = 0 */
#घोषणा OUT			(OE)
		/* oe = 1, pu = 0, od = 1 */
#घोषणा BIसूची			(OE | OD)
		/* oe = 1, pu = 1, od = 1 */
#घोषणा BIसूची_PU		(OE | PU | OD)

/* RETIME_TYPE */
/*
 * B Mode
 * Bypass reसमय with optional delay parameter
 */
#घोषणा BYPASS		(0)
/*
 * R0, R1, R0D, R1D modes
 * single-edge data non inverted घड़ी, reसमय data with clk
 */
#घोषणा SE_NICLK_IO	(RT)
/*
 * RIV0, RIV1, RIV0D, RIV1D modes
 * single-edge data inverted घड़ी, reसमय data with clk
 */
#घोषणा SE_ICLK_IO	(RT | INVERTCLK)
/*
 * R0E, R1E, R0ED, R1ED modes
 * द्विगुन-edge data, reसमय data with clk
 */
#घोषणा DE_IO		(RT | DOUBLE_EDGE)
/*
 * CIV0, CIV1 modes with inverted घड़ी
 * Retiming the clk pins will park घड़ी & reduce the noise within the core.
 */
#घोषणा ICLK		(RT | CLKNOTDATA | INVERTCLK)
/*
 * CLK0, CLK1 modes with non-inverted घड़ी
 * Retiming the clk pins will park घड़ी & reduce the noise within the core.
 */
#घोषणा NICLK		(RT | CLKNOTDATA)
#पूर्ण_अगर /* _ST_PINCFG_H_ */
