<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* ------------------------------------------------------------------------- */
/* i2c-iop3xx.h algorithm driver definitions निजी to i2c-iop3xx.c         */
/* ------------------------------------------------------------------------- */
/*   Copyright (C) 2003 Peter Milne, D-TACQ Solutions Ltd
 *                      <Peter करोt Milne at D hyphen TACQ करोt com>

 */
/* ------------------------------------------------------------------------- */


#अगर_अघोषित I2C_IOP3XX_H
#घोषणा I2C_IOP3XX_H 1

/*
 * iop321 hardware bit definitions
 */
#घोषणा IOP3XX_ICR_FAST_MODE	0x8000	/* 1=400kBps, 0=100kBps */
#घोषणा IOP3XX_ICR_UNIT_RESET	0x4000	/* 1=RESET */
#घोषणा IOP3XX_ICR_SAD_IE	0x2000	/* 1=Slave Detect Interrupt Enable */
#घोषणा IOP3XX_ICR_ALD_IE	0x1000	/* 1=Arb Loss Detect Interrupt Enable */
#घोषणा IOP3XX_ICR_SSD_IE	0x0800	/* 1=Slave STOP Detect Interrupt Enable */
#घोषणा IOP3XX_ICR_BERR_IE	0x0400	/* 1=Bus Error Interrupt Enable */
#घोषणा IOP3XX_ICR_RXFULL_IE	0x0200	/* 1=Receive Full Interrupt Enable */
#घोषणा IOP3XX_ICR_TXEMPTY_IE	0x0100	/* 1=Transmit Empty Interrupt Enable */
#घोषणा IOP3XX_ICR_GCD		0x0080	/* 1=General Call Disable */
/*
 * IOP3XX_ICR_GCD: 1 disables response as slave. "This bit must be set
 * when sending a master mode general call message from the I2C unit"
 */
#घोषणा IOP3XX_ICR_UE		0x0040	/* 1=Unit Enable */
/*
 * "NOTE: To aव्योम I2C bus पूर्णांकegrity problems, 
 * the user needs to ensure that the GPIO Output Data Register - 
 * GPOD bits associated with an I2C port are cleared prior to setting 
 * the enable bit क्रम that I2C serial port. 
 * The user prepares to enable I2C port 0 and 
 * I2C port 1 by clearing GPOD bits 7:6 and GPOD bits 5:4, respectively.
 */
#घोषणा IOP3XX_ICR_SCLEN	0x0020	/* 1=SCL enable क्रम master mode */
#घोषणा IOP3XX_ICR_MABORT	0x0010	/* 1=Send a STOP with no data 
					 * NB TBYTE must be clear */
#घोषणा IOP3XX_ICR_TBYTE	0x0008	/* 1=Send/Receive a byte. i2c clears */
#घोषणा IOP3XX_ICR_NACK		0x0004	/* 1=reply with NACK */
#घोषणा IOP3XX_ICR_MSTOP	0x0002	/* 1=send a STOP after next data byte */
#घोषणा IOP3XX_ICR_MSTART	0x0001	/* 1=initiate a START */


#घोषणा IOP3XX_ISR_BERRD	0x0400	/* 1=BUS ERROR Detected */
#घोषणा IOP3XX_ISR_SAD		0x0200	/* 1=Slave ADdress Detected */
#घोषणा IOP3XX_ISR_GCAD		0x0100	/* 1=General Call Address Detected */
#घोषणा IOP3XX_ISR_RXFULL	0x0080	/* 1=Receive Full */
#घोषणा IOP3XX_ISR_TXEMPTY	0x0040	/* 1=Transmit Empty */
#घोषणा IOP3XX_ISR_ALD		0x0020	/* 1=Arbitration Loss Detected */
#घोषणा IOP3XX_ISR_SSD		0x0010	/* 1=Slave STOP Detected */
#घोषणा IOP3XX_ISR_BBUSY	0x0008	/* 1=Bus BUSY */
#घोषणा IOP3XX_ISR_UNITBUSY	0x0004	/* 1=Unit Busy */
#घोषणा IOP3XX_ISR_NACK		0x0002	/* 1=Unit Rx or Tx a NACK */
#घोषणा IOP3XX_ISR_RXREAD	0x0001	/* 1=READ 0=WRITE (R/W bit of slave addr */

#घोषणा IOP3XX_ISR_CLEARBITS	0x07f0

#घोषणा IOP3XX_ISAR_SAMASK	0x007f

#घोषणा IOP3XX_IDBR_MASK	0x00ff

#घोषणा IOP3XX_IBMR_SCL		0x0002
#घोषणा IOP3XX_IBMR_SDA		0x0001

#घोषणा IOP3XX_GPOD_I2C0	0x00c0	/* clear these bits to enable ch0 */
#घोषणा IOP3XX_GPOD_I2C1	0x0030	/* clear these bits to enable ch1 */

#घोषणा MYSAR			0	/* शेष slave address */

#घोषणा I2C_ERR			321
#घोषणा I2C_ERR_BERR		(I2C_ERR+0)
#घोषणा I2C_ERR_ALD		(I2C_ERR+1)


#घोषणा	CR_OFFSET		0
#घोषणा	SR_OFFSET		0x4
#घोषणा	SAR_OFFSET		0x8
#घोषणा	DBR_OFFSET		0xc
#घोषणा	CCR_OFFSET		0x10
#घोषणा	BMR_OFFSET		0x14

#घोषणा	IOP3XX_I2C_IO_SIZE	0x18

काष्ठा i2c_algo_iop3xx_data अणु
	व्योम __iomem *ioaddr;
	रुको_queue_head_t रुकोq;
	spinlock_t lock;
	u32 SR_enabled, SR_received;
	पूर्णांक id;
	काष्ठा gpio_desc *gpio_scl;
	काष्ठा gpio_desc *gpio_sda;
पूर्ण;

#पूर्ण_अगर /* I2C_IOP3XX_H */
