<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Realtek RTL28xxU DVB USB driver
 *
 * Copyright (C) 2009 Antti Palosaari <crope@iki.fi>
 * Copyright (C) 2011 Antti Palosaari <crope@iki.fi>
 */

#अगर_अघोषित RTL28XXU_H
#घोषणा RTL28XXU_H

#समावेश <linux/platक्रमm_device.h>

#समावेश "dvb_usb.h"

#समावेश "rtl2830.h"
#समावेश "rtl2832.h"
#समावेश "rtl2832_sdr.h"
#समावेश "mn88472.h"
#समावेश "mn88473.h"
#समावेश "cxd2841er.h"

#समावेश "qt1010.h"
#समावेश "mt2060.h"
#समावेश "mxl5005s.h"
#समावेश "fc0012.h"
#समावेश "fc0013.h"
#समावेश "e4000.h"
#समावेश "fc2580.h"
#समावेश "tua9001.h"
#समावेश "r820t.h"
#समावेश "si2168.h"
#समावेश "si2157.h"

/*
 * USB commands
 * (usb_control_msg() index parameter)
 */

#घोषणा DEMOD            0x0000
#घोषणा USB              0x0100
#घोषणा SYS              0x0200
#घोषणा I2C              0x0300
#घोषणा I2C_DA           0x0600

#घोषणा CMD_WR_FLAG      0x0010
#घोषणा CMD_DEMOD_RD     0x0000
#घोषणा CMD_DEMOD_WR     0x0010
#घोषणा CMD_USB_RD       0x0100
#घोषणा CMD_USB_WR       0x0110
#घोषणा CMD_SYS_RD       0x0200
#घोषणा CMD_IR_RD        0x0201
#घोषणा CMD_IR_WR        0x0211
#घोषणा CMD_SYS_WR       0x0210
#घोषणा CMD_I2C_RD       0x0300
#घोषणा CMD_I2C_WR       0x0310
#घोषणा CMD_I2C_DA_RD    0x0600
#घोषणा CMD_I2C_DA_WR    0x0610


काष्ठा rtl28xxu_dev अणु
	u8 buf[128];
	u8 chip_id;
	u8 tuner;
	अक्षर *tuner_name;
	u8 page; /* पूर्णांकegrated demod active रेजिस्टर page */
	काष्ठा i2c_adapter *demod_i2c_adapter;
	bool rc_active;
	bool new_i2c_ग_लिखो;
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;
	काष्ठा i2c_client *i2c_client_slave_demod;
	काष्ठा platक्रमm_device *platक्रमm_device_sdr;
	#घोषणा SLAVE_DEMOD_NONE           0
	#घोषणा SLAVE_DEMOD_MN88472        1
	#घोषणा SLAVE_DEMOD_MN88473        2
	#घोषणा SLAVE_DEMOD_SI2168         3
	#घोषणा SLAVE_DEMOD_CXD2837ER      4
	अचिन्हित पूर्णांक slave_demod:3;
	जोड़ अणु
		काष्ठा rtl2830_platक्रमm_data rtl2830_platक्रमm_data;
		काष्ठा rtl2832_platक्रमm_data rtl2832_platक्रमm_data;
	पूर्ण;
पूर्ण;

क्रमागत rtl28xxu_chip_id अणु
	CHIP_ID_NONE,
	CHIP_ID_RTL2831U,
	CHIP_ID_RTL2832U,
पूर्ण;

/* XXX: Hack. This must be keep sync with rtl2832 demod driver. */
क्रमागत rtl28xxu_tuner अणु
	TUNER_NONE,

	TUNER_RTL2830_QT1010          = 0x10,
	TUNER_RTL2830_MT2060,
	TUNER_RTL2830_MXL5005S,

	TUNER_RTL2832_MT2266          = 0x20,
	TUNER_RTL2832_FC2580,
	TUNER_RTL2832_MT2063,
	TUNER_RTL2832_MAX3543,
	TUNER_RTL2832_TUA9001,
	TUNER_RTL2832_MXL5007T,
	TUNER_RTL2832_FC0012,
	TUNER_RTL2832_E4000,
	TUNER_RTL2832_TDA18272,
	TUNER_RTL2832_FC0013,
	TUNER_RTL2832_R820T,
	TUNER_RTL2832_R828D,
	TUNER_RTL2832_SI2157,
पूर्ण;

काष्ठा rtl28xxu_req अणु
	u16 value;
	u16 index;
	u16 size;
	u8 *data;
पूर्ण;

काष्ठा rtl28xxu_reg_val अणु
	u16 reg;
	u8 val;
पूर्ण;

काष्ठा rtl28xxu_reg_val_mask अणु
	u16 reg;
	u8 val;
	u8 mask;
पूर्ण;

/*
 * memory map
 *
 * 0x0000 DEMOD : demodulator
 * 0x2000 USB   : SIE, USB endpoपूर्णांक, debug, DMA
 * 0x3000 SYS   : प्रणाली
 * 0xfc00 RC    : remote controller (not RTL2831U)
 */

/*
 * USB रेजिस्टरs
 */
/* SIE Control Registers */
#घोषणा USB_SYSCTL         0x2000 /* USB प्रणाली control */
#घोषणा USB_SYSCTL_0       0x2000 /* USB प्रणाली control */
#घोषणा USB_SYSCTL_1       0x2001 /* USB प्रणाली control */
#घोषणा USB_SYSCTL_2       0x2002 /* USB प्रणाली control */
#घोषणा USB_SYSCTL_3       0x2003 /* USB प्रणाली control */
#घोषणा USB_IRQSTAT        0x2008 /* SIE पूर्णांकerrupt status */
#घोषणा USB_IRQEN          0x200C /* SIE पूर्णांकerrupt enable */
#घोषणा USB_CTRL           0x2010 /* USB control */
#घोषणा USB_STAT           0x2014 /* USB status */
#घोषणा USB_DEVADDR        0x2018 /* USB device address */
#घोषणा USB_TEST           0x201C /* USB test mode */
#घोषणा USB_FRAME_NUMBER   0x2020 /* frame number */
#घोषणा USB_FIFO_ADDR      0x2028 /* address of SIE FIFO RAM */
#घोषणा USB_FIFO_CMD       0x202A /* SIE FIFO RAM access command */
#घोषणा USB_FIFO_DATA      0x2030 /* SIE FIFO RAM data */
/* Endpoपूर्णांक Registers */
#घोषणा EP0_SETUPA         0x20F8 /* EP 0 setup packet lower byte */
#घोषणा EP0_SETUPB         0x20FC /* EP 0 setup packet higher byte */
#घोषणा USB_EP0_CFG        0x2104 /* EP 0 configure */
#घोषणा USB_EP0_CTL        0x2108 /* EP 0 control */
#घोषणा USB_EP0_STAT       0x210C /* EP 0 status */
#घोषणा USB_EP0_IRQSTAT    0x2110 /* EP 0 पूर्णांकerrupt status */
#घोषणा USB_EP0_IRQEN      0x2114 /* EP 0 पूर्णांकerrupt enable */
#घोषणा USB_EP0_MAXPKT     0x2118 /* EP 0 max packet size */
#घोषणा USB_EP0_BC         0x2120 /* EP 0 FIFO byte counter */
#घोषणा USB_EPA_CFG        0x2144 /* EP A configure */
#घोषणा USB_EPA_CFG_0      0x2144 /* EP A configure */
#घोषणा USB_EPA_CFG_1      0x2145 /* EP A configure */
#घोषणा USB_EPA_CFG_2      0x2146 /* EP A configure */
#घोषणा USB_EPA_CFG_3      0x2147 /* EP A configure */
#घोषणा USB_EPA_CTL        0x2148 /* EP A control */
#घोषणा USB_EPA_CTL_0      0x2148 /* EP A control */
#घोषणा USB_EPA_CTL_1      0x2149 /* EP A control */
#घोषणा USB_EPA_CTL_2      0x214A /* EP A control */
#घोषणा USB_EPA_CTL_3      0x214B /* EP A control */
#घोषणा USB_EPA_STAT       0x214C /* EP A status */
#घोषणा USB_EPA_IRQSTAT    0x2150 /* EP A पूर्णांकerrupt status */
#घोषणा USB_EPA_IRQEN      0x2154 /* EP A पूर्णांकerrupt enable */
#घोषणा USB_EPA_MAXPKT     0x2158 /* EP A max packet size */
#घोषणा USB_EPA_MAXPKT_0   0x2158 /* EP A max packet size */
#घोषणा USB_EPA_MAXPKT_1   0x2159 /* EP A max packet size */
#घोषणा USB_EPA_MAXPKT_2   0x215A /* EP A max packet size */
#घोषणा USB_EPA_MAXPKT_3   0x215B /* EP A max packet size */
#घोषणा USB_EPA_FIFO_CFG   0x2160 /* EP A FIFO configure */
#घोषणा USB_EPA_FIFO_CFG_0 0x2160 /* EP A FIFO configure */
#घोषणा USB_EPA_FIFO_CFG_1 0x2161 /* EP A FIFO configure */
#घोषणा USB_EPA_FIFO_CFG_2 0x2162 /* EP A FIFO configure */
#घोषणा USB_EPA_FIFO_CFG_3 0x2163 /* EP A FIFO configure */
/* Debug Registers */
#घोषणा USB_PHYTSTDIS      0x2F04 /* PHY test disable */
#घोषणा USB_TOUT_VAL       0x2F08 /* USB समय-out समय */
#घोषणा USB_VDRCTRL        0x2F10 /* UTMI venकरोr संकेत control */
#घोषणा USB_VSTAIN         0x2F14 /* UTMI venकरोr संकेत status in */
#घोषणा USB_VLOADM         0x2F18 /* UTMI load venकरोr संकेत status in */
#घोषणा USB_VSTAOUT        0x2F1C /* UTMI venकरोr संकेत status out */
#घोषणा USB_UTMI_TST       0x2F80 /* UTMI test */
#घोषणा USB_UTMI_STATUS    0x2F84 /* UTMI status */
#घोषणा USB_TSTCTL         0x2F88 /* test control */
#घोषणा USB_TSTCTL2        0x2F8C /* test control 2 */
#घोषणा USB_PID_FORCE      0x2F90 /* क्रमce PID */
#घोषणा USB_PKTERR_CNT     0x2F94 /* packet error counter */
#घोषणा USB_RXERR_CNT      0x2F98 /* RX error counter */
#घोषणा USB_MEM_BIST       0x2F9C /* MEM BIST test */
#घोषणा USB_SLBBIST        0x2FA0 /* self-loop-back BIST */
#घोषणा USB_CNTTEST        0x2FA4 /* counter test */
#घोषणा USB_PHYTST         0x2FC0 /* USB PHY test */
#घोषणा USB_DBGIDX         0x2FF0 /* select inभागidual block debug संकेत */
#घोषणा USB_DBGMUX         0x2FF4 /* debug संकेत module mux */

/*
 * SYS रेजिस्टरs
 */
/* demod control रेजिस्टरs */
#घोषणा SYS_SYS0           0x3000 /* include DEMOD_CTL, GPO, GPI, GPOE */
#घोषणा SYS_DEMOD_CTL      0x3000 /* control रेजिस्टर क्रम DVB-T demodulator */
/* GPIO रेजिस्टरs */
#घोषणा SYS_GPIO_OUT_VAL   0x3001 /* output value of GPIO */
#घोषणा SYS_GPIO_IN_VAL    0x3002 /* input value of GPIO */
#घोषणा SYS_GPIO_OUT_EN    0x3003 /* output enable of GPIO */
#घोषणा SYS_SYS1           0x3004 /* include GPD, SYSINTE, SYSINTS, GP_CFG0 */
#घोषणा SYS_GPIO_सूची       0x3004 /* direction control क्रम GPIO */
#घोषणा SYS_SYSINTE        0x3005 /* प्रणाली पूर्णांकerrupt enable */
#घोषणा SYS_SYSINTS        0x3006 /* प्रणाली पूर्णांकerrupt status */
#घोषणा SYS_GPIO_CFG0      0x3007 /* PAD configuration क्रम GPIO0-GPIO3 */
#घोषणा SYS_SYS2           0x3008 /* include GP_CFG1 and 3 reserved bytes */
#घोषणा SYS_GPIO_CFG1      0x3008 /* PAD configuration क्रम GPIO4 */
#घोषणा SYS_DEMOD_CTL1     0x300B

/* IrDA रेजिस्टरs */
#घोषणा SYS_IRRC_PSR       0x3020 /* IR protocol selection */
#घोषणा SYS_IRRC_PER       0x3024 /* IR protocol extension */
#घोषणा SYS_IRRC_SF        0x3028 /* IR sampling frequency */
#घोषणा SYS_IRRC_DPIR      0x302C /* IR data package पूर्णांकerval */
#घोषणा SYS_IRRC_CR        0x3030 /* IR control */
#घोषणा SYS_IRRC_RP        0x3034 /* IR पढ़ो port */
#घोषणा SYS_IRRC_SR        0x3038 /* IR status */
/* I2C master रेजिस्टरs */
#घोषणा SYS_I2CCR          0x3040 /* I2C घड़ी */
#घोषणा SYS_I2CMCR         0x3044 /* I2C master control */
#घोषणा SYS_I2CMSTR        0x3048 /* I2C master SCL timing */
#घोषणा SYS_I2CMSR         0x304C /* I2C master status */
#घोषणा SYS_I2CMFR         0x3050 /* I2C master FIFO */

/*
 * IR रेजिस्टरs
 */
#घोषणा IR_RX_BUF          0xFC00
#घोषणा IR_RX_IE           0xFD00
#घोषणा IR_RX_IF           0xFD01
#घोषणा IR_RX_CTRL         0xFD02
#घोषणा IR_RX_CFG          0xFD03
#घोषणा IR_MAX_DURATION0   0xFD04
#घोषणा IR_MAX_DURATION1   0xFD05
#घोषणा IR_IDLE_LEN0       0xFD06
#घोषणा IR_IDLE_LEN1       0xFD07
#घोषणा IR_GLITCH_LEN      0xFD08
#घोषणा IR_RX_BUF_CTRL     0xFD09
#घोषणा IR_RX_BUF_DATA     0xFD0A
#घोषणा IR_RX_BC           0xFD0B
#घोषणा IR_RX_CLK          0xFD0C
#घोषणा IR_RX_C_COUNT_L    0xFD0D
#घोषणा IR_RX_C_COUNT_H    0xFD0E
#घोषणा IR_SUSPEND_CTRL    0xFD10
#घोषणा IR_ERR_TOL_CTRL    0xFD11
#घोषणा IR_UNIT_LEN        0xFD12
#घोषणा IR_ERR_TOL_LEN     0xFD13
#घोषणा IR_MAX_H_TOL_LEN   0xFD14
#घोषणा IR_MAX_L_TOL_LEN   0xFD15
#घोषणा IR_MASK_CTRL       0xFD16
#घोषणा IR_MASK_DATA       0xFD17
#घोषणा IR_RES_MASK_ADDR   0xFD18
#घोषणा IR_RES_MASK_T_LEN  0xFD19

#पूर्ण_अगर
