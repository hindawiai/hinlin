<शैली गुरु>
/*
 * Intel 5100 Memory Controllers kernel module
 *
 * This file may be distributed under the terms of the
 * GNU General Public License.
 *
 * This module is based on the following करोcument:
 *
 * Intel 5100X Chipset Memory Controller Hub (MCH) - Datasheet
 *      http://करोwnload.पूर्णांकel.com/design/chipsets/datashts/318378.pdf
 *
 * The पूर्णांकel 5100 has two independent channels. EDAC core currently
 * can not reflect this configuration so instead the chip-select
 * rows क्रम each respective channel are laid out one after another,
 * the first half beदीर्घing to channel 0, the second half beदीर्घing
 * to channel 1.
 *
 * This driver is क्रम DDR2 DIMMs, and it uses chip select to select among the
 * several ranks. However, instead of showing memories as ranks, it outमाला_दो
 * them as DIMM's. An पूर्णांकernal table creates the association between ranks
 * and DIMM's.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/pci_ids.h>
#समावेश <linux/edac.h>
#समावेश <linux/delay.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/debugfs.h>

#समावेश "edac_module.h"

/* रेजिस्टर addresses */

/* device 16, func 1 */
#घोषणा I5100_MC		0x40	/* Memory Control Register */
#घोषणा 	I5100_MC_SCRBEN_MASK	(1 << 7)
#घोषणा 	I5100_MC_SCRBDONE_MASK	(1 << 4)
#घोषणा I5100_MS		0x44	/* Memory Status Register */
#घोषणा I5100_SPDDATA		0x48	/* Serial Presence Detect Status Reg */
#घोषणा I5100_SPDCMD		0x4c	/* Serial Presence Detect Command Reg */
#घोषणा I5100_TOLM		0x6c	/* Top of Low Memory */
#घोषणा I5100_MIR0		0x80	/* Memory Interleave Range 0 */
#घोषणा I5100_MIR1		0x84	/* Memory Interleave Range 1 */
#घोषणा I5100_AMIR_0		0x8c	/* Adjusted Memory Interleave Range 0 */
#घोषणा I5100_AMIR_1		0x90	/* Adjusted Memory Interleave Range 1 */
#घोषणा I5100_FERR_NF_MEM	0xa0	/* MC First Non Fatal Errors */
#घोषणा		I5100_FERR_NF_MEM_M16ERR_MASK	(1 << 16)
#घोषणा		I5100_FERR_NF_MEM_M15ERR_MASK	(1 << 15)
#घोषणा		I5100_FERR_NF_MEM_M14ERR_MASK	(1 << 14)
#घोषणा		I5100_FERR_NF_MEM_M12ERR_MASK	(1 << 12)
#घोषणा		I5100_FERR_NF_MEM_M11ERR_MASK	(1 << 11)
#घोषणा		I5100_FERR_NF_MEM_M10ERR_MASK	(1 << 10)
#घोषणा		I5100_FERR_NF_MEM_M6ERR_MASK	(1 << 6)
#घोषणा		I5100_FERR_NF_MEM_M5ERR_MASK	(1 << 5)
#घोषणा		I5100_FERR_NF_MEM_M4ERR_MASK	(1 << 4)
#घोषणा		I5100_FERR_NF_MEM_M1ERR_MASK	(1 << 1)
#घोषणा		I5100_FERR_NF_MEM_ANY_MASK	\
			(I5100_FERR_NF_MEM_M16ERR_MASK | \
			I5100_FERR_NF_MEM_M15ERR_MASK | \
			I5100_FERR_NF_MEM_M14ERR_MASK | \
			I5100_FERR_NF_MEM_M12ERR_MASK | \
			I5100_FERR_NF_MEM_M11ERR_MASK | \
			I5100_FERR_NF_MEM_M10ERR_MASK | \
			I5100_FERR_NF_MEM_M6ERR_MASK | \
			I5100_FERR_NF_MEM_M5ERR_MASK | \
			I5100_FERR_NF_MEM_M4ERR_MASK | \
			I5100_FERR_NF_MEM_M1ERR_MASK)
#घोषणा	I5100_NERR_NF_MEM	0xa4	/* MC Next Non-Fatal Errors */
#घोषणा I5100_EMASK_MEM		0xa8	/* MC Error Mask Register */
#घोषणा I5100_MEM0EINJMSK0	0x200	/* Injection Mask0 Register Channel 0 */
#घोषणा I5100_MEM1EINJMSK0	0x208	/* Injection Mask0 Register Channel 1 */
#घोषणा		I5100_MEMXEINJMSK0_EINJEN	(1 << 27)
#घोषणा I5100_MEM0EINJMSK1	0x204	/* Injection Mask1 Register Channel 0 */
#घोषणा I5100_MEM1EINJMSK1	0x206	/* Injection Mask1 Register Channel 1 */

/* Device 19, Function 0 */
#घोषणा I5100_DINJ0 0x9a

/* device 21 and 22, func 0 */
#घोषणा I5100_MTR_0	0x154	/* Memory Technology Registers 0-3 */
#घोषणा I5100_DMIR	0x15c	/* DIMM Interleave Range */
#घोषणा	I5100_VALIDLOG	0x18c	/* Valid Log Markers */
#घोषणा	I5100_NRECMEMA	0x190	/* Non-Recoverable Memory Error Log Reg A */
#घोषणा	I5100_NRECMEMB	0x194	/* Non-Recoverable Memory Error Log Reg B */
#घोषणा	I5100_REDMEMA	0x198	/* Recoverable Memory Data Error Log Reg A */
#घोषणा	I5100_REDMEMB	0x19c	/* Recoverable Memory Data Error Log Reg B */
#घोषणा	I5100_RECMEMA	0x1a0	/* Recoverable Memory Error Log Reg A */
#घोषणा	I5100_RECMEMB	0x1a4	/* Recoverable Memory Error Log Reg B */
#घोषणा I5100_MTR_4	0x1b0	/* Memory Technology Registers 4,5 */

/* bit field accessors */

अटल अंतरभूत u32 i5100_mc_scrben(u32 mc)
अणु
	वापस mc >> 7 & 1;
पूर्ण

अटल अंतरभूत u32 i5100_mc_errdeten(u32 mc)
अणु
	वापस mc >> 5 & 1;
पूर्ण

अटल अंतरभूत u32 i5100_mc_scrbकरोne(u32 mc)
अणु
	वापस mc >> 4 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_spddata_rकरो(u16 a)
अणु
	वापस a >> 15 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_spddata_sbe(u16 a)
अणु
	वापस a >> 13 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_spddata_busy(u16 a)
अणु
	वापस a >> 12 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_spddata_data(u16 a)
अणु
	वापस a & ((1 << 8) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_spdcmd_create(u32 dti, u32 ckovrd, u32 sa, u32 ba,
				      u32 data, u32 cmd)
अणु
	वापस	((dti & ((1 << 4) - 1))  << 28) |
		((ckovrd & 1)            << 27) |
		((sa & ((1 << 3) - 1))   << 24) |
		((ba & ((1 << 8) - 1))   << 16) |
		((data & ((1 << 8) - 1)) <<  8) |
		(cmd & 1);
पूर्ण

अटल अंतरभूत u16 i5100_tolm_tolm(u16 a)
अणु
	वापस a >> 12 & ((1 << 4) - 1);
पूर्ण

अटल अंतरभूत u16 i5100_mir_limit(u16 a)
अणु
	वापस a >> 4 & ((1 << 12) - 1);
पूर्ण

अटल अंतरभूत u16 i5100_mir_way1(u16 a)
अणु
	वापस a >> 1 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_mir_way0(u16 a)
अणु
	वापस a & 1;
पूर्ण

अटल अंतरभूत u32 i5100_ferr_nf_mem_chan_indx(u32 a)
अणु
	वापस a >> 28 & 1;
पूर्ण

अटल अंतरभूत u32 i5100_ferr_nf_mem_any(u32 a)
अणु
	वापस a & I5100_FERR_NF_MEM_ANY_MASK;
पूर्ण

अटल अंतरभूत u32 i5100_nerr_nf_mem_any(u32 a)
अणु
	वापस i5100_ferr_nf_mem_any(a);
पूर्ण

अटल अंतरभूत u32 i5100_dmir_limit(u32 a)
अणु
	वापस a >> 16 & ((1 << 11) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_dmir_rank(u32 a, u32 i)
अणु
	वापस a >> (4 * i) & ((1 << 2) - 1);
पूर्ण

अटल अंतरभूत u16 i5100_mtr_present(u16 a)
अणु
	वापस a >> 10 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_mtr_ethrottle(u16 a)
अणु
	वापस a >> 9 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_mtr_width(u16 a)
अणु
	वापस a >> 8 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_mtr_numbank(u16 a)
अणु
	वापस a >> 6 & 1;
पूर्ण

अटल अंतरभूत u16 i5100_mtr_numrow(u16 a)
अणु
	वापस a >> 2 & ((1 << 2) - 1);
पूर्ण

अटल अंतरभूत u16 i5100_mtr_numcol(u16 a)
अणु
	वापस a & ((1 << 2) - 1);
पूर्ण


अटल अंतरभूत u32 i5100_validlog_redmemvalid(u32 a)
अणु
	वापस a >> 2 & 1;
पूर्ण

अटल अंतरभूत u32 i5100_validlog_recmemvalid(u32 a)
अणु
	वापस a >> 1 & 1;
पूर्ण

अटल अंतरभूत u32 i5100_validlog_nrecmemvalid(u32 a)
अणु
	वापस a & 1;
पूर्ण

अटल अंतरभूत u32 i5100_nrecmema_merr(u32 a)
अणु
	वापस a >> 15 & ((1 << 5) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_nrecmema_bank(u32 a)
अणु
	वापस a >> 12 & ((1 << 3) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_nrecmema_rank(u32 a)
अणु
	वापस a >>  8 & ((1 << 3) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_nrecmema_dm_buf_id(u32 a)
अणु
	वापस a & ((1 << 8) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_nrecmemb_cas(u32 a)
अणु
	वापस a >> 16 & ((1 << 13) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_nrecmemb_ras(u32 a)
अणु
	वापस a & ((1 << 16) - 1);
पूर्ण

अटल अंतरभूत u32 i5100_recmema_merr(u32 a)
अणु
	वापस i5100_nrecmema_merr(a);
पूर्ण

अटल अंतरभूत u32 i5100_recmema_bank(u32 a)
अणु
	वापस i5100_nrecmema_bank(a);
पूर्ण

अटल अंतरभूत u32 i5100_recmema_rank(u32 a)
अणु
	वापस i5100_nrecmema_rank(a);
पूर्ण

अटल अंतरभूत u32 i5100_recmemb_cas(u32 a)
अणु
	वापस i5100_nrecmemb_cas(a);
पूर्ण

अटल अंतरभूत u32 i5100_recmemb_ras(u32 a)
अणु
	वापस i5100_nrecmemb_ras(a);
पूर्ण

/* some generic limits */
#घोषणा I5100_MAX_RANKS_PER_CHAN	6
#घोषणा I5100_CHANNELS			    2
#घोषणा I5100_MAX_RANKS_PER_DIMM	4
#घोषणा I5100_DIMM_ADDR_LINES		(6 - 3)	/* 64 bits / 8 bits per byte */
#घोषणा I5100_MAX_DIMM_SLOTS_PER_CHAN	4
#घोषणा I5100_MAX_RANK_INTERLEAVE	4
#घोषणा I5100_MAX_DMIRS			5
#घोषणा I5100_SCRUB_REFRESH_RATE	(5 * 60 * HZ)

काष्ठा i5100_priv अणु
	/* ranks on each dimm -- 0 maps to not present -- obtained via SPD */
	पूर्णांक dimm_numrank[I5100_CHANNELS][I5100_MAX_DIMM_SLOTS_PER_CHAN];

	/*
	 * मुख्यboard chip select map -- maps i5100 chip selects to
	 * DIMM slot chip selects.  In the हाल of only 4 ranks per
	 * channel, the mapping is fairly obvious but not unique.
	 * we map -1 -> NC and assume both channels use the same
	 * map...
	 *
	 */
	पूर्णांक dimm_csmap[I5100_MAX_DIMM_SLOTS_PER_CHAN][I5100_MAX_RANKS_PER_DIMM];

	/* memory पूर्णांकerleave range */
	काष्ठा अणु
		u64	 limit;
		अचिन्हित way[2];
	पूर्ण mir[I5100_CHANNELS];

	/* adjusted memory पूर्णांकerleave range रेजिस्टर */
	अचिन्हित amir[I5100_CHANNELS];

	/* dimm पूर्णांकerleave range */
	काष्ठा अणु
		अचिन्हित rank[I5100_MAX_RANK_INTERLEAVE];
		u64	 limit;
	पूर्ण dmir[I5100_CHANNELS][I5100_MAX_DMIRS];

	/* memory technology रेजिस्टरs... */
	काष्ठा अणु
		अचिन्हित present;	/* 0 or 1 */
		अचिन्हित ethrottle;	/* 0 or 1 */
		अचिन्हित width;		/* 4 or 8 bits  */
		अचिन्हित numbank;	/* 2 or 3 lines */
		अचिन्हित numrow;	/* 13 .. 16 lines */
		अचिन्हित numcol;	/* 11 .. 12 lines */
	पूर्ण mtr[I5100_CHANNELS][I5100_MAX_RANKS_PER_CHAN];

	u64 tolm;		/* top of low memory in bytes */
	अचिन्हित ranksperchan;	/* number of ranks per channel */

	काष्ठा pci_dev *mc;	/* device 16 func 1 */
	काष्ठा pci_dev *einj;	/* device 19 func 0 */
	काष्ठा pci_dev *ch0mm;	/* device 21 func 0 */
	काष्ठा pci_dev *ch1mm;	/* device 22 func 0 */

	काष्ठा delayed_work i5100_scrubbing;
	पूर्णांक scrub_enable;

	/* Error injection */
	u8 inject_channel;
	u8 inject_hlinesel;
	u8 inject_deviceptr1;
	u8 inject_deviceptr2;
	u16 inject_eccmask1;
	u16 inject_eccmask2;

	काष्ठा dentry *debugfs;
पूर्ण;

अटल काष्ठा dentry *i5100_debugfs;

/* map a rank/chan to a slot number on the मुख्यboard */
अटल पूर्णांक i5100_rank_to_slot(स्थिर काष्ठा mem_ctl_info *mci,
			      पूर्णांक chan, पूर्णांक rank)
अणु
	स्थिर काष्ठा i5100_priv *priv = mci->pvt_info;
	पूर्णांक i;

	क्रम (i = 0; i < I5100_MAX_DIMM_SLOTS_PER_CHAN; i++) अणु
		पूर्णांक j;
		स्थिर पूर्णांक numrank = priv->dimm_numrank[chan][i];

		क्रम (j = 0; j < numrank; j++)
			अगर (priv->dimm_csmap[i][j] == rank)
				वापस i * 2 + chan;
	पूर्ण

	वापस -1;
पूर्ण

अटल स्थिर अक्षर *i5100_err_msg(अचिन्हित err)
अणु
	अटल स्थिर अक्षर *merrs[] = अणु
		"unknown", /* 0 */
		"uncorrectable data ECC on replay", /* 1 */
		"unknown", /* 2 */
		"unknown", /* 3 */
		"aliased uncorrectable demand data ECC", /* 4 */
		"aliased uncorrectable spare-copy data ECC", /* 5 */
		"aliased uncorrectable patrol data ECC", /* 6 */
		"unknown", /* 7 */
		"unknown", /* 8 */
		"unknown", /* 9 */
		"non-aliased uncorrectable demand data ECC", /* 10 */
		"non-aliased uncorrectable spare-copy data ECC", /* 11 */
		"non-aliased uncorrectable patrol data ECC", /* 12 */
		"unknown", /* 13 */
		"correctable demand data ECC", /* 14 */
		"correctable spare-copy data ECC", /* 15 */
		"correctable patrol data ECC", /* 16 */
		"unknown", /* 17 */
		"SPD protocol error", /* 18 */
		"unknown", /* 19 */
		"spare copy initiated", /* 20 */
		"spare copy completed", /* 21 */
	पूर्ण;
	अचिन्हित i;

	क्रम (i = 0; i < ARRAY_SIZE(merrs); i++)
		अगर (1 << i & err)
			वापस merrs[i];

	वापस "none";
पूर्ण

/* convert csrow index पूर्णांकo a rank (per channel -- 0..5) */
अटल अचिन्हित पूर्णांक i5100_csrow_to_rank(स्थिर काष्ठा mem_ctl_info *mci,
					अचिन्हित पूर्णांक csrow)
अणु
	स्थिर काष्ठा i5100_priv *priv = mci->pvt_info;

	वापस csrow % priv->ranksperchan;
पूर्ण

/* convert csrow index पूर्णांकo a channel (0..1) */
अटल अचिन्हित पूर्णांक i5100_csrow_to_chan(स्थिर काष्ठा mem_ctl_info *mci,
					अचिन्हित पूर्णांक csrow)
अणु
	स्थिर काष्ठा i5100_priv *priv = mci->pvt_info;

	वापस csrow / priv->ranksperchan;
पूर्ण

अटल व्योम i5100_handle_ce(काष्ठा mem_ctl_info *mci,
			    पूर्णांक chan,
			    अचिन्हित bank,
			    अचिन्हित rank,
			    अचिन्हित दीर्घ syndrome,
			    अचिन्हित cas,
			    अचिन्हित ras,
			    स्थिर अक्षर *msg)
अणु
	अक्षर detail[80];

	/* Form out message */
	snम_लिखो(detail, माप(detail),
		 "bank %u, cas %u, ras %u\n",
		 bank, cas, ras);

	edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, 1,
			     0, 0, syndrome,
			     chan, rank, -1,
			     msg, detail);
पूर्ण

अटल व्योम i5100_handle_ue(काष्ठा mem_ctl_info *mci,
			    पूर्णांक chan,
			    अचिन्हित bank,
			    अचिन्हित rank,
			    अचिन्हित दीर्घ syndrome,
			    अचिन्हित cas,
			    अचिन्हित ras,
			    स्थिर अक्षर *msg)
अणु
	अक्षर detail[80];

	/* Form out message */
	snम_लिखो(detail, माप(detail),
		 "bank %u, cas %u, ras %u\n",
		 bank, cas, ras);

	edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
			     0, 0, syndrome,
			     chan, rank, -1,
			     msg, detail);
पूर्ण

अटल व्योम i5100_पढ़ो_log(काष्ठा mem_ctl_info *mci, पूर्णांक chan,
			   u32 ferr, u32 nerr)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	काष्ठा pci_dev *pdev = (chan) ? priv->ch1mm : priv->ch0mm;
	u32 dw;
	u32 dw2;
	अचिन्हित syndrome = 0;
	अचिन्हित merr;
	अचिन्हित bank;
	अचिन्हित rank;
	अचिन्हित cas;
	अचिन्हित ras;

	pci_पढ़ो_config_dword(pdev, I5100_VALIDLOG, &dw);

	अगर (i5100_validlog_redmemvalid(dw)) अणु
		pci_पढ़ो_config_dword(pdev, I5100_REDMEMA, &dw2);
		syndrome = dw2;
		pci_पढ़ो_config_dword(pdev, I5100_REDMEMB, &dw2);
	पूर्ण

	अगर (i5100_validlog_recmemvalid(dw)) अणु
		स्थिर अक्षर *msg;

		pci_पढ़ो_config_dword(pdev, I5100_RECMEMA, &dw2);
		merr = i5100_recmema_merr(dw2);
		bank = i5100_recmema_bank(dw2);
		rank = i5100_recmema_rank(dw2);

		pci_पढ़ो_config_dword(pdev, I5100_RECMEMB, &dw2);
		cas = i5100_recmemb_cas(dw2);
		ras = i5100_recmemb_ras(dw2);

		/* FIXME:  not really sure अगर this is what merr is...
		 */
		अगर (!merr)
			msg = i5100_err_msg(ferr);
		अन्यथा
			msg = i5100_err_msg(nerr);

		i5100_handle_ce(mci, chan, bank, rank, syndrome, cas, ras, msg);
	पूर्ण

	अगर (i5100_validlog_nrecmemvalid(dw)) अणु
		स्थिर अक्षर *msg;

		pci_पढ़ो_config_dword(pdev, I5100_NRECMEMA, &dw2);
		merr = i5100_nrecmema_merr(dw2);
		bank = i5100_nrecmema_bank(dw2);
		rank = i5100_nrecmema_rank(dw2);

		pci_पढ़ो_config_dword(pdev, I5100_NRECMEMB, &dw2);
		cas = i5100_nrecmemb_cas(dw2);
		ras = i5100_nrecmemb_ras(dw2);

		/* FIXME:  not really sure अगर this is what merr is...
		 */
		अगर (!merr)
			msg = i5100_err_msg(ferr);
		अन्यथा
			msg = i5100_err_msg(nerr);

		i5100_handle_ue(mci, chan, bank, rank, syndrome, cas, ras, msg);
	पूर्ण

	pci_ग_लिखो_config_dword(pdev, I5100_VALIDLOG, dw);
पूर्ण

अटल व्योम i5100_check_error(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	u32 dw, dw2;

	pci_पढ़ो_config_dword(priv->mc, I5100_FERR_NF_MEM, &dw);
	अगर (i5100_ferr_nf_mem_any(dw)) अणु

		pci_पढ़ो_config_dword(priv->mc, I5100_NERR_NF_MEM, &dw2);

		i5100_पढ़ो_log(mci, i5100_ferr_nf_mem_chan_indx(dw),
			       i5100_ferr_nf_mem_any(dw),
			       i5100_nerr_nf_mem_any(dw2));

		pci_ग_लिखो_config_dword(priv->mc, I5100_NERR_NF_MEM, dw2);
	पूर्ण
	pci_ग_लिखो_config_dword(priv->mc, I5100_FERR_NF_MEM, dw);
पूर्ण

/* The i5100 chipset will scrub the entire memory once, then
 * set a करोne bit. Continuous scrubbing is achieved by enqueing
 * delayed work to a workqueue, checking every few minutes अगर
 * the scrubbing has completed and अगर so reinitiating it.
 */

अटल व्योम i5100_refresh_scrubbing(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *i5100_scrubbing = to_delayed_work(work);
	काष्ठा i5100_priv *priv = container_of(i5100_scrubbing,
					       काष्ठा i5100_priv,
					       i5100_scrubbing);
	u32 dw;

	pci_पढ़ो_config_dword(priv->mc, I5100_MC, &dw);

	अगर (priv->scrub_enable) अणु

		pci_पढ़ो_config_dword(priv->mc, I5100_MC, &dw);

		अगर (i5100_mc_scrbकरोne(dw)) अणु
			dw |= I5100_MC_SCRBEN_MASK;
			pci_ग_लिखो_config_dword(priv->mc, I5100_MC, dw);
			pci_पढ़ो_config_dword(priv->mc, I5100_MC, &dw);
		पूर्ण

		schedule_delayed_work(&(priv->i5100_scrubbing),
				      I5100_SCRUB_REFRESH_RATE);
	पूर्ण
पूर्ण
/*
 * The bandwidth is based on experimentation, feel मुक्त to refine it.
 */
अटल पूर्णांक i5100_set_scrub_rate(काष्ठा mem_ctl_info *mci, u32 bandwidth)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	u32 dw;

	pci_पढ़ो_config_dword(priv->mc, I5100_MC, &dw);
	अगर (bandwidth) अणु
		priv->scrub_enable = 1;
		dw |= I5100_MC_SCRBEN_MASK;
		schedule_delayed_work(&(priv->i5100_scrubbing),
				      I5100_SCRUB_REFRESH_RATE);
	पूर्ण अन्यथा अणु
		priv->scrub_enable = 0;
		dw &= ~I5100_MC_SCRBEN_MASK;
		cancel_delayed_work(&(priv->i5100_scrubbing));
	पूर्ण
	pci_ग_लिखो_config_dword(priv->mc, I5100_MC, dw);

	pci_पढ़ो_config_dword(priv->mc, I5100_MC, &dw);

	bandwidth = 5900000 * i5100_mc_scrben(dw);

	वापस bandwidth;
पूर्ण

अटल पूर्णांक i5100_get_scrub_rate(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	u32 dw;

	pci_पढ़ो_config_dword(priv->mc, I5100_MC, &dw);

	वापस 5900000 * i5100_mc_scrben(dw);
पूर्ण

अटल काष्ठा pci_dev *pci_get_device_func(अचिन्हित venकरोr,
					   अचिन्हित device,
					   अचिन्हित func)
अणु
	काष्ठा pci_dev *ret = शून्य;

	जबतक (1) अणु
		ret = pci_get_device(venकरोr, device, ret);

		अगर (!ret)
			अवरोध;

		अगर (PCI_FUNC(ret->devfn) == func)
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल अचिन्हित दीर्घ i5100_npages(काष्ठा mem_ctl_info *mci, अचिन्हित पूर्णांक csrow)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	स्थिर अचिन्हित पूर्णांक chan_rank = i5100_csrow_to_rank(mci, csrow);
	स्थिर अचिन्हित पूर्णांक chan = i5100_csrow_to_chan(mci, csrow);
	अचिन्हित addr_lines;

	/* dimm present? */
	अगर (!priv->mtr[chan][chan_rank].present)
		वापस 0ULL;

	addr_lines =
		I5100_DIMM_ADDR_LINES +
		priv->mtr[chan][chan_rank].numcol +
		priv->mtr[chan][chan_rank].numrow +
		priv->mtr[chan][chan_rank].numbank;

	वापस (अचिन्हित दीर्घ)
		((अचिन्हित दीर्घ दीर्घ) (1ULL << addr_lines) / PAGE_SIZE);
पूर्ण

अटल व्योम i5100_init_mtr(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	काष्ठा pci_dev *mms[2] = अणु priv->ch0mm, priv->ch1mm पूर्ण;
	पूर्णांक i;

	क्रम (i = 0; i < I5100_CHANNELS; i++) अणु
		पूर्णांक j;
		काष्ठा pci_dev *pdev = mms[i];

		क्रम (j = 0; j < I5100_MAX_RANKS_PER_CHAN; j++) अणु
			स्थिर अचिन्हित addr =
				(j < 4) ? I5100_MTR_0 + j * 2 :
					  I5100_MTR_4 + (j - 4) * 2;
			u16 w;

			pci_पढ़ो_config_word(pdev, addr, &w);

			priv->mtr[i][j].present = i5100_mtr_present(w);
			priv->mtr[i][j].ethrottle = i5100_mtr_ethrottle(w);
			priv->mtr[i][j].width = 4 + 4 * i5100_mtr_width(w);
			priv->mtr[i][j].numbank = 2 + i5100_mtr_numbank(w);
			priv->mtr[i][j].numrow = 13 + i5100_mtr_numrow(w);
			priv->mtr[i][j].numcol = 10 + i5100_mtr_numcol(w);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * FIXME: make this पूर्णांकo a real i2c adapter (so that dimm-decode
 * will work)?
 */
अटल पूर्णांक i5100_पढ़ो_spd_byte(स्थिर काष्ठा mem_ctl_info *mci,
			       u8 ch, u8 slot, u8 addr, u8 *byte)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	u16 w;

	pci_पढ़ो_config_word(priv->mc, I5100_SPDDATA, &w);
	अगर (i5100_spddata_busy(w))
		वापस -1;

	pci_ग_लिखो_config_dword(priv->mc, I5100_SPDCMD,
			       i5100_spdcmd_create(0xa, 1, ch * 4 + slot, addr,
						   0, 0));

	/* रुको up to 100ms */
	udelay(100);
	जबतक (1) अणु
		pci_पढ़ो_config_word(priv->mc, I5100_SPDDATA, &w);
		अगर (!i5100_spddata_busy(w))
			अवरोध;
		udelay(100);
	पूर्ण

	अगर (!i5100_spddata_rकरो(w) || i5100_spddata_sbe(w))
		वापस -1;

	*byte = i5100_spddata_data(w);

	वापस 0;
पूर्ण

/*
 * fill dimm chip select map
 *
 * FIXME:
 *   o not the only way to may chip selects to dimm slots
 *   o investigate अगर there is some way to obtain this map from the bios
 */
अटल व्योम i5100_init_dimm_csmap(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	पूर्णांक i;

	क्रम (i = 0; i < I5100_MAX_DIMM_SLOTS_PER_CHAN; i++) अणु
		पूर्णांक j;

		क्रम (j = 0; j < I5100_MAX_RANKS_PER_DIMM; j++)
			priv->dimm_csmap[i][j] = -1; /* शेष NC */
	पूर्ण

	/* only 2 chip selects per slot... */
	अगर (priv->ranksperchan == 4) अणु
		priv->dimm_csmap[0][0] = 0;
		priv->dimm_csmap[0][1] = 3;
		priv->dimm_csmap[1][0] = 1;
		priv->dimm_csmap[1][1] = 2;
		priv->dimm_csmap[2][0] = 2;
		priv->dimm_csmap[3][0] = 3;
	पूर्ण अन्यथा अणु
		priv->dimm_csmap[0][0] = 0;
		priv->dimm_csmap[0][1] = 1;
		priv->dimm_csmap[1][0] = 2;
		priv->dimm_csmap[1][1] = 3;
		priv->dimm_csmap[2][0] = 4;
		priv->dimm_csmap[2][1] = 5;
	पूर्ण
पूर्ण

अटल व्योम i5100_init_dimm_layout(काष्ठा pci_dev *pdev,
				   काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	पूर्णांक i;

	क्रम (i = 0; i < I5100_CHANNELS; i++) अणु
		पूर्णांक j;

		क्रम (j = 0; j < I5100_MAX_DIMM_SLOTS_PER_CHAN; j++) अणु
			u8 rank;

			अगर (i5100_पढ़ो_spd_byte(mci, i, j, 5, &rank) < 0)
				priv->dimm_numrank[i][j] = 0;
			अन्यथा
				priv->dimm_numrank[i][j] = (rank & 3) + 1;
		पूर्ण
	पूर्ण

	i5100_init_dimm_csmap(mci);
पूर्ण

अटल व्योम i5100_init_पूर्णांकerleaving(काष्ठा pci_dev *pdev,
				    काष्ठा mem_ctl_info *mci)
अणु
	u16 w;
	u32 dw;
	काष्ठा i5100_priv *priv = mci->pvt_info;
	काष्ठा pci_dev *mms[2] = अणु priv->ch0mm, priv->ch1mm पूर्ण;
	पूर्णांक i;

	pci_पढ़ो_config_word(pdev, I5100_TOLM, &w);
	priv->tolm = (u64) i5100_tolm_tolm(w) * 256 * 1024 * 1024;

	pci_पढ़ो_config_word(pdev, I5100_MIR0, &w);
	priv->mir[0].limit = (u64) i5100_mir_limit(w) << 28;
	priv->mir[0].way[1] = i5100_mir_way1(w);
	priv->mir[0].way[0] = i5100_mir_way0(w);

	pci_पढ़ो_config_word(pdev, I5100_MIR1, &w);
	priv->mir[1].limit = (u64) i5100_mir_limit(w) << 28;
	priv->mir[1].way[1] = i5100_mir_way1(w);
	priv->mir[1].way[0] = i5100_mir_way0(w);

	pci_पढ़ो_config_word(pdev, I5100_AMIR_0, &w);
	priv->amir[0] = w;
	pci_पढ़ो_config_word(pdev, I5100_AMIR_1, &w);
	priv->amir[1] = w;

	क्रम (i = 0; i < I5100_CHANNELS; i++) अणु
		पूर्णांक j;

		क्रम (j = 0; j < 5; j++) अणु
			पूर्णांक k;

			pci_पढ़ो_config_dword(mms[i], I5100_DMIR + j * 4, &dw);

			priv->dmir[i][j].limit =
				(u64) i5100_dmir_limit(dw) << 28;
			क्रम (k = 0; k < I5100_MAX_RANKS_PER_DIMM; k++)
				priv->dmir[i][j].rank[k] =
					i5100_dmir_rank(dw, k);
		पूर्ण
	पूर्ण

	i5100_init_mtr(mci);
पूर्ण

अटल व्योम i5100_init_csrows(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	काष्ठा dimm_info *dimm;

	mci_क्रम_each_dimm(mci, dimm) अणु
		स्थिर अचिन्हित दीर्घ npages = i5100_npages(mci, dimm->idx);
		स्थिर अचिन्हित पूर्णांक chan = i5100_csrow_to_chan(mci, dimm->idx);
		स्थिर अचिन्हित पूर्णांक rank = i5100_csrow_to_rank(mci, dimm->idx);

		अगर (!npages)
			जारी;

		dimm->nr_pages = npages;
		dimm->grain = 32;
		dimm->dtype = (priv->mtr[chan][rank].width == 4) ?
				DEV_X4 : DEV_X8;
		dimm->mtype = MEM_RDDR2;
		dimm->edac_mode = EDAC_SECDED;
		snम_लिखो(dimm->label, माप(dimm->label), "DIMM%u",
			 i5100_rank_to_slot(mci, chan, rank));

		edac_dbg(2, "dimm channel %d, rank %d, size %ld\n",
			 chan, rank, (दीर्घ)PAGES_TO_MiB(npages));
	पूर्ण
पूर्ण

/****************************************************************************
 *                       Error injection routines
 ****************************************************************************/

अटल व्योम i5100_करो_inject(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;
	u32 mask0;
	u16 mask1;

	/* MEM[1:0]EINJMSK0
	 * 31    - ADDRMATCHEN
	 * 29:28 - HLINESEL
	 *         00 Reserved
	 *         01 Lower half of cache line
	 *         10 Upper half of cache line
	 *         11 Both upper and lower parts of cache line
	 * 27    - EINJEN
	 * 25:19 - XORMASK1 क्रम deviceptr1
	 * 9:5   - SEC2RAM क्रम deviceptr2
	 * 4:0   - FIR2RAM क्रम deviceptr1
	 */
	mask0 = ((priv->inject_hlinesel & 0x3) << 28) |
		I5100_MEMXEINJMSK0_EINJEN |
		((priv->inject_eccmask1 & 0xffff) << 10) |
		((priv->inject_deviceptr2 & 0x1f) << 5) |
		(priv->inject_deviceptr1 & 0x1f);

	/* MEM[1:0]EINJMSK1
	 * 15:0  - XORMASK2 क्रम deviceptr2
	 */
	mask1 = priv->inject_eccmask2;

	अगर (priv->inject_channel == 0) अणु
		pci_ग_लिखो_config_dword(priv->mc, I5100_MEM0EINJMSK0, mask0);
		pci_ग_लिखो_config_word(priv->mc, I5100_MEM0EINJMSK1, mask1);
	पूर्ण अन्यथा अणु
		pci_ग_लिखो_config_dword(priv->mc, I5100_MEM1EINJMSK0, mask0);
		pci_ग_लिखो_config_word(priv->mc, I5100_MEM1EINJMSK1, mask1);
	पूर्ण

	/* Error Injection Response Function
	 * Intel 5100 Memory Controller Hub Chipset (318378) datasheet
	 * hपूर्णांकs about this रेजिस्टर but carry no data about them. All
	 * data regarding device 19 is based on experimentation and the
	 * Intel 7300 Chipset Memory Controller Hub (318082) datasheet
	 * which appears to be accurate क्रम the i5100 in this area.
	 *
	 * The injection code करोn't work without setting this रेजिस्टर.
	 * The रेजिस्टर needs to be flipped off then on अन्यथा the hardware
	 * will only preक्रमm the first injection.
	 *
	 * Stop condition bits 7:4
	 * 1010 - Stop after one injection
	 * 1011 - Never stop injecting faults
	 *
	 * Start condition bits 3:0
	 * 1010 - Never start
	 * 1011 - Start immediately
	 */
	pci_ग_लिखो_config_byte(priv->einj, I5100_DINJ0, 0xaa);
	pci_ग_लिखो_config_byte(priv->einj, I5100_DINJ0, 0xab);
पूर्ण

#घोषणा to_mci(k) container_of(k, काष्ठा mem_ctl_info, dev)
अटल sमाप_प्रकार inject_enable_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *data,
		माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा device *dev = file->निजी_data;
	काष्ठा mem_ctl_info *mci = to_mci(dev);

	i5100_करो_inject(mci);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations i5100_inject_enable_fops = अणु
	.खोलो = simple_खोलो,
	.ग_लिखो = inject_enable_ग_लिखो,
	.llseek = generic_file_llseek,
पूर्ण;

अटल पूर्णांक i5100_setup_debugfs(काष्ठा mem_ctl_info *mci)
अणु
	काष्ठा i5100_priv *priv = mci->pvt_info;

	अगर (!i5100_debugfs)
		वापस -ENODEV;

	priv->debugfs = edac_debugfs_create_dir_at(mci->bus->name, i5100_debugfs);

	अगर (!priv->debugfs)
		वापस -ENOMEM;

	edac_debugfs_create_x8("inject_channel", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_channel);
	edac_debugfs_create_x8("inject_hlinesel", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_hlinesel);
	edac_debugfs_create_x8("inject_deviceptr1", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_deviceptr1);
	edac_debugfs_create_x8("inject_deviceptr2", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_deviceptr2);
	edac_debugfs_create_x16("inject_eccmask1", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_eccmask1);
	edac_debugfs_create_x16("inject_eccmask2", S_IRUGO | S_IWUSR, priv->debugfs,
				&priv->inject_eccmask2);
	edac_debugfs_create_file("inject_enable", S_IWUSR, priv->debugfs,
				&mci->dev, &i5100_inject_enable_fops);

	वापस 0;

पूर्ण

अटल पूर्णांक i5100_init_one(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *id)
अणु
	पूर्णांक rc;
	काष्ठा mem_ctl_info *mci;
	काष्ठा edac_mc_layer layers[2];
	काष्ठा i5100_priv *priv;
	काष्ठा pci_dev *ch0mm, *ch1mm, *einj;
	पूर्णांक ret = 0;
	u32 dw;
	पूर्णांक ranksperch;

	अगर (PCI_FUNC(pdev->devfn) != 1)
		वापस -ENODEV;

	rc = pci_enable_device(pdev);
	अगर (rc < 0) अणु
		ret = rc;
		जाओ bail;
	पूर्ण

	/* ECC enabled? */
	pci_पढ़ो_config_dword(pdev, I5100_MC, &dw);
	अगर (!i5100_mc_errdeten(dw)) अणु
		prपूर्णांकk(KERN_INFO "i5100_edac: ECC not enabled.\n");
		ret = -ENODEV;
		जाओ bail_pdev;
	पूर्ण

	/* figure out how many ranks, from strapped state of 48GB_Mode input */
	pci_पढ़ो_config_dword(pdev, I5100_MS, &dw);
	ranksperch = !!(dw & (1 << 8)) * 2 + 4;

	/* enable error reporting... */
	pci_पढ़ो_config_dword(pdev, I5100_EMASK_MEM, &dw);
	dw &= ~I5100_FERR_NF_MEM_ANY_MASK;
	pci_ग_लिखो_config_dword(pdev, I5100_EMASK_MEM, dw);

	/* device 21, func 0, Channel 0 Memory Map, Error Flag/Mask, etc... */
	ch0mm = pci_get_device_func(PCI_VENDOR_ID_INTEL,
				    PCI_DEVICE_ID_INTEL_5100_21, 0);
	अगर (!ch0mm) अणु
		ret = -ENODEV;
		जाओ bail_pdev;
	पूर्ण

	rc = pci_enable_device(ch0mm);
	अगर (rc < 0) अणु
		ret = rc;
		जाओ bail_ch0;
	पूर्ण

	/* device 22, func 0, Channel 1 Memory Map, Error Flag/Mask, etc... */
	ch1mm = pci_get_device_func(PCI_VENDOR_ID_INTEL,
				    PCI_DEVICE_ID_INTEL_5100_22, 0);
	अगर (!ch1mm) अणु
		ret = -ENODEV;
		जाओ bail_disable_ch0;
	पूर्ण

	rc = pci_enable_device(ch1mm);
	अगर (rc < 0) अणु
		ret = rc;
		जाओ bail_ch1;
	पूर्ण

	layers[0].type = EDAC_MC_LAYER_CHANNEL;
	layers[0].size = 2;
	layers[0].is_virt_csrow = false;
	layers[1].type = EDAC_MC_LAYER_SLOT;
	layers[1].size = ranksperch;
	layers[1].is_virt_csrow = true;
	mci = edac_mc_alloc(0, ARRAY_SIZE(layers), layers,
			    माप(*priv));
	अगर (!mci) अणु
		ret = -ENOMEM;
		जाओ bail_disable_ch1;
	पूर्ण


	/* device 19, func 0, Error injection */
	einj = pci_get_device_func(PCI_VENDOR_ID_INTEL,
				    PCI_DEVICE_ID_INTEL_5100_19, 0);
	अगर (!einj) अणु
		ret = -ENODEV;
		जाओ bail_mc_मुक्त;
	पूर्ण

	rc = pci_enable_device(einj);
	अगर (rc < 0) अणु
		ret = rc;
		जाओ bail_einj;
	पूर्ण

	mci->pdev = &pdev->dev;

	priv = mci->pvt_info;
	priv->ranksperchan = ranksperch;
	priv->mc = pdev;
	priv->ch0mm = ch0mm;
	priv->ch1mm = ch1mm;
	priv->einj = einj;

	INIT_DELAYED_WORK(&(priv->i5100_scrubbing), i5100_refresh_scrubbing);

	/* If scrubbing was alपढ़ोy enabled by the bios, start मुख्यtaining it */
	pci_पढ़ो_config_dword(pdev, I5100_MC, &dw);
	अगर (i5100_mc_scrben(dw)) अणु
		priv->scrub_enable = 1;
		schedule_delayed_work(&(priv->i5100_scrubbing),
				      I5100_SCRUB_REFRESH_RATE);
	पूर्ण

	i5100_init_dimm_layout(pdev, mci);
	i5100_init_पूर्णांकerleaving(pdev, mci);

	mci->mtype_cap = MEM_FLAG_FB_DDR2;
	mci->edac_ctl_cap = EDAC_FLAG_SECDED;
	mci->edac_cap = EDAC_FLAG_SECDED;
	mci->mod_name = "i5100_edac.c";
	mci->ctl_name = "i5100";
	mci->dev_name = pci_name(pdev);
	mci->ctl_page_to_phys = शून्य;

	mci->edac_check = i5100_check_error;
	mci->set_sdram_scrub_rate = i5100_set_scrub_rate;
	mci->get_sdram_scrub_rate = i5100_get_scrub_rate;

	priv->inject_channel = 0;
	priv->inject_hlinesel = 0;
	priv->inject_deviceptr1 = 0;
	priv->inject_deviceptr2 = 0;
	priv->inject_eccmask1 = 0;
	priv->inject_eccmask2 = 0;

	i5100_init_csrows(mci);

	/* this strange स्थिरruction seems to be in every driver, dunno why */
	चयन (edac_op_state) अणु
	हाल EDAC_OPSTATE_POLL:
	हाल EDAC_OPSTATE_NMI:
		अवरोध;
	शेष:
		edac_op_state = EDAC_OPSTATE_POLL;
		अवरोध;
	पूर्ण

	अगर (edac_mc_add_mc(mci)) अणु
		ret = -ENODEV;
		जाओ bail_scrub;
	पूर्ण

	i5100_setup_debugfs(mci);

	वापस ret;

bail_scrub:
	priv->scrub_enable = 0;
	cancel_delayed_work_sync(&(priv->i5100_scrubbing));
	pci_disable_device(einj);

bail_einj:
	pci_dev_put(einj);

bail_mc_मुक्त:
	edac_mc_मुक्त(mci);

bail_disable_ch1:
	pci_disable_device(ch1mm);

bail_ch1:
	pci_dev_put(ch1mm);

bail_disable_ch0:
	pci_disable_device(ch0mm);

bail_ch0:
	pci_dev_put(ch0mm);

bail_pdev:
	pci_disable_device(pdev);

bail:
	वापस ret;
पूर्ण

अटल व्योम i5100_हटाओ_one(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mem_ctl_info *mci;
	काष्ठा i5100_priv *priv;

	mci = edac_mc_del_mc(&pdev->dev);

	अगर (!mci)
		वापस;

	priv = mci->pvt_info;

	edac_debugfs_हटाओ_recursive(priv->debugfs);

	priv->scrub_enable = 0;
	cancel_delayed_work_sync(&(priv->i5100_scrubbing));

	pci_disable_device(pdev);
	pci_disable_device(priv->ch0mm);
	pci_disable_device(priv->ch1mm);
	pci_disable_device(priv->einj);
	pci_dev_put(priv->ch0mm);
	pci_dev_put(priv->ch1mm);
	pci_dev_put(priv->einj);

	edac_mc_मुक्त(mci);
पूर्ण

अटल स्थिर काष्ठा pci_device_id i5100_pci_tbl[] = अणु
	/* Device 16, Function 0, Channel 0 Memory Map, Error Flag/Mask, ... */
	अणु PCI_DEVICE(PCI_VENDOR_ID_INTEL, PCI_DEVICE_ID_INTEL_5100_16) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, i5100_pci_tbl);

अटल काष्ठा pci_driver i5100_driver = अणु
	.name = KBUILD_BASENAME,
	.probe = i5100_init_one,
	.हटाओ = i5100_हटाओ_one,
	.id_table = i5100_pci_tbl,
पूर्ण;

अटल पूर्णांक __init i5100_init(व्योम)
अणु
	पूर्णांक pci_rc;

	i5100_debugfs = edac_debugfs_create_dir_at("i5100_edac", शून्य);

	pci_rc = pci_रेजिस्टर_driver(&i5100_driver);
	वापस (pci_rc < 0) ? pci_rc : 0;
पूर्ण

अटल व्योम __निकास i5100_निकास(व्योम)
अणु
	edac_debugfs_हटाओ(i5100_debugfs);

	pci_unरेजिस्टर_driver(&i5100_driver);
पूर्ण

module_init(i5100_init);
module_निकास(i5100_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR
    ("Arthur Jones <ajones@riverbed.com>");
MODULE_DESCRIPTION("MC Driver for Intel I5100 memory controllers");
