<शैली गुरु>
/* SPDX-License-Identअगरier: (BSD-3-Clause OR GPL-2.0-only) */
/* Copyright(c) 2014 - 2020 Intel Corporation */
#अगर_अघोषित ADF_CFG_COMMON_H_
#घोषणा ADF_CFG_COMMON_H_

#समावेश <linux/types.h>
#समावेश <linux/ioctl.h>

#घोषणा ADF_CFG_MAX_STR_LEN 64
#घोषणा ADF_CFG_MAX_KEY_LEN_IN_BYTES ADF_CFG_MAX_STR_LEN
#घोषणा ADF_CFG_MAX_VAL_LEN_IN_BYTES ADF_CFG_MAX_STR_LEN
#घोषणा ADF_CFG_MAX_SECTION_LEN_IN_BYTES ADF_CFG_MAX_STR_LEN
#घोषणा ADF_CFG_BASE_DEC 10
#घोषणा ADF_CFG_BASE_HEX 16
#घोषणा ADF_CFG_ALL_DEVICES 0xFE
#घोषणा ADF_CFG_NO_DEVICE 0xFF
#घोषणा ADF_CFG_AFFINITY_WHATEVER 0xFF
#घोषणा MAX_DEVICE_NAME_SIZE 32
#घोषणा ADF_MAX_DEVICES (32 * 32)
#घोषणा ADF_DEVS_ARRAY_SIZE BITS_TO_LONGS(ADF_MAX_DEVICES)

क्रमागत adf_cfg_val_type अणु
	ADF_DEC,
	ADF_HEX,
	ADF_STR
पूर्ण;

क्रमागत adf_device_type अणु
	DEV_UNKNOWN = 0,
	DEV_DH895XCC,
	DEV_DH895XCCVF,
	DEV_C62X,
	DEV_C62XVF,
	DEV_C3XXX,
	DEV_C3XXXVF,
	DEV_4XXX,
पूर्ण;

काष्ठा adf_dev_status_info अणु
	क्रमागत adf_device_type type;
	__u32 accel_id;
	__u32 instance_id;
	__u8 num_ae;
	__u8 num_accel;
	__u8 num_logical_accel;
	__u8 banks_per_accel;
	__u8 state;
	__u8 bus;
	__u8 dev;
	__u8 fun;
	अक्षर name[MAX_DEVICE_NAME_SIZE];
पूर्ण;

#घोषणा ADF_CTL_IOC_MAGIC 'a'
#घोषणा IOCTL_CONFIG_SYS_RESOURCE_PARAMETERS _IOW(ADF_CTL_IOC_MAGIC, 0, \
		काष्ठा adf_user_cfg_ctl_data)
#घोषणा IOCTL_STOP_ACCEL_DEV _IOW(ADF_CTL_IOC_MAGIC, 1, \
		काष्ठा adf_user_cfg_ctl_data)
#घोषणा IOCTL_START_ACCEL_DEV _IOW(ADF_CTL_IOC_MAGIC, 2, \
		काष्ठा adf_user_cfg_ctl_data)
#घोषणा IOCTL_STATUS_ACCEL_DEV _IOW(ADF_CTL_IOC_MAGIC, 3, __u32)
#घोषणा IOCTL_GET_NUM_DEVICES _IOW(ADF_CTL_IOC_MAGIC, 4, __s32)
#पूर्ण_अगर
