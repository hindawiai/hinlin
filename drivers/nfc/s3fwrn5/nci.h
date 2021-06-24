<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * NCI based driver क्रम Samsung S3FWRN5 NFC chip
 *
 * Copyright (C) 2015 Samsung Electrnoics
 * Robert Baldyga <r.baldyga@samsung.com>
 */

#अगर_अघोषित __LOCAL_S3FWRN5_NCI_H_
#घोषणा __LOCAL_S3FWRN5_NCI_H_

#समावेश "s3fwrn5.h"

#घोषणा NCI_PROP_SET_RFREG	0x22

काष्ठा nci_prop_set_rfreg_cmd अणु
	__u8 index;
	__u8 data[252];
पूर्ण;

काष्ठा nci_prop_set_rfreg_rsp अणु
	__u8 status;
पूर्ण;

#घोषणा NCI_PROP_START_RFREG	0x26

काष्ठा nci_prop_start_rfreg_rsp अणु
	__u8 status;
पूर्ण;

#घोषणा NCI_PROP_STOP_RFREG	0x27

काष्ठा nci_prop_stop_rfreg_cmd अणु
	__u16 checksum;
पूर्ण;

काष्ठा nci_prop_stop_rfreg_rsp अणु
	__u8 status;
पूर्ण;

#घोषणा NCI_PROP_FW_CFG		0x28

काष्ठा nci_prop_fw_cfg_cmd अणु
	__u8 clk_type;
	__u8 clk_speed;
	__u8 clk_req;
पूर्ण;

काष्ठा nci_prop_fw_cfg_rsp अणु
	__u8 status;
पूर्ण;

व्योम s3fwrn5_nci_get_prop_ops(काष्ठा nci_driver_ops **ops, माप_प्रकार *n);
पूर्णांक s3fwrn5_nci_rf_configure(काष्ठा s3fwrn5_info *info, स्थिर अक्षर *fw_name);

#पूर्ण_अगर /* __LOCAL_S3FWRN5_NCI_H_ */
