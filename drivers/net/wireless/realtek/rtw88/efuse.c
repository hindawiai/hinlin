<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright(c) 2018-2019  Realtek Corporation
 */

#समावेश <linux/iopoll.h>

#समावेश "main.h"
#समावेश "efuse.h"
#समावेश "reg.h"
#समावेश "debug.h"

#घोषणा RTW_EFUSE_BANK_WIFI		0x0

अटल व्योम चयन_efuse_bank(काष्ठा rtw_dev *rtwdev)
अणु
	rtw_ग_लिखो32_mask(rtwdev, REG_LDO_EFUSE_CTRL, BIT_MASK_EFUSE_BANK_SEL,
			 RTW_EFUSE_BANK_WIFI);
पूर्ण

#घोषणा invalid_efuse_header(hdr1, hdr2) \
	((hdr1) == 0xff || (((hdr1) & 0x1f) == 0xf && (hdr2) == 0xff))
#घोषणा invalid_efuse_content(word_en, i) \
	(((word_en) & BIT(i)) != 0x0)
#घोषणा get_efuse_blk_idx_2_byte(hdr1, hdr2) \
	((((hdr2) & 0xf0) >> 1) | (((hdr1) >> 5) & 0x07))
#घोषणा get_efuse_blk_idx_1_byte(hdr1) \
	(((hdr1) & 0xf0) >> 4)
#घोषणा block_idx_to_logical_idx(blk_idx, i) \
	(((blk_idx) << 3) + ((i) << 1))

/* efuse header क्रमmat
 *
 * | 7        5   4    0 | 7        4   3          0 | 15  8  7   0 |
 *   block[2:0]   0 1111   block[6:3]   word_en[3:0]   byte0  byte1
 * | header 1 (optional) |          header 2         |    word N    |
 *
 * word_en: 4 bits each word. 0 -> ग_लिखो; 1 -> not ग_लिखो
 * N: 1~4, depends on word_en
 */
अटल पूर्णांक rtw_dump_logical_efuse_map(काष्ठा rtw_dev *rtwdev, u8 *phy_map,
				      u8 *log_map)
अणु
	u32 physical_size = rtwdev->efuse.physical_size;
	u32 protect_size = rtwdev->efuse.protect_size;
	u32 logical_size = rtwdev->efuse.logical_size;
	u32 phy_idx, log_idx;
	u8 hdr1, hdr2;
	u8 blk_idx;
	u8 word_en;
	पूर्णांक i;

	क्रम (phy_idx = 0; phy_idx < physical_size - protect_size;) अणु
		hdr1 = phy_map[phy_idx];
		hdr2 = phy_map[phy_idx + 1];
		अगर (invalid_efuse_header(hdr1, hdr2))
			अवरोध;

		अगर ((hdr1 & 0x1f) == 0xf) अणु
			/* 2-byte header क्रमmat */
			blk_idx = get_efuse_blk_idx_2_byte(hdr1, hdr2);
			word_en = hdr2 & 0xf;
			phy_idx += 2;
		पूर्ण अन्यथा अणु
			/* 1-byte header क्रमmat */
			blk_idx = get_efuse_blk_idx_1_byte(hdr1);
			word_en = hdr1 & 0xf;
			phy_idx += 1;
		पूर्ण

		क्रम (i = 0; i < 4; i++) अणु
			अगर (invalid_efuse_content(word_en, i))
				जारी;

			log_idx = block_idx_to_logical_idx(blk_idx, i);
			अगर (phy_idx + 1 > physical_size - protect_size ||
			    log_idx + 1 > logical_size)
				वापस -EINVAL;

			log_map[log_idx] = phy_map[phy_idx];
			log_map[log_idx + 1] = phy_map[phy_idx + 1];
			phy_idx += 2;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rtw_dump_physical_efuse_map(काष्ठा rtw_dev *rtwdev, u8 *map)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	u32 size = rtwdev->efuse.physical_size;
	u32 efuse_ctl;
	u32 addr;
	u32 cnt;

	rtw_chip_efuse_grant_on(rtwdev);

	चयन_efuse_bank(rtwdev);

	/* disable 2.5V LDO */
	chip->ops->cfg_lकरो25(rtwdev, false);

	efuse_ctl = rtw_पढ़ो32(rtwdev, REG_EFUSE_CTRL);

	क्रम (addr = 0; addr < size; addr++) अणु
		efuse_ctl &= ~(BIT_MASK_EF_DATA | BITS_EF_ADDR);
		efuse_ctl |= (addr & BIT_MASK_EF_ADDR) << BIT_SHIFT_EF_ADDR;
		rtw_ग_लिखो32(rtwdev, REG_EFUSE_CTRL, efuse_ctl & (~BIT_EF_FLAG));

		cnt = 1000000;
		करो अणु
			udelay(1);
			efuse_ctl = rtw_पढ़ो32(rtwdev, REG_EFUSE_CTRL);
			अगर (--cnt == 0)
				वापस -EBUSY;
		पूर्ण जबतक (!(efuse_ctl & BIT_EF_FLAG));

		*(map + addr) = (u8)(efuse_ctl & BIT_MASK_EF_DATA);
	पूर्ण

	rtw_chip_efuse_grant_off(rtwdev);

	वापस 0;
पूर्ण

पूर्णांक rtw_पढ़ो8_physical_efuse(काष्ठा rtw_dev *rtwdev, u16 addr, u8 *data)
अणु
	u32 efuse_ctl;
	पूर्णांक ret;

	rtw_ग_लिखो32_mask(rtwdev, REG_EFUSE_CTRL, 0x3ff00, addr);
	rtw_ग_लिखो32_clr(rtwdev, REG_EFUSE_CTRL, BIT_EF_FLAG);

	ret = पढ़ो_poll_समयout(rtw_पढ़ो32, efuse_ctl, efuse_ctl & BIT_EF_FLAG,
				1000, 100000, false, rtwdev, REG_EFUSE_CTRL);
	अगर (ret) अणु
		*data = EFUSE_READ_FAIL;
		वापस ret;
	पूर्ण

	*data = rtw_पढ़ो8(rtwdev, REG_EFUSE_CTRL);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtw_पढ़ो8_physical_efuse);

पूर्णांक rtw_parse_efuse_map(काष्ठा rtw_dev *rtwdev)
अणु
	काष्ठा rtw_chip_info *chip = rtwdev->chip;
	काष्ठा rtw_efuse *efuse = &rtwdev->efuse;
	u32 phy_size = efuse->physical_size;
	u32 log_size = efuse->logical_size;
	u8 *phy_map = शून्य;
	u8 *log_map = शून्य;
	पूर्णांक ret = 0;

	phy_map = kदो_स्मृति(phy_size, GFP_KERNEL);
	log_map = kदो_स्मृति(log_size, GFP_KERNEL);
	अगर (!phy_map || !log_map) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त;
	पूर्ण

	ret = rtw_dump_physical_efuse_map(rtwdev, phy_map);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to dump efuse physical map\n");
		जाओ out_मुक्त;
	पूर्ण

	स_रखो(log_map, 0xff, log_size);
	ret = rtw_dump_logical_efuse_map(rtwdev, phy_map, log_map);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to dump efuse logical map\n");
		जाओ out_मुक्त;
	पूर्ण

	ret = chip->ops->पढ़ो_efuse(rtwdev, log_map);
	अगर (ret) अणु
		rtw_err(rtwdev, "failed to read efuse map\n");
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	kमुक्त(log_map);
	kमुक्त(phy_map);

	वापस ret;
पूर्ण
