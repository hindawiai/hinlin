<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * SMI PCIe driver क्रम DVBSky cards.
 *
 * Copyright (C) 2014 Max nibble <nibble.max@gmail.com>
 */

#अगर_अघोषित _SMI_PCIE_H_
#घोषणा _SMI_PCIE_H_

#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>

#समावेश <media/demux.h>
#समावेश <media/dmxdev.h>
#समावेश <media/dvb_demux.h>
#समावेश <media/dvb_frontend.h>
#समावेश <media/dvb_net.h>
#समावेश <media/dvbdev.h>

/* -------- Register Base -------- */
#घोषणा    MSI_CONTROL_REG_BASE                 0x0800
#घोषणा    SYSTEM_CONTROL_REG_BASE              0x0880
#घोषणा    PCIE_EP_DEBUG_REG_BASE               0x08C0
#घोषणा    IR_CONTROL_REG_BASE                  0x0900
#घोषणा    I2C_A_CONTROL_REG_BASE               0x0940
#घोषणा    I2C_B_CONTROL_REG_BASE               0x0980
#घोषणा    ATV_PORTA_CONTROL_REG_BASE           0x09C0
#घोषणा    DTV_PORTA_CONTROL_REG_BASE           0x0A00
#घोषणा    AES_PORTA_CONTROL_REG_BASE           0x0A80
#घोषणा    DMA_PORTA_CONTROL_REG_BASE           0x0AC0
#घोषणा    ATV_PORTB_CONTROL_REG_BASE           0x0B00
#घोषणा    DTV_PORTB_CONTROL_REG_BASE           0x0B40
#घोषणा    AES_PORTB_CONTROL_REG_BASE           0x0BC0
#घोषणा    DMA_PORTB_CONTROL_REG_BASE           0x0C00
#घोषणा    UART_A_REGISTER_BASE                 0x0C40
#घोषणा    UART_B_REGISTER_BASE                 0x0C80
#घोषणा    GPS_CONTROL_REG_BASE                 0x0CC0
#घोषणा    DMA_PORTC_CONTROL_REG_BASE           0x0D00
#घोषणा    DMA_PORTD_CONTROL_REG_BASE           0x0D00
#घोषणा    AES_RANDOM_DATA_BASE                 0x0D80
#घोषणा    AES_KEY_IN_BASE                      0x0D90
#घोषणा    RANDOM_DATA_LIB_BASE                 0x0E00
#घोषणा    IR_DATA_BUFFER_BASE                  0x0F00
#घोषणा    PORTA_TS_BUFFER_BASE                 0x1000
#घोषणा    PORTA_I2S_BUFFER_BASE                0x1400
#घोषणा    PORTB_TS_BUFFER_BASE                 0x1800
#घोषणा    PORTB_I2S_BUFFER_BASE                0x1C00

/* -------- MSI control and state रेजिस्टर -------- */
#घोषणा MSI_DELAY_TIMER             (MSI_CONTROL_REG_BASE + 0x00)
#घोषणा MSI_INT_STATUS              (MSI_CONTROL_REG_BASE + 0x08)
#घोषणा MSI_INT_STATUS_CLR          (MSI_CONTROL_REG_BASE + 0x0C)
#घोषणा MSI_INT_STATUS_SET          (MSI_CONTROL_REG_BASE + 0x10)
#घोषणा MSI_INT_ENA                 (MSI_CONTROL_REG_BASE + 0x14)
#घोषणा MSI_INT_ENA_CLR             (MSI_CONTROL_REG_BASE + 0x18)
#घोषणा MSI_INT_ENA_SET             (MSI_CONTROL_REG_BASE + 0x1C)
#घोषणा MSI_SOFT_RESET              (MSI_CONTROL_REG_BASE + 0x20)
#घोषणा MSI_CFG_SRC0                (MSI_CONTROL_REG_BASE + 0x24)

/* -------- Hybird Controller System Control रेजिस्टर -------- */
#घोषणा MUX_MODE_CTRL         (SYSTEM_CONTROL_REG_BASE + 0x00)
	#घोषणा rbPaMSMask        0x07
	#घोषणा rbPaMSDtvNoGpio   0x00 /*[2:0], DTV Simple mode */
	#घोषणा rbPaMSDtv4bitGpio 0x01 /*[2:0], DTV TS2 Serial mode)*/
	#घोषणा rbPaMSDtv7bitGpio 0x02 /*[2:0], DTV TS0 Serial mode*/
	#घोषणा rbPaMS8bitGpio    0x03 /*[2:0], GPIO mode selected;(8bit GPIO)*/
	#घोषणा rbPaMSAtv         0x04 /*[2:0], 3'b1xx: ATV mode select*/
	#घोषणा rbPbMSMask        0x38
	#घोषणा rbPbMSDtvNoGpio   0x00 /*[5:3], DTV Simple mode */
	#घोषणा rbPbMSDtv4bitGpio 0x08 /*[5:3], DTV TS2 Serial mode*/
	#घोषणा rbPbMSDtv7bitGpio 0x10 /*[5:3], DTV TS0 Serial mode*/
	#घोषणा rbPbMS8bitGpio    0x18 /*[5:3], GPIO mode selected;(8bit GPIO)*/
	#घोषणा rbPbMSAtv         0x20 /*[5:3], 3'b1xx: ATV mode select*/
	#घोषणा rbPaAESEN         0x40 /*[6], port A AES enable bit*/
	#घोषणा rbPbAESEN         0x80 /*[7], port B AES enable bit*/

#घोषणा INTERNAL_RST                (SYSTEM_CONTROL_REG_BASE + 0x04)
#घोषणा PERIPHERAL_CTRL             (SYSTEM_CONTROL_REG_BASE + 0x08)
#घोषणा GPIO_0to7_CTRL              (SYSTEM_CONTROL_REG_BASE + 0x0C)
#घोषणा GPIO_8to15_CTRL             (SYSTEM_CONTROL_REG_BASE + 0x10)
#घोषणा GPIO_16to24_CTRL            (SYSTEM_CONTROL_REG_BASE + 0x14)
#घोषणा GPIO_INT_SRC_CFG            (SYSTEM_CONTROL_REG_BASE + 0x18)
#घोषणा SYS_BUF_STATUS              (SYSTEM_CONTROL_REG_BASE + 0x1C)
#घोषणा PCIE_IP_REG_ACS             (SYSTEM_CONTROL_REG_BASE + 0x20)
#घोषणा PCIE_IP_REG_ACS_ADDR        (SYSTEM_CONTROL_REG_BASE + 0x24)
#घोषणा PCIE_IP_REG_ACS_DATA        (SYSTEM_CONTROL_REG_BASE + 0x28)

/* -------- IR Control रेजिस्टर -------- */
#घोषणा   IR_Init_Reg         (IR_CONTROL_REG_BASE + 0x00)
#घोषणा   IR_Idle_Cnt_Low     (IR_CONTROL_REG_BASE + 0x04)
#घोषणा   IR_Idle_Cnt_High    (IR_CONTROL_REG_BASE + 0x05)
#घोषणा   IR_Unit_Cnt_Low     (IR_CONTROL_REG_BASE + 0x06)
#घोषणा   IR_Unit_Cnt_High    (IR_CONTROL_REG_BASE + 0x07)
#घोषणा   IR_Data_Cnt         (IR_CONTROL_REG_BASE + 0x08)
#घोषणा   rbIRen            0x80
#घोषणा   rbIRhighidle      0x10
#घोषणा   rbIRlowidle       0x00
#घोषणा   rbIRVld           0x04

/* -------- I2C A control and state रेजिस्टर -------- */
#घोषणा I2C_A_CTL_STATUS                 (I2C_A_CONTROL_REG_BASE + 0x00)
#घोषणा I2C_A_ADDR                       (I2C_A_CONTROL_REG_BASE + 0x04)
#घोषणा I2C_A_SW_CTL                     (I2C_A_CONTROL_REG_BASE + 0x08)
#घोषणा I2C_A_TIME_OUT_CNT               (I2C_A_CONTROL_REG_BASE + 0x0C)
#घोषणा I2C_A_FIFO_STATUS                (I2C_A_CONTROL_REG_BASE + 0x10)
#घोषणा I2C_A_FS_EN                      (I2C_A_CONTROL_REG_BASE + 0x14)
#घोषणा I2C_A_FIFO_DATA                  (I2C_A_CONTROL_REG_BASE + 0x20)

/* -------- I2C B control and state रेजिस्टर -------- */
#घोषणा I2C_B_CTL_STATUS                 (I2C_B_CONTROL_REG_BASE + 0x00)
#घोषणा I2C_B_ADDR                       (I2C_B_CONTROL_REG_BASE + 0x04)
#घोषणा I2C_B_SW_CTL                     (I2C_B_CONTROL_REG_BASE + 0x08)
#घोषणा I2C_B_TIME_OUT_CNT               (I2C_B_CONTROL_REG_BASE + 0x0C)
#घोषणा I2C_B_FIFO_STATUS                (I2C_B_CONTROL_REG_BASE + 0x10)
#घोषणा I2C_B_FS_EN                      (I2C_B_CONTROL_REG_BASE + 0x14)
#घोषणा I2C_B_FIFO_DATA                  (I2C_B_CONTROL_REG_BASE + 0x20)

#घोषणा VIDEO_CTRL_STATUS_A	(ATV_PORTA_CONTROL_REG_BASE + 0x04)

/* -------- Digital TV control रेजिस्टर, Port A -------- */
#घोषणा MPEG2_CTRL_A		(DTV_PORTA_CONTROL_REG_BASE + 0x00)
#घोषणा SERIAL_IN_ADDR_A	(DTV_PORTA_CONTROL_REG_BASE + 0x4C)
#घोषणा VLD_CNT_ADDR_A		(DTV_PORTA_CONTROL_REG_BASE + 0x60)
#घोषणा ERR_CNT_ADDR_A		(DTV_PORTA_CONTROL_REG_BASE + 0x64)
#घोषणा BRD_CNT_ADDR_A		(DTV_PORTA_CONTROL_REG_BASE + 0x68)

/* -------- DMA Control Register, Port A  -------- */
#घोषणा DMA_PORTA_CHAN0_ADDR_LOW        (DMA_PORTA_CONTROL_REG_BASE + 0x00)
#घोषणा DMA_PORTA_CHAN0_ADDR_HI         (DMA_PORTA_CONTROL_REG_BASE + 0x04)
#घोषणा DMA_PORTA_CHAN0_TRANS_STATE     (DMA_PORTA_CONTROL_REG_BASE + 0x08)
#घोषणा DMA_PORTA_CHAN0_CONTROL         (DMA_PORTA_CONTROL_REG_BASE + 0x0C)
#घोषणा DMA_PORTA_CHAN1_ADDR_LOW        (DMA_PORTA_CONTROL_REG_BASE + 0x10)
#घोषणा DMA_PORTA_CHAN1_ADDR_HI         (DMA_PORTA_CONTROL_REG_BASE + 0x14)
#घोषणा DMA_PORTA_CHAN1_TRANS_STATE     (DMA_PORTA_CONTROL_REG_BASE + 0x18)
#घोषणा DMA_PORTA_CHAN1_CONTROL         (DMA_PORTA_CONTROL_REG_BASE + 0x1C)
#घोषणा DMA_PORTA_MANAGEMENT            (DMA_PORTA_CONTROL_REG_BASE + 0x20)
#घोषणा VIDEO_CTRL_STATUS_B             (ATV_PORTB_CONTROL_REG_BASE + 0x04)

/* -------- Digital TV control रेजिस्टर, Port B -------- */
#घोषणा MPEG2_CTRL_B		(DTV_PORTB_CONTROL_REG_BASE + 0x00)
#घोषणा SERIAL_IN_ADDR_B	(DTV_PORTB_CONTROL_REG_BASE + 0x4C)
#घोषणा VLD_CNT_ADDR_B		(DTV_PORTB_CONTROL_REG_BASE + 0x60)
#घोषणा ERR_CNT_ADDR_B		(DTV_PORTB_CONTROL_REG_BASE + 0x64)
#घोषणा BRD_CNT_ADDR_B		(DTV_PORTB_CONTROL_REG_BASE + 0x68)

/* -------- AES control रेजिस्टर, Port B -------- */
#घोषणा AES_CTRL_B		(AES_PORTB_CONTROL_REG_BASE + 0x00)
#घोषणा AES_KEY_BASE_B	(AES_PORTB_CONTROL_REG_BASE + 0x04)

/* -------- DMA Control Register, Port B  -------- */
#घोषणा DMA_PORTB_CHAN0_ADDR_LOW        (DMA_PORTB_CONTROL_REG_BASE + 0x00)
#घोषणा DMA_PORTB_CHAN0_ADDR_HI         (DMA_PORTB_CONTROL_REG_BASE + 0x04)
#घोषणा DMA_PORTB_CHAN0_TRANS_STATE     (DMA_PORTB_CONTROL_REG_BASE + 0x08)
#घोषणा DMA_PORTB_CHAN0_CONTROL         (DMA_PORTB_CONTROL_REG_BASE + 0x0C)
#घोषणा DMA_PORTB_CHAN1_ADDR_LOW        (DMA_PORTB_CONTROL_REG_BASE + 0x10)
#घोषणा DMA_PORTB_CHAN1_ADDR_HI         (DMA_PORTB_CONTROL_REG_BASE + 0x14)
#घोषणा DMA_PORTB_CHAN1_TRANS_STATE     (DMA_PORTB_CONTROL_REG_BASE + 0x18)
#घोषणा DMA_PORTB_CHAN1_CONTROL         (DMA_PORTB_CONTROL_REG_BASE + 0x1C)
#घोषणा DMA_PORTB_MANAGEMENT            (DMA_PORTB_CONTROL_REG_BASE + 0x20)

#घोषणा DMA_TRANS_UNIT_188 (0x00000007)

/* -------- Macro define of 24 पूर्णांकerrupt resource --------*/
#घोषणा DMA_A_CHAN0_DONE_INT   (0x00000001)
#घोषणा DMA_A_CHAN1_DONE_INT   (0x00000002)
#घोषणा DMA_B_CHAN0_DONE_INT   (0x00000004)
#घोषणा DMA_B_CHAN1_DONE_INT   (0x00000008)
#घोषणा DMA_C_CHAN0_DONE_INT   (0x00000010)
#घोषणा DMA_C_CHAN1_DONE_INT   (0x00000020)
#घोषणा DMA_D_CHAN0_DONE_INT   (0x00000040)
#घोषणा DMA_D_CHAN1_DONE_INT   (0x00000080)
#घोषणा DATA_BUF_OVERFLOW_INT  (0x00000100)
#घोषणा UART_0_X_INT           (0x00000200)
#घोषणा UART_1_X_INT           (0x00000400)
#घोषणा IR_X_INT               (0x00000800)
#घोषणा GPIO_0_INT             (0x00001000)
#घोषणा GPIO_1_INT             (0x00002000)
#घोषणा GPIO_2_INT             (0x00004000)
#घोषणा GPIO_3_INT             (0x00008000)
#घोषणा ALL_INT                (0x0000FFFF)

/* software I2C bit mask */
#घोषणा SW_I2C_MSK_MODE         0x01
#घोषणा SW_I2C_MSK_CLK_OUT      0x02
#घोषणा SW_I2C_MSK_DAT_OUT      0x04
#घोषणा SW_I2C_MSK_CLK_EN       0x08
#घोषणा SW_I2C_MSK_DAT_EN       0x10
#घोषणा SW_I2C_MSK_DAT_IN       0x40
#घोषणा SW_I2C_MSK_CLK_IN       0x80

#घोषणा SMI_VID		0x1ADE
#घोषणा SMI_PID		0x3038
#घोषणा SMI_TS_DMA_BUF_SIZE	(1024 * 188)

काष्ठा smi_cfg_info अणु
#घोषणा SMI_DVBSKY_S952         0
#घोषणा SMI_DVBSKY_S950         1
#घोषणा SMI_DVBSKY_T9580        2
#घोषणा SMI_DVBSKY_T982         3
#घोषणा SMI_TECHNOTREND_S2_4200 4
	पूर्णांक type;
	अक्षर *name;
#घोषणा SMI_TS_शून्य             0
#घोषणा SMI_TS_DMA_SINGLE       1
#घोषणा SMI_TS_DMA_BOTH         3
/* SMI_TS_शून्य: not use;
 * SMI_TS_DMA_SINGLE: use DMA 0 only;
 * SMI_TS_DMA_BOTH:use DMA 0 and 1.*/
	पूर्णांक ts_0;
	पूर्णांक ts_1;
#घोषणा DVBSKY_FE_शून्य          0
#घोषणा DVBSKY_FE_M88RS6000     1
#घोषणा DVBSKY_FE_M88DS3103     2
#घोषणा DVBSKY_FE_SIT2          3
	पूर्णांक fe_0;
	पूर्णांक fe_1;
	अक्षर *rc_map;
पूर्ण;

काष्ठा smi_rc अणु
	काष्ठा smi_dev *dev;
	काष्ठा rc_dev *rc_dev;
	अक्षर input_phys[64];
	अक्षर device_name[64];
	u8 irData[256];

	पूर्णांक users;
पूर्ण;

काष्ठा smi_port अणु
	काष्ठा smi_dev *dev;
	पूर्णांक idx;
	पूर्णांक enable;
	पूर्णांक fe_type;
	/* regs */
	u32 DMA_CHAN0_ADDR_LOW;
	u32 DMA_CHAN0_ADDR_HI;
	u32 DMA_CHAN0_TRANS_STATE;
	u32 DMA_CHAN0_CONTROL;
	u32 DMA_CHAN1_ADDR_LOW;
	u32 DMA_CHAN1_ADDR_HI;
	u32 DMA_CHAN1_TRANS_STATE;
	u32 DMA_CHAN1_CONTROL;
	u32 DMA_MANAGEMENT;
	/* dma */
	dma_addr_t dma_addr[2];
	u8 *cpu_addr[2];
	u32 _dmaInterruptCH0;
	u32 _dmaInterruptCH1;
	u32 _पूर्णांक_status;
	काष्ठा tasklet_काष्ठा tasklet;
	/* dvb */
	काष्ठा dmx_frontend hw_frontend;
	काष्ठा dmx_frontend mem_frontend;
	काष्ठा dmxdev dmxdev;
	काष्ठा dvb_adapter dvb_adapter;
	काष्ठा dvb_demux demux;
	काष्ठा dvb_net dvbnet;
	पूर्णांक users;
	काष्ठा dvb_frontend *fe;
	/* frontend i2c module */
	काष्ठा i2c_client *i2c_client_demod;
	काष्ठा i2c_client *i2c_client_tuner;
पूर्ण;

काष्ठा smi_dev अणु
	पूर्णांक nr;
	काष्ठा smi_cfg_info *info;

	/* pcie */
	काष्ठा pci_dev *pci_dev;
	u32 __iomem *lmmio;

	/* ts port */
	काष्ठा smi_port ts_port[2];

	/* i2c */
	काष्ठा i2c_adapter i2c_bus[2];
	काष्ठा i2c_algo_bit_data i2c_bit[2];

	/* ir */
	काष्ठा smi_rc ir;
पूर्ण;

#घोषणा smi_पढ़ो(reg)             पढ़ोl(dev->lmmio + ((reg)>>2))
#घोषणा smi_ग_लिखो(reg, value)     ग_लिखोl((value), dev->lmmio + ((reg)>>2))

#घोषणा smi_anकरोr(reg, mask, value) \
	ग_लिखोl((पढ़ोl(dev->lmmio+((reg)>>2)) & ~(mask)) |\
	((value) & (mask)), dev->lmmio+((reg)>>2))

#घोषणा smi_set(reg, bit)          smi_anकरोr((reg), (bit), (bit))
#घोषणा smi_clear(reg, bit)        smi_anकरोr((reg), (bit), 0)

पूर्णांक smi_ir_irq(काष्ठा smi_rc *ir, u32 पूर्णांक_status);
व्योम smi_ir_start(काष्ठा smi_rc *ir);
व्योम smi_ir_निकास(काष्ठा smi_dev *dev);
पूर्णांक smi_ir_init(काष्ठा smi_dev *dev);

#पूर्ण_अगर /* #अगर_अघोषित _SMI_PCIE_H_ */
