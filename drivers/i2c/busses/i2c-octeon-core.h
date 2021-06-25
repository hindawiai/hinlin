<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/atomic.h>
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-smbus.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>

/* Controller command patterns */
#घोषणा SW_TWSI_V		BIT_ULL(63)	/* Valid bit */
#घोषणा SW_TWSI_EIA		BIT_ULL(61)	/* Extended पूर्णांकernal address */
#घोषणा SW_TWSI_R		BIT_ULL(56)	/* Result or पढ़ो bit */
#घोषणा SW_TWSI_SOVR		BIT_ULL(55)	/* Size override */
#घोषणा SW_TWSI_SIZE_SHIFT	52
#घोषणा SW_TWSI_ADDR_SHIFT	40
#घोषणा SW_TWSI_IA_SHIFT	32		/* Internal address */

/* Controller opcode word (bits 60:57) */
#घोषणा SW_TWSI_OP_SHIFT	57
#घोषणा SW_TWSI_OP_7		(0ULL << SW_TWSI_OP_SHIFT)
#घोषणा SW_TWSI_OP_7_IA		(1ULL << SW_TWSI_OP_SHIFT)
#घोषणा SW_TWSI_OP_10		(2ULL << SW_TWSI_OP_SHIFT)
#घोषणा SW_TWSI_OP_10_IA	(3ULL << SW_TWSI_OP_SHIFT)
#घोषणा SW_TWSI_OP_TWSI_CLK	(4ULL << SW_TWSI_OP_SHIFT)
#घोषणा SW_TWSI_OP_EOP		(6ULL << SW_TWSI_OP_SHIFT) /* Extended opcode */

/* Controller extended opcode word (bits 34:32) */
#घोषणा SW_TWSI_EOP_SHIFT	32
#घोषणा SW_TWSI_EOP_TWSI_DATA	(SW_TWSI_OP_EOP | 1ULL << SW_TWSI_EOP_SHIFT)
#घोषणा SW_TWSI_EOP_TWSI_CTL	(SW_TWSI_OP_EOP | 2ULL << SW_TWSI_EOP_SHIFT)
#घोषणा SW_TWSI_EOP_TWSI_CLKCTL	(SW_TWSI_OP_EOP | 3ULL << SW_TWSI_EOP_SHIFT)
#घोषणा SW_TWSI_EOP_TWSI_STAT	(SW_TWSI_OP_EOP | 3ULL << SW_TWSI_EOP_SHIFT)
#घोषणा SW_TWSI_EOP_TWSI_RST	(SW_TWSI_OP_EOP | 7ULL << SW_TWSI_EOP_SHIFT)

/* Controller command and status bits */
#घोषणा TWSI_CTL_CE		0x80	/* High level controller enable */
#घोषणा TWSI_CTL_ENAB		0x40	/* Bus enable */
#घोषणा TWSI_CTL_STA		0x20	/* Master-mode start, HW clears when करोne */
#घोषणा TWSI_CTL_STP		0x10	/* Master-mode stop, HW clears when करोne */
#घोषणा TWSI_CTL_IFLG		0x08	/* HW event, SW ग_लिखोs 0 to ACK */
#घोषणा TWSI_CTL_AAK		0x04	/* Assert ACK */

/* Status values */
#घोषणा STAT_BUS_ERROR		0x00
#घोषणा STAT_START		0x08
#घोषणा STAT_REP_START		0x10
#घोषणा STAT_TXADDR_ACK		0x18
#घोषणा STAT_TXADDR_NAK		0x20
#घोषणा STAT_TXDATA_ACK		0x28
#घोषणा STAT_TXDATA_NAK		0x30
#घोषणा STAT_LOST_ARB_38	0x38
#घोषणा STAT_RXADDR_ACK		0x40
#घोषणा STAT_RXADDR_NAK		0x48
#घोषणा STAT_RXDATA_ACK		0x50
#घोषणा STAT_RXDATA_NAK		0x58
#घोषणा STAT_SLAVE_60		0x60
#घोषणा STAT_LOST_ARB_68	0x68
#घोषणा STAT_SLAVE_70		0x70
#घोषणा STAT_LOST_ARB_78	0x78
#घोषणा STAT_SLAVE_80		0x80
#घोषणा STAT_SLAVE_88		0x88
#घोषणा STAT_GENDATA_ACK	0x90
#घोषणा STAT_GENDATA_NAK	0x98
#घोषणा STAT_SLAVE_A0		0xA0
#घोषणा STAT_SLAVE_A8		0xA8
#घोषणा STAT_LOST_ARB_B0	0xB0
#घोषणा STAT_SLAVE_LOST		0xB8
#घोषणा STAT_SLAVE_NAK		0xC0
#घोषणा STAT_SLAVE_ACK		0xC8
#घोषणा STAT_AD2W_ACK		0xD0
#घोषणा STAT_AD2W_NAK		0xD8
#घोषणा STAT_IDLE		0xF8

/* TWSI_INT values */
#घोषणा TWSI_INT_ST_INT		BIT_ULL(0)
#घोषणा TWSI_INT_TS_INT		BIT_ULL(1)
#घोषणा TWSI_INT_CORE_INT	BIT_ULL(2)
#घोषणा TWSI_INT_ST_EN		BIT_ULL(4)
#घोषणा TWSI_INT_TS_EN		BIT_ULL(5)
#घोषणा TWSI_INT_CORE_EN	BIT_ULL(6)
#घोषणा TWSI_INT_SDA_OVR	BIT_ULL(8)
#घोषणा TWSI_INT_SCL_OVR	BIT_ULL(9)
#घोषणा TWSI_INT_SDA		BIT_ULL(10)
#घोषणा TWSI_INT_SCL		BIT_ULL(11)

#घोषणा I2C_OCTEON_EVENT_WAIT 80 /* microseconds */

/* Register offsets */
काष्ठा octeon_i2c_reg_offset अणु
	अचिन्हित पूर्णांक sw_twsi;
	अचिन्हित पूर्णांक twsi_पूर्णांक;
	अचिन्हित पूर्णांक sw_twsi_ext;
पूर्ण;

#घोषणा SW_TWSI(x)	(x->roff.sw_twsi)
#घोषणा TWSI_INT(x)	(x->roff.twsi_पूर्णांक)
#घोषणा SW_TWSI_EXT(x)	(x->roff.sw_twsi_ext)

काष्ठा octeon_i2c अणु
	रुको_queue_head_t queue;
	काष्ठा i2c_adapter adap;
	काष्ठा octeon_i2c_reg_offset roff;
	काष्ठा clk *clk;
	पूर्णांक irq;
	पूर्णांक hlc_irq;		/* For cn7890 only */
	u32 twsi_freq;
	पूर्णांक sys_freq;
	व्योम __iomem *twsi_base;
	काष्ठा device *dev;
	bool hlc_enabled;
	bool broken_irq_mode;
	bool broken_irq_check;
	व्योम (*पूर्णांक_enable)(काष्ठा octeon_i2c *);
	व्योम (*पूर्णांक_disable)(काष्ठा octeon_i2c *);
	व्योम (*hlc_पूर्णांक_enable)(काष्ठा octeon_i2c *);
	व्योम (*hlc_पूर्णांक_disable)(काष्ठा octeon_i2c *);
	atomic_t पूर्णांक_enable_cnt;
	atomic_t hlc_पूर्णांक_enable_cnt;
	काष्ठा i2c_smbus_alert_setup alert_data;
	काष्ठा i2c_client *ara;
पूर्ण;

अटल अंतरभूत व्योम octeon_i2c_ग_लिखोq_flush(u64 val, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोq(val, addr);
	__raw_पढ़ोq(addr);	/* रुको क्रम ग_लिखो to land */
पूर्ण

/**
 * octeon_i2c_reg_ग_लिखो - ग_लिखो an I2C core रेजिस्टर
 * @i2c: The काष्ठा octeon_i2c
 * @eop_reg: Register selector
 * @data: Value to be written
 *
 * The I2C core रेजिस्टरs are accessed indirectly via the SW_TWSI CSR.
 */
अटल अंतरभूत व्योम octeon_i2c_reg_ग_लिखो(काष्ठा octeon_i2c *i2c, u64 eop_reg, u8 data)
अणु
	पूर्णांक tries = 1000;
	u64 पंचांगp;

	__raw_ग_लिखोq(SW_TWSI_V | eop_reg | data, i2c->twsi_base + SW_TWSI(i2c));
	करो अणु
		पंचांगp = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
		अगर (--tries < 0)
			वापस;
	पूर्ण जबतक ((पंचांगp & SW_TWSI_V) != 0);
पूर्ण

#घोषणा octeon_i2c_ctl_ग_लिखो(i2c, val)					\
	octeon_i2c_reg_ग_लिखो(i2c, SW_TWSI_EOP_TWSI_CTL, val)
#घोषणा octeon_i2c_data_ग_लिखो(i2c, val)					\
	octeon_i2c_reg_ग_लिखो(i2c, SW_TWSI_EOP_TWSI_DATA, val)

/**
 * octeon_i2c_reg_पढ़ो - पढ़ो lower bits of an I2C core रेजिस्टर
 * @i2c: The काष्ठा octeon_i2c
 * @eop_reg: Register selector
 *
 * Returns the data.
 *
 * The I2C core रेजिस्टरs are accessed indirectly via the SW_TWSI CSR.
 */
अटल अंतरभूत पूर्णांक octeon_i2c_reg_पढ़ो(काष्ठा octeon_i2c *i2c, u64 eop_reg,
				      पूर्णांक *error)
अणु
	पूर्णांक tries = 1000;
	u64 पंचांगp;

	__raw_ग_लिखोq(SW_TWSI_V | eop_reg | SW_TWSI_R, i2c->twsi_base + SW_TWSI(i2c));
	करो अणु
		पंचांगp = __raw_पढ़ोq(i2c->twsi_base + SW_TWSI(i2c));
		अगर (--tries < 0) अणु
			/* संकेत that the वापसed data is invalid */
			अगर (error)
				*error = -EIO;
			वापस 0;
		पूर्ण
	पूर्ण जबतक ((पंचांगp & SW_TWSI_V) != 0);

	वापस पंचांगp & 0xFF;
पूर्ण

#घोषणा octeon_i2c_ctl_पढ़ो(i2c)					\
	octeon_i2c_reg_पढ़ो(i2c, SW_TWSI_EOP_TWSI_CTL, शून्य)
#घोषणा octeon_i2c_data_पढ़ो(i2c, error)				\
	octeon_i2c_reg_पढ़ो(i2c, SW_TWSI_EOP_TWSI_DATA, error)
#घोषणा octeon_i2c_stat_पढ़ो(i2c)					\
	octeon_i2c_reg_पढ़ो(i2c, SW_TWSI_EOP_TWSI_STAT, शून्य)

/**
 * octeon_i2c_पढ़ो_पूर्णांक - पढ़ो the TWSI_INT रेजिस्टर
 * @i2c: The काष्ठा octeon_i2c
 *
 * Returns the value of the रेजिस्टर.
 */
अटल अंतरभूत u64 octeon_i2c_पढ़ो_पूर्णांक(काष्ठा octeon_i2c *i2c)
अणु
	वापस __raw_पढ़ोq(i2c->twsi_base + TWSI_INT(i2c));
पूर्ण

/**
 * octeon_i2c_ग_लिखो_पूर्णांक - ग_लिखो the TWSI_INT रेजिस्टर
 * @i2c: The काष्ठा octeon_i2c
 * @data: Value to be written
 */
अटल अंतरभूत व्योम octeon_i2c_ग_लिखो_पूर्णांक(काष्ठा octeon_i2c *i2c, u64 data)
अणु
	octeon_i2c_ग_लिखोq_flush(data, i2c->twsi_base + TWSI_INT(i2c));
पूर्ण

/* Prototypes */
irqवापस_t octeon_i2c_isr(पूर्णांक irq, व्योम *dev_id);
पूर्णांक octeon_i2c_xfer(काष्ठा i2c_adapter *adap, काष्ठा i2c_msg *msgs, पूर्णांक num);
पूर्णांक octeon_i2c_init_lowlevel(काष्ठा octeon_i2c *i2c);
व्योम octeon_i2c_set_घड़ी(काष्ठा octeon_i2c *i2c);
बाह्य काष्ठा i2c_bus_recovery_info octeon_i2c_recovery_info;
