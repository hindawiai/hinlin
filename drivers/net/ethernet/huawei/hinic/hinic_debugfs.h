<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_DEBUGFS_H
#घोषणा HINIC_DEBUGFS_H

#समावेश "hinic_dev.h"

#घोषणा    TBL_ID_FUNC_CFG_SM_NODE                      11
#घोषणा    TBL_ID_FUNC_CFG_SM_INST                      1

#घोषणा HINIC_FUNCTION_CONFIGURE_TABLE_SIZE             64
#घोषणा HINIC_FUNCTION_CONFIGURE_TABLE			1

काष्ठा hinic_cmd_lt_rd अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	अचिन्हित अक्षर node;
	अचिन्हित अक्षर inst;
	अचिन्हित अक्षर entry_size;
	अचिन्हित अक्षर rsvd;
	अचिन्हित पूर्णांक lt_index;
	अचिन्हित पूर्णांक offset;
	अचिन्हित पूर्णांक len;
	अचिन्हित अक्षर data[100];
पूर्ण;

काष्ठा tag_sml_funcfg_tbl अणु
	जोड़ अणु
		काष्ठा अणु
			u32 rsvd0            :8;
			u32 nic_rx_mode      :5;
			u32 rsvd1            :18;
			u32 valid            :1;
		पूर्ण bs;

		u32 value;
	पूर्ण dw0;

	जोड़ अणु
		काष्ठा अणु
			u32 vlan_id             :12;
			u32 vlan_mode           :3;
			u32 fast_recycled_mode  :1;
			u32 mtu                 :16;
		पूर्ण bs;

		u32 value;
	पूर्ण dw1;

	u32 dw2;
	u32 dw3;
	u32 dw4;
	u32 dw5;
	u32 dw6;
	u32 dw7;
	u32 dw8;
	u32 dw9;
	u32 dw10;
	u32 dw11;
	u32 dw12;

	जोड़ अणु
		काष्ठा अणु
			u32 rsvd2               :15;
			u32 cfg_q_num           :9;
			u32 cfg_rq_depth        :6;
			u32 vhd_type            :2;
		पूर्ण bs;

		u32 value;
	पूर्ण dw13;

	u32 dw14;
	u32 dw15;
पूर्ण;

पूर्णांक hinic_sq_debug_add(काष्ठा hinic_dev *dev, u16 sq_id);

व्योम hinic_sq_debug_rem(काष्ठा hinic_sq *sq);

पूर्णांक hinic_rq_debug_add(काष्ठा hinic_dev *dev, u16 rq_id);

व्योम hinic_rq_debug_rem(काष्ठा hinic_rq *rq);

पूर्णांक hinic_func_table_debug_add(काष्ठा hinic_dev *dev);

व्योम hinic_func_table_debug_rem(काष्ठा hinic_dev *dev);

व्योम hinic_sq_dbgfs_init(काष्ठा hinic_dev *nic_dev);

व्योम hinic_sq_dbgfs_uninit(काष्ठा hinic_dev *nic_dev);

व्योम hinic_rq_dbgfs_init(काष्ठा hinic_dev *nic_dev);

व्योम hinic_rq_dbgfs_uninit(काष्ठा hinic_dev *nic_dev);

व्योम hinic_func_tbl_dbgfs_init(काष्ठा hinic_dev *nic_dev);

व्योम hinic_func_tbl_dbgfs_uninit(काष्ठा hinic_dev *nic_dev);

व्योम hinic_dbg_init(काष्ठा hinic_dev *nic_dev);

व्योम hinic_dbg_uninit(काष्ठा hinic_dev *nic_dev);

व्योम hinic_dbg_रेजिस्टर_debugfs(स्थिर अक्षर *debugfs_dir_name);

व्योम hinic_dbg_unरेजिस्टर_debugfs(व्योम);

#पूर्ण_अगर
