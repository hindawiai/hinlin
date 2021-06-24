<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* include/video/ili9320.c
 *
 * ILI9320 LCD controller configuration control.
 *
 * Copyright 2007 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * http://armlinux.simtec.co.uk/
*/

#घोषणा ILI9320_REG(x)	(x)

#घोषणा ILI9320_INDEX			ILI9320_REG(0x00)

#घोषणा ILI9320_OSCILATION		ILI9320_REG(0x00)
#घोषणा ILI9320_DRIVER			ILI9320_REG(0x01)
#घोषणा ILI9320_DRIVEWAVE		ILI9320_REG(0x02)
#घोषणा ILI9320_ENTRYMODE		ILI9320_REG(0x03)
#घोषणा ILI9320_RESIZING		ILI9320_REG(0x04)
#घोषणा ILI9320_DISPLAY1		ILI9320_REG(0x07)
#घोषणा ILI9320_DISPLAY2		ILI9320_REG(0x08)
#घोषणा ILI9320_DISPLAY3		ILI9320_REG(0x09)
#घोषणा ILI9320_DISPLAY4		ILI9320_REG(0x0A)
#घोषणा ILI9320_RGB_IF1			ILI9320_REG(0x0C)
#घोषणा ILI9320_FRAMEMAKER		ILI9320_REG(0x0D)
#घोषणा ILI9320_RGB_IF2			ILI9320_REG(0x0F)

#घोषणा ILI9320_POWER1			ILI9320_REG(0x10)
#घोषणा ILI9320_POWER2			ILI9320_REG(0x11)
#घोषणा ILI9320_POWER3			ILI9320_REG(0x12)
#घोषणा ILI9320_POWER4			ILI9320_REG(0x13)
#घोषणा ILI9320_GRAM_HORIZ_ADDR		ILI9320_REG(0x20)
#घोषणा ILI9320_GRAM_VERT_ADD		ILI9320_REG(0x21)
#घोषणा ILI9320_POWER7			ILI9320_REG(0x29)
#घोषणा ILI9320_FRAME_RATE_COLOUR	ILI9320_REG(0x2B)

#घोषणा ILI9320_GAMMA1			ILI9320_REG(0x30)
#घोषणा ILI9320_GAMMA2			ILI9320_REG(0x31)
#घोषणा ILI9320_GAMMA3			ILI9320_REG(0x32)
#घोषणा ILI9320_GAMMA4			ILI9320_REG(0x35)
#घोषणा ILI9320_GAMMA5			ILI9320_REG(0x36)
#घोषणा ILI9320_GAMMA6			ILI9320_REG(0x37)
#घोषणा ILI9320_GAMMA7			ILI9320_REG(0x38)
#घोषणा ILI9320_GAMMA8			ILI9320_REG(0x39)
#घोषणा ILI9320_GAMMA9			ILI9320_REG(0x3C)
#घोषणा ILI9320_GAMMA10			ILI9320_REG(0x3D)

#घोषणा ILI9320_HORIZ_START		ILI9320_REG(0x50)
#घोषणा ILI9320_HORIZ_END		ILI9320_REG(0x51)
#घोषणा ILI9320_VERT_START		ILI9320_REG(0x52)
#घोषणा ILI9320_VERT_END		ILI9320_REG(0x53)

#घोषणा ILI9320_DRIVER2			ILI9320_REG(0x60)
#घोषणा ILI9320_BASE_IMAGE		ILI9320_REG(0x61)
#घोषणा ILI9320_VERT_SCROLL		ILI9320_REG(0x6a)

#घोषणा ILI9320_PARTIAL1_POSITION	ILI9320_REG(0x80)
#घोषणा ILI9320_PARTIAL1_START		ILI9320_REG(0x81)
#घोषणा ILI9320_PARTIAL1_END		ILI9320_REG(0x82)
#घोषणा ILI9320_PARTIAL2_POSITION	ILI9320_REG(0x83)
#घोषणा ILI9320_PARTIAL2_START		ILI9320_REG(0x84)
#घोषणा ILI9320_PARTIAL2_END		ILI9320_REG(0x85)

#घोषणा ILI9320_INTERFACE1		ILI9320_REG(0x90)
#घोषणा ILI9320_INTERFACE2		ILI9320_REG(0x92)
#घोषणा ILI9320_INTERFACE3		ILI9320_REG(0x93)
#घोषणा ILI9320_INTERFACE4		ILI9320_REG(0x95)
#घोषणा ILI9320_INTERFACE5		ILI9320_REG(0x97)
#घोषणा ILI9320_INTERFACE6		ILI9320_REG(0x98)

/* Register contents definitions. */

#घोषणा ILI9320_OSCILATION_OSC		(1 << 0)

#घोषणा ILI9320_DRIVER_SS		(1 << 8)
#घोषणा ILI9320_DRIVER_SM		(1 << 10)

#घोषणा ILI9320_DRIVEWAVE_EOR		(1 << 8)
#घोषणा ILI9320_DRIVEWAVE_BC		(1 << 9)
#घोषणा ILI9320_DRIVEWAVE_MUSTSET	(1 << 10)

#घोषणा ILI9320_ENTRYMODE_AM		(1 << 3)
#घोषणा ILI9320_ENTRYMODE_ID(x)		((x) << 4)
#घोषणा ILI9320_ENTRYMODE_ORG		(1 << 7)
#घोषणा ILI9320_ENTRYMODE_HWM		(1 << 8)
#घोषणा ILI9320_ENTRYMODE_BGR		(1 << 12)
#घोषणा ILI9320_ENTRYMODE_DFM		(1 << 14)
#घोषणा ILI9320_ENTRYMODE_TRI		(1 << 15)


#घोषणा ILI9320_RESIZING_RSZ(x)		((x) << 0)
#घोषणा ILI9320_RESIZING_RCH(x)		((x) << 4)
#घोषणा ILI9320_RESIZING_RCV(x)		((x) << 8)


#घोषणा ILI9320_DISPLAY1_D(x)		((x) << 0)
#घोषणा ILI9320_DISPLAY1_CL		(1 << 3)
#घोषणा ILI9320_DISPLAY1_DTE		(1 << 4)
#घोषणा ILI9320_DISPLAY1_GON		(1 << 5)
#घोषणा ILI9320_DISPLAY1_BASEE		(1 << 8)
#घोषणा ILI9320_DISPLAY1_PTDE(x)	((x) << 12)


#घोषणा ILI9320_DISPLAY2_BP(x)		((x) << 0)
#घोषणा ILI9320_DISPLAY2_FP(x)		((x) << 8)


#घोषणा ILI9320_RGBIF1_RIM_RGB18	(0 << 0)
#घोषणा ILI9320_RGBIF1_RIM_RGB16	(1 << 0)
#घोषणा ILI9320_RGBIF1_RIM_RGB6		(2 << 0)

#घोषणा ILI9320_RGBIF1_CLK_INT		(0 << 4)
#घोषणा ILI9320_RGBIF1_CLK_RGBIF	(1 << 4)
#घोषणा ILI9320_RGBIF1_CLK_VSYNC	(2 << 4)

#घोषणा ILI9320_RGBIF1_RM		(1 << 8)

#घोषणा ILI9320_RGBIF1_ENC_FRAMES(x)	(((x) - 1)<< 13)

#घोषणा ILI9320_RGBIF2_DPL		(1 << 0)
#घोषणा ILI9320_RGBIF2_EPL		(1 << 1)
#घोषणा ILI9320_RGBIF2_HSPL		(1 << 3)
#घोषणा ILI9320_RGBIF2_VSPL		(1 << 4)


#घोषणा ILI9320_POWER1_SLP		(1 << 1)
#घोषणा ILI9320_POWER1_DSTB		(1 << 2)
#घोषणा ILI9320_POWER1_AP(x)		((x) << 4)
#घोषणा ILI9320_POWER1_APE		(1 << 7)
#घोषणा ILI9320_POWER1_BT(x)		((x) << 8)
#घोषणा ILI9320_POWER1_SAP		(1 << 12)


#घोषणा ILI9320_POWER2_VC(x)		((x) << 0)
#घोषणा ILI9320_POWER2_DC0(x)		((x) << 4)
#घोषणा ILI9320_POWER2_DC1(x)		((x) << 8)


#घोषणा ILI9320_POWER3_VRH(x)		((x) << 0)
#घोषणा ILI9320_POWER3_PON		(1 << 4)
#घोषणा ILI9320_POWER3_VCMR		(1 << 8)


#घोषणा ILI9320_POWER4_VREOUT(x)	((x) << 8)


#घोषणा ILI9320_DRIVER2_SCNL(x)		((x) << 0)
#घोषणा ILI9320_DRIVER2_NL(x)		((x) << 8)
#घोषणा ILI9320_DRIVER2_GS		(1 << 15)


#घोषणा ILI9320_BASEIMAGE_REV		(1 << 0)
#घोषणा ILI9320_BASEIMAGE_VLE		(1 << 1)
#घोषणा ILI9320_BASEIMAGE_NDL		(1 << 2)


#घोषणा ILI9320_INTERFACE4_RTNE(x)	(x)
#घोषणा ILI9320_INTERFACE4_DIVE(x)	((x) << 8)

/* SPI पूर्णांकerface definitions */

#घोषणा ILI9320_SPI_IDCODE		(0x70)
#घोषणा ILI9320_SPI_ID(x)		((x) << 2)
#घोषणा ILI9320_SPI_READ		(0x01)
#घोषणा ILI9320_SPI_WRITE		(0x00)
#घोषणा ILI9320_SPI_DATA		(0x02)
#घोषणा ILI9320_SPI_INDEX		(0x00)

/* platक्रमm data to pass configuration from lcd */

क्रमागत ili9320_suspend अणु
	ILI9320_SUSPEND_OFF,
	ILI9320_SUSPEND_DEEP,
पूर्ण;

काष्ठा ili9320_platdata अणु
	अचिन्हित लघु	hsize;
	अचिन्हित लघु	vsize;

	क्रमागत ili9320_suspend suspend;

	/* set the reset line, 0 = reset निश्चितed, 1 = normal */
	व्योम		(*reset)(अचिन्हित पूर्णांक val);

	अचिन्हित लघु	entry_mode;
	अचिन्हित लघु	display2;
	अचिन्हित लघु	display3;
	अचिन्हित लघु	display4;
	अचिन्हित लघु	rgb_अगर1;
	अचिन्हित लघु	rgb_अगर2;
	अचिन्हित लघु	पूर्णांकerface2;
	अचिन्हित लघु	पूर्णांकerface3;
	अचिन्हित लघु	पूर्णांकerface4;
	अचिन्हित लघु	पूर्णांकerface5;
	अचिन्हित लघु	पूर्णांकerface6;
पूर्ण;

