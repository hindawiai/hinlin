<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश "main.h"
#समावेश "util.h"
#समावेश "reg.h"

bool check_hw_पढ़ोy(काष्ठा rtw_dev *rtwdev, u32 addr, u32 mask, u32 target)
अणु
	u32 cnt;

	क्रम (cnt = 0; cnt < 1000; cnt++) अणु
		अगर (rtw_पढ़ो32_mask(rtwdev, addr, mask) == target)
			वापस true;

		udelay(10);
	पूर्ण

	वापस false;
पूर्ण
EXPORT_SYMBOL(check_hw_पढ़ोy);

bool ltecoex_पढ़ो_reg(काष्ठा rtw_dev *rtwdev, u16 offset, u32 *val)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_ltecoex_addr *ltecoex = chip->ltecoex_addr;

	अगर (!check_hw_पढ़ोy(rtwdev, ltecoex->ctrl, LTECOEX_READY, 1))
		वापस false;

	rtw_ग_लिखो32(rtwdev, ltecoex->ctrl, 0x800F0000 | offset);
	*val = rtw_पढ़ो32(rtwdev, ltecoex->rdata);

	वापस true;
पूर्ण

bool ltecoex_reg_ग_लिखो(काष्ठा rtw_dev *rtwdev, u16 offset, u32 value)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	स्थिर काष्ठा rtw_ltecoex_addr *ltecoex = chip->ltecoex_addr;

	अगर (!check_hw_पढ़ोy(rtwdev, ltecoex->ctrl, LTECOEX_READY, 1))
		वापस false;

	rtw_ग_लिखो32(rtwdev, ltecoex->wdata, value);
	rtw_ग_लिखो32(rtwdev, ltecoex->ctrl, 0xC00F0000 | offset);

	वापस true;
पूर्ण

व्योम rtw_restore_reg(काष्ठा rtw_dev *rtwdev,
		     काष्ठा rtw_backup_info *bckp, u32 num)
अणु
	u8 len;
	u32 reg;
	u32 val;
	पूर्णांक i;

	क्रम (i = 0; i < num; i++, bckp++) अणु
		len = bckp->len;
		reg = bckp->reg;
		val = bckp->val;

		चयन (len) अणु
		हाल 1:
			rtw_ग_लिखो8(rtwdev, reg, (u8)val);
			अवरोध;
		हाल 2:
			rtw_ग_लिखो16(rtwdev, reg, (u16)val);
			अवरोध;
		हाल 4:
			rtw_ग_लिखो32(rtwdev, reg, (u32)val);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtw_restore_reg);

व्योम rtw_desc_to_mcsrate(u16 rate, u8 *mcs, u8 *nss)
अणु
	अगर (rate <= DESC_RATE54M)
		वापस;

	अगर (rate >= DESC_RATEVHT1SS_MCS0 &&
	    rate <= DESC_RATEVHT1SS_MCS9) अणु
		*nss = 1;
		*mcs = rate - DESC_RATEVHT1SS_MCS0;
	पूर्ण अन्यथा अगर (rate >= DESC_RATEVHT2SS_MCS0 &&
		   rate <= DESC_RATEVHT2SS_MCS9) अणु
		*nss = 2;
		*mcs = rate - DESC_RATEVHT2SS_MCS0;
	पूर्ण अन्यथा अगर (rate >= DESC_RATEVHT3SS_MCS0 &&
		   rate <= DESC_RATEVHT3SS_MCS9) अणु
		*nss = 3;
		*mcs = rate - DESC_RATEVHT3SS_MCS0;
	पूर्ण अन्यथा अगर (rate >= DESC_RATEVHT4SS_MCS0 &&
		   rate <= DESC_RATEVHT4SS_MCS9) अणु
		*nss = 4;
		*mcs = rate - DESC_RATEVHT4SS_MCS0;
	पूर्ण अन्यथा अगर (rate >= DESC_RATEMCS0 &&
		   rate <= DESC_RATEMCS15) अणु
		*mcs = rate - DESC_RATEMCS0;
	पूर्ण
पूर्ण
