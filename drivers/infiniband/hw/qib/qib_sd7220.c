<शैली गुरु>
/*
 * Copyright (c) 2013 Intel Corporation. All rights reserved.
 * Copyright (c) 2006 - 2012 QLogic Corporation. All rights reserved.
 * Copyright (c) 2003, 2004, 2005, 2006 PathScale, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/*
 * This file contains all of the code that is specअगरic to the SerDes
 * on the QLogic_IB 7220 chip.
 */

#समावेश <linux/pci.h>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/firmware.h>

#समावेश "qib.h"
#समावेश "qib_7220.h"

#घोषणा SD7220_FW_NAME "qlogic/sd7220.fw"
MODULE_FIRMWARE(SD7220_FW_NAME);

/*
 * Same as in qib_iba7220.c, but just the रेजिस्टरs needed here.
 * Could move whole set to qib_7220.h, but decided better to keep
 * local.
 */
#घोषणा KREG_IDX(regname) (QIB_7220_##regname##_OFFS / माप(u64))
#घोषणा kr_hwerrclear KREG_IDX(HwErrClear)
#घोषणा kr_hwerrmask KREG_IDX(HwErrMask)
#घोषणा kr_hwerrstatus KREG_IDX(HwErrStatus)
#घोषणा kr_ibcstatus KREG_IDX(IBCStatus)
#घोषणा kr_ibserdesctrl KREG_IDX(IBSerDesCtrl)
#घोषणा kr_scratch KREG_IDX(Scratch)
#घोषणा kr_xgxs_cfg KREG_IDX(XGXSCfg)
/* these are used only here, not in qib_iba7220.c */
#घोषणा kr_ibsd_epb_access_ctrl KREG_IDX(ibsd_epb_access_ctrl)
#घोषणा kr_ibsd_epb_transaction_reg KREG_IDX(ibsd_epb_transaction_reg)
#घोषणा kr_pciesd_epb_transaction_reg KREG_IDX(pciesd_epb_transaction_reg)
#घोषणा kr_pciesd_epb_access_ctrl KREG_IDX(pciesd_epb_access_ctrl)
#घोषणा kr_serdes_ddsrxeq0 KREG_IDX(SerDes_DDSRXEQ0)

/*
 * The IBSerDesMappTable is a memory that holds values to be stored in
 * various SerDes रेजिस्टरs by IBC.
 */
#घोषणा kr_serdes_maptable KREG_IDX(IBSerDesMappTable)

/*
 * Below used क्रम sdnum parameter, selecting one of the two sections
 * used क्रम PCIe, or the single SerDes used क्रम IB.
 */
#घोषणा PCIE_SERDES0 0
#घोषणा PCIE_SERDES1 1

/*
 * The EPB requires addressing in a particular क्रमm. EPB_LOC() is पूर्णांकended
 * to make #definitions a little more पढ़ोable.
 */
#घोषणा EPB_ADDR_SHF 8
#घोषणा EPB_LOC(chn, elt, reg) \
	(((elt & 0xf) | ((chn & 7) << 4) | ((reg & 0x3f) << 9)) << \
	 EPB_ADDR_SHF)
#घोषणा EPB_IB_QUAD0_CS_SHF (25)
#घोषणा EPB_IB_QUAD0_CS (1U <<  EPB_IB_QUAD0_CS_SHF)
#घोषणा EPB_IB_UC_CS_SHF (26)
#घोषणा EPB_PCIE_UC_CS_SHF (27)
#घोषणा EPB_GLOBAL_WR (1U << (EPB_ADDR_SHF + 8))

/* Forward declarations. */
अटल पूर्णांक qib_sd7220_reg_mod(काष्ठा qib_devdata *dd, पूर्णांक sdnum, u32 loc,
			      u32 data, u32 mask);
अटल पूर्णांक ibsd_mod_allchnls(काष्ठा qib_devdata *dd, पूर्णांक loc, पूर्णांक val,
			     पूर्णांक mask);
अटल पूर्णांक qib_sd_trimकरोne_poll(काष्ठा qib_devdata *dd);
अटल व्योम qib_sd_trimकरोne_monitor(काष्ठा qib_devdata *dd, स्थिर अक्षर *where);
अटल पूर्णांक qib_sd_setvals(काष्ठा qib_devdata *dd);
अटल पूर्णांक qib_sd_early(काष्ठा qib_devdata *dd);
अटल पूर्णांक qib_sd_dactrim(काष्ठा qib_devdata *dd);
अटल पूर्णांक qib_पूर्णांकernal_presets(काष्ठा qib_devdata *dd);
/* Tweak the रेजिस्टर (CMUCTRL5) that contains the TRIMSELF controls */
अटल पूर्णांक qib_sd_trimself(काष्ठा qib_devdata *dd, पूर्णांक val);
अटल पूर्णांक epb_access(काष्ठा qib_devdata *dd, पूर्णांक sdnum, पूर्णांक claim);
अटल पूर्णांक qib_sd7220_ib_load(काष्ठा qib_devdata *dd,
			      स्थिर काष्ठा firmware *fw);
अटल पूर्णांक qib_sd7220_ib_vfy(काष्ठा qib_devdata *dd,
			     स्थिर काष्ठा firmware *fw);

/*
 * Below keeps track of whether the "once per power-on" initialization has
 * been करोne, because uC code Version 1.32.17 or higher allows the uC to
 * be reset at will, and Automatic Equalization may require it. So the
 * state of the reset "pin", is no दीर्घer valid. Instead, we check क्रम the
 * actual uC code having been loaded.
 */
अटल पूर्णांक qib_ibsd_ucode_loaded(काष्ठा qib_pportdata *ppd,
				 स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;

	अगर (!dd->cspec->serdes_first_init_करोne &&
	    qib_sd7220_ib_vfy(dd, fw) > 0)
		dd->cspec->serdes_first_init_करोne = 1;
	वापस dd->cspec->serdes_first_init_करोne;
पूर्ण

/* repeat #घोषणा क्रम local use. "Real" #घोषणा is in qib_iba7220.c */
#घोषणा QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR      0x0000004000000000ULL
#घोषणा IB_MPREG5 (EPB_LOC(6, 0, 0xE) | (1L << EPB_IB_UC_CS_SHF))
#घोषणा IB_MPREG6 (EPB_LOC(6, 0, 0xF) | (1U << EPB_IB_UC_CS_SHF))
#घोषणा UC_PAR_CLR_D 8
#घोषणा UC_PAR_CLR_M 0xC
#घोषणा IB_CTRL2(chn) (EPB_LOC(chn, 7, 3) | EPB_IB_QUAD0_CS)
#घोषणा START_EQ1(chan) EPB_LOC(chan, 7, 0x27)

व्योम qib_sd7220_clr_ibpar(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret;

	/* clear, then re-enable parity errs */
	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6,
		UC_PAR_CLR_D, UC_PAR_CLR_M);
	अगर (ret < 0) अणु
		qib_dev_err(dd, "Failed clearing IBSerDes Parity err\n");
		जाओ bail;
	पूर्ण
	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6, 0,
		UC_PAR_CLR_M);

	qib_पढ़ो_kreg32(dd, kr_scratch);
	udelay(4);
	qib_ग_लिखो_kreg(dd, kr_hwerrclear,
		QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR);
	qib_पढ़ो_kreg32(dd, kr_scratch);
bail:
	वापस;
पूर्ण

/*
 * After a reset or other unusual event, the epb पूर्णांकerface may need
 * to be re-synchronized, between the host and the uC.
 * वापसs <0 क्रम failure to resync within IBSD_RESYNC_TRIES (not expected)
 */
#घोषणा IBSD_RESYNC_TRIES 3
#घोषणा IB_PGUDP(chn) (EPB_LOC((chn), 2, 1) | EPB_IB_QUAD0_CS)
#घोषणा IB_CMUDONE(chn) (EPB_LOC((chn), 7, 0xF) | EPB_IB_QUAD0_CS)

अटल पूर्णांक qib_resync_ibepb(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret, pat, tries, chn;
	u32 loc;

	ret = -1;
	chn = 0;
	क्रम (tries = 0; tries < (4 * IBSD_RESYNC_TRIES); ++tries) अणु
		loc = IB_PGUDP(chn);
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, 0, 0);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed read in resync\n");
			जारी;
		पूर्ण
		अगर (ret != 0xF0 && ret != 0x55 && tries == 0)
			qib_dev_err(dd, "unexpected pattern in resync\n");
		pat = ret ^ 0xA5; /* alternate F0 and 55 */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, pat, 0xFF);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed write in resync\n");
			जारी;
		पूर्ण
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, 0, 0);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed re-read in resync\n");
			जारी;
		पूर्ण
		अगर (ret != pat) अणु
			qib_dev_err(dd, "Failed compare1 in resync\n");
			जारी;
		पूर्ण
		loc = IB_CMUDONE(chn);
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, 0, 0);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed CMUDONE rd in resync\n");
			जारी;
		पूर्ण
		अगर ((ret & 0x70) != ((chn << 4) | 0x40)) अणु
			qib_dev_err(dd, "Bad CMUDONE value %02X, chn %d\n",
				    ret, chn);
			जारी;
		पूर्ण
		अगर (++chn == 4)
			अवरोध;  /* Success */
	पूर्ण
	वापस (ret > 0) ? 0 : ret;
पूर्ण

/*
 * Localize the stuff that should be करोne to change IB uC reset
 * वापसs <0 क्रम errors.
 */
अटल पूर्णांक qib_ibsd_reset(काष्ठा qib_devdata *dd, पूर्णांक निश्चित_rst)
अणु
	u64 rst_val;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flags;

	rst_val = qib_पढ़ो_kreg64(dd, kr_ibserdesctrl);
	अगर (निश्चित_rst) अणु
		/*
		 * Venकरोr recommends "interrupting" uC beक्रमe reset, to
		 * minimize possible glitches.
		 */
		spin_lock_irqsave(&dd->cspec->sdepb_lock, flags);
		epb_access(dd, IB_7220_SERDES, 1);
		rst_val |= 1ULL;
		/* Squelch possible parity error from _निश्चितing_ reset */
		qib_ग_लिखो_kreg(dd, kr_hwerrmask,
			       dd->cspec->hwerrmask &
			       ~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR);
		qib_ग_लिखो_kreg(dd, kr_ibserdesctrl, rst_val);
		/* flush ग_लिखो, delay to ensure it took effect */
		qib_पढ़ो_kreg32(dd, kr_scratch);
		udelay(2);
		/* once it's reset, can हटाओ पूर्णांकerrupt */
		epb_access(dd, IB_7220_SERDES, -1);
		spin_unlock_irqrestore(&dd->cspec->sdepb_lock, flags);
	पूर्ण अन्यथा अणु
		/*
		 * Beक्रमe we de-निश्चित reset, we need to deal with
		 * possible glitch on the Parity-error line.
		 * Suppress it around the reset, both in chip-level
		 * hwerrmask and in IB uC control reg. uC will allow
		 * it again during startup.
		 */
		u64 val;

		rst_val &= ~(1ULL);
		qib_ग_लिखो_kreg(dd, kr_hwerrmask,
			       dd->cspec->hwerrmask &
			       ~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR);

		ret = qib_resync_ibepb(dd);
		अगर (ret < 0)
			qib_dev_err(dd, "unable to re-sync IB EPB\n");

		/* set uC control regs to suppress parity errs */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG5, 1, 1);
		अगर (ret < 0)
			जाओ bail;
		/* IB uC code past Version 1.32.17 allow suppression of wकरोg */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6, 0x80,
			0x80);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed to set WDOG disable\n");
			जाओ bail;
		पूर्ण
		qib_ग_लिखो_kreg(dd, kr_ibserdesctrl, rst_val);
		/* flush ग_लिखो, delay क्रम startup */
		qib_पढ़ो_kreg32(dd, kr_scratch);
		udelay(1);
		/* clear, then re-enable parity errs */
		qib_sd7220_clr_ibpar(dd);
		val = qib_पढ़ो_kreg64(dd, kr_hwerrstatus);
		अगर (val & QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR) अणु
			qib_dev_err(dd, "IBUC Parity still set after RST\n");
			dd->cspec->hwerrmask &=
				~QLOGIC_IB_HWE_IB_UC_MEMORYPARITYERR;
		पूर्ण
		qib_ग_लिखो_kreg(dd, kr_hwerrmask,
			dd->cspec->hwerrmask);
	पूर्ण

bail:
	वापस ret;
पूर्ण

अटल व्योम qib_sd_trimकरोne_monitor(काष्ठा qib_devdata *dd,
	स्थिर अक्षर *where)
अणु
	पूर्णांक ret, chn, baduns;
	u64 val;

	अगर (!where)
		where = "?";

	/* give समय क्रम reset to settle out in EPB */
	udelay(2);

	ret = qib_resync_ibepb(dd);
	अगर (ret < 0)
		qib_dev_err(dd, "not able to re-sync IB EPB (%s)\n", where);

	/* Do "sacrificial read" to get EPB in sane state after reset */
	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_CTRL2(0), 0, 0);
	अगर (ret < 0)
		qib_dev_err(dd, "Failed TRIMDONE 1st read, (%s)\n", where);

	/* Check/show "summary" Trim-करोne bit in IBCStatus */
	val = qib_पढ़ो_kreg64(dd, kr_ibcstatus);
	अगर (!(val & (1ULL << 11)))
		qib_dev_err(dd, "IBCS TRIMDONE clear (%s)\n", where);
	/*
	 * Do "dummy read/mod/wr" to get EPB in sane state after reset
	 * The शेष value क्रम MPREG6 is 0.
	 */
	udelay(2);

	ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, IB_MPREG6, 0x80, 0x80);
	अगर (ret < 0)
		qib_dev_err(dd, "Failed Dummy RMW, (%s)\n", where);
	udelay(10);

	baduns = 0;

	क्रम (chn = 3; chn >= 0; --chn) अणु
		/* Read CTRL reg क्रम each channel to check TRIMDONE */
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
			IB_CTRL2(chn), 0, 0);
		अगर (ret < 0)
			qib_dev_err(dd,
				"Failed checking TRIMDONE, chn %d (%s)\n",
				chn, where);

		अगर (!(ret & 0x10)) अणु
			पूर्णांक probe;

			baduns |= (1 << chn);
			qib_dev_err(dd,
				"TRIMDONE cleared on chn %d (%02X). (%s)\n",
				chn, ret, where);
			probe = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_PGUDP(0), 0, 0);
			qib_dev_err(dd, "probe is %d (%02X)\n",
				probe, probe);
			probe = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_CTRL2(chn), 0, 0);
			qib_dev_err(dd, "re-read: %d (%02X)\n",
				probe, probe);
			ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_CTRL2(chn), 0x10, 0x10);
			अगर (ret < 0)
				qib_dev_err(dd,
					"Err on TRIMDONE rewrite1\n");
		पूर्ण
	पूर्ण
	क्रम (chn = 3; chn >= 0; --chn) अणु
		/* Read CTRL reg क्रम each channel to check TRIMDONE */
		अगर (baduns & (1 << chn)) अणु
			qib_dev_err(dd,
				"Resetting TRIMDONE on chn %d (%s)\n",
				chn, where);
			ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
				IB_CTRL2(chn), 0x10, 0x10);
			अगर (ret < 0)
				qib_dev_err(dd,
					"Failed re-setting TRIMDONE, chn %d (%s)\n",
					chn, where);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Below is portion of IBA7220-specअगरic bringup_serdes() that actually
 * deals with रेजिस्टरs and memory within the SerDes itself.
 * Post IB uC code version 1.32.17, was_reset being 1 is not really
 * inक्रमmative, so we द्विगुन-check.
 */
पूर्णांक qib_sd7220_init(काष्ठा qib_devdata *dd)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret = 1; /* शेष to failure */
	पूर्णांक first_reset, was_reset;

	/* SERDES MPU reset recorded in D0 */
	was_reset = (qib_पढ़ो_kreg64(dd, kr_ibserdesctrl) & 1);
	अगर (!was_reset) अणु
		/* entered with reset not निश्चितed, we need to करो it */
		qib_ibsd_reset(dd, 1);
		qib_sd_trimकरोne_monitor(dd, "Driver-reload");
	पूर्ण

	ret = request_firmware(&fw, SD7220_FW_NAME, &dd->pcidev->dev);
	अगर (ret) अणु
		qib_dev_err(dd, "Failed to load IB SERDES image\n");
		जाओ करोne;
	पूर्ण

	/* Substitute our deduced value क्रम was_reset */
	ret = qib_ibsd_ucode_loaded(dd->pport, fw);
	अगर (ret < 0)
		जाओ bail;

	first_reset = !ret; /* First reset अगर IBSD uCode not yet loaded */
	/*
	 * Alter some regs per venकरोr latest करोc, reset-शेषs
	 * are not right क्रम IB.
	 */
	ret = qib_sd_early(dd);
	अगर (ret < 0) अणु
		qib_dev_err(dd, "Failed to set IB SERDES early defaults\n");
		जाओ bail;
	पूर्ण
	/*
	 * Set DAC manual trim IB.
	 * We only करो this once after chip has been reset (usually
	 * same as once per प्रणाली boot).
	 */
	अगर (first_reset) अणु
		ret = qib_sd_dactrim(dd);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed IB SERDES DAC trim\n");
			जाओ bail;
		पूर्ण
	पूर्ण
	/*
	 * Set various रेजिस्टरs (DDS and RXEQ) that will be
	 * controlled by IBC (in 1.2 mode) to reasonable preset values
	 * Calling the "internal" version aव्योमs the "check for needed"
	 * and "trimdone monitor" that might be counter-productive.
	 */
	ret = qib_पूर्णांकernal_presets(dd);
	अगर (ret < 0) अणु
		qib_dev_err(dd, "Failed to set IB SERDES presets\n");
		जाओ bail;
	पूर्ण
	ret = qib_sd_trimself(dd, 0x80);
	अगर (ret < 0) अणु
		qib_dev_err(dd, "Failed to set IB SERDES TRIMSELF\n");
		जाओ bail;
	पूर्ण

	/* Load image, then try to verअगरy */
	ret = 0;        /* Assume success */
	अगर (first_reset) अणु
		पूर्णांक vfy;
		पूर्णांक trim_करोne;

		ret = qib_sd7220_ib_load(dd, fw);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed to load IB SERDES image\n");
			जाओ bail;
		पूर्ण अन्यथा अणु
			/* Loaded image, try to verअगरy */
			vfy = qib_sd7220_ib_vfy(dd, fw);
			अगर (vfy != ret) अणु
				qib_dev_err(dd, "SERDES PRAM VFY failed\n");
				जाओ bail;
			पूर्ण /* end अगर verअगरied */
		पूर्ण /* end अगर loaded */

		/*
		 * Loaded and verअगरied. Almost good...
		 * hold "success" in ret
		 */
		ret = 0;
		/*
		 * Prev steps all worked, जारी bringup
		 * De-निश्चित RESET to uC, only in first reset, to allow
		 * trimming.
		 *
		 * Since our शेष setup sets START_EQ1 to
		 * PRESET, we need to clear that क्रम this very first run.
		 */
		ret = ibsd_mod_allchnls(dd, START_EQ1(0), 0, 0x38);
		अगर (ret < 0) अणु
			qib_dev_err(dd, "Failed clearing START_EQ1\n");
			जाओ bail;
		पूर्ण

		qib_ibsd_reset(dd, 0);
		/*
		 * If this is not the first reset, trimकरोne should be set
		 * alपढ़ोy. We may need to check about this.
		 */
		trim_करोne = qib_sd_trimकरोne_poll(dd);
		/*
		 * Whether or not trimकरोne succeeded, we need to put the
		 * uC back पूर्णांकo reset to aव्योम a possible fight with the
		 * IBC state-machine.
		 */
		qib_ibsd_reset(dd, 1);

		अगर (!trim_करोne) अणु
			qib_dev_err(dd, "No TRIMDONE seen\n");
			जाओ bail;
		पूर्ण
		/*
		 * DEBUG: check each समय we reset अगर trimकरोne bits have
		 * gotten cleared, and re-set them.
		 */
		qib_sd_trimकरोne_monitor(dd, "First-reset");
		/* Remember so we करो not re-करो the load, dactrim, etc. */
		dd->cspec->serdes_first_init_करोne = 1;
	पूर्ण
	/*
	 * setup क्रम channel training and load values क्रम
	 * RxEq and DDS in tables used by IBC in IB1.2 mode
	 */
	ret = 0;
	अगर (qib_sd_setvals(dd) >= 0)
		जाओ करोne;
bail:
	ret = 1;
करोne:
	/* start relock समयr regardless, but start at 1 second */
	set_7220_relock_poll(dd, -1);

	release_firmware(fw);
	वापस ret;
पूर्ण

#घोषणा EPB_ACC_REQ 1
#घोषणा EPB_ACC_GNT 0x100
#घोषणा EPB_DATA_MASK 0xFF
#घोषणा EPB_RD (1ULL << 24)
#घोषणा EPB_TRANS_RDY (1ULL << 31)
#घोषणा EPB_TRANS_ERR (1ULL << 30)
#घोषणा EPB_TRANS_TRIES 5

/*
 * query, claim, release ownership of the EPB (External Parallel Bus)
 * क्रम a specअगरied SERDES.
 * the "claim" parameter is >0 to claim, <0 to release, 0 to query.
 * Returns <0 क्रम errors, >0 अगर we had ownership, अन्यथा 0.
 */
अटल पूर्णांक epb_access(काष्ठा qib_devdata *dd, पूर्णांक sdnum, पूर्णांक claim)
अणु
	u16 acc;
	u64 accval;
	पूर्णांक owned = 0;
	u64 oct_sel = 0;

	चयन (sdnum) अणु
	हाल IB_7220_SERDES:
		/*
		 * The IB SERDES "ownership" is fairly simple. A single each
		 * request/grant.
		 */
		acc = kr_ibsd_epb_access_ctrl;
		अवरोध;

	हाल PCIE_SERDES0:
	हाल PCIE_SERDES1:
		/* PCIe SERDES has two "octants", need to select which */
		acc = kr_pciesd_epb_access_ctrl;
		oct_sel = (2 << (sdnum - PCIE_SERDES0));
		अवरोध;

	शेष:
		वापस 0;
	पूर्ण

	/* Make sure any outstanding transaction was seen */
	qib_पढ़ो_kreg32(dd, kr_scratch);
	udelay(15);

	accval = qib_पढ़ो_kreg32(dd, acc);

	owned = !!(accval & EPB_ACC_GNT);
	अगर (claim < 0) अणु
		/* Need to release */
		u64 pollval;
		/*
		 * The only ग_लिखोable bits are the request and CS.
		 * Both should be clear
		 */
		u64 newval = 0;

		qib_ग_लिखो_kreg(dd, acc, newval);
		/* First पढ़ो after ग_लिखो is not trustworthy */
		pollval = qib_पढ़ो_kreg32(dd, acc);
		udelay(5);
		pollval = qib_पढ़ो_kreg32(dd, acc);
		अगर (pollval & EPB_ACC_GNT)
			owned = -1;
	पूर्ण अन्यथा अगर (claim > 0) अणु
		/* Need to claim */
		u64 pollval;
		u64 newval = EPB_ACC_REQ | oct_sel;

		qib_ग_लिखो_kreg(dd, acc, newval);
		/* First पढ़ो after ग_लिखो is not trustworthy */
		pollval = qib_पढ़ो_kreg32(dd, acc);
		udelay(5);
		pollval = qib_पढ़ो_kreg32(dd, acc);
		अगर (!(pollval & EPB_ACC_GNT))
			owned = -1;
	पूर्ण
	वापस owned;
पूर्ण

/*
 * Lemma to deal with race condition of ग_लिखो..पढ़ो to epb regs
 */
अटल पूर्णांक epb_trans(काष्ठा qib_devdata *dd, u16 reg, u64 i_val, u64 *o_vp)
अणु
	पूर्णांक tries;
	u64 transval;

	qib_ग_लिखो_kreg(dd, reg, i_val);
	/* Throw away first पढ़ो, as RDY bit may be stale */
	transval = qib_पढ़ो_kreg64(dd, reg);

	क्रम (tries = EPB_TRANS_TRIES; tries; --tries) अणु
		transval = qib_पढ़ो_kreg32(dd, reg);
		अगर (transval & EPB_TRANS_RDY)
			अवरोध;
		udelay(5);
	पूर्ण
	अगर (transval & EPB_TRANS_ERR)
		वापस -1;
	अगर (tries > 0 && o_vp)
		*o_vp = transval;
	वापस tries;
पूर्ण

/**
 * qib_sd7220_reg_mod - modअगरy SERDES रेजिस्टर
 * @dd: the qlogic_ib device
 * @sdnum: which SERDES to access
 * @loc: location - channel, element, रेजिस्टर, as packed by EPB_LOC() macro.
 * @wd: Write Data - value to set in रेजिस्टर
 * @mask: ones where data should be spliced पूर्णांकo reg.
 *
 * Basic रेजिस्टर पढ़ो/modअगरy/ग_लिखो, with un-needed acesses elided. That is,
 * a mask of zero will prevent ग_लिखो, जबतक a mask of 0xFF will prevent पढ़ो.
 * वापसs current (presumed, अगर a ग_लिखो was करोne) contents of selected
 * रेजिस्टर, or <0 अगर errors.
 */
अटल पूर्णांक qib_sd7220_reg_mod(काष्ठा qib_devdata *dd, पूर्णांक sdnum, u32 loc,
			      u32 wd, u32 mask)
अणु
	u16 trans;
	u64 transval;
	पूर्णांक owned;
	पूर्णांक tries, ret;
	अचिन्हित दीर्घ flags;

	चयन (sdnum) अणु
	हाल IB_7220_SERDES:
		trans = kr_ibsd_epb_transaction_reg;
		अवरोध;

	हाल PCIE_SERDES0:
	हाल PCIE_SERDES1:
		trans = kr_pciesd_epb_transaction_reg;
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	/*
	 * All access is locked in software (vs other host thपढ़ोs) and
	 * hardware (vs uC access).
	 */
	spin_lock_irqsave(&dd->cspec->sdepb_lock, flags);

	owned = epb_access(dd, sdnum, 1);
	अगर (owned < 0) अणु
		spin_unlock_irqrestore(&dd->cspec->sdepb_lock, flags);
		वापस -1;
	पूर्ण
	क्रम (tries = EPB_TRANS_TRIES; tries; --tries) अणु
		transval = qib_पढ़ो_kreg32(dd, trans);
		अगर (transval & EPB_TRANS_RDY)
			अवरोध;
		udelay(5);
	पूर्ण

	अगर (tries > 0) अणु
		tries = 1;      /* to make पढ़ो-skip work */
		अगर (mask != 0xFF) अणु
			/*
			 * Not a pure ग_लिखो, so need to पढ़ो.
			 * loc encodes chip-select as well as address
			 */
			transval = loc | EPB_RD;
			tries = epb_trans(dd, trans, transval, &transval);
		पूर्ण
		अगर (tries > 0 && mask != 0) अणु
			/*
			 * Not a pure पढ़ो, so need to ग_लिखो.
			 */
			wd = (wd & mask) | (transval & ~mask);
			transval = loc | (wd & EPB_DATA_MASK);
			tries = epb_trans(dd, trans, transval, &transval);
		पूर्ण
	पूर्ण
	/* अन्यथा, failed to see पढ़ोy, what error-handling? */

	/*
	 * Release bus. Failure is an error.
	 */
	अगर (epb_access(dd, sdnum, -1) < 0)
		ret = -1;
	अन्यथा
		ret = transval & EPB_DATA_MASK;

	spin_unlock_irqrestore(&dd->cspec->sdepb_lock, flags);
	अगर (tries <= 0)
		ret = -1;
	वापस ret;
पूर्ण

#घोषणा EPB_ROM_R (2)
#घोषणा EPB_ROM_W (1)
/*
 * Below, all uC-related, use appropriate UC_CS, depending
 * on which SerDes is used.
 */
#घोषणा EPB_UC_CTL EPB_LOC(6, 0, 0)
#घोषणा EPB_MADDRL EPB_LOC(6, 0, 2)
#घोषणा EPB_MADDRH EPB_LOC(6, 0, 3)
#घोषणा EPB_ROMDATA EPB_LOC(6, 0, 4)
#घोषणा EPB_RAMDATA EPB_LOC(6, 0, 5)

/* Transfer date to/from uC Program RAM of IB or PCIe SerDes */
अटल पूर्णांक qib_sd7220_ram_xfer(काष्ठा qib_devdata *dd, पूर्णांक sdnum, u32 loc,
			       u8 *buf, पूर्णांक cnt, पूर्णांक rd_notwr)
अणु
	u16 trans;
	u64 transval;
	u64 csbit;
	पूर्णांक owned;
	पूर्णांक tries;
	पूर्णांक sofar;
	पूर्णांक addr;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	/* Pick appropriate transaction reg and "Chip select" क्रम this serdes */
	चयन (sdnum) अणु
	हाल IB_7220_SERDES:
		csbit = 1ULL << EPB_IB_UC_CS_SHF;
		trans = kr_ibsd_epb_transaction_reg;
		अवरोध;

	हाल PCIE_SERDES0:
	हाल PCIE_SERDES1:
		/* PCIe SERDES has uC "chip select" in dअगरferent bit, too */
		csbit = 1ULL << EPB_PCIE_UC_CS_SHF;
		trans = kr_pciesd_epb_transaction_reg;
		अवरोध;

	शेष:
		वापस -1;
	पूर्ण

	spin_lock_irqsave(&dd->cspec->sdepb_lock, flags);

	owned = epb_access(dd, sdnum, 1);
	अगर (owned < 0) अणु
		spin_unlock_irqrestore(&dd->cspec->sdepb_lock, flags);
		वापस -1;
	पूर्ण

	/*
	 * In future code, we may need to distinguish several address ranges,
	 * and select various memories based on this. For now, just trim
	 * "loc" (location including address and memory select) to
	 * "addr" (address within memory). we will only support PRAM
	 * The memory is 8KB.
	 */
	addr = loc & 0x1FFF;
	क्रम (tries = EPB_TRANS_TRIES; tries; --tries) अणु
		transval = qib_पढ़ो_kreg32(dd, trans);
		अगर (transval & EPB_TRANS_RDY)
			अवरोध;
		udelay(5);
	पूर्ण

	sofar = 0;
	अगर (tries > 0) अणु
		/*
		 * Every "memory" access is करोubly-indirect.
		 * We set two bytes of address, then पढ़ो/ग_लिखो
		 * one or mores bytes of data.
		 */

		/* First, we set control to "Read" or "Write" */
		transval = csbit | EPB_UC_CTL |
			(rd_notwr ? EPB_ROM_R : EPB_ROM_W);
		tries = epb_trans(dd, trans, transval, &transval);
		जबतक (tries > 0 && sofar < cnt) अणु
			अगर (!sofar) अणु
				/* Only set address at start of chunk */
				पूर्णांक addrbyte = (addr + sofar) >> 8;

				transval = csbit | EPB_MADDRH | addrbyte;
				tries = epb_trans(dd, trans, transval,
						  &transval);
				अगर (tries <= 0)
					अवरोध;
				addrbyte = (addr + sofar) & 0xFF;
				transval = csbit | EPB_MADDRL | addrbyte;
				tries = epb_trans(dd, trans, transval,
						 &transval);
				अगर (tries <= 0)
					अवरोध;
			पूर्ण

			अगर (rd_notwr)
				transval = csbit | EPB_ROMDATA | EPB_RD;
			अन्यथा
				transval = csbit | EPB_ROMDATA | buf[sofar];
			tries = epb_trans(dd, trans, transval, &transval);
			अगर (tries <= 0)
				अवरोध;
			अगर (rd_notwr)
				buf[sofar] = transval & EPB_DATA_MASK;
			++sofar;
		पूर्ण
		/* Finally, clear control-bit क्रम Read or Write */
		transval = csbit | EPB_UC_CTL;
		tries = epb_trans(dd, trans, transval, &transval);
	पूर्ण

	ret = sofar;
	/* Release bus. Failure is an error */
	अगर (epb_access(dd, sdnum, -1) < 0)
		ret = -1;

	spin_unlock_irqrestore(&dd->cspec->sdepb_lock, flags);
	अगर (tries <= 0)
		ret = -1;
	वापस ret;
पूर्ण

#घोषणा PROG_CHUNK 64

अटल पूर्णांक qib_sd7220_prog_ld(काष्ठा qib_devdata *dd, पूर्णांक sdnum,
			      स्थिर u8 *img, पूर्णांक len, पूर्णांक offset)
अणु
	पूर्णांक cnt, sofar, req;

	sofar = 0;
	जबतक (sofar < len) अणु
		req = len - sofar;
		अगर (req > PROG_CHUNK)
			req = PROG_CHUNK;
		cnt = qib_sd7220_ram_xfer(dd, sdnum, offset + sofar,
					  (u8 *)img + sofar, req, 0);
		अगर (cnt < req) अणु
			sofar = -1;
			अवरोध;
		पूर्ण
		sofar += req;
	पूर्ण
	वापस sofar;
पूर्ण

#घोषणा VFY_CHUNK 64
#घोषणा SD_PRAM_ERROR_LIMIT 42

अटल पूर्णांक qib_sd7220_prog_vfy(काष्ठा qib_devdata *dd, पूर्णांक sdnum,
			       स्थिर u8 *img, पूर्णांक len, पूर्णांक offset)
अणु
	पूर्णांक cnt, sofar, req, idx, errors;
	अचिन्हित अक्षर पढ़ोback[VFY_CHUNK];

	errors = 0;
	sofar = 0;
	जबतक (sofar < len) अणु
		req = len - sofar;
		अगर (req > VFY_CHUNK)
			req = VFY_CHUNK;
		cnt = qib_sd7220_ram_xfer(dd, sdnum, sofar + offset,
					  पढ़ोback, req, 1);
		अगर (cnt < req) अणु
			/* failed in पढ़ो itself */
			sofar = -1;
			अवरोध;
		पूर्ण
		क्रम (idx = 0; idx < cnt; ++idx) अणु
			अगर (पढ़ोback[idx] != img[idx+sofar])
				++errors;
		पूर्ण
		sofar += cnt;
	पूर्ण
	वापस errors ? -errors : sofar;
पूर्ण

अटल पूर्णांक
qib_sd7220_ib_load(काष्ठा qib_devdata *dd, स्थिर काष्ठा firmware *fw)
अणु
	वापस qib_sd7220_prog_ld(dd, IB_7220_SERDES, fw->data, fw->size, 0);
पूर्ण

अटल पूर्णांक
qib_sd7220_ib_vfy(काष्ठा qib_devdata *dd, स्थिर काष्ठा firmware *fw)
अणु
	वापस qib_sd7220_prog_vfy(dd, IB_7220_SERDES, fw->data, fw->size, 0);
पूर्ण

/*
 * IRQ not set up at this poपूर्णांक in init, so we poll.
 */
#घोषणा IB_SERDES_TRIM_DONE (1ULL << 11)
#घोषणा TRIM_TMO (15)

अटल पूर्णांक qib_sd_trimकरोne_poll(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक trim_पंचांगo, ret;
	uपूर्णांक64_t val;

	/*
	 * Default to failure, so IBC will not start
	 * without IB_SERDES_TRIM_DONE.
	 */
	ret = 0;
	क्रम (trim_पंचांगo = 0; trim_पंचांगo < TRIM_TMO; ++trim_पंचांगo) अणु
		val = qib_पढ़ो_kreg64(dd, kr_ibcstatus);
		अगर (val & IB_SERDES_TRIM_DONE) अणु
			ret = 1;
			अवरोध;
		पूर्ण
		msleep(20);
	पूर्ण
	अगर (trim_पंचांगo >= TRIM_TMO) अणु
		qib_dev_err(dd, "No TRIMDONE in %d tries\n", trim_पंचांगo);
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

#घोषणा TX_FAST_ELT (9)

/*
 * Set the "negotiation" values क्रम SERDES. These are used by the IB1.2
 * link negotiation. Macros below are attempt to keep the values a
 * little more human-editable.
 * First, values related to Drive De-emphasis Settings.
 */

#घोषणा NUM_DDS_REGS 6
#घोषणा DDS_REG_MAP 0x76A910 /* LSB-first list of regs (in elt 9) to mod */

#घोषणा DDS_VAL(amp_d, मुख्य_d, ipst_d, ipre_d, amp_s, मुख्य_s, ipst_s, ipre_s) \
	अणु अणु ((amp_d & 0x1F) << 1) | 1, ((amp_s & 0x1F) << 1) | 1, \
	  (मुख्य_d << 3) | 4 | (ipre_d >> 2), \
	  (मुख्य_s << 3) | 4 | (ipre_s >> 2), \
	  ((ipst_d & 0xF) << 1) | ((ipre_d & 3) << 6) | 0x21, \
	  ((ipst_s & 0xF) << 1) | ((ipre_s & 3) << 6) | 0x21 पूर्ण पूर्ण

अटल काष्ठा dds_init अणु
	uपूर्णांक8_t reg_vals[NUM_DDS_REGS];
पूर्ण dds_init_vals[] = अणु
	/*       DDR(FDR)       SDR(HDR)   */
	/* Venकरोr recommends below क्रम 3m cable */
#घोषणा DDS_3M 0
	DDS_VAL(31, 19, 12, 0, 29, 22,  9, 0),
	DDS_VAL(31, 12, 15, 4, 31, 15, 15, 1),
	DDS_VAL(31, 13, 15, 3, 31, 16, 15, 0),
	DDS_VAL(31, 14, 15, 2, 31, 17, 14, 0),
	DDS_VAL(31, 15, 15, 1, 31, 18, 13, 0),
	DDS_VAL(31, 16, 15, 0, 31, 19, 12, 0),
	DDS_VAL(31, 17, 14, 0, 31, 20, 11, 0),
	DDS_VAL(31, 18, 13, 0, 30, 21, 10, 0),
	DDS_VAL(31, 20, 11, 0, 28, 23,  8, 0),
	DDS_VAL(31, 21, 10, 0, 27, 24,  7, 0),
	DDS_VAL(31, 22,  9, 0, 26, 25,  6, 0),
	DDS_VAL(30, 23,  8, 0, 25, 26,  5, 0),
	DDS_VAL(29, 24,  7, 0, 23, 27,  4, 0),
	/* Venकरोr recommends below क्रम 1m cable */
#घोषणा DDS_1M 13
	DDS_VAL(28, 25,  6, 0, 21, 28,  3, 0),
	DDS_VAL(27, 26,  5, 0, 19, 29,  2, 0),
	DDS_VAL(25, 27,  4, 0, 17, 30,  1, 0)
पूर्ण;

/*
 * Now the RXEQ section of the table.
 */
/* Hardware packs an element number and रेजिस्टर address thus: */
#घोषणा RXEQ_INIT_RDESC(elt, addr) (((elt) & 0xF) | ((addr) << 4))
#घोषणा RXEQ_VAL(elt, adr, val0, val1, val2, val3) \
	अणुRXEQ_INIT_RDESC((elt), (adr)), अणु(val0), (val1), (val2), (val3)पूर्ण पूर्ण

#घोषणा RXEQ_VAL_ALL(elt, adr, val)  \
	अणुRXEQ_INIT_RDESC((elt), (adr)), अणु(val), (val), (val), (val)पूर्ण पूर्ण

#घोषणा RXEQ_SDR_DFELTH 0
#घोषणा RXEQ_SDR_TLTH 0
#घोषणा RXEQ_SDR_G1CNT_Z1CNT 0x11
#घोषणा RXEQ_SDR_ZCNT 23

अटल काष्ठा rxeq_init अणु
	u16 rdesc;      /* in क्रमm used in SerDesDDSRXEQ */
	u8  rdata[4];
पूर्ण rxeq_init_vals[] = अणु
	/* Set Rcv Eq. to Preset node */
	RXEQ_VAL_ALL(7, 0x27, 0x10),
	/* Set DFELTHFDR/HDR thresholds */
	RXEQ_VAL(7, 8,    0, 0, 0, 0), /* FDR, was 0, 1, 2, 3 */
	RXEQ_VAL(7, 0x21, 0, 0, 0, 0), /* HDR */
	/* Set TLTHFDR/HDR theshold */
	RXEQ_VAL(7, 9,    2, 2, 2, 2), /* FDR, was 0, 2, 4, 6 */
	RXEQ_VAL(7, 0x23, 2, 2, 2, 2), /* HDR, was  0, 1, 2, 3 */
	/* Set Preamp setting 2 (ZFR/ZCNT) */
	RXEQ_VAL(7, 0x1B, 12, 12, 12, 12), /* FDR, was 12, 16, 20, 24 */
	RXEQ_VAL(7, 0x1C, 12, 12, 12, 12), /* HDR, was 12, 16, 20, 24 */
	/* Set Preamp DC gain and Setting 1 (GFR/GHR) */
	RXEQ_VAL(7, 0x1E, 16, 16, 16, 16), /* FDR, was 16, 17, 18, 20 */
	RXEQ_VAL(7, 0x1F, 16, 16, 16, 16), /* HDR, was 16, 17, 18, 20 */
	/* Toggle RELOCK (in VCDL_CTRL0) to lock to data */
	RXEQ_VAL_ALL(6, 6, 0x20), /* Set D5 High */
	RXEQ_VAL_ALL(6, 6, 0), /* Set D5 Low */
पूर्ण;

/* There are 17 values from venकरोr, but IBC only accesses the first 16 */
#घोषणा DDS_ROWS (16)
#घोषणा RXEQ_ROWS ARRAY_SIZE(rxeq_init_vals)

अटल पूर्णांक qib_sd_setvals(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक idx, midx;
	पूर्णांक min_idx;     /* Minimum index क्रम this portion of table */
	uपूर्णांक32_t dds_reg_map;
	u64 __iomem *taddr, *iaddr;
	uपूर्णांक64_t data;
	uपूर्णांक64_t sdctl;

	taddr = dd->kregbase + kr_serdes_maptable;
	iaddr = dd->kregbase + kr_serdes_ddsrxeq0;

	/*
	 * Init the DDS section of the table.
	 * Each "row" of the table provokes NUM_DDS_REG ग_लिखोs, to the
	 * रेजिस्टरs indicated in DDS_REG_MAP.
	 */
	sdctl = qib_पढ़ो_kreg64(dd, kr_ibserdesctrl);
	sdctl = (sdctl & ~(0x1f << 8)) | (NUM_DDS_REGS << 8);
	sdctl = (sdctl & ~(0x1f << 13)) | (RXEQ_ROWS << 13);
	qib_ग_लिखो_kreg(dd, kr_ibserdesctrl, sdctl);

	/*
	 * Iterate करोwn table within loop क्रम each रेजिस्टर to store.
	 */
	dds_reg_map = DDS_REG_MAP;
	क्रम (idx = 0; idx < NUM_DDS_REGS; ++idx) अणु
		data = ((dds_reg_map & 0xF) << 4) | TX_FAST_ELT;
		ग_लिखोq(data, iaddr + idx);
		qib_पढ़ो_kreg32(dd, kr_scratch);
		dds_reg_map >>= 4;
		क्रम (midx = 0; midx < DDS_ROWS; ++midx) अणु
			u64 __iomem *daddr = taddr + ((midx << 4) + idx);

			data = dds_init_vals[midx].reg_vals[idx];
			ग_लिखोq(data, daddr);
			qib_पढ़ो_kreg32(dd, kr_scratch);
		पूर्ण /* End inner क्रम (vals क्रम this reg, each row) */
	पूर्ण /* end outer क्रम (regs to be stored) */

	/*
	 * Init the RXEQ section of the table.
	 * This runs in a dअगरferent order, as the pattern of
	 * रेजिस्टर references is more complex, but there are only
	 * four "data" values per रेजिस्टर.
	 */
	min_idx = idx; /* RXEQ indices pick up where DDS left off */
	taddr += 0x100; /* RXEQ data is in second half of table */
	/* Iterate through RXEQ रेजिस्टर addresses */
	क्रम (idx = 0; idx < RXEQ_ROWS; ++idx) अणु
		पूर्णांक didx; /* "destination" */
		पूर्णांक vidx;

		/* didx is offset by min_idx to address RXEQ range of regs */
		didx = idx + min_idx;
		/* Store the next RXEQ रेजिस्टर address */
		ग_लिखोq(rxeq_init_vals[idx].rdesc, iaddr + didx);
		qib_पढ़ो_kreg32(dd, kr_scratch);
		/* Iterate through RXEQ values */
		क्रम (vidx = 0; vidx < 4; vidx++) अणु
			data = rxeq_init_vals[idx].rdata[vidx];
			ग_लिखोq(data, taddr + (vidx << 6) + idx);
			qib_पढ़ो_kreg32(dd, kr_scratch);
		पूर्ण
	पूर्ण /* end outer क्रम (Reg-ग_लिखोs क्रम RXEQ) */
	वापस 0;
पूर्ण

#घोषणा CMUCTRL5 EPB_LOC(7, 0, 0x15)
#घोषणा RXHSCTRL0(chan) EPB_LOC(chan, 6, 0)
#घोषणा VCDL_DAC2(chan) EPB_LOC(chan, 6, 5)
#घोषणा VCDL_CTRL0(chan) EPB_LOC(chan, 6, 6)
#घोषणा VCDL_CTRL2(chan) EPB_LOC(chan, 6, 8)
#घोषणा START_EQ2(chan) EPB_LOC(chan, 7, 0x28)

/*
 * Repeat a "store" across all channels of the IB SerDes.
 * Although nominally it inherits the "read value" of the last
 * channel it modअगरied, the only really useful वापस is <0 क्रम
 * failure, >= 0 क्रम success. The parameter 'loc' is assumed to
 * be the location in some channel of the रेजिस्टर to be modअगरied
 * The caller can specअगरy use of the "gang write" option of EPB,
 * in which हाल we use the specअगरied channel data क्रम any fields
 * not explicitely written.
 */
अटल पूर्णांक ibsd_mod_allchnls(काष्ठा qib_devdata *dd, पूर्णांक loc, पूर्णांक val,
			     पूर्णांक mask)
अणु
	पूर्णांक ret = -1;
	पूर्णांक chnl;

	अगर (loc & EPB_GLOBAL_WR) अणु
		/*
		 * Our caller has assured us that we can set all four
		 * channels at once. Trust that. If mask is not 0xFF,
		 * we will पढ़ो the _specअगरied_ channel क्रम our starting
		 * value.
		 */
		loc |= (1U << EPB_IB_QUAD0_CS_SHF);
		chnl = (loc >> (4 + EPB_ADDR_SHF)) & 7;
		अगर (mask != 0xFF) अणु
			ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES,
						 loc & ~EPB_GLOBAL_WR, 0, 0);
			अगर (ret < 0) अणु
				पूर्णांक sloc = loc >> EPB_ADDR_SHF;

				qib_dev_err(dd,
					"pre-read failed: elt %d, addr 0x%X, chnl %d\n",
					(sloc & 0xF),
					(sloc >> 9) & 0x3f, chnl);
				वापस ret;
			पूर्ण
			val = (ret & ~mask) | (val & mask);
		पूर्ण
		loc &=  ~(7 << (4+EPB_ADDR_SHF));
		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, val, 0xFF);
		अगर (ret < 0) अणु
			पूर्णांक sloc = loc >> EPB_ADDR_SHF;

			qib_dev_err(dd,
				"Global WR failed: elt %d, addr 0x%X, val %02X\n",
				(sloc & 0xF), (sloc >> 9) & 0x3f, val);
		पूर्ण
		वापस ret;
	पूर्ण
	/* Clear "channel" and set CS so we can simply iterate */
	loc &=  ~(7 << (4+EPB_ADDR_SHF));
	loc |= (1U << EPB_IB_QUAD0_CS_SHF);
	क्रम (chnl = 0; chnl < 4; ++chnl) अणु
		पूर्णांक cloc = loc | (chnl << (4+EPB_ADDR_SHF));

		ret = qib_sd7220_reg_mod(dd, IB_7220_SERDES, cloc, val, mask);
		अगर (ret < 0) अणु
			पूर्णांक sloc = loc >> EPB_ADDR_SHF;

			qib_dev_err(dd,
				"Write failed: elt %d, addr 0x%X, chnl %d, val 0x%02X, mask 0x%02X\n",
				(sloc & 0xF), (sloc >> 9) & 0x3f, chnl,
				val & 0xFF, mask & 0xFF);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Set the Tx values normally modअगरied by IBC in IB1.2 mode to शेष
 * values, as gotten from first row of init table.
 */
अटल पूर्णांक set_dds_vals(काष्ठा qib_devdata *dd, काष्ठा dds_init *ddi)
अणु
	पूर्णांक ret;
	पूर्णांक idx, reg, data;
	uपूर्णांक32_t regmap;

	regmap = DDS_REG_MAP;
	क्रम (idx = 0; idx < NUM_DDS_REGS; ++idx) अणु
		reg = (regmap & 0xF);
		regmap >>= 4;
		data = ddi->reg_vals[idx];
		/* Venकरोr says RMW not needed क्रम these regs, use 0xFF mask */
		ret = ibsd_mod_allchnls(dd, EPB_LOC(0, 9, reg), data, 0xFF);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Set the Rx values normally modअगरied by IBC in IB1.2 mode to शेष
 * values, as gotten from selected column of init table.
 */
अटल पूर्णांक set_rxeq_vals(काष्ठा qib_devdata *dd, पूर्णांक vsel)
अणु
	पूर्णांक ret;
	पूर्णांक ridx;
	पूर्णांक cnt = ARRAY_SIZE(rxeq_init_vals);

	क्रम (ridx = 0; ridx < cnt; ++ridx) अणु
		पूर्णांक elt, reg, val, loc;

		elt = rxeq_init_vals[ridx].rdesc & 0xF;
		reg = rxeq_init_vals[ridx].rdesc >> 4;
		loc = EPB_LOC(0, elt, reg);
		val = rxeq_init_vals[ridx].rdata[vsel];
		/* mask of 0xFF, because hardware करोes full-byte store. */
		ret = ibsd_mod_allchnls(dd, loc, val, 0xFF);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/*
 * Set the शेष values (row 0) क्रम DDR Driver Demphasis.
 * we करो this initially and whenever we turn off IB-1.2
 *
 * The "default" values क्रम Rx equalization are also stored to
 * SerDes रेजिस्टरs. Formerly (and still शेष), we used set 2.
 * For experimenting with cables and link-partners, we allow changing
 * that via a module parameter.
 */
अटल अचिन्हित qib_rxeq_set = 2;
module_param_named(rxeq_शेष_set, qib_rxeq_set, uपूर्णांक,
		   S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(rxeq_शेष_set,
		 "Which set [0..3] of Rx Equalization values is default");

अटल पूर्णांक qib_पूर्णांकernal_presets(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;

	ret = set_dds_vals(dd, dds_init_vals + DDS_3M);

	अगर (ret < 0)
		qib_dev_err(dd, "Failed to set default DDS values\n");
	ret = set_rxeq_vals(dd, qib_rxeq_set & 3);
	अगर (ret < 0)
		qib_dev_err(dd, "Failed to set default RXEQ values\n");
	वापस ret;
पूर्ण

पूर्णांक qib_sd7220_presets(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret = 0;

	अगर (!dd->cspec->presets_needed)
		वापस ret;
	dd->cspec->presets_needed = 0;
	/* Assert uC reset, so we करोn't clash with it. */
	qib_ibsd_reset(dd, 1);
	udelay(2);
	qib_sd_trimकरोne_monitor(dd, "link-down");

	ret = qib_पूर्णांकernal_presets(dd);
	वापस ret;
पूर्ण

अटल पूर्णांक qib_sd_trimself(काष्ठा qib_devdata *dd, पूर्णांक val)
अणु
	पूर्णांक loc = CMUCTRL5 | (1U << EPB_IB_QUAD0_CS_SHF);

	वापस qib_sd7220_reg_mod(dd, IB_7220_SERDES, loc, val, 0xFF);
पूर्ण

अटल पूर्णांक qib_sd_early(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret;

	ret = ibsd_mod_allchnls(dd, RXHSCTRL0(0) | EPB_GLOBAL_WR, 0xD4, 0xFF);
	अगर (ret < 0)
		जाओ bail;
	ret = ibsd_mod_allchnls(dd, START_EQ1(0) | EPB_GLOBAL_WR, 0x10, 0xFF);
	अगर (ret < 0)
		जाओ bail;
	ret = ibsd_mod_allchnls(dd, START_EQ2(0) | EPB_GLOBAL_WR, 0x30, 0xFF);
bail:
	वापस ret;
पूर्ण

#घोषणा BACTRL(chnl) EPB_LOC(chnl, 6, 0x0E)
#घोषणा LDOUTCTRL1(chnl) EPB_LOC(chnl, 7, 6)
#घोषणा RXHSSTATUS(chnl) EPB_LOC(chnl, 6, 0xF)

अटल पूर्णांक qib_sd_dactrim(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक ret;

	ret = ibsd_mod_allchnls(dd, VCDL_DAC2(0) | EPB_GLOBAL_WR, 0x2D, 0xFF);
	अगर (ret < 0)
		जाओ bail;

	/* more fine-tuning of what will be शेष */
	ret = ibsd_mod_allchnls(dd, VCDL_CTRL2(0), 3, 0xF);
	अगर (ret < 0)
		जाओ bail;

	ret = ibsd_mod_allchnls(dd, BACTRL(0) | EPB_GLOBAL_WR, 0x40, 0xFF);
	अगर (ret < 0)
		जाओ bail;

	ret = ibsd_mod_allchnls(dd, LDOUTCTRL1(0) | EPB_GLOBAL_WR, 0x04, 0xFF);
	अगर (ret < 0)
		जाओ bail;

	ret = ibsd_mod_allchnls(dd, RXHSSTATUS(0) | EPB_GLOBAL_WR, 0x04, 0xFF);
	अगर (ret < 0)
		जाओ bail;

	/*
	 * Delay क्रम max possible number of steps, with slop.
	 * Each step is about 4usec.
	 */
	udelay(415);

	ret = ibsd_mod_allchnls(dd, LDOUTCTRL1(0) | EPB_GLOBAL_WR, 0x00, 0xFF);

bail:
	वापस ret;
पूर्ण

#घोषणा RELOCK_FIRST_MS 3
#घोषणा RXLSPPM(chan) EPB_LOC(chan, 0, 2)
व्योम toggle_7220_rclkrls(काष्ठा qib_devdata *dd)
अणु
	पूर्णांक loc = RXLSPPM(0) | EPB_GLOBAL_WR;
	पूर्णांक ret;

	ret = ibsd_mod_allchnls(dd, loc, 0, 0x80);
	अगर (ret < 0)
		qib_dev_err(dd, "RCLKRLS failed to clear D7\n");
	अन्यथा अणु
		udelay(1);
		ibsd_mod_allchnls(dd, loc, 0x80, 0x80);
	पूर्ण
	/* And again क्रम good measure */
	udelay(1);
	ret = ibsd_mod_allchnls(dd, loc, 0, 0x80);
	अगर (ret < 0)
		qib_dev_err(dd, "RCLKRLS failed to clear D7\n");
	अन्यथा अणु
		udelay(1);
		ibsd_mod_allchnls(dd, loc, 0x80, 0x80);
	पूर्ण
	/* Now reset xgxs and IBC to complete the recovery */
	dd->f_xgxs_reset(dd->pport);
पूर्ण

/*
 * Shut करोwn the समयr that polls क्रम relock occasions, अगर needed
 * this is "hooked" from qib_7220_quiet_serdes(), which is called
 * just beक्रमe qib_shutकरोwn_device() in qib_driver.c shuts करोwn all
 * the other समयrs
 */
व्योम shutकरोwn_7220_relock_poll(काष्ठा qib_devdata *dd)
अणु
	अगर (dd->cspec->relock_समयr_active)
		del_समयr_sync(&dd->cspec->relock_समयr);
पूर्ण

अटल अचिन्हित qib_relock_by_समयr = 1;
module_param_named(relock_by_समयr, qib_relock_by_समयr, uपूर्णांक,
		   S_IWUSR | S_IRUGO);
MODULE_PARM_DESC(relock_by_समयr, "Allow relock attempt if link not up");

अटल व्योम qib_run_relock(काष्ठा समयr_list *t)
अणु
	काष्ठा qib_chip_specअगरic *cs = from_समयr(cs, t, relock_समयr);
	काष्ठा qib_devdata *dd = cs->dd;
	काष्ठा qib_pportdata *ppd = dd->pport;
	पूर्णांक समयoff;

	/*
	 * Check link-training state क्रम "stuck" state, when करोwn.
	 * अगर found, try relock and schedule another try at
	 * exponentially growing delay, maxed at one second.
	 * अगर not stuck, our work is करोne.
	 */
	अगर ((dd->flags & QIB_INITTED) && !(ppd->lflags &
	    (QIBL_IB_AUTONEG_INPROG | QIBL_LINKINIT | QIBL_LINKARMED |
	     QIBL_LINKACTIVE))) अणु
		अगर (qib_relock_by_समयr) अणु
			अगर (!(ppd->lflags & QIBL_IB_LINK_DISABLED))
				toggle_7220_rclkrls(dd);
		पूर्ण
		/* re-set समयr क्रम next check */
		समयoff = cs->relock_पूर्णांकerval << 1;
		अगर (समयoff > HZ)
			समयoff = HZ;
		cs->relock_पूर्णांकerval = समयoff;
	पूर्ण अन्यथा
		समयoff = HZ;
	mod_समयr(&cs->relock_समयr, jअगरfies + समयoff);
पूर्ण

व्योम set_7220_relock_poll(काष्ठा qib_devdata *dd, पूर्णांक ibup)
अणु
	काष्ठा qib_chip_specअगरic *cs = dd->cspec;

	अगर (ibup) अणु
		/* We are now up, relax समयr to 1 second पूर्णांकerval */
		अगर (cs->relock_समयr_active) अणु
			cs->relock_पूर्णांकerval = HZ;
			mod_समयr(&cs->relock_समयr, jअगरfies + HZ);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Transition to करोwn, (re-)set समयr to लघु पूर्णांकerval. */
		अचिन्हित पूर्णांक समयout;

		समयout = msecs_to_jअगरfies(RELOCK_FIRST_MS);
		अगर (समयout == 0)
			समयout = 1;
		/* If समयr has not yet been started, करो so. */
		अगर (!cs->relock_समयr_active) अणु
			cs->relock_समयr_active = 1;
			समयr_setup(&cs->relock_समयr, qib_run_relock, 0);
			cs->relock_पूर्णांकerval = समयout;
			cs->relock_समयr.expires = jअगरfies + समयout;
			add_समयr(&cs->relock_समयr);
		पूर्ण अन्यथा अणु
			cs->relock_पूर्णांकerval = समयout;
			mod_समयr(&cs->relock_समयr, jअगरfies + समयout);
		पूर्ण
	पूर्ण
पूर्ण
