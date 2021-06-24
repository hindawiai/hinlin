<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_CXT_H
#घोषणा _QED_CXT_H

#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/qed/qed_अगर.h>
#समावेश "qed_hsi.h"
#समावेश "qed.h"

काष्ठा qed_cxt_info अणु
	व्योम			*p_cxt;
	u32			iid;
	क्रमागत protocol_type	type;
पूर्ण;

#घोषणा MAX_TID_BLOCKS                  512
काष्ठा qed_tid_mem अणु
	u32 tid_size;
	u32 num_tids_per_block;
	u32 waste;
	u8 *blocks[MAX_TID_BLOCKS];	/* 4K */
पूर्ण;

/**
 * @brief qeकरो_cid_get_cxt_info - Returns the context info क्रम a specअगरic cid
 *
 *
 * @param p_hwfn
 * @param p_info in/out
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_get_cid_info(काष्ठा qed_hwfn *p_hwfn,
			 काष्ठा qed_cxt_info *p_info);

/**
 * @brief qed_cxt_get_tid_mem_info
 *
 * @param p_hwfn
 * @param p_info
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_get_tid_mem_info(काष्ठा qed_hwfn *p_hwfn,
			     काष्ठा qed_tid_mem *p_info);

#घोषणा QED_CXT_ISCSI_TID_SEG	PROTOCOLID_ISCSI
#घोषणा QED_CXT_ROCE_TID_SEG	PROTOCOLID_ROCE
#घोषणा QED_CXT_FCOE_TID_SEG	PROTOCOLID_FCOE
क्रमागत qed_cxt_elem_type अणु
	QED_ELEM_CXT,
	QED_ELEM_SRQ,
	QED_ELEM_TASK,
	QED_ELEM_XRC_SRQ,
पूर्ण;

u32 qed_cxt_get_proto_cid_count(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत protocol_type type, u32 *vf_cid);

/**
 * @brief qed_cxt_set_pf_params - Set the PF params क्रम cxt init
 *
 * @param p_hwfn
 * @param rdma_tasks - requested maximum
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_set_pf_params(काष्ठा qed_hwfn *p_hwfn, u32 rdma_tasks);

/**
 * @brief qed_cxt_cfg_ilt_compute - compute ILT init parameters
 *
 * @param p_hwfn
 * @param last_line
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_cfg_ilt_compute(काष्ठा qed_hwfn *p_hwfn, u32 *last_line);

/**
 * @brief qed_cxt_cfg_ilt_compute_excess - how many lines can be decreased
 *
 * @param p_hwfn
 * @param used_lines
 */
u32 qed_cxt_cfg_ilt_compute_excess(काष्ठा qed_hwfn *p_hwfn, u32 used_lines);

/**
 * @brief qed_cxt_mngr_alloc - Allocate and init the context manager काष्ठा
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_mngr_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_cxt_mngr_मुक्त
 *
 * @param p_hwfn
 */
व्योम qed_cxt_mngr_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_cxt_tables_alloc - Allocate ILT shaकरोw, Searcher T2, acquired map
 *
 * @param p_hwfn
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_tables_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_cxt_mngr_setup - Reset the acquired CIDs
 *
 * @param p_hwfn
 */
व्योम qed_cxt_mngr_setup(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_cxt_hw_init_common - Initailze ILT and DQ, common phase, per path.
 *
 *
 *
 * @param p_hwfn
 */
व्योम qed_cxt_hw_init_common(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_cxt_hw_init_pf - Initailze ILT and DQ, PF phase, per path.
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_cxt_hw_init_pf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_qm_init_pf - Initailze the QM PF phase, per path
 *
 * @param p_hwfn
 * @param p_ptt
 * @param is_pf_loading
 */
व्योम qed_qm_init_pf(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, bool is_pf_loading);

/**
 * @brief Reconfigures QM pf on the fly
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_qm_reconf(काष्ठा qed_hwfn *p_hwfn, काष्ठा qed_ptt *p_ptt);

#घोषणा QED_CXT_PF_CID (0xff)

/**
 * @brief qed_cxt_release - Release a cid
 *
 * @param p_hwfn
 * @param cid
 */
व्योम qed_cxt_release_cid(काष्ठा qed_hwfn *p_hwfn, u32 cid);

/**
 * @brief qed_cxt_release - Release a cid beदीर्घing to a vf-queue
 *
 * @param p_hwfn
 * @param cid
 * @param vfid - engine relative index. QED_CXT_PF_CID अगर beदीर्घs to PF
 */
व्योम _qed_cxt_release_cid(काष्ठा qed_hwfn *p_hwfn, u32 cid, u8 vfid);

/**
 * @brief qed_cxt_acquire - Acquire a new cid of a specअगरic protocol type
 *
 * @param p_hwfn
 * @param type
 * @param p_cid
 *
 * @वापस पूर्णांक
 */
पूर्णांक qed_cxt_acquire_cid(काष्ठा qed_hwfn *p_hwfn,
			क्रमागत protocol_type type, u32 *p_cid);

/**
 * @brief _qed_cxt_acquire - Acquire a new cid of a specअगरic protocol type
 *                           क्रम a vf-queue
 *
 * @param p_hwfn
 * @param type
 * @param p_cid
 * @param vfid - engine relative index. QED_CXT_PF_CID अगर beदीर्घs to PF
 *
 * @वापस पूर्णांक
 */
पूर्णांक _qed_cxt_acquire_cid(काष्ठा qed_hwfn *p_hwfn,
			 क्रमागत protocol_type type, u32 *p_cid, u8 vfid);

पूर्णांक qed_cxt_dynamic_ilt_alloc(काष्ठा qed_hwfn *p_hwfn,
			      क्रमागत qed_cxt_elem_type elem_type, u32 iid);
u32 qed_cxt_get_proto_tid_count(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत protocol_type type);
u32 qed_cxt_get_proto_cid_start(काष्ठा qed_hwfn *p_hwfn,
				क्रमागत protocol_type type);
पूर्णांक qed_cxt_मुक्त_proto_ilt(काष्ठा qed_hwfn *p_hwfn, क्रमागत protocol_type proto);

#घोषणा QED_CTX_WORKING_MEM 0
#घोषणा QED_CTX_FL_MEM 1
पूर्णांक qed_cxt_get_task_ctx(काष्ठा qed_hwfn *p_hwfn,
			 u32 tid, u8 ctx_type, व्योम **task_ctx);

/* Max number of connection types in HW (DQ/CDU etc.) */
#घोषणा MAX_CONN_TYPES          PROTOCOLID_COMMON
#घोषणा NUM_TASK_TYPES          2
#घोषणा NUM_TASK_PF_SEGMENTS    4
#घोषणा NUM_TASK_VF_SEGMENTS    1

/* PF per protocl configuration object */
#घोषणा TASK_SEGMENTS   (NUM_TASK_PF_SEGMENTS + NUM_TASK_VF_SEGMENTS)
#घोषणा TASK_SEGMENT_VF (NUM_TASK_PF_SEGMENTS)

काष्ठा qed_tid_seg अणु
	u32 count;
	u8 type;
	bool has_fl_mem;
पूर्ण;

काष्ठा qed_conn_type_cfg अणु
	u32 cid_count;
	u32 cids_per_vf;
	काष्ठा qed_tid_seg tid_seg[TASK_SEGMENTS];
पूर्ण;

/* ILT Client configuration,
 * Per connection type (protocol) resources (cids, tis, vf cids etc.)
 * 1 - क्रम connection context (CDUC) and क्रम each task context we need two
 * values, क्रम regular task context and क्रम क्रमce load memory
 */
#घोषणा ILT_CLI_PF_BLOCKS       (1 + NUM_TASK_PF_SEGMENTS * 2)
#घोषणा ILT_CLI_VF_BLOCKS       (1 + NUM_TASK_VF_SEGMENTS * 2)
#घोषणा CDUC_BLK                (0)
#घोषणा SRQ_BLK                 (0)
#घोषणा CDUT_SEG_BLK(n)         (1 + (u8)(n))
#घोषणा CDUT_FL_SEG_BLK(n, X)   (1 + (n) + NUM_TASK_ ## X ## _SEGMENTS)

काष्ठा ilt_cfg_pair अणु
	u32 reg;
	u32 val;
पूर्ण;

काष्ठा qed_ilt_cli_blk अणु
	u32 total_size;		/* 0 means not active */
	u32 real_size_in_page;
	u32 start_line;
	u32 dynamic_line_offset;
	u32 dynamic_line_cnt;
पूर्ण;

काष्ठा qed_ilt_client_cfg अणु
	bool active;

	/* ILT boundaries */
	काष्ठा ilt_cfg_pair first;
	काष्ठा ilt_cfg_pair last;
	काष्ठा ilt_cfg_pair p_size;

	/* ILT client blocks क्रम PF */
	काष्ठा qed_ilt_cli_blk pf_blks[ILT_CLI_PF_BLOCKS];
	u32 pf_total_lines;

	/* ILT client blocks क्रम VFs */
	काष्ठा qed_ilt_cli_blk vf_blks[ILT_CLI_VF_BLOCKS];
	u32 vf_total_lines;
पूर्ण;

काष्ठा qed_cid_acquired_map अणु
	u32		start_cid;
	u32		max_count;
	अचिन्हित दीर्घ	*cid_map;
पूर्ण;

काष्ठा qed_src_t2 अणु
	काष्ठा phys_mem_desc *dma_mem;
	u32 num_pages;
	u64 first_मुक्त;
	u64 last_मुक्त;
पूर्ण;

काष्ठा qed_cxt_mngr अणु
	/* Per protocl configuration */
	काष्ठा qed_conn_type_cfg	conn_cfg[MAX_CONN_TYPES];

	/* computed ILT काष्ठाure */
	काष्ठा qed_ilt_client_cfg	clients[MAX_ILT_CLIENTS];

	/* Task type sizes */
	u32 task_type_size[NUM_TASK_TYPES];

	/* total number of VFs क्रम this hwfn -
	 * ALL VFs are symmetric in terms of HW resources
	 */
	u32 vf_count;
	u32 first_vf_in_pf;

	/* Acquired CIDs */
	काष्ठा qed_cid_acquired_map	acquired[MAX_CONN_TYPES];

	काष्ठा qed_cid_acquired_map
	acquired_vf[MAX_CONN_TYPES][MAX_NUM_VFS];

	/* ILT  shaकरोw table */
	काष्ठा phys_mem_desc *ilt_shaकरोw;
	u32 ilt_shaकरोw_size;
	u32 pf_start_line;

	/* Mutex क्रम a dynamic ILT allocation */
	काष्ठा mutex mutex;

	/* SRC T2 */
	काष्ठा qed_src_t2 src_t2;

	/* total number of SRQ's क्रम this hwfn */
	u32 srq_count;
	u32 xrc_srq_count;

	/* Maximal number of L2 steering filters */
	u32 arfs_count;

	u8 task_type_id;
	u16 task_ctx_size;
	u16 conn_ctx_size;
पूर्ण;

u16 qed_get_cdut_num_pf_init_pages(काष्ठा qed_hwfn *p_hwfn);
u16 qed_get_cdut_num_vf_init_pages(काष्ठा qed_hwfn *p_hwfn);
u16 qed_get_cdut_num_pf_work_pages(काष्ठा qed_hwfn *p_hwfn);
u16 qed_get_cdut_num_vf_work_pages(काष्ठा qed_hwfn *p_hwfn);

u32 qed_cxt_get_ilt_page_size(काष्ठा qed_hwfn *p_hwfn,
			      क्रमागत ilt_clients ilt_client);

u32 qed_cxt_get_total_srq_count(काष्ठा qed_hwfn *p_hwfn);

#पूर्ण_अगर
