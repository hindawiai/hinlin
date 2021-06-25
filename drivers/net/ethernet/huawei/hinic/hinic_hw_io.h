<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Huawei HiNIC PCI Express Linux driver
 * Copyright(c) 2017 Huawei Technologies Co., Ltd
 */

#अगर_अघोषित HINIC_HW_IO_H
#घोषणा HINIC_HW_IO_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/sizes.h>

#समावेश "hinic_hw_if.h"
#समावेश "hinic_hw_eqs.h"
#समावेश "hinic_hw_wq.h"
#समावेश "hinic_hw_cmdq.h"
#समावेश "hinic_hw_qp.h"

#घोषणा HINIC_DB_PAGE_SIZE      SZ_4K
#घोषणा HINIC_DB_SIZE           SZ_4M
#घोषणा HINIC_HW_WQ_PAGE_SIZE	SZ_4K
#घोषणा HINIC_DEFAULT_WQ_PAGE_SIZE SZ_256K

#घोषणा HINIC_DB_MAX_AREAS      (HINIC_DB_SIZE / HINIC_DB_PAGE_SIZE)

क्रमागत hinic_db_type अणु
	HINIC_DB_CMDQ_TYPE,
	HINIC_DB_SQ_TYPE,
पूर्ण;

क्रमागत hinic_io_path अणु
	HINIC_CTRL_PATH,
	HINIC_DATA_PATH,
पूर्ण;

काष्ठा hinic_मुक्त_db_area अणु
	पूर्णांक             db_idx[HINIC_DB_MAX_AREAS];

	पूर्णांक             alloc_pos;
	पूर्णांक             वापस_pos;

	पूर्णांक             num_मुक्त;

	/* Lock क्रम getting db area */
	काष्ठा semaphore        idx_lock;
पूर्ण;

काष्ठा hinic_nic_cfg अणु
	/* lock क्रम getting nic cfg */
	काष्ठा mutex		cfg_mutex;
	bool			छोड़ो_set;
	u32			स्वतः_neg;
	u32			rx_छोड़ो;
	u32			tx_छोड़ो;
पूर्ण;

काष्ठा hinic_func_to_io अणु
	काष्ठा hinic_hwअगर       *hwअगर;
	काष्ठा hinic_hwdev      *hwdev;
	u16			global_qpn;
	काष्ठा hinic_ceqs       ceqs;

	काष्ठा hinic_wqs        wqs;

	काष्ठा hinic_wq         *sq_wq;
	काष्ठा hinic_wq         *rq_wq;

	काष्ठा hinic_qp         *qps;
	u16                     max_qps;

	u16			sq_depth;
	u16			rq_depth;

	व्योम __iomem            **sq_db;
	व्योम __iomem            *db_base;

	व्योम                    *ci_addr_base;
	dma_addr_t              ci_dma_base;

	काष्ठा hinic_मुक्त_db_area       मुक्त_db_area;

	व्योम __iomem                    *cmdq_db_area[HINIC_MAX_CMDQ_TYPES];

	काष्ठा hinic_cmdqs              cmdqs;

	u16			max_vfs;
	काष्ठा vf_data_storage	*vf_infos;
	u8			link_status;
	काष्ठा hinic_nic_cfg	nic_cfg;
पूर्ण;

काष्ठा hinic_wq_page_size अणु
	u8	status;
	u8	version;
	u8	rsvd0[6];

	u16	func_idx;
	u8	ppf_idx;
	u8	page_size;

	u32	rsvd1;
पूर्ण;

पूर्णांक hinic_set_wq_page_size(काष्ठा hinic_hwdev *hwdev, u16 func_idx,
			   u32 page_size);

पूर्णांक hinic_io_create_qps(काष्ठा hinic_func_to_io *func_to_io,
			u16 base_qpn, पूर्णांक num_qps,
			काष्ठा msix_entry *sq_msix_entries,
			काष्ठा msix_entry *rq_msix_entries);

व्योम hinic_io_destroy_qps(काष्ठा hinic_func_to_io *func_to_io,
			  पूर्णांक num_qps);

पूर्णांक hinic_io_init(काष्ठा hinic_func_to_io *func_to_io,
		  काष्ठा hinic_hwअगर *hwअगर, u16 max_qps, पूर्णांक num_ceqs,
		  काष्ठा msix_entry *ceq_msix_entries);

व्योम hinic_io_मुक्त(काष्ठा hinic_func_to_io *func_to_io);

#पूर्ण_अगर
