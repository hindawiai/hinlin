<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Internal header file क्रम QE TDM mode routines.
 *
 * Copyright (C) 2016 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors:	Zhao Qiang <qiang.zhao@nxp.com>
 */

#अगर_अघोषित _QE_TDM_H_
#घोषणा _QE_TDM_H_

#समावेश <linux/kernel.h>
#समावेश <linux/list.h>

#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>

#समावेश <soc/fsl/qe/ucc.h>
#समावेश <soc/fsl/qe/ucc_fast.h>

/* SI RAM entries */
#घोषणा SIR_LAST	0x0001
#घोषणा SIR_BYTE	0x0002
#घोषणा SIR_CNT(x)	((x) << 2)
#घोषणा SIR_CSEL(x)	((x) << 5)
#घोषणा SIR_SGS		0x0200
#घोषणा SIR_SWTR	0x4000
#घोषणा SIR_MCC		0x8000
#घोषणा SIR_IDLE	0

/* SIxMR fields */
#घोषणा SIMR_SAD(x) ((x) << 12)
#घोषणा SIMR_SDM_NORMAL	0x0000
#घोषणा SIMR_SDM_INTERNAL_LOOPBACK	0x0800
#घोषणा SIMR_SDM_MASK	0x0c00
#घोषणा SIMR_CRT	0x0040
#घोषणा SIMR_SL		0x0020
#घोषणा SIMR_CE		0x0010
#घोषणा SIMR_FE		0x0008
#घोषणा SIMR_GM		0x0004
#घोषणा SIMR_TFSD(n)	(n)
#घोषणा SIMR_RFSD(n)	((n) << 8)

क्रमागत tdm_ts_t अणु
	TDM_TX_TS,
	TDM_RX_TS
पूर्ण;

क्रमागत tdm_framer_t अणु
	TDM_FRAMER_T1,
	TDM_FRAMER_E1
पूर्ण;

क्रमागत tdm_mode_t अणु
	TDM_INTERNAL_LOOPBACK,
	TDM_NORMAL
पूर्ण;

काष्ठा si_mode_info अणु
	u8 simr_rfsd;
	u8 simr_tfsd;
	u8 simr_crt;
	u8 simr_sl;
	u8 simr_ce;
	u8 simr_fe;
	u8 simr_gm;
पूर्ण;

काष्ठा ucc_tdm_info अणु
	काष्ठा ucc_fast_info uf_info;
	काष्ठा si_mode_info si_info;
पूर्ण;

काष्ठा ucc_tdm अणु
	u16 tdm_port;		/* port क्रम this tdm:TDMA,TDMB */
	u32 siram_entry_id;
	u16 __iomem *siram;
	काष्ठा si1 __iomem *si_regs;
	क्रमागत tdm_framer_t tdm_framer_type;
	क्रमागत tdm_mode_t tdm_mode;
	u8 num_of_ts;		/* the number of बारlots in this tdm frame */
	u32 tx_ts_mask;		/* tx समय slot mask */
	u32 rx_ts_mask;		/* rx समय slot mask */
पूर्ण;

पूर्णांक ucc_of_parse_tdm(काष्ठा device_node *np, काष्ठा ucc_tdm *utdm,
		     काष्ठा ucc_tdm_info *ut_info);
व्योम ucc_tdm_init(काष्ठा ucc_tdm *utdm, काष्ठा ucc_tdm_info *ut_info);
#पूर्ण_अगर
