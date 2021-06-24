<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2006 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors: 	Shlomi Gridish <gridish@मुक्तscale.com>
 * 		Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * Internal header file क्रम UCC unit routines.
 */
#अगर_अघोषित __UCC_H__
#घोषणा __UCC_H__

#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#घोषणा STATISTICS

#घोषणा UCC_MAX_NUM	8

/* Slow or fast type क्रम UCCs.
*/
क्रमागत ucc_speed_type अणु
	UCC_SPEED_TYPE_FAST = UCC_GUEMR_MODE_FAST_RX | UCC_GUEMR_MODE_FAST_TX,
	UCC_SPEED_TYPE_SLOW = UCC_GUEMR_MODE_SLOW_RX | UCC_GUEMR_MODE_SLOW_TX
पूर्ण;

/* ucc_set_type
 * Sets UCC to slow or fast mode.
 *
 * ucc_num - (In) number of UCC (0-7).
 * speed   - (In) slow or fast mode क्रम UCC.
 */
पूर्णांक ucc_set_type(अचिन्हित पूर्णांक ucc_num, क्रमागत ucc_speed_type speed);

पूर्णांक ucc_set_qe_mux_mii_mng(अचिन्हित पूर्णांक ucc_num);

पूर्णांक ucc_set_qe_mux_rxtx(अचिन्हित पूर्णांक ucc_num, क्रमागत qe_घड़ी घड़ी,
	क्रमागत comm_dir mode);
पूर्णांक ucc_set_tdm_rxtx_clk(अचिन्हित पूर्णांक tdm_num, क्रमागत qe_घड़ी घड़ी,
			 क्रमागत comm_dir mode);
पूर्णांक ucc_set_tdm_rxtx_sync(अचिन्हित पूर्णांक tdm_num, क्रमागत qe_घड़ी घड़ी,
			  क्रमागत comm_dir mode);

पूर्णांक ucc_mux_set_grant_tsa_bkpt(अचिन्हित पूर्णांक ucc_num, पूर्णांक set, u32 mask);

/* QE MUX घड़ी routing क्रम UCC
*/
अटल अंतरभूत पूर्णांक ucc_set_qe_mux_grant(अचिन्हित पूर्णांक ucc_num, पूर्णांक set)
अणु
	वापस ucc_mux_set_grant_tsa_bkpt(ucc_num, set, QE_CMXUCR_GRANT);
पूर्ण

अटल अंतरभूत पूर्णांक ucc_set_qe_mux_tsa(अचिन्हित पूर्णांक ucc_num, पूर्णांक set)
अणु
	वापस ucc_mux_set_grant_tsa_bkpt(ucc_num, set, QE_CMXUCR_TSA);
पूर्ण

अटल अंतरभूत पूर्णांक ucc_set_qe_mux_bkpt(अचिन्हित पूर्णांक ucc_num, पूर्णांक set)
अणु
	वापस ucc_mux_set_grant_tsa_bkpt(ucc_num, set, QE_CMXUCR_BKPT);
पूर्ण

#पूर्ण_अगर				/* __UCC_H__ */
