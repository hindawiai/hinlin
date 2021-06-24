<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008, 2009 QLogic Corporation. All rights reserved.
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

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "qib.h"
#समावेश "qib_qsfp.h"

/*
 * QSFP support क्रम ib_qib driver, using "Two Wire Serial Interface" driver
 * in qib_twsi.c
 */
#घोषणा QSFP_MAX_RETRY 4

अटल पूर्णांक qsfp_पढ़ो(काष्ठा qib_pportdata *ppd, पूर्णांक addr, व्योम *bp, पूर्णांक len)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 out, mask;
	पूर्णांक ret, cnt, pass = 0;
	पूर्णांक stuck = 0;
	u8 *buff = bp;

	ret = mutex_lock_पूर्णांकerruptible(&dd->eep_lock);
	अगर (ret)
		जाओ no_unlock;

	अगर (dd->twsi_eeprom_dev == QIB_TWSI_NO_DEV) अणु
		ret = -ENXIO;
		जाओ bail;
	पूर्ण

	/*
	 * We presume, अगर we are called at all, that this board has
	 * QSFP. This is on the same i2c chain as the legacy parts,
	 * but only responds अगर the module is selected via GPIO pins.
	 * Further, there are very दीर्घ setup and hold requirements
	 * on MODSEL.
	 */
	mask = QSFP_GPIO_MOD_SEL_N | QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	out = QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	अगर (ppd->hw_pidx) अणु
		mask <<= QSFP_GPIO_PORT2_SHIFT;
		out <<= QSFP_GPIO_PORT2_SHIFT;
	पूर्ण

	dd->f_gpio_mod(dd, out, mask, mask);

	/*
	 * Module could take up to 2 Msec to respond to MOD_SEL, and there
	 * is no way to tell अगर it is पढ़ोy, so we must रुको.
	 */
	msleep(20);

	/* Make sure TWSI bus is in sane state. */
	ret = qib_twsi_reset(dd);
	अगर (ret) अणु
		qib_dev_porterr(dd, ppd->port,
				"QSFP interface Reset for read failed\n");
		ret = -EIO;
		stuck = 1;
		जाओ deselect;
	पूर्ण

	/* All QSFP modules are at A0 */

	cnt = 0;
	जबतक (cnt < len) अणु
		अचिन्हित in_page;
		पूर्णांक wlen = len - cnt;

		in_page = addr % QSFP_PAGESIZE;
		अगर ((in_page + wlen) > QSFP_PAGESIZE)
			wlen = QSFP_PAGESIZE - in_page;
		ret = qib_twsi_blk_rd(dd, QSFP_DEV, addr, buff + cnt, wlen);
		/* Some QSFP's fail first try. Retry as experiment */
		अगर (ret && cnt == 0 && ++pass < QSFP_MAX_RETRY)
			जारी;
		अगर (ret) अणु
			/* qib_twsi_blk_rd() 1 क्रम error, अन्यथा 0 */
			ret = -EIO;
			जाओ deselect;
		पूर्ण
		addr += wlen;
		cnt += wlen;
	पूर्ण
	ret = cnt;

deselect:
	/*
	 * Module could take up to 10 uSec after transfer beक्रमe
	 * पढ़ोy to respond to MOD_SEL negation, and there is no way
	 * to tell अगर it is पढ़ोy, so we must रुको.
	 */
	udelay(10);
	/* set QSFP MODSEL, RST. LP all high */
	dd->f_gpio_mod(dd, mask, mask, mask);

	/*
	 * Module could take up to 2 Msec to respond to MOD_SEL
	 * going away, and there is no way to tell अगर it is पढ़ोy.
	 * so we must रुको.
	 */
	अगर (stuck)
		qib_dev_err(dd, "QSFP interface bus stuck non-idle\n");

	अगर (pass >= QSFP_MAX_RETRY && ret)
		qib_dev_porterr(dd, ppd->port, "QSFP failed even retrying\n");
	अन्यथा अगर (pass)
		qib_dev_porterr(dd, ppd->port, "QSFP retries: %d\n", pass);

	msleep(20);

bail:
	mutex_unlock(&dd->eep_lock);

no_unlock:
	वापस ret;
पूर्ण

/*
 * qsfp_ग_लिखो
 * We करो not ordinarily ग_लिखो the QSFP, but this is needed to select
 * the page on non-flat QSFPs, and possibly later unusual हालs
 */
अटल पूर्णांक qib_qsfp_ग_लिखो(काष्ठा qib_pportdata *ppd, पूर्णांक addr, व्योम *bp,
			  पूर्णांक len)
अणु
	काष्ठा qib_devdata *dd = ppd->dd;
	u32 out, mask;
	पूर्णांक ret, cnt;
	u8 *buff = bp;

	ret = mutex_lock_पूर्णांकerruptible(&dd->eep_lock);
	अगर (ret)
		जाओ no_unlock;

	अगर (dd->twsi_eeprom_dev == QIB_TWSI_NO_DEV) अणु
		ret = -ENXIO;
		जाओ bail;
	पूर्ण

	/*
	 * We presume, अगर we are called at all, that this board has
	 * QSFP. This is on the same i2c chain as the legacy parts,
	 * but only responds अगर the module is selected via GPIO pins.
	 * Further, there are very दीर्घ setup and hold requirements
	 * on MODSEL.
	 */
	mask = QSFP_GPIO_MOD_SEL_N | QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	out = QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	अगर (ppd->hw_pidx) अणु
		mask <<= QSFP_GPIO_PORT2_SHIFT;
		out <<= QSFP_GPIO_PORT2_SHIFT;
	पूर्ण
	dd->f_gpio_mod(dd, out, mask, mask);

	/*
	 * Module could take up to 2 Msec to respond to MOD_SEL,
	 * and there is no way to tell अगर it is पढ़ोy, so we must रुको.
	 */
	msleep(20);

	/* Make sure TWSI bus is in sane state. */
	ret = qib_twsi_reset(dd);
	अगर (ret) अणु
		qib_dev_porterr(dd, ppd->port,
				"QSFP interface Reset for write failed\n");
		ret = -EIO;
		जाओ deselect;
	पूर्ण

	/* All QSFP modules are at A0 */

	cnt = 0;
	जबतक (cnt < len) अणु
		अचिन्हित in_page;
		पूर्णांक wlen = len - cnt;

		in_page = addr % QSFP_PAGESIZE;
		अगर ((in_page + wlen) > QSFP_PAGESIZE)
			wlen = QSFP_PAGESIZE - in_page;
		ret = qib_twsi_blk_wr(dd, QSFP_DEV, addr, buff + cnt, wlen);
		अगर (ret) अणु
			/* qib_twsi_blk_wr() 1 क्रम error, अन्यथा 0 */
			ret = -EIO;
			जाओ deselect;
		पूर्ण
		addr += wlen;
		cnt += wlen;
	पूर्ण
	ret = cnt;

deselect:
	/*
	 * Module could take up to 10 uSec after transfer beक्रमe
	 * पढ़ोy to respond to MOD_SEL negation, and there is no way
	 * to tell अगर it is पढ़ोy, so we must रुको.
	 */
	udelay(10);
	/* set QSFP MODSEL, RST, LP high */
	dd->f_gpio_mod(dd, mask, mask, mask);
	/*
	 * Module could take up to 2 Msec to respond to MOD_SEL
	 * going away, and there is no way to tell अगर it is पढ़ोy.
	 * so we must रुको.
	 */
	msleep(20);

bail:
	mutex_unlock(&dd->eep_lock);

no_unlock:
	वापस ret;
पूर्ण

/*
 * For validation, we want to check the checksums, even of the
 * fields we करो not otherwise use. This function पढ़ोs the bytes from
 * <first> to <next-1> and वापसs the 8lsbs of the sum, or <0 क्रम errors
 */
अटल पूर्णांक qsfp_cks(काष्ठा qib_pportdata *ppd, पूर्णांक first, पूर्णांक next)
अणु
	पूर्णांक ret;
	u16 cks;
	u8 bval;

	cks = 0;
	जबतक (first < next) अणु
		ret = qsfp_पढ़ो(ppd, first, &bval, 1);
		अगर (ret < 0)
			जाओ bail;
		cks += bval;
		++first;
	पूर्ण
	ret = cks & 0xFF;
bail:
	वापस ret;

पूर्ण

पूर्णांक qib_refresh_qsfp_cache(काष्ठा qib_pportdata *ppd, काष्ठा qib_qsfp_cache *cp)
अणु
	पूर्णांक ret;
	पूर्णांक idx;
	u16 cks;
	u8 peek[4];

	/* ensure sane contents on invalid पढ़ोs, क्रम cable swaps */
	स_रखो(cp, 0, माप(*cp));

	अगर (!qib_qsfp_mod_present(ppd)) अणु
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	ret = qsfp_पढ़ो(ppd, 0, peek, 3);
	अगर (ret < 0)
		जाओ bail;
	अगर ((peek[0] & 0xFE) != 0x0C)
		qib_dev_porterr(ppd->dd, ppd->port,
				"QSFP byte0 is 0x%02X, S/B 0x0C/D\n", peek[0]);

	अगर ((peek[2] & 4) == 0) अणु
		/*
		 * If cable is paged, rather than "flat memory", we need to
		 * set the page to zero, Even अगर it alपढ़ोy appears to be zero.
		 */
		u8 poke = 0;

		ret = qib_qsfp_ग_लिखो(ppd, 127, &poke, 1);
		udelay(50);
		अगर (ret != 1) अणु
			qib_dev_porterr(ppd->dd, ppd->port,
					"Failed QSFP Page set\n");
			जाओ bail;
		पूर्ण
	पूर्ण

	ret = qsfp_पढ़ो(ppd, QSFP_MOD_ID_OFFS, &cp->id, 1);
	अगर (ret < 0)
		जाओ bail;
	अगर ((cp->id & 0xFE) != 0x0C)
		qib_dev_porterr(ppd->dd, ppd->port,
				"QSFP ID byte is 0x%02X, S/B 0x0C/D\n", cp->id);
	cks = cp->id;

	ret = qsfp_पढ़ो(ppd, QSFP_MOD_PWR_OFFS, &cp->pwr, 1);
	अगर (ret < 0)
		जाओ bail;
	cks += cp->pwr;

	ret = qsfp_cks(ppd, QSFP_MOD_PWR_OFFS + 1, QSFP_MOD_LEN_OFFS);
	अगर (ret < 0)
		जाओ bail;
	cks += ret;

	ret = qsfp_पढ़ो(ppd, QSFP_MOD_LEN_OFFS, &cp->len, 1);
	अगर (ret < 0)
		जाओ bail;
	cks += cp->len;

	ret = qsfp_पढ़ो(ppd, QSFP_MOD_TECH_OFFS, &cp->tech, 1);
	अगर (ret < 0)
		जाओ bail;
	cks += cp->tech;

	ret = qsfp_पढ़ो(ppd, QSFP_VEND_OFFS, &cp->venकरोr, QSFP_VEND_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_VEND_LEN; ++idx)
		cks += cp->venकरोr[idx];

	ret = qsfp_पढ़ो(ppd, QSFP_IBXCV_OFFS, &cp->xt_xcv, 1);
	अगर (ret < 0)
		जाओ bail;
	cks += cp->xt_xcv;

	ret = qsfp_पढ़ो(ppd, QSFP_VOUI_OFFS, &cp->oui, QSFP_VOUI_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_VOUI_LEN; ++idx)
		cks += cp->oui[idx];

	ret = qsfp_पढ़ो(ppd, QSFP_PN_OFFS, &cp->partnum, QSFP_PN_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_PN_LEN; ++idx)
		cks += cp->partnum[idx];

	ret = qsfp_पढ़ो(ppd, QSFP_REV_OFFS, &cp->rev, QSFP_REV_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_REV_LEN; ++idx)
		cks += cp->rev[idx];

	ret = qsfp_पढ़ो(ppd, QSFP_ATTEN_OFFS, &cp->atten, QSFP_ATTEN_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_ATTEN_LEN; ++idx)
		cks += cp->atten[idx];

	ret = qsfp_cks(ppd, QSFP_ATTEN_OFFS + QSFP_ATTEN_LEN, QSFP_CC_OFFS);
	अगर (ret < 0)
		जाओ bail;
	cks += ret;

	cks &= 0xFF;
	ret = qsfp_पढ़ो(ppd, QSFP_CC_OFFS, &cp->cks1, 1);
	अगर (ret < 0)
		जाओ bail;
	अगर (cks != cp->cks1)
		qib_dev_porterr(ppd->dd, ppd->port,
				"QSFP cks1 is %02X, computed %02X\n", cp->cks1,
				cks);

	/* Second checksum covers 192 to (serial, date, lot) */
	ret = qsfp_cks(ppd, QSFP_CC_OFFS + 1, QSFP_SN_OFFS);
	अगर (ret < 0)
		जाओ bail;
	cks = ret;

	ret = qsfp_पढ़ो(ppd, QSFP_SN_OFFS, &cp->serial, QSFP_SN_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_SN_LEN; ++idx)
		cks += cp->serial[idx];

	ret = qsfp_पढ़ो(ppd, QSFP_DATE_OFFS, &cp->date, QSFP_DATE_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_DATE_LEN; ++idx)
		cks += cp->date[idx];

	ret = qsfp_पढ़ो(ppd, QSFP_LOT_OFFS, &cp->lot, QSFP_LOT_LEN);
	अगर (ret < 0)
		जाओ bail;
	क्रम (idx = 0; idx < QSFP_LOT_LEN; ++idx)
		cks += cp->lot[idx];

	ret = qsfp_cks(ppd, QSFP_LOT_OFFS + QSFP_LOT_LEN, QSFP_CC_EXT_OFFS);
	अगर (ret < 0)
		जाओ bail;
	cks += ret;

	ret = qsfp_पढ़ो(ppd, QSFP_CC_EXT_OFFS, &cp->cks2, 1);
	अगर (ret < 0)
		जाओ bail;
	cks &= 0xFF;
	अगर (cks != cp->cks2)
		qib_dev_porterr(ppd->dd, ppd->port,
				"QSFP cks2 is %02X, computed %02X\n", cp->cks2,
				cks);
	वापस 0;

bail:
	cp->id = 0;
	वापस ret;
पूर्ण

स्थिर अक्षर * स्थिर qib_qsfp_devtech[16] = अणु
	"850nm VCSEL", "1310nm VCSEL", "1550nm VCSEL", "1310nm FP",
	"1310nm DFB", "1550nm DFB", "1310nm EML", "1550nm EML",
	"Cu Misc", "1490nm DFB", "Cu NoEq", "Cu Eq",
	"Undef", "Cu Active BothEq", "Cu FarEq", "Cu NearEq"
पूर्ण;

#घोषणा QSFP_DUMP_CHUNK 16 /* Holds दीर्घest string */
#घोषणा QSFP_DEFAULT_HDR_CNT 224

अटल स्थिर अक्षर *pwr_codes = "1.5W2.0W2.5W3.5W";

पूर्णांक qib_qsfp_mod_present(काष्ठा qib_pportdata *ppd)
अणु
	u32 mask;
	पूर्णांक ret;

	mask = QSFP_GPIO_MOD_PRS_N <<
		(ppd->hw_pidx * QSFP_GPIO_PORT2_SHIFT);
	ret = ppd->dd->f_gpio_mod(ppd->dd, 0, 0, 0);

	वापस !((ret & mask) >>
		 ((ppd->hw_pidx * QSFP_GPIO_PORT2_SHIFT) + 3));
पूर्ण

/*
 * Initialize काष्ठाures that control access to QSFP. Called once per port
 * on cards that support QSFP.
 */
व्योम qib_qsfp_init(काष्ठा qib_qsfp_data *qd,
		   व्योम (*fevent)(काष्ठा work_काष्ठा *))
अणु
	u32 mask, highs;

	काष्ठा qib_devdata *dd = qd->ppd->dd;

	/* Initialize work काष्ठा क्रम later QSFP events */
	INIT_WORK(&qd->work, fevent);

	/*
	 * Later, we may want more validation. For now, just set up pins and
	 * blip reset. If module is present, call qib_refresh_qsfp_cache(),
	 * to करो further init.
	 */
	mask = QSFP_GPIO_MOD_SEL_N | QSFP_GPIO_MOD_RST_N | QSFP_GPIO_LP_MODE;
	highs = mask - QSFP_GPIO_MOD_RST_N;
	अगर (qd->ppd->hw_pidx) अणु
		mask <<= QSFP_GPIO_PORT2_SHIFT;
		highs <<= QSFP_GPIO_PORT2_SHIFT;
	पूर्ण
	dd->f_gpio_mod(dd, highs, mask, mask);
	udelay(20); /* Generous RST dwell */

	dd->f_gpio_mod(dd, mask, mask, mask);
पूर्ण

पूर्णांक qib_qsfp_dump(काष्ठा qib_pportdata *ppd, अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा qib_qsfp_cache cd;
	u8 bin_buff[QSFP_DUMP_CHUNK];
	अक्षर lenstr[6];
	पूर्णांक sofar, ret;
	पूर्णांक bidx = 0;

	sofar = 0;
	ret = qib_refresh_qsfp_cache(ppd, &cd);
	अगर (ret < 0)
		जाओ bail;

	lenstr[0] = ' ';
	lenstr[1] = '\0';
	अगर (QSFP_IS_CU(cd.tech))
		प्र_लिखो(lenstr, "%dM ", cd.len);

	sofar += scnम_लिखो(buf + sofar, len - sofar, "PWR:%.3sW\n", pwr_codes +
			   (QSFP_PWR(cd.pwr) * 4));

	sofar += scnम_लिखो(buf + sofar, len - sofar, "TECH:%s%s\n", lenstr,
			   qib_qsfp_devtech[cd.tech >> 4]);

	sofar += scnम_लिखो(buf + sofar, len - sofar, "Vendor:%.*s\n",
			   QSFP_VEND_LEN, cd.venकरोr);

	sofar += scnम_लिखो(buf + sofar, len - sofar, "OUI:%06X\n",
			   QSFP_OUI(cd.oui));

	sofar += scnम_लिखो(buf + sofar, len - sofar, "Part#:%.*s\n",
			   QSFP_PN_LEN, cd.partnum);
	sofar += scnम_लिखो(buf + sofar, len - sofar, "Rev:%.*s\n",
			   QSFP_REV_LEN, cd.rev);
	अगर (QSFP_IS_CU(cd.tech))
		sofar += scnम_लिखो(buf + sofar, len - sofar, "Atten:%d, %d\n",
				   QSFP_ATTEN_SDR(cd.atten),
				   QSFP_ATTEN_DDR(cd.atten));
	sofar += scnम_लिखो(buf + sofar, len - sofar, "Serial:%.*s\n",
			   QSFP_SN_LEN, cd.serial);
	sofar += scnम_लिखो(buf + sofar, len - sofar, "Date:%.*s\n",
			   QSFP_DATE_LEN, cd.date);
	sofar += scnम_लिखो(buf + sofar, len - sofar, "Lot:%.*s\n",
			   QSFP_LOT_LEN, cd.lot);

	जबतक (bidx < QSFP_DEFAULT_HDR_CNT) अणु
		पूर्णांक iidx;

		ret = qsfp_पढ़ो(ppd, bidx, bin_buff, QSFP_DUMP_CHUNK);
		अगर (ret < 0)
			जाओ bail;
		क्रम (iidx = 0; iidx < ret; ++iidx) अणु
			sofar += scnम_लिखो(buf + sofar, len-sofar, " %02X",
				bin_buff[iidx]);
		पूर्ण
		sofar += scnम_लिखो(buf + sofar, len - sofar, "\n");
		bidx += QSFP_DUMP_CHUNK;
	पूर्ण
	ret = sofar;
bail:
	वापस ret;
पूर्ण
