<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause) */
/* QLogic qed NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#अगर_अघोषित _QED_HW_H
#घोषणा _QED_HW_H

#समावेश <linux/types.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश "qed.h"
#समावेश "qed_dev_api.h"

/* Forward decleration */
काष्ठा qed_ptt;

क्रमागत reserved_ptts अणु
	RESERVED_PTT_EDIAG,
	RESERVED_PTT_USER_SPACE,
	RESERVED_PTT_MAIN,
	RESERVED_PTT_DPC,
	RESERVED_PTT_MAX
पूर्ण;

क्रमागत _dmae_cmd_dst_mask अणु
	DMAE_CMD_DST_MASK_NONE	= 0,
	DMAE_CMD_DST_MASK_PCIE	= 1,
	DMAE_CMD_DST_MASK_GRC	= 2
पूर्ण;

क्रमागत _dmae_cmd_src_mask अणु
	DMAE_CMD_SRC_MASK_PCIE	= 0,
	DMAE_CMD_SRC_MASK_GRC	= 1
पूर्ण;

क्रमागत _dmae_cmd_crc_mask अणु
	DMAE_CMD_COMP_CRC_EN_MASK_NONE	= 0,
	DMAE_CMD_COMP_CRC_EN_MASK_SET	= 1
पूर्ण;

/* definitions क्रम DMA स्थिरants */
#घोषणा DMAE_GO_VALUE   0x1

#घोषणा DMAE_COMPLETION_VAL     0xD1AE
#घोषणा DMAE_CMD_ENDIANITY      0x2

#घोषणा DMAE_CMD_SIZE   14
#घोषणा DMAE_CMD_SIZE_TO_FILL   (DMAE_CMD_SIZE - 5)
#घोषणा DMAE_MIN_WAIT_TIME      0x2
#घोषणा DMAE_MAX_CLIENTS        32

/**
 * @brief qed_gtt_init - Initialize GTT winकरोws
 *
 * @param p_hwfn
 */
व्योम qed_gtt_init(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ptt_invalidate - Forces all ptt entries to be re-configured
 *
 * @param p_hwfn
 */
व्योम qed_ptt_invalidate(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ptt_pool_alloc - Allocate and initialize PTT pool
 *
 * @param p_hwfn
 *
 * @वापस काष्ठा _qed_status - success (0), negative - error.
 */
पूर्णांक qed_ptt_pool_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ptt_pool_मुक्त -
 *
 * @param p_hwfn
 */
व्योम qed_ptt_pool_मुक्त(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_ptt_get_hw_addr - Get PTT's GRC/HW address
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस u32
 */
u32 qed_ptt_get_hw_addr(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_ptt_get_bar_addr - Get PPT's बाह्यal BAR address
 *
 * @param p_hwfn
 * @param p_ptt
 *
 * @वापस u32
 */
u32 qed_ptt_get_bar_addr(काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_ptt_set_win - Set PTT Winकरोw's GRC BAR address
 *
 * @param p_hwfn
 * @param new_hw_addr
 * @param p_ptt
 */
व्योम qed_ptt_set_win(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt,
		     u32 new_hw_addr);

/**
 * @brief qed_get_reserved_ptt - Get a specअगरic reserved PTT
 *
 * @param p_hwfn
 * @param ptt_idx
 *
 * @वापस काष्ठा qed_ptt *
 */
काष्ठा qed_ptt *qed_get_reserved_ptt(काष्ठा qed_hwfn *p_hwfn,
				     क्रमागत reserved_ptts ptt_idx);

/**
 * @brief qed_wr - Write value to BAR using the given ptt
 *
 * @param p_hwfn
 * @param p_ptt
 * @param val
 * @param hw_addr
 */
व्योम qed_wr(काष्ठा qed_hwfn *p_hwfn,
	    काष्ठा qed_ptt *p_ptt,
	    u32 hw_addr,
	    u32 val);

/**
 * @brief qed_rd - Read value from BAR using the given ptt
 *
 * @param p_hwfn
 * @param p_ptt
 * @param val
 * @param hw_addr
 */
u32 qed_rd(काष्ठा qed_hwfn *p_hwfn,
	   काष्ठा qed_ptt *p_ptt,
	   u32 hw_addr);

/**
 * @brief qed_स_नकल_from - copy n bytes from BAR using the given
 *        ptt
 *
 * @param p_hwfn
 * @param p_ptt
 * @param dest
 * @param hw_addr
 * @param n
 */
व्योम qed_स_नकल_from(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt,
		     व्योम *dest,
		     u32 hw_addr,
		     माप_प्रकार n);

/**
 * @brief qed_स_नकल_to - copy n bytes to BAR using the given
 *        ptt
 *
 * @param p_hwfn
 * @param p_ptt
 * @param hw_addr
 * @param src
 * @param n
 */
व्योम qed_स_नकल_to(काष्ठा qed_hwfn *p_hwfn,
		   काष्ठा qed_ptt *p_ptt,
		   u32 hw_addr,
		   व्योम *src,
		   माप_प्रकार n);
/**
 * @brief qed_fid_pretend - pretend to another function when
 *        accessing the ptt winकरोw. There is no way to unpretend
 *        a function. The only way to cancel a pretend is to
 *        pretend back to the original function.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param fid - fid field of pxp_pretend काष्ठाure. Can contain
 *            either pf / vf, port/path fields are करोn't care.
 */
व्योम qed_fid_pretend(काष्ठा qed_hwfn *p_hwfn,
		     काष्ठा qed_ptt *p_ptt,
		     u16 fid);

/**
 * @brief qed_port_pretend - pretend to another port when
 *        accessing the ptt winकरोw
 *
 * @param p_hwfn
 * @param p_ptt
 * @param port_id - the port to pretend to
 */
व्योम qed_port_pretend(काष्ठा qed_hwfn *p_hwfn,
		      काष्ठा qed_ptt *p_ptt,
		      u8 port_id);

/**
 * @brief qed_port_unpretend - cancel any previously set port
 *        pretend
 *
 * @param p_hwfn
 * @param p_ptt
 */
व्योम qed_port_unpretend(काष्ठा qed_hwfn *p_hwfn,
			काष्ठा qed_ptt *p_ptt);

/**
 * @brief qed_port_fid_pretend - pretend to another port and another function
 *        when accessing the ptt winकरोw
 *
 * @param p_hwfn
 * @param p_ptt
 * @param port_id - the port to pretend to
 * @param fid - fid field of pxp_pretend काष्ठाure. Can contain either pf / vf.
 */
व्योम qed_port_fid_pretend(काष्ठा qed_hwfn *p_hwfn,
			  काष्ठा qed_ptt *p_ptt, u8 port_id, u16 fid);

/**
 * @brief qed_vfid_to_concrete - build a concrete FID क्रम a
 *        given VF ID
 *
 * @param p_hwfn
 * @param p_ptt
 * @param vfid
 */
u32 qed_vfid_to_concrete(काष्ठा qed_hwfn *p_hwfn, u8 vfid);

/**
 * @brief qed_dmae_idx_to_go_cmd - map the idx to dmae cmd
 * this is declared here since other files will require it.
 * @param idx
 */
u32 qed_dmae_idx_to_go_cmd(u8 idx);

/**
 * @brief qed_dmae_info_alloc - Init the dmae_info काष्ठाure
 * which is part of p_hwfn.
 * @param p_hwfn
 */
पूर्णांक qed_dmae_info_alloc(काष्ठा qed_hwfn *p_hwfn);

/**
 * @brief qed_dmae_info_मुक्त - Free the dmae_info काष्ठाure
 * which is part of p_hwfn
 *
 * @param p_hwfn
 */
व्योम qed_dmae_info_मुक्त(काष्ठा qed_hwfn *p_hwfn);

जोड़ qed_qm_pq_params अणु
	काष्ठा अणु
		u8 q_idx;
	पूर्ण iscsi;

	काष्ठा अणु
		u8 tc;
	पूर्ण	core;

	काष्ठा अणु
		u8	is_vf;
		u8	vf_id;
		u8	tc;
	पूर्ण	eth;

	काष्ठा अणु
		u8 dcqcn;
		u8 qpid;	/* roce relative */
	पूर्ण roce;
पूर्ण;

पूर्णांक qed_init_fw_data(काष्ठा qed_dev *cdev,
		     स्थिर u8 *fw_data);

पूर्णांक qed_dmae_sanity(काष्ठा qed_hwfn *p_hwfn,
		    काष्ठा qed_ptt *p_ptt, स्थिर अक्षर *phase);

#घोषणा QED_HW_ERR_MAX_STR_SIZE 256

/**
 * @brief qed_hw_err_notअगरy - Notअगरy upper layer driver and management FW
 *	about a HW error.
 *
 * @param p_hwfn
 * @param p_ptt
 * @param err_type
 * @param fmt - debug data buffer to send to the MFW
 * @param ... - buffer क्रमmat args
 */
व्योम __म_लिखो(4, 5) __cold qed_hw_err_notअगरy(काष्ठा qed_hwfn *p_hwfn,
					     काष्ठा qed_ptt *p_ptt,
					     क्रमागत qed_hw_err_type err_type,
					     स्थिर अक्षर *fmt, ...);
#पूर्ण_अगर
