<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Synopsys DesignWare I2C adapter driver.
 *
 * Based on the TI DAVINCI I2C adapter driver.
 *
 * Copyright (C) 2006 Texas Instruments.
 * Copyright (C) 2007 MontaVista Software Inc.
 * Copyright (C) 2009 Provigent Ltd.
 */

#समावेश <linux/bits.h>
#समावेश <linux/compiler_types.h>
#समावेश <linux/completion.h>
#समावेश <linux/dev_prपूर्णांकk.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/regmap.h>
#समावेश <linux/types.h>

#घोषणा DW_IC_DEFAULT_FUNCTIONALITY (I2C_FUNC_I2C |			\
					I2C_FUNC_SMBUS_BYTE |		\
					I2C_FUNC_SMBUS_BYTE_DATA |	\
					I2C_FUNC_SMBUS_WORD_DATA |	\
					I2C_FUNC_SMBUS_BLOCK_DATA |	\
					I2C_FUNC_SMBUS_I2C_BLOCK)

#घोषणा DW_IC_CON_MASTER			BIT(0)
#घोषणा DW_IC_CON_SPEED_STD			(1 << 1)
#घोषणा DW_IC_CON_SPEED_FAST			(2 << 1)
#घोषणा DW_IC_CON_SPEED_HIGH			(3 << 1)
#घोषणा DW_IC_CON_SPEED_MASK			GENMASK(2, 1)
#घोषणा DW_IC_CON_10BITADDR_SLAVE		BIT(3)
#घोषणा DW_IC_CON_10BITADDR_MASTER		BIT(4)
#घोषणा DW_IC_CON_RESTART_EN			BIT(5)
#घोषणा DW_IC_CON_SLAVE_DISABLE			BIT(6)
#घोषणा DW_IC_CON_STOP_DET_IFADDRESSED		BIT(7)
#घोषणा DW_IC_CON_TX_EMPTY_CTRL			BIT(8)
#घोषणा DW_IC_CON_RX_FIFO_FULL_HLD_CTRL		BIT(9)

#घोषणा DW_IC_DATA_CMD_DAT			GENMASK(7, 0)

/*
 * Registers offset
 */
#घोषणा DW_IC_CON		0x00
#घोषणा DW_IC_TAR		0x04
#घोषणा DW_IC_SAR		0x08
#घोषणा DW_IC_DATA_CMD		0x10
#घोषणा DW_IC_SS_SCL_HCNT	0x14
#घोषणा DW_IC_SS_SCL_LCNT	0x18
#घोषणा DW_IC_FS_SCL_HCNT	0x1c
#घोषणा DW_IC_FS_SCL_LCNT	0x20
#घोषणा DW_IC_HS_SCL_HCNT	0x24
#घोषणा DW_IC_HS_SCL_LCNT	0x28
#घोषणा DW_IC_INTR_STAT		0x2c
#घोषणा DW_IC_INTR_MASK		0x30
#घोषणा DW_IC_RAW_INTR_STAT	0x34
#घोषणा DW_IC_RX_TL		0x38
#घोषणा DW_IC_TX_TL		0x3c
#घोषणा DW_IC_CLR_INTR		0x40
#घोषणा DW_IC_CLR_RX_UNDER	0x44
#घोषणा DW_IC_CLR_RX_OVER	0x48
#घोषणा DW_IC_CLR_TX_OVER	0x4c
#घोषणा DW_IC_CLR_RD_REQ	0x50
#घोषणा DW_IC_CLR_TX_ABRT	0x54
#घोषणा DW_IC_CLR_RX_DONE	0x58
#घोषणा DW_IC_CLR_ACTIVITY	0x5c
#घोषणा DW_IC_CLR_STOP_DET	0x60
#घोषणा DW_IC_CLR_START_DET	0x64
#घोषणा DW_IC_CLR_GEN_CALL	0x68
#घोषणा DW_IC_ENABLE		0x6c
#घोषणा DW_IC_STATUS		0x70
#घोषणा DW_IC_TXFLR		0x74
#घोषणा DW_IC_RXFLR		0x78
#घोषणा DW_IC_SDA_HOLD		0x7c
#घोषणा DW_IC_TX_ABRT_SOURCE	0x80
#घोषणा DW_IC_ENABLE_STATUS	0x9c
#घोषणा DW_IC_CLR_RESTART_DET	0xa8
#घोषणा DW_IC_COMP_PARAM_1	0xf4
#घोषणा DW_IC_COMP_VERSION	0xf8
#घोषणा DW_IC_SDA_HOLD_MIN_VERS	0x3131312A
#घोषणा DW_IC_COMP_TYPE		0xfc
#घोषणा DW_IC_COMP_TYPE_VALUE	0x44570140

#घोषणा DW_IC_INTR_RX_UNDER	BIT(0)
#घोषणा DW_IC_INTR_RX_OVER	BIT(1)
#घोषणा DW_IC_INTR_RX_FULL	BIT(2)
#घोषणा DW_IC_INTR_TX_OVER	BIT(3)
#घोषणा DW_IC_INTR_TX_EMPTY	BIT(4)
#घोषणा DW_IC_INTR_RD_REQ	BIT(5)
#घोषणा DW_IC_INTR_TX_ABRT	BIT(6)
#घोषणा DW_IC_INTR_RX_DONE	BIT(7)
#घोषणा DW_IC_INTR_ACTIVITY	BIT(8)
#घोषणा DW_IC_INTR_STOP_DET	BIT(9)
#घोषणा DW_IC_INTR_START_DET	BIT(10)
#घोषणा DW_IC_INTR_GEN_CALL	BIT(11)
#घोषणा DW_IC_INTR_RESTART_DET	BIT(12)

#घोषणा DW_IC_INTR_DEFAULT_MASK		(DW_IC_INTR_RX_FULL | \
					 DW_IC_INTR_TX_ABRT | \
					 DW_IC_INTR_STOP_DET)
#घोषणा DW_IC_INTR_MASTER_MASK		(DW_IC_INTR_DEFAULT_MASK | \
					 DW_IC_INTR_TX_EMPTY)
#घोषणा DW_IC_INTR_SLAVE_MASK		(DW_IC_INTR_DEFAULT_MASK | \
					 DW_IC_INTR_RX_DONE | \
					 DW_IC_INTR_RX_UNDER | \
					 DW_IC_INTR_RD_REQ)

#घोषणा DW_IC_STATUS_ACTIVITY		BIT(0)
#घोषणा DW_IC_STATUS_TFE		BIT(2)
#घोषणा DW_IC_STATUS_MASTER_ACTIVITY	BIT(5)
#घोषणा DW_IC_STATUS_SLAVE_ACTIVITY	BIT(6)

#घोषणा DW_IC_SDA_HOLD_RX_SHIFT		16
#घोषणा DW_IC_SDA_HOLD_RX_MASK		GENMASK(23, 16)

#घोषणा DW_IC_ERR_TX_ABRT	0x1

#घोषणा DW_IC_TAR_10BITADDR_MASTER BIT(12)

#घोषणा DW_IC_COMP_PARAM_1_SPEED_MODE_HIGH	(BIT(2) | BIT(3))
#घोषणा DW_IC_COMP_PARAM_1_SPEED_MODE_MASK	GENMASK(3, 2)

/*
 * status codes
 */
#घोषणा STATUS_IDLE			0x0
#घोषणा STATUS_WRITE_IN_PROGRESS	0x1
#घोषणा STATUS_READ_IN_PROGRESS		0x2

/*
 * operation modes
 */
#घोषणा DW_IC_MASTER		0
#घोषणा DW_IC_SLAVE		1

/*
 * Hardware पात codes from the DW_IC_TX_ABRT_SOURCE रेजिस्टर
 *
 * Only expected पात codes are listed here
 * refer to the datasheet क्रम the full list
 */
#घोषणा ABRT_7B_ADDR_NOACK	0
#घोषणा ABRT_10ADDR1_NOACK	1
#घोषणा ABRT_10ADDR2_NOACK	2
#घोषणा ABRT_TXDATA_NOACK	3
#घोषणा ABRT_GCALL_NOACK	4
#घोषणा ABRT_GCALL_READ		5
#घोषणा ABRT_SBYTE_ACKDET	7
#घोषणा ABRT_SBYTE_NORSTRT	9
#घोषणा ABRT_10B_RD_NORSTRT	10
#घोषणा ABRT_MASTER_DIS		11
#घोषणा ARB_LOST		12
#घोषणा ABRT_SLAVE_FLUSH_TXFIFO	13
#घोषणा ABRT_SLAVE_ARBLOST	14
#घोषणा ABRT_SLAVE_RD_INTX	15

#घोषणा DW_IC_TX_ABRT_7B_ADDR_NOACK		BIT(ABRT_7B_ADDR_NOACK)
#घोषणा DW_IC_TX_ABRT_10ADDR1_NOACK		BIT(ABRT_10ADDR1_NOACK)
#घोषणा DW_IC_TX_ABRT_10ADDR2_NOACK		BIT(ABRT_10ADDR2_NOACK)
#घोषणा DW_IC_TX_ABRT_TXDATA_NOACK		BIT(ABRT_TXDATA_NOACK)
#घोषणा DW_IC_TX_ABRT_GCALL_NOACK		BIT(ABRT_GCALL_NOACK)
#घोषणा DW_IC_TX_ABRT_GCALL_READ		BIT(ABRT_GCALL_READ)
#घोषणा DW_IC_TX_ABRT_SBYTE_ACKDET		BIT(ABRT_SBYTE_ACKDET)
#घोषणा DW_IC_TX_ABRT_SBYTE_NORSTRT		BIT(ABRT_SBYTE_NORSTRT)
#घोषणा DW_IC_TX_ABRT_10B_RD_NORSTRT		BIT(ABRT_10B_RD_NORSTRT)
#घोषणा DW_IC_TX_ABRT_MASTER_DIS		BIT(ABRT_MASTER_DIS)
#घोषणा DW_IC_TX_ARB_LOST			BIT(ARB_LOST)
#घोषणा DW_IC_RX_ABRT_SLAVE_RD_INTX		BIT(ABRT_SLAVE_RD_INTX)
#घोषणा DW_IC_RX_ABRT_SLAVE_ARBLOST		BIT(ABRT_SLAVE_ARBLOST)
#घोषणा DW_IC_RX_ABRT_SLAVE_FLUSH_TXFIFO	BIT(ABRT_SLAVE_FLUSH_TXFIFO)

#घोषणा DW_IC_TX_ABRT_NOACK		(DW_IC_TX_ABRT_7B_ADDR_NOACK | \
					 DW_IC_TX_ABRT_10ADDR1_NOACK | \
					 DW_IC_TX_ABRT_10ADDR2_NOACK | \
					 DW_IC_TX_ABRT_TXDATA_NOACK | \
					 DW_IC_TX_ABRT_GCALL_NOACK)

काष्ठा clk;
काष्ठा device;
काष्ठा reset_control;

/**
 * काष्ठा dw_i2c_dev - निजी i2c-designware data
 * @dev: driver model device node
 * @map: IO रेजिस्टरs map
 * @sysmap: System controller रेजिस्टरs map
 * @base: IO रेजिस्टरs poपूर्णांकer
 * @ext: Extended IO रेजिस्टरs poपूर्णांकer
 * @cmd_complete: tx completion indicator
 * @clk: input reference घड़ी
 * @pclk: घड़ी required to access the रेजिस्टरs
 * @slave: represent an I2C slave device
 * @cmd_err: run समय hadware error code
 * @msgs: poपूर्णांकs to an array of messages currently being transferred
 * @msgs_num: the number of elements in msgs
 * @msg_ग_लिखो_idx: the element index of the current tx message in the msgs
 *	array
 * @tx_buf_len: the length of the current tx buffer
 * @tx_buf: the current tx buffer
 * @msg_पढ़ो_idx: the element index of the current rx message in the msgs
 *	array
 * @rx_buf_len: the length of the current rx buffer
 * @rx_buf: the current rx buffer
 * @msg_err: error status of the current transfer
 * @status: i2c master status, one of STATUS_*
 * @पात_source: copy of the TX_ABRT_SOURCE रेजिस्टर
 * @irq: पूर्णांकerrupt number क्रम the i2c master
 * @adapter: i2c subप्रणाली adapter node
 * @slave_cfg: configuration क्रम the slave device
 * @tx_fअगरo_depth: depth of the hardware tx fअगरo
 * @rx_fअगरo_depth: depth of the hardware rx fअगरo
 * @rx_outstanding: current master-rx elements in tx fअगरo
 * @timings: bus घड़ी frequency, SDA hold and other timings
 * @sda_hold_समय: SDA hold value
 * @ss_hcnt: standard speed HCNT value
 * @ss_lcnt: standard speed LCNT value
 * @fs_hcnt: fast speed HCNT value
 * @fs_lcnt: fast speed LCNT value
 * @fp_hcnt: fast plus HCNT value
 * @fp_lcnt: fast plus LCNT value
 * @hs_hcnt: high speed HCNT value
 * @hs_lcnt: high speed LCNT value
 * @acquire_lock: function to acquire a hardware lock on the bus
 * @release_lock: function to release a hardware lock on the bus
 * @shared_with_punit: true अगर this bus is shared with the SoCs PUNIT
 * @disable: function to disable the controller
 * @disable_पूर्णांक: function to disable all पूर्णांकerrupts
 * @init: function to initialize the I2C hardware
 * @mode: operation mode - DW_IC_MASTER or DW_IC_SLAVE
 * @suspended: set to true अगर the controller is suspended
 *
 * HCNT and LCNT parameters can be used अगर the platक्रमm knows more accurate
 * values than the one computed based only on the input घड़ी frequency.
 * Leave them to be %0 अगर not used.
 */
काष्ठा dw_i2c_dev अणु
	काष्ठा device		*dev;
	काष्ठा regmap		*map;
	काष्ठा regmap		*sysmap;
	व्योम __iomem		*base;
	व्योम __iomem		*ext;
	काष्ठा completion	cmd_complete;
	काष्ठा clk		*clk;
	काष्ठा clk		*pclk;
	काष्ठा reset_control	*rst;
	काष्ठा i2c_client		*slave;
	u32			(*get_clk_rate_khz) (काष्ठा dw_i2c_dev *dev);
	पूर्णांक			cmd_err;
	काष्ठा i2c_msg		*msgs;
	पूर्णांक			msgs_num;
	पूर्णांक			msg_ग_लिखो_idx;
	u32			tx_buf_len;
	u8			*tx_buf;
	पूर्णांक			msg_पढ़ो_idx;
	u32			rx_buf_len;
	u8			*rx_buf;
	पूर्णांक			msg_err;
	अचिन्हित पूर्णांक		status;
	u32			पात_source;
	पूर्णांक			irq;
	u32			flags;
	काष्ठा i2c_adapter	adapter;
	u32			functionality;
	u32			master_cfg;
	u32			slave_cfg;
	अचिन्हित पूर्णांक		tx_fअगरo_depth;
	अचिन्हित पूर्णांक		rx_fअगरo_depth;
	पूर्णांक			rx_outstanding;
	काष्ठा i2c_timings	timings;
	u32			sda_hold_समय;
	u16			ss_hcnt;
	u16			ss_lcnt;
	u16			fs_hcnt;
	u16			fs_lcnt;
	u16			fp_hcnt;
	u16			fp_lcnt;
	u16			hs_hcnt;
	u16			hs_lcnt;
	पूर्णांक			(*acquire_lock)(व्योम);
	व्योम			(*release_lock)(व्योम);
	bool			shared_with_punit;
	व्योम			(*disable)(काष्ठा dw_i2c_dev *dev);
	व्योम			(*disable_पूर्णांक)(काष्ठा dw_i2c_dev *dev);
	पूर्णांक			(*init)(काष्ठा dw_i2c_dev *dev);
	पूर्णांक			(*set_sda_hold_समय)(काष्ठा dw_i2c_dev *dev);
	पूर्णांक			mode;
	काष्ठा i2c_bus_recovery_info rinfo;
	bool			suspended;
पूर्ण;

#घोषणा ACCESS_INTR_MASK	BIT(0)
#घोषणा ACCESS_NO_IRQ_SUSPEND	BIT(1)

#घोषणा MODEL_MSCC_OCELOT	BIT(8)
#घोषणा MODEL_BAIKAL_BT1	BIT(9)
#घोषणा MODEL_AMD_NAVI_GPU	BIT(10)
#घोषणा MODEL_MASK		GENMASK(11, 8)

/*
 * Enable UCSI पूर्णांकerrupt by writing 0xd at रेजिस्टर
 * offset 0x474 specअगरied in hardware specअगरication.
 */
#घोषणा AMD_UCSI_INTR_REG	0x474
#घोषणा AMD_UCSI_INTR_EN	0xd

पूर्णांक i2c_dw_init_regmap(काष्ठा dw_i2c_dev *dev);
u32 i2c_dw_scl_hcnt(u32 ic_clk, u32 tSYMBOL, u32 tf, पूर्णांक cond, पूर्णांक offset);
u32 i2c_dw_scl_lcnt(u32 ic_clk, u32 tLOW, u32 tf, पूर्णांक offset);
पूर्णांक i2c_dw_set_sda_hold(काष्ठा dw_i2c_dev *dev);
अचिन्हित दीर्घ i2c_dw_clk_rate(काष्ठा dw_i2c_dev *dev);
पूर्णांक i2c_dw_prepare_clk(काष्ठा dw_i2c_dev *dev, bool prepare);
पूर्णांक i2c_dw_acquire_lock(काष्ठा dw_i2c_dev *dev);
व्योम i2c_dw_release_lock(काष्ठा dw_i2c_dev *dev);
पूर्णांक i2c_dw_रुको_bus_not_busy(काष्ठा dw_i2c_dev *dev);
पूर्णांक i2c_dw_handle_tx_पात(काष्ठा dw_i2c_dev *dev);
पूर्णांक i2c_dw_set_fअगरo_size(काष्ठा dw_i2c_dev *dev);
u32 i2c_dw_func(काष्ठा i2c_adapter *adap);
व्योम i2c_dw_disable(काष्ठा dw_i2c_dev *dev);
व्योम i2c_dw_disable_पूर्णांक(काष्ठा dw_i2c_dev *dev);

अटल अंतरभूत व्योम __i2c_dw_enable(काष्ठा dw_i2c_dev *dev)
अणु
	regmap_ग_लिखो(dev->map, DW_IC_ENABLE, 1);
पूर्ण

अटल अंतरभूत व्योम __i2c_dw_disable_noरुको(काष्ठा dw_i2c_dev *dev)
अणु
	regmap_ग_लिखो(dev->map, DW_IC_ENABLE, 0);
पूर्ण

व्योम __i2c_dw_disable(काष्ठा dw_i2c_dev *dev);

बाह्य व्योम i2c_dw_configure_master(काष्ठा dw_i2c_dev *dev);
बाह्य पूर्णांक i2c_dw_probe_master(काष्ठा dw_i2c_dev *dev);

#अगर IS_ENABLED(CONFIG_I2C_DESIGNWARE_SLAVE)
बाह्य व्योम i2c_dw_configure_slave(काष्ठा dw_i2c_dev *dev);
बाह्य पूर्णांक i2c_dw_probe_slave(काष्ठा dw_i2c_dev *dev);
#अन्यथा
अटल अंतरभूत व्योम i2c_dw_configure_slave(काष्ठा dw_i2c_dev *dev) अणु पूर्ण
अटल अंतरभूत पूर्णांक i2c_dw_probe_slave(काष्ठा dw_i2c_dev *dev) अणु वापस -EINVAL; पूर्ण
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक i2c_dw_probe(काष्ठा dw_i2c_dev *dev)
अणु
	चयन (dev->mode) अणु
	हाल DW_IC_SLAVE:
		वापस i2c_dw_probe_slave(dev);
	हाल DW_IC_MASTER:
		वापस i2c_dw_probe_master(dev);
	शेष:
		dev_err(dev->dev, "Wrong operation mode: %d\n", dev->mode);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम i2c_dw_configure(काष्ठा dw_i2c_dev *dev)
अणु
	अगर (i2c_detect_slave_mode(dev->dev))
		i2c_dw_configure_slave(dev);
	अन्यथा
		i2c_dw_configure_master(dev);
पूर्ण

#अगर IS_ENABLED(CONFIG_I2C_DESIGNWARE_BAYTRAIL)
बाह्य पूर्णांक i2c_dw_probe_lock_support(काष्ठा dw_i2c_dev *dev);
#अन्यथा
अटल अंतरभूत पूर्णांक i2c_dw_probe_lock_support(काष्ठा dw_i2c_dev *dev) अणु वापस 0; पूर्ण
#पूर्ण_अगर

पूर्णांक i2c_dw_validate_speed(काष्ठा dw_i2c_dev *dev);
व्योम i2c_dw_adjust_bus_speed(काष्ठा dw_i2c_dev *dev);

#अगर IS_ENABLED(CONFIG_ACPI)
पूर्णांक i2c_dw_acpi_configure(काष्ठा device *device);
#अन्यथा
अटल अंतरभूत पूर्णांक i2c_dw_acpi_configure(काष्ठा device *device) अणु वापस -ENODEV; पूर्ण
#पूर्ण_अगर
