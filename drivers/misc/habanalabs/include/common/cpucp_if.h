<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित CPUCP_IF_H
#घोषणा CPUCP_IF_H

#समावेश <linux/types.h>
#समावेश <linux/अगर_ether.h>

#समावेश "hl_boot_if.h"

#घोषणा NUM_HBM_PSEUDO_CH				2
#घोषणा NUM_HBM_CH_PER_DEV				8
#घोषणा CPUCP_PKT_HBM_ECC_INFO_WR_PAR_SHIFT		0
#घोषणा CPUCP_PKT_HBM_ECC_INFO_WR_PAR_MASK		0x00000001
#घोषणा CPUCP_PKT_HBM_ECC_INFO_RD_PAR_SHIFT		1
#घोषणा CPUCP_PKT_HBM_ECC_INFO_RD_PAR_MASK		0x00000002
#घोषणा CPUCP_PKT_HBM_ECC_INFO_CA_PAR_SHIFT		2
#घोषणा CPUCP_PKT_HBM_ECC_INFO_CA_PAR_MASK		0x00000004
#घोषणा CPUCP_PKT_HBM_ECC_INFO_DERR_SHIFT		3
#घोषणा CPUCP_PKT_HBM_ECC_INFO_DERR_MASK		0x00000008
#घोषणा CPUCP_PKT_HBM_ECC_INFO_SERR_SHIFT		4
#घोषणा CPUCP_PKT_HBM_ECC_INFO_SERR_MASK		0x00000010
#घोषणा CPUCP_PKT_HBM_ECC_INFO_TYPE_SHIFT		5
#घोषणा CPUCP_PKT_HBM_ECC_INFO_TYPE_MASK		0x00000020
#घोषणा CPUCP_PKT_HBM_ECC_INFO_HBM_CH_SHIFT		6
#घोषणा CPUCP_PKT_HBM_ECC_INFO_HBM_CH_MASK		0x000007C0

#घोषणा PLL_MAP_MAX_BITS	128
#घोषणा PLL_MAP_LEN		(PLL_MAP_MAX_BITS / 8)

/*
 * info of the pkt queue poपूर्णांकers in the first async occurrence
 */
काष्ठा cpucp_pkt_sync_err अणु
	__le32 pi;
	__le32 ci;
पूर्ण;

काष्ठा hl_eq_hbm_ecc_data अणु
	/* SERR counter */
	__le32 sec_cnt;
	/* DERR counter */
	__le32 dec_cnt;
	/* Supplemental Inक्रमmation according to the mask bits */
	__le32 hbm_ecc_info;
	/* Address in hbm where the ecc happened */
	__le32 first_addr;
	/* SERR continuous address counter */
	__le32 sec_cont_cnt;
	__le32 pad;
पूर्ण;

/*
 * EVENT QUEUE
 */

काष्ठा hl_eq_header अणु
	__le32 reserved;
	__le32 ctl;
पूर्ण;

काष्ठा hl_eq_ecc_data अणु
	__le64 ecc_address;
	__le64 ecc_syndrom;
	__u8 memory_wrapper_idx;
	__u8 pad[7];
पूर्ण;

क्रमागत hl_sm_sei_cause अणु
	SM_SEI_SO_OVERFLOW,
	SM_SEI_LBW_4B_UNALIGNED,
	SM_SEI_AXI_RESPONSE_ERR
पूर्ण;

काष्ठा hl_eq_sm_sei_data अणु
	__le32 sei_log;
	/* क्रमागत hl_sm_sei_cause */
	__u8 sei_cause;
	__u8 pad[3];
पूर्ण;

काष्ठा hl_eq_entry अणु
	काष्ठा hl_eq_header hdr;
	जोड़ अणु
		काष्ठा hl_eq_ecc_data ecc_data;
		काष्ठा hl_eq_hbm_ecc_data hbm_ecc_data;
		काष्ठा hl_eq_sm_sei_data sm_sei_data;
		काष्ठा cpucp_pkt_sync_err pkt_sync_err;
		__le64 data[7];
	पूर्ण;
पूर्ण;

#घोषणा HL_EQ_ENTRY_SIZE		माप(काष्ठा hl_eq_entry)

#घोषणा EQ_CTL_READY_SHIFT		31
#घोषणा EQ_CTL_READY_MASK		0x80000000

#घोषणा EQ_CTL_EVENT_TYPE_SHIFT		16
#घोषणा EQ_CTL_EVENT_TYPE_MASK		0x03FF0000

क्रमागत pq_init_status अणु
	PQ_INIT_STATUS_NA = 0,
	PQ_INIT_STATUS_READY_FOR_CP,
	PQ_INIT_STATUS_READY_FOR_HOST,
	PQ_INIT_STATUS_READY_FOR_CP_SINGLE_MSI
पूर्ण;

/*
 * CpuCP Primary Queue Packets
 *
 * During normal operation, the host's kernel driver needs to send various
 * messages to CpuCP, usually either to SET some value पूर्णांकo a H/W periphery or
 * to GET the current value of some H/W periphery. For example, SET the
 * frequency of MME/TPC and GET the value of the thermal sensor.
 *
 * These messages can be initiated either by the User application or by the
 * host's driver itself, e.g. घातer management code. In either हाल, the
 * communication from the host's driver to CpuCP will *always* be in
 * synchronous mode, meaning that the host will send a single message and poll
 * until the message was acknowledged and the results are पढ़ोy (अगर results are
 * needed).
 *
 * This means that only a single message can be sent at a समय and the host's
 * driver must रुको क्रम its result beक्रमe sending the next message. Having said
 * that, because these are control messages which are sent in a relatively low
 * frequency, this limitation seems acceptable. It's important to note that
 * in हाल of multiple devices, messages to dअगरferent devices *can* be sent
 * at the same समय.
 *
 * The message, inमाला_दो/outमाला_दो (अगर relevant) and fence object will be located
 * on the device DDR at an address that will be determined by the host's driver.
 * During device initialization phase, the host will pass to CpuCP that address.
 * Most of the message types will contain inमाला_दो/outमाला_दो inside the message
 * itself. The common part of each message will contain the opcode of the
 * message (its type) and a field representing a fence object.
 *
 * When the host's driver wishes to send a message to CPU CP, it will ग_लिखो the
 * message contents to the device DDR, clear the fence object and then ग_लिखो to
 * the PSOC_ARC1_AUX_SW_INTR, to issue पूर्णांकerrupt 121 to ARC Management CPU.
 *
 * Upon receiving the पूर्णांकerrupt (#121), CpuCP will पढ़ो the message from the
 * DDR. In हाल the message is a SET operation, CpuCP will first perक्रमm the
 * operation and then ग_लिखो to the fence object on the device DDR. In हाल the
 * message is a GET operation, CpuCP will first fill the results section on the
 * device DDR and then ग_लिखो to the fence object. If an error occurred, CpuCP
 * will fill the rc field with the right error code.
 *
 * In the meanसमय, the host's driver will poll on the fence object. Once the
 * host sees that the fence object is संकेतed, it will पढ़ो the results from
 * the device DDR (अगर relevant) and resume the code execution in the host's
 * driver.
 *
 * To use QMAN packets, the opcode must be the QMAN opcode, shअगरted by 8
 * so the value being put by the host's driver matches the value पढ़ो by CpuCP
 *
 * Non-QMAN packets should be limited to values 1 through (2^8 - 1)
 *
 * Detailed description:
 *
 * CPUCP_PACKET_DISABLE_PCI_ACCESS -
 *       After receiving this packet the embedded CPU must NOT issue PCI
 *       transactions (पढ़ो/ग_लिखो) towards the Host CPU. This also include
 *       sending MSI-X पूर्णांकerrupts.
 *       This packet is usually sent beक्रमe the device is moved to D3Hot state.
 *
 * CPUCP_PACKET_ENABLE_PCI_ACCESS -
 *       After receiving this packet the embedded CPU is allowed to issue PCI
 *       transactions towards the Host CPU, including sending MSI-X पूर्णांकerrupts.
 *       This packet is usually send after the device is moved to D0 state.
 *
 * CPUCP_PACKET_TEMPERATURE_GET -
 *       Fetch the current temperature / Max / Max Hyst / Critical /
 *       Critical Hyst of a specअगरied thermal sensor. The packet's
 *       arguments specअगरy the desired sensor and the field to get.
 *
 * CPUCP_PACKET_VOLTAGE_GET -
 *       Fetch the voltage / Max / Min of a specअगरied sensor. The packet's
 *       arguments specअगरy the sensor and type.
 *
 * CPUCP_PACKET_CURRENT_GET -
 *       Fetch the current / Max / Min of a specअगरied sensor. The packet's
 *       arguments specअगरy the sensor and type.
 *
 * CPUCP_PACKET_FAN_SPEED_GET -
 *       Fetch the speed / Max / Min of a specअगरied fan. The packet's
 *       arguments specअगरy the sensor and type.
 *
 * CPUCP_PACKET_PWM_GET -
 *       Fetch the pwm value / mode of a specअगरied pwm. The packet's
 *       arguments specअगरy the sensor and type.
 *
 * CPUCP_PACKET_PWM_SET -
 *       Set the pwm value / mode of a specअगरied pwm. The packet's
 *       arguments specअगरy the sensor, type and value.
 *
 * CPUCP_PACKET_FREQUENCY_SET -
 *       Set the frequency of a specअगरied PLL. The packet's arguments specअगरy
 *       the PLL and the desired frequency. The actual frequency in the device
 *       might dअगरfer from the requested frequency.
 *
 * CPUCP_PACKET_FREQUENCY_GET -
 *       Fetch the frequency of a specअगरied PLL. The packet's arguments specअगरy
 *       the PLL.
 *
 * CPUCP_PACKET_LED_SET -
 *       Set the state of a specअगरied led. The packet's arguments
 *       specअगरy the led and the desired state.
 *
 * CPUCP_PACKET_I2C_WR -
 *       Write 32-bit value to I2C device. The packet's arguments specअगरy the
 *       I2C bus, address and value.
 *
 * CPUCP_PACKET_I2C_RD -
 *       Read 32-bit value from I2C device. The packet's arguments specअगरy the
 *       I2C bus and address.
 *
 * CPUCP_PACKET_INFO_GET -
 *       Fetch inक्रमmation from the device as specअगरied in the packet's
 *       काष्ठाure. The host's driver passes the max size it allows the CpuCP to
 *       ग_लिखो to the काष्ठाure, to prevent data corruption in हाल of
 *       mismatched driver/FW versions.
 *
 * CPUCP_PACKET_FLASH_PROGRAM_REMOVED - this packet was हटाओd
 *
 * CPUCP_PACKET_UNMASK_RAZWI_IRQ -
 *       Unmask the given IRQ. The IRQ number is specअगरied in the value field.
 *       The packet is sent after receiving an पूर्णांकerrupt and prपूर्णांकing its
 *       relevant inक्रमmation.
 *
 * CPUCP_PACKET_UNMASK_RAZWI_IRQ_ARRAY -
 *       Unmask the given IRQs. The IRQs numbers are specअगरied in an array right
 *       after the cpucp_packet काष्ठाure, where its first element is the array
 *       length. The packet is sent after a soft reset was करोne in order to
 *       handle any पूर्णांकerrupts that were sent during the reset process.
 *
 * CPUCP_PACKET_TEST -
 *       Test packet क्रम CpuCP connectivity. The CPU will put the fence value
 *       in the result field.
 *
 * CPUCP_PACKET_FREQUENCY_CURR_GET -
 *       Fetch the current frequency of a specअगरied PLL. The packet's arguments
 *       specअगरy the PLL.
 *
 * CPUCP_PACKET_MAX_POWER_GET -
 *       Fetch the maximal घातer of the device.
 *
 * CPUCP_PACKET_MAX_POWER_SET -
 *       Set the maximal घातer of the device. The packet's arguments specअगरy
 *       the घातer.
 *
 * CPUCP_PACKET_EEPROM_DATA_GET -
 *       Get EEPROM data from the CpuCP kernel. The buffer is specअगरied in the
 *       addr field. The CPU will put the वापसed data size in the result
 *       field. In addition, the host's driver passes the max size it allows the
 *       CpuCP to ग_लिखो to the काष्ठाure, to prevent data corruption in हाल of
 *       mismatched driver/FW versions.
 *
 * CPUCP_PACKET_NIC_INFO_GET -
 *       Fetch inक्रमmation from the device regarding the NIC. the host's driver
 *       passes the max size it allows the CpuCP to ग_लिखो to the काष्ठाure, to
 *       prevent data corruption in हाल of mismatched driver/FW versions.
 *
 * CPUCP_PACKET_TEMPERATURE_SET -
 *       Set the value of the offset property of a specअगरied thermal sensor.
 *       The packet's arguments specअगरy the desired sensor and the field to
 *       set.
 *
 * CPUCP_PACKET_VOLTAGE_SET -
 *       Trigger the reset_history property of a specअगरied voltage sensor.
 *       The packet's arguments specअगरy the desired sensor and the field to
 *       set.
 *
 * CPUCP_PACKET_CURRENT_SET -
 *       Trigger the reset_history property of a specअगरied current sensor.
 *       The packet's arguments specअगरy the desired sensor and the field to
 *       set.
 *
 * CPUCP_PACKET_PCIE_THROUGHPUT_GET
 *       Get throughput of PCIe.
 *       The packet's arguments specअगरy the transaction direction (TX/RX).
 *       The winकरोw measurement is 10[msec], and the वापस value is in KB/sec.
 *
 * CPUCP_PACKET_PCIE_REPLAY_CNT_GET
 *       Replay count measures number of "replay" events, which is basicly
 *       number of retries करोne by PCIe.
 *
 * CPUCP_PACKET_TOTAL_ENERGY_GET
 *       Total Energy is measurement of energy from the समय FW Linux
 *       is loaded. It is calculated by multiplying the average घातer
 *       by समय (passed from armcp start). The units are in MilliJouls.
 *
 * CPUCP_PACKET_PLL_INFO_GET
 *       Fetch frequencies of PLL from the required PLL IP.
 *       The packet's arguments specअगरy the device PLL type
 *       Pll type is the PLL from device pll_index क्रमागत.
 *       The result is composed of 4 outमाला_दो, each is 16-bit
 *       frequency in MHz.
 *
 * CPUCP_PACKET_POWER_GET
 *       Fetch the present घातer consumption of the device (Current * Voltage).
 *
 * CPUCP_PACKET_NIC_PFC_SET -
 *       Enable/Disable the NIC PFC feature. The packet's arguments specअगरy the
 *       NIC port, relevant lanes to configure and one bit indication क्रम
 *       enable/disable.
 *
 * CPUCP_PACKET_NIC_FAULT_GET -
 *       Fetch the current indication क्रम local/remote faults from the NIC MAC.
 *       The result is 32-bit value of the relevant रेजिस्टर.
 *
 * CPUCP_PACKET_NIC_LPBK_SET -
 *       Enable/Disable the MAC loopback feature. The packet's arguments specअगरy
 *       the NIC port, relevant lanes to configure and one bit indication क्रम
 *       enable/disable.
 *
 * CPUCP_PACKET_NIC_MAC_INIT -
 *       Configure the NIC MAC channels. The packet's arguments specअगरy the
 *       NIC port and the speed.
 *
 * CPUCP_PACKET_MSI_INFO_SET -
 *       set the index number क्रम each supported msi type going from
 *       host to device
 */

क्रमागत cpucp_packet_id अणु
	CPUCP_PACKET_DISABLE_PCI_ACCESS = 1,	/* पूर्णांकernal */
	CPUCP_PACKET_ENABLE_PCI_ACCESS,		/* पूर्णांकernal */
	CPUCP_PACKET_TEMPERATURE_GET,		/* sysfs */
	CPUCP_PACKET_VOLTAGE_GET,		/* sysfs */
	CPUCP_PACKET_CURRENT_GET,		/* sysfs */
	CPUCP_PACKET_FAN_SPEED_GET,		/* sysfs */
	CPUCP_PACKET_PWM_GET,			/* sysfs */
	CPUCP_PACKET_PWM_SET,			/* sysfs */
	CPUCP_PACKET_FREQUENCY_SET,		/* sysfs */
	CPUCP_PACKET_FREQUENCY_GET,		/* sysfs */
	CPUCP_PACKET_LED_SET,			/* debugfs */
	CPUCP_PACKET_I2C_WR,			/* debugfs */
	CPUCP_PACKET_I2C_RD,			/* debugfs */
	CPUCP_PACKET_INFO_GET,			/* IOCTL */
	CPUCP_PACKET_FLASH_PROGRAM_REMOVED,
	CPUCP_PACKET_UNMASK_RAZWI_IRQ,		/* पूर्णांकernal */
	CPUCP_PACKET_UNMASK_RAZWI_IRQ_ARRAY,	/* पूर्णांकernal */
	CPUCP_PACKET_TEST,			/* पूर्णांकernal */
	CPUCP_PACKET_FREQUENCY_CURR_GET,	/* sysfs */
	CPUCP_PACKET_MAX_POWER_GET,		/* sysfs */
	CPUCP_PACKET_MAX_POWER_SET,		/* sysfs */
	CPUCP_PACKET_EEPROM_DATA_GET,		/* sysfs */
	CPUCP_PACKET_NIC_INFO_GET,		/* पूर्णांकernal */
	CPUCP_PACKET_TEMPERATURE_SET,		/* sysfs */
	CPUCP_PACKET_VOLTAGE_SET,		/* sysfs */
	CPUCP_PACKET_CURRENT_SET,		/* sysfs */
	CPUCP_PACKET_PCIE_THROUGHPUT_GET,	/* पूर्णांकernal */
	CPUCP_PACKET_PCIE_REPLAY_CNT_GET,	/* पूर्णांकernal */
	CPUCP_PACKET_TOTAL_ENERGY_GET,		/* पूर्णांकernal */
	CPUCP_PACKET_PLL_INFO_GET,		/* पूर्णांकernal */
	CPUCP_PACKET_NIC_STATUS,		/* पूर्णांकernal */
	CPUCP_PACKET_POWER_GET,			/* पूर्णांकernal */
	CPUCP_PACKET_NIC_PFC_SET,		/* पूर्णांकernal */
	CPUCP_PACKET_NIC_FAULT_GET,		/* पूर्णांकernal */
	CPUCP_PACKET_NIC_LPBK_SET,		/* पूर्णांकernal */
	CPUCP_PACKET_NIC_MAC_CFG,		/* पूर्णांकernal */
	CPUCP_PACKET_MSI_INFO_SET,		/* पूर्णांकernal */
पूर्ण;

#घोषणा CPUCP_PACKET_FENCE_VAL	0xFE8CE7A5

#घोषणा CPUCP_PKT_CTL_RC_SHIFT		12
#घोषणा CPUCP_PKT_CTL_RC_MASK		0x0000F000

#घोषणा CPUCP_PKT_CTL_OPCODE_SHIFT	16
#घोषणा CPUCP_PKT_CTL_OPCODE_MASK	0x1FFF0000

#घोषणा CPUCP_PKT_RES_PLL_OUT0_SHIFT	0
#घोषणा CPUCP_PKT_RES_PLL_OUT0_MASK	0x000000000000FFFFull
#घोषणा CPUCP_PKT_RES_PLL_OUT1_SHIFT	16
#घोषणा CPUCP_PKT_RES_PLL_OUT1_MASK	0x00000000FFFF0000ull
#घोषणा CPUCP_PKT_RES_PLL_OUT2_SHIFT	32
#घोषणा CPUCP_PKT_RES_PLL_OUT2_MASK	0x0000FFFF00000000ull
#घोषणा CPUCP_PKT_RES_PLL_OUT3_SHIFT	48
#घोषणा CPUCP_PKT_RES_PLL_OUT3_MASK	0xFFFF000000000000ull

काष्ठा cpucp_packet अणु
	जोड़ अणु
		__le64 value;	/* For SET packets */
		__le64 result;	/* For GET packets */
		__le64 addr;	/* For PQ */
	पूर्ण;

	__le32 ctl;

	__le32 fence;		/* Signal to host that message is completed */

	जोड़ अणु
		काष्ठा अणु/* For temperature/current/voltage/fan/pwm get/set */
			__le16 sensor_index;
			__le16 type;
		पूर्ण;

		काष्ठा अणु	/* For I2C पढ़ो/ग_लिखो */
			__u8 i2c_bus;
			__u8 i2c_addr;
			__u8 i2c_reg;
			__u8 pad; /* unused */
		पूर्ण;

		काष्ठा अणु/* For PLL info fetch */
			__le16 pll_type;
			/* TODO pll_reg is kept temporary beक्रमe removal */
			__le16 pll_reg;
		पूर्ण;

		/* For any general request */
		__le32 index;

		/* For frequency get/set */
		__le32 pll_index;

		/* For led set */
		__le32 led_index;

		/* For get CpuCP info/EEPROM data/NIC info */
		__le32 data_max_size;
	पूर्ण;

	__le32 reserved;
पूर्ण;

काष्ठा cpucp_unmask_irq_arr_packet अणु
	काष्ठा cpucp_packet cpucp_pkt;
	__le32 length;
	__le32 irqs[0];
पूर्ण;

काष्ठा cpucp_array_data_packet अणु
	काष्ठा cpucp_packet cpucp_pkt;
	__le32 length;
	__le32 data[0];
पूर्ण;

क्रमागत cpucp_packet_rc अणु
	cpucp_packet_success,
	cpucp_packet_invalid,
	cpucp_packet_fault
पूर्ण;

/*
 * cpucp_temp_type should adhere to hwmon_temp_attributes
 * defined in Linux kernel hwmon.h file
 */
क्रमागत cpucp_temp_type अणु
	cpucp_temp_input,
	cpucp_temp_max = 6,
	cpucp_temp_max_hyst,
	cpucp_temp_crit,
	cpucp_temp_crit_hyst,
	cpucp_temp_offset = 19,
	cpucp_temp_highest = 22,
	cpucp_temp_reset_history = 23
पूर्ण;

क्रमागत cpucp_in_attributes अणु
	cpucp_in_input,
	cpucp_in_min,
	cpucp_in_max,
	cpucp_in_highest = 7,
	cpucp_in_reset_history
पूर्ण;

क्रमागत cpucp_curr_attributes अणु
	cpucp_curr_input,
	cpucp_curr_min,
	cpucp_curr_max,
	cpucp_curr_highest = 7,
	cpucp_curr_reset_history
पूर्ण;

क्रमागत cpucp_fan_attributes अणु
	cpucp_fan_input,
	cpucp_fan_min = 2,
	cpucp_fan_max
पूर्ण;

क्रमागत cpucp_pwm_attributes अणु
	cpucp_pwm_input,
	cpucp_pwm_enable
पूर्ण;

क्रमागत cpucp_pcie_throughput_attributes अणु
	cpucp_pcie_throughput_tx,
	cpucp_pcie_throughput_rx
पूर्ण;

/* TODO temporary kept beक्रमe removal */
क्रमागत cpucp_pll_reg_attributes अणु
	cpucp_pll_nr_reg,
	cpucp_pll_nf_reg,
	cpucp_pll_od_reg,
	cpucp_pll_भाग_factor_reg,
	cpucp_pll_भाग_sel_reg
पूर्ण;

/* TODO temporary kept beक्रमe removal */
क्रमागत cpucp_pll_type_attributes अणु
	cpucp_pll_cpu,
	cpucp_pll_pci,
पूर्ण;

/*
 * MSI type क्रमागतeration table क्रम all ASICs and future SW versions.
 * For future ASIC-LKD compatibility, we can only add new क्रमागतerations.
 * at the end of the table (beक्रमe CPUCP_NUM_OF_MSI_TYPES).
 * Changing the order of entries or removing entries is not allowed.
 */
क्रमागत cpucp_msi_type अणु
	CPUCP_EVENT_QUEUE_MSI_TYPE,
	CPUCP_NIC_PORT1_MSI_TYPE,
	CPUCP_NIC_PORT3_MSI_TYPE,
	CPUCP_NIC_PORT5_MSI_TYPE,
	CPUCP_NIC_PORT7_MSI_TYPE,
	CPUCP_NIC_PORT9_MSI_TYPE,
	CPUCP_NUM_OF_MSI_TYPES
पूर्ण;

/*
 * PLL क्रमागतeration table used क्रम all ASICs and future SW versions.
 * For future ASIC-LKD compatibility, we can only add new क्रमागतerations.
 * at the end of the table.
 * Changing the order of entries or removing entries is not allowed.
 */
क्रमागत pll_index अणु
	CPU_PLL = 0,
	PCI_PLL = 1,
	NIC_PLL = 2,
	DMA_PLL = 3,
	MESH_PLL = 4,
	MME_PLL = 5,
	TPC_PLL = 6,
	IF_PLL = 7,
	SRAM_PLL = 8,
	NS_PLL = 9,
	HBM_PLL = 10,
	MSS_PLL = 11,
	DDR_PLL = 12,
	VID_PLL = 13,
	BANK_PLL = 14,
	MMU_PLL = 15,
	IC_PLL = 16,
	MC_PLL = 17,
	EMMC_PLL = 18,
	PLL_MAX
पूर्ण;

/* Event Queue Packets */

काष्ठा eq_generic_event अणु
	__le64 data[7];
पूर्ण;

/*
 * CpuCP info
 */

#घोषणा CARD_NAME_MAX_LEN		16
#घोषणा CPUCP_MAX_SENSORS		128
#घोषणा CPUCP_MAX_NICS			128
#घोषणा CPUCP_LANES_PER_NIC		4
#घोषणा CPUCP_NIC_QSFP_EEPROM_MAX_LEN	1024
#घोषणा CPUCP_MAX_NIC_LANES		(CPUCP_MAX_NICS * CPUCP_LANES_PER_NIC)
#घोषणा CPUCP_NIC_MASK_ARR_LEN		((CPUCP_MAX_NICS + 63) / 64)
#घोषणा CPUCP_NIC_POLARITY_ARR_LEN	((CPUCP_MAX_NIC_LANES + 63) / 64)

काष्ठा cpucp_sensor अणु
	__le32 type;
	__le32 flags;
पूर्ण;

/**
 * काष्ठा cpucp_card_types - ASIC card type.
 * @cpucp_card_type_pci: PCI card.
 * @cpucp_card_type_pmc: PCI Mezzanine Card.
 */
क्रमागत cpucp_card_types अणु
	cpucp_card_type_pci,
	cpucp_card_type_pmc
पूर्ण;

#घोषणा CPUCP_SEC_CONF_ENABLED_SHIFT	0
#घोषणा CPUCP_SEC_CONF_ENABLED_MASK	0x00000001

#घोषणा CPUCP_SEC_CONF_FLASH_WP_SHIFT	1
#घोषणा CPUCP_SEC_CONF_FLASH_WP_MASK	0x00000002

#घोषणा CPUCP_SEC_CONF_EEPROM_WP_SHIFT	2
#घोषणा CPUCP_SEC_CONF_EEPROM_WP_MASK	0x00000004

/**
 * काष्ठा cpucp_security_info - Security inक्रमmation.
 * @config: configuration bit field
 * @keys_num: number of stored keys
 * @revoked_keys: revoked keys bit field
 * @min_svn: minimal security version
 */
काष्ठा cpucp_security_info अणु
	__u8 config;
	__u8 keys_num;
	__u8 revoked_keys;
	__u8 min_svn;
पूर्ण;

/**
 * काष्ठा cpucp_info - Info from CpuCP that is necessary to the host's driver
 * @sensors: available sensors description.
 * @kernel_version: CpuCP linux kernel version.
 * @reserved: reserved field.
 * @card_type: card configuration type.
 * @card_location: in a server, each card has dअगरferent connections topology
 *                 depending on its location (relevant क्रम PMC card type)
 * @cpld_version: CPLD programmed F/W version.
 * @infineon_version: Infineon मुख्य DC-DC version.
 * @fuse_version: silicon production FUSE inक्रमmation.
 * @thermal_version: thermald S/W version.
 * @cpucp_version: CpuCP S/W version.
 * @dram_size: available DRAM size.
 * @card_name: card name that will be displayed in HWMON subप्रणाली on the host
 * @sec_info: security inक्रमmation
 * @pll_map: Bit map of supported PLLs क्रम current ASIC version.
 */
काष्ठा cpucp_info अणु
	काष्ठा cpucp_sensor sensors[CPUCP_MAX_SENSORS];
	__u8 kernel_version[VERSION_MAX_LEN];
	__le32 reserved;
	__le32 card_type;
	__le32 card_location;
	__le32 cpld_version;
	__le32 infineon_version;
	__u8 fuse_version[VERSION_MAX_LEN];
	__u8 thermal_version[VERSION_MAX_LEN];
	__u8 cpucp_version[VERSION_MAX_LEN];
	__le32 reserved2;
	__le64 dram_size;
	अक्षर card_name[CARD_NAME_MAX_LEN];
	__le64 reserved3;
	__le64 reserved4;
	__u8 reserved5;
	__u8 pad[7];
	काष्ठा cpucp_security_info sec_info;
	__le32 reserved6;
	__u8 pll_map[PLL_MAP_LEN];
पूर्ण;

काष्ठा cpucp_mac_addr अणु
	__u8 mac_addr[ETH_ALEN];
पूर्ण;

काष्ठा cpucp_nic_info अणु
	काष्ठा cpucp_mac_addr mac_addrs[CPUCP_MAX_NICS];
	__le64 link_mask[CPUCP_NIC_MASK_ARR_LEN];
	__le64 pol_tx_mask[CPUCP_NIC_POLARITY_ARR_LEN];
	__le64 pol_rx_mask[CPUCP_NIC_POLARITY_ARR_LEN];
	__le64 link_ext_mask[CPUCP_NIC_MASK_ARR_LEN];
	__u8 qsfp_eeprom[CPUCP_NIC_QSFP_EEPROM_MAX_LEN];
	__le64 स्वतः_neg_mask[CPUCP_NIC_MASK_ARR_LEN];
पूर्ण;

#पूर्ण_अगर /* CPUCP_IF_H */
