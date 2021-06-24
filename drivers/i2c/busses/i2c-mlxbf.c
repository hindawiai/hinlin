<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Mellanox BlueField I2C bus driver
 *
 *  Copyright (C) 2020 Mellanox Technologies, Ltd.
 */

#समावेश <linux/acpi.h>
#समावेश <linux/delay.h>
#समावेश <linux/err.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/i2c.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/माला.स>

/* Defines what functionality is present. */
#घोषणा MLXBF_I2C_FUNC_SMBUS_BLOCK \
	(I2C_FUNC_SMBUS_BLOCK_DATA | I2C_FUNC_SMBUS_BLOCK_PROC_CALL)

#घोषणा MLXBF_I2C_FUNC_SMBUS_DEFAULT \
	(I2C_FUNC_SMBUS_BYTE      | I2C_FUNC_SMBUS_BYTE_DATA | \
	 I2C_FUNC_SMBUS_WORD_DATA | I2C_FUNC_SMBUS_I2C_BLOCK | \
	 I2C_FUNC_SMBUS_PROC_CALL)

#घोषणा MLXBF_I2C_FUNC_ALL \
	(MLXBF_I2C_FUNC_SMBUS_DEFAULT | MLXBF_I2C_FUNC_SMBUS_BLOCK | \
	 I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SLAVE)

#घोषणा MLXBF_I2C_SMBUS_MAX        3

/* Shared resources info in BlueField platक्रमms. */

#घोषणा MLXBF_I2C_COALESCE_TYU_ADDR    0x02801300
#घोषणा MLXBF_I2C_COALESCE_TYU_SIZE    0x010

#घोषणा MLXBF_I2C_GPIO_TYU_ADDR        0x02802000
#घोषणा MLXBF_I2C_GPIO_TYU_SIZE        0x100

#घोषणा MLXBF_I2C_COREPLL_TYU_ADDR     0x02800358
#घोषणा MLXBF_I2C_COREPLL_TYU_SIZE     0x008

#घोषणा MLXBF_I2C_COREPLL_YU_ADDR      0x02800c30
#घोषणा MLXBF_I2C_COREPLL_YU_SIZE      0x00c

#घोषणा MLXBF_I2C_SHARED_RES_MAX       3

/*
 * Note that the following SMBus, CAUSE, GPIO and PLL रेजिस्टर addresses
 * refer to their respective offsets relative to the corresponding
 * memory-mapped region whose addresses are specअगरied in either the DT or
 * the ACPI tables or above.
 */

/*
 * SMBus Master core घड़ी frequency. Timing configurations are
 * strongly dependent on the core घड़ी frequency of the SMBus
 * Master. Default value is set to 400MHz.
 */
#घोषणा MLXBF_I2C_TYU_PLL_OUT_FREQ  (400 * 1000 * 1000)
/* Reference घड़ी क्रम Bluefield - 156 MHz. */
#घोषणा MLXBF_I2C_PLL_IN_FREQ       (156 * 1000 * 1000)

/* Constant used to determine the PLL frequency. */
#घोषणा MLNXBF_I2C_COREPLL_CONST    16384

/* PLL रेजिस्टरs. */
#घोषणा MLXBF_I2C_CORE_PLL_REG0         0x0
#घोषणा MLXBF_I2C_CORE_PLL_REG1         0x4
#घोषणा MLXBF_I2C_CORE_PLL_REG2         0x8

/* OR cause रेजिस्टर. */
#घोषणा MLXBF_I2C_CAUSE_OR_EVTEN0    0x14
#घोषणा MLXBF_I2C_CAUSE_OR_CLEAR     0x18

/* Arbiter Cause Register. */
#घोषणा MLXBF_I2C_CAUSE_ARBITER      0x1c

/*
 * Cause Status flags. Note that those bits might be considered
 * as पूर्णांकerrupt enabled bits.
 */

/* Transaction ended with STOP. */
#घोषणा MLXBF_I2C_CAUSE_TRANSACTION_ENDED  BIT(0)
/* Master arbitration lost. */
#घोषणा MLXBF_I2C_CAUSE_M_ARBITRATION_LOST BIT(1)
/* Unexpected start detected. */
#घोषणा MLXBF_I2C_CAUSE_UNEXPECTED_START   BIT(2)
/* Unexpected stop detected. */
#घोषणा MLXBF_I2C_CAUSE_UNEXPECTED_STOP    BIT(3)
/* Wait क्रम transfer continuation. */
#घोषणा MLXBF_I2C_CAUSE_WAIT_FOR_FW_DATA   BIT(4)
/* Failed to generate STOP. */
#घोषणा MLXBF_I2C_CAUSE_PUT_STOP_FAILED    BIT(5)
/* Failed to generate START. */
#घोषणा MLXBF_I2C_CAUSE_PUT_START_FAILED   BIT(6)
/* Clock toggle completed. */
#घोषणा MLXBF_I2C_CAUSE_CLK_TOGGLE_DONE    BIT(7)
/* Transfer समयout occurred. */
#घोषणा MLXBF_I2C_CAUSE_M_FW_TIMEOUT       BIT(8)
/* Master busy bit reset. */
#घोषणा MLXBF_I2C_CAUSE_M_GW_BUSY_FALL     BIT(9)

#घोषणा MLXBF_I2C_CAUSE_MASTER_ARBITER_BITS_MASK     GENMASK(9, 0)

#घोषणा MLXBF_I2C_CAUSE_MASTER_STATUS_ERROR \
	(MLXBF_I2C_CAUSE_M_ARBITRATION_LOST | \
	 MLXBF_I2C_CAUSE_UNEXPECTED_START | \
	 MLXBF_I2C_CAUSE_UNEXPECTED_STOP | \
	 MLXBF_I2C_CAUSE_PUT_STOP_FAILED | \
	 MLXBF_I2C_CAUSE_PUT_START_FAILED | \
	 MLXBF_I2C_CAUSE_CLK_TOGGLE_DONE | \
	 MLXBF_I2C_CAUSE_M_FW_TIMEOUT)

/*
 * Slave cause status flags. Note that those bits might be considered
 * as पूर्णांकerrupt enabled bits.
 */

/* Write transaction received successfully. */
#घोषणा MLXBF_I2C_CAUSE_WRITE_SUCCESS         BIT(0)
/* Read transaction received, रुकोing क्रम response. */
#घोषणा MLXBF_I2C_CAUSE_READ_WAIT_FW_RESPONSE BIT(13)
/* Slave busy bit reset. */
#घोषणा MLXBF_I2C_CAUSE_S_GW_BUSY_FALL        BIT(18)

#घोषणा MLXBF_I2C_CAUSE_SLAVE_ARBITER_BITS_MASK     GENMASK(20, 0)

/* Cause coalesce रेजिस्टरs. */
#घोषणा MLXBF_I2C_CAUSE_COALESCE_0        0x00
#घोषणा MLXBF_I2C_CAUSE_COALESCE_1        0x04
#घोषणा MLXBF_I2C_CAUSE_COALESCE_2        0x08

#घोषणा MLXBF_I2C_CAUSE_TYU_SLAVE_BIT   MLXBF_I2C_SMBUS_MAX
#घोषणा MLXBF_I2C_CAUSE_YU_SLAVE_BIT    1

/* Functional enable रेजिस्टर. */
#घोषणा MLXBF_I2C_GPIO_0_FUNC_EN_0    0x28
/* Force OE enable रेजिस्टर. */
#घोषणा MLXBF_I2C_GPIO_0_FORCE_OE_EN  0x30
/*
 * Note that Smbus GWs are on GPIOs 30:25. Two pins are used to control
 * SDA/SCL lines:
 *
 *  SMBUS GW0 -> bits[26:25]
 *  SMBUS GW1 -> bits[28:27]
 *  SMBUS GW2 -> bits[30:29]
 */
#घोषणा MLXBF_I2C_GPIO_SMBUS_GW_PINS(num) (25 + ((num) << 1))

/* Note that gw_id can be 0,1 or 2. */
#घोषणा MLXBF_I2C_GPIO_SMBUS_GW_MASK(num) \
	(0xffffffff & (~(0x3 << MLXBF_I2C_GPIO_SMBUS_GW_PINS(num))))

#घोषणा MLXBF_I2C_GPIO_SMBUS_GW_RESET_PINS(num, val) \
	((val) & MLXBF_I2C_GPIO_SMBUS_GW_MASK(num))

#घोषणा MLXBF_I2C_GPIO_SMBUS_GW_ASSERT_PINS(num, val) \
	((val) | (0x3 << MLXBF_I2C_GPIO_SMBUS_GW_PINS(num)))

/* SMBus timing parameters. */
#घोषणा MLXBF_I2C_SMBUS_TIMER_SCL_LOW_SCL_HIGH    0x00
#घोषणा MLXBF_I2C_SMBUS_TIMER_FALL_RISE_SPIKE     0x04
#घोषणा MLXBF_I2C_SMBUS_TIMER_THOLD               0x08
#घोषणा MLXBF_I2C_SMBUS_TIMER_TSETUP_START_STOP   0x0c
#घोषणा MLXBF_I2C_SMBUS_TIMER_TSETUP_DATA         0x10
#घोषणा MLXBF_I2C_SMBUS_THIGH_MAX_TBUF            0x14
#घोषणा MLXBF_I2C_SMBUS_SCL_LOW_TIMEOUT           0x18

/*
 * Defines SMBus operating frequency and core घड़ी frequency.
 * According to ADB files, शेष values are compliant to 100KHz SMBus
 * @ 400MHz core घड़ी. The driver should be able to calculate core
 * frequency based on PLL parameters.
 */
#घोषणा MLXBF_I2C_COREPLL_FREQ          MLXBF_I2C_TYU_PLL_OUT_FREQ

/* Core PLL TYU configuration. */
#घोषणा MLXBF_I2C_COREPLL_CORE_F_TYU_MASK   GENMASK(12, 0)
#घोषणा MLXBF_I2C_COREPLL_CORE_OD_TYU_MASK  GENMASK(3, 0)
#घोषणा MLXBF_I2C_COREPLL_CORE_R_TYU_MASK   GENMASK(5, 0)

#घोषणा MLXBF_I2C_COREPLL_CORE_F_TYU_SHIFT  3
#घोषणा MLXBF_I2C_COREPLL_CORE_OD_TYU_SHIFT 16
#घोषणा MLXBF_I2C_COREPLL_CORE_R_TYU_SHIFT  20

/* Core PLL YU configuration. */
#घोषणा MLXBF_I2C_COREPLL_CORE_F_YU_MASK    GENMASK(25, 0)
#घोषणा MLXBF_I2C_COREPLL_CORE_OD_YU_MASK   GENMASK(3, 0)
#घोषणा MLXBF_I2C_COREPLL_CORE_R_YU_MASK    GENMASK(5, 0)

#घोषणा MLXBF_I2C_COREPLL_CORE_F_YU_SHIFT   0
#घोषणा MLXBF_I2C_COREPLL_CORE_OD_YU_SHIFT  1
#घोषणा MLXBF_I2C_COREPLL_CORE_R_YU_SHIFT   26

/* Core PLL frequency. */
अटल u64 mlxbf_i2c_corepll_frequency;

/* SMBus Master GW. */
#घोषणा MLXBF_I2C_SMBUS_MASTER_GW     0x200
/* Number of bytes received and sent. */
#घोषणा MLXBF_I2C_SMBUS_RS_BYTES      0x300
/* Packet error check (PEC) value. */
#घोषणा MLXBF_I2C_SMBUS_MASTER_PEC    0x304
/* Status bits (ACK/NACK/FW Timeout). */
#घोषणा MLXBF_I2C_SMBUS_MASTER_STATUS 0x308
/* SMbus Master Finite State Machine. */
#घोषणा MLXBF_I2C_SMBUS_MASTER_FSM    0x310

/*
 * When enabled, the master will issue a stop condition in हाल of
 * समयout जबतक रुकोing क्रम FW response.
 */
#घोषणा MLXBF_I2C_SMBUS_EN_FW_TIMEOUT 0x31c

/* SMBus master GW control bits offset in MLXBF_I2C_SMBUS_MASTER_GW[31:3]. */
#घोषणा MLXBF_I2C_MASTER_LOCK_BIT         BIT(31) /* Lock bit. */
#घोषणा MLXBF_I2C_MASTER_BUSY_BIT         BIT(30) /* Busy bit. */
#घोषणा MLXBF_I2C_MASTER_START_BIT        BIT(29) /* Control start. */
#घोषणा MLXBF_I2C_MASTER_CTL_WRITE_BIT    BIT(28) /* Control ग_लिखो phase. */
#घोषणा MLXBF_I2C_MASTER_CTL_READ_BIT     BIT(19) /* Control पढ़ो phase. */
#घोषणा MLXBF_I2C_MASTER_STOP_BIT         BIT(3)  /* Control stop. */

#घोषणा MLXBF_I2C_MASTER_ENABLE \
	(MLXBF_I2C_MASTER_LOCK_BIT | MLXBF_I2C_MASTER_BUSY_BIT | \
	 MLXBF_I2C_MASTER_START_BIT | MLXBF_I2C_MASTER_STOP_BIT)

#घोषणा MLXBF_I2C_MASTER_ENABLE_WRITE \
	(MLXBF_I2C_MASTER_ENABLE | MLXBF_I2C_MASTER_CTL_WRITE_BIT)

#घोषणा MLXBF_I2C_MASTER_ENABLE_READ \
	(MLXBF_I2C_MASTER_ENABLE | MLXBF_I2C_MASTER_CTL_READ_BIT)

#घोषणा MLXBF_I2C_MASTER_SLV_ADDR_SHIFT   12 /* Slave address shअगरt. */
#घोषणा MLXBF_I2C_MASTER_WRITE_SHIFT      21 /* Control ग_लिखो bytes shअगरt. */
#घोषणा MLXBF_I2C_MASTER_SEND_PEC_SHIFT   20 /* Send PEC byte shअगरt. */
#घोषणा MLXBF_I2C_MASTER_PARSE_EXP_SHIFT  11 /* Parse expected bytes shअगरt. */
#घोषणा MLXBF_I2C_MASTER_READ_SHIFT       4  /* Control पढ़ो bytes shअगरt. */

/* SMBus master GW Data descriptor. */
#घोषणा MLXBF_I2C_MASTER_DATA_DESC_ADDR   0x280
#घोषणा MLXBF_I2C_MASTER_DATA_DESC_SIZE   0x80 /* Size in bytes. */

/* Maximum bytes to पढ़ो/ग_लिखो per SMBus transaction. */
#घोषणा MLXBF_I2C_MASTER_DATA_R_LENGTH  MLXBF_I2C_MASTER_DATA_DESC_SIZE
#घोषणा MLXBF_I2C_MASTER_DATA_W_LENGTH (MLXBF_I2C_MASTER_DATA_DESC_SIZE - 1)

/* All bytes were transmitted. */
#घोषणा MLXBF_I2C_SMBUS_STATUS_BYTE_CNT_DONE      BIT(0)
/* NACK received. */
#घोषणा MLXBF_I2C_SMBUS_STATUS_NACK_RCV           BIT(1)
/* Slave's byte count >128 bytes. */
#घोषणा MLXBF_I2C_SMBUS_STATUS_READ_ERR           BIT(2)
/* Timeout occurred. */
#घोषणा MLXBF_I2C_SMBUS_STATUS_FW_TIMEOUT         BIT(3)

#घोषणा MLXBF_I2C_SMBUS_MASTER_STATUS_MASK        GENMASK(3, 0)

#घोषणा MLXBF_I2C_SMBUS_MASTER_STATUS_ERROR \
	(MLXBF_I2C_SMBUS_STATUS_NACK_RCV | \
	 MLXBF_I2C_SMBUS_STATUS_READ_ERR | \
	 MLXBF_I2C_SMBUS_STATUS_FW_TIMEOUT)

#घोषणा MLXBF_I2C_SMBUS_MASTER_FSM_STOP_MASK      BIT(31)
#घोषणा MLXBF_I2C_SMBUS_MASTER_FSM_PS_STATE_MASK  BIT(15)

/* SMBus slave GW. */
#घोषणा MLXBF_I2C_SMBUS_SLAVE_GW              0x400
/* Number of bytes received and sent from/to master. */
#घोषणा MLXBF_I2C_SMBUS_SLAVE_RS_MASTER_BYTES 0x500
/* Packet error check (PEC) value. */
#घोषणा MLXBF_I2C_SMBUS_SLAVE_PEC             0x504
/* SMBus slave Finite State Machine (FSM). */
#घोषणा MLXBF_I2C_SMBUS_SLAVE_FSM             0x510
/*
 * Should be set when all उठाओd causes handled, and cleared by HW on
 * every new cause.
 */
#घोषणा MLXBF_I2C_SMBUS_SLAVE_READY           0x52c

/* SMBus slave GW control bits offset in MLXBF_I2C_SMBUS_SLAVE_GW[31:19]. */
#घोषणा MLXBF_I2C_SLAVE_BUSY_BIT         BIT(30) /* Busy bit. */
#घोषणा MLXBF_I2C_SLAVE_WRITE_BIT        BIT(29) /* Control ग_लिखो enable. */

#घोषणा MLXBF_I2C_SLAVE_ENABLE \
	(MLXBF_I2C_SLAVE_BUSY_BIT | MLXBF_I2C_SLAVE_WRITE_BIT)

#घोषणा MLXBF_I2C_SLAVE_WRITE_BYTES_SHIFT 22 /* Number of bytes to ग_लिखो. */
#घोषणा MLXBF_I2C_SLAVE_SEND_PEC_SHIFT    21 /* Send PEC byte shअगरt. */

/* SMBus slave GW Data descriptor. */
#घोषणा MLXBF_I2C_SLAVE_DATA_DESC_ADDR   0x480
#घोषणा MLXBF_I2C_SLAVE_DATA_DESC_SIZE   0x80 /* Size in bytes. */

/* SMbus slave configuration रेजिस्टरs. */
#घोषणा MLXBF_I2C_SMBUS_SLAVE_ADDR_CFG        0x514
#घोषणा MLXBF_I2C_SMBUS_SLAVE_ADDR_CNT        16
#घोषणा MLXBF_I2C_SMBUS_SLAVE_ADDR_EN_BIT     7
#घोषणा MLXBF_I2C_SMBUS_SLAVE_ADDR_MASK       GENMASK(6, 0)

#घोषणा MLXBF_I2C_SLAVE_ADDR_ENABLED(addr) \
	((addr) & (1 << MLXBF_I2C_SMBUS_SLAVE_ADDR_EN_BIT))

/*
 * Timeout is given in microsends. Note also that समयout handling is not
 * exact.
 */
#घोषणा MLXBF_I2C_SMBUS_TIMEOUT   (300 * 1000) /* 300ms */

/* Encapsulates timing parameters. */
काष्ठा mlxbf_i2c_timings अणु
	u16 scl_high;		/* Clock high period. */
	u16 scl_low;		/* Clock low period. */
	u8 sda_rise;		/* Data rise समय. */
	u8 sda_fall;		/* Data fall समय. */
	u8 scl_rise;		/* Clock rise समय. */
	u8 scl_fall;		/* Clock fall समय. */
	u16 hold_start;		/* Hold समय after (REPEATED) START. */
	u16 hold_data;		/* Data hold समय. */
	u16 setup_start;	/* REPEATED START condition setup समय. */
	u16 setup_stop;		/* STOP condition setup समय. */
	u16 setup_data;		/* Data setup समय. */
	u16 pad;		/* Padding. */
	u16 buf;		/* Bus मुक्त समय between STOP and START. */
	u16 thigh_max;		/* Thigh max. */
	u32 समयout;		/* Detect घड़ी low समयout. */
पूर्ण;

क्रमागत अणु
	MLXBF_I2C_F_READ = BIT(0),
	MLXBF_I2C_F_WRITE = BIT(1),
	MLXBF_I2C_F_NORESTART = BIT(3),
	MLXBF_I2C_F_SMBUS_OPERATION = BIT(4),
	MLXBF_I2C_F_SMBUS_BLOCK = BIT(5),
	MLXBF_I2C_F_SMBUS_PEC = BIT(6),
	MLXBF_I2C_F_SMBUS_PROCESS_CALL = BIT(7),
पूर्ण;

काष्ठा mlxbf_i2c_smbus_operation अणु
	u32 flags;
	u32 length; /* Buffer length in bytes. */
	u8 *buffer;
पूर्ण;

#घोषणा MLXBF_I2C_SMBUS_OP_CNT_1	1
#घोषणा MLXBF_I2C_SMBUS_OP_CNT_2	2
#घोषणा MLXBF_I2C_SMBUS_OP_CNT_3	3
#घोषणा MLXBF_I2C_SMBUS_MAX_OP_CNT	MLXBF_I2C_SMBUS_OP_CNT_3

काष्ठा mlxbf_i2c_smbus_request अणु
	u8 slave;
	u8 operation_cnt;
	काष्ठा mlxbf_i2c_smbus_operation operation[MLXBF_I2C_SMBUS_MAX_OP_CNT];
पूर्ण;

काष्ठा mlxbf_i2c_resource अणु
	व्योम __iomem *io;
	काष्ठा resource *params;
	काष्ठा mutex *lock; /* Mutex to protect mlxbf_i2c_resource. */
	u8 type;
पूर्ण;

/* List of chip resources that are being accessed by the driver. */
क्रमागत अणु
	MLXBF_I2C_SMBUS_RES,
	MLXBF_I2C_MST_CAUSE_RES,
	MLXBF_I2C_SLV_CAUSE_RES,
	MLXBF_I2C_COALESCE_RES,
	MLXBF_I2C_COREPLL_RES,
	MLXBF_I2C_GPIO_RES,
	MLXBF_I2C_END_RES,
पूर्ण;

/* Helper macro to define an I2C resource parameters. */
#घोषणा MLXBF_I2C_RES_PARAMS(addr, size, str) \
	अणु \
		.start = (addr), \
		.end = (addr) + (size) - 1, \
		.name = (str) \
	पूर्ण

अटल काष्ठा resource mlxbf_i2c_coalesce_tyu_params =
		MLXBF_I2C_RES_PARAMS(MLXBF_I2C_COALESCE_TYU_ADDR,
				     MLXBF_I2C_COALESCE_TYU_SIZE,
				     "COALESCE_MEM");
अटल काष्ठा resource mlxbf_i2c_corepll_tyu_params =
		MLXBF_I2C_RES_PARAMS(MLXBF_I2C_COREPLL_TYU_ADDR,
				     MLXBF_I2C_COREPLL_TYU_SIZE,
				     "COREPLL_MEM");
अटल काष्ठा resource mlxbf_i2c_corepll_yu_params =
		MLXBF_I2C_RES_PARAMS(MLXBF_I2C_COREPLL_YU_ADDR,
				     MLXBF_I2C_COREPLL_YU_SIZE,
				     "COREPLL_MEM");
अटल काष्ठा resource mlxbf_i2c_gpio_tyu_params =
		MLXBF_I2C_RES_PARAMS(MLXBF_I2C_GPIO_TYU_ADDR,
				     MLXBF_I2C_GPIO_TYU_SIZE,
				     "GPIO_MEM");

अटल काष्ठा mutex mlxbf_i2c_coalesce_lock;
अटल काष्ठा mutex mlxbf_i2c_corepll_lock;
अटल काष्ठा mutex mlxbf_i2c_gpio_lock;

/* Mellanox BlueField chip type. */
क्रमागत mlxbf_i2c_chip_type अणु
	MLXBF_I2C_CHIP_TYPE_1, /* Mellanox BlueField-1 chip. */
	MLXBF_I2C_CHIP_TYPE_2, /* Mallanox BlueField-2 chip. */
पूर्ण;

काष्ठा mlxbf_i2c_chip_info अणु
	क्रमागत mlxbf_i2c_chip_type type;
	/* Chip shared resources that are being used by the I2C controller. */
	काष्ठा mlxbf_i2c_resource *shared_res[MLXBF_I2C_SHARED_RES_MAX];

	/* Callback to calculate the core PLL frequency. */
	u64 (*calculate_freq)(काष्ठा mlxbf_i2c_resource *corepll_res);
पूर्ण;

काष्ठा mlxbf_i2c_priv अणु
	स्थिर काष्ठा mlxbf_i2c_chip_info *chip;
	काष्ठा i2c_adapter adap;
	काष्ठा mlxbf_i2c_resource *smbus;
	काष्ठा mlxbf_i2c_resource *mst_cause;
	काष्ठा mlxbf_i2c_resource *slv_cause;
	काष्ठा mlxbf_i2c_resource *coalesce;
	u64 frequency; /* Core frequency in Hz. */
	पूर्णांक bus; /* Physical bus identअगरier. */
	पूर्णांक irq;
	काष्ठा i2c_client *slave;
पूर्ण;

अटल काष्ठा mlxbf_i2c_resource mlxbf_i2c_coalesce_res[] = अणु
	[MLXBF_I2C_CHIP_TYPE_1] = अणु
		.params = &mlxbf_i2c_coalesce_tyu_params,
		.lock = &mlxbf_i2c_coalesce_lock,
		.type = MLXBF_I2C_COALESCE_RES
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा mlxbf_i2c_resource mlxbf_i2c_corepll_res[] = अणु
	[MLXBF_I2C_CHIP_TYPE_1] = अणु
		.params = &mlxbf_i2c_corepll_tyu_params,
		.lock = &mlxbf_i2c_corepll_lock,
		.type = MLXBF_I2C_COREPLL_RES
	पूर्ण,
	[MLXBF_I2C_CHIP_TYPE_2] = अणु
		.params = &mlxbf_i2c_corepll_yu_params,
		.lock = &mlxbf_i2c_corepll_lock,
		.type = MLXBF_I2C_COREPLL_RES,
	पूर्ण
पूर्ण;

अटल काष्ठा mlxbf_i2c_resource mlxbf_i2c_gpio_res[] = अणु
	[MLXBF_I2C_CHIP_TYPE_1] = अणु
		.params = &mlxbf_i2c_gpio_tyu_params,
		.lock = &mlxbf_i2c_gpio_lock,
		.type = MLXBF_I2C_GPIO_RES
	पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल u8 mlxbf_i2c_bus_count;

अटल काष्ठा mutex mlxbf_i2c_bus_lock;

/* Polling frequency in microseconds. */
#घोषणा MLXBF_I2C_POLL_FREQ_IN_USEC        200

#घोषणा MLXBF_I2C_SHIFT_0   0
#घोषणा MLXBF_I2C_SHIFT_8   8
#घोषणा MLXBF_I2C_SHIFT_16  16
#घोषणा MLXBF_I2C_SHIFT_24  24

#घोषणा MLXBF_I2C_MASK_8    GENMASK(7, 0)
#घोषणा MLXBF_I2C_MASK_16   GENMASK(15, 0)

#घोषणा MLXBF_I2C_FREQUENCY_1GHZ  1000000000

/*
 * Function to poll a set of bits at a specअगरic address; it checks whether
 * the bits are equal to zero when eq_zero is set to 'true', and not equal
 * to zero when eq_zero is set to 'false'.
 * Note that the समयout is given in microseconds.
 */
अटल u32 mlxbf_smbus_poll(व्योम __iomem *io, u32 addr, u32 mask,
			    bool eq_zero, u32  समयout)
अणु
	u32 bits;

	समयout = (समयout / MLXBF_I2C_POLL_FREQ_IN_USEC) + 1;

	करो अणु
		bits = पढ़ोl(io + addr) & mask;
		अगर (eq_zero ? bits == 0 : bits != 0)
			वापस eq_zero ? 1 : bits;
		udelay(MLXBF_I2C_POLL_FREQ_IN_USEC);
	पूर्ण जबतक (समयout-- != 0);

	वापस 0;
पूर्ण

/*
 * SW must make sure that the SMBus Master GW is idle beक्रमe starting
 * a transaction. Accordingly, this function polls the Master FSM stop
 * bit; it वापसs false when the bit is निश्चितed, true अगर not.
 */
अटल bool mlxbf_smbus_master_रुको_क्रम_idle(काष्ठा mlxbf_i2c_priv *priv)
अणु
	u32 mask = MLXBF_I2C_SMBUS_MASTER_FSM_STOP_MASK;
	u32 addr = MLXBF_I2C_SMBUS_MASTER_FSM;
	u32 समयout = MLXBF_I2C_SMBUS_TIMEOUT;

	अगर (mlxbf_smbus_poll(priv->smbus->io, addr, mask, true, समयout))
		वापस true;

	वापस false;
पूर्ण

अटल bool mlxbf_i2c_smbus_transaction_success(u32 master_status,
						u32 cause_status)
अणु
	/*
	 * When transaction ended with STOP, all bytes were transmitted,
	 * and no NACK received, then the transaction ended successfully.
	 * On the other hand, when the GW is configured with the stop bit
	 * de-निश्चितed then the SMBus expects the following GW configuration
	 * क्रम transfer continuation.
	 */
	अगर ((cause_status & MLXBF_I2C_CAUSE_WAIT_FOR_FW_DATA) ||
	    ((cause_status & MLXBF_I2C_CAUSE_TRANSACTION_ENDED) &&
	     (master_status & MLXBF_I2C_SMBUS_STATUS_BYTE_CNT_DONE) &&
	     !(master_status & MLXBF_I2C_SMBUS_STATUS_NACK_RCV)))
		वापस true;

	वापस false;
पूर्ण

/*
 * Poll SMBus master status and वापस transaction status,
 * i.e. whether succeeded or failed. I2C and SMBus fault codes
 * are वापसed as negative numbers from most calls, with zero
 * or some positive number indicating a non-fault वापस.
 */
अटल पूर्णांक mlxbf_i2c_smbus_check_status(काष्ठा mlxbf_i2c_priv *priv)
अणु
	u32 master_status_bits;
	u32 cause_status_bits;

	/*
	 * GW busy bit is उठाओd by the driver and cleared by the HW
	 * when the transaction is completed. The busy bit is a good
	 * indicator of transaction status. So poll the busy bit, and
	 * then पढ़ो the cause and master status bits to determine अगर
	 * errors occurred during the transaction.
	 */
	mlxbf_smbus_poll(priv->smbus->io, MLXBF_I2C_SMBUS_MASTER_GW,
			 MLXBF_I2C_MASTER_BUSY_BIT, true,
			 MLXBF_I2C_SMBUS_TIMEOUT);

	/* Read cause status bits. */
	cause_status_bits = पढ़ोl(priv->mst_cause->io +
					MLXBF_I2C_CAUSE_ARBITER);
	cause_status_bits &= MLXBF_I2C_CAUSE_MASTER_ARBITER_BITS_MASK;

	/*
	 * Parse both Cause and Master GW bits, then वापस transaction status.
	 */

	master_status_bits = पढ़ोl(priv->smbus->io +
					MLXBF_I2C_SMBUS_MASTER_STATUS);
	master_status_bits &= MLXBF_I2C_SMBUS_MASTER_STATUS_MASK;

	अगर (mlxbf_i2c_smbus_transaction_success(master_status_bits,
						cause_status_bits))
		वापस 0;

	/*
	 * In हाल of समयout on GW busy, the ISR will clear busy bit but
	 * transaction ended bits cause will not be set so the transaction
	 * fails. Then, we must check Master GW status bits.
	 */
	अगर ((master_status_bits & MLXBF_I2C_SMBUS_MASTER_STATUS_ERROR) &&
	    (cause_status_bits & (MLXBF_I2C_CAUSE_TRANSACTION_ENDED |
				  MLXBF_I2C_CAUSE_M_GW_BUSY_FALL)))
		वापस -EIO;

	अगर (cause_status_bits & MLXBF_I2C_CAUSE_MASTER_STATUS_ERROR)
		वापस -EAGAIN;

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम mlxbf_i2c_smbus_ग_लिखो_data(काष्ठा mlxbf_i2c_priv *priv,
				       स्थिर u8 *data, u8 length, u32 addr)
अणु
	u8 offset, aligned_length;
	u32 data32;

	aligned_length = round_up(length, 4);

	/*
	 * Copy data bytes from 4-byte aligned source buffer.
	 * Data copied to the Master GW Data Descriptor MUST be shअगरted
	 * left so the data starts at the MSB of the descriptor रेजिस्टरs
	 * as required by the underlying hardware. Enable byte swapping
	 * when writing data bytes to the 32 * 32-bit HW Data रेजिस्टरs
	 * a.k.a Master GW Data Descriptor.
	 */
	क्रम (offset = 0; offset < aligned_length; offset += माप(u32)) अणु
		data32 = *((u32 *)(data + offset));
		ioग_लिखो32be(data32, priv->smbus->io + addr + offset);
	पूर्ण
पूर्ण

अटल व्योम mlxbf_i2c_smbus_पढ़ो_data(काष्ठा mlxbf_i2c_priv *priv,
				      u8 *data, u8 length, u32 addr)
अणु
	u32 data32, mask;
	u8 byte, offset;

	mask = माप(u32) - 1;

	/*
	 * Data bytes in the Master GW Data Descriptor are shअगरted left
	 * so the data starts at the MSB of the descriptor रेजिस्टरs as
	 * set by the underlying hardware. Enable byte swapping जबतक
	 * पढ़ोing data bytes from the 32 * 32-bit HW Data रेजिस्टरs
	 * a.k.a Master GW Data Descriptor.
	 */

	क्रम (offset = 0; offset < (length & ~mask); offset += माप(u32)) अणु
		data32 = ioपढ़ो32be(priv->smbus->io + addr + offset);
		*((u32 *)(data + offset)) = data32;
	पूर्ण

	अगर (!(length & mask))
		वापस;

	data32 = ioपढ़ो32be(priv->smbus->io + addr + offset);

	क्रम (byte = 0; byte < (length & mask); byte++) अणु
		data[offset + byte] = data32 & GENMASK(7, 0);
		data32 = ror32(data32, MLXBF_I2C_SHIFT_8);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxbf_i2c_smbus_enable(काष्ठा mlxbf_i2c_priv *priv, u8 slave,
				  u8 len, u8 block_en, u8 pec_en, bool पढ़ो)
अणु
	u32 command;

	/* Set Master GW control word. */
	अगर (पढ़ो) अणु
		command = MLXBF_I2C_MASTER_ENABLE_READ;
		command |= rol32(len, MLXBF_I2C_MASTER_READ_SHIFT);
	पूर्ण अन्यथा अणु
		command = MLXBF_I2C_MASTER_ENABLE_WRITE;
		command |= rol32(len, MLXBF_I2C_MASTER_WRITE_SHIFT);
	पूर्ण
	command |= rol32(slave, MLXBF_I2C_MASTER_SLV_ADDR_SHIFT);
	command |= rol32(block_en, MLXBF_I2C_MASTER_PARSE_EXP_SHIFT);
	command |= rol32(pec_en, MLXBF_I2C_MASTER_SEND_PEC_SHIFT);

	/* Clear status bits. */
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_MASTER_STATUS);
	/* Set the cause data. */
	ग_लिखोl(~0x0, priv->smbus->io + MLXBF_I2C_CAUSE_OR_CLEAR);
	/* Zero PEC byte. */
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_MASTER_PEC);
	/* Zero byte count. */
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_RS_BYTES);

	/* GW activation. */
	ग_लिखोl(command, priv->smbus->io + MLXBF_I2C_SMBUS_MASTER_GW);

	/*
	 * Poll master status and check status bits. An ACK is sent when
	 * completing writing data to the bus (Master 'byte_count_done' bit
	 * is set to 1).
	 */
	वापस mlxbf_i2c_smbus_check_status(priv);
पूर्ण

अटल पूर्णांक
mlxbf_i2c_smbus_start_transaction(काष्ठा mlxbf_i2c_priv *priv,
				  काष्ठा mlxbf_i2c_smbus_request *request)
अणु
	u8 data_desc[MLXBF_I2C_MASTER_DATA_DESC_SIZE] = अणु 0 पूर्ण;
	u8 op_idx, data_idx, data_len, ग_लिखो_len, पढ़ो_len;
	काष्ठा mlxbf_i2c_smbus_operation *operation;
	u8 पढ़ो_en, ग_लिखो_en, block_en, pec_en;
	u8 slave, flags, addr;
	u8 *पढ़ो_buf;
	पूर्णांक ret = 0;

	अगर (request->operation_cnt > MLXBF_I2C_SMBUS_MAX_OP_CNT)
		वापस -EINVAL;

	पढ़ो_buf = शून्य;
	data_idx = 0;
	पढ़ो_en = 0;
	ग_लिखो_en = 0;
	ग_लिखो_len = 0;
	पढ़ो_len = 0;
	block_en = 0;
	pec_en = 0;
	slave = request->slave & GENMASK(6, 0);
	addr = slave << 1;

	/* First of all, check whether the HW is idle. */
	अगर (WARN_ON(!mlxbf_smbus_master_रुको_क्रम_idle(priv)))
		वापस -EBUSY;

	/* Set first byte. */
	data_desc[data_idx++] = addr;

	क्रम (op_idx = 0; op_idx < request->operation_cnt; op_idx++) अणु
		operation = &request->operation[op_idx];
		flags = operation->flags;

		/*
		 * Note that पढ़ो and ग_लिखो operations might be handled by a
		 * single command. If the MLXBF_I2C_F_SMBUS_OPERATION is set
		 * then ग_लिखो command byte and set the optional SMBus specअगरic
		 * bits such as block_en and pec_en. These bits MUST be
		 * submitted by the first operation only.
		 */
		अगर (op_idx == 0 && flags & MLXBF_I2C_F_SMBUS_OPERATION) अणु
			block_en = flags & MLXBF_I2C_F_SMBUS_BLOCK;
			pec_en = flags & MLXBF_I2C_F_SMBUS_PEC;
		पूर्ण

		अगर (flags & MLXBF_I2C_F_WRITE) अणु
			ग_लिखो_en = 1;
			ग_लिखो_len += operation->length;
			स_नकल(data_desc + data_idx,
			       operation->buffer, operation->length);
			data_idx += operation->length;
		पूर्ण
		/*
		 * We assume that पढ़ो operations are perक्रमmed only once per
		 * SMBus transaction. *TBD* protect this statement so it won't
		 * be executed twice? or वापस an error अगर we try to पढ़ो more
		 * than once?
		 */
		अगर (flags & MLXBF_I2C_F_READ) अणु
			पढ़ो_en = 1;
			/* Subtract 1 as required by HW. */
			पढ़ो_len = operation->length - 1;
			पढ़ो_buf = operation->buffer;
		पूर्ण
	पूर्ण

	/* Set Master GW data descriptor. */
	data_len = ग_लिखो_len + 1; /* Add one byte of the slave address. */
	/*
	 * Note that data_len cannot be 0. Indeed, the slave address byte
	 * must be written to the data रेजिस्टरs.
	 */
	mlxbf_i2c_smbus_ग_लिखो_data(priv, (स्थिर u8 *)data_desc, data_len,
				   MLXBF_I2C_MASTER_DATA_DESC_ADDR);

	अगर (ग_लिखो_en) अणु
		ret = mlxbf_i2c_smbus_enable(priv, slave, ग_लिखो_len, block_en,
					 pec_en, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (पढ़ो_en) अणु
		/* Write slave address to Master GW data descriptor. */
		mlxbf_i2c_smbus_ग_लिखो_data(priv, (स्थिर u8 *)&addr, 1,
					   MLXBF_I2C_MASTER_DATA_DESC_ADDR);
		ret = mlxbf_i2c_smbus_enable(priv, slave, पढ़ो_len, block_en,
					 pec_en, 1);
		अगर (!ret) अणु
			/* Get Master GW data descriptor. */
			mlxbf_i2c_smbus_पढ़ो_data(priv, data_desc, पढ़ो_len + 1,
					     MLXBF_I2C_MASTER_DATA_DESC_ADDR);

			/* Get data from Master GW data descriptor. */
			स_नकल(पढ़ो_buf, data_desc, पढ़ो_len + 1);
		पूर्ण

		/*
		 * After a पढ़ो operation the SMBus FSM ps (present state)
		 * needs to be 'manually' reset. This should be हटाओd in
		 * next tag पूर्णांकegration.
		 */
		ग_लिखोl(MLXBF_I2C_SMBUS_MASTER_FSM_PS_STATE_MASK,
			priv->smbus->io + MLXBF_I2C_SMBUS_MASTER_FSM);
	पूर्ण

	वापस ret;
पूर्ण

/* I2C SMBus protocols. */

अटल व्योम
mlxbf_i2c_smbus_quick_command(काष्ठा mlxbf_i2c_smbus_request *request,
			      u8 पढ़ो)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_1;

	request->operation[0].length = 0;
	request->operation[0].flags = MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= पढ़ो ? MLXBF_I2C_F_READ : 0;
पूर्ण

अटल व्योम mlxbf_i2c_smbus_byte_func(काष्ठा mlxbf_i2c_smbus_request *request,
				      u8 *data, bool पढ़ो, bool pec_check)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_1;

	request->operation[0].length = 1;
	request->operation[0].length += pec_check;

	request->operation[0].flags = MLXBF_I2C_F_SMBUS_OPERATION;
	request->operation[0].flags |= पढ़ो ?
				MLXBF_I2C_F_READ : MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= pec_check ? MLXBF_I2C_F_SMBUS_PEC : 0;

	request->operation[0].buffer = data;
पूर्ण

अटल व्योम
mlxbf_i2c_smbus_data_byte_func(काष्ठा mlxbf_i2c_smbus_request *request,
			       u8 *command, u8 *data, bool पढ़ो, bool pec_check)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_2;

	request->operation[0].length = 1;
	request->operation[0].flags =
			MLXBF_I2C_F_SMBUS_OPERATION | MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= pec_check ? MLXBF_I2C_F_SMBUS_PEC : 0;
	request->operation[0].buffer = command;

	request->operation[1].length = 1;
	request->operation[1].length += pec_check;
	request->operation[1].flags = पढ़ो ?
				MLXBF_I2C_F_READ : MLXBF_I2C_F_WRITE;
	request->operation[1].buffer = data;
पूर्ण

अटल व्योम
mlxbf_i2c_smbus_data_word_func(काष्ठा mlxbf_i2c_smbus_request *request,
			       u8 *command, u8 *data, bool पढ़ो, bool pec_check)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_2;

	request->operation[0].length = 1;
	request->operation[0].flags =
			MLXBF_I2C_F_SMBUS_OPERATION | MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= pec_check ? MLXBF_I2C_F_SMBUS_PEC : 0;
	request->operation[0].buffer = command;

	request->operation[1].length = 2;
	request->operation[1].length += pec_check;
	request->operation[1].flags = पढ़ो ?
				MLXBF_I2C_F_READ : MLXBF_I2C_F_WRITE;
	request->operation[1].buffer = data;
पूर्ण

अटल व्योम
mlxbf_i2c_smbus_i2c_block_func(काष्ठा mlxbf_i2c_smbus_request *request,
			       u8 *command, u8 *data, u8 *data_len, bool पढ़ो,
			       bool pec_check)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_2;

	request->operation[0].length = 1;
	request->operation[0].flags =
			MLXBF_I2C_F_SMBUS_OPERATION | MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= pec_check ? MLXBF_I2C_F_SMBUS_PEC : 0;
	request->operation[0].buffer = command;

	/*
	 * As specअगरied in the standard, the max number of bytes to पढ़ो/ग_लिखो
	 * per block operation is 32 bytes. In Golan code, the controller can
	 * पढ़ो up to 128 bytes and ग_लिखो up to 127 bytes.
	 */
	request->operation[1].length =
	    (*data_len + pec_check > I2C_SMBUS_BLOCK_MAX) ?
	    I2C_SMBUS_BLOCK_MAX : *data_len + pec_check;
	request->operation[1].flags = पढ़ो ?
				MLXBF_I2C_F_READ : MLXBF_I2C_F_WRITE;
	/*
	 * Skip the first data byte, which corresponds to the number of bytes
	 * to पढ़ो/ग_लिखो.
	 */
	request->operation[1].buffer = data + 1;

	*data_len = request->operation[1].length;

	/* Set the number of byte to पढ़ो. This will be used by userspace. */
	अगर (पढ़ो)
		data[0] = *data_len;
पूर्ण

अटल व्योम mlxbf_i2c_smbus_block_func(काष्ठा mlxbf_i2c_smbus_request *request,
				       u8 *command, u8 *data, u8 *data_len,
				       bool पढ़ो, bool pec_check)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_2;

	request->operation[0].length = 1;
	request->operation[0].flags =
			MLXBF_I2C_F_SMBUS_OPERATION | MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= MLXBF_I2C_F_SMBUS_BLOCK;
	request->operation[0].flags |= pec_check ? MLXBF_I2C_F_SMBUS_PEC : 0;
	request->operation[0].buffer = command;

	request->operation[1].length =
	    (*data_len + pec_check > I2C_SMBUS_BLOCK_MAX) ?
	    I2C_SMBUS_BLOCK_MAX : *data_len + pec_check;
	request->operation[1].flags = पढ़ो ?
				MLXBF_I2C_F_READ : MLXBF_I2C_F_WRITE;
	request->operation[1].buffer = data + 1;

	*data_len = request->operation[1].length;

	/* Set the number of bytes to पढ़ो. This will be used by userspace. */
	अगर (पढ़ो)
		data[0] = *data_len;
पूर्ण

अटल व्योम
mlxbf_i2c_smbus_process_call_func(काष्ठा mlxbf_i2c_smbus_request *request,
				  u8 *command, u8 *data, bool pec_check)
अणु
	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_3;

	request->operation[0].length = 1;
	request->operation[0].flags =
			MLXBF_I2C_F_SMBUS_OPERATION | MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= MLXBF_I2C_F_SMBUS_BLOCK;
	request->operation[0].flags |= pec_check ? MLXBF_I2C_F_SMBUS_PEC : 0;
	request->operation[0].buffer = command;

	request->operation[1].length = 2;
	request->operation[1].flags = MLXBF_I2C_F_WRITE;
	request->operation[1].buffer = data;

	request->operation[2].length = 3;
	request->operation[2].flags = MLXBF_I2C_F_READ;
	request->operation[2].buffer = data;
पूर्ण

अटल व्योम
mlxbf_i2c_smbus_blk_process_call_func(काष्ठा mlxbf_i2c_smbus_request *request,
				      u8 *command, u8 *data, u8 *data_len,
				      bool pec_check)
अणु
	u32 length;

	request->operation_cnt = MLXBF_I2C_SMBUS_OP_CNT_3;

	request->operation[0].length = 1;
	request->operation[0].flags =
			MLXBF_I2C_F_SMBUS_OPERATION | MLXBF_I2C_F_WRITE;
	request->operation[0].flags |= MLXBF_I2C_F_SMBUS_BLOCK;
	request->operation[0].flags |= (pec_check) ? MLXBF_I2C_F_SMBUS_PEC : 0;
	request->operation[0].buffer = command;

	length = (*data_len + pec_check > I2C_SMBUS_BLOCK_MAX) ?
	    I2C_SMBUS_BLOCK_MAX : *data_len + pec_check;

	request->operation[1].length = length - pec_check;
	request->operation[1].flags = MLXBF_I2C_F_WRITE;
	request->operation[1].buffer = data;

	request->operation[2].length = length;
	request->operation[2].flags = MLXBF_I2C_F_READ;
	request->operation[2].buffer = data;

	*data_len = length; /* including PEC byte. */
पूर्ण

/* Initialization functions. */

अटल bool mlxbf_i2c_has_chip_type(काष्ठा mlxbf_i2c_priv *priv, u8 type)
अणु
	वापस priv->chip->type == type;
पूर्ण

अटल काष्ठा mlxbf_i2c_resource *
mlxbf_i2c_get_shared_resource(काष्ठा mlxbf_i2c_priv *priv, u8 type)
अणु
	स्थिर काष्ठा mlxbf_i2c_chip_info *chip = priv->chip;
	काष्ठा mlxbf_i2c_resource *res;
	u8 res_idx = 0;

	क्रम (res_idx = 0; res_idx < MLXBF_I2C_SHARED_RES_MAX; res_idx++) अणु
		res = chip->shared_res[res_idx];
		अगर (res && res->type == type)
			वापस res;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxbf_i2c_init_resource(काष्ठा platक्रमm_device *pdev,
				   काष्ठा mlxbf_i2c_resource **res,
				   u8 type)
अणु
	काष्ठा mlxbf_i2c_resource *पंचांगp_res;
	काष्ठा device *dev = &pdev->dev;

	अगर (!res || *res || type >= MLXBF_I2C_END_RES)
		वापस -EINVAL;

	पंचांगp_res = devm_kzalloc(dev, माप(काष्ठा mlxbf_i2c_resource),
			       GFP_KERNEL);
	अगर (!पंचांगp_res)
		वापस -ENOMEM;

	पंचांगp_res->params = platक्रमm_get_resource(pdev, IORESOURCE_MEM, type);
	अगर (!पंचांगp_res->params) अणु
		devm_kमुक्त(dev, पंचांगp_res);
		वापस -EIO;
	पूर्ण

	पंचांगp_res->io = devm_ioremap_resource(dev, पंचांगp_res->params);
	अगर (IS_ERR(पंचांगp_res->io)) अणु
		devm_kमुक्त(dev, पंचांगp_res);
		वापस PTR_ERR(पंचांगp_res->io);
	पूर्ण

	पंचांगp_res->type = type;

	*res = पंचांगp_res;

	वापस 0;
पूर्ण

अटल u32 mlxbf_i2c_get_ticks(काष्ठा mlxbf_i2c_priv *priv, u64 nanoseconds,
			       bool minimum)
अणु
	u64 frequency;
	u32 ticks;

	/*
	 * Compute ticks as follow:
	 *
	 *           Ticks
	 * Time = --------- x 10^9    =>    Ticks = Time x Frequency x 10^-9
	 *         Frequency
	 */
	frequency = priv->frequency;
	ticks = (nanoseconds * frequency) / MLXBF_I2C_FREQUENCY_1GHZ;
	/*
	 * The number of ticks is rounded करोwn and अगर minimum is equal to 1
	 * then add one tick.
	 */
	अगर (minimum)
		ticks++;

	वापस ticks;
पूर्ण

अटल u32 mlxbf_i2c_set_समयr(काष्ठा mlxbf_i2c_priv *priv, u64 nsec, bool opt,
			       u32 mask, u8 shअगरt)
अणु
	u32 val = (mlxbf_i2c_get_ticks(priv, nsec, opt) & mask) << shअगरt;

	वापस val;
पूर्ण

अटल व्योम mlxbf_i2c_set_timings(काष्ठा mlxbf_i2c_priv *priv,
				  स्थिर काष्ठा mlxbf_i2c_timings *timings)
अणु
	u32 समयr;

	समयr = mlxbf_i2c_set_समयr(priv, timings->scl_high,
				    false, MLXBF_I2C_MASK_16,
				    MLXBF_I2C_SHIFT_0);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->scl_low,
				     false, MLXBF_I2C_MASK_16,
				     MLXBF_I2C_SHIFT_16);
	ग_लिखोl(समयr, priv->smbus->io +
		MLXBF_I2C_SMBUS_TIMER_SCL_LOW_SCL_HIGH);

	समयr = mlxbf_i2c_set_समयr(priv, timings->sda_rise, false,
				    MLXBF_I2C_MASK_8, MLXBF_I2C_SHIFT_0);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->sda_fall, false,
				     MLXBF_I2C_MASK_8, MLXBF_I2C_SHIFT_8);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->scl_rise, false,
				     MLXBF_I2C_MASK_8, MLXBF_I2C_SHIFT_16);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->scl_fall, false,
				     MLXBF_I2C_MASK_8, MLXBF_I2C_SHIFT_24);
	ग_लिखोl(समयr, priv->smbus->io +
		MLXBF_I2C_SMBUS_TIMER_FALL_RISE_SPIKE);

	समयr = mlxbf_i2c_set_समयr(priv, timings->hold_start, true,
				    MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_0);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->hold_data, true,
				     MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_16);
	ग_लिखोl(समयr, priv->smbus->io + MLXBF_I2C_SMBUS_TIMER_THOLD);

	समयr = mlxbf_i2c_set_समयr(priv, timings->setup_start, true,
				    MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_0);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->setup_stop, true,
				     MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_16);
	ग_लिखोl(समयr, priv->smbus->io +
		MLXBF_I2C_SMBUS_TIMER_TSETUP_START_STOP);

	समयr = mlxbf_i2c_set_समयr(priv, timings->setup_data, true,
				    MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_0);
	ग_लिखोl(समयr, priv->smbus->io + MLXBF_I2C_SMBUS_TIMER_TSETUP_DATA);

	समयr = mlxbf_i2c_set_समयr(priv, timings->buf, false,
				    MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_0);
	समयr |= mlxbf_i2c_set_समयr(priv, timings->thigh_max, false,
				     MLXBF_I2C_MASK_16, MLXBF_I2C_SHIFT_16);
	ग_लिखोl(समयr, priv->smbus->io + MLXBF_I2C_SMBUS_THIGH_MAX_TBUF);

	समयr = timings->समयout;
	ग_लिखोl(समयr, priv->smbus->io + MLXBF_I2C_SMBUS_SCL_LOW_TIMEOUT);
पूर्ण

क्रमागत mlxbf_i2c_timings_config अणु
	MLXBF_I2C_TIMING_CONFIG_100KHZ,
	MLXBF_I2C_TIMING_CONFIG_400KHZ,
	MLXBF_I2C_TIMING_CONFIG_1000KHZ,
पूर्ण;

/*
 * Note that the mlxbf_i2c_timings->समयout value is not related to the
 * bus frequency, it is impacted by the समय it takes the driver to
 * complete data transmission beक्रमe transaction पात.
 */
अटल स्थिर काष्ठा mlxbf_i2c_timings mlxbf_i2c_timings[] = अणु
	[MLXBF_I2C_TIMING_CONFIG_100KHZ] = अणु
		.scl_high = 4810,
		.scl_low = 5000,
		.hold_start = 4000,
		.setup_start = 4800,
		.setup_stop = 4000,
		.setup_data = 250,
		.sda_rise = 50,
		.sda_fall = 50,
		.scl_rise = 50,
		.scl_fall = 50,
		.hold_data = 300,
		.buf = 20000,
		.thigh_max = 5000,
		.समयout = 106500
	पूर्ण,
	[MLXBF_I2C_TIMING_CONFIG_400KHZ] = अणु
		.scl_high = 1011,
		.scl_low = 1300,
		.hold_start = 600,
		.setup_start = 700,
		.setup_stop = 600,
		.setup_data = 100,
		.sda_rise = 50,
		.sda_fall = 50,
		.scl_rise = 50,
		.scl_fall = 50,
		.hold_data = 300,
		.buf = 20000,
		.thigh_max = 5000,
		.समयout = 106500
	पूर्ण,
	[MLXBF_I2C_TIMING_CONFIG_1000KHZ] = अणु
		.scl_high = 600,
		.scl_low = 1300,
		.hold_start = 600,
		.setup_start = 600,
		.setup_stop = 600,
		.setup_data = 100,
		.sda_rise = 50,
		.sda_fall = 50,
		.scl_rise = 50,
		.scl_fall = 50,
		.hold_data = 300,
		.buf = 20000,
		.thigh_max = 5000,
		.समयout = 106500
	पूर्ण
पूर्ण;

अटल पूर्णांक mlxbf_i2c_init_timings(काष्ठा platक्रमm_device *pdev,
				  काष्ठा mlxbf_i2c_priv *priv)
अणु
	क्रमागत mlxbf_i2c_timings_config config_idx;
	काष्ठा device *dev = &pdev->dev;
	u32 config_khz;

	पूर्णांक ret;

	ret = device_property_पढ़ो_u32(dev, "clock-frequency", &config_khz);
	अगर (ret < 0)
		config_khz = I2C_MAX_STANDARD_MODE_FREQ;

	चयन (config_khz) अणु
	शेष:
		/* Default settings is 100 KHz. */
		pr_warn("Illegal value %d: defaulting to 100 KHz\n",
			config_khz);
		fallthrough;
	हाल I2C_MAX_STANDARD_MODE_FREQ:
		config_idx = MLXBF_I2C_TIMING_CONFIG_100KHZ;
		अवरोध;

	हाल I2C_MAX_FAST_MODE_FREQ:
		config_idx = MLXBF_I2C_TIMING_CONFIG_400KHZ;
		अवरोध;

	हाल I2C_MAX_FAST_MODE_PLUS_FREQ:
		config_idx = MLXBF_I2C_TIMING_CONFIG_1000KHZ;
		अवरोध;
	पूर्ण

	mlxbf_i2c_set_timings(priv, &mlxbf_i2c_timings[config_idx]);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_get_gpio(काष्ठा platक्रमm_device *pdev,
			      काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *gpio_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource	*params;
	resource_माप_प्रकार size;

	gpio_res = mlxbf_i2c_get_shared_resource(priv, MLXBF_I2C_GPIO_RES);
	अगर (!gpio_res)
		वापस -EPERM;

	/*
	 * The GPIO region in TYU space is shared among I2C busses.
	 * This function MUST be serialized to aव्योम racing when
	 * claiming the memory region and/or setting up the GPIO.
	 */
	lockdep_निश्चित_held(gpio_res->lock);

	/* Check whether the memory map exist. */
	अगर (gpio_res->io)
		वापस 0;

	params = gpio_res->params;
	size = resource_size(params);

	अगर (!devm_request_mem_region(dev, params->start, size, params->name))
		वापस -EFAULT;

	gpio_res->io = devm_ioremap(dev, params->start, size);
	अगर (!gpio_res->io) अणु
		devm_release_mem_region(dev, params->start, size);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_release_gpio(काष्ठा platक्रमm_device *pdev,
				  काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *gpio_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource	*params;

	gpio_res = mlxbf_i2c_get_shared_resource(priv, MLXBF_I2C_GPIO_RES);
	अगर (!gpio_res)
		वापस 0;

	mutex_lock(gpio_res->lock);

	अगर (gpio_res->io) अणु
		/* Release the GPIO resource. */
		params = gpio_res->params;
		devm_iounmap(dev, gpio_res->io);
		devm_release_mem_region(dev, params->start,
					resource_size(params));
	पूर्ण

	mutex_unlock(gpio_res->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_get_corepll(काष्ठा platक्रमm_device *pdev,
				 काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *corepll_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *params;
	resource_माप_प्रकार size;

	corepll_res = mlxbf_i2c_get_shared_resource(priv,
						    MLXBF_I2C_COREPLL_RES);
	अगर (!corepll_res)
		वापस -EPERM;

	/*
	 * The COREPLL region in TYU space is shared among I2C busses.
	 * This function MUST be serialized to aव्योम racing when
	 * claiming the memory region.
	 */
	lockdep_निश्चित_held(corepll_res->lock);

	/* Check whether the memory map exist. */
	अगर (corepll_res->io)
		वापस 0;

	params = corepll_res->params;
	size = resource_size(params);

	अगर (!devm_request_mem_region(dev, params->start, size, params->name))
		वापस -EFAULT;

	corepll_res->io = devm_ioremap(dev, params->start, size);
	अगर (!corepll_res->io) अणु
		devm_release_mem_region(dev, params->start, size);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_release_corepll(काष्ठा platक्रमm_device *pdev,
				     काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *corepll_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *params;

	corepll_res = mlxbf_i2c_get_shared_resource(priv,
						    MLXBF_I2C_COREPLL_RES);

	mutex_lock(corepll_res->lock);

	अगर (corepll_res->io) अणु
		/* Release the CorePLL resource. */
		params = corepll_res->params;
		devm_iounmap(dev, corepll_res->io);
		devm_release_mem_region(dev, params->start,
					resource_size(params));
	पूर्ण

	mutex_unlock(corepll_res->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_init_master(काष्ठा platक्रमm_device *pdev,
				 काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *gpio_res;
	काष्ठा device *dev = &pdev->dev;
	u32 config_reg;
	पूर्णांक ret;

	/* This configuration is only needed क्रम BlueField 1. */
	अगर (!mlxbf_i2c_has_chip_type(priv, MLXBF_I2C_CHIP_TYPE_1))
		वापस 0;

	gpio_res = mlxbf_i2c_get_shared_resource(priv, MLXBF_I2C_GPIO_RES);
	अगर (!gpio_res)
		वापस -EPERM;

	/*
	 * The GPIO region in TYU space is shared among I2C busses.
	 * This function MUST be serialized to aव्योम racing when
	 * claiming the memory region and/or setting up the GPIO.
	 */

	mutex_lock(gpio_res->lock);

	ret = mlxbf_i2c_get_gpio(pdev, priv);
	अगर (ret < 0) अणु
		dev_err(dev, "Failed to get gpio resource");
		mutex_unlock(gpio_res->lock);
		वापस ret;
	पूर्ण

	/*
	 * TYU - Configuration क्रम GPIO pins. Those pins must be निश्चितed in
	 * MLXBF_I2C_GPIO_0_FUNC_EN_0, i.e. GPIO 0 is controlled by HW, and must
	 * be reset in MLXBF_I2C_GPIO_0_FORCE_OE_EN, i.e. GPIO_OE will be driven
	 * instead of HW_OE.
	 * For now, we करो not reset the GPIO state when the driver is हटाओd.
	 * First, it is not necessary to disable the bus since we are using
	 * the same busses. Then, some busses might be shared among Linux and
	 * platक्रमm firmware; disabling the bus might compromise the प्रणाली
	 * functionality.
	 */
	config_reg = पढ़ोl(gpio_res->io + MLXBF_I2C_GPIO_0_FUNC_EN_0);
	config_reg = MLXBF_I2C_GPIO_SMBUS_GW_ASSERT_PINS(priv->bus,
							 config_reg);
	ग_लिखोl(config_reg, gpio_res->io + MLXBF_I2C_GPIO_0_FUNC_EN_0);

	config_reg = पढ़ोl(gpio_res->io + MLXBF_I2C_GPIO_0_FORCE_OE_EN);
	config_reg = MLXBF_I2C_GPIO_SMBUS_GW_RESET_PINS(priv->bus,
							config_reg);
	ग_लिखोl(config_reg, gpio_res->io + MLXBF_I2C_GPIO_0_FORCE_OE_EN);

	mutex_unlock(gpio_res->lock);

	वापस 0;
पूर्ण

अटल u64 mlxbf_calculate_freq_from_tyu(काष्ठा mlxbf_i2c_resource *corepll_res)
अणु
	u64 core_frequency, pad_frequency;
	u8 core_od, core_r;
	u32 corepll_val;
	u16 core_f;

	pad_frequency = MLXBF_I2C_PLL_IN_FREQ;

	corepll_val = पढ़ोl(corepll_res->io + MLXBF_I2C_CORE_PLL_REG1);

	/* Get Core PLL configuration bits. */
	core_f = rol32(corepll_val, MLXBF_I2C_COREPLL_CORE_F_TYU_SHIFT) &
			MLXBF_I2C_COREPLL_CORE_F_TYU_MASK;
	core_od = rol32(corepll_val, MLXBF_I2C_COREPLL_CORE_OD_TYU_SHIFT) &
			MLXBF_I2C_COREPLL_CORE_OD_TYU_MASK;
	core_r = rol32(corepll_val, MLXBF_I2C_COREPLL_CORE_R_TYU_SHIFT) &
			MLXBF_I2C_COREPLL_CORE_R_TYU_MASK;

	/*
	 * Compute PLL output frequency as follow:
	 *
	 *                                       CORE_F + 1
	 * PLL_OUT_FREQ = PLL_IN_FREQ * ----------------------------
	 *                              (CORE_R + 1) * (CORE_OD + 1)
	 *
	 * Where PLL_OUT_FREQ and PLL_IN_FREQ refer to CoreFrequency
	 * and PadFrequency, respectively.
	 */
	core_frequency = pad_frequency * (++core_f);
	core_frequency /= (++core_r) * (++core_od);

	वापस core_frequency;
पूर्ण

अटल u64 mlxbf_calculate_freq_from_yu(काष्ठा mlxbf_i2c_resource *corepll_res)
अणु
	u32 corepll_reg1_val, corepll_reg2_val;
	u64 corepll_frequency, pad_frequency;
	u8 core_od, core_r;
	u32 core_f;

	pad_frequency = MLXBF_I2C_PLL_IN_FREQ;

	corepll_reg1_val = पढ़ोl(corepll_res->io + MLXBF_I2C_CORE_PLL_REG1);
	corepll_reg2_val = पढ़ोl(corepll_res->io + MLXBF_I2C_CORE_PLL_REG2);

	/* Get Core PLL configuration bits */
	core_f = rol32(corepll_reg1_val, MLXBF_I2C_COREPLL_CORE_F_YU_SHIFT) &
			MLXBF_I2C_COREPLL_CORE_F_YU_MASK;
	core_r = rol32(corepll_reg1_val, MLXBF_I2C_COREPLL_CORE_R_YU_SHIFT) &
			MLXBF_I2C_COREPLL_CORE_R_YU_MASK;
	core_od = rol32(corepll_reg2_val,  MLXBF_I2C_COREPLL_CORE_OD_YU_SHIFT) &
			MLXBF_I2C_COREPLL_CORE_OD_YU_MASK;

	/*
	 * Compute PLL output frequency as follow:
	 *
	 *                                     CORE_F / 16384
	 * PLL_OUT_FREQ = PLL_IN_FREQ * ----------------------------
	 *                              (CORE_R + 1) * (CORE_OD + 1)
	 *
	 * Where PLL_OUT_FREQ and PLL_IN_FREQ refer to CoreFrequency
	 * and PadFrequency, respectively.
	 */
	corepll_frequency = (pad_frequency * core_f) / MLNXBF_I2C_COREPLL_CONST;
	corepll_frequency /= (++core_r) * (++core_od);

	वापस corepll_frequency;
पूर्ण

अटल पूर्णांक mlxbf_i2c_calculate_corepll_freq(काष्ठा platक्रमm_device *pdev,
					    काष्ठा mlxbf_i2c_priv *priv)
अणु
	स्थिर काष्ठा mlxbf_i2c_chip_info *chip = priv->chip;
	काष्ठा mlxbf_i2c_resource *corepll_res;
	काष्ठा device *dev = &pdev->dev;
	u64 *freq = &priv->frequency;
	पूर्णांक ret;

	corepll_res = mlxbf_i2c_get_shared_resource(priv,
						    MLXBF_I2C_COREPLL_RES);
	अगर (!corepll_res)
		वापस -EPERM;

	/*
	 * First, check whether the TYU core Clock frequency is set.
	 * The TYU core frequency is the same क्रम all I2C busses; when
	 * the first device माला_लो probed the frequency is determined and
	 * stored पूर्णांकo a globally visible variable. So, first of all,
	 * check whether the frequency is alपढ़ोy set. Here, we assume
	 * that the frequency is expected to be greater than 0.
	 */
	mutex_lock(corepll_res->lock);
	अगर (!mlxbf_i2c_corepll_frequency) अणु
		अगर (!chip->calculate_freq) अणु
			mutex_unlock(corepll_res->lock);
			वापस -EPERM;
		पूर्ण

		ret = mlxbf_i2c_get_corepll(pdev, priv);
		अगर (ret < 0) अणु
			dev_err(dev, "Failed to get corePLL resource");
			mutex_unlock(corepll_res->lock);
			वापस ret;
		पूर्ण

		mlxbf_i2c_corepll_frequency = chip->calculate_freq(corepll_res);
	पूर्ण
	mutex_unlock(corepll_res->lock);

	*freq = mlxbf_i2c_corepll_frequency;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_slave_enable(काष्ठा mlxbf_i2c_priv *priv, u8 addr)
अणु
	u32 slave_reg, slave_reg_पंचांगp, slave_reg_avail, slave_addr_mask;
	u8 reg, reg_cnt, byte, addr_पंचांगp, reg_avail, byte_avail;
	bool avail, disabled;

	disabled = false;
	avail = false;

	अगर (!priv)
		वापस -EPERM;

	reg_cnt = MLXBF_I2C_SMBUS_SLAVE_ADDR_CNT >> 2;
	slave_addr_mask = MLXBF_I2C_SMBUS_SLAVE_ADDR_MASK;

	/*
	 * Read the slave रेजिस्टरs. There are 4 * 32-bit slave रेजिस्टरs.
	 * Each slave रेजिस्टर can hold up to 4 * 8-bit slave configuration
	 * (7-bit address, 1 status bit (1 अगर enabled, 0 अगर not)).
	 */
	क्रम (reg = 0; reg < reg_cnt; reg++) अणु
		slave_reg = पढ़ोl(priv->smbus->io +
				MLXBF_I2C_SMBUS_SLAVE_ADDR_CFG + reg * 0x4);
		/*
		 * Each रेजिस्टर holds 4 slave addresses. So, we have to keep
		 * the byte order consistent with the value पढ़ो in order to
		 * update the रेजिस्टर correctly, अगर needed.
		 */
		slave_reg_पंचांगp = slave_reg;
		क्रम (byte = 0; byte < 4; byte++) अणु
			addr_पंचांगp = slave_reg_पंचांगp & GENMASK(7, 0);

			/*
			 * Mark the first available slave address slot, i.e. its
			 * enabled bit should be unset. This slot might be used
			 * later on to रेजिस्टर our slave.
			 */
			अगर (!avail && !MLXBF_I2C_SLAVE_ADDR_ENABLED(addr_पंचांगp)) अणु
				avail = true;
				reg_avail = reg;
				byte_avail = byte;
				slave_reg_avail = slave_reg;
			पूर्ण

			/*
			 * Parse slave address bytes and check whether the
			 * slave address alपढ़ोy exists and it's enabled,
			 * i.e. most signअगरicant bit is set.
			 */
			अगर ((addr_पंचांगp & slave_addr_mask) == addr) अणु
				अगर (MLXBF_I2C_SLAVE_ADDR_ENABLED(addr_पंचांगp))
					वापस 0;
				disabled = true;
				अवरोध;
			पूर्ण

			/* Parse next byte. */
			slave_reg_पंचांगp >>= 8;
		पूर्ण

		/* Exit the loop अगर the slave address is found. */
		अगर (disabled)
			अवरोध;
	पूर्ण

	अगर (!avail && !disabled)
		वापस -EINVAL; /* No room क्रम a new slave address. */

	अगर (avail && !disabled) अणु
		reg = reg_avail;
		byte = byte_avail;
		/* Set the slave address. */
		slave_reg_avail &= ~(slave_addr_mask << (byte * 8));
		slave_reg_avail |= addr << (byte * 8);
		slave_reg = slave_reg_avail;
	पूर्ण

	/* Enable the slave address and update the रेजिस्टर. */
	slave_reg |= (1 << MLXBF_I2C_SMBUS_SLAVE_ADDR_EN_BIT) << (byte * 8);
	ग_लिखोl(slave_reg, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_ADDR_CFG +
		reg * 0x4);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_slave_disable(काष्ठा mlxbf_i2c_priv *priv)
अणु
	u32 slave_reg, slave_reg_पंचांगp, slave_addr_mask;
	u8 addr, addr_पंचांगp, reg, reg_cnt, slave_byte;
	काष्ठा i2c_client *client = priv->slave;
	bool exist;

	exist = false;

	addr = client->addr;
	reg_cnt = MLXBF_I2C_SMBUS_SLAVE_ADDR_CNT >> 2;
	slave_addr_mask = MLXBF_I2C_SMBUS_SLAVE_ADDR_MASK;

	/*
	 * Read the slave रेजिस्टरs. There are 4 * 32-bit slave रेजिस्टरs.
	 * Each slave रेजिस्टर can hold up to 4 * 8-bit slave configuration
	 * (7-bit address, 1 status bit (1 अगर enabled, 0 अगर not)).
	 */
	क्रम (reg = 0; reg < reg_cnt; reg++) अणु
		slave_reg = पढ़ोl(priv->smbus->io +
				MLXBF_I2C_SMBUS_SLAVE_ADDR_CFG + reg * 0x4);

		/* Check whether the address slots are empty. */
		अगर (slave_reg == 0)
			जारी;

		/*
		 * Each रेजिस्टर holds 4 slave addresses. So, we have to keep
		 * the byte order consistent with the value पढ़ो in order to
		 * update the रेजिस्टर correctly, अगर needed.
		 */
		slave_reg_पंचांगp = slave_reg;
		slave_byte = 0;
		जबतक (slave_reg_पंचांगp != 0) अणु
			addr_पंचांगp = slave_reg_पंचांगp & slave_addr_mask;
			/*
			 * Parse slave address bytes and check whether the
			 * slave address alपढ़ोy exists.
			 */
			अगर (addr_पंचांगp == addr) अणु
				exist = true;
				अवरोध;
			पूर्ण

			/* Parse next byte. */
			slave_reg_पंचांगp >>= 8;
			slave_byte += 1;
		पूर्ण

		/* Exit the loop अगर the slave address is found. */
		अगर (exist)
			अवरोध;
	पूर्ण

	अगर (!exist)
		वापस 0; /* Slave is not रेजिस्टरed, nothing to करो. */

	/* Cleanup the slave address slot. */
	slave_reg &= ~(GENMASK(7, 0) << (slave_byte * 8));
	ग_लिखोl(slave_reg, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_ADDR_CFG +
		reg * 0x4);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_init_coalesce(काष्ठा platक्रमm_device *pdev,
				   काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *coalesce_res;
	काष्ठा resource *params;
	resource_माप_प्रकार size;
	पूर्णांक ret = 0;

	/*
	 * Unlike BlueField-1 platक्रमm, the coalesce रेजिस्टरs is a dedicated
	 * resource in the next generations of BlueField.
	 */
	अगर (mlxbf_i2c_has_chip_type(priv, MLXBF_I2C_CHIP_TYPE_1)) अणु
		coalesce_res = mlxbf_i2c_get_shared_resource(priv,
						MLXBF_I2C_COALESCE_RES);
		अगर (!coalesce_res)
			वापस -EPERM;

		/*
		 * The Cause Coalesce group in TYU space is shared among
		 * I2C busses. This function MUST be serialized to aव्योम
		 * racing when claiming the memory region.
		 */
		lockdep_निश्चित_held(mlxbf_i2c_gpio_res->lock);

		/* Check whether the memory map exist. */
		अगर (coalesce_res->io) अणु
			priv->coalesce = coalesce_res;
			वापस 0;
		पूर्ण

		params = coalesce_res->params;
		size = resource_size(params);

		अगर (!request_mem_region(params->start, size, params->name))
			वापस -EFAULT;

		coalesce_res->io = ioremap(params->start, size);
		अगर (!coalesce_res->io) अणु
			release_mem_region(params->start, size);
			वापस -ENOMEM;
		पूर्ण

		priv->coalesce = coalesce_res;

	पूर्ण अन्यथा अणु
		ret = mlxbf_i2c_init_resource(pdev, &priv->coalesce,
					      MLXBF_I2C_COALESCE_RES);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक mlxbf_i2c_release_coalesce(काष्ठा platक्रमm_device *pdev,
				      काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा mlxbf_i2c_resource *coalesce_res;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *params;
	resource_माप_प्रकार size;

	coalesce_res = priv->coalesce;

	अगर (coalesce_res->io) अणु
		params = coalesce_res->params;
		size = resource_size(params);
		अगर (mlxbf_i2c_has_chip_type(priv, MLXBF_I2C_CHIP_TYPE_1)) अणु
			mutex_lock(coalesce_res->lock);
			iounmap(coalesce_res->io);
			release_mem_region(params->start, size);
			mutex_unlock(coalesce_res->lock);
		पूर्ण अन्यथा अणु
			devm_release_mem_region(dev, params->start, size);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_init_slave(काष्ठा platक्रमm_device *pdev,
				काष्ठा mlxbf_i2c_priv *priv)
अणु
	काष्ठा device *dev = &pdev->dev;
	u32 पूर्णांक_reg;
	पूर्णांक ret;

	/* Reset FSM. */
	ग_लिखोl(0, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_FSM);

	/*
	 * Enable slave cause पूर्णांकerrupt bits. Drive
	 * MLXBF_I2C_CAUSE_READ_WAIT_FW_RESPONSE and
	 * MLXBF_I2C_CAUSE_WRITE_SUCCESS, these are enabled when an बाह्यal
	 * masters issue a Read and Write, respectively. But, clear all
	 * पूर्णांकerrupts first.
	 */
	ग_लिखोl(~0, priv->slv_cause->io + MLXBF_I2C_CAUSE_OR_CLEAR);
	पूर्णांक_reg = MLXBF_I2C_CAUSE_READ_WAIT_FW_RESPONSE;
	पूर्णांक_reg |= MLXBF_I2C_CAUSE_WRITE_SUCCESS;
	ग_लिखोl(पूर्णांक_reg, priv->slv_cause->io + MLXBF_I2C_CAUSE_OR_EVTEN0);

	/* Finally, set the 'ready' bit to start handling transactions. */
	ग_लिखोl(0x1, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_READY);

	/* Initialize the cause coalesce resource. */
	ret = mlxbf_i2c_init_coalesce(pdev, priv);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize cause coalesce\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool mlxbf_i2c_has_coalesce(काष्ठा mlxbf_i2c_priv *priv, bool *पढ़ो,
				   bool *ग_लिखो)
अणु
	स्थिर काष्ठा mlxbf_i2c_chip_info *chip = priv->chip;
	u32 coalesce0_reg, cause_reg;
	u8 slave_shअगरt, is_set;

	*ग_लिखो = false;
	*पढ़ो = false;

	slave_shअगरt = chip->type != MLXBF_I2C_CHIP_TYPE_1 ?
				MLXBF_I2C_CAUSE_YU_SLAVE_BIT :
				priv->bus + MLXBF_I2C_CAUSE_TYU_SLAVE_BIT;

	coalesce0_reg = पढ़ोl(priv->coalesce->io + MLXBF_I2C_CAUSE_COALESCE_0);
	is_set = coalesce0_reg & (1 << slave_shअगरt);

	अगर (!is_set)
		वापस false;

	/* Check the source of the पूर्णांकerrupt, i.e. whether a Read or Write. */
	cause_reg = पढ़ोl(priv->slv_cause->io + MLXBF_I2C_CAUSE_ARBITER);
	अगर (cause_reg & MLXBF_I2C_CAUSE_READ_WAIT_FW_RESPONSE)
		*पढ़ो = true;
	अन्यथा अगर (cause_reg & MLXBF_I2C_CAUSE_WRITE_SUCCESS)
		*ग_लिखो = true;

	/* Clear cause bits. */
	ग_लिखोl(~0x0, priv->slv_cause->io + MLXBF_I2C_CAUSE_OR_CLEAR);

	वापस true;
पूर्ण

अटल bool mlxbf_smbus_slave_रुको_क्रम_idle(काष्ठा mlxbf_i2c_priv *priv,
					    u32 समयout)
अणु
	u32 mask = MLXBF_I2C_CAUSE_S_GW_BUSY_FALL;
	u32 addr = MLXBF_I2C_CAUSE_ARBITER;

	अगर (mlxbf_smbus_poll(priv->slv_cause->io, addr, mask, false, समयout))
		वापस true;

	वापस false;
पूर्ण

/* Send byte to 'external' smbus master. */
अटल पूर्णांक mlxbf_smbus_irq_send(काष्ठा mlxbf_i2c_priv *priv, u8 recv_bytes)
अणु
	u8 data_desc[MLXBF_I2C_SLAVE_DATA_DESC_SIZE] = अणु 0 पूर्ण;
	u8 ग_लिखो_size, pec_en, addr, byte, value, byte_cnt, desc_size;
	काष्ठा i2c_client *slave = priv->slave;
	u32 control32, data32;
	पूर्णांक ret;

	अगर (!slave)
		वापस -EINVAL;

	addr = 0;
	byte = 0;
	desc_size = MLXBF_I2C_SLAVE_DATA_DESC_SIZE;

	/*
	 * Read bytes received from the बाह्यal master. These bytes should
	 * be located in the first data descriptor रेजिस्टर of the slave GW.
	 * These bytes are the slave address byte and the पूर्णांकernal रेजिस्टर
	 * address, अगर supplied.
	 */
	अगर (recv_bytes > 0) अणु
		data32 = ioपढ़ो32be(priv->smbus->io +
					MLXBF_I2C_SLAVE_DATA_DESC_ADDR);

		/* Parse the received bytes. */
		चयन (recv_bytes) अणु
		हाल 2:
			byte = (data32 >> 8) & GENMASK(7, 0);
			fallthrough;
		हाल 1:
			addr = (data32 & GENMASK(7, 0)) >> 1;
		पूर्ण

		/* Check whether it's our slave address. */
		अगर (slave->addr != addr)
			वापस -EINVAL;
	पूर्ण

	/*
	 * I2C पढ़ो transactions may start by a WRITE followed by a READ.
	 * Indeed, most slave devices would expect the पूर्णांकernal address
	 * following the slave address byte. So, ग_लिखो that byte first,
	 * and then, send the requested data bytes to the master.
	 */
	अगर (recv_bytes > 1) अणु
		i2c_slave_event(slave, I2C_SLAVE_WRITE_REQUESTED, &value);
		value = byte;
		ret = i2c_slave_event(slave, I2C_SLAVE_WRITE_RECEIVED,
				      &value);
		i2c_slave_event(slave, I2C_SLAVE_STOP, &value);

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/*
	 * Now, send data to the master; currently, the driver supports
	 * READ_BYTE, READ_WORD and BLOCK READ protocols. Note that the
	 * hardware can send up to 128 bytes per transfer. That is the
	 * size of its data रेजिस्टरs.
	 */
	i2c_slave_event(slave, I2C_SLAVE_READ_REQUESTED, &value);

	क्रम (byte_cnt = 0; byte_cnt < desc_size; byte_cnt++) अणु
		data_desc[byte_cnt] = value;
		i2c_slave_event(slave, I2C_SLAVE_READ_PROCESSED, &value);
	पूर्ण

	/* Send a stop condition to the backend. */
	i2c_slave_event(slave, I2C_SLAVE_STOP, &value);

	/* Handle the actual transfer. */

	/* Set the number of bytes to ग_लिखो to master. */
	ग_लिखो_size = (byte_cnt - 1) & 0x7f;

	/* Write data to Slave GW data descriptor. */
	mlxbf_i2c_smbus_ग_लिखो_data(priv, data_desc, byte_cnt,
				   MLXBF_I2C_SLAVE_DATA_DESC_ADDR);

	pec_en = 0; /* Disable PEC since it is not supported. */

	/* Prepare control word. */
	control32 = MLXBF_I2C_SLAVE_ENABLE;
	control32 |= rol32(ग_लिखो_size, MLXBF_I2C_SLAVE_WRITE_BYTES_SHIFT);
	control32 |= rol32(pec_en, MLXBF_I2C_SLAVE_SEND_PEC_SHIFT);

	ग_लिखोl(control32, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_GW);

	/*
	 * Wait until the transfer is completed; the driver will रुको
	 * until the GW is idle, a cause will rise on fall of GW busy.
	 */
	mlxbf_smbus_slave_रुको_क्रम_idle(priv, MLXBF_I2C_SMBUS_TIMEOUT);

	/* Release the Slave GW. */
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_RS_MASTER_BYTES);
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_PEC);
	ग_लिखोl(0x1, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_READY);

	वापस 0;
पूर्ण

/* Receive bytes from 'external' smbus master. */
अटल पूर्णांक mlxbf_smbus_irq_recv(काष्ठा mlxbf_i2c_priv *priv, u8 recv_bytes)
अणु
	u8 data_desc[MLXBF_I2C_SLAVE_DATA_DESC_SIZE] = अणु 0 पूर्ण;
	काष्ठा i2c_client *slave = priv->slave;
	u8 value, byte, addr;
	पूर्णांक ret = 0;

	अगर (!slave)
		वापस -EINVAL;

	/* Read data from Slave GW data descriptor. */
	mlxbf_i2c_smbus_पढ़ो_data(priv, data_desc, recv_bytes,
				  MLXBF_I2C_SLAVE_DATA_DESC_ADDR);

	/* Check whether its our slave address. */
	addr = data_desc[0] >> 1;
	अगर (slave->addr != addr)
		वापस -EINVAL;

	/*
	 * Notअगरy the slave backend; another I2C master wants to ग_लिखो data
	 * to us. This event is sent once the slave address and the ग_लिखो bit
	 * is detected.
	 */
	i2c_slave_event(slave, I2C_SLAVE_WRITE_REQUESTED, &value);

	/* Send the received data to the slave backend. */
	क्रम (byte = 1; byte < recv_bytes; byte++) अणु
		value = data_desc[byte];
		ret = i2c_slave_event(slave, I2C_SLAVE_WRITE_RECEIVED,
				      &value);
		अगर (ret < 0)
			अवरोध;
	पूर्ण

	/* Send a stop condition to the backend. */
	i2c_slave_event(slave, I2C_SLAVE_STOP, &value);

	/* Release the Slave GW. */
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_RS_MASTER_BYTES);
	ग_लिखोl(0x0, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_PEC);
	ग_लिखोl(0x1, priv->smbus->io + MLXBF_I2C_SMBUS_SLAVE_READY);

	वापस ret;
पूर्ण

अटल irqवापस_t mlxbf_smbus_irq(पूर्णांक irq, व्योम *ptr)
अणु
	काष्ठा mlxbf_i2c_priv *priv = ptr;
	bool पढ़ो, ग_लिखो, irq_is_set;
	u32 rw_bytes_reg;
	u8 recv_bytes;

	/*
	 * Read TYU पूर्णांकerrupt रेजिस्टर and determine the source of the
	 * पूर्णांकerrupt. Based on the source of the पूर्णांकerrupt one of the
	 * following actions are perक्रमmed:
	 *  - Receive data and send response to master.
	 *  - Send data and release slave GW.
	 *
	 * Handle पढ़ो/ग_लिखो transaction only. CRmaster and Iarp requests
	 * are ignored क्रम now.
	 */
	irq_is_set = mlxbf_i2c_has_coalesce(priv, &पढ़ो, &ग_लिखो);
	अगर (!irq_is_set || (!पढ़ो && !ग_लिखो)) अणु
		/* Nothing to करो here, पूर्णांकerrupt was not from this device. */
		वापस IRQ_NONE;
	पूर्ण

	/*
	 * The MLXBF_I2C_SMBUS_SLAVE_RS_MASTER_BYTES includes the number of
	 * bytes from/to master. These are defined by 8-bits each. If the lower
	 * 8 bits are set, then the master expect to पढ़ो N bytes from the
	 * slave, अगर the higher 8 bits are sent then the slave expect N bytes
	 * from the master.
	 */
	rw_bytes_reg = पढ़ोl(priv->smbus->io +
				MLXBF_I2C_SMBUS_SLAVE_RS_MASTER_BYTES);
	recv_bytes = (rw_bytes_reg >> 8) & GENMASK(7, 0);

	/*
	 * For now, the slave supports 128 bytes transfer. Discard reमुख्यing
	 * data bytes अगर the master wrote more than
	 * MLXBF_I2C_SLAVE_DATA_DESC_SIZE, i.e, the actual size of the slave
	 * data descriptor.
	 *
	 * Note that we will never expect to transfer more than 128 bytes; as
	 * specअगरied in the SMBus standard, block transactions cannot exceed
	 * 32 bytes.
	 */
	recv_bytes = recv_bytes > MLXBF_I2C_SLAVE_DATA_DESC_SIZE ?
		MLXBF_I2C_SLAVE_DATA_DESC_SIZE : recv_bytes;

	अगर (पढ़ो)
		mlxbf_smbus_irq_send(priv, recv_bytes);
	अन्यथा
		mlxbf_smbus_irq_recv(priv, recv_bytes);

	वापस IRQ_HANDLED;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 mlxbf_i2c_smbus_xfer(काष्ठा i2c_adapter *adap, u16 addr,
				अचिन्हित लघु flags, अक्षर पढ़ो_ग_लिखो,
				u8 command, पूर्णांक size,
				जोड़ i2c_smbus_data *data)
अणु
	काष्ठा mlxbf_i2c_smbus_request request = अणु 0 पूर्ण;
	काष्ठा mlxbf_i2c_priv *priv;
	bool पढ़ो, pec;
	u8 byte_cnt;

	request.slave = addr;

	पढ़ो = (पढ़ो_ग_लिखो == I2C_SMBUS_READ);
	pec = flags & I2C_FUNC_SMBUS_PEC;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		mlxbf_i2c_smbus_quick_command(&request, पढ़ो);
		dev_dbg(&adap->dev, "smbus quick, slave 0x%02x\n", addr);
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		mlxbf_i2c_smbus_byte_func(&request,
					  पढ़ो ? &data->byte : &command, पढ़ो,
					  pec);
		dev_dbg(&adap->dev, "smbus %s byte, slave 0x%02x.\n",
			पढ़ो ? "read" : "write", addr);
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		mlxbf_i2c_smbus_data_byte_func(&request, &command, &data->byte,
					       पढ़ो, pec);
		dev_dbg(&adap->dev, "smbus %s byte data at 0x%02x, slave 0x%02x.\n",
			पढ़ो ? "read" : "write", command, addr);
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		mlxbf_i2c_smbus_data_word_func(&request, &command,
					       (u8 *)&data->word, पढ़ो, pec);
		dev_dbg(&adap->dev, "smbus %s word data at 0x%02x, slave 0x%02x.\n",
			पढ़ो ? "read" : "write", command, addr);
		अवरोध;

	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		byte_cnt = data->block[0];
		mlxbf_i2c_smbus_i2c_block_func(&request, &command, data->block,
					       &byte_cnt, पढ़ो, pec);
		dev_dbg(&adap->dev, "i2c %s block data, %d bytes at 0x%02x, slave 0x%02x.\n",
			पढ़ो ? "read" : "write", byte_cnt, command, addr);
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		byte_cnt = पढ़ो ? I2C_SMBUS_BLOCK_MAX : data->block[0];
		mlxbf_i2c_smbus_block_func(&request, &command, data->block,
					   &byte_cnt, पढ़ो, pec);
		dev_dbg(&adap->dev, "smbus %s block data, %d bytes at 0x%02x, slave 0x%02x.\n",
			पढ़ो ? "read" : "write", byte_cnt, command, addr);
		अवरोध;

	हाल I2C_FUNC_SMBUS_PROC_CALL:
		mlxbf_i2c_smbus_process_call_func(&request, &command,
						  (u8 *)&data->word, pec);
		dev_dbg(&adap->dev, "process call, wr/rd at 0x%02x, slave 0x%02x.\n",
			command, addr);
		अवरोध;

	हाल I2C_FUNC_SMBUS_BLOCK_PROC_CALL:
		byte_cnt = data->block[0];
		mlxbf_i2c_smbus_blk_process_call_func(&request, &command,
						      data->block, &byte_cnt,
						      pec);
		dev_dbg(&adap->dev, "block process call, wr/rd %d bytes, slave 0x%02x.\n",
			byte_cnt, addr);
		अवरोध;

	शेष:
		dev_dbg(&adap->dev, "Unsupported I2C/SMBus command %d\n",
			size);
		वापस -EOPNOTSUPP;
	पूर्ण

	priv = i2c_get_adapdata(adap);

	वापस mlxbf_i2c_smbus_start_transaction(priv, &request);
पूर्ण

अटल पूर्णांक mlxbf_i2c_reg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा mlxbf_i2c_priv *priv = i2c_get_adapdata(slave->adapter);
	पूर्णांक ret;

	अगर (priv->slave)
		वापस -EBUSY;

	/*
	 * Do not support ten bit chip address and करो not use Packet Error
	 * Checking (PEC).
	 */
	अगर (slave->flags & (I2C_CLIENT_TEN | I2C_CLIENT_PEC))
		वापस -EAFNOSUPPORT;

	ret = mlxbf_slave_enable(priv, slave->addr);
	अगर (ret < 0)
		वापस ret;

	priv->slave = slave;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_unreg_slave(काष्ठा i2c_client *slave)
अणु
	काष्ठा mlxbf_i2c_priv *priv = i2c_get_adapdata(slave->adapter);
	पूर्णांक ret;

	WARN_ON(!priv->slave);

	/* Unरेजिस्टर slave, i.e. disable the slave address in hardware. */
	ret = mlxbf_slave_disable(priv);
	अगर (ret < 0)
		वापस ret;

	priv->slave = शून्य;

	वापस 0;
पूर्ण

अटल u32 mlxbf_i2c_functionality(काष्ठा i2c_adapter *adap)
अणु
	वापस MLXBF_I2C_FUNC_ALL;
पूर्ण

अटल काष्ठा mlxbf_i2c_chip_info mlxbf_i2c_chip[] = अणु
	[MLXBF_I2C_CHIP_TYPE_1] = अणु
		.type = MLXBF_I2C_CHIP_TYPE_1,
		.shared_res = अणु
			[0] = &mlxbf_i2c_coalesce_res[MLXBF_I2C_CHIP_TYPE_1],
			[1] = &mlxbf_i2c_corepll_res[MLXBF_I2C_CHIP_TYPE_1],
			[2] = &mlxbf_i2c_gpio_res[MLXBF_I2C_CHIP_TYPE_1]
		पूर्ण,
		.calculate_freq = mlxbf_calculate_freq_from_tyu
	पूर्ण,
	[MLXBF_I2C_CHIP_TYPE_2] = अणु
		.type = MLXBF_I2C_CHIP_TYPE_2,
		.shared_res = अणु
			[0] = &mlxbf_i2c_corepll_res[MLXBF_I2C_CHIP_TYPE_2]
		पूर्ण,
		.calculate_freq = mlxbf_calculate_freq_from_yu
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा i2c_algorithm mlxbf_i2c_algo = अणु
	.smbus_xfer = mlxbf_i2c_smbus_xfer,
	.functionality = mlxbf_i2c_functionality,
	.reg_slave = mlxbf_i2c_reg_slave,
	.unreg_slave = mlxbf_i2c_unreg_slave,
पूर्ण;

अटल काष्ठा i2c_adapter_quirks mlxbf_i2c_quirks = अणु
	.max_पढ़ो_len = MLXBF_I2C_MASTER_DATA_R_LENGTH,
	.max_ग_लिखो_len = MLXBF_I2C_MASTER_DATA_W_LENGTH,
पूर्ण;

अटल स्थिर काष्ठा of_device_id mlxbf_i2c_dt_ids[] = अणु
	अणु
		.compatible = "mellanox,i2c-mlxbf1",
		.data = &mlxbf_i2c_chip[MLXBF_I2C_CHIP_TYPE_1]
	पूर्ण,
	अणु
		.compatible = "mellanox,i2c-mlxbf2",
		.data = &mlxbf_i2c_chip[MLXBF_I2C_CHIP_TYPE_2]
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, mlxbf_i2c_dt_ids);

#अगर_घोषित CONFIG_ACPI
अटल स्थिर काष्ठा acpi_device_id mlxbf_i2c_acpi_ids[] = अणु
	अणु "MLNXBF03", (kernel_uदीर्घ_t)&mlxbf_i2c_chip[MLXBF_I2C_CHIP_TYPE_1] पूर्ण,
	अणु "MLNXBF23", (kernel_uदीर्घ_t)&mlxbf_i2c_chip[MLXBF_I2C_CHIP_TYPE_2] पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(acpi, mlxbf_i2c_acpi_ids);

अटल पूर्णांक mlxbf_i2c_acpi_probe(काष्ठा device *dev, काष्ठा mlxbf_i2c_priv *priv)
अणु
	स्थिर काष्ठा acpi_device_id *aid;
	काष्ठा acpi_device *adev;
	अचिन्हित दीर्घ bus_id = 0;
	स्थिर अक्षर *uid;
	पूर्णांक ret;

	अगर (acpi_disabled)
		वापस -ENOENT;

	adev = ACPI_COMPANION(dev);
	अगर (!adev)
		वापस -ENXIO;

	aid = acpi_match_device(mlxbf_i2c_acpi_ids, dev);
	अगर (!aid)
		वापस -ENODEV;

	priv->chip = (काष्ठा mlxbf_i2c_chip_info *)aid->driver_data;

	uid = acpi_device_uid(adev);
	अगर (!uid || !(*uid)) अणु
		dev_err(dev, "Cannot retrieve UID\n");
		वापस -ENODEV;
	पूर्ण

	ret = kम_से_अदीर्घ(uid, 0, &bus_id);
	अगर (!ret)
		priv->bus = bus_id;

	वापस ret;
पूर्ण
#अन्यथा
अटल पूर्णांक mlxbf_i2c_acpi_probe(काष्ठा device *dev, काष्ठा mlxbf_i2c_priv *priv)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर /* CONFIG_ACPI */

अटल पूर्णांक mlxbf_i2c_of_probe(काष्ठा device *dev, काष्ठा mlxbf_i2c_priv *priv)
अणु
	स्थिर काष्ठा of_device_id *oid;
	पूर्णांक bus_id = -1;

	अगर (IS_ENABLED(CONFIG_OF) && dev->of_node) अणु
		oid = of_match_node(mlxbf_i2c_dt_ids, dev->of_node);
		अगर (!oid)
			वापस -ENODEV;

		priv->chip = oid->data;

		bus_id = of_alias_get_id(dev->of_node, "i2c");
		अगर (bus_id >= 0)
			priv->bus = bus_id;
	पूर्ण

	अगर (bus_id < 0) अणु
		dev_err(dev, "Cannot get bus id");
		वापस bus_id;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा mlxbf_i2c_priv *priv;
	काष्ठा i2c_adapter *adap;
	पूर्णांक irq, ret;

	priv = devm_kzalloc(dev, माप(काष्ठा mlxbf_i2c_priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	ret = mlxbf_i2c_acpi_probe(dev, priv);
	अगर (ret < 0 && ret != -ENOENT && ret != -ENXIO)
		ret = mlxbf_i2c_of_probe(dev, priv);

	अगर (ret < 0)
		वापस ret;

	ret = mlxbf_i2c_init_resource(pdev, &priv->smbus,
				      MLXBF_I2C_SMBUS_RES);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot fetch smbus resource info");
		वापस ret;
	पूर्ण

	ret = mlxbf_i2c_init_resource(pdev, &priv->mst_cause,
				      MLXBF_I2C_MST_CAUSE_RES);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot fetch cause master resource info");
		वापस ret;
	पूर्ण

	ret = mlxbf_i2c_init_resource(pdev, &priv->slv_cause,
				      MLXBF_I2C_SLV_CAUSE_RES);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot fetch cause slave resource info");
		वापस ret;
	पूर्ण

	adap = &priv->adap;
	adap->owner = THIS_MODULE;
	adap->class = I2C_CLASS_HWMON;
	adap->algo = &mlxbf_i2c_algo;
	adap->quirks = &mlxbf_i2c_quirks;
	adap->dev.parent = dev;
	adap->dev.of_node = dev->of_node;
	adap->nr = priv->bus;

	snम_लिखो(adap->name, माप(adap->name), "i2c%d", adap->nr);
	i2c_set_adapdata(adap, priv);

	/* Read Core PLL frequency. */
	ret = mlxbf_i2c_calculate_corepll_freq(pdev, priv);
	अगर (ret < 0) अणु
		dev_err(dev, "cannot get core clock frequency\n");
		/* Set to शेष value. */
		priv->frequency = MLXBF_I2C_COREPLL_FREQ;
	पूर्ण

	/*
	 * Initialize master.
	 * Note that a physical bus might be shared among Linux and firmware
	 * (e.g., ATF). Thus, the bus should be initialized and पढ़ोy and
	 * bus initialization would be unnecessary. This requires additional
	 * knowledge about physical busses. But, since an extra initialization
	 * करोes not really hurt, then keep the code as is.
	 */
	ret = mlxbf_i2c_init_master(pdev, priv);
	अगर (ret < 0) अणु
		dev_err(dev, "failed to initialize smbus master %d",
			priv->bus);
		वापस ret;
	पूर्ण

	mlxbf_i2c_init_timings(pdev, priv);

	mlxbf_i2c_init_slave(pdev, priv);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस irq;
	ret = devm_request_irq(dev, irq, mlxbf_smbus_irq,
			       IRQF_ONESHOT | IRQF_SHARED | IRQF_PROBE_SHARED,
			       dev_name(dev), priv);
	अगर (ret < 0) अणु
		dev_err(dev, "Cannot get irq %d\n", irq);
		वापस ret;
	पूर्ण

	priv->irq = irq;

	platक्रमm_set_drvdata(pdev, priv);

	ret = i2c_add_numbered_adapter(adap);
	अगर (ret < 0)
		वापस ret;

	mutex_lock(&mlxbf_i2c_bus_lock);
	mlxbf_i2c_bus_count++;
	mutex_unlock(&mlxbf_i2c_bus_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक mlxbf_i2c_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा mlxbf_i2c_priv *priv = platक्रमm_get_drvdata(pdev);
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *params;

	params = priv->smbus->params;
	devm_release_mem_region(dev, params->start, resource_size(params));

	params = priv->mst_cause->params;
	devm_release_mem_region(dev, params->start, resource_size(params));

	params = priv->slv_cause->params;
	devm_release_mem_region(dev, params->start, resource_size(params));

	/*
	 * Release shared resources. This should be करोne when releasing
	 * the I2C controller.
	 */
	mutex_lock(&mlxbf_i2c_bus_lock);
	अगर (--mlxbf_i2c_bus_count == 0) अणु
		mlxbf_i2c_release_coalesce(pdev, priv);
		mlxbf_i2c_release_corepll(pdev, priv);
		mlxbf_i2c_release_gpio(pdev, priv);
	पूर्ण
	mutex_unlock(&mlxbf_i2c_bus_lock);

	devm_मुक्त_irq(dev, priv->irq, priv);

	i2c_del_adapter(&priv->adap);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mlxbf_i2c_driver = अणु
	.probe = mlxbf_i2c_probe,
	.हटाओ = mlxbf_i2c_हटाओ,
	.driver = अणु
		.name = "i2c-mlxbf",
		.of_match_table = mlxbf_i2c_dt_ids,
#अगर_घोषित CONFIG_ACPI
		.acpi_match_table = ACPI_PTR(mlxbf_i2c_acpi_ids),
#पूर्ण_अगर /* CONFIG_ACPI  */
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init mlxbf_i2c_init(व्योम)
अणु
	mutex_init(&mlxbf_i2c_coalesce_lock);
	mutex_init(&mlxbf_i2c_corepll_lock);
	mutex_init(&mlxbf_i2c_gpio_lock);

	mutex_init(&mlxbf_i2c_bus_lock);

	वापस platक्रमm_driver_रेजिस्टर(&mlxbf_i2c_driver);
पूर्ण
module_init(mlxbf_i2c_init);

अटल व्योम __निकास mlxbf_i2c_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&mlxbf_i2c_driver);

	mutex_destroy(&mlxbf_i2c_bus_lock);

	mutex_destroy(&mlxbf_i2c_gpio_lock);
	mutex_destroy(&mlxbf_i2c_corepll_lock);
	mutex_destroy(&mlxbf_i2c_coalesce_lock);
पूर्ण
module_निकास(mlxbf_i2c_निकास);

MODULE_DESCRIPTION("Mellanox BlueField I2C bus driver");
MODULE_AUTHOR("Khalil Blaiech <kblaiech@nvidia.com>");
MODULE_LICENSE("GPL v2");
