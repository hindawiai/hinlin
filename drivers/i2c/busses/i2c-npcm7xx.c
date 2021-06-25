<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Nuvoton NPCM7xx I2C Controller driver
 *
 * Copyright (C) 2020 Nuvoton Technologies tali.perry@nuvoton.com
 */
#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/iopoll.h>
#समावेश <linux/irq.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mfd/syscon.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>

क्रमागत i2c_mode अणु
	I2C_MASTER,
	I2C_SLAVE,
पूर्ण;

/*
 * External I2C Interface driver xfer indication values, which indicate status
 * of the bus.
 */
क्रमागत i2c_state_ind अणु
	I2C_NO_STATUS_IND = 0,
	I2C_SLAVE_RCV_IND,
	I2C_SLAVE_XMIT_IND,
	I2C_SLAVE_XMIT_MISSING_DATA_IND,
	I2C_SLAVE_RESTART_IND,
	I2C_SLAVE_DONE_IND,
	I2C_MASTER_DONE_IND,
	I2C_NACK_IND,
	I2C_BUS_ERR_IND,
	I2C_WAKE_UP_IND,
	I2C_BLOCK_BYTES_ERR_IND,
	I2C_SLAVE_RCV_MISSING_DATA_IND,
पूर्ण;

/*
 * Operation type values (used to define the operation currently running)
 * module is पूर्णांकerrupt driven, on each पूर्णांकerrupt the current operation is
 * checked to see अगर the module is currently पढ़ोing or writing.
 */
क्रमागत i2c_oper अणु
	I2C_NO_OPER = 0,
	I2C_WRITE_OPER,
	I2C_READ_OPER,
पूर्ण;

/* I2C Bank (module had 2 banks of रेजिस्टरs) */
क्रमागत i2c_bank अणु
	I2C_BANK_0 = 0,
	I2C_BANK_1,
पूर्ण;

/* Internal I2C states values (क्रम the I2C module state machine). */
क्रमागत i2c_state अणु
	I2C_DISABLE = 0,
	I2C_IDLE,
	I2C_MASTER_START,
	I2C_SLAVE_MATCH,
	I2C_OPER_STARTED,
	I2C_STOP_PENDING,
पूर्ण;

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
/* Module supports setting multiple own slave addresses */
क्रमागत i2c_addr अणु
	I2C_SLAVE_ADDR1 = 0,
	I2C_SLAVE_ADDR2,
	I2C_SLAVE_ADDR3,
	I2C_SLAVE_ADDR4,
	I2C_SLAVE_ADDR5,
	I2C_SLAVE_ADDR6,
	I2C_SLAVE_ADDR7,
	I2C_SLAVE_ADDR8,
	I2C_SLAVE_ADDR9,
	I2C_SLAVE_ADDR10,
	I2C_GC_ADDR,
	I2C_ARP_ADDR,
पूर्ण;
#पूर्ण_अगर

/* init रेजिस्टर and शेष value required to enable module */
#घोषणा NPCM_I2CSEGCTL			0xE4
#घोषणा NPCM_I2CSEGCTL_INIT_VAL		0x0333F000

/* Common regs */
#घोषणा NPCM_I2CSDA			0x00
#घोषणा NPCM_I2CST			0x02
#घोषणा NPCM_I2CCST			0x04
#घोषणा NPCM_I2CCTL1			0x06
#घोषणा NPCM_I2CADDR1			0x08
#घोषणा NPCM_I2CCTL2			0x0A
#घोषणा NPCM_I2CADDR2			0x0C
#घोषणा NPCM_I2CCTL3			0x0E
#घोषणा NPCM_I2CCST2			0x18
#घोषणा NPCM_I2CCST3			0x19
#घोषणा I2C_VER				0x1F

/*BANK0 regs*/
#घोषणा NPCM_I2CADDR3			0x10
#घोषणा NPCM_I2CADDR7			0x11
#घोषणा NPCM_I2CADDR4			0x12
#घोषणा NPCM_I2CADDR8			0x13
#घोषणा NPCM_I2CADDR5			0x14
#घोषणा NPCM_I2CADDR9			0x15
#घोषणा NPCM_I2CADDR6			0x16
#घोषणा NPCM_I2CADDR10			0x17

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
/*
 * npcm_i2caddr array:
 * The module supports having multiple own slave addresses.
 * Since the addr regs are sprinkled all over the address space,
 * use this array to get the address or each रेजिस्टर.
 */
#घोषणा I2C_NUM_OWN_ADDR 10
अटल स्थिर पूर्णांक npcm_i2caddr[I2C_NUM_OWN_ADDR] = अणु
	NPCM_I2CADDR1, NPCM_I2CADDR2, NPCM_I2CADDR3, NPCM_I2CADDR4,
	NPCM_I2CADDR5, NPCM_I2CADDR6, NPCM_I2CADDR7, NPCM_I2CADDR8,
	NPCM_I2CADDR9, NPCM_I2CADDR10,
पूर्ण;
#पूर्ण_अगर

#घोषणा NPCM_I2CCTL4			0x1A
#घोषणा NPCM_I2CCTL5			0x1B
#घोषणा NPCM_I2CSCLLT			0x1C /* SCL Low Time */
#घोषणा NPCM_I2CFIF_CTL			0x1D /* FIFO Control */
#घोषणा NPCM_I2CSCLHT			0x1E /* SCL High Time */

/* BANK 1 regs */
#घोषणा NPCM_I2CFIF_CTS			0x10 /* Both FIFOs Control and Status */
#घोषणा NPCM_I2CTXF_CTL			0x12 /* Tx-FIFO Control */
#घोषणा NPCM_I2CT_OUT			0x14 /* Bus T.O. */
#घोषणा NPCM_I2CPEC			0x16 /* PEC Data */
#घोषणा NPCM_I2CTXF_STS			0x1A /* Tx-FIFO Status */
#घोषणा NPCM_I2CRXF_STS			0x1C /* Rx-FIFO Status */
#घोषणा NPCM_I2CRXF_CTL			0x1E /* Rx-FIFO Control */

/* NPCM_I2CST reg fields */
#घोषणा NPCM_I2CST_XMIT			BIT(0)
#घोषणा NPCM_I2CST_MASTER		BIT(1)
#घोषणा NPCM_I2CST_NMATCH		BIT(2)
#घोषणा NPCM_I2CST_STASTR		BIT(3)
#घोषणा NPCM_I2CST_NEGACK		BIT(4)
#घोषणा NPCM_I2CST_BER			BIT(5)
#घोषणा NPCM_I2CST_SDAST		BIT(6)
#घोषणा NPCM_I2CST_SLVSTP		BIT(7)

/* NPCM_I2CCST reg fields */
#घोषणा NPCM_I2CCST_BUSY		BIT(0)
#घोषणा NPCM_I2CCST_BB			BIT(1)
#घोषणा NPCM_I2CCST_MATCH		BIT(2)
#घोषणा NPCM_I2CCST_GCMATCH		BIT(3)
#घोषणा NPCM_I2CCST_TSDA		BIT(4)
#घोषणा NPCM_I2CCST_TGSCL		BIT(5)
#घोषणा NPCM_I2CCST_MATCHAF		BIT(6)
#घोषणा NPCM_I2CCST_ARPMATCH		BIT(7)

/* NPCM_I2CCTL1 reg fields */
#घोषणा NPCM_I2CCTL1_START		BIT(0)
#घोषणा NPCM_I2CCTL1_STOP		BIT(1)
#घोषणा NPCM_I2CCTL1_INTEN		BIT(2)
#घोषणा NPCM_I2CCTL1_EOBINTE		BIT(3)
#घोषणा NPCM_I2CCTL1_ACK		BIT(4)
#घोषणा NPCM_I2CCTL1_GCMEN		BIT(5)
#घोषणा NPCM_I2CCTL1_NMINTE		BIT(6)
#घोषणा NPCM_I2CCTL1_STASTRE		BIT(7)

/* RW1S fields (inside a RW reg): */
#घोषणा NPCM_I2CCTL1_RWS   \
	(NPCM_I2CCTL1_START | NPCM_I2CCTL1_STOP | NPCM_I2CCTL1_ACK)

/* npcm_i2caddr reg fields */
#घोषणा NPCM_I2CADDR_A			GENMASK(6, 0)
#घोषणा NPCM_I2CADDR_SAEN		BIT(7)

/* NPCM_I2CCTL2 reg fields */
#घोषणा I2CCTL2_ENABLE			BIT(0)
#घोषणा I2CCTL2_SCLFRQ6_0		GENMASK(7, 1)

/* NPCM_I2CCTL3 reg fields */
#घोषणा I2CCTL3_SCLFRQ8_7		GENMASK(1, 0)
#घोषणा I2CCTL3_ARPMEN			BIT(2)
#घोषणा I2CCTL3_IDL_START		BIT(3)
#घोषणा I2CCTL3_400K_MODE		BIT(4)
#घोषणा I2CCTL3_BNK_SEL			BIT(5)
#घोषणा I2CCTL3_SDA_LVL			BIT(6)
#घोषणा I2CCTL3_SCL_LVL			BIT(7)

/* NPCM_I2CCST2 reg fields */
#घोषणा NPCM_I2CCST2_MATCHA1F		BIT(0)
#घोषणा NPCM_I2CCST2_MATCHA2F		BIT(1)
#घोषणा NPCM_I2CCST2_MATCHA3F		BIT(2)
#घोषणा NPCM_I2CCST2_MATCHA4F		BIT(3)
#घोषणा NPCM_I2CCST2_MATCHA5F		BIT(4)
#घोषणा NPCM_I2CCST2_MATCHA6F		BIT(5)
#घोषणा NPCM_I2CCST2_MATCHA7F		BIT(5)
#घोषणा NPCM_I2CCST2_INTSTS		BIT(7)

/* NPCM_I2CCST3 reg fields */
#घोषणा NPCM_I2CCST3_MATCHA8F		BIT(0)
#घोषणा NPCM_I2CCST3_MATCHA9F		BIT(1)
#घोषणा NPCM_I2CCST3_MATCHA10F		BIT(2)
#घोषणा NPCM_I2CCST3_EO_BUSY		BIT(7)

/* NPCM_I2CCTL4 reg fields */
#घोषणा I2CCTL4_HLDT			GENMASK(5, 0)
#घोषणा I2CCTL4_LVL_WE			BIT(7)

/* NPCM_I2CCTL5 reg fields */
#घोषणा I2CCTL5_DBNCT			GENMASK(3, 0)

/* NPCM_I2CFIF_CTS reg fields */
#घोषणा NPCM_I2CFIF_CTS_RXF_TXE		BIT(1)
#घोषणा NPCM_I2CFIF_CTS_RFTE_IE		BIT(3)
#घोषणा NPCM_I2CFIF_CTS_CLR_FIFO	BIT(6)
#घोषणा NPCM_I2CFIF_CTS_SLVRSTR		BIT(7)

/* NPCM_I2CTXF_CTL reg fields */
#घोषणा NPCM_I2CTXF_CTL_TX_THR		GENMASK(4, 0)
#घोषणा NPCM_I2CTXF_CTL_THR_TXIE	BIT(6)

/* NPCM_I2CT_OUT reg fields */
#घोषणा NPCM_I2CT_OUT_TO_CKDIV		GENMASK(5, 0)
#घोषणा NPCM_I2CT_OUT_T_OUTIE		BIT(6)
#घोषणा NPCM_I2CT_OUT_T_OUTST		BIT(7)

/* NPCM_I2CTXF_STS reg fields */
#घोषणा NPCM_I2CTXF_STS_TX_BYTES	GENMASK(4, 0)
#घोषणा NPCM_I2CTXF_STS_TX_THST		BIT(6)

/* NPCM_I2CRXF_STS reg fields */
#घोषणा NPCM_I2CRXF_STS_RX_BYTES	GENMASK(4, 0)
#घोषणा NPCM_I2CRXF_STS_RX_THST		BIT(6)

/* NPCM_I2CFIF_CTL reg fields */
#घोषणा NPCM_I2CFIF_CTL_FIFO_EN		BIT(4)

/* NPCM_I2CRXF_CTL reg fields */
#घोषणा NPCM_I2CRXF_CTL_RX_THR		GENMASK(4, 0)
#घोषणा NPCM_I2CRXF_CTL_LAST_PEC	BIT(5)
#घोषणा NPCM_I2CRXF_CTL_THR_RXIE	BIT(6)

#घोषणा I2C_HW_FIFO_SIZE		16

/* I2C_VER reg fields */
#घोषणा I2C_VER_VERSION			GENMASK(6, 0)
#घोषणा I2C_VER_FIFO_EN			BIT(7)

/* stall/stuck समयout in us */
#घोषणा DEFAULT_STALL_COUNT		25

/* SCLFRQ field position */
#घोषणा SCLFRQ_0_TO_6			GENMASK(6, 0)
#घोषणा SCLFRQ_7_TO_8			GENMASK(8, 7)

/* supported clk settings. values in Hz. */
#घोषणा I2C_FREQ_MIN_HZ			10000
#घोषणा I2C_FREQ_MAX_HZ			I2C_MAX_FAST_MODE_PLUS_FREQ

/* Status of one I2C module */
काष्ठा npcm_i2c अणु
	काष्ठा i2c_adapter adap;
	काष्ठा device *dev;
	अचिन्हित अक्षर __iomem *reg;
	spinlock_t lock;   /* IRQ synchronization */
	काष्ठा completion cmd_complete;
	पूर्णांक cmd_err;
	काष्ठा i2c_msg *msgs;
	पूर्णांक msgs_num;
	पूर्णांक num;
	u32 apb_clk;
	काष्ठा i2c_bus_recovery_info rinfo;
	क्रमागत i2c_state state;
	क्रमागत i2c_oper operation;
	क्रमागत i2c_mode master_or_slave;
	क्रमागत i2c_state_ind stop_ind;
	u8 dest_addr;
	u8 *rd_buf;
	u16 rd_size;
	u16 rd_ind;
	u8 *wr_buf;
	u16 wr_size;
	u16 wr_ind;
	bool fअगरo_use;
	u16 PEC_mask; /* PEC bit mask per slave address */
	bool PEC_use;
	bool पढ़ो_block_use;
	अचिन्हित दीर्घ पूर्णांक_समय_stamp;
	अचिन्हित दीर्घ bus_freq; /* in Hz */
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	u8 own_slave_addr;
	काष्ठा i2c_client *slave;
	पूर्णांक slv_rd_size;
	पूर्णांक slv_rd_ind;
	पूर्णांक slv_wr_size;
	पूर्णांक slv_wr_ind;
	u8 slv_rd_buf[I2C_HW_FIFO_SIZE];
	u8 slv_wr_buf[I2C_HW_FIFO_SIZE];
#पूर्ण_अगर
	काष्ठा dentry *debugfs; /* debugfs device directory */
	u64 ber_cnt;
	u64 rec_succ_cnt;
	u64 rec_fail_cnt;
	u64 nack_cnt;
	u64 समयout_cnt;
पूर्ण;

अटल अंतरभूत व्योम npcm_i2c_select_bank(काष्ठा npcm_i2c *bus,
					क्रमागत i2c_bank bank)
अणु
	u8 i2cctl3 = ioपढ़ो8(bus->reg + NPCM_I2CCTL3);

	अगर (bank == I2C_BANK_0)
		i2cctl3 = i2cctl3 & ~I2CCTL3_BNK_SEL;
	अन्यथा
		i2cctl3 = i2cctl3 | I2CCTL3_BNK_SEL;
	ioग_लिखो8(i2cctl3, bus->reg + NPCM_I2CCTL3);
पूर्ण

अटल व्योम npcm_i2c_init_params(काष्ठा npcm_i2c *bus)
अणु
	bus->stop_ind = I2C_NO_STATUS_IND;
	bus->rd_size = 0;
	bus->wr_size = 0;
	bus->rd_ind = 0;
	bus->wr_ind = 0;
	bus->पढ़ो_block_use = false;
	bus->पूर्णांक_समय_stamp = 0;
	bus->PEC_use = false;
	bus->PEC_mask = 0;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	अगर (bus->slave)
		bus->master_or_slave = I2C_SLAVE;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_wr_byte(काष्ठा npcm_i2c *bus, u8 data)
अणु
	ioग_लिखो8(data, bus->reg + NPCM_I2CSDA);
पूर्ण

अटल अंतरभूत u8 npcm_i2c_rd_byte(काष्ठा npcm_i2c *bus)
अणु
	वापस ioपढ़ो8(bus->reg + NPCM_I2CSDA);
पूर्ण

अटल पूर्णांक npcm_i2c_get_SCL(काष्ठा i2c_adapter *_adap)
अणु
	काष्ठा npcm_i2c *bus = container_of(_adap, काष्ठा npcm_i2c, adap);

	वापस !!(I2CCTL3_SCL_LVL & ioपढ़ो32(bus->reg + NPCM_I2CCTL3));
पूर्ण

अटल पूर्णांक npcm_i2c_get_SDA(काष्ठा i2c_adapter *_adap)
अणु
	काष्ठा npcm_i2c *bus = container_of(_adap, काष्ठा npcm_i2c, adap);

	वापस !!(I2CCTL3_SDA_LVL & ioपढ़ो32(bus->reg + NPCM_I2CCTL3));
पूर्ण

अटल अंतरभूत u16 npcm_i2c_get_index(काष्ठा npcm_i2c *bus)
अणु
	अगर (bus->operation == I2C_READ_OPER)
		वापस bus->rd_ind;
	अगर (bus->operation == I2C_WRITE_OPER)
		वापस bus->wr_ind;
	वापस 0;
पूर्ण

/* quick protocol (just address) */
अटल अंतरभूत bool npcm_i2c_is_quick(काष्ठा npcm_i2c *bus)
अणु
	वापस bus->wr_size == 0 && bus->rd_size == 0;
पूर्ण

अटल व्योम npcm_i2c_disable(काष्ठा npcm_i2c *bus)
अणु
	u8 i2cctl2;

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	पूर्णांक i;

	/* select bank 0 क्रम I2C addresses */
	npcm_i2c_select_bank(bus, I2C_BANK_0);

	/* Slave addresses removal */
	क्रम (i = I2C_SLAVE_ADDR1; i < I2C_NUM_OWN_ADDR; i++)
		ioग_लिखो8(0, bus->reg + npcm_i2caddr[i]);

	npcm_i2c_select_bank(bus, I2C_BANK_1);
#पूर्ण_अगर
	/* Disable module */
	i2cctl2 = ioपढ़ो8(bus->reg + NPCM_I2CCTL2);
	i2cctl2 = i2cctl2 & ~I2CCTL2_ENABLE;
	ioग_लिखो8(i2cctl2, bus->reg + NPCM_I2CCTL2);

	bus->state = I2C_DISABLE;
पूर्ण

अटल व्योम npcm_i2c_enable(काष्ठा npcm_i2c *bus)
अणु
	u8 i2cctl2 = ioपढ़ो8(bus->reg + NPCM_I2CCTL2);

	i2cctl2 = i2cctl2 | I2CCTL2_ENABLE;
	ioग_लिखो8(i2cctl2, bus->reg + NPCM_I2CCTL2);
	bus->state = I2C_IDLE;
पूर्ण

/* enable\disable end of busy (EOB) पूर्णांकerrupts */
अटल अंतरभूत व्योम npcm_i2c_eob_पूर्णांक(काष्ठा npcm_i2c *bus, bool enable)
अणु
	u8 val;

	/* Clear EO_BUSY pending bit: */
	val = ioपढ़ो8(bus->reg + NPCM_I2CCST3);
	val = val | NPCM_I2CCST3_EO_BUSY;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCST3);

	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val &= ~NPCM_I2CCTL1_RWS;
	अगर (enable)
		val |= NPCM_I2CCTL1_EOBINTE;
	अन्यथा
		val &= ~NPCM_I2CCTL1_EOBINTE;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);
पूर्ण

अटल अंतरभूत bool npcm_i2c_tx_fअगरo_empty(काष्ठा npcm_i2c *bus)
अणु
	u8 tx_fअगरo_sts;

	tx_fअगरo_sts = ioपढ़ो8(bus->reg + NPCM_I2CTXF_STS);
	/* check अगर TX FIFO is not empty */
	अगर ((tx_fअगरo_sts & NPCM_I2CTXF_STS_TX_BYTES) == 0)
		वापस false;

	/* check अगर TX FIFO status bit is set: */
	वापस !!FIELD_GET(NPCM_I2CTXF_STS_TX_THST, tx_fअगरo_sts);
पूर्ण

अटल अंतरभूत bool npcm_i2c_rx_fअगरo_full(काष्ठा npcm_i2c *bus)
अणु
	u8 rx_fअगरo_sts;

	rx_fअगरo_sts = ioपढ़ो8(bus->reg + NPCM_I2CRXF_STS);
	/* check अगर RX FIFO is not empty: */
	अगर ((rx_fअगरo_sts & NPCM_I2CRXF_STS_RX_BYTES) == 0)
		वापस false;

	/* check अगर rx fअगरo full status is set: */
	वापस !!FIELD_GET(NPCM_I2CRXF_STS_RX_THST, rx_fअगरo_sts);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_clear_fअगरo_पूर्णांक(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTS);
	val = (val & NPCM_I2CFIF_CTS_SLVRSTR) | NPCM_I2CFIF_CTS_RXF_TXE;
	ioग_लिखो8(val, bus->reg + NPCM_I2CFIF_CTS);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_clear_tx_fअगरo(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CTXF_STS);
	val = val | NPCM_I2CTXF_STS_TX_THST;
	ioग_लिखो8(val, bus->reg + NPCM_I2CTXF_STS);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_clear_rx_fअगरo(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CRXF_STS);
	val = val | NPCM_I2CRXF_STS_RX_THST;
	ioग_लिखो8(val, bus->reg + NPCM_I2CRXF_STS);
पूर्ण

अटल व्योम npcm_i2c_पूर्णांक_enable(काष्ठा npcm_i2c *bus, bool enable)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val &= ~NPCM_I2CCTL1_RWS;
	अगर (enable)
		val |= NPCM_I2CCTL1_INTEN;
	अन्यथा
		val &= ~NPCM_I2CCTL1_INTEN;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_master_start(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val &= ~(NPCM_I2CCTL1_STOP | NPCM_I2CCTL1_ACK);
	val |= NPCM_I2CCTL1_START;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_master_stop(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	/*
	 * override HW issue: I2C may fail to supply stop condition in Master
	 * Write operation.
	 * Need to delay at least 5 us from the last पूर्णांक, beक्रमe issueing a stop
	 */
	udelay(10); /* function called from पूर्णांकerrupt, can't sleep */
	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val &= ~(NPCM_I2CCTL1_START | NPCM_I2CCTL1_ACK);
	val |= NPCM_I2CCTL1_STOP;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);

	अगर (!bus->fअगरo_use)
		वापस;

	npcm_i2c_select_bank(bus, I2C_BANK_1);

	अगर (bus->operation == I2C_READ_OPER)
		npcm_i2c_clear_rx_fअगरo(bus);
	अन्यथा
		npcm_i2c_clear_tx_fअगरo(bus);
	npcm_i2c_clear_fअगरo_पूर्णांक(bus);
	ioग_लिखो8(0, bus->reg + NPCM_I2CTXF_CTL);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_stall_after_start(काष्ठा npcm_i2c *bus, bool stall)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val &= ~NPCM_I2CCTL1_RWS;
	अगर (stall)
		val |= NPCM_I2CCTL1_STASTRE;
	अन्यथा
		val &= ~NPCM_I2CCTL1_STASTRE;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_nack(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val &= ~(NPCM_I2CCTL1_STOP | NPCM_I2CCTL1_START);
	val |= NPCM_I2CCTL1_ACK;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
अटल व्योम npcm_i2c_slave_पूर्णांक_enable(काष्ठा npcm_i2c *bus, bool enable)
अणु
	u8 i2cctl1;

	/* enable पूर्णांकerrupt on slave match: */
	i2cctl1 = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	i2cctl1 &= ~NPCM_I2CCTL1_RWS;
	अगर (enable)
		i2cctl1 |= NPCM_I2CCTL1_NMINTE;
	अन्यथा
		i2cctl1 &= ~NPCM_I2CCTL1_NMINTE;
	ioग_लिखो8(i2cctl1, bus->reg + NPCM_I2CCTL1);
पूर्ण

अटल पूर्णांक npcm_i2c_slave_enable(काष्ठा npcm_i2c *bus, क्रमागत i2c_addr addr_type,
				 u8 addr, bool enable)
अणु
	u8 i2cctl1;
	u8 i2cctl3;
	u8 sa_reg;

	sa_reg = (addr & 0x7F) | FIELD_PREP(NPCM_I2CADDR_SAEN, enable);
	अगर (addr_type == I2C_GC_ADDR) अणु
		i2cctl1 = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
		अगर (enable)
			i2cctl1 |= NPCM_I2CCTL1_GCMEN;
		अन्यथा
			i2cctl1 &= ~NPCM_I2CCTL1_GCMEN;
		ioग_लिखो8(i2cctl1, bus->reg + NPCM_I2CCTL1);
		वापस 0;
	पूर्ण
	अगर (addr_type == I2C_ARP_ADDR) अणु
		i2cctl3 = ioपढ़ो8(bus->reg + NPCM_I2CCTL3);
		अगर (enable)
			i2cctl3 |= I2CCTL3_ARPMEN;
		अन्यथा
			i2cctl3 &= ~I2CCTL3_ARPMEN;
		ioग_लिखो8(i2cctl3, bus->reg + NPCM_I2CCTL3);
		वापस 0;
	पूर्ण
	अगर (addr_type >= I2C_ARP_ADDR)
		वापस -EFAULT;
	/* select bank 0 क्रम address 3 to 10 */
	अगर (addr_type > I2C_SLAVE_ADDR2)
		npcm_i2c_select_bank(bus, I2C_BANK_0);
	/* Set and enable the address */
	ioग_लिखो8(sa_reg, bus->reg + npcm_i2caddr[addr_type]);
	npcm_i2c_slave_पूर्णांक_enable(bus, enable);
	अगर (addr_type > I2C_SLAVE_ADDR2)
		npcm_i2c_select_bank(bus, I2C_BANK_1);
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम npcm_i2c_reset(काष्ठा npcm_i2c *bus)
अणु
	/*
	 * Save I2CCTL1 relevant bits. It is being cleared when the module
	 *  is disabled.
	 */
	u8 i2cctl1;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	u8 addr;
#पूर्ण_अगर

	i2cctl1 = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);

	npcm_i2c_disable(bus);
	npcm_i2c_enable(bus);

	/* Restore NPCM_I2CCTL1 Status */
	i2cctl1 &= ~NPCM_I2CCTL1_RWS;
	ioग_लिखो8(i2cctl1, bus->reg + NPCM_I2CCTL1);

	/* Clear BB (BUS BUSY) bit */
	ioग_लिखो8(NPCM_I2CCST_BB, bus->reg + NPCM_I2CCST);
	ioग_लिखो8(0xFF, bus->reg + NPCM_I2CST);

	/* Clear EOB bit */
	ioग_लिखो8(NPCM_I2CCST3_EO_BUSY, bus->reg + NPCM_I2CCST3);

	/* Clear all fअगरo bits: */
	ioग_लिखो8(NPCM_I2CFIF_CTS_CLR_FIFO, bus->reg + NPCM_I2CFIF_CTS);

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	अगर (bus->slave) अणु
		addr = bus->slave->addr;
		npcm_i2c_slave_enable(bus, I2C_SLAVE_ADDR1, addr, true);
	पूर्ण
#पूर्ण_अगर

	bus->state = I2C_IDLE;
पूर्ण

अटल अंतरभूत bool npcm_i2c_is_master(काष्ठा npcm_i2c *bus)
अणु
	वापस !!FIELD_GET(NPCM_I2CST_MASTER, ioपढ़ो8(bus->reg + NPCM_I2CST));
पूर्ण

अटल व्योम npcm_i2c_callback(काष्ठा npcm_i2c *bus,
			      क्रमागत i2c_state_ind op_status, u16 info)
अणु
	काष्ठा i2c_msg *msgs;
	पूर्णांक msgs_num;

	msgs = bus->msgs;
	msgs_num = bus->msgs_num;
	/*
	 * check that transaction was not समयd-out, and msgs still
	 * holds a valid value.
	 */
	अगर (!msgs)
		वापस;

	अगर (completion_करोne(&bus->cmd_complete))
		वापस;

	चयन (op_status) अणु
	हाल I2C_MASTER_DONE_IND:
		bus->cmd_err = bus->msgs_num;
		fallthrough;
	हाल I2C_BLOCK_BYTES_ERR_IND:
		/* Master tx finished and all transmit bytes were sent */
		अगर (bus->msgs) अणु
			अगर (msgs[0].flags & I2C_M_RD)
				msgs[0].len = info;
			अन्यथा अगर (msgs_num == 2 &&
				 msgs[1].flags & I2C_M_RD)
				msgs[1].len = info;
		पूर्ण
		अगर (completion_करोne(&bus->cmd_complete) == false)
			complete(&bus->cmd_complete);
	अवरोध;

	हाल I2C_NACK_IND:
		/* MASTER transmit got a NACK beक्रमe tx all bytes */
		bus->cmd_err = -ENXIO;
		अगर (bus->master_or_slave == I2C_MASTER)
			complete(&bus->cmd_complete);

		अवरोध;
	हाल I2C_BUS_ERR_IND:
		/* Bus error */
		bus->cmd_err = -EAGAIN;
		अगर (bus->master_or_slave == I2C_MASTER)
			complete(&bus->cmd_complete);

		अवरोध;
	हाल I2C_WAKE_UP_IND:
		/* I2C wake up */
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	bus->operation = I2C_NO_OPER;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	अगर (bus->slave)
		bus->master_or_slave = I2C_SLAVE;
#पूर्ण_अगर
पूर्ण

अटल u8 npcm_i2c_fअगरo_usage(काष्ठा npcm_i2c *bus)
अणु
	अगर (bus->operation == I2C_WRITE_OPER)
		वापस FIELD_GET(NPCM_I2CTXF_STS_TX_BYTES,
				 ioपढ़ो8(bus->reg + NPCM_I2CTXF_STS));
	अगर (bus->operation == I2C_READ_OPER)
		वापस FIELD_GET(NPCM_I2CRXF_STS_RX_BYTES,
				 ioपढ़ो8(bus->reg + NPCM_I2CRXF_STS));
	वापस 0;
पूर्ण

अटल व्योम npcm_i2c_ग_लिखो_to_fअगरo_master(काष्ठा npcm_i2c *bus, u16 max_bytes)
अणु
	u8 size_मुक्त_fअगरo;

	/*
	 * Fill the FIFO, जबतक the FIFO is not full and there are more bytes
	 * to ग_लिखो
	 */
	size_मुक्त_fअगरo = I2C_HW_FIFO_SIZE - npcm_i2c_fअगरo_usage(bus);
	जबतक (max_bytes-- && size_मुक्त_fअगरo) अणु
		अगर (bus->wr_ind < bus->wr_size)
			npcm_i2c_wr_byte(bus, bus->wr_buf[bus->wr_ind++]);
		अन्यथा
			npcm_i2c_wr_byte(bus, 0xFF);
		size_मुक्त_fअगरo = I2C_HW_FIFO_SIZE - npcm_i2c_fअगरo_usage(bus);
	पूर्ण
पूर्ण

/*
 * npcm_i2c_set_fअगरo:
 * configure the FIFO beक्रमe using it. If nपढ़ो is -1 RX FIFO will not be
 * configured. same क्रम nग_लिखो
 */
अटल व्योम npcm_i2c_set_fअगरo(काष्ठा npcm_i2c *bus, पूर्णांक nपढ़ो, पूर्णांक nग_लिखो)
अणु
	u8 rxf_ctl = 0;

	अगर (!bus->fअगरo_use)
		वापस;
	npcm_i2c_select_bank(bus, I2C_BANK_1);
	npcm_i2c_clear_tx_fअगरo(bus);
	npcm_i2c_clear_rx_fअगरo(bus);

	/* configure RX FIFO */
	अगर (nपढ़ो > 0) अणु
		rxf_ctl = min_t(पूर्णांक, nपढ़ो, I2C_HW_FIFO_SIZE);

		/* set LAST bit. अगर LAST is set next FIFO packet is nacked */
		अगर (nपढ़ो <= I2C_HW_FIFO_SIZE)
			rxf_ctl |= NPCM_I2CRXF_CTL_LAST_PEC;

		/*
		 * अगर we are about to पढ़ो the first byte in blk rd mode,
		 * करोn't NACK it. If slave returns zero size HW can't NACK
		 * it immidiattly, it will पढ़ो extra byte and then NACK.
		 */
		अगर (bus->rd_ind == 0 && bus->पढ़ो_block_use) अणु
			/* set fअगरo to पढ़ो one byte, no last: */
			rxf_ctl = 1;
		पूर्ण

		/* set fअगरo size: */
		ioग_लिखो8(rxf_ctl, bus->reg + NPCM_I2CRXF_CTL);
	पूर्ण

	/* configure TX FIFO */
	अगर (nग_लिखो > 0) अणु
		अगर (nग_लिखो > I2C_HW_FIFO_SIZE)
			/* data to send is more then FIFO size. */
			ioग_लिखो8(I2C_HW_FIFO_SIZE, bus->reg + NPCM_I2CTXF_CTL);
		अन्यथा
			ioग_लिखो8(nग_लिखो, bus->reg + NPCM_I2CTXF_CTL);

		npcm_i2c_clear_tx_fअगरo(bus);
	पूर्ण
पूर्ण

अटल व्योम npcm_i2c_पढ़ो_fअगरo(काष्ठा npcm_i2c *bus, u8 bytes_in_fअगरo)
अणु
	u8 data;

	जबतक (bytes_in_fअगरo--) अणु
		data = npcm_i2c_rd_byte(bus);
		अगर (bus->rd_ind < bus->rd_size)
			bus->rd_buf[bus->rd_ind++] = data;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम npcm_i2c_clear_master_status(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	/* Clear NEGACK, STASTR and BER bits */
	val = NPCM_I2CST_BER | NPCM_I2CST_NEGACK | NPCM_I2CST_STASTR;
	ioग_लिखो8(val, bus->reg + NPCM_I2CST);
पूर्ण

अटल व्योम npcm_i2c_master_पात(काष्ठा npcm_i2c *bus)
अणु
	/* Only current master is allowed to issue a stop condition */
	अगर (!npcm_i2c_is_master(bus))
		वापस;

	npcm_i2c_eob_पूर्णांक(bus, true);
	npcm_i2c_master_stop(bus);
	npcm_i2c_clear_master_status(bus);
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
अटल u8 npcm_i2c_get_slave_addr(काष्ठा npcm_i2c *bus, क्रमागत i2c_addr addr_type)
अणु
	u8 slave_add;

	/* select bank 0 क्रम address 3 to 10 */
	अगर (addr_type > I2C_SLAVE_ADDR2)
		npcm_i2c_select_bank(bus, I2C_BANK_0);

	slave_add = ioपढ़ो8(bus->reg + npcm_i2caddr[(पूर्णांक)addr_type]);

	अगर (addr_type > I2C_SLAVE_ADDR2)
		npcm_i2c_select_bank(bus, I2C_BANK_1);

	वापस slave_add;
पूर्ण

अटल पूर्णांक npcm_i2c_हटाओ_slave_addr(काष्ठा npcm_i2c *bus, u8 slave_add)
अणु
	पूर्णांक i;

	/* Set the enable bit */
	slave_add |= 0x80;
	npcm_i2c_select_bank(bus, I2C_BANK_0);
	क्रम (i = I2C_SLAVE_ADDR1; i < I2C_NUM_OWN_ADDR; i++) अणु
		अगर (ioपढ़ो8(bus->reg + npcm_i2caddr[i]) == slave_add)
			ioग_लिखो8(0, bus->reg + npcm_i2caddr[i]);
	पूर्ण
	npcm_i2c_select_bank(bus, I2C_BANK_1);
	वापस 0;
पूर्ण

अटल व्योम npcm_i2c_ग_लिखो_fअगरo_slave(काष्ठा npcm_i2c *bus, u16 max_bytes)
अणु
	/*
	 * Fill the FIFO, जबतक the FIFO is not full and there are more bytes
	 * to ग_लिखो
	 */
	npcm_i2c_clear_fअगरo_पूर्णांक(bus);
	npcm_i2c_clear_tx_fअगरo(bus);
	ioग_लिखो8(0, bus->reg + NPCM_I2CTXF_CTL);
	जबतक (max_bytes-- && I2C_HW_FIFO_SIZE != npcm_i2c_fअगरo_usage(bus)) अणु
		अगर (bus->slv_wr_size <= 0)
			अवरोध;
		bus->slv_wr_ind = bus->slv_wr_ind % I2C_HW_FIFO_SIZE;
		npcm_i2c_wr_byte(bus, bus->slv_wr_buf[bus->slv_wr_ind]);
		bus->slv_wr_ind++;
		bus->slv_wr_ind = bus->slv_wr_ind % I2C_HW_FIFO_SIZE;
		bus->slv_wr_size--;
	पूर्ण
पूर्ण

अटल व्योम npcm_i2c_पढ़ो_fअगरo_slave(काष्ठा npcm_i2c *bus, u8 bytes_in_fअगरo)
अणु
	u8 data;

	अगर (!bus->slave)
		वापस;

	जबतक (bytes_in_fअगरo--) अणु
		data = npcm_i2c_rd_byte(bus);

		bus->slv_rd_ind = bus->slv_rd_ind % I2C_HW_FIFO_SIZE;
		bus->slv_rd_buf[bus->slv_rd_ind] = data;
		bus->slv_rd_ind++;

		/* 1st byte is length in block protocol: */
		अगर (bus->slv_rd_ind == 1 && bus->पढ़ो_block_use)
			bus->slv_rd_size = data + bus->PEC_use + 1;
	पूर्ण
पूर्ण

अटल पूर्णांक npcm_i2c_slave_get_wr_buf(काष्ठा npcm_i2c *bus)
अणु
	पूर्णांक i;
	u8 value;
	पूर्णांक ind;
	पूर्णांक ret = bus->slv_wr_ind;

	/* fill a cyclic buffer */
	क्रम (i = 0; i < I2C_HW_FIFO_SIZE; i++) अणु
		अगर (bus->slv_wr_size >= I2C_HW_FIFO_SIZE)
			अवरोध;
		i2c_slave_event(bus->slave, I2C_SLAVE_READ_REQUESTED, &value);
		ind = (bus->slv_wr_ind + bus->slv_wr_size) % I2C_HW_FIFO_SIZE;
		bus->slv_wr_buf[ind] = value;
		bus->slv_wr_size++;
		i2c_slave_event(bus->slave, I2C_SLAVE_READ_PROCESSED, &value);
	पूर्ण
	वापस I2C_HW_FIFO_SIZE - ret;
पूर्ण

अटल व्योम npcm_i2c_slave_send_rd_buf(काष्ठा npcm_i2c *bus)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < bus->slv_rd_ind; i++)
		i2c_slave_event(bus->slave, I2C_SLAVE_WRITE_RECEIVED,
				&bus->slv_rd_buf[i]);
	/*
	 * once we send bytes up, need to reset the counter of the wr buf
	 * got data from master (new offset in device), ignore wr fअगरo:
	 */
	अगर (bus->slv_rd_ind) अणु
		bus->slv_wr_size = 0;
		bus->slv_wr_ind = 0;
	पूर्ण

	bus->slv_rd_ind = 0;
	bus->slv_rd_size = bus->adap.quirks->max_पढ़ो_len;

	npcm_i2c_clear_fअगरo_पूर्णांक(bus);
	npcm_i2c_clear_rx_fअगरo(bus);
पूर्ण

अटल व्योम npcm_i2c_slave_receive(काष्ठा npcm_i2c *bus, u16 nपढ़ो,
				   u8 *पढ़ो_data)
अणु
	bus->state = I2C_OPER_STARTED;
	bus->operation = I2C_READ_OPER;
	bus->slv_rd_size = nपढ़ो;
	bus->slv_rd_ind = 0;

	ioग_लिखो8(0, bus->reg + NPCM_I2CTXF_CTL);
	ioग_लिखो8(I2C_HW_FIFO_SIZE, bus->reg + NPCM_I2CRXF_CTL);
	npcm_i2c_clear_tx_fअगरo(bus);
	npcm_i2c_clear_rx_fअगरo(bus);
पूर्ण

अटल व्योम npcm_i2c_slave_xmit(काष्ठा npcm_i2c *bus, u16 nग_लिखो,
				u8 *ग_लिखो_data)
अणु
	अगर (nग_लिखो == 0)
		वापस;

	bus->state = I2C_OPER_STARTED;
	bus->operation = I2C_WRITE_OPER;

	/* get the next buffer */
	npcm_i2c_slave_get_wr_buf(bus);
	npcm_i2c_ग_लिखो_fअगरo_slave(bus, nग_लिखो);
पूर्ण

/*
 * npcm_i2c_slave_wr_buf_sync:
 * currently slave IF only supports single byte operations.
 * in order to utilyze the npcm HW FIFO, the driver will ask क्रम 16 bytes
 * at a समय, pack them in buffer, and then transmit them all together
 * to the FIFO and onward to the bus.
 * NACK on पढ़ो will be once reached to bus->adap->quirks->max_पढ़ो_len.
 * sending a NACK wherever the backend requests क्रम it is not supported.
 * the next two functions allow पढ़ोing to local buffer beक्रमe writing it all
 * to the HW FIFO.
 */
अटल व्योम npcm_i2c_slave_wr_buf_sync(काष्ठा npcm_i2c *bus)
अणु
	पूर्णांक left_in_fअगरo;

	left_in_fअगरo = FIELD_GET(NPCM_I2CTXF_STS_TX_BYTES,
				 ioपढ़ो8(bus->reg + NPCM_I2CTXF_STS));

	/* fअगरo alपढ़ोy full: */
	अगर (left_in_fअगरo >= I2C_HW_FIFO_SIZE ||
	    bus->slv_wr_size >= I2C_HW_FIFO_SIZE)
		वापस;

	/* update the wr fअगरo index back to the untransmitted bytes: */
	bus->slv_wr_ind = bus->slv_wr_ind - left_in_fअगरo;
	bus->slv_wr_size = bus->slv_wr_size + left_in_fअगरo;

	अगर (bus->slv_wr_ind < 0)
		bus->slv_wr_ind += I2C_HW_FIFO_SIZE;
पूर्ण

अटल व्योम npcm_i2c_slave_rd_wr(काष्ठा npcm_i2c *bus)
अणु
	अगर (NPCM_I2CST_XMIT & ioपढ़ो8(bus->reg + NPCM_I2CST)) अणु
		/*
		 * Slave got an address match with direction bit 1 so it should
		 * transmit data. Write till the master will NACK
		 */
		bus->operation = I2C_WRITE_OPER;
		npcm_i2c_slave_xmit(bus, bus->adap.quirks->max_ग_लिखो_len,
				    bus->slv_wr_buf);
	पूर्ण अन्यथा अणु
		/*
		 * Slave got an address match with direction bit 0 so it should
		 * receive data.
		 * this module करोes not support saying no to bytes.
		 * it will always ACK.
		 */
		bus->operation = I2C_READ_OPER;
		npcm_i2c_पढ़ो_fअगरo_slave(bus, npcm_i2c_fअगरo_usage(bus));
		bus->stop_ind = I2C_SLAVE_RCV_IND;
		npcm_i2c_slave_send_rd_buf(bus);
		npcm_i2c_slave_receive(bus, bus->adap.quirks->max_पढ़ो_len,
				       bus->slv_rd_buf);
	पूर्ण
पूर्ण

अटल irqवापस_t npcm_i2c_पूर्णांक_slave_handler(काष्ठा npcm_i2c *bus)
अणु
	u8 val;
	irqवापस_t ret = IRQ_NONE;
	u8 i2cst = ioपढ़ो8(bus->reg + NPCM_I2CST);

	/* Slave: A NACK has occurred */
	अगर (NPCM_I2CST_NEGACK & i2cst) अणु
		bus->stop_ind = I2C_NACK_IND;
		npcm_i2c_slave_wr_buf_sync(bus);
		अगर (bus->fअगरo_use)
			/* clear the FIFO */
			ioग_लिखो8(NPCM_I2CFIF_CTS_CLR_FIFO,
				 bus->reg + NPCM_I2CFIF_CTS);

		/* In slave ग_लिखो, NACK is OK, otherwise it is a problem */
		bus->stop_ind = I2C_NO_STATUS_IND;
		bus->operation = I2C_NO_OPER;
		bus->own_slave_addr = 0xFF;

		/*
		 * Slave has to रुको क्रम STOP to decide this is the end
		 * of the transaction. tx is not yet considered as करोne
		 */
		ioग_लिखो8(NPCM_I2CST_NEGACK, bus->reg + NPCM_I2CST);

		ret = IRQ_HANDLED;
	पूर्ण

	/* Slave mode: a Bus Error (BER) has been identअगरied */
	अगर (NPCM_I2CST_BER & i2cst) अणु
		/*
		 * Check whether bus arbitration or Start or Stop during data
		 * xfer bus arbitration problem should not result in recovery
		 */
		bus->stop_ind = I2C_BUS_ERR_IND;

		/* रुको क्रम bus busy beक्रमe clear fअगरo */
		ioग_लिखो8(NPCM_I2CFIF_CTS_CLR_FIFO, bus->reg + NPCM_I2CFIF_CTS);

		bus->state = I2C_IDLE;

		/*
		 * in BER हाल we might get 2 पूर्णांकerrupts: one क्रम slave one क्रम
		 * master ( क्रम a channel which is master\slave चयनing)
		 */
		अगर (completion_करोne(&bus->cmd_complete) == false) अणु
			bus->cmd_err = -EIO;
			complete(&bus->cmd_complete);
		पूर्ण
		bus->own_slave_addr = 0xFF;
		ioग_लिखो8(NPCM_I2CST_BER, bus->reg + NPCM_I2CST);
		ret = IRQ_HANDLED;
	पूर्ण

	/* A Slave Stop Condition has been identअगरied */
	अगर (NPCM_I2CST_SLVSTP & i2cst) अणु
		u8 bytes_in_fअगरo = npcm_i2c_fअगरo_usage(bus);

		bus->stop_ind = I2C_SLAVE_DONE_IND;

		अगर (bus->operation == I2C_READ_OPER)
			npcm_i2c_पढ़ो_fअगरo_slave(bus, bytes_in_fअगरo);

		/* अगर the buffer is empty nothing will be sent */
		npcm_i2c_slave_send_rd_buf(bus);

		/* Slave करोne transmitting or receiving */
		bus->stop_ind = I2C_NO_STATUS_IND;

		/*
		 * Note, just because we got here, it करोesn't mean we through
		 * away the wr buffer.
		 * we keep it until the next received offset.
		 */
		bus->operation = I2C_NO_OPER;
		bus->own_slave_addr = 0xFF;
		i2c_slave_event(bus->slave, I2C_SLAVE_STOP, 0);
		ioग_लिखो8(NPCM_I2CST_SLVSTP, bus->reg + NPCM_I2CST);
		अगर (bus->fअगरo_use) अणु
			npcm_i2c_clear_fअगरo_पूर्णांक(bus);
			npcm_i2c_clear_rx_fअगरo(bus);
			npcm_i2c_clear_tx_fअगरo(bus);

			ioग_लिखो8(NPCM_I2CFIF_CTS_CLR_FIFO,
				 bus->reg + NPCM_I2CFIF_CTS);
		पूर्ण
		bus->state = I2C_IDLE;
		ret = IRQ_HANDLED;
	पूर्ण

	/* restart condition occurred and Rx-FIFO was not empty */
	अगर (bus->fअगरo_use && FIELD_GET(NPCM_I2CFIF_CTS_SLVRSTR,
				       ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTS))) अणु
		bus->stop_ind = I2C_SLAVE_RESTART_IND;
		bus->master_or_slave = I2C_SLAVE;
		अगर (bus->operation == I2C_READ_OPER)
			npcm_i2c_पढ़ो_fअगरo_slave(bus, npcm_i2c_fअगरo_usage(bus));
		bus->operation = I2C_WRITE_OPER;
		ioग_लिखो8(0, bus->reg + NPCM_I2CRXF_CTL);
		val = NPCM_I2CFIF_CTS_CLR_FIFO | NPCM_I2CFIF_CTS_SLVRSTR |
		      NPCM_I2CFIF_CTS_RXF_TXE;
		ioग_लिखो8(val, bus->reg + NPCM_I2CFIF_CTS);
		npcm_i2c_slave_rd_wr(bus);
		ret = IRQ_HANDLED;
	पूर्ण

	/* A Slave Address Match has been identअगरied */
	अगर (NPCM_I2CST_NMATCH & i2cst) अणु
		u8 info = 0;

		/* Address match स्वतःmatically implies slave mode */
		bus->master_or_slave = I2C_SLAVE;
		npcm_i2c_clear_fअगरo_पूर्णांक(bus);
		npcm_i2c_clear_rx_fअगरo(bus);
		npcm_i2c_clear_tx_fअगरo(bus);
		ioग_लिखो8(0, bus->reg + NPCM_I2CTXF_CTL);
		ioग_लिखो8(I2C_HW_FIFO_SIZE, bus->reg + NPCM_I2CRXF_CTL);
		अगर (NPCM_I2CST_XMIT & i2cst) अणु
			bus->operation = I2C_WRITE_OPER;
		पूर्ण अन्यथा अणु
			i2c_slave_event(bus->slave, I2C_SLAVE_WRITE_REQUESTED,
					&info);
			bus->operation = I2C_READ_OPER;
		पूर्ण
		अगर (bus->own_slave_addr == 0xFF) अणु
			/* Check which type of address match */
			val = ioपढ़ो8(bus->reg + NPCM_I2CCST);
			अगर (NPCM_I2CCST_MATCH & val) अणु
				u16 addr;
				क्रमागत i2c_addr eaddr;
				u8 i2ccst2;
				u8 i2ccst3;

				i2ccst3 = ioपढ़ो8(bus->reg + NPCM_I2CCST3);
				i2ccst2 = ioपढ़ो8(bus->reg + NPCM_I2CCST2);

				/*
				 * the i2c module can response to 10 own SA.
				 * check which one was addressed by the master.
				 * repond to the first one.
				 */
				addr = ((i2ccst3 & 0x07) << 7) |
					(i2ccst2 & 0x7F);
				info = ffs(addr);
				eaddr = (क्रमागत i2c_addr)info;
				addr = npcm_i2c_get_slave_addr(bus, eaddr);
				addr &= 0x7F;
				bus->own_slave_addr = addr;
				अगर (bus->PEC_mask & BIT(info))
					bus->PEC_use = true;
				अन्यथा
					bus->PEC_use = false;
			पूर्ण अन्यथा अणु
				अगर (NPCM_I2CCST_GCMATCH & val)
					bus->own_slave_addr = 0;
				अगर (NPCM_I2CCST_ARPMATCH & val)
					bus->own_slave_addr = 0x61;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			 *  Slave match can happen in two options:
			 *  1. Start, SA, पढ़ो (slave पढ़ो without further aकरो)
			 *  2. Start, SA, पढ़ो, data, restart, SA, पढ़ो,  ...
			 *     (slave पढ़ो in fragmented mode)
			 *  3. Start, SA, ग_लिखो, data, restart, SA, पढ़ो, ..
			 *     (regular ग_लिखो-पढ़ो mode)
			 */
			अगर ((bus->state == I2C_OPER_STARTED &&
			     bus->operation == I2C_READ_OPER &&
			     bus->stop_ind == I2C_SLAVE_XMIT_IND) ||
			     bus->stop_ind == I2C_SLAVE_RCV_IND) अणु
				/* slave tx after slave rx w/o STOP */
				bus->stop_ind = I2C_SLAVE_RESTART_IND;
			पूर्ण
		पूर्ण

		अगर (NPCM_I2CST_XMIT & i2cst)
			bus->stop_ind = I2C_SLAVE_XMIT_IND;
		अन्यथा
			bus->stop_ind = I2C_SLAVE_RCV_IND;
		bus->state = I2C_SLAVE_MATCH;
		npcm_i2c_slave_rd_wr(bus);
		ioग_लिखो8(NPCM_I2CST_NMATCH, bus->reg + NPCM_I2CST);
		ret = IRQ_HANDLED;
	पूर्ण

	/* Slave SDA status is set - tx or rx */
	अगर ((NPCM_I2CST_SDAST & i2cst) ||
	    (bus->fअगरo_use &&
	    (npcm_i2c_tx_fअगरo_empty(bus) || npcm_i2c_rx_fअगरo_full(bus)))) अणु
		npcm_i2c_slave_rd_wr(bus);
		ioग_लिखो8(NPCM_I2CST_SDAST, bus->reg + NPCM_I2CST);
		ret = IRQ_HANDLED;
	पूर्ण /* SDAST */

	वापस ret;
पूर्ण

अटल पूर्णांक npcm_i2c_reg_slave(काष्ठा i2c_client *client)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा npcm_i2c *bus = i2c_get_adapdata(client->adapter);

	bus->slave = client;

	अगर (!bus->slave)
		वापस -EINVAL;

	अगर (client->flags & I2C_CLIENT_TEN)
		वापस -EAFNOSUPPORT;

	spin_lock_irqsave(&bus->lock, lock_flags);

	npcm_i2c_init_params(bus);
	bus->slv_rd_size = 0;
	bus->slv_wr_size = 0;
	bus->slv_rd_ind = 0;
	bus->slv_wr_ind = 0;
	अगर (client->flags & I2C_CLIENT_PEC)
		bus->PEC_use = true;

	dev_info(bus->dev, "i2c%d register slave SA=0x%x, PEC=%d\n", bus->num,
		 client->addr, bus->PEC_use);

	npcm_i2c_slave_enable(bus, I2C_SLAVE_ADDR1, client->addr, true);
	npcm_i2c_clear_fअगरo_पूर्णांक(bus);
	npcm_i2c_clear_rx_fअगरo(bus);
	npcm_i2c_clear_tx_fअगरo(bus);
	npcm_i2c_slave_पूर्णांक_enable(bus, true);

	spin_unlock_irqrestore(&bus->lock, lock_flags);
	वापस 0;
पूर्ण

अटल पूर्णांक npcm_i2c_unreg_slave(काष्ठा i2c_client *client)
अणु
	काष्ठा npcm_i2c *bus = client->adapter->algo_data;
	अचिन्हित दीर्घ lock_flags;

	spin_lock_irqsave(&bus->lock, lock_flags);
	अगर (!bus->slave) अणु
		spin_unlock_irqrestore(&bus->lock, lock_flags);
		वापस -EINVAL;
	पूर्ण
	npcm_i2c_slave_पूर्णांक_enable(bus, false);
	npcm_i2c_हटाओ_slave_addr(bus, client->addr);
	bus->slave = शून्य;
	spin_unlock_irqrestore(&bus->lock, lock_flags);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_I2C_SLAVE */

अटल व्योम npcm_i2c_master_fअगरo_पढ़ो(काष्ठा npcm_i2c *bus)
अणु
	पूर्णांक rcount;
	पूर्णांक fअगरo_bytes;
	क्रमागत i2c_state_ind ind = I2C_MASTER_DONE_IND;

	fअगरo_bytes = npcm_i2c_fअगरo_usage(bus);
	rcount = bus->rd_size - bus->rd_ind;

	/*
	 * In order not to change the RX_TRH during transaction (we found that
	 * this might be problematic अगर it takes too much समय to पढ़ो the FIFO)
	 * we पढ़ो the data in the following way. If the number of bytes to
	 * पढ़ो == FIFO Size + C (where C < FIFO Size)then first पढ़ो C bytes
	 * and in the next पूर्णांक we पढ़ो rest of the data.
	 */
	अगर (rcount < (2 * I2C_HW_FIFO_SIZE) && rcount > I2C_HW_FIFO_SIZE)
		fअगरo_bytes = rcount - I2C_HW_FIFO_SIZE;

	अगर (rcount <= fअगरo_bytes) अणु
		/* last bytes are about to be पढ़ो - end of tx */
		bus->state = I2C_STOP_PENDING;
		bus->stop_ind = ind;
		npcm_i2c_eob_पूर्णांक(bus, true);
		/* Stop should be set beक्रमe पढ़ोing last byte. */
		npcm_i2c_master_stop(bus);
		npcm_i2c_पढ़ो_fअगरo(bus, fअगरo_bytes);
	पूर्ण अन्यथा अणु
		npcm_i2c_पढ़ो_fअगरo(bus, fअगरo_bytes);
		rcount = bus->rd_size - bus->rd_ind;
		npcm_i2c_set_fअगरo(bus, rcount, -1);
	पूर्ण
पूर्ण

अटल व्योम npcm_i2c_irq_master_handler_ग_लिखो(काष्ठा npcm_i2c *bus)
अणु
	u16 wcount;

	अगर (bus->fअगरo_use)
		npcm_i2c_clear_tx_fअगरo(bus); /* clear the TX fअगरo status bit */

	/* Master ग_लिखो operation - last byte handling */
	अगर (bus->wr_ind == bus->wr_size) अणु
		अगर (bus->fअगरo_use && npcm_i2c_fअगरo_usage(bus) > 0)
			/*
			 * No more bytes to send (to add to the FIFO),
			 * however the FIFO is not empty yet. It is
			 * still in the middle of tx. Currently there's nothing
			 * to करो except क्रम रुकोing to the end of the tx
			 * We will get an पूर्णांक when the FIFO will get empty.
			 */
			वापस;

		अगर (bus->rd_size == 0) अणु
			/* all bytes have been written, in wr only operation */
			npcm_i2c_eob_पूर्णांक(bus, true);
			bus->state = I2C_STOP_PENDING;
			bus->stop_ind = I2C_MASTER_DONE_IND;
			npcm_i2c_master_stop(bus);
			/* Clear SDA Status bit (by writing dummy byte) */
			npcm_i2c_wr_byte(bus, 0xFF);

		पूर्ण अन्यथा अणु
			/* last ग_लिखो-byte written on previous पूर्णांक - restart */
			npcm_i2c_set_fअगरo(bus, bus->rd_size, -1);
			/* Generate repeated start upon next ग_लिखो to SDA */
			npcm_i2c_master_start(bus);

			/*
			 * Receiving one byte only - stall after successful
			 * completion of send address byte. If we NACK here, and
			 * slave करोesn't ACK the address, we might
			 * unपूर्णांकentionally NACK the next multi-byte पढ़ो.
			 */
			अगर (bus->rd_size == 1)
				npcm_i2c_stall_after_start(bus, true);

			/* Next पूर्णांक will occur on पढ़ो */
			bus->operation = I2C_READ_OPER;
			/* send the slave address in पढ़ो direction */
			npcm_i2c_wr_byte(bus, bus->dest_addr | 0x1);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* ग_लिखो next byte not last byte and not slave address */
		अगर (!bus->fअगरo_use || bus->wr_size == 1) अणु
			npcm_i2c_wr_byte(bus, bus->wr_buf[bus->wr_ind++]);
		पूर्ण अन्यथा अणु
			wcount = bus->wr_size - bus->wr_ind;
			npcm_i2c_set_fअगरo(bus, -1, wcount);
			अगर (wcount)
				npcm_i2c_ग_लिखो_to_fअगरo_master(bus, wcount);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम npcm_i2c_irq_master_handler_पढ़ो(काष्ठा npcm_i2c *bus)
अणु
	u16 block_extra_bytes_size;
	u8 data;

	/* added bytes to the packet: */
	block_extra_bytes_size = bus->पढ़ो_block_use + bus->PEC_use;

	/*
	 * Perक्रमm master पढ़ो, distinguishing between last byte and the rest of
	 * the bytes. The last byte should be पढ़ो when the घड़ी is stopped
	 */
	अगर (bus->rd_ind == 0) अणु /* first byte handling: */
		अगर (bus->पढ़ो_block_use) अणु
			/* first byte in block protocol is the size: */
			data = npcm_i2c_rd_byte(bus);
			data = clamp_val(data, 1, I2C_SMBUS_BLOCK_MAX);
			bus->rd_size = data + block_extra_bytes_size;
			bus->rd_buf[bus->rd_ind++] = data;

			/* clear RX FIFO पूर्णांकerrupt status: */
			अगर (bus->fअगरo_use) अणु
				data = ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTS);
				data = data | NPCM_I2CFIF_CTS_RXF_TXE;
				ioग_लिखो8(data, bus->reg + NPCM_I2CFIF_CTS);
			पूर्ण

			npcm_i2c_set_fअगरo(bus, bus->rd_size - 1, -1);
			npcm_i2c_stall_after_start(bus, false);
		पूर्ण अन्यथा अणु
			npcm_i2c_clear_tx_fअगरo(bus);
			npcm_i2c_master_fअगरo_पढ़ो(bus);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (bus->rd_size == block_extra_bytes_size &&
		    bus->पढ़ो_block_use) अणु
			bus->state = I2C_STOP_PENDING;
			bus->stop_ind = I2C_BLOCK_BYTES_ERR_IND;
			bus->cmd_err = -EIO;
			npcm_i2c_eob_पूर्णांक(bus, true);
			npcm_i2c_master_stop(bus);
			npcm_i2c_पढ़ो_fअगरo(bus, npcm_i2c_fअगरo_usage(bus));
		पूर्ण अन्यथा अणु
			npcm_i2c_master_fअगरo_पढ़ो(bus);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम npcm_i2c_irq_handle_nmatch(काष्ठा npcm_i2c *bus)
अणु
	ioग_लिखो8(NPCM_I2CST_NMATCH, bus->reg + NPCM_I2CST);
	npcm_i2c_nack(bus);
	bus->stop_ind = I2C_BUS_ERR_IND;
	npcm_i2c_callback(bus, bus->stop_ind, npcm_i2c_get_index(bus));
पूर्ण

/* A NACK has occurred */
अटल व्योम npcm_i2c_irq_handle_nack(काष्ठा npcm_i2c *bus)
अणु
	u8 val;

	अगर (bus->nack_cnt < ULदीर्घ_उच्च)
		bus->nack_cnt++;

	अगर (bus->fअगरo_use) अणु
		/*
		 * अगर there are still untransmitted bytes in TX FIFO
		 * reduce them from wr_ind
		 */
		अगर (bus->operation == I2C_WRITE_OPER)
			bus->wr_ind -= npcm_i2c_fअगरo_usage(bus);

		/* clear the FIFO */
		ioग_लिखो8(NPCM_I2CFIF_CTS_CLR_FIFO, bus->reg + NPCM_I2CFIF_CTS);
	पूर्ण

	/* In master ग_लिखो operation, got unexpected NACK */
	bus->stop_ind = I2C_NACK_IND;
	/* Only current master is allowed to issue Stop Condition */
	अगर (npcm_i2c_is_master(bus)) अणु
		/* stopping in the middle */
		npcm_i2c_eob_पूर्णांक(bus, false);
		npcm_i2c_master_stop(bus);

		/*
		 * The bus is released from stall only after the SW clears
		 * NEGACK bit. Then a Stop condition is sent.
		 */
		npcm_i2c_clear_master_status(bus);
		पढ़ोx_poll_समयout_atomic(ioपढ़ो8, bus->reg + NPCM_I2CCST, val,
					  !(val & NPCM_I2CCST_BUSY), 10, 200);
	पूर्ण
	bus->state = I2C_IDLE;

	/*
	 * In Master mode, NACK should be cleared only after STOP.
	 * In such हाल, the bus is released from stall only after the
	 * software clears NACK bit. Then a Stop condition is sent.
	 */
	npcm_i2c_callback(bus, bus->stop_ind, bus->wr_ind);
पूर्ण

	/* Master mode: a Bus Error has been identअगरied */
अटल व्योम npcm_i2c_irq_handle_ber(काष्ठा npcm_i2c *bus)
अणु
	अगर (bus->ber_cnt < ULदीर्घ_उच्च)
		bus->ber_cnt++;
	bus->stop_ind = I2C_BUS_ERR_IND;
	अगर (npcm_i2c_is_master(bus)) अणु
		npcm_i2c_master_पात(bus);
	पूर्ण अन्यथा अणु
		npcm_i2c_clear_master_status(bus);

		/* Clear BB (BUS BUSY) bit */
		ioग_लिखो8(NPCM_I2CCST_BB, bus->reg + NPCM_I2CCST);

		bus->cmd_err = -EAGAIN;
		npcm_i2c_callback(bus, bus->stop_ind, npcm_i2c_get_index(bus));
	पूर्ण
	bus->state = I2C_IDLE;
पूर्ण

	/* EOB: a master End Of Busy (meaning STOP completed) */
अटल व्योम npcm_i2c_irq_handle_eob(काष्ठा npcm_i2c *bus)
अणु
	npcm_i2c_eob_पूर्णांक(bus, false);
	bus->state = I2C_IDLE;
	npcm_i2c_callback(bus, bus->stop_ind, bus->rd_ind);
पूर्ण

/* Address sent and requested stall occurred (Master mode) */
अटल व्योम npcm_i2c_irq_handle_stall_after_start(काष्ठा npcm_i2c *bus)
अणु
	अगर (npcm_i2c_is_quick(bus)) अणु
		bus->state = I2C_STOP_PENDING;
		bus->stop_ind = I2C_MASTER_DONE_IND;
		npcm_i2c_eob_पूर्णांक(bus, true);
		npcm_i2c_master_stop(bus);
	पूर्ण अन्यथा अगर ((bus->rd_size == 1) && !bus->पढ़ो_block_use) अणु
		/*
		 * Receiving one byte only - set NACK after ensuring
		 * slave ACKed the address byte.
		 */
		npcm_i2c_nack(bus);
	पूर्ण

	/* Reset stall-after-address-byte */
	npcm_i2c_stall_after_start(bus, false);

	/* Clear stall only after setting STOP */
	ioग_लिखो8(NPCM_I2CST_STASTR, bus->reg + NPCM_I2CST);
पूर्ण

/* SDA status is set - TX or RX, master */
अटल व्योम npcm_i2c_irq_handle_sda(काष्ठा npcm_i2c *bus, u8 i2cst)
अणु
	u8 fअगर_cts;

	अगर (!npcm_i2c_is_master(bus))
		वापस;

	अगर (bus->state == I2C_IDLE) अणु
		bus->stop_ind = I2C_WAKE_UP_IND;

		अगर (npcm_i2c_is_quick(bus) || bus->पढ़ो_block_use)
			/*
			 * Need to stall after successful
			 * completion of sending address byte
			 */
			npcm_i2c_stall_after_start(bus, true);
		अन्यथा
			npcm_i2c_stall_after_start(bus, false);

		/*
		 * Receiving one byte only - stall after successful completion
		 * of sending address byte If we NACK here, and slave करोesn't
		 * ACK the address, we might unपूर्णांकentionally NACK the next
		 * multi-byte पढ़ो
		 */
		अगर (bus->wr_size == 0 && bus->rd_size == 1)
			npcm_i2c_stall_after_start(bus, true);

		/* Initiate I2C master tx */

		/* select bank 1 क्रम FIFO regs */
		npcm_i2c_select_bank(bus, I2C_BANK_1);

		fअगर_cts = ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTS);
		fअगर_cts = fअगर_cts & ~NPCM_I2CFIF_CTS_SLVRSTR;

		/* clear FIFO and relevant status bits. */
		fअगर_cts = fअगर_cts | NPCM_I2CFIF_CTS_CLR_FIFO;
		ioग_लिखो8(fअगर_cts, bus->reg + NPCM_I2CFIF_CTS);

		/* re-enable */
		fअगर_cts = fअगर_cts | NPCM_I2CFIF_CTS_RXF_TXE;
		ioग_लिखो8(fअगर_cts, bus->reg + NPCM_I2CFIF_CTS);

		/*
		 * Configure the FIFO threshold:
		 * according to the needed # of bytes to पढ़ो.
		 * Note: due to HW limitation can't config the rx fअगरo beक्रमe it
		 * got and ACK on the restart. LAST bit will not be reset unless
		 * RX completed. It will stay set on the next tx.
		 */
		अगर (bus->wr_size)
			npcm_i2c_set_fअगरo(bus, -1, bus->wr_size);
		अन्यथा
			npcm_i2c_set_fअगरo(bus, bus->rd_size, -1);

		bus->state = I2C_OPER_STARTED;

		अगर (npcm_i2c_is_quick(bus) || bus->wr_size)
			npcm_i2c_wr_byte(bus, bus->dest_addr);
		अन्यथा
			npcm_i2c_wr_byte(bus, bus->dest_addr | BIT(0));
	/* SDA पूर्णांकerrupt, after start\लestart */
	पूर्ण अन्यथा अणु
		अगर (NPCM_I2CST_XMIT & i2cst) अणु
			bus->operation = I2C_WRITE_OPER;
			npcm_i2c_irq_master_handler_ग_लिखो(bus);
		पूर्ण अन्यथा अणु
			bus->operation = I2C_READ_OPER;
			npcm_i2c_irq_master_handler_पढ़ो(bus);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक npcm_i2c_पूर्णांक_master_handler(काष्ठा npcm_i2c *bus)
अणु
	u8 i2cst;
	पूर्णांक ret = -EIO;

	i2cst = ioपढ़ो8(bus->reg + NPCM_I2CST);

	अगर (FIELD_GET(NPCM_I2CST_NMATCH, i2cst)) अणु
		npcm_i2c_irq_handle_nmatch(bus);
		वापस 0;
	पूर्ण
	/* A NACK has occurred */
	अगर (FIELD_GET(NPCM_I2CST_NEGACK, i2cst)) अणु
		npcm_i2c_irq_handle_nack(bus);
		वापस 0;
	पूर्ण

	/* Master mode: a Bus Error has been identअगरied */
	अगर (FIELD_GET(NPCM_I2CST_BER, i2cst)) अणु
		npcm_i2c_irq_handle_ber(bus);
		वापस 0;
	पूर्ण

	/* EOB: a master End Of Busy (meaning STOP completed) */
	अगर ((FIELD_GET(NPCM_I2CCTL1_EOBINTE,
		       ioपढ़ो8(bus->reg + NPCM_I2CCTL1)) == 1) &&
	    (FIELD_GET(NPCM_I2CCST3_EO_BUSY,
		       ioपढ़ो8(bus->reg + NPCM_I2CCST3)))) अणु
		npcm_i2c_irq_handle_eob(bus);
		वापस 0;
	पूर्ण

	/* Address sent and requested stall occurred (Master mode) */
	अगर (FIELD_GET(NPCM_I2CST_STASTR, i2cst)) अणु
		npcm_i2c_irq_handle_stall_after_start(bus);
		ret = 0;
	पूर्ण

	/* SDA status is set - TX or RX, master */
	अगर (FIELD_GET(NPCM_I2CST_SDAST, i2cst) ||
	    (bus->fअगरo_use &&
	    (npcm_i2c_tx_fअगरo_empty(bus) || npcm_i2c_rx_fअगरo_full(bus)))) अणु
		npcm_i2c_irq_handle_sda(bus, i2cst);
		ret = 0;
	पूर्ण

	वापस ret;
पूर्ण

/* recovery using TGCLK functionality of the module */
अटल पूर्णांक npcm_i2c_recovery_tgclk(काष्ठा i2c_adapter *_adap)
अणु
	u8               val;
	u8               fअगर_cts;
	bool             करोne = false;
	पूर्णांक              status = -ENOTRECOVERABLE;
	काष्ठा npcm_i2c *bus = container_of(_adap, काष्ठा npcm_i2c, adap);
	/* Allow 3 bytes (27 toggles) to be पढ़ो from the slave: */
	पूर्णांक              iter = 27;

	अगर ((npcm_i2c_get_SDA(_adap) == 1) && (npcm_i2c_get_SCL(_adap) == 1)) अणु
		dev_dbg(bus->dev, "bus%d recovery skipped, bus not stuck",
			bus->num);
		npcm_i2c_reset(bus);
		वापस status;
	पूर्ण

	npcm_i2c_पूर्णांक_enable(bus, false);
	npcm_i2c_disable(bus);
	npcm_i2c_enable(bus);
	ioग_लिखो8(NPCM_I2CCST_BB, bus->reg + NPCM_I2CCST);
	npcm_i2c_clear_tx_fअगरo(bus);
	npcm_i2c_clear_rx_fअगरo(bus);
	ioग_लिखो8(0, bus->reg + NPCM_I2CRXF_CTL);
	ioग_लिखो8(0, bus->reg + NPCM_I2CTXF_CTL);
	npcm_i2c_stall_after_start(bus, false);

	/* select bank 1 क्रम FIFO regs */
	npcm_i2c_select_bank(bus, I2C_BANK_1);

	/* clear FIFO and relevant status bits. */
	fअगर_cts = ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTS);
	fअगर_cts &= ~NPCM_I2CFIF_CTS_SLVRSTR;
	fअगर_cts |= NPCM_I2CFIF_CTS_CLR_FIFO;
	ioग_लिखो8(fअगर_cts, bus->reg + NPCM_I2CFIF_CTS);
	npcm_i2c_set_fअगरo(bus, -1, 0);

	/* Repeat the following sequence until SDA is released */
	करो अणु
		/* Issue a single SCL toggle */
		ioग_लिखो8(NPCM_I2CCST_TGSCL, bus->reg + NPCM_I2CCST);
		usleep_range(20, 30);
		/* If SDA line is inactive (high), stop */
		अगर (npcm_i2c_get_SDA(_adap)) अणु
			करोne = true;
			status = 0;
		पूर्ण
	पूर्ण जबतक (!करोne && iter--);

	/* If SDA line is released: send start-addr-stop, to re-sync. */
	अगर (npcm_i2c_get_SDA(_adap)) अणु
		/* Send an address byte in ग_लिखो direction: */
		npcm_i2c_wr_byte(bus, bus->dest_addr);
		npcm_i2c_master_start(bus);
		/* Wait until START condition is sent */
		status = पढ़ोx_poll_समयout(npcm_i2c_get_SCL, _adap, val, !val,
					    20, 200);
		/* If START condition was sent */
		अगर (npcm_i2c_is_master(bus) > 0) अणु
			usleep_range(20, 30);
			npcm_i2c_master_stop(bus);
			usleep_range(200, 500);
		पूर्ण
	पूर्ण
	npcm_i2c_reset(bus);
	npcm_i2c_पूर्णांक_enable(bus, true);

	अगर ((npcm_i2c_get_SDA(_adap) == 1) && (npcm_i2c_get_SCL(_adap) == 1))
		status = 0;
	अन्यथा
		status = -ENOTRECOVERABLE;
	अगर (status) अणु
		अगर (bus->rec_fail_cnt < ULदीर्घ_उच्च)
			bus->rec_fail_cnt++;
	पूर्ण अन्यथा अणु
		अगर (bus->rec_succ_cnt < ULदीर्घ_उच्च)
			bus->rec_succ_cnt++;
	पूर्ण
	वापस status;
पूर्ण

/* recovery using bit banging functionality of the module */
अटल व्योम npcm_i2c_recovery_init(काष्ठा i2c_adapter *_adap)
अणु
	काष्ठा npcm_i2c *bus = container_of(_adap, काष्ठा npcm_i2c, adap);
	काष्ठा i2c_bus_recovery_info *rinfo = &bus->rinfo;

	rinfo->recover_bus = npcm_i2c_recovery_tgclk;

	/*
	 * npcm i2c HW allows direct पढ़ोing of SCL and SDA.
	 * However, it करोes not support setting SCL and SDA directly.
	 * The recovery function can togle SCL when SDA is low (but not set)
	 * Getter functions used पूर्णांकernally, and can be used बाह्यaly.
	 */
	rinfo->get_scl = npcm_i2c_get_SCL;
	rinfo->get_sda = npcm_i2c_get_SDA;
	_adap->bus_recovery_info = rinfo;
पूर्ण

/* SCLFRQ min/max field values */
#घोषणा SCLFRQ_MIN  10
#घोषणा SCLFRQ_MAX  511
#घोषणा clk_coef(freq, mul)	DIV_ROUND_UP((freq) * (mul), 1000000)

/*
 * npcm_i2c_init_clk: init HW timing parameters.
 * NPCM7XX i2c module timing parameters are depenent on module core clk (APB)
 * and bus frequency.
 * 100kHz bus requires tSCL = 4 * SCLFRQ * tCLK. LT and HT are simetric.
 * 400kHz bus requires assymetric HT and LT. A dअगरferent equation is recomended
 * by the HW designer, given core घड़ी range (equations in comments below).
 *
 */
अटल पूर्णांक npcm_i2c_init_clk(काष्ठा npcm_i2c *bus, u32 bus_freq_hz)
अणु
	u32  k1 = 0;
	u32  k2 = 0;
	u8   dbnct = 0;
	u32  sclfrq = 0;
	u8   hldt = 7;
	u8   fast_mode = 0;
	u32  src_clk_khz;
	u32  bus_freq_khz;

	src_clk_khz = bus->apb_clk / 1000;
	bus_freq_khz = bus_freq_hz / 1000;
	bus->bus_freq = bus_freq_hz;

	/* 100KHz and below: */
	अगर (bus_freq_hz <= I2C_MAX_STANDARD_MODE_FREQ) अणु
		sclfrq = src_clk_khz / (bus_freq_khz * 4);

		अगर (sclfrq < SCLFRQ_MIN || sclfrq > SCLFRQ_MAX)
			वापस -गलत_तर्क;

		अगर (src_clk_khz >= 40000)
			hldt = 17;
		अन्यथा अगर (src_clk_khz >= 12500)
			hldt = 15;
		अन्यथा
			hldt = 7;
	पूर्ण

	/* 400KHz: */
	अन्यथा अगर (bus_freq_hz <= I2C_MAX_FAST_MODE_FREQ) अणु
		sclfrq = 0;
		fast_mode = I2CCTL3_400K_MODE;

		अगर (src_clk_khz < 7500)
			/* 400KHZ cannot be supported क्रम core घड़ी < 7.5MHz */
			वापस -गलत_तर्क;

		अन्यथा अगर (src_clk_khz >= 50000) अणु
			k1 = 80;
			k2 = 48;
			hldt = 12;
			dbnct = 7;
		पूर्ण

		/* Master or Slave with frequency > 25MHz */
		अन्यथा अगर (src_clk_khz > 25000) अणु
			hldt = clk_coef(src_clk_khz, 300) + 7;
			k1 = clk_coef(src_clk_khz, 1600);
			k2 = clk_coef(src_clk_khz, 900);
		पूर्ण
	पूर्ण

	/* 1MHz: */
	अन्यथा अगर (bus_freq_hz <= I2C_MAX_FAST_MODE_PLUS_FREQ) अणु
		sclfrq = 0;
		fast_mode = I2CCTL3_400K_MODE;

		/* 1MHZ cannot be supported क्रम core घड़ी < 24 MHz */
		अगर (src_clk_khz < 24000)
			वापस -गलत_तर्क;

		k1 = clk_coef(src_clk_khz, 620);
		k2 = clk_coef(src_clk_khz, 380);

		/* Core clk > 40 MHz */
		अगर (src_clk_khz > 40000) अणु
			/*
			 * Set HLDT:
			 * SDA hold समय:  (HLDT-7) * T(CLK) >= 120
			 * HLDT = 120/T(CLK) + 7 = 120 * FREQ(CLK) + 7
			 */
			hldt = clk_coef(src_clk_khz, 120) + 7;
		पूर्ण अन्यथा अणु
			hldt = 7;
			dbnct = 2;
		पूर्ण
	पूर्ण

	/* Frequency larger than 1 MHz is not supported */
	अन्यथा
		वापस -EINVAL;

	अगर (bus_freq_hz >= I2C_MAX_FAST_MODE_FREQ) अणु
		k1 = round_up(k1, 2);
		k2 = round_up(k2 + 1, 2);
		अगर (k1 < SCLFRQ_MIN || k1 > SCLFRQ_MAX ||
		    k2 < SCLFRQ_MIN || k2 > SCLFRQ_MAX)
			वापस -गलत_तर्क;
	पूर्ण

	/* ग_लिखो sclfrq value. bits [6:0] are in I2CCTL2 reg */
	ioग_लिखो8(FIELD_PREP(I2CCTL2_SCLFRQ6_0, sclfrq & 0x7F),
		 bus->reg + NPCM_I2CCTL2);

	/* bits [8:7] are in I2CCTL3 reg */
	ioग_लिखो8(fast_mode | FIELD_PREP(I2CCTL3_SCLFRQ8_7, (sclfrq >> 7) & 0x3),
		 bus->reg + NPCM_I2CCTL3);

	/* Select Bank 0 to access NPCM_I2CCTL4/NPCM_I2CCTL5 */
	npcm_i2c_select_bank(bus, I2C_BANK_0);

	अगर (bus_freq_hz >= I2C_MAX_FAST_MODE_FREQ) अणु
		/*
		 * Set SCL Low/High Time:
		 * k1 = 2 * SCLLT7-0 -> Low Time  = k1 / 2
		 * k2 = 2 * SCLLT7-0 -> High Time = k2 / 2
		 */
		ioग_लिखो8(k1 / 2, bus->reg + NPCM_I2CSCLLT);
		ioग_लिखो8(k2 / 2, bus->reg + NPCM_I2CSCLHT);

		ioग_लिखो8(dbnct, bus->reg + NPCM_I2CCTL5);
	पूर्ण

	ioग_लिखो8(hldt, bus->reg + NPCM_I2CCTL4);

	/* Return to Bank 1, and stay there by शेष: */
	npcm_i2c_select_bank(bus, I2C_BANK_1);

	वापस 0;
पूर्ण

अटल पूर्णांक npcm_i2c_init_module(काष्ठा npcm_i2c *bus, क्रमागत i2c_mode mode,
				u32 bus_freq_hz)
अणु
	u8 val;
	पूर्णांक ret;

	/* Check whether module alपढ़ोy enabled or frequency is out of bounds */
	अगर ((bus->state != I2C_DISABLE && bus->state != I2C_IDLE) ||
	    bus_freq_hz < I2C_FREQ_MIN_HZ || bus_freq_hz > I2C_FREQ_MAX_HZ)
		वापस -EINVAL;

	npcm_i2c_disable(bus);

	/* Configure FIFO mode : */
	अगर (FIELD_GET(I2C_VER_FIFO_EN, ioपढ़ो8(bus->reg + I2C_VER))) अणु
		bus->fअगरo_use = true;
		npcm_i2c_select_bank(bus, I2C_BANK_0);
		val = ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTL);
		val |= NPCM_I2CFIF_CTL_FIFO_EN;
		ioग_लिखो8(val, bus->reg + NPCM_I2CFIF_CTL);
		npcm_i2c_select_bank(bus, I2C_BANK_1);
	पूर्ण अन्यथा अणु
		bus->fअगरo_use = false;
	पूर्ण

	/* Configure I2C module घड़ी frequency */
	ret = npcm_i2c_init_clk(bus, bus_freq_hz);
	अगर (ret) अणु
		dev_err(bus->dev, "npcm_i2c_init_clk failed\n");
		वापस ret;
	पूर्ण

	/* Enable module (beक्रमe configuring CTL1) */
	npcm_i2c_enable(bus);
	bus->state = I2C_IDLE;
	val = ioपढ़ो8(bus->reg + NPCM_I2CCTL1);
	val = (val | NPCM_I2CCTL1_NMINTE) & ~NPCM_I2CCTL1_RWS;
	ioग_लिखो8(val, bus->reg + NPCM_I2CCTL1);

	npcm_i2c_पूर्णांक_enable(bus, true);

	npcm_i2c_reset(bus);

	वापस 0;
पूर्ण

अटल पूर्णांक __npcm_i2c_init(काष्ठा npcm_i2c *bus, काष्ठा platक्रमm_device *pdev)
अणु
	u32 clk_freq_hz;
	पूर्णांक ret;

	/* Initialize the पूर्णांकernal data काष्ठाures */
	bus->state = I2C_DISABLE;
	bus->master_or_slave = I2C_SLAVE;
	bus->पूर्णांक_समय_stamp = 0;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	bus->slave = शून्य;
#पूर्ण_अगर

	ret = device_property_पढ़ो_u32(&pdev->dev, "clock-frequency",
				       &clk_freq_hz);
	अगर (ret) अणु
		dev_info(&pdev->dev, "Could not read clock-frequency property");
		clk_freq_hz = I2C_MAX_STANDARD_MODE_FREQ;
	पूर्ण

	ret = npcm_i2c_init_module(bus, I2C_MASTER, clk_freq_hz);
	अगर (ret) अणु
		dev_err(&pdev->dev, "npcm_i2c_init_module failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल irqवापस_t npcm_i2c_bus_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा npcm_i2c *bus = dev_id;

	अगर (npcm_i2c_is_master(bus))
		bus->master_or_slave = I2C_MASTER;

	अगर (bus->master_or_slave == I2C_MASTER) अणु
		bus->पूर्णांक_समय_stamp = jअगरfies;
		अगर (!npcm_i2c_पूर्णांक_master_handler(bus))
			वापस IRQ_HANDLED;
	पूर्ण
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	अगर (bus->slave) अणु
		bus->master_or_slave = I2C_SLAVE;
		वापस npcm_i2c_पूर्णांक_slave_handler(bus);
	पूर्ण
#पूर्ण_अगर
	वापस IRQ_NONE;
पूर्ण

अटल bool npcm_i2c_master_start_xmit(काष्ठा npcm_i2c *bus,
				       u8 slave_addr, u16 nग_लिखो, u16 nपढ़ो,
				       u8 *ग_लिखो_data, u8 *पढ़ो_data,
				       bool use_PEC, bool use_पढ़ो_block)
अणु
	अगर (bus->state != I2C_IDLE) अणु
		bus->cmd_err = -EBUSY;
		वापस false;
	पूर्ण
	bus->dest_addr = slave_addr << 1;
	bus->wr_buf = ग_लिखो_data;
	bus->wr_size = nग_लिखो;
	bus->wr_ind = 0;
	bus->rd_buf = पढ़ो_data;
	bus->rd_size = nपढ़ो;
	bus->rd_ind = 0;
	bus->PEC_use = 0;

	/* क्रम tx PEC is appended to buffer from i2c IF. PEC flag is ignored */
	अगर (nपढ़ो)
		bus->PEC_use = use_PEC;

	bus->पढ़ो_block_use = use_पढ़ो_block;
	अगर (nपढ़ो && !nग_लिखो)
		bus->operation = I2C_READ_OPER;
	अन्यथा
		bus->operation = I2C_WRITE_OPER;
	अगर (bus->fअगरo_use) अणु
		u8 i2cfअगर_cts;

		npcm_i2c_select_bank(bus, I2C_BANK_1);
		/* clear FIFO and relevant status bits. */
		i2cfअगर_cts = ioपढ़ो8(bus->reg + NPCM_I2CFIF_CTS);
		i2cfअगर_cts &= ~NPCM_I2CFIF_CTS_SLVRSTR;
		i2cfअगर_cts |= NPCM_I2CFIF_CTS_CLR_FIFO;
		ioग_लिखो8(i2cfअगर_cts, bus->reg + NPCM_I2CFIF_CTS);
	पूर्ण

	bus->state = I2C_IDLE;
	npcm_i2c_stall_after_start(bus, true);
	npcm_i2c_master_start(bus);
	वापस true;
पूर्ण

अटल पूर्णांक npcm_i2c_master_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs,
				पूर्णांक num)
अणु
	काष्ठा npcm_i2c *bus = container_of(adap, काष्ठा npcm_i2c, adap);
	काष्ठा i2c_msg *msg0, *msg1;
	अचिन्हित दीर्घ समय_left, flags;
	u16 nग_लिखो, nपढ़ो;
	u8 *ग_लिखो_data, *पढ़ो_data;
	u8 slave_addr;
	पूर्णांक समयout;
	पूर्णांक ret = 0;
	bool पढ़ो_block = false;
	bool पढ़ो_PEC = false;
	u8 bus_busy;
	अचिन्हित दीर्घ समयout_usec;

	अगर (bus->state == I2C_DISABLE) अणु
		dev_err(bus->dev, "I2C%d module is disabled", bus->num);
		वापस -EINVAL;
	पूर्ण

	msg0 = &msgs[0];
	slave_addr = msg0->addr;
	अगर (msg0->flags & I2C_M_RD) अणु /* पढ़ो */
		nग_लिखो = 0;
		ग_लिखो_data = शून्य;
		पढ़ो_data = msg0->buf;
		अगर (msg0->flags & I2C_M_RECV_LEN) अणु
			nपढ़ो = 1;
			पढ़ो_block = true;
			अगर (msg0->flags & I2C_CLIENT_PEC)
				पढ़ो_PEC = true;
		पूर्ण अन्यथा अणु
			nपढ़ो = msg0->len;
		पूर्ण
	पूर्ण अन्यथा अणु /* ग_लिखो */
		nग_लिखो = msg0->len;
		ग_लिखो_data = msg0->buf;
		nपढ़ो = 0;
		पढ़ो_data = शून्य;
		अगर (num == 2) अणु
			msg1 = &msgs[1];
			पढ़ो_data = msg1->buf;
			अगर (msg1->flags & I2C_M_RECV_LEN) अणु
				nपढ़ो = 1;
				पढ़ो_block = true;
				अगर (msg1->flags & I2C_CLIENT_PEC)
					पढ़ो_PEC = true;
			पूर्ण अन्यथा अणु
				nपढ़ो = msg1->len;
				पढ़ो_block = false;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Adaptive TimeOut: estimated समय in usec + 100% margin:
	 * 2: द्विगुन the समयout क्रम घड़ी stretching हाल
	 * 9: bits per transaction (including the ack/nack)
	 */
	समयout_usec = (2 * 9 * USEC_PER_SEC / bus->bus_freq) * (2 + nपढ़ो + nग_लिखो);
	समयout = max(msecs_to_jअगरfies(35), usecs_to_jअगरfies(समयout_usec));
	अगर (nग_लिखो >= 32 * 1024 || nपढ़ो >= 32 * 1024) अणु
		dev_err(bus->dev, "i2c%d buffer too big\n", bus->num);
		वापस -EINVAL;
	पूर्ण

	समय_left = jअगरfies + msecs_to_jअगरfies(DEFAULT_STALL_COUNT) + 1;
	करो अणु
		/*
		 * we must clear slave address immediately when the bus is not
		 * busy, so we spinlock it, but we करोn't keep the lock क्रम the
		 * entire जबतक since it is too दीर्घ.
		 */
		spin_lock_irqsave(&bus->lock, flags);
		bus_busy = ioपढ़ो8(bus->reg + NPCM_I2CCST) & NPCM_I2CCST_BB;
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
		अगर (!bus_busy && bus->slave)
			ioग_लिखो8((bus->slave->addr & 0x7F),
				 bus->reg + NPCM_I2CADDR1);
#पूर्ण_अगर
		spin_unlock_irqrestore(&bus->lock, flags);

	पूर्ण जबतक (समय_is_after_jअगरfies(समय_left) && bus_busy);

	अगर (bus_busy) अणु
		ioग_लिखो8(NPCM_I2CCST_BB, bus->reg + NPCM_I2CCST);
		npcm_i2c_reset(bus);
		i2c_recover_bus(adap);
		वापस -EAGAIN;
	पूर्ण

	npcm_i2c_init_params(bus);
	bus->dest_addr = slave_addr;
	bus->msgs = msgs;
	bus->msgs_num = num;
	bus->cmd_err = 0;
	bus->पढ़ो_block_use = पढ़ो_block;

	reinit_completion(&bus->cmd_complete);
	अगर (!npcm_i2c_master_start_xmit(bus, slave_addr, nग_लिखो, nपढ़ो,
					ग_लिखो_data, पढ़ो_data, पढ़ो_PEC,
					पढ़ो_block))
		ret = -EBUSY;

	अगर (ret != -EBUSY) अणु
		समय_left = रुको_क्रम_completion_समयout(&bus->cmd_complete,
							समयout);

		अगर (समय_left == 0) अणु
			अगर (bus->समयout_cnt < ULदीर्घ_उच्च)
				bus->समयout_cnt++;
			अगर (bus->master_or_slave == I2C_MASTER) अणु
				i2c_recover_bus(adap);
				bus->cmd_err = -EIO;
				bus->state = I2C_IDLE;
			पूर्ण
		पूर्ण
	पूर्ण
	ret = bus->cmd_err;

	/* अगर there was BER, check अगर need to recover the bus: */
	अगर (bus->cmd_err == -EAGAIN)
		ret = i2c_recover_bus(adap);

	/*
	 * After any type of error, check अगर LAST bit is still set,
	 * due to a HW issue.
	 * It cannot be cleared without resetting the module.
	 */
	अगर (bus->cmd_err &&
	    (NPCM_I2CRXF_CTL_LAST_PEC & ioपढ़ो8(bus->reg + NPCM_I2CRXF_CTL)))
		npcm_i2c_reset(bus);

#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	/* reenable slave अगर it was enabled */
	अगर (bus->slave)
		ioग_लिखो8((bus->slave->addr & 0x7F) | NPCM_I2CADDR_SAEN,
			 bus->reg + NPCM_I2CADDR1);
#पूर्ण_अगर
	वापस bus->cmd_err;
पूर्ण

अटल u32 npcm_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस I2C_FUNC_I2C |
	       I2C_FUNC_SMBUS_EMUL |
	       I2C_FUNC_SMBUS_BLOCK_DATA |
	       I2C_FUNC_SMBUS_PEC |
	       I2C_FUNC_SLAVE;
पूर्ण

अटल स्थिर काष्ठा i2c_adapter_quirks npcm_i2c_quirks = अणु
	.max_पढ़ो_len = 32768,
	.max_ग_लिखो_len = 32768,
	.flags = I2C_AQ_COMB_WRITE_THEN_READ,
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm npcm_i2c_algo = अणु
	.master_xfer = npcm_i2c_master_xfer,
	.functionality = npcm_i2c_functionality,
#अगर IS_ENABLED(CONFIG_I2C_SLAVE)
	.reg_slave	= npcm_i2c_reg_slave,
	.unreg_slave	= npcm_i2c_unreg_slave,
#पूर्ण_अगर
पूर्ण;

/* i2c debugfs directory: used to keep health monitor of i2c devices */
अटल काष्ठा dentry *npcm_i2c_debugfs_dir;

अटल व्योम npcm_i2c_init_debugfs(काष्ठा platक्रमm_device *pdev,
				  काष्ठा npcm_i2c *bus)
अणु
	काष्ठा dentry *d;

	अगर (!npcm_i2c_debugfs_dir)
		वापस;
	d = debugfs_create_dir(dev_name(&pdev->dev), npcm_i2c_debugfs_dir);
	अगर (IS_ERR_OR_शून्य(d))
		वापस;
	debugfs_create_u64("ber_cnt", 0444, d, &bus->ber_cnt);
	debugfs_create_u64("nack_cnt", 0444, d, &bus->nack_cnt);
	debugfs_create_u64("rec_succ_cnt", 0444, d, &bus->rec_succ_cnt);
	debugfs_create_u64("rec_fail_cnt", 0444, d, &bus->rec_fail_cnt);
	debugfs_create_u64("timeout_cnt", 0444, d, &bus->समयout_cnt);

	bus->debugfs = d;
पूर्ण

अटल पूर्णांक npcm_i2c_probe_bus(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा npcm_i2c *bus;
	काष्ठा i2c_adapter *adap;
	काष्ठा clk *i2c_clk;
	अटल काष्ठा regmap *gcr_regmap;
	अटल काष्ठा regmap *clk_regmap;
	पूर्णांक irq;
	पूर्णांक ret;

	bus = devm_kzalloc(&pdev->dev, माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस -ENOMEM;

	bus->dev = &pdev->dev;

	bus->num = of_alias_get_id(pdev->dev.of_node, "i2c");
	/* core clk must be acquired to calculate module timing settings */
	i2c_clk = devm_clk_get(&pdev->dev, शून्य);
	अगर (IS_ERR(i2c_clk))
		वापस PTR_ERR(i2c_clk);
	bus->apb_clk = clk_get_rate(i2c_clk);

	gcr_regmap = syscon_regmap_lookup_by_compatible("nuvoton,npcm750-gcr");
	अगर (IS_ERR(gcr_regmap))
		वापस PTR_ERR(gcr_regmap);
	regmap_ग_लिखो(gcr_regmap, NPCM_I2CSEGCTL, NPCM_I2CSEGCTL_INIT_VAL);

	clk_regmap = syscon_regmap_lookup_by_compatible("nuvoton,npcm750-clk");
	अगर (IS_ERR(clk_regmap))
		वापस PTR_ERR(clk_regmap);

	bus->reg = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(bus->reg))
		वापस PTR_ERR(bus->reg);

	spin_lock_init(&bus->lock);
	init_completion(&bus->cmd_complete);

	adap = &bus->adap;
	adap->owner = THIS_MODULE;
	adap->retries = 3;
	adap->समयout = HZ;
	adap->algo = &npcm_i2c_algo;
	adap->quirks = &npcm_i2c_quirks;
	adap->algo_data = bus;
	adap->dev.parent = &pdev->dev;
	adap->dev.of_node = pdev->dev.of_node;
	adap->nr = pdev->id;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;

	ret = devm_request_irq(bus->dev, irq, npcm_i2c_bus_irq, 0,
			       dev_name(bus->dev), bus);
	अगर (ret)
		वापस ret;

	ret = __npcm_i2c_init(bus, pdev);
	अगर (ret)
		वापस ret;

	npcm_i2c_recovery_init(adap);

	i2c_set_adapdata(adap, bus);

	snम_लिखो(bus->adap.name, माप(bus->adap.name), "npcm_i2c_%d",
		 bus->num);
	ret = i2c_add_numbered_adapter(&bus->adap);
	अगर (ret)
		वापस ret;

	platक्रमm_set_drvdata(pdev, bus);
	npcm_i2c_init_debugfs(pdev, bus);
	वापस 0;
पूर्ण

अटल पूर्णांक npcm_i2c_हटाओ_bus(काष्ठा platक्रमm_device *pdev)
अणु
	अचिन्हित दीर्घ lock_flags;
	काष्ठा npcm_i2c *bus = platक्रमm_get_drvdata(pdev);

	debugfs_हटाओ_recursive(bus->debugfs);
	spin_lock_irqsave(&bus->lock, lock_flags);
	npcm_i2c_disable(bus);
	spin_unlock_irqrestore(&bus->lock, lock_flags);
	i2c_del_adapter(&bus->adap);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id npcm_i2c_bus_of_table[] = अणु
	अणु .compatible = "nuvoton,npcm750-i2c", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, npcm_i2c_bus_of_table);

अटल काष्ठा platक्रमm_driver npcm_i2c_bus_driver = अणु
	.probe = npcm_i2c_probe_bus,
	.हटाओ = npcm_i2c_हटाओ_bus,
	.driver = अणु
		.name = "nuvoton-i2c",
		.of_match_table = npcm_i2c_bus_of_table,
	पूर्ण
पूर्ण;

अटल पूर्णांक __init npcm_i2c_init(व्योम)
अणु
	npcm_i2c_debugfs_dir = debugfs_create_dir("npcm_i2c", शून्य);
	platक्रमm_driver_रेजिस्टर(&npcm_i2c_bus_driver);
	वापस 0;
पूर्ण
module_init(npcm_i2c_init);

अटल व्योम __निकास npcm_i2c_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&npcm_i2c_bus_driver);
	debugfs_हटाओ_recursive(npcm_i2c_debugfs_dir);
पूर्ण
module_निकास(npcm_i2c_निकास);

MODULE_AUTHOR("Avi Fishman <avi.fishman@gmail.com>");
MODULE_AUTHOR("Tali Perry <tali.perry@nuvoton.com>");
MODULE_AUTHOR("Tyrone Ting <kfting@nuvoton.com>");
MODULE_DESCRIPTION("Nuvoton I2C Bus Driver");
MODULE_LICENSE("GPL v2");
