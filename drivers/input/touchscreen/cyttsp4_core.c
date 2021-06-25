<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * cyttsp4_core.c
 * Cypress TrueTouch(TM) Standard Product V4 Core driver module.
 * For use with Cypress Txx4xx parts.
 * Supported parts include:
 * TMA4XX
 * TMA1036
 *
 * Copyright (C) 2012 Cypress Semiconductor
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 */

#समावेश "cyttsp4_core.h"
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/input/mt.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>

/* Timeout in ms. */
#घोषणा CY_CORE_REQUEST_EXCLUSIVE_TIMEOUT	500
#घोषणा CY_CORE_SLEEP_REQUEST_EXCLUSIVE_TIMEOUT	5000
#घोषणा CY_CORE_MODE_CHANGE_TIMEOUT		1000
#घोषणा CY_CORE_RESET_AND_WAIT_TIMEOUT		500
#घोषणा CY_CORE_WAKEUP_TIMEOUT			500

#घोषणा CY_CORE_STARTUP_RETRY_COUNT		3

अटल स्थिर अक्षर * स्थिर cyttsp4_tch_असल_string[] = अणु
	[CY_TCH_X]	= "X",
	[CY_TCH_Y]	= "Y",
	[CY_TCH_P]	= "P",
	[CY_TCH_T]	= "T",
	[CY_TCH_E]	= "E",
	[CY_TCH_O]	= "O",
	[CY_TCH_W]	= "W",
	[CY_TCH_MAJ]	= "MAJ",
	[CY_TCH_MIN]	= "MIN",
	[CY_TCH_OR]	= "OR",
	[CY_TCH_NUM_ABS] = "INVALID"
पूर्ण;

अटल स्थिर u8 ldr_निकास[] = अणु
	0xFF, 0x01, 0x3B, 0x00, 0x00, 0x4F, 0x6D, 0x17
पूर्ण;

अटल स्थिर u8 ldr_err_app[] = अणु
	0x01, 0x02, 0x00, 0x00, 0x55, 0xDD, 0x17
पूर्ण;

अटल अंतरभूत माप_प्रकार merge_bytes(u8 high, u8 low)
अणु
	वापस (high << 8) + low;
पूर्ण

#अगर_घोषित VERBOSE_DEBUG
अटल व्योम cyttsp4_pr_buf(काष्ठा device *dev, u8 *pr_buf, u8 *dptr, पूर्णांक size,
		स्थिर अक्षर *data_name)
अणु
	पूर्णांक i, k;
	स्थिर अक्षर fmt[] = "%02X ";
	पूर्णांक max;

	अगर (!size)
		वापस;

	max = (CY_MAX_PRBUF_SIZE - 1) - माप(CY_PR_TRUNCATED);

	pr_buf[0] = 0;
	क्रम (i = k = 0; i < size && k < max; i++, k += 3)
		scnम_लिखो(pr_buf + k, CY_MAX_PRBUF_SIZE, fmt, dptr[i]);

	dev_vdbg(dev, "%s:  %s[0..%d]=%s%s\n", __func__, data_name, size - 1,
			pr_buf, size <= max ? "" : CY_PR_TRUNCATED);
पूर्ण
#अन्यथा
#घोषणा cyttsp4_pr_buf(dev, pr_buf, dptr, size, data_name) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

अटल पूर्णांक cyttsp4_load_status_regs(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	काष्ठा device *dev = cd->dev;
	पूर्णांक rc;

	rc = cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, si->si_ofs.mode_size,
			si->xy_mode);
	अगर (rc < 0)
		dev_err(dev, "%s: fail read mode regs r=%d\n",
			__func__, rc);
	अन्यथा
		cyttsp4_pr_buf(dev, cd->pr_buf, si->xy_mode,
			si->si_ofs.mode_size, "xy_mode");

	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_handshake(काष्ठा cyttsp4 *cd, u8 mode)
अणु
	u8 cmd = mode ^ CY_HST_TOGGLE;
	पूर्णांक rc;

	/*
	 * Mode change issued, handshaking now will cause endless mode change
	 * requests, क्रम sync mode modechange will करो same with handshake
	 * */
	अगर (mode & CY_HST_MODE_CHANGE)
		वापस 0;

	rc = cyttsp4_adap_ग_लिखो(cd, CY_REG_BASE, माप(cmd), &cmd);
	अगर (rc < 0)
		dev_err(cd->dev, "%s: bus write fail on handshake (ret=%d)\n",
				__func__, rc);

	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_hw_soft_reset(काष्ठा cyttsp4 *cd)
अणु
	u8 cmd = CY_HST_RESET;
	पूर्णांक rc = cyttsp4_adap_ग_लिखो(cd, CY_REG_BASE, माप(cmd), &cmd);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: FAILED to execute SOFT reset\n",
				__func__);
		वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp4_hw_hard_reset(काष्ठा cyttsp4 *cd)
अणु
	अगर (cd->cpdata->xres) अणु
		cd->cpdata->xres(cd->cpdata, cd->dev);
		dev_dbg(cd->dev, "%s: execute HARD reset\n", __func__);
		वापस 0;
	पूर्ण
	dev_err(cd->dev, "%s: FAILED to execute HARD reset\n", __func__);
	वापस -ENOSYS;
पूर्ण

अटल पूर्णांक cyttsp4_hw_reset(काष्ठा cyttsp4 *cd)
अणु
	पूर्णांक rc = cyttsp4_hw_hard_reset(cd);
	अगर (rc == -ENOSYS)
		rc = cyttsp4_hw_soft_reset(cd);
	वापस rc;
पूर्ण

/*
 * Gets number of bits क्रम a touch filed as parameter,
 * sets maximum value क्रम field which is used as bit mask
 * and वापसs number of bytes required क्रम that field
 */
अटल पूर्णांक cyttsp4_bits_2_bytes(अचिन्हित पूर्णांक nbits, माप_प्रकार *max)
अणु
	*max = 1UL << nbits;
	वापस (nbits + 7) / 8;
पूर्ण

अटल पूर्णांक cyttsp4_si_data_offsets(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	पूर्णांक rc = cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, माप(si->si_data),
			&si->si_data);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read sysinfo data offsets r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	/* Prपूर्णांक sysinfo data offsets */
	cyttsp4_pr_buf(cd->dev, cd->pr_buf, (u8 *)&si->si_data,
		       माप(si->si_data), "sysinfo_data_offsets");

	/* convert sysinfo data offset bytes पूर्णांकo पूर्णांकegers */

	si->si_ofs.map_sz = merge_bytes(si->si_data.map_szh,
			si->si_data.map_szl);
	si->si_ofs.map_sz = merge_bytes(si->si_data.map_szh,
			si->si_data.map_szl);
	si->si_ofs.cydata_ofs = merge_bytes(si->si_data.cydata_ofsh,
			si->si_data.cydata_ofsl);
	si->si_ofs.test_ofs = merge_bytes(si->si_data.test_ofsh,
			si->si_data.test_ofsl);
	si->si_ofs.pcfg_ofs = merge_bytes(si->si_data.pcfg_ofsh,
			si->si_data.pcfg_ofsl);
	si->si_ofs.opcfg_ofs = merge_bytes(si->si_data.opcfg_ofsh,
			si->si_data.opcfg_ofsl);
	si->si_ofs.ddata_ofs = merge_bytes(si->si_data.ddata_ofsh,
			si->si_data.ddata_ofsl);
	si->si_ofs.mdata_ofs = merge_bytes(si->si_data.mdata_ofsh,
			si->si_data.mdata_ofsl);
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_cydata(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	पूर्णांक पढ़ो_offset;
	पूर्णांक mfgid_sz, calc_mfgid_sz;
	व्योम *p;
	पूर्णांक rc;

	अगर (si->si_ofs.test_ofs <= si->si_ofs.cydata_ofs) अणु
		dev_err(cd->dev,
			"%s: invalid offset test_ofs: %zu, cydata_ofs: %zu\n",
			__func__, si->si_ofs.test_ofs, si->si_ofs.cydata_ofs);
		वापस -EINVAL;
	पूर्ण

	si->si_ofs.cydata_size = si->si_ofs.test_ofs - si->si_ofs.cydata_ofs;
	dev_dbg(cd->dev, "%s: cydata size: %zd\n", __func__,
			si->si_ofs.cydata_size);

	p = kपुनः_स्मृति(si->si_ptrs.cydata, si->si_ofs.cydata_size, GFP_KERNEL);
	अगर (p == शून्य) अणु
		dev_err(cd->dev, "%s: failed to allocate cydata memory\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	si->si_ptrs.cydata = p;

	पढ़ो_offset = si->si_ofs.cydata_ofs;

	/* Read the CYDA रेजिस्टरs up to MFGID field */
	rc = cyttsp4_adap_पढ़ो(cd, पढ़ो_offset,
			दुरत्व(काष्ठा cyttsp4_cydata, mfgid_sz)
				+ माप(si->si_ptrs.cydata->mfgid_sz),
			si->si_ptrs.cydata);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read cydata r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	/* Check MFGID size */
	mfgid_sz = si->si_ptrs.cydata->mfgid_sz;
	calc_mfgid_sz = si->si_ofs.cydata_size - माप(काष्ठा cyttsp4_cydata);
	अगर (mfgid_sz != calc_mfgid_sz) अणु
		dev_err(cd->dev, "%s: mismatch in MFGID size, reported:%d calculated:%d\n",
			__func__, mfgid_sz, calc_mfgid_sz);
		वापस -EINVAL;
	पूर्ण

	पढ़ो_offset += दुरत्व(काष्ठा cyttsp4_cydata, mfgid_sz)
			+ माप(si->si_ptrs.cydata->mfgid_sz);

	/* Read the CYDA रेजिस्टरs क्रम MFGID field */
	rc = cyttsp4_adap_पढ़ो(cd, पढ़ो_offset, si->si_ptrs.cydata->mfgid_sz,
			si->si_ptrs.cydata->mfg_id);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read cydata r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	पढ़ो_offset += si->si_ptrs.cydata->mfgid_sz;

	/* Read the rest of the CYDA रेजिस्टरs */
	rc = cyttsp4_adap_पढ़ो(cd, पढ़ो_offset,
			माप(काष्ठा cyttsp4_cydata)
				- दुरत्व(काष्ठा cyttsp4_cydata, cyito_idh),
			&si->si_ptrs.cydata->cyito_idh);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read cydata r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	cyttsp4_pr_buf(cd->dev, cd->pr_buf, (u8 *)si->si_ptrs.cydata,
		si->si_ofs.cydata_size, "sysinfo_cydata");
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_test_data(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	व्योम *p;
	पूर्णांक rc;

	अगर (si->si_ofs.pcfg_ofs <= si->si_ofs.test_ofs) अणु
		dev_err(cd->dev,
			"%s: invalid offset pcfg_ofs: %zu, test_ofs: %zu\n",
			__func__, si->si_ofs.pcfg_ofs, si->si_ofs.test_ofs);
		वापस -EINVAL;
	पूर्ण

	si->si_ofs.test_size = si->si_ofs.pcfg_ofs - si->si_ofs.test_ofs;

	p = kपुनः_स्मृति(si->si_ptrs.test, si->si_ofs.test_size, GFP_KERNEL);
	अगर (p == शून्य) अणु
		dev_err(cd->dev, "%s: failed to allocate test memory\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	si->si_ptrs.test = p;

	rc = cyttsp4_adap_पढ़ो(cd, si->si_ofs.test_ofs, si->si_ofs.test_size,
			si->si_ptrs.test);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read test data r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	cyttsp4_pr_buf(cd->dev, cd->pr_buf,
		       (u8 *)si->si_ptrs.test, si->si_ofs.test_size,
		       "sysinfo_test_data");
	अगर (si->si_ptrs.test->post_codel &
	    CY_POST_CODEL_WDG_RST)
		dev_info(cd->dev, "%s: %s codel=%02X\n",
			 __func__, "Reset was a WATCHDOG RESET",
			 si->si_ptrs.test->post_codel);

	अगर (!(si->si_ptrs.test->post_codel &
	      CY_POST_CODEL_CFG_DATA_CRC_FAIL))
		dev_info(cd->dev, "%s: %s codel=%02X\n", __func__,
			 "Config Data CRC FAIL",
			 si->si_ptrs.test->post_codel);

	अगर (!(si->si_ptrs.test->post_codel &
	      CY_POST_CODEL_PANEL_TEST_FAIL))
		dev_info(cd->dev, "%s: %s codel=%02X\n",
			 __func__, "PANEL TEST FAIL",
			 si->si_ptrs.test->post_codel);

	dev_info(cd->dev, "%s: SCANNING is %s codel=%02X\n",
		 __func__, si->si_ptrs.test->post_codel & 0x08 ?
		 "ENABLED" : "DISABLED",
		 si->si_ptrs.test->post_codel);
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_pcfg_data(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	व्योम *p;
	पूर्णांक rc;

	अगर (si->si_ofs.opcfg_ofs <= si->si_ofs.pcfg_ofs) अणु
		dev_err(cd->dev,
			"%s: invalid offset opcfg_ofs: %zu, pcfg_ofs: %zu\n",
			__func__, si->si_ofs.opcfg_ofs, si->si_ofs.pcfg_ofs);
		वापस -EINVAL;
	पूर्ण

	si->si_ofs.pcfg_size = si->si_ofs.opcfg_ofs - si->si_ofs.pcfg_ofs;

	p = kपुनः_स्मृति(si->si_ptrs.pcfg, si->si_ofs.pcfg_size, GFP_KERNEL);
	अगर (p == शून्य) अणु
		dev_err(cd->dev, "%s: failed to allocate pcfg memory\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	si->si_ptrs.pcfg = p;

	rc = cyttsp4_adap_पढ़ो(cd, si->si_ofs.pcfg_ofs, si->si_ofs.pcfg_size,
			si->si_ptrs.pcfg);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read pcfg data r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण

	si->si_ofs.max_x = merge_bytes((si->si_ptrs.pcfg->res_xh
			& CY_PCFG_RESOLUTION_X_MASK), si->si_ptrs.pcfg->res_xl);
	si->si_ofs.x_origin = !!(si->si_ptrs.pcfg->res_xh
			& CY_PCFG_ORIGIN_X_MASK);
	si->si_ofs.max_y = merge_bytes((si->si_ptrs.pcfg->res_yh
			& CY_PCFG_RESOLUTION_Y_MASK), si->si_ptrs.pcfg->res_yl);
	si->si_ofs.y_origin = !!(si->si_ptrs.pcfg->res_yh
			& CY_PCFG_ORIGIN_Y_MASK);
	si->si_ofs.max_p = merge_bytes(si->si_ptrs.pcfg->max_zh,
			si->si_ptrs.pcfg->max_zl);

	cyttsp4_pr_buf(cd->dev, cd->pr_buf,
		       (u8 *)si->si_ptrs.pcfg,
		       si->si_ofs.pcfg_size, "sysinfo_pcfg_data");
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_opcfg_data(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	काष्ठा cyttsp4_tch_असल_params *tch;
	काष्ठा cyttsp4_tch_rec_params *tch_old, *tch_new;
	क्रमागत cyttsp4_tch_असल असल;
	पूर्णांक i;
	व्योम *p;
	पूर्णांक rc;

	अगर (si->si_ofs.ddata_ofs <= si->si_ofs.opcfg_ofs) अणु
		dev_err(cd->dev,
			"%s: invalid offset ddata_ofs: %zu, opcfg_ofs: %zu\n",
			__func__, si->si_ofs.ddata_ofs, si->si_ofs.opcfg_ofs);
		वापस -EINVAL;
	पूर्ण

	si->si_ofs.opcfg_size = si->si_ofs.ddata_ofs - si->si_ofs.opcfg_ofs;

	p = kपुनः_स्मृति(si->si_ptrs.opcfg, si->si_ofs.opcfg_size, GFP_KERNEL);
	अगर (p == शून्य) अणु
		dev_err(cd->dev, "%s: failed to allocate opcfg memory\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण
	si->si_ptrs.opcfg = p;

	rc = cyttsp4_adap_पढ़ो(cd, si->si_ofs.opcfg_ofs, si->si_ofs.opcfg_size,
			si->si_ptrs.opcfg);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail read opcfg data r=%d\n",
			__func__, rc);
		वापस rc;
	पूर्ण
	si->si_ofs.cmd_ofs = si->si_ptrs.opcfg->cmd_ofs;
	si->si_ofs.rep_ofs = si->si_ptrs.opcfg->rep_ofs;
	si->si_ofs.rep_sz = (si->si_ptrs.opcfg->rep_szh * 256) +
		si->si_ptrs.opcfg->rep_szl;
	si->si_ofs.num_btns = si->si_ptrs.opcfg->num_btns;
	si->si_ofs.num_btn_regs = (si->si_ofs.num_btns +
		CY_NUM_BTN_PER_REG - 1) / CY_NUM_BTN_PER_REG;
	si->si_ofs.tt_stat_ofs = si->si_ptrs.opcfg->tt_stat_ofs;
	si->si_ofs.obj_cfg0 = si->si_ptrs.opcfg->obj_cfg0;
	si->si_ofs.max_tchs = si->si_ptrs.opcfg->max_tchs &
		CY_BYTE_OFS_MASK;
	si->si_ofs.tch_rec_size = si->si_ptrs.opcfg->tch_rec_size &
		CY_BYTE_OFS_MASK;

	/* Get the old touch fields */
	क्रम (असल = CY_TCH_X; असल < CY_NUM_TCH_FIELDS; असल++) अणु
		tch = &si->si_ofs.tch_असल[असल];
		tch_old = &si->si_ptrs.opcfg->tch_rec_old[असल];

		tch->ofs = tch_old->loc & CY_BYTE_OFS_MASK;
		tch->size = cyttsp4_bits_2_bytes(tch_old->size,
						 &tch->max);
		tch->bofs = (tch_old->loc & CY_BOFS_MASK) >> CY_BOFS_SHIFT;
	पूर्ण

	/* button fields */
	si->si_ofs.btn_rec_size = si->si_ptrs.opcfg->btn_rec_size;
	si->si_ofs.btn_dअगरf_ofs = si->si_ptrs.opcfg->btn_dअगरf_ofs;
	si->si_ofs.btn_dअगरf_size = si->si_ptrs.opcfg->btn_dअगरf_size;

	अगर (si->si_ofs.tch_rec_size > CY_TMA1036_TCH_REC_SIZE) अणु
		/* Get the extended touch fields */
		क्रम (i = 0; i < CY_NUM_EXT_TCH_FIELDS; असल++, i++) अणु
			tch = &si->si_ofs.tch_असल[असल];
			tch_new = &si->si_ptrs.opcfg->tch_rec_new[i];

			tch->ofs = tch_new->loc & CY_BYTE_OFS_MASK;
			tch->size = cyttsp4_bits_2_bytes(tch_new->size,
							 &tch->max);
			tch->bofs = (tch_new->loc & CY_BOFS_MASK) >> CY_BOFS_SHIFT;
		पूर्ण
	पूर्ण

	क्रम (असल = 0; असल < CY_TCH_NUM_ABS; असल++) अणु
		dev_dbg(cd->dev, "%s: tch_rec_%s\n", __func__,
			cyttsp4_tch_असल_string[असल]);
		dev_dbg(cd->dev, "%s:     ofs =%2zd\n", __func__,
			si->si_ofs.tch_असल[असल].ofs);
		dev_dbg(cd->dev, "%s:     siz =%2zd\n", __func__,
			si->si_ofs.tch_असल[असल].size);
		dev_dbg(cd->dev, "%s:     max =%2zd\n", __func__,
			si->si_ofs.tch_असल[असल].max);
		dev_dbg(cd->dev, "%s:     bofs=%2zd\n", __func__,
			si->si_ofs.tch_असल[असल].bofs);
	पूर्ण

	si->si_ofs.mode_size = si->si_ofs.tt_stat_ofs + 1;
	si->si_ofs.data_size = si->si_ofs.max_tchs *
		si->si_ptrs.opcfg->tch_rec_size;

	cyttsp4_pr_buf(cd->dev, cd->pr_buf, (u8 *)si->si_ptrs.opcfg,
		si->si_ofs.opcfg_size, "sysinfo_opcfg_data");

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_ddata(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	व्योम *p;
	पूर्णांक rc;

	si->si_ofs.ddata_size = si->si_ofs.mdata_ofs - si->si_ofs.ddata_ofs;

	p = kपुनः_स्मृति(si->si_ptrs.ddata, si->si_ofs.ddata_size, GFP_KERNEL);
	अगर (p == शून्य) अणु
		dev_err(cd->dev, "%s: fail alloc ddata memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	si->si_ptrs.ddata = p;

	rc = cyttsp4_adap_पढ़ो(cd, si->si_ofs.ddata_ofs, si->si_ofs.ddata_size,
			si->si_ptrs.ddata);
	अगर (rc < 0)
		dev_err(cd->dev, "%s: fail read ddata data r=%d\n",
			__func__, rc);
	अन्यथा
		cyttsp4_pr_buf(cd->dev, cd->pr_buf,
			       (u8 *)si->si_ptrs.ddata,
			       si->si_ofs.ddata_size, "sysinfo_ddata");
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_mdata(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	व्योम *p;
	पूर्णांक rc;

	si->si_ofs.mdata_size = si->si_ofs.map_sz - si->si_ofs.mdata_ofs;

	p = kपुनः_स्मृति(si->si_ptrs.mdata, si->si_ofs.mdata_size, GFP_KERNEL);
	अगर (p == शून्य) अणु
		dev_err(cd->dev, "%s: fail alloc mdata memory\n", __func__);
		वापस -ENOMEM;
	पूर्ण
	si->si_ptrs.mdata = p;

	rc = cyttsp4_adap_पढ़ो(cd, si->si_ofs.mdata_ofs, si->si_ofs.mdata_size,
			si->si_ptrs.mdata);
	अगर (rc < 0)
		dev_err(cd->dev, "%s: fail read mdata data r=%d\n",
			__func__, rc);
	अन्यथा
		cyttsp4_pr_buf(cd->dev, cd->pr_buf,
			       (u8 *)si->si_ptrs.mdata,
			       si->si_ofs.mdata_size, "sysinfo_mdata");
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_btn_data(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	पूर्णांक btn;
	पूर्णांक num_defined_keys;
	u16 *key_table;
	व्योम *p;
	पूर्णांक rc = 0;

	अगर (si->si_ofs.num_btns) अणु
		si->si_ofs.btn_keys_size = si->si_ofs.num_btns *
			माप(काष्ठा cyttsp4_btn);

		p = kपुनः_स्मृति(si->btn, si->si_ofs.btn_keys_size,
				GFP_KERNEL|__GFP_ZERO);
		अगर (p == शून्य) अणु
			dev_err(cd->dev, "%s: %s\n", __func__,
				"fail alloc btn_keys memory");
			वापस -ENOMEM;
		पूर्ण
		si->btn = p;

		अगर (cd->cpdata->sett[CY_IC_GRPNUM_BTN_KEYS] == शून्य)
			num_defined_keys = 0;
		अन्यथा अगर (cd->cpdata->sett[CY_IC_GRPNUM_BTN_KEYS]->data == शून्य)
			num_defined_keys = 0;
		अन्यथा
			num_defined_keys = cd->cpdata->sett
				[CY_IC_GRPNUM_BTN_KEYS]->size;

		क्रम (btn = 0; btn < si->si_ofs.num_btns &&
			btn < num_defined_keys; btn++) अणु
			key_table = (u16 *)cd->cpdata->sett
				[CY_IC_GRPNUM_BTN_KEYS]->data;
			si->btn[btn].key_code = key_table[btn];
			si->btn[btn].state = CY_BTN_RELEASED;
			si->btn[btn].enabled = true;
		पूर्ण
		क्रम (; btn < si->si_ofs.num_btns; btn++) अणु
			si->btn[btn].key_code = KEY_RESERVED;
			si->btn[btn].state = CY_BTN_RELEASED;
			si->btn[btn].enabled = true;
		पूर्ण

		वापस rc;
	पूर्ण

	si->si_ofs.btn_keys_size = 0;
	kमुक्त(si->btn);
	si->btn = शून्य;
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_si_get_op_data_ptrs(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	व्योम *p;

	p = kपुनः_स्मृति(si->xy_mode, si->si_ofs.mode_size, GFP_KERNEL|__GFP_ZERO);
	अगर (p == शून्य)
		वापस -ENOMEM;
	si->xy_mode = p;

	p = kपुनः_स्मृति(si->xy_data, si->si_ofs.data_size, GFP_KERNEL|__GFP_ZERO);
	अगर (p == शून्य)
		वापस -ENOMEM;
	si->xy_data = p;

	p = kपुनः_स्मृति(si->btn_rec_data,
			si->si_ofs.btn_rec_size * si->si_ofs.num_btns,
			GFP_KERNEL|__GFP_ZERO);
	अगर (p == शून्य)
		वापस -ENOMEM;
	si->btn_rec_data = p;

	वापस 0;
पूर्ण

अटल व्योम cyttsp4_si_put_log_data(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	dev_dbg(cd->dev, "%s: cydata_ofs =%4zd siz=%4zd\n", __func__,
		si->si_ofs.cydata_ofs, si->si_ofs.cydata_size);
	dev_dbg(cd->dev, "%s: test_ofs   =%4zd siz=%4zd\n", __func__,
		si->si_ofs.test_ofs, si->si_ofs.test_size);
	dev_dbg(cd->dev, "%s: pcfg_ofs   =%4zd siz=%4zd\n", __func__,
		si->si_ofs.pcfg_ofs, si->si_ofs.pcfg_size);
	dev_dbg(cd->dev, "%s: opcfg_ofs  =%4zd siz=%4zd\n", __func__,
		si->si_ofs.opcfg_ofs, si->si_ofs.opcfg_size);
	dev_dbg(cd->dev, "%s: ddata_ofs  =%4zd siz=%4zd\n", __func__,
		si->si_ofs.ddata_ofs, si->si_ofs.ddata_size);
	dev_dbg(cd->dev, "%s: mdata_ofs  =%4zd siz=%4zd\n", __func__,
		si->si_ofs.mdata_ofs, si->si_ofs.mdata_size);

	dev_dbg(cd->dev, "%s: cmd_ofs       =%4zd\n", __func__,
		si->si_ofs.cmd_ofs);
	dev_dbg(cd->dev, "%s: rep_ofs       =%4zd\n", __func__,
		si->si_ofs.rep_ofs);
	dev_dbg(cd->dev, "%s: rep_sz        =%4zd\n", __func__,
		si->si_ofs.rep_sz);
	dev_dbg(cd->dev, "%s: num_btns      =%4zd\n", __func__,
		si->si_ofs.num_btns);
	dev_dbg(cd->dev, "%s: num_btn_regs  =%4zd\n", __func__,
		si->si_ofs.num_btn_regs);
	dev_dbg(cd->dev, "%s: tt_stat_ofs   =%4zd\n", __func__,
		si->si_ofs.tt_stat_ofs);
	dev_dbg(cd->dev, "%s: tch_rec_size  =%4zd\n", __func__,
		si->si_ofs.tch_rec_size);
	dev_dbg(cd->dev, "%s: max_tchs      =%4zd\n", __func__,
		si->si_ofs.max_tchs);
	dev_dbg(cd->dev, "%s: mode_size     =%4zd\n", __func__,
		si->si_ofs.mode_size);
	dev_dbg(cd->dev, "%s: data_size     =%4zd\n", __func__,
		si->si_ofs.data_size);
	dev_dbg(cd->dev, "%s: map_sz        =%4zd\n", __func__,
		si->si_ofs.map_sz);

	dev_dbg(cd->dev, "%s: btn_rec_size   =%2zd\n", __func__,
		si->si_ofs.btn_rec_size);
	dev_dbg(cd->dev, "%s: btn_diff_ofs   =%2zd\n", __func__,
		si->si_ofs.btn_dअगरf_ofs);
	dev_dbg(cd->dev, "%s: btn_diff_size  =%2zd\n", __func__,
		si->si_ofs.btn_dअगरf_size);

	dev_dbg(cd->dev, "%s: max_x    = 0x%04zX (%zd)\n", __func__,
		si->si_ofs.max_x, si->si_ofs.max_x);
	dev_dbg(cd->dev, "%s: x_origin = %zd (%s)\n", __func__,
		si->si_ofs.x_origin,
		si->si_ofs.x_origin == CY_NORMAL_ORIGIN ?
		"left corner" : "right corner");
	dev_dbg(cd->dev, "%s: max_y    = 0x%04zX (%zd)\n", __func__,
		si->si_ofs.max_y, si->si_ofs.max_y);
	dev_dbg(cd->dev, "%s: y_origin = %zd (%s)\n", __func__,
		si->si_ofs.y_origin,
		si->si_ofs.y_origin == CY_NORMAL_ORIGIN ?
		"upper corner" : "lower corner");
	dev_dbg(cd->dev, "%s: max_p    = 0x%04zX (%zd)\n", __func__,
		si->si_ofs.max_p, si->si_ofs.max_p);

	dev_dbg(cd->dev, "%s: xy_mode=%p xy_data=%p\n", __func__,
		si->xy_mode, si->xy_data);
पूर्ण

अटल पूर्णांक cyttsp4_get_sysinfo_regs(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;
	पूर्णांक rc;

	rc = cyttsp4_si_data_offsets(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_cydata(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_test_data(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_pcfg_data(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_opcfg_data(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_ddata(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_mdata(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_btn_data(cd);
	अगर (rc < 0)
		वापस rc;

	rc = cyttsp4_si_get_op_data_ptrs(cd);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: failed to get_op_data\n",
			__func__);
		वापस rc;
	पूर्ण

	cyttsp4_si_put_log_data(cd);

	/* provide flow control handshake */
	rc = cyttsp4_handshake(cd, si->si_data.hst_mode);
	अगर (rc < 0)
		dev_err(cd->dev, "%s: handshake fail on sysinfo reg\n",
			__func__);

	si->पढ़ोy = true;
	वापस rc;
पूर्ण

अटल व्योम cyttsp4_queue_startup_(काष्ठा cyttsp4 *cd)
अणु
	अगर (cd->startup_state == STARTUP_NONE) अणु
		cd->startup_state = STARTUP_QUEUED;
		schedule_work(&cd->startup_work);
		dev_dbg(cd->dev, "%s: cyttsp4_startup queued\n", __func__);
	पूर्ण अन्यथा अणु
		dev_dbg(cd->dev, "%s: startup_state = %d\n", __func__,
			cd->startup_state);
	पूर्ण
पूर्ण

अटल व्योम cyttsp4_report_slot_lअगरtoff(काष्ठा cyttsp4_mt_data *md,
		पूर्णांक max_slots)
अणु
	पूर्णांक t;

	अगर (md->num_prv_tch == 0)
		वापस;

	क्रम (t = 0; t < max_slots; t++) अणु
		input_mt_slot(md->input, t);
		input_mt_report_slot_inactive(md->input);
	पूर्ण
पूर्ण

अटल व्योम cyttsp4_lअगरt_all(काष्ठा cyttsp4_mt_data *md)
अणु
	अगर (!md->si)
		वापस;

	अगर (md->num_prv_tch != 0) अणु
		cyttsp4_report_slot_lअगरtoff(md,
				md->si->si_ofs.tch_असल[CY_TCH_T].max);
		input_sync(md->input);
		md->num_prv_tch = 0;
	पूर्ण
पूर्ण

अटल व्योम cyttsp4_get_touch_axis(काष्ठा cyttsp4_mt_data *md,
	पूर्णांक *axis, पूर्णांक size, पूर्णांक max, u8 *xy_data, पूर्णांक bofs)
अणु
	पूर्णांक nbyte;
	पूर्णांक next;

	क्रम (nbyte = 0, *axis = 0, next = 0; nbyte < size; nbyte++) अणु
		dev_vdbg(&md->input->dev,
			"%s: *axis=%02X(%d) size=%d max=%08X xy_data=%p"
			" xy_data[%d]=%02X(%d) bofs=%d\n",
			__func__, *axis, *axis, size, max, xy_data, next,
			xy_data[next], xy_data[next], bofs);
		*axis = (*axis * 256) + (xy_data[next] >> bofs);
		next++;
	पूर्ण

	*axis &= max - 1;

	dev_vdbg(&md->input->dev,
		"%s: *axis=%02X(%d) size=%d max=%08X xy_data=%p"
		" xy_data[%d]=%02X(%d)\n",
		__func__, *axis, *axis, size, max, xy_data, next,
		xy_data[next], xy_data[next]);
पूर्ण

अटल व्योम cyttsp4_get_touch(काष्ठा cyttsp4_mt_data *md,
	काष्ठा cyttsp4_touch *touch, u8 *xy_data)
अणु
	काष्ठा device *dev = &md->input->dev;
	काष्ठा cyttsp4_sysinfo *si = md->si;
	क्रमागत cyttsp4_tch_असल असल;
	bool flipped;

	क्रम (असल = CY_TCH_X; असल < CY_TCH_NUM_ABS; असल++) अणु
		cyttsp4_get_touch_axis(md, &touch->असल[असल],
			si->si_ofs.tch_असल[असल].size,
			si->si_ofs.tch_असल[असल].max,
			xy_data + si->si_ofs.tch_असल[असल].ofs,
			si->si_ofs.tch_असल[असल].bofs);
		dev_vdbg(dev, "%s: get %s=%04X(%d)\n", __func__,
			cyttsp4_tch_असल_string[असल],
			touch->असल[असल], touch->असल[असल]);
	पूर्ण

	अगर (md->pdata->flags & CY_FLAG_FLIP) अणु
		swap(touch->असल[CY_TCH_X], touch->असल[CY_TCH_Y]);
		flipped = true;
	पूर्ण अन्यथा
		flipped = false;

	अगर (md->pdata->flags & CY_FLAG_INV_X) अणु
		अगर (flipped)
			touch->असल[CY_TCH_X] = md->si->si_ofs.max_y -
				touch->असल[CY_TCH_X];
		अन्यथा
			touch->असल[CY_TCH_X] = md->si->si_ofs.max_x -
				touch->असल[CY_TCH_X];
	पूर्ण
	अगर (md->pdata->flags & CY_FLAG_INV_Y) अणु
		अगर (flipped)
			touch->असल[CY_TCH_Y] = md->si->si_ofs.max_x -
				touch->असल[CY_TCH_Y];
		अन्यथा
			touch->असल[CY_TCH_Y] = md->si->si_ofs.max_y -
				touch->असल[CY_TCH_Y];
	पूर्ण

	dev_vdbg(dev, "%s: flip=%s inv-x=%s inv-y=%s x=%04X(%d) y=%04X(%d)\n",
		__func__, flipped ? "true" : "false",
		md->pdata->flags & CY_FLAG_INV_X ? "true" : "false",
		md->pdata->flags & CY_FLAG_INV_Y ? "true" : "false",
		touch->असल[CY_TCH_X], touch->असल[CY_TCH_X],
		touch->असल[CY_TCH_Y], touch->असल[CY_TCH_Y]);
पूर्ण

अटल व्योम cyttsp4_final_sync(काष्ठा input_dev *input, पूर्णांक max_slots, पूर्णांक *ids)
अणु
	पूर्णांक t;

	क्रम (t = 0; t < max_slots; t++) अणु
		अगर (ids[t])
			जारी;
		input_mt_slot(input, t);
		input_mt_report_slot_inactive(input);
	पूर्ण

	input_sync(input);
पूर्ण

अटल व्योम cyttsp4_get_mt_touches(काष्ठा cyttsp4_mt_data *md, पूर्णांक num_cur_tch)
अणु
	काष्ठा device *dev = &md->input->dev;
	काष्ठा cyttsp4_sysinfo *si = md->si;
	काष्ठा cyttsp4_touch tch;
	पूर्णांक sig;
	पूर्णांक i, j, t = 0;
	पूर्णांक ids[max(CY_TMA1036_MAX_TCH, CY_TMA4XX_MAX_TCH)];

	स_रखो(ids, 0, si->si_ofs.tch_असल[CY_TCH_T].max * माप(पूर्णांक));
	क्रम (i = 0; i < num_cur_tch; i++) अणु
		cyttsp4_get_touch(md, &tch, si->xy_data +
			(i * si->si_ofs.tch_rec_size));
		अगर ((tch.असल[CY_TCH_T] < md->pdata->frmwrk->असल
			[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + CY_MIN_OST]) ||
			(tch.असल[CY_TCH_T] > md->pdata->frmwrk->असल
			[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + CY_MAX_OST])) अणु
			dev_err(dev, "%s: tch=%d -> bad trk_id=%d max_id=%d\n",
				__func__, i, tch.असल[CY_TCH_T],
				md->pdata->frmwrk->असल[(CY_ABS_ID_OST *
				CY_NUM_ABS_SET) + CY_MAX_OST]);
			जारी;
		पूर्ण

		/* use 0 based track id's */
		sig = md->pdata->frmwrk->असल
			[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + 0];
		अगर (sig != CY_IGNORE_VALUE) अणु
			t = tch.असल[CY_TCH_T] - md->pdata->frmwrk->असल
				[(CY_ABS_ID_OST * CY_NUM_ABS_SET) + CY_MIN_OST];
			अगर (tch.असल[CY_TCH_E] == CY_EV_LIFTOFF) अणु
				dev_dbg(dev, "%s: t=%d e=%d lift-off\n",
					__func__, t, tch.असल[CY_TCH_E]);
				जाओ cyttsp4_get_mt_touches_pr_tch;
			पूर्ण
			input_mt_slot(md->input, t);
			input_mt_report_slot_state(md->input, MT_TOOL_FINGER,
					true);
			ids[t] = true;
		पूर्ण

		/* all devices: position and pressure fields */
		क्रम (j = 0; j <= CY_ABS_W_OST; j++) अणु
			sig = md->pdata->frmwrk->असल[((CY_ABS_X_OST + j) *
				CY_NUM_ABS_SET) + 0];
			अगर (sig != CY_IGNORE_VALUE)
				input_report_असल(md->input, sig,
					tch.असल[CY_TCH_X + j]);
		पूर्ण
		अगर (si->si_ofs.tch_rec_size > CY_TMA1036_TCH_REC_SIZE) अणु
			/*
			 * TMA400 size and orientation fields:
			 * अगर pressure is non-zero and major touch
			 * संकेत is zero, then set major and minor touch
			 * संकेतs to minimum non-zero value
			 */
			अगर (tch.असल[CY_TCH_P] > 0 && tch.असल[CY_TCH_MAJ] == 0)
				tch.असल[CY_TCH_MAJ] = tch.असल[CY_TCH_MIN] = 1;

			/* Get the extended touch fields */
			क्रम (j = 0; j < CY_NUM_EXT_TCH_FIELDS; j++) अणु
				sig = md->pdata->frmwrk->असल
					[((CY_ABS_MAJ_OST + j) *
					CY_NUM_ABS_SET) + 0];
				अगर (sig != CY_IGNORE_VALUE)
					input_report_असल(md->input, sig,
						tch.असल[CY_TCH_MAJ + j]);
			पूर्ण
		पूर्ण

cyttsp4_get_mt_touches_pr_tch:
		अगर (si->si_ofs.tch_rec_size > CY_TMA1036_TCH_REC_SIZE)
			dev_dbg(dev,
				"%s: t=%d x=%d y=%d z=%d M=%d m=%d o=%d e=%d\n",
				__func__, t,
				tch.असल[CY_TCH_X],
				tch.असल[CY_TCH_Y],
				tch.असल[CY_TCH_P],
				tch.असल[CY_TCH_MAJ],
				tch.असल[CY_TCH_MIN],
				tch.असल[CY_TCH_OR],
				tch.असल[CY_TCH_E]);
		अन्यथा
			dev_dbg(dev,
				"%s: t=%d x=%d y=%d z=%d e=%d\n", __func__,
				t,
				tch.असल[CY_TCH_X],
				tch.असल[CY_TCH_Y],
				tch.असल[CY_TCH_P],
				tch.असल[CY_TCH_E]);
	पूर्ण

	cyttsp4_final_sync(md->input, si->si_ofs.tch_असल[CY_TCH_T].max, ids);

	md->num_prv_tch = num_cur_tch;

	वापस;
पूर्ण

/* पढ़ो xy_data क्रम all current touches */
अटल पूर्णांक cyttsp4_xy_worker(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_mt_data *md = &cd->md;
	काष्ठा device *dev = &md->input->dev;
	काष्ठा cyttsp4_sysinfo *si = md->si;
	u8 num_cur_tch;
	u8 hst_mode;
	u8 rep_len;
	u8 rep_stat;
	u8 tt_stat;
	पूर्णांक rc = 0;

	/*
	 * Get event data from cyttsp4 device.
	 * The event data includes all data
	 * क्रम all active touches.
	 * Event data also includes button data
	 */
	/*
	 * Use 2 पढ़ोs:
	 * 1st पढ़ो to get mode + button bytes + touch count (core)
	 * 2nd पढ़ो (optional) to get touch 1 - touch n data
	 */
	hst_mode = si->xy_mode[CY_REG_BASE];
	rep_len = si->xy_mode[si->si_ofs.rep_ofs];
	rep_stat = si->xy_mode[si->si_ofs.rep_ofs + 1];
	tt_stat = si->xy_mode[si->si_ofs.tt_stat_ofs];
	dev_vdbg(dev, "%s: %s%02X %s%d %s%02X %s%02X\n", __func__,
		"hst_mode=", hst_mode, "rep_len=", rep_len,
		"rep_stat=", rep_stat, "tt_stat=", tt_stat);

	num_cur_tch = GET_NUM_TOUCHES(tt_stat);
	dev_vdbg(dev, "%s: num_cur_tch=%d\n", __func__, num_cur_tch);

	अगर (rep_len == 0 && num_cur_tch > 0) अणु
		dev_err(dev, "%s: report length error rep_len=%d num_tch=%d\n",
			__func__, rep_len, num_cur_tch);
		जाओ cyttsp4_xy_worker_निकास;
	पूर्ण

	/* पढ़ो touches */
	अगर (num_cur_tch > 0) अणु
		rc = cyttsp4_adap_पढ़ो(cd, si->si_ofs.tt_stat_ofs + 1,
				num_cur_tch * si->si_ofs.tch_rec_size,
				si->xy_data);
		अगर (rc < 0) अणु
			dev_err(dev, "%s: read fail on touch regs r=%d\n",
				__func__, rc);
			जाओ cyttsp4_xy_worker_निकास;
		पूर्ण
	पूर्ण

	/* prपूर्णांक xy data */
	cyttsp4_pr_buf(dev, cd->pr_buf, si->xy_data, num_cur_tch *
		si->si_ofs.tch_rec_size, "xy_data");

	/* check any error conditions */
	अगर (IS_BAD_PKT(rep_stat)) अणु
		dev_dbg(dev, "%s: Invalid buffer detected\n", __func__);
		rc = 0;
		जाओ cyttsp4_xy_worker_निकास;
	पूर्ण

	अगर (IS_LARGE_AREA(tt_stat))
		dev_dbg(dev, "%s: Large area detected\n", __func__);

	अगर (num_cur_tch > si->si_ofs.max_tchs) अणु
		dev_err(dev, "%s: too many tch; set to max tch (n=%d c=%zd)\n",
				__func__, num_cur_tch, si->si_ofs.max_tchs);
		num_cur_tch = si->si_ofs.max_tchs;
	पूर्ण

	/* extract xy_data क्रम all currently reported touches */
	dev_vdbg(dev, "%s: extract data num_cur_tch=%d\n", __func__,
		num_cur_tch);
	अगर (num_cur_tch)
		cyttsp4_get_mt_touches(md, num_cur_tch);
	अन्यथा
		cyttsp4_lअगरt_all(md);

	rc = 0;

cyttsp4_xy_worker_निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_mt_attention(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा device *dev = cd->dev;
	काष्ठा cyttsp4_mt_data *md = &cd->md;
	पूर्णांक rc = 0;

	अगर (!md->si)
		वापस 0;

	mutex_lock(&md->report_lock);
	अगर (!md->is_suspended) अणु
		/* core handles handshake */
		rc = cyttsp4_xy_worker(cd);
	पूर्ण अन्यथा अणु
		dev_vdbg(dev, "%s: Ignoring report while suspended\n",
			__func__);
	पूर्ण
	mutex_unlock(&md->report_lock);
	अगर (rc < 0)
		dev_err(dev, "%s: xy_worker error r=%d\n", __func__, rc);

	वापस rc;
पूर्ण

अटल irqवापस_t cyttsp4_irq(पूर्णांक irq, व्योम *handle)
अणु
	काष्ठा cyttsp4 *cd = handle;
	काष्ठा device *dev = cd->dev;
	क्रमागत cyttsp4_mode cur_mode;
	u8 cmd_ofs = cd->sysinfo.si_ofs.cmd_ofs;
	u8 mode[3];
	पूर्णांक rc;

	/*
	 * Check whether this IRQ should be ignored (बाह्यal)
	 * This should be the very first thing to check since
	 * ignore_irq may be set क्रम a very लघु period of समय
	 */
	अगर (atomic_पढ़ो(&cd->ignore_irq)) अणु
		dev_vdbg(dev, "%s: Ignoring IRQ\n", __func__);
		वापस IRQ_HANDLED;
	पूर्ण

	dev_dbg(dev, "%s int:0x%x\n", __func__, cd->पूर्णांक_status);

	mutex_lock(&cd->प्रणाली_lock);

	/* Just to debug */
	अगर (cd->sleep_state == SS_SLEEP_ON || cd->sleep_state == SS_SLEEPING)
		dev_vdbg(dev, "%s: Received IRQ while in sleep\n", __func__);

	rc = cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, माप(mode), mode);
	अगर (rc) अणु
		dev_err(cd->dev, "%s: Fail read adapter r=%d\n", __func__, rc);
		जाओ cyttsp4_irq_निकास;
	पूर्ण
	dev_vdbg(dev, "%s mode[0-2]:0x%X 0x%X 0x%X\n", __func__,
			mode[0], mode[1], mode[2]);

	अगर (IS_BOOTLOADER(mode[0], mode[1])) अणु
		cur_mode = CY_MODE_BOOTLOADER;
		dev_vdbg(dev, "%s: bl running\n", __func__);
		अगर (cd->mode == CY_MODE_BOOTLOADER) अणु
			/* Signal bootloader heartbeat heard */
			wake_up(&cd->रुको_q);
			जाओ cyttsp4_irq_निकास;
		पूर्ण

		/* चयन to bootloader */
		dev_dbg(dev, "%s: restart switch to bl m=%d -> m=%d\n",
			__func__, cd->mode, cur_mode);

		/* catch operation->bl glitch */
		अगर (cd->mode != CY_MODE_UNKNOWN) अणु
			/* Inहाल startup_state करो not let startup_() */
			cd->mode = CY_MODE_UNKNOWN;
			cyttsp4_queue_startup_(cd);
			जाओ cyttsp4_irq_निकास;
		पूर्ण

		/*
		 * करो not wake thपढ़ो on this चयन since
		 * it is possible to get an early heartbeat
		 * prior to perक्रमming the reset
		 */
		cd->mode = cur_mode;

		जाओ cyttsp4_irq_निकास;
	पूर्ण

	चयन (mode[0] & CY_HST_MODE) अणु
	हाल CY_HST_OPERATE:
		cur_mode = CY_MODE_OPERATIONAL;
		dev_vdbg(dev, "%s: operational\n", __func__);
		अवरोध;
	हाल CY_HST_CAT:
		cur_mode = CY_MODE_CAT;
		dev_vdbg(dev, "%s: CaT\n", __func__);
		अवरोध;
	हाल CY_HST_SYSINFO:
		cur_mode = CY_MODE_SYSINFO;
		dev_vdbg(dev, "%s: sysinfo\n", __func__);
		अवरोध;
	शेष:
		cur_mode = CY_MODE_UNKNOWN;
		dev_err(dev, "%s: unknown HST mode 0x%02X\n", __func__,
			mode[0]);
		अवरोध;
	पूर्ण

	/* Check whether this IRQ should be ignored (पूर्णांकernal) */
	अगर (cd->पूर्णांक_status & CY_INT_IGNORE) अणु
		dev_vdbg(dev, "%s: Ignoring IRQ\n", __func__);
		जाओ cyttsp4_irq_निकास;
	पूर्ण

	/* Check क्रम wake up पूर्णांकerrupt */
	अगर (cd->पूर्णांक_status & CY_INT_AWAKE) अणु
		cd->पूर्णांक_status &= ~CY_INT_AWAKE;
		wake_up(&cd->रुको_q);
		dev_vdbg(dev, "%s: Received wake up interrupt\n", __func__);
		जाओ cyttsp4_irq_handshake;
	पूर्ण

	/* Expecting mode change पूर्णांकerrupt */
	अगर ((cd->पूर्णांक_status & CY_INT_MODE_CHANGE)
			&& (mode[0] & CY_HST_MODE_CHANGE) == 0) अणु
		cd->पूर्णांक_status &= ~CY_INT_MODE_CHANGE;
		dev_dbg(dev, "%s: finish mode switch m=%d -> m=%d\n",
				__func__, cd->mode, cur_mode);
		cd->mode = cur_mode;
		wake_up(&cd->रुको_q);
		जाओ cyttsp4_irq_handshake;
	पूर्ण

	/* compare current core mode to current device mode */
	dev_vdbg(dev, "%s: cd->mode=%d cur_mode=%d\n",
			__func__, cd->mode, cur_mode);
	अगर ((mode[0] & CY_HST_MODE_CHANGE) == 0 && cd->mode != cur_mode) अणु
		/* Unexpected mode change occurred */
		dev_err(dev, "%s %d->%d 0x%x\n", __func__, cd->mode,
				cur_mode, cd->पूर्णांक_status);
		dev_dbg(dev, "%s: Unexpected mode change, startup\n",
				__func__);
		cyttsp4_queue_startup_(cd);
		जाओ cyttsp4_irq_निकास;
	पूर्ण

	/* Expecting command complete पूर्णांकerrupt */
	dev_vdbg(dev, "%s: command byte:0x%x\n", __func__, mode[cmd_ofs]);
	अगर ((cd->पूर्णांक_status & CY_INT_EXEC_CMD)
			&& mode[cmd_ofs] & CY_CMD_COMPLETE) अणु
		cd->पूर्णांक_status &= ~CY_INT_EXEC_CMD;
		dev_vdbg(dev, "%s: Received command complete interrupt\n",
				__func__);
		wake_up(&cd->रुको_q);
		/*
		 * It is possible to receive a single पूर्णांकerrupt क्रम
		 * command complete and touch/button status report.
		 * Continue processing क्रम a possible status report.
		 */
	पूर्ण

	/* This should be status report, पढ़ो status regs */
	अगर (cd->mode == CY_MODE_OPERATIONAL) अणु
		dev_vdbg(dev, "%s: Read status registers\n", __func__);
		rc = cyttsp4_load_status_regs(cd);
		अगर (rc < 0)
			dev_err(dev, "%s: fail read mode regs r=%d\n",
				__func__, rc);
	पूर्ण

	cyttsp4_mt_attention(cd);

cyttsp4_irq_handshake:
	/* handshake the event */
	dev_vdbg(dev, "%s: Handshake mode=0x%02X r=%d\n",
			__func__, mode[0], rc);
	rc = cyttsp4_handshake(cd, mode[0]);
	अगर (rc < 0)
		dev_err(dev, "%s: Fail handshake mode=0x%02X r=%d\n",
				__func__, mode[0], rc);

	/*
	 * a non-zero udelay period is required क्रम using
	 * IRQF_TRIGGER_LOW in order to delay until the
	 * device completes isr deनिश्चित
	 */
	udelay(cd->cpdata->level_irq_udelay);

cyttsp4_irq_निकास:
	mutex_unlock(&cd->प्रणाली_lock);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम cyttsp4_start_wd_समयr(काष्ठा cyttsp4 *cd)
अणु
	अगर (!CY_WATCHDOG_TIMEOUT)
		वापस;

	mod_समयr(&cd->watchकरोg_समयr, jअगरfies +
			msecs_to_jअगरfies(CY_WATCHDOG_TIMEOUT));
पूर्ण

अटल व्योम cyttsp4_stop_wd_समयr(काष्ठा cyttsp4 *cd)
अणु
	अगर (!CY_WATCHDOG_TIMEOUT)
		वापस;

	/*
	 * Ensure we रुको until the watchकरोg समयr
	 * running on a dअगरferent CPU finishes
	 */
	del_समयr_sync(&cd->watchकरोg_समयr);
	cancel_work_sync(&cd->watchकरोg_work);
	del_समयr_sync(&cd->watchकरोg_समयr);
पूर्ण

अटल व्योम cyttsp4_watchकरोg_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा cyttsp4 *cd = from_समयr(cd, t, watchकरोg_समयr);

	dev_vdbg(cd->dev, "%s: Watchdog timer triggered\n", __func__);

	schedule_work(&cd->watchकरोg_work);

	वापस;
पूर्ण

अटल पूर्णांक cyttsp4_request_exclusive(काष्ठा cyttsp4 *cd, व्योम *ownptr,
		पूर्णांक समयout_ms)
अणु
	पूर्णांक t = msecs_to_jअगरfies(समयout_ms);
	bool with_समयout = (समयout_ms != 0);

	mutex_lock(&cd->प्रणाली_lock);
	अगर (!cd->exclusive_dev && cd->exclusive_रुकोs == 0) अणु
		cd->exclusive_dev = ownptr;
		जाओ निकास;
	पूर्ण

	cd->exclusive_रुकोs++;
रुको:
	mutex_unlock(&cd->प्रणाली_lock);
	अगर (with_समयout) अणु
		t = रुको_event_समयout(cd->रुको_q, !cd->exclusive_dev, t);
		अगर (IS_TMO(t)) अणु
			dev_err(cd->dev, "%s: tmo waiting exclusive access\n",
				__func__);
			mutex_lock(&cd->प्रणाली_lock);
			cd->exclusive_रुकोs--;
			mutex_unlock(&cd->प्रणाली_lock);
			वापस -ETIME;
		पूर्ण
	पूर्ण अन्यथा अणु
		रुको_event(cd->रुको_q, !cd->exclusive_dev);
	पूर्ण
	mutex_lock(&cd->प्रणाली_lock);
	अगर (cd->exclusive_dev)
		जाओ रुको;
	cd->exclusive_dev = ownptr;
	cd->exclusive_रुकोs--;
निकास:
	mutex_unlock(&cd->प्रणाली_lock);

	वापस 0;
पूर्ण

/*
 * वापसs error अगर was not owned
 */
अटल पूर्णांक cyttsp4_release_exclusive(काष्ठा cyttsp4 *cd, व्योम *ownptr)
अणु
	mutex_lock(&cd->प्रणाली_lock);
	अगर (cd->exclusive_dev != ownptr) अणु
		mutex_unlock(&cd->प्रणाली_lock);
		वापस -EINVAL;
	पूर्ण

	dev_vdbg(cd->dev, "%s: exclusive_dev %p freed\n",
		__func__, cd->exclusive_dev);
	cd->exclusive_dev = शून्य;
	wake_up(&cd->रुको_q);
	mutex_unlock(&cd->प्रणाली_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp4_रुको_bl_heartbeat(काष्ठा cyttsp4 *cd)
अणु
	दीर्घ t;
	पूर्णांक rc = 0;

	/* रुको heartbeat */
	dev_vdbg(cd->dev, "%s: wait heartbeat...\n", __func__);
	t = रुको_event_समयout(cd->रुको_q, cd->mode == CY_MODE_BOOTLOADER,
			msecs_to_jअगरfies(CY_CORE_RESET_AND_WAIT_TIMEOUT));
	अगर (IS_TMO(t)) अणु
		dev_err(cd->dev, "%s: tmo waiting bl heartbeat cd->mode=%d\n",
			__func__, cd->mode);
		rc = -ETIME;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_रुको_sysinfo_mode(काष्ठा cyttsp4 *cd)
अणु
	दीर्घ t;

	dev_vdbg(cd->dev, "%s: wait sysinfo...\n", __func__);

	t = रुको_event_समयout(cd->रुको_q, cd->mode == CY_MODE_SYSINFO,
			msecs_to_jअगरfies(CY_CORE_MODE_CHANGE_TIMEOUT));
	अगर (IS_TMO(t)) अणु
		dev_err(cd->dev, "%s: tmo waiting exit bl cd->mode=%d\n",
			__func__, cd->mode);
		mutex_lock(&cd->प्रणाली_lock);
		cd->पूर्णांक_status &= ~CY_INT_MODE_CHANGE;
		mutex_unlock(&cd->प्रणाली_lock);
		वापस -ETIME;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp4_reset_and_रुको(काष्ठा cyttsp4 *cd)
अणु
	पूर्णांक rc;

	/* reset hardware */
	mutex_lock(&cd->प्रणाली_lock);
	dev_dbg(cd->dev, "%s: reset hw...\n", __func__);
	rc = cyttsp4_hw_reset(cd);
	cd->mode = CY_MODE_UNKNOWN;
	mutex_unlock(&cd->प्रणाली_lock);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s:Fail hw reset r=%d\n", __func__, rc);
		वापस rc;
	पूर्ण

	वापस cyttsp4_रुको_bl_heartbeat(cd);
पूर्ण

/*
 * वापसs err अगर refused or समयout; block until mode change complete
 * bit is set (mode change पूर्णांकerrupt)
 */
अटल पूर्णांक cyttsp4_set_mode(काष्ठा cyttsp4 *cd, पूर्णांक new_mode)
अणु
	u8 new_dev_mode;
	u8 mode;
	दीर्घ t;
	पूर्णांक rc;

	चयन (new_mode) अणु
	हाल CY_MODE_OPERATIONAL:
		new_dev_mode = CY_HST_OPERATE;
		अवरोध;
	हाल CY_MODE_SYSINFO:
		new_dev_mode = CY_HST_SYSINFO;
		अवरोध;
	हाल CY_MODE_CAT:
		new_dev_mode = CY_HST_CAT;
		अवरोध;
	शेष:
		dev_err(cd->dev, "%s: invalid mode: %02X(%d)\n",
			__func__, new_mode, new_mode);
		वापस -EINVAL;
	पूर्ण

	/* change mode */
	dev_dbg(cd->dev, "%s: %s=%p new_dev_mode=%02X new_mode=%d\n",
			__func__, "have exclusive", cd->exclusive_dev,
			new_dev_mode, new_mode);

	mutex_lock(&cd->प्रणाली_lock);
	rc = cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, माप(mode), &mode);
	अगर (rc < 0) अणु
		mutex_unlock(&cd->प्रणाली_lock);
		dev_err(cd->dev, "%s: Fail read mode r=%d\n",
			__func__, rc);
		जाओ निकास;
	पूर्ण

	/* Clear device mode bits and set to new mode */
	mode &= ~CY_HST_MODE;
	mode |= new_dev_mode | CY_HST_MODE_CHANGE;

	cd->पूर्णांक_status |= CY_INT_MODE_CHANGE;
	rc = cyttsp4_adap_ग_लिखो(cd, CY_REG_BASE, माप(mode), &mode);
	mutex_unlock(&cd->प्रणाली_lock);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: Fail write mode change r=%d\n",
				__func__, rc);
		जाओ निकास;
	पूर्ण

	/* रुको क्रम mode change करोne पूर्णांकerrupt */
	t = रुको_event_समयout(cd->रुको_q,
			(cd->पूर्णांक_status & CY_INT_MODE_CHANGE) == 0,
			msecs_to_jअगरfies(CY_CORE_MODE_CHANGE_TIMEOUT));
	dev_dbg(cd->dev, "%s: back from wait t=%ld cd->mode=%d\n",
			__func__, t, cd->mode);

	अगर (IS_TMO(t)) अणु
		dev_err(cd->dev, "%s: %s\n", __func__,
				"tmo waiting mode change");
		mutex_lock(&cd->प्रणाली_lock);
		cd->पूर्णांक_status &= ~CY_INT_MODE_CHANGE;
		mutex_unlock(&cd->प्रणाली_lock);
		rc = -EINVAL;
	पूर्ण

निकास:
	वापस rc;
पूर्ण

अटल व्योम cyttsp4_watchकरोg_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cyttsp4 *cd =
		container_of(work, काष्ठा cyttsp4, watchकरोg_work);
	u8 *mode;
	पूर्णांक retval;

	mutex_lock(&cd->प्रणाली_lock);
	retval = cyttsp4_load_status_regs(cd);
	अगर (retval < 0) अणु
		dev_err(cd->dev,
			"%s: failed to access device in watchdog timer r=%d\n",
			__func__, retval);
		cyttsp4_queue_startup_(cd);
		जाओ cyttsp4_समयr_watchकरोg_निकास_error;
	पूर्ण
	mode = &cd->sysinfo.xy_mode[CY_REG_BASE];
	अगर (IS_BOOTLOADER(mode[0], mode[1])) अणु
		dev_err(cd->dev,
			"%s: device found in bootloader mode when operational mode\n",
			__func__);
		cyttsp4_queue_startup_(cd);
		जाओ cyttsp4_समयr_watchकरोg_निकास_error;
	पूर्ण

	cyttsp4_start_wd_समयr(cd);
cyttsp4_समयr_watchकरोg_निकास_error:
	mutex_unlock(&cd->प्रणाली_lock);
	वापस;
पूर्ण

अटल पूर्णांक cyttsp4_core_sleep_(काष्ठा cyttsp4 *cd)
अणु
	क्रमागत cyttsp4_sleep_state ss = SS_SLEEP_ON;
	क्रमागत cyttsp4_पूर्णांक_state पूर्णांक_status = CY_INT_IGNORE;
	पूर्णांक rc = 0;
	u8 mode[2];

	/* Alपढ़ोy in sleep mode? */
	mutex_lock(&cd->प्रणाली_lock);
	अगर (cd->sleep_state == SS_SLEEP_ON) अणु
		mutex_unlock(&cd->प्रणाली_lock);
		वापस 0;
	पूर्ण
	cd->sleep_state = SS_SLEEPING;
	mutex_unlock(&cd->प्रणाली_lock);

	cyttsp4_stop_wd_समयr(cd);

	/* Wait until currently running IRQ handler निकासs and disable IRQ */
	disable_irq(cd->irq);

	dev_vdbg(cd->dev, "%s: write DEEP SLEEP...\n", __func__);
	mutex_lock(&cd->प्रणाली_lock);
	rc = cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, माप(mode), &mode);
	अगर (rc) अणु
		mutex_unlock(&cd->प्रणाली_lock);
		dev_err(cd->dev, "%s: Fail read adapter r=%d\n", __func__, rc);
		जाओ error;
	पूर्ण

	अगर (IS_BOOTLOADER(mode[0], mode[1])) अणु
		mutex_unlock(&cd->प्रणाली_lock);
		dev_err(cd->dev, "%s: Device in BOOTLOADER mode.\n", __func__);
		rc = -EINVAL;
		जाओ error;
	पूर्ण

	mode[0] |= CY_HST_SLEEP;
	rc = cyttsp4_adap_ग_लिखो(cd, CY_REG_BASE, माप(mode[0]), &mode[0]);
	mutex_unlock(&cd->प्रणाली_lock);
	अगर (rc) अणु
		dev_err(cd->dev, "%s: Fail write adapter r=%d\n", __func__, rc);
		जाओ error;
	पूर्ण
	dev_vdbg(cd->dev, "%s: write DEEP SLEEP succeeded\n", __func__);

	अगर (cd->cpdata->घातer) अणु
		dev_dbg(cd->dev, "%s: Power down HW\n", __func__);
		rc = cd->cpdata->घातer(cd->cpdata, 0, cd->dev, &cd->ignore_irq);
	पूर्ण अन्यथा अणु
		dev_dbg(cd->dev, "%s: No power function\n", __func__);
		rc = 0;
	पूर्ण
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: HW Power down fails r=%d\n",
				__func__, rc);
		जाओ error;
	पूर्ण

	/* Give समय to FW to sleep */
	msleep(50);

	जाओ निकास;

error:
	ss = SS_SLEEP_OFF;
	पूर्णांक_status = CY_INT_NONE;
	cyttsp4_start_wd_समयr(cd);

निकास:
	mutex_lock(&cd->प्रणाली_lock);
	cd->sleep_state = ss;
	cd->पूर्णांक_status |= पूर्णांक_status;
	mutex_unlock(&cd->प्रणाली_lock);
	enable_irq(cd->irq);
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_startup_(काष्ठा cyttsp4 *cd)
अणु
	पूर्णांक retry = CY_CORE_STARTUP_RETRY_COUNT;
	पूर्णांक rc;

	cyttsp4_stop_wd_समयr(cd);

reset:
	अगर (retry != CY_CORE_STARTUP_RETRY_COUNT)
		dev_dbg(cd->dev, "%s: Retry %d\n", __func__,
			CY_CORE_STARTUP_RETRY_COUNT - retry);

	/* reset hardware and रुको क्रम heartbeat */
	rc = cyttsp4_reset_and_रुको(cd);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: Error on h/w reset r=%d\n", __func__, rc);
		अगर (retry--)
			जाओ reset;
		जाओ निकास;
	पूर्ण

	/* निकास bl पूर्णांकo sysinfo mode */
	dev_vdbg(cd->dev, "%s: write exit ldr...\n", __func__);
	mutex_lock(&cd->प्रणाली_lock);
	cd->पूर्णांक_status &= ~CY_INT_IGNORE;
	cd->पूर्णांक_status |= CY_INT_MODE_CHANGE;

	rc = cyttsp4_adap_ग_लिखो(cd, CY_REG_BASE, माप(ldr_निकास),
			(u8 *)ldr_निकास);
	mutex_unlock(&cd->प्रणाली_lock);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: Fail write r=%d\n", __func__, rc);
		अगर (retry--)
			जाओ reset;
		जाओ निकास;
	पूर्ण

	rc = cyttsp4_रुको_sysinfo_mode(cd);
	अगर (rc < 0) अणु
		u8 buf[माप(ldr_err_app)];
		पूर्णांक rc1;

		/* Check क्रम invalid/corrupted touch application */
		rc1 = cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, माप(ldr_err_app),
				buf);
		अगर (rc1) अणु
			dev_err(cd->dev, "%s: Fail read r=%d\n", __func__, rc1);
		पूर्ण अन्यथा अगर (!स_भेद(buf, ldr_err_app, माप(ldr_err_app))) अणु
			dev_err(cd->dev, "%s: Error launching touch application\n",
				__func__);
			mutex_lock(&cd->प्रणाली_lock);
			cd->invalid_touch_app = true;
			mutex_unlock(&cd->प्रणाली_lock);
			जाओ निकास_no_wd;
		पूर्ण

		अगर (retry--)
			जाओ reset;
		जाओ निकास;
	पूर्ण

	mutex_lock(&cd->प्रणाली_lock);
	cd->invalid_touch_app = false;
	mutex_unlock(&cd->प्रणाली_lock);

	/* पढ़ो sysinfo data */
	dev_vdbg(cd->dev, "%s: get sysinfo regs..\n", __func__);
	rc = cyttsp4_get_sysinfo_regs(cd);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: failed to get sysinfo regs rc=%d\n",
			__func__, rc);
		अगर (retry--)
			जाओ reset;
		जाओ निकास;
	पूर्ण

	rc = cyttsp4_set_mode(cd, CY_MODE_OPERATIONAL);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: failed to set mode to operational rc=%d\n",
			__func__, rc);
		अगर (retry--)
			जाओ reset;
		जाओ निकास;
	पूर्ण

	cyttsp4_lअगरt_all(&cd->md);

	/* restore to sleep अगर was suspended */
	mutex_lock(&cd->प्रणाली_lock);
	अगर (cd->sleep_state == SS_SLEEP_ON) अणु
		cd->sleep_state = SS_SLEEP_OFF;
		mutex_unlock(&cd->प्रणाली_lock);
		cyttsp4_core_sleep_(cd);
		जाओ निकास_no_wd;
	पूर्ण
	mutex_unlock(&cd->प्रणाली_lock);

निकास:
	cyttsp4_start_wd_समयr(cd);
निकास_no_wd:
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_startup(काष्ठा cyttsp4 *cd)
अणु
	पूर्णांक rc;

	mutex_lock(&cd->प्रणाली_lock);
	cd->startup_state = STARTUP_RUNNING;
	mutex_unlock(&cd->प्रणाली_lock);

	rc = cyttsp4_request_exclusive(cd, cd->dev,
			CY_CORE_REQUEST_EXCLUSIVE_TIMEOUT);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail get exclusive ex=%p own=%p\n",
				__func__, cd->exclusive_dev, cd->dev);
		जाओ निकास;
	पूर्ण

	rc = cyttsp4_startup_(cd);

	अगर (cyttsp4_release_exclusive(cd, cd->dev) < 0)
		/* Don't वापस fail code, mode is alपढ़ोy changed. */
		dev_err(cd->dev, "%s: fail to release exclusive\n", __func__);
	अन्यथा
		dev_vdbg(cd->dev, "%s: pass release exclusive\n", __func__);

निकास:
	mutex_lock(&cd->प्रणाली_lock);
	cd->startup_state = STARTUP_NONE;
	mutex_unlock(&cd->प्रणाली_lock);

	/* Wake the रुकोers क्रम end of startup */
	wake_up(&cd->रुको_q);

	वापस rc;
पूर्ण

अटल व्योम cyttsp4_startup_work_function(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cyttsp4 *cd =  container_of(work, काष्ठा cyttsp4, startup_work);
	पूर्णांक rc;

	rc = cyttsp4_startup(cd);
	अगर (rc < 0)
		dev_err(cd->dev, "%s: Fail queued startup r=%d\n",
			__func__, rc);
पूर्ण

अटल व्योम cyttsp4_मुक्त_si_ptrs(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा cyttsp4_sysinfo *si = &cd->sysinfo;

	अगर (!si)
		वापस;

	kमुक्त(si->si_ptrs.cydata);
	kमुक्त(si->si_ptrs.test);
	kमुक्त(si->si_ptrs.pcfg);
	kमुक्त(si->si_ptrs.opcfg);
	kमुक्त(si->si_ptrs.ddata);
	kमुक्त(si->si_ptrs.mdata);
	kमुक्त(si->btn);
	kमुक्त(si->xy_mode);
	kमुक्त(si->xy_data);
	kमुक्त(si->btn_rec_data);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cyttsp4_core_sleep(काष्ठा cyttsp4 *cd)
अणु
	पूर्णांक rc;

	rc = cyttsp4_request_exclusive(cd, cd->dev,
			CY_CORE_SLEEP_REQUEST_EXCLUSIVE_TIMEOUT);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail get exclusive ex=%p own=%p\n",
				__func__, cd->exclusive_dev, cd->dev);
		वापस 0;
	पूर्ण

	rc = cyttsp4_core_sleep_(cd);

	अगर (cyttsp4_release_exclusive(cd, cd->dev) < 0)
		dev_err(cd->dev, "%s: fail to release exclusive\n", __func__);
	अन्यथा
		dev_vdbg(cd->dev, "%s: pass release exclusive\n", __func__);

	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_core_wake_(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा device *dev = cd->dev;
	पूर्णांक rc;
	u8 mode;
	पूर्णांक t;

	/* Alपढ़ोy woken? */
	mutex_lock(&cd->प्रणाली_lock);
	अगर (cd->sleep_state == SS_SLEEP_OFF) अणु
		mutex_unlock(&cd->प्रणाली_lock);
		वापस 0;
	पूर्ण
	cd->पूर्णांक_status &= ~CY_INT_IGNORE;
	cd->पूर्णांक_status |= CY_INT_AWAKE;
	cd->sleep_state = SS_WAKING;

	अगर (cd->cpdata->घातer) अणु
		dev_dbg(dev, "%s: Power up HW\n", __func__);
		rc = cd->cpdata->घातer(cd->cpdata, 1, dev, &cd->ignore_irq);
	पूर्ण अन्यथा अणु
		dev_dbg(dev, "%s: No power function\n", __func__);
		rc = -ENOSYS;
	पूर्ण
	अगर (rc < 0) अणु
		dev_err(dev, "%s: HW Power up fails r=%d\n",
				__func__, rc);

		/* Initiate a पढ़ो transaction to wake up */
		cyttsp4_adap_पढ़ो(cd, CY_REG_BASE, माप(mode), &mode);
	पूर्ण अन्यथा
		dev_vdbg(cd->dev, "%s: HW power up succeeds\n",
			__func__);
	mutex_unlock(&cd->प्रणाली_lock);

	t = रुको_event_समयout(cd->रुको_q,
			(cd->पूर्णांक_status & CY_INT_AWAKE) == 0,
			msecs_to_jअगरfies(CY_CORE_WAKEUP_TIMEOUT));
	अगर (IS_TMO(t)) अणु
		dev_err(dev, "%s: TMO waiting for wakeup\n", __func__);
		mutex_lock(&cd->प्रणाली_lock);
		cd->पूर्णांक_status &= ~CY_INT_AWAKE;
		/* Try starting up */
		cyttsp4_queue_startup_(cd);
		mutex_unlock(&cd->प्रणाली_lock);
	पूर्ण

	mutex_lock(&cd->प्रणाली_lock);
	cd->sleep_state = SS_SLEEP_OFF;
	mutex_unlock(&cd->प्रणाली_lock);

	cyttsp4_start_wd_समयr(cd);

	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp4_core_wake(काष्ठा cyttsp4 *cd)
अणु
	पूर्णांक rc;

	rc = cyttsp4_request_exclusive(cd, cd->dev,
			CY_CORE_REQUEST_EXCLUSIVE_TIMEOUT);
	अगर (rc < 0) अणु
		dev_err(cd->dev, "%s: fail get exclusive ex=%p own=%p\n",
				__func__, cd->exclusive_dev, cd->dev);
		वापस 0;
	पूर्ण

	rc = cyttsp4_core_wake_(cd);

	अगर (cyttsp4_release_exclusive(cd, cd->dev) < 0)
		dev_err(cd->dev, "%s: fail to release exclusive\n", __func__);
	अन्यथा
		dev_vdbg(cd->dev, "%s: pass release exclusive\n", __func__);

	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_core_suspend(काष्ठा device *dev)
अणु
	काष्ठा cyttsp4 *cd = dev_get_drvdata(dev);
	काष्ठा cyttsp4_mt_data *md = &cd->md;
	पूर्णांक rc;

	md->is_suspended = true;

	rc = cyttsp4_core_sleep(cd);
	अगर (rc < 0) अणु
		dev_err(dev, "%s: Error on sleep\n", __func__);
		वापस -EAGAIN;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक cyttsp4_core_resume(काष्ठा device *dev)
अणु
	काष्ठा cyttsp4 *cd = dev_get_drvdata(dev);
	काष्ठा cyttsp4_mt_data *md = &cd->md;
	पूर्णांक rc;

	md->is_suspended = false;

	rc = cyttsp4_core_wake(cd);
	अगर (rc < 0) अणु
		dev_err(dev, "%s: Error on wake\n", __func__);
		वापस -EAGAIN;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

स्थिर काष्ठा dev_pm_ops cyttsp4_pm_ops = अणु
	SET_SYSTEM_SLEEP_PM_OPS(cyttsp4_core_suspend, cyttsp4_core_resume)
	SET_RUNTIME_PM_OPS(cyttsp4_core_suspend, cyttsp4_core_resume, शून्य)
पूर्ण;
EXPORT_SYMBOL_GPL(cyttsp4_pm_ops);

अटल पूर्णांक cyttsp4_mt_खोलो(काष्ठा input_dev *input)
अणु
	pm_runसमय_get(input->dev.parent);
	वापस 0;
पूर्ण

अटल व्योम cyttsp4_mt_बंद(काष्ठा input_dev *input)
अणु
	काष्ठा cyttsp4_mt_data *md = input_get_drvdata(input);
	mutex_lock(&md->report_lock);
	अगर (!md->is_suspended)
		pm_runसमय_put(input->dev.parent);
	mutex_unlock(&md->report_lock);
पूर्ण


अटल पूर्णांक cyttsp4_setup_input_device(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा device *dev = cd->dev;
	काष्ठा cyttsp4_mt_data *md = &cd->md;
	पूर्णांक संकेत = CY_IGNORE_VALUE;
	पूर्णांक max_x, max_y, max_p, min, max;
	पूर्णांक max_x_पंचांगp, max_y_पंचांगp;
	पूर्णांक i;
	पूर्णांक rc;

	dev_vdbg(dev, "%s: Initialize event signals\n", __func__);
	__set_bit(EV_ABS, md->input->evbit);
	__set_bit(EV_REL, md->input->evbit);
	__set_bit(EV_KEY, md->input->evbit);

	max_x_पंचांगp = md->si->si_ofs.max_x;
	max_y_पंचांगp = md->si->si_ofs.max_y;

	/* get maximum values from the sysinfo data */
	अगर (md->pdata->flags & CY_FLAG_FLIP) अणु
		max_x = max_y_पंचांगp - 1;
		max_y = max_x_पंचांगp - 1;
	पूर्ण अन्यथा अणु
		max_x = max_x_पंचांगp - 1;
		max_y = max_y_पंचांगp - 1;
	पूर्ण
	max_p = md->si->si_ofs.max_p;

	/* set event संकेत capabilities */
	क्रम (i = 0; i < (md->pdata->frmwrk->size / CY_NUM_ABS_SET); i++) अणु
		संकेत = md->pdata->frmwrk->असल
			[(i * CY_NUM_ABS_SET) + CY_SIGNAL_OST];
		अगर (संकेत != CY_IGNORE_VALUE) अणु
			__set_bit(संकेत, md->input->असलbit);
			min = md->pdata->frmwrk->असल
				[(i * CY_NUM_ABS_SET) + CY_MIN_OST];
			max = md->pdata->frmwrk->असल
				[(i * CY_NUM_ABS_SET) + CY_MAX_OST];
			अगर (i == CY_ABS_ID_OST) अणु
				/* shअगरt track ids करोwn to start at 0 */
				max = max - min;
				min = min - min;
			पूर्ण अन्यथा अगर (i == CY_ABS_X_OST)
				max = max_x;
			अन्यथा अगर (i == CY_ABS_Y_OST)
				max = max_y;
			अन्यथा अगर (i == CY_ABS_P_OST)
				max = max_p;
			input_set_असल_params(md->input, संकेत, min, max,
				md->pdata->frmwrk->असल
				[(i * CY_NUM_ABS_SET) + CY_FUZZ_OST],
				md->pdata->frmwrk->असल
				[(i * CY_NUM_ABS_SET) + CY_FLAT_OST]);
			dev_dbg(dev, "%s: register signal=%02X min=%d max=%d\n",
				__func__, संकेत, min, max);
			अगर ((i == CY_ABS_ID_OST) &&
				(md->si->si_ofs.tch_rec_size <
				CY_TMA4XX_TCH_REC_SIZE))
				अवरोध;
		पूर्ण
	पूर्ण

	input_mt_init_slots(md->input, md->si->si_ofs.tch_असल[CY_TCH_T].max,
			INPUT_MT_सूचीECT);
	rc = input_रेजिस्टर_device(md->input);
	अगर (rc < 0)
		dev_err(dev, "%s: Error, failed register input device r=%d\n",
			__func__, rc);
	वापस rc;
पूर्ण

अटल पूर्णांक cyttsp4_mt_probe(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा device *dev = cd->dev;
	काष्ठा cyttsp4_mt_data *md = &cd->md;
	काष्ठा cyttsp4_mt_platक्रमm_data *pdata = cd->pdata->mt_pdata;
	पूर्णांक rc = 0;

	mutex_init(&md->report_lock);
	md->pdata = pdata;
	/* Create the input device and रेजिस्टर it. */
	dev_vdbg(dev, "%s: Create the input device and register it\n",
		__func__);
	md->input = input_allocate_device();
	अगर (md->input == शून्य) अणु
		dev_err(dev, "%s: Error, failed to allocate input device\n",
			__func__);
		rc = -ENOSYS;
		जाओ error_alloc_failed;
	पूर्ण

	md->input->name = pdata->inp_dev_name;
	scnम_लिखो(md->phys, माप(md->phys)-1, "%s", dev_name(dev));
	md->input->phys = md->phys;
	md->input->id.bustype = cd->bus_ops->bustype;
	md->input->dev.parent = dev;
	md->input->खोलो = cyttsp4_mt_खोलो;
	md->input->बंद = cyttsp4_mt_बंद;
	input_set_drvdata(md->input, md);

	/* get sysinfo */
	md->si = &cd->sysinfo;

	rc = cyttsp4_setup_input_device(cd);
	अगर (rc)
		जाओ error_init_input;

	वापस 0;

error_init_input:
	input_मुक्त_device(md->input);
error_alloc_failed:
	dev_err(dev, "%s failed.\n", __func__);
	वापस rc;
पूर्ण

काष्ठा cyttsp4 *cyttsp4_probe(स्थिर काष्ठा cyttsp4_bus_ops *ops,
		काष्ठा device *dev, u16 irq, माप_प्रकार xfer_buf_size)
अणु
	काष्ठा cyttsp4 *cd;
	काष्ठा cyttsp4_platक्रमm_data *pdata = dev_get_platdata(dev);
	अचिन्हित दीर्घ irq_flags;
	पूर्णांक rc = 0;

	अगर (!pdata || !pdata->core_pdata || !pdata->mt_pdata) अणु
		dev_err(dev, "%s: Missing platform data\n", __func__);
		rc = -ENODEV;
		जाओ error_no_pdata;
	पूर्ण

	cd = kzalloc(माप(*cd), GFP_KERNEL);
	अगर (!cd) अणु
		dev_err(dev, "%s: Error, kzalloc\n", __func__);
		rc = -ENOMEM;
		जाओ error_alloc_data;
	पूर्ण

	cd->xfer_buf = kzalloc(xfer_buf_size, GFP_KERNEL);
	अगर (!cd->xfer_buf) अणु
		dev_err(dev, "%s: Error, kzalloc\n", __func__);
		rc = -ENOMEM;
		जाओ error_मुक्त_cd;
	पूर्ण

	/* Initialize device info */
	cd->dev = dev;
	cd->pdata = pdata;
	cd->cpdata = pdata->core_pdata;
	cd->bus_ops = ops;

	/* Initialize mutexes and spinlocks */
	mutex_init(&cd->प्रणाली_lock);
	mutex_init(&cd->adap_lock);

	/* Initialize रुको queue */
	init_रुकोqueue_head(&cd->रुको_q);

	/* Initialize works */
	INIT_WORK(&cd->startup_work, cyttsp4_startup_work_function);
	INIT_WORK(&cd->watchकरोg_work, cyttsp4_watchकरोg_work);

	/* Initialize IRQ */
	cd->irq = gpio_to_irq(cd->cpdata->irq_gpio);
	अगर (cd->irq < 0) अणु
		rc = -EINVAL;
		जाओ error_मुक्त_xfer;
	पूर्ण

	dev_set_drvdata(dev, cd);

	/* Call platक्रमm init function */
	अगर (cd->cpdata->init) अणु
		dev_dbg(cd->dev, "%s: Init HW\n", __func__);
		rc = cd->cpdata->init(cd->cpdata, 1, cd->dev);
	पूर्ण अन्यथा अणु
		dev_dbg(cd->dev, "%s: No HW INIT function\n", __func__);
		rc = 0;
	पूर्ण
	अगर (rc < 0)
		dev_err(cd->dev, "%s: HW Init fail r=%d\n", __func__, rc);

	dev_dbg(dev, "%s: initialize threaded irq=%d\n", __func__, cd->irq);
	अगर (cd->cpdata->level_irq_udelay > 0)
		/* use level triggered पूर्णांकerrupts */
		irq_flags = IRQF_TRIGGER_LOW | IRQF_ONESHOT;
	अन्यथा
		/* use edge triggered पूर्णांकerrupts */
		irq_flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;

	rc = request_thपढ़ोed_irq(cd->irq, शून्य, cyttsp4_irq, irq_flags,
		dev_name(dev), cd);
	अगर (rc < 0) अणु
		dev_err(dev, "%s: Error, could not request irq\n", __func__);
		जाओ error_request_irq;
	पूर्ण

	/* Setup watchकरोg समयr */
	समयr_setup(&cd->watchकरोg_समयr, cyttsp4_watchकरोg_समयr, 0);

	/*
	 * call startup directly to ensure that the device
	 * is tested beक्रमe leaving the probe
	 */
	rc = cyttsp4_startup(cd);

	/* Do not fail probe अगर startup fails but the device is detected */
	अगर (rc < 0 && cd->mode == CY_MODE_UNKNOWN) अणु
		dev_err(cd->dev, "%s: Fail initial startup r=%d\n",
			__func__, rc);
		जाओ error_startup;
	पूर्ण

	rc = cyttsp4_mt_probe(cd);
	अगर (rc < 0) अणु
		dev_err(dev, "%s: Error, fail mt probe\n", __func__);
		जाओ error_startup;
	पूर्ण

	pm_runसमय_enable(dev);

	वापस cd;

error_startup:
	cancel_work_sync(&cd->startup_work);
	cyttsp4_stop_wd_समयr(cd);
	pm_runसमय_disable(dev);
	cyttsp4_मुक्त_si_ptrs(cd);
	मुक्त_irq(cd->irq, cd);
error_request_irq:
	अगर (cd->cpdata->init)
		cd->cpdata->init(cd->cpdata, 0, dev);
error_मुक्त_xfer:
	kमुक्त(cd->xfer_buf);
error_मुक्त_cd:
	kमुक्त(cd);
error_alloc_data:
error_no_pdata:
	dev_err(dev, "%s failed.\n", __func__);
	वापस ERR_PTR(rc);
पूर्ण
EXPORT_SYMBOL_GPL(cyttsp4_probe);

अटल व्योम cyttsp4_mt_release(काष्ठा cyttsp4_mt_data *md)
अणु
	input_unरेजिस्टर_device(md->input);
	input_set_drvdata(md->input, शून्य);
पूर्ण

पूर्णांक cyttsp4_हटाओ(काष्ठा cyttsp4 *cd)
अणु
	काष्ठा device *dev = cd->dev;

	cyttsp4_mt_release(&cd->md);

	/*
	 * Suspend the device beक्रमe मुक्तing the startup_work and stopping
	 * the watchकरोg since sleep function restarts watchकरोg on failure
	 */
	pm_runसमय_suspend(dev);
	pm_runसमय_disable(dev);

	cancel_work_sync(&cd->startup_work);

	cyttsp4_stop_wd_समयr(cd);

	मुक्त_irq(cd->irq, cd);
	अगर (cd->cpdata->init)
		cd->cpdata->init(cd->cpdata, 0, dev);
	cyttsp4_मुक्त_si_ptrs(cd);
	kमुक्त(cd);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(cyttsp4_हटाओ);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Cypress TrueTouch(R) Standard touchscreen core driver");
MODULE_AUTHOR("Cypress");
