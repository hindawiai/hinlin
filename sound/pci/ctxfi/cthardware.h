<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008, Creative Technology Ltd. All Rights Reserved.
 *
 * @File	cthardware.h
 *
 * @Brief
 * This file contains the definition of hardware access methord.
 *
 * @Author	Liu Chun
 * @Date 	May 13 2008
 */

#अगर_अघोषित CTHARDWARE_H
#घोषणा CTHARDWARE_H

#समावेश <linux/types.h>
#समावेश <linux/pci.h>
#समावेश <sound/core.h>

क्रमागत CHIPTYP अणु
	ATC20K1,
	ATC20K2,
	ATCNONE
पूर्ण;

क्रमागत CTCARDS अणु
	/* 20k1 models */
	CTSB055X,
	CT20K1_MODEL_FIRST = CTSB055X,
	CTSB073X,
	CTUAA,
	CT20K1_UNKNOWN,
	/* 20k2 models */
	CTSB0760,
	CT20K2_MODEL_FIRST = CTSB0760,
	CTHENDRIX,
	CTSB0880,
	CTSB1270,
	CT20K2_UNKNOWN,
	NUM_CTCARDS		/* This should always be the last */
पूर्ण;

/* Type of input source क्रम ADC */
क्रमागत ADCSRCअणु
	ADC_MICIN,
	ADC_LINEIN,
	ADC_VIDEO,
	ADC_AUX,
	ADC_NONE	/* Switch to digital input */
पूर्ण;

काष्ठा card_conf अणु
	/* device भव mem page table page physical addr
	 * (supporting one page table page now) */
	अचिन्हित दीर्घ vm_pgt_phys;
	अचिन्हित पूर्णांक rsr;	/* reference sample rate in Hzs*/
	अचिन्हित पूर्णांक msr;	/* master sample rate in rsrs */
पूर्ण;

काष्ठा capabilities अणु
	अचिन्हित पूर्णांक digit_io_चयन:1;
	अचिन्हित पूर्णांक dedicated_mic:1;
	अचिन्हित पूर्णांक output_चयन:1;
	अचिन्हित पूर्णांक mic_source_चयन:1;
पूर्ण;

काष्ठा hw अणु
	पूर्णांक (*card_init)(काष्ठा hw *hw, काष्ठा card_conf *info);
	पूर्णांक (*card_stop)(काष्ठा hw *hw);
	पूर्णांक (*pll_init)(काष्ठा hw *hw, अचिन्हित पूर्णांक rsr);
#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक (*suspend)(काष्ठा hw *hw);
	पूर्णांक (*resume)(काष्ठा hw *hw, काष्ठा card_conf *info);
#पूर्ण_अगर
	पूर्णांक (*is_adc_source_selected)(काष्ठा hw *hw, क्रमागत ADCSRC source);
	पूर्णांक (*select_adc_source)(काष्ठा hw *hw, क्रमागत ADCSRC source);
	काष्ठा capabilities (*capabilities)(काष्ठा hw *hw);
	पूर्णांक (*output_चयन_get)(काष्ठा hw *hw);
	पूर्णांक (*output_चयन_put)(काष्ठा hw *hw, पूर्णांक position);
	पूर्णांक (*mic_source_चयन_get)(काष्ठा hw *hw);
	पूर्णांक (*mic_source_चयन_put)(काष्ठा hw *hw, पूर्णांक position);

	/* SRC operations */
	पूर्णांक (*src_rsc_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*src_rsc_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*src_set_state)(व्योम *blk, अचिन्हित पूर्णांक state);
	पूर्णांक (*src_set_bm)(व्योम *blk, अचिन्हित पूर्णांक bm);
	पूर्णांक (*src_set_rsr)(व्योम *blk, अचिन्हित पूर्णांक rsr);
	पूर्णांक (*src_set_sf)(व्योम *blk, अचिन्हित पूर्णांक sf);
	पूर्णांक (*src_set_wr)(व्योम *blk, अचिन्हित पूर्णांक wr);
	पूर्णांक (*src_set_pm)(व्योम *blk, अचिन्हित पूर्णांक pm);
	पूर्णांक (*src_set_rom)(व्योम *blk, अचिन्हित पूर्णांक rom);
	पूर्णांक (*src_set_vo)(व्योम *blk, अचिन्हित पूर्णांक vo);
	पूर्णांक (*src_set_st)(व्योम *blk, अचिन्हित पूर्णांक st);
	पूर्णांक (*src_set_ie)(व्योम *blk, अचिन्हित पूर्णांक ie);
	पूर्णांक (*src_set_ilsz)(व्योम *blk, अचिन्हित पूर्णांक ilsz);
	पूर्णांक (*src_set_bp)(व्योम *blk, अचिन्हित पूर्णांक bp);
	पूर्णांक (*src_set_cisz)(व्योम *blk, अचिन्हित पूर्णांक cisz);
	पूर्णांक (*src_set_ca)(व्योम *blk, अचिन्हित पूर्णांक ca);
	पूर्णांक (*src_set_sa)(व्योम *blk, अचिन्हित पूर्णांक sa);
	पूर्णांक (*src_set_la)(व्योम *blk, अचिन्हित पूर्णांक la);
	पूर्णांक (*src_set_pitch)(व्योम *blk, अचिन्हित पूर्णांक pitch);
	पूर्णांक (*src_set_clear_zbufs)(व्योम *blk, अचिन्हित पूर्णांक clear);
	पूर्णांक (*src_set_dirty)(व्योम *blk, अचिन्हित पूर्णांक flags);
	पूर्णांक (*src_set_dirty_all)(व्योम *blk);
	पूर्णांक (*src_commit_ग_लिखो)(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk);
	पूर्णांक (*src_get_ca)(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk);
	अचिन्हित पूर्णांक (*src_get_dirty)(व्योम *blk);
	अचिन्हित पूर्णांक (*src_dirty_conj_mask)(व्योम);
	पूर्णांक (*src_mgr_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*src_mgr_put_ctrl_blk)(व्योम *blk);
	/* syncly enable src @idx */
	पूर्णांक (*src_mgr_enbs_src)(व्योम *blk, अचिन्हित पूर्णांक idx);
	/* enable src @idx */
	पूर्णांक (*src_mgr_enb_src)(व्योम *blk, अचिन्हित पूर्णांक idx);
	/* disable src @idx */
	पूर्णांक (*src_mgr_dsb_src)(व्योम *blk, अचिन्हित पूर्णांक idx);
	पूर्णांक (*src_mgr_commit_ग_लिखो)(काष्ठा hw *hw, व्योम *blk);

	/* SRC Input Mapper operations */
	पूर्णांक (*srcimp_mgr_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*srcimp_mgr_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*srcimp_mgr_set_imaparc)(व्योम *blk, अचिन्हित पूर्णांक slot);
	पूर्णांक (*srcimp_mgr_set_imapuser)(व्योम *blk, अचिन्हित पूर्णांक user);
	पूर्णांक (*srcimp_mgr_set_imapnxt)(व्योम *blk, अचिन्हित पूर्णांक next);
	पूर्णांक (*srcimp_mgr_set_imapaddr)(व्योम *blk, अचिन्हित पूर्णांक addr);
	पूर्णांक (*srcimp_mgr_commit_ग_लिखो)(काष्ठा hw *hw, व्योम *blk);

	/* AMIXER operations */
	पूर्णांक (*amixer_rsc_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*amixer_rsc_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*amixer_mgr_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*amixer_mgr_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*amixer_set_mode)(व्योम *blk, अचिन्हित पूर्णांक mode);
	पूर्णांक (*amixer_set_iv)(व्योम *blk, अचिन्हित पूर्णांक iv);
	पूर्णांक (*amixer_set_x)(व्योम *blk, अचिन्हित पूर्णांक x);
	पूर्णांक (*amixer_set_y)(व्योम *blk, अचिन्हित पूर्णांक y);
	पूर्णांक (*amixer_set_sadr)(व्योम *blk, अचिन्हित पूर्णांक sadr);
	पूर्णांक (*amixer_set_se)(व्योम *blk, अचिन्हित पूर्णांक se);
	पूर्णांक (*amixer_set_dirty)(व्योम *blk, अचिन्हित पूर्णांक flags);
	पूर्णांक (*amixer_set_dirty_all)(व्योम *blk);
	पूर्णांक (*amixer_commit_ग_लिखो)(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk);
	पूर्णांक (*amixer_get_y)(व्योम *blk);
	अचिन्हित पूर्णांक (*amixer_get_dirty)(व्योम *blk);

	/* DAIO operations */
	पूर्णांक (*dai_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*dai_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*dai_srt_set_srco)(व्योम *blk, अचिन्हित पूर्णांक src);
	पूर्णांक (*dai_srt_set_srcm)(व्योम *blk, अचिन्हित पूर्णांक src);
	पूर्णांक (*dai_srt_set_rsr)(व्योम *blk, अचिन्हित पूर्णांक rsr);
	पूर्णांक (*dai_srt_set_drat)(व्योम *blk, अचिन्हित पूर्णांक drat);
	पूर्णांक (*dai_srt_set_ec)(व्योम *blk, अचिन्हित पूर्णांक ec);
	पूर्णांक (*dai_srt_set_et)(व्योम *blk, अचिन्हित पूर्णांक et);
	पूर्णांक (*dai_commit_ग_लिखो)(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk);
	पूर्णांक (*dao_get_ctrl_blk)(व्योम **rblk);
	पूर्णांक (*dao_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*dao_set_spos)(व्योम *blk, अचिन्हित पूर्णांक spos);
	पूर्णांक (*dao_commit_ग_लिखो)(काष्ठा hw *hw, अचिन्हित पूर्णांक idx, व्योम *blk);
	पूर्णांक (*dao_get_spos)(व्योम *blk, अचिन्हित पूर्णांक *spos);

	पूर्णांक (*daio_mgr_get_ctrl_blk)(काष्ठा hw *hw, व्योम **rblk);
	पूर्णांक (*daio_mgr_put_ctrl_blk)(व्योम *blk);
	पूर्णांक (*daio_mgr_enb_dai)(व्योम *blk, अचिन्हित पूर्णांक idx);
	पूर्णांक (*daio_mgr_dsb_dai)(व्योम *blk, अचिन्हित पूर्णांक idx);
	पूर्णांक (*daio_mgr_enb_dao)(व्योम *blk, अचिन्हित पूर्णांक idx);
	पूर्णांक (*daio_mgr_dsb_dao)(व्योम *blk, अचिन्हित पूर्णांक idx);
	पूर्णांक (*daio_mgr_dao_init)(व्योम *blk, अचिन्हित पूर्णांक idx,
						अचिन्हित पूर्णांक conf);
	पूर्णांक (*daio_mgr_set_imaparc)(व्योम *blk, अचिन्हित पूर्णांक slot);
	पूर्णांक (*daio_mgr_set_imapnxt)(व्योम *blk, अचिन्हित पूर्णांक next);
	पूर्णांक (*daio_mgr_set_imapaddr)(व्योम *blk, अचिन्हित पूर्णांक addr);
	पूर्णांक (*daio_mgr_commit_ग_लिखो)(काष्ठा hw *hw, व्योम *blk);

	पूर्णांक (*set_समयr_irq)(काष्ठा hw *hw, पूर्णांक enable);
	पूर्णांक (*set_समयr_tick)(काष्ठा hw *hw, अचिन्हित पूर्णांक tick);
	अचिन्हित पूर्णांक (*get_wc)(काष्ठा hw *hw);

	व्योम (*irq_callback)(व्योम *data, अचिन्हित पूर्णांक bit);
	व्योम *irq_callback_data;

	काष्ठा pci_dev *pci;	/* the pci kernel काष्ठाure of this card */
	काष्ठा snd_card *card;	/* poपूर्णांकer to this card */
	पूर्णांक irq;
	अचिन्हित दीर्घ io_base;
	व्योम __iomem *mem_base;

	क्रमागत CHIPTYP chip_type;
	क्रमागत CTCARDS model;
पूर्ण;

पूर्णांक create_hw_obj(काष्ठा pci_dev *pci, क्रमागत CHIPTYP chip_type,
		  क्रमागत CTCARDS model, काष्ठा hw **rhw);
पूर्णांक destroy_hw_obj(काष्ठा hw *hw);

अचिन्हित पूर्णांक get_field(अचिन्हित पूर्णांक data, अचिन्हित पूर्णांक field);
व्योम set_field(अचिन्हित पूर्णांक *data, अचिन्हित पूर्णांक field, अचिन्हित पूर्णांक value);

/* IRQ bits */
#घोषणा	PLL_INT		(1 << 10) /* PLL input-घड़ी out-of-range */
#घोषणा FI_INT		(1 << 9)  /* क्रमced पूर्णांकerrupt */
#घोषणा IT_INT		(1 << 8)  /* समयr पूर्णांकerrupt */
#घोषणा PCI_INT		(1 << 7)  /* PCI bus error pending */
#घोषणा URT_INT		(1 << 6)  /* UART Tx/Rx */
#घोषणा GPI_INT		(1 << 5)  /* GPI pin */
#घोषणा MIX_INT		(1 << 4)  /* mixer parameter segment FIFO channels */
#घोषणा DAI_INT		(1 << 3)  /* DAI (SR-tracker or SPDIF-receiver) */
#घोषणा TP_INT		(1 << 2)  /* transport priority queue */
#घोषणा DSP_INT		(1 << 1)  /* DSP */
#घोषणा SRC_INT		(1 << 0)  /* SRC channels */

#पूर्ण_अगर /* CTHARDWARE_H */
