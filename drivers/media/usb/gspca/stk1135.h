<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * STK1135 रेजिस्टरs
 *
 * Copyright (c) 2013 Ondrej Zary
 */

#घोषणा STK1135_REG_GCTRL	0x000	/* GPIO control */
#घोषणा STK1135_REG_ICTRL	0x004	/* Interrupt control */
#घोषणा STK1135_REG_IDATA	0x008	/* Interrupt data */
#घोषणा STK1135_REG_RMCTL	0x00c	/* Remote wakeup control */
#घोषणा STK1135_REG_POSVA	0x010	/* Power-on strapping data */

#घोषणा STK1135_REG_SENSO	0x018	/* Sensor select options */
#घोषणा STK1135_REG_PLLFD	0x01c	/* PLL frequency भागider */

#घोषणा STK1135_REG_SCTRL	0x100	/* Sensor control रेजिस्टर */
#घोषणा STK1135_REG_DCTRL	0x104	/* Decimation control रेजिस्टर */
#घोषणा STK1135_REG_CISPO	0x110	/* Capture image starting position */
#घोषणा STK1135_REG_CIEPO	0x114	/* Capture image ending position */
#घोषणा STK1135_REG_TCTRL	0x120	/* Test data control */

#घोषणा STK1135_REG_SICTL	0x200	/* Serial पूर्णांकerface control रेजिस्टर */
#घोषणा STK1135_REG_SBUSW	0x204	/* Serial bus ग_लिखो */
#घोषणा STK1135_REG_SBUSR	0x208	/* Serial bus पढ़ो */
#घोषणा STK1135_REG_SCSI	0x20c	/* Software control serial पूर्णांकerface */
#घोषणा STK1135_REG_GSBWP	0x210	/* General serial bus ग_लिखो port */
#घोषणा STK1135_REG_GSBRP	0x214	/* General serial bus पढ़ो port */
#घोषणा STK1135_REG_ASIC	0x2fc	/* Alternate serial पूर्णांकerface control */

#घोषणा STK1135_REG_TMGEN	0x300	/* Timing generator */
#घोषणा STK1135_REG_TCP1	0x350	/* Timing control parameter 1 */

काष्ठा stk1135_pkt_header अणु
	u8 flags;
	u8 seq;
	__le16 gpio;
पूर्ण __packed;

#घोषणा STK1135_HDR_FRAME_START	(1 << 7)
#घोषणा STK1135_HDR_ODD		(1 << 6)
#घोषणा STK1135_HDR_I2C_VBLANK	(1 << 5)

#घोषणा STK1135_HDR_SEQ_MASK	0x3f
