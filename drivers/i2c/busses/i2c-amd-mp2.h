<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * AMD MP2 I2C adapter driver
 *
 * Authors: Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 *          Elie Morisse <syniurge@gmail.com>
 */

#अगर_अघोषित I2C_AMD_PCI_MP2_H
#घोषणा I2C_AMD_PCI_MP2_H

#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>
#समावेश <linux/pm_runसमय.स>

#घोषणा PCI_DEVICE_ID_AMD_MP2	0x15E6

काष्ठा amd_i2c_common;
काष्ठा amd_mp2_dev;

क्रमागत अणु
	/* MP2 C2P Message Registers */
	AMD_C2P_MSG0 = 0x10500,			/* MP2 Message क्रम I2C0 */
	AMD_C2P_MSG1 = 0x10504,			/* MP2 Message क्रम I2C1 */
	AMD_C2P_MSG2 = 0x10508,			/* DRAM Address Lo / Data 0 */
	AMD_C2P_MSG3 = 0x1050c,			/* DRAM Address HI / Data 1 */
	AMD_C2P_MSG4 = 0x10510,			/* Data 2 */
	AMD_C2P_MSG5 = 0x10514,			/* Data 3 */
	AMD_C2P_MSG6 = 0x10518,			/* Data 4 */
	AMD_C2P_MSG7 = 0x1051c,			/* Data 5 */
	AMD_C2P_MSG8 = 0x10520,			/* Data 6 */
	AMD_C2P_MSG9 = 0x10524,			/* Data 7 */

	/* MP2 P2C Message Registers */
	AMD_P2C_MSG0 = 0x10680,			/* Do not use */
	AMD_P2C_MSG1 = 0x10684,			/* I2C0 पूर्णांकerrupt रेजिस्टर */
	AMD_P2C_MSG2 = 0x10688,			/* I2C1 पूर्णांकerrupt रेजिस्टर */
	AMD_P2C_MSG3 = 0x1068C,			/* MP2 debug info */
	AMD_P2C_MSG_INTEN = 0x10690,		/* MP2 पूर्णांकerrupt gen रेजिस्टर */
	AMD_P2C_MSG_INTSTS = 0x10694,		/* Interrupt status */
पूर्ण;

/* Command रेजिस्टर data काष्ठाures */

#घोषणा i2c_none (-1)
क्रमागत i2c_cmd अणु
	i2c_पढ़ो = 0,
	i2c_ग_लिखो,
	i2c_enable,
	i2c_disable,
	number_of_sensor_discovered,
	is_mp2_active,
	invalid_cmd = 0xF,
पूर्ण;

क्रमागत speed_क्रमागत अणु
	speed100k = 0,
	speed400k = 1,
	speed1000k = 2,
	speed1400k = 3,
	speed3400k = 4
पूर्ण;

क्रमागत mem_type अणु
	use_dram = 0,
	use_c2pmsg = 1,
पूर्ण;

/**
 * जोड़ i2c_cmd_base : bit access of C2P commands
 * @i2c_cmd: bit 0..3 i2c R/W command
 * @bus_id: bit 4..7 i2c bus index
 * @slave_addr: bit 8..15 slave address
 * @length: bit 16..27 पढ़ो/ग_लिखो length
 * @i2c_speed: bit 28..30 bus speed
 * @mem_type: bit 31 0-DRAM; 1-C2P msg o/p
 */
जोड़ i2c_cmd_base अणु
	u32 ul;
	काष्ठा अणु
		क्रमागत i2c_cmd i2c_cmd : 4;
		u8 bus_id : 4;
		u32 slave_addr : 8;
		u32 length : 12;
		क्रमागत speed_क्रमागत i2c_speed : 3;
		क्रमागत mem_type mem_type : 1;
	पूर्ण s;
पूर्ण;

क्रमागत response_type अणु
	invalid_response = 0,
	command_success = 1,
	command_failed = 2,
पूर्ण;

क्रमागत status_type अणु
	i2c_पढ़ोcomplete_event = 0,
	i2c_पढ़ोfail_event = 1,
	i2c_ग_लिखोcomplete_event = 2,
	i2c_ग_लिखोfail_event = 3,
	i2c_busenable_complete = 4,
	i2c_busenable_failed = 5,
	i2c_busdisable_complete = 6,
	i2c_busdisable_failed = 7,
	invalid_data_length = 8,
	invalid_slave_address = 9,
	invalid_i2cbus_id = 10,
	invalid_dram_addr = 11,
	invalid_command = 12,
	mp2_active = 13,
	numberof_sensors_discovered_resp = 14,
	i2c_bus_notinitialized
पूर्ण;

/**
 * जोड़ i2c_event : bit access of P2C events
 * @response: bit 0..1 i2c response type
 * @status: bit 2..6 status_type
 * @mem_type: bit 7 0-DRAM; 1-C2P msg o/p
 * @bus_id: bit 8..11 i2c bus id
 * @length: bit 12..23 message length
 * @slave_addr: bit 24-31 slave address
 */
जोड़ i2c_event अणु
	u32 ul;
	काष्ठा अणु
		क्रमागत response_type response : 2;
		क्रमागत status_type status : 5;
		क्रमागत mem_type mem_type : 1;
		u8 bus_id : 4;
		u32 length : 12;
		u32 slave_addr : 8;
	पूर्ण r;
पूर्ण;

/**
 * काष्ठा amd_i2c_common - per bus/i2c adapter context, shared
 *	between the pci and the platक्रमm driver
 * @eventval: MP2 event value set by the IRQ handler
 * @mp2_dev: MP2 pci device this adapter is part of
 * @msg: i2c message
 * @cmd_completion: function called by the IRQ handler to संकेत
 *		    the platक्रमm driver
 * @reqcmd: requested i2c command type
 * @cmd_success: set to true अगर the MP2 responded to a command with
 *		 the expected status and response type
 * @bus_id: bus index
 * @i2c_speed: i2c bus speed determined by the slowest slave
 * @dma_buf: अगर msg length > 32, holds the DMA buffer भव address
 * @dma_addr: अगर msg length > 32, holds the DMA buffer address
 */
काष्ठा amd_i2c_common अणु
	जोड़ i2c_event eventval;
	काष्ठा amd_mp2_dev *mp2_dev;
	काष्ठा i2c_msg *msg;
	व्योम (*cmd_completion)(काष्ठा amd_i2c_common *i2c_common);
	क्रमागत i2c_cmd reqcmd;
	u8 cmd_success;
	u8 bus_id;
	क्रमागत speed_क्रमागत i2c_speed;
	u8 *dma_buf;
	dma_addr_t dma_addr;
#अगर_घोषित CONFIG_PM
	पूर्णांक (*suspend)(काष्ठा amd_i2c_common *i2c_common);
	पूर्णांक (*resume)(काष्ठा amd_i2c_common *i2c_common);
#पूर्ण_अगर /* CONFIG_PM */
पूर्ण;

/**
 * काष्ठा amd_mp2_dev - per PCI device context
 * @pci_dev: PCI driver node
 * @busses: MP2 devices may have up to two busses,
 *	    each bus corresponding to an i2c adapter
 * @mmio: iommapped रेजिस्टरs
 * @c2p_lock: controls access to the C2P mailbox shared between
 *	      the two adapters
 * @c2p_lock_busid: id of the adapter which locked c2p_lock
 */
काष्ठा amd_mp2_dev अणु
	काष्ठा pci_dev *pci_dev;
	काष्ठा amd_i2c_common *busses[2];
	व्योम __iomem *mmio;
	काष्ठा mutex c2p_lock;
	u8 c2p_lock_busid;
	अचिन्हित पूर्णांक probed;
पूर्ण;

/* PCIe communication driver */

पूर्णांक amd_mp2_rw(काष्ठा amd_i2c_common *i2c_common, क्रमागत i2c_cmd reqcmd);
पूर्णांक amd_mp2_bus_enable_set(काष्ठा amd_i2c_common *i2c_common, bool enable);

व्योम amd_mp2_process_event(काष्ठा amd_i2c_common *i2c_common);

व्योम amd_mp2_rw_समयout(काष्ठा amd_i2c_common *i2c_common);

पूर्णांक amd_mp2_रेजिस्टर_cb(काष्ठा amd_i2c_common *i2c_common);
पूर्णांक amd_mp2_unरेजिस्टर_cb(काष्ठा amd_i2c_common *i2c_common);

काष्ठा amd_mp2_dev *amd_mp2_find_device(व्योम);

अटल अंतरभूत व्योम amd_mp2_pm_runसमय_get(काष्ठा amd_mp2_dev *mp2_dev)
अणु
	pm_runसमय_get_sync(&mp2_dev->pci_dev->dev);
पूर्ण

अटल अंतरभूत व्योम amd_mp2_pm_runसमय_put(काष्ठा amd_mp2_dev *mp2_dev)
अणु
	pm_runसमय_mark_last_busy(&mp2_dev->pci_dev->dev);
	pm_runसमय_put_स्वतःsuspend(&mp2_dev->pci_dev->dev);
पूर्ण

#पूर्ण_अगर
