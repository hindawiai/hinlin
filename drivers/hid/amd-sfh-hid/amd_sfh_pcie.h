<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AMD MP2 PCIe communication driver
 * Copyright 2020 Advanced Micro Devices, Inc.
 * Authors: Shyam Sundar S K <Shyam-sundar.S-k@amd.com>
 *	    Sandeep Singh <Sandeep.singh@amd.com>
 */

#अगर_अघोषित PCIE_MP2_AMD_H
#घोषणा PCIE_MP2_AMD_H

#समावेश <linux/pci.h>

#घोषणा PCI_DEVICE_ID_AMD_MP2	0x15E4

#घोषणा ENABLE_SENSOR		1
#घोषणा DISABLE_SENSOR		2
#घोषणा STOP_ALL_SENSORS	8

/* MP2 C2P Message Registers */
#घोषणा AMD_C2P_MSG0	0x10500
#घोषणा AMD_C2P_MSG1	0x10504
#घोषणा AMD_C2P_MSG2	0x10508

/* MP2 P2C Message Registers */
#घोषणा AMD_P2C_MSG3	0x1068C /* Supported Sensors info */

/* SFH Command रेजिस्टर */
जोड़ sfh_cmd_base अणु
	u32 ul;
	काष्ठा अणु
		u32 cmd_id : 8;
		u32 sensor_id : 8;
		u32 period : 16;
	पूर्ण s;
पूर्ण;

जोड़ sfh_cmd_param अणु
	u32 ul;
	काष्ठा अणु
		u32 buf_layout : 2;
		u32 buf_length : 6;
		u32 rsvd : 24;
	पूर्ण s;
पूर्ण;

काष्ठा sfh_cmd_reg अणु
	जोड़ sfh_cmd_base cmd_base;
	जोड़ sfh_cmd_param cmd_param;
	phys_addr_t phys_addr;
पूर्ण;

क्रमागत sensor_idx अणु
	accel_idx = 0,
	gyro_idx = 1,
	mag_idx = 2,
	als_idx = 19
पूर्ण;

काष्ठा amd_mp2_dev अणु
	काष्ठा pci_dev *pdev;
	काष्ठा amdtp_cl_data *cl_data;
	व्योम __iomem *mmio;
पूर्ण;

काष्ठा amd_mp2_sensor_info अणु
	u8 sensor_idx;
	u32 period;
	dma_addr_t dma_address;
पूर्ण;

व्योम amd_start_sensor(काष्ठा amd_mp2_dev *privdata, काष्ठा amd_mp2_sensor_info info);
व्योम amd_stop_sensor(काष्ठा amd_mp2_dev *privdata, u16 sensor_idx);
व्योम amd_stop_all_sensors(काष्ठा amd_mp2_dev *privdata);
पूर्णांक amd_mp2_get_sensor_num(काष्ठा amd_mp2_dev *privdata, u8 *sensor_id);
पूर्णांक amd_sfh_hid_client_init(काष्ठा amd_mp2_dev *privdata);
पूर्णांक amd_sfh_hid_client_deinit(काष्ठा amd_mp2_dev *privdata);
#पूर्ण_अगर
