<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc. All rights reserved.
 *
 * Authors:	Zhao Qiang <qiang.zhao@nxp.com>
 *
 * Description:
 * QE TDM API Set - TDM specअगरic routines implementations.
 */
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <soc/fsl/qe/qe_tdm.h>

अटल पूर्णांक set_tdm_framer(स्थिर अक्षर *tdm_framer_type)
अणु
	अगर (म_भेद(tdm_framer_type, "e1") == 0)
		वापस TDM_FRAMER_E1;
	अन्यथा अगर (म_भेद(tdm_framer_type, "t1") == 0)
		वापस TDM_FRAMER_T1;
	अन्यथा
		वापस -EINVAL;
पूर्ण

अटल व्योम set_si_param(काष्ठा ucc_tdm *utdm, काष्ठा ucc_tdm_info *ut_info)
अणु
	काष्ठा si_mode_info *si_info = &ut_info->si_info;

	अगर (utdm->tdm_mode == TDM_INTERNAL_LOOPBACK) अणु
		si_info->simr_crt = 1;
		si_info->simr_rfsd = 0;
	पूर्ण
पूर्ण

पूर्णांक ucc_of_parse_tdm(काष्ठा device_node *np, काष्ठा ucc_tdm *utdm,
		     काष्ठा ucc_tdm_info *ut_info)
अणु
	स्थिर अक्षर *sprop;
	पूर्णांक ret = 0;
	u32 val;

	sprop = of_get_property(np, "fsl,rx-sync-clock", शून्य);
	अगर (sprop) अणु
		ut_info->uf_info.rx_sync = qe_घड़ी_source(sprop);
		अगर ((ut_info->uf_info.rx_sync < QE_CLK_NONE) ||
		    (ut_info->uf_info.rx_sync > QE_RSYNC_PIN)) अणु
			pr_err("QE-TDM: Invalid rx-sync-clock property\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("QE-TDM: Invalid rx-sync-clock property\n");
		वापस -EINVAL;
	पूर्ण

	sprop = of_get_property(np, "fsl,tx-sync-clock", शून्य);
	अगर (sprop) अणु
		ut_info->uf_info.tx_sync = qe_घड़ी_source(sprop);
		अगर ((ut_info->uf_info.tx_sync < QE_CLK_NONE) ||
		    (ut_info->uf_info.tx_sync > QE_TSYNC_PIN)) अणु
			pr_err("QE-TDM: Invalid tx-sync-clock property\n");
		वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		pr_err("QE-TDM: Invalid tx-sync-clock property\n");
		वापस -EINVAL;
	पूर्ण

	ret = of_property_पढ़ो_u32_index(np, "fsl,tx-timeslot-mask", 0, &val);
	अगर (ret) अणु
		pr_err("QE-TDM: Invalid tx-timeslot-mask property\n");
		वापस -EINVAL;
	पूर्ण
	utdm->tx_ts_mask = val;

	ret = of_property_पढ़ो_u32_index(np, "fsl,rx-timeslot-mask", 0, &val);
	अगर (ret) अणु
		ret = -EINVAL;
		pr_err("QE-TDM: Invalid rx-timeslot-mask property\n");
		वापस ret;
	पूर्ण
	utdm->rx_ts_mask = val;

	ret = of_property_पढ़ो_u32_index(np, "fsl,tdm-id", 0, &val);
	अगर (ret) अणु
		ret = -EINVAL;
		pr_err("QE-TDM: No fsl,tdm-id property for this UCC\n");
		वापस ret;
	पूर्ण
	utdm->tdm_port = val;
	ut_info->uf_info.tdm_num = utdm->tdm_port;

	अगर (of_property_पढ़ो_bool(np, "fsl,tdm-internal-loopback"))
		utdm->tdm_mode = TDM_INTERNAL_LOOPBACK;
	अन्यथा
		utdm->tdm_mode = TDM_NORMAL;

	sprop = of_get_property(np, "fsl,tdm-framer-type", शून्य);
	अगर (!sprop) अणु
		ret = -EINVAL;
		pr_err("QE-TDM: No tdm-framer-type property for UCC\n");
		वापस ret;
	पूर्ण
	ret = set_tdm_framer(sprop);
	अगर (ret < 0)
		वापस -EINVAL;
	utdm->tdm_framer_type = ret;

	ret = of_property_पढ़ो_u32_index(np, "fsl,siram-entry-id", 0, &val);
	अगर (ret) अणु
		ret = -EINVAL;
		pr_err("QE-TDM: No siram entry id for UCC\n");
		वापस ret;
	पूर्ण
	utdm->siram_entry_id = val;

	set_si_param(utdm, ut_info);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ucc_of_parse_tdm);

व्योम ucc_tdm_init(काष्ठा ucc_tdm *utdm, काष्ठा ucc_tdm_info *ut_info)
अणु
	काष्ठा si1 __iomem *si_regs;
	u16 __iomem *siram;
	u16 siram_entry_valid;
	u16 siram_entry_बंदd;
	u16 ucc_num;
	u8 csel;
	u16 sixmr;
	u16 tdm_port;
	u32 siram_entry_id;
	u32 mask;
	पूर्णांक i;

	si_regs = utdm->si_regs;
	siram = utdm->siram;
	ucc_num = ut_info->uf_info.ucc_num;
	tdm_port = utdm->tdm_port;
	siram_entry_id = utdm->siram_entry_id;

	अगर (utdm->tdm_framer_type == TDM_FRAMER_T1)
		utdm->num_of_ts = 24;
	अगर (utdm->tdm_framer_type == TDM_FRAMER_E1)
		utdm->num_of_ts = 32;

	/* set siram table */
	csel = (ucc_num < 4) ? ucc_num + 9 : ucc_num - 3;

	siram_entry_valid = SIR_CSEL(csel) | SIR_BYTE | SIR_CNT(0);
	siram_entry_बंदd = SIR_IDLE | SIR_BYTE | SIR_CNT(0);

	क्रम (i = 0; i < utdm->num_of_ts; i++) अणु
		mask = 0x01 << i;

		अगर (utdm->tx_ts_mask & mask)
			ioग_लिखो16be(siram_entry_valid,
				    &siram[siram_entry_id * 32 + i]);
		अन्यथा
			ioग_लिखो16be(siram_entry_बंदd,
				    &siram[siram_entry_id * 32 + i]);

		अगर (utdm->rx_ts_mask & mask)
			ioग_लिखो16be(siram_entry_valid,
				    &siram[siram_entry_id * 32 + 0x200 +  i]);
		अन्यथा
			ioग_लिखो16be(siram_entry_बंदd,
				    &siram[siram_entry_id * 32 + 0x200 +  i]);
	पूर्ण

	qe_setbits_be16(&siram[(siram_entry_id * 32) + (utdm->num_of_ts - 1)],
			SIR_LAST);
	qe_setbits_be16(&siram[(siram_entry_id * 32) + 0x200 + (utdm->num_of_ts - 1)],
			SIR_LAST);

	/* Set SIxMR रेजिस्टर */
	sixmr = SIMR_SAD(siram_entry_id);

	sixmr &= ~SIMR_SDM_MASK;

	अगर (utdm->tdm_mode == TDM_INTERNAL_LOOPBACK)
		sixmr |= SIMR_SDM_INTERNAL_LOOPBACK;
	अन्यथा
		sixmr |= SIMR_SDM_NORMAL;

	sixmr |= SIMR_RFSD(ut_info->si_info.simr_rfsd) |
			SIMR_TFSD(ut_info->si_info.simr_tfsd);

	अगर (ut_info->si_info.simr_crt)
		sixmr |= SIMR_CRT;
	अगर (ut_info->si_info.simr_sl)
		sixmr |= SIMR_SL;
	अगर (ut_info->si_info.simr_ce)
		sixmr |= SIMR_CE;
	अगर (ut_info->si_info.simr_fe)
		sixmr |= SIMR_FE;
	अगर (ut_info->si_info.simr_gm)
		sixmr |= SIMR_GM;

	चयन (tdm_port) अणु
	हाल 0:
		ioग_लिखो16be(sixmr, &si_regs->sixmr1[0]);
		अवरोध;
	हाल 1:
		ioग_लिखो16be(sixmr, &si_regs->sixmr1[1]);
		अवरोध;
	हाल 2:
		ioग_लिखो16be(sixmr, &si_regs->sixmr1[2]);
		अवरोध;
	हाल 3:
		ioग_लिखो16be(sixmr, &si_regs->sixmr1[3]);
		अवरोध;
	शेष:
		pr_err("QE-TDM: can not find tdm sixmr reg\n");
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ucc_tdm_init);
