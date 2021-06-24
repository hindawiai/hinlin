<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * rtl8712_efuse.c
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 * Linux device driver क्रम RTL8192SU
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>.
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/

#घोषणा _RTL8712_EFUSE_C_

#समावेश "osdep_service.h"
#समावेश "drv_types.h"
#समावेश "rtl8712_efuse.h"

/* reserve 3 bytes क्रम HW stop पढ़ो */
अटल पूर्णांक efuse_available_max_size = EFUSE_MAX_SIZE - 3 /*0x1FD*/;

अटल व्योम efuse_reg_ctrl(काष्ठा _adapter *adapter, u8 bPowerOn)
अणु
	u8 पंचांगpu8 = 0;

	अगर (bPowerOn) अणु
		/* -----------------e-fuse pwr & clk reg ctrl ---------------
		 * Enable LDOE25 Macro Block
		 */
		पंचांगpu8 = r8712_पढ़ो8(adapter, EFUSE_TEST + 3);
		पंचांगpu8 |= 0x80;
		r8712_ग_लिखो8(adapter, EFUSE_TEST + 3, पंचांगpu8);
		msleep(20); /* क्रम some platक्रमm , need some delay समय */
		/* Change Efuse Clock क्रम ग_लिखो action to 40MHZ */
		r8712_ग_लिखो8(adapter, EFUSE_CLK_CTRL, 0x03);
		msleep(20); /* क्रम some platक्रमm , need some delay समय */
	पूर्ण अन्यथा अणु
		/* -----------------e-fuse pwr & clk reg ctrl -----------------
		 * Disable LDOE25 Macro Block
		 */
		पंचांगpu8 = r8712_पढ़ो8(adapter, EFUSE_TEST + 3);
		पंचांगpu8 &= 0x7F;
		r8712_ग_लिखो8(adapter, EFUSE_TEST + 3, पंचांगpu8);
		/* Change Efuse Clock क्रम ग_लिखो action to 500K */
		r8712_ग_लिखो8(adapter, EFUSE_CLK_CTRL, 0x02);
	पूर्ण
पूर्ण

/*
 * Beक्रमe ग_लिखो E-Fuse, this function must be called.
 */
u8 r8712_efuse_reg_init(काष्ठा _adapter *adapter)
अणु
	वापस true;
पूर्ण

व्योम r8712_efuse_reg_uninit(काष्ठा _adapter *adapter)
अणु
	efuse_reg_ctrl(adapter, false);
पूर्ण

अटल u8 efuse_one_byte_पढ़ो(काष्ठा _adapter *adapter, u16 addr, u8 *data)
अणु
	u8 पंचांगpidx = 0, bResult;

	/* -----------------e-fuse reg ctrl --------------------------------- */
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 1, (u8)(addr & 0xFF)); /* address */
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 2, ((u8)((addr >> 8) & 0x03)) |
	       (r8712_पढ़ो8(adapter, EFUSE_CTRL + 2) & 0xFC));
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 3, 0x72); /* पढ़ो cmd */
	/* रुको क्रम complete */
	जबतक (!(0x80 & r8712_पढ़ो8(adapter, EFUSE_CTRL + 3)) &&
	       (पंचांगpidx < 100))
		पंचांगpidx++;
	अगर (पंचांगpidx < 100) अणु
		*data = r8712_पढ़ो8(adapter, EFUSE_CTRL);
		bResult = true;
	पूर्ण अन्यथा अणु
		*data = 0xff;
		bResult = false;
	पूर्ण
	वापस bResult;
पूर्ण

अटल u8 efuse_one_byte_ग_लिखो(काष्ठा _adapter *adapter, u16 addr, u8 data)
अणु
	u8 पंचांगpidx = 0, bResult;

	/* -----------------e-fuse reg ctrl -------------------------------- */
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 1, (u8)(addr & 0xFF)); /* address */
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 2, ((u8)((addr >> 8) & 0x03)) |
	       (r8712_पढ़ो8(adapter, EFUSE_CTRL + 2) & 0xFC));
	r8712_ग_लिखो8(adapter, EFUSE_CTRL, data); /* data */
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 3, 0xF2); /* ग_लिखो cmd */
	/* रुको क्रम complete */
	जबतक ((0x80 &  r8712_पढ़ो8(adapter, EFUSE_CTRL + 3)) &&
	       (पंचांगpidx < 100))
		पंचांगpidx++;
	अगर (पंचांगpidx < 100)
		bResult = true;
	अन्यथा
		bResult = false;
	वापस bResult;
पूर्ण

अटल u8 efuse_one_byte_rw(काष्ठा _adapter *adapter, u8 bRead, u16 addr,
			    u8 *data)
अणु
	u8 पंचांगpidx = 0, पंचांगpv8 = 0, bResult;

	/* -----------------e-fuse reg ctrl --------------------------------- */
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 1, (u8)(addr & 0xFF)); /* address */
	पंचांगpv8 = ((u8)((addr >> 8) & 0x03)) |
		 (r8712_पढ़ो8(adapter, EFUSE_CTRL + 2) & 0xFC);
	r8712_ग_लिखो8(adapter, EFUSE_CTRL + 2, पंचांगpv8);
	अगर (bRead) अणु
		r8712_ग_लिखो8(adapter, EFUSE_CTRL + 3,  0x72); /* पढ़ो cmd */
		जबतक (!(0x80 & r8712_पढ़ो8(adapter, EFUSE_CTRL + 3)) &&
		       (पंचांगpidx < 100))
			पंचांगpidx++;
		अगर (पंचांगpidx < 100) अणु
			*data = r8712_पढ़ो8(adapter, EFUSE_CTRL);
			bResult = true;
		पूर्ण अन्यथा अणु
			*data = 0;
			bResult = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		r8712_ग_लिखो8(adapter, EFUSE_CTRL, *data); /* data */
		r8712_ग_लिखो8(adapter, EFUSE_CTRL + 3, 0xF2); /* ग_लिखो cmd */
		जबतक ((0x80 & r8712_पढ़ो8(adapter, EFUSE_CTRL + 3)) &&
		       (पंचांगpidx < 100))
			पंचांगpidx++;
		अगर (पंचांगpidx < 100)
			bResult = true;
		अन्यथा
			bResult = false;
	पूर्ण
	वापस bResult;
पूर्ण

अटल u8 efuse_is_empty(काष्ठा _adapter *adapter, u8 *empty)
अणु
	u8 value, ret = true;

	/* पढ़ो one byte to check अगर E-Fuse is empty */
	अगर (efuse_one_byte_rw(adapter, true, 0, &value)) अणु
		अगर (value == 0xFF)
			*empty = true;
		अन्यथा
			*empty = false;
	पूर्ण अन्यथा अणु
		ret = false;
	पूर्ण
	वापस ret;
पूर्ण

व्योम r8712_efuse_change_max_size(काष्ठा _adapter *adapter)
अणु
	u16 pre_pg_data_saddr = 0x1FB;
	u16 i;
	u16 pre_pg_data_size = 5;
	u8 pre_pg_data[5];

	क्रम (i = 0; i < pre_pg_data_size; i++)
		efuse_one_byte_पढ़ो(adapter, pre_pg_data_saddr + i,
				    &pre_pg_data[i]);
	अगर ((pre_pg_data[0] == 0x03) && (pre_pg_data[1] == 0x00) &&
	    (pre_pg_data[2] == 0x00) && (pre_pg_data[3] == 0x00) &&
	    (pre_pg_data[4] == 0x0C))
		efuse_available_max_size -= pre_pg_data_size;
पूर्ण

पूर्णांक r8712_efuse_get_max_size(काष्ठा _adapter *adapter)
अणु
	वापस	efuse_available_max_size;
पूर्ण

अटल u8 calculate_word_cnts(स्थिर u8 word_en)
अणु
	u8 word_cnts = 0;
	u8 word_idx;

	क्रम (word_idx = 0; word_idx < PGPKG_MAX_WORDS; word_idx++)
		अगर (!(word_en & BIT(word_idx)))
			word_cnts++; /* 0 : ग_लिखो enable */
	वापस word_cnts;
पूर्ण

अटल व्योम pgpacket_copy_data(स्थिर u8 word_en, स्थिर u8 *sourdata,
			       u8 *targetdata)
अणु
	u8 पंचांगpindex = 0;
	u8 word_idx, byte_idx;

	क्रम (word_idx = 0; word_idx < PGPKG_MAX_WORDS; word_idx++) अणु
		अगर (!(word_en & BIT(word_idx))) अणु
			byte_idx = word_idx * 2;
			targetdata[byte_idx] = sourdata[पंचांगpindex++];
			targetdata[byte_idx + 1] = sourdata[पंचांगpindex++];
		पूर्ण
	पूर्ण
पूर्ण

u16 r8712_efuse_get_current_size(काष्ठा _adapter *adapter)
अणु
	पूर्णांक bContinual = true;
	u16 efuse_addr = 0;
	u8 hworden = 0;
	u8 efuse_data, word_cnts = 0;

	जबतक (bContinual && efuse_one_byte_पढ़ो(adapter, efuse_addr,
	       &efuse_data) && (efuse_addr < efuse_available_max_size)) अणु
		अगर (efuse_data != 0xFF) अणु
			hworden =  efuse_data & 0x0F;
			word_cnts = calculate_word_cnts(hworden);
			/* पढ़ो next header */
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
		पूर्ण अन्यथा अणु
			bContinual = false;
		पूर्ण
	पूर्ण
	वापस efuse_addr;
पूर्ण

u8 r8712_efuse_pg_packet_पढ़ो(काष्ठा _adapter *adapter, u8 offset, u8 *data)
अणु
	u8 hoffset = 0, hworden = 0, word_cnts = 0;
	u16 efuse_addr = 0;
	u8 efuse_data;
	u8 पंचांगpidx = 0;
	u8 पंचांगpdata[PGPKT_DATA_SIZE];
	u8 ret = true;

	अगर (!data)
		वापस false;
	अगर (offset > 0x0f)
		वापस false;
	स_रखो(data, 0xFF, माप(u8) * PGPKT_DATA_SIZE);
	जबतक (efuse_addr < efuse_available_max_size) अणु
		अगर (efuse_one_byte_पढ़ो(adapter, efuse_addr, &efuse_data)) अणु
			अगर (efuse_data == 0xFF)
				अवरोध;
			hoffset = (efuse_data >> 4) & 0x0F;
			hworden =  efuse_data & 0x0F;
			word_cnts = calculate_word_cnts(hworden);
			अगर (hoffset == offset) अणु
				स_रखो(पंचांगpdata, 0xFF, PGPKT_DATA_SIZE);
				क्रम (पंचांगpidx = 0; पंचांगpidx < word_cnts * 2;
				     पंचांगpidx++) अणु
					अगर (efuse_one_byte_पढ़ो(adapter,
					    efuse_addr + 1 + पंचांगpidx,
					    &efuse_data)) अणु
						पंचांगpdata[पंचांगpidx] = efuse_data;
					पूर्ण अन्यथा अणु
						ret = false;
					पूर्ण
				पूर्ण
				pgpacket_copy_data(hworden, पंचांगpdata, data);
			पूर्ण
			efuse_addr += 1 + (word_cnts * 2);
		पूर्ण अन्यथा अणु
			ret = false;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल u8 fix_header(काष्ठा _adapter *adapter, u8 header, u16 header_addr)
अणु
	काष्ठा PGPKT_STRUCT pkt;
	u8 offset, word_en, value;
	u16 addr;
	पूर्णांक i;
	u8 ret = true;

	pkt.offset = GET_EFUSE_OFFSET(header);
	pkt.word_en = GET_EFUSE_WORD_EN(header);
	addr = header_addr + 1 + calculate_word_cnts(pkt.word_en) * 2;
	अगर (addr > efuse_available_max_size)
		वापस false;
	/* retrieve original data */
	addr = 0;
	जबतक (addr < header_addr) अणु
		अगर (!efuse_one_byte_पढ़ो(adapter, addr++, &value)) अणु
			ret = false;
			अवरोध;
		पूर्ण
		offset = GET_EFUSE_OFFSET(value);
		word_en = GET_EFUSE_WORD_EN(value);
		अगर (pkt.offset != offset) अणु
			addr += calculate_word_cnts(word_en) * 2;
			जारी;
		पूर्ण
		क्रम (i = 0; i < PGPKG_MAX_WORDS; i++) अणु
			अगर (BIT(i) & word_en) अणु
				अगर (BIT(i) & pkt.word_en) अणु
					अगर (efuse_one_byte_पढ़ो(
							adapter, addr,
							&value))
						pkt.data[i * 2] = value;
					अन्यथा
						वापस false;
					अगर (efuse_one_byte_पढ़ो(
							adapter,
							addr + 1,
							&value))
						pkt.data[i * 2 + 1] =
							value;
					अन्यथा
						वापस false;
				पूर्ण
				addr += 2;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (addr != header_addr)
		वापस false;
	addr++;
	/* fill original data */
	क्रम (i = 0; i < PGPKG_MAX_WORDS; i++) अणु
		अगर (BIT(i) & pkt.word_en) अणु
			efuse_one_byte_ग_लिखो(adapter, addr, pkt.data[i * 2]);
			efuse_one_byte_ग_लिखो(adapter, addr + 1,
					     pkt.data[i * 2 + 1]);
			/* additional check */
			अगर (!efuse_one_byte_पढ़ो(adapter, addr, &value)) अणु
				ret = false;
			पूर्ण अन्यथा अगर (pkt.data[i * 2] != value) अणु
				ret = false;
				अगर (value == 0xFF) /* ग_लिखो again */
					efuse_one_byte_ग_लिखो(adapter, addr,
							     pkt.data[i * 2]);
			पूर्ण
			अगर (!efuse_one_byte_पढ़ो(adapter, addr + 1, &value)) अणु
				ret = false;
			पूर्ण अन्यथा अगर (pkt.data[i * 2 + 1] != value) अणु
				ret = false;
				अगर (value == 0xFF) /* ग_लिखो again */
					efuse_one_byte_ग_लिखो(adapter, addr + 1,
							     pkt.data[i * 2 +
								      1]);
			पूर्ण
		पूर्ण
		addr += 2;
	पूर्ण
	वापस ret;
पूर्ण

u8 r8712_efuse_pg_packet_ग_लिखो(काष्ठा _adapter *adapter, स्थिर u8 offset,
			       स्थिर u8 word_en, स्थिर u8 *data)
अणु
	u8 pg_header = 0;
	u16 efuse_addr = 0, curr_size = 0;
	u8 efuse_data, target_word_cnts = 0;
	पूर्णांक repeat_बार;
	पूर्णांक sub_repeat;
	u8 bResult = true;

	/* check अगर E-Fuse Clock Enable and E-Fuse Clock is 40M */
	efuse_data = r8712_पढ़ो8(adapter, EFUSE_CLK_CTRL);
	अगर (efuse_data != 0x03)
		वापस false;
	pg_header = MAKE_EFUSE_HEADER(offset, word_en);
	target_word_cnts = calculate_word_cnts(word_en);
	repeat_बार = 0;
	efuse_addr = 0;
	जबतक (efuse_addr < efuse_available_max_size) अणु
		curr_size = r8712_efuse_get_current_size(adapter);
		अगर ((curr_size + 1 + target_word_cnts * 2) >
		     efuse_available_max_size)
			वापस false; /*target_word_cnts + pg header(1 byte)*/
		efuse_addr = curr_size; /* current size is also the last addr*/
		efuse_one_byte_ग_लिखो(adapter, efuse_addr, pg_header); /*hdr*/
		sub_repeat = 0;
		/* check अगर what we पढ़ो is what we ग_लिखो */
		जबतक (!efuse_one_byte_पढ़ो(adapter, efuse_addr,
					    &efuse_data)) अणु
			अगर (++sub_repeat > _REPEAT_THRESHOLD_) अणु
				bResult = false; /* जारी to blind ग_लिखो */
				अवरोध; /* जारी to blind ग_लिखो */
			पूर्ण
		पूर्ण
		अगर ((sub_repeat > _REPEAT_THRESHOLD_) ||
		    (pg_header == efuse_data)) अणु
			/* ग_लिखो header ok OR can't check header(creep) */
			u8 i;

			/* go to next address */
			efuse_addr++;
			क्रम (i = 0; i < target_word_cnts * 2; i++) अणु
				efuse_one_byte_ग_लिखो(adapter,
						     efuse_addr + i,
						     *(data + i));
				अगर (!efuse_one_byte_पढ़ो(adapter,
							 efuse_addr + i,
							 &efuse_data))
					bResult = false;
				अन्यथा अगर (*(data + i) != efuse_data) /* fail */
					bResult = false;
			पूर्ण
			अवरोध;
		पूर्ण
		/* ग_लिखो header fail */
		bResult = false;
		अगर (efuse_data == 0xFF)
			वापस bResult; /* nothing damaged. */
		/* call rescue procedure */
		अगर (!fix_header(adapter, efuse_data, efuse_addr))
			वापस false; /* rescue fail */

		अगर (++repeat_बार > _REPEAT_THRESHOLD_) /* fail */
			अवरोध;
		/* otherwise, take another risk... */
	पूर्ण
	वापस bResult;
पूर्ण

u8 r8712_efuse_access(काष्ठा _adapter *adapter, u8 bRead, u16 start_addr,
		      u16 cnts, u8 *data)
अणु
	पूर्णांक i;
	u8 res = true;

	अगर (start_addr > EFUSE_MAX_SIZE)
		वापस false;
	अगर (!bRead && ((start_addr + cnts) >
	   efuse_available_max_size))
		वापस false;
	अगर (!bRead && !r8712_efuse_reg_init(adapter))
		वापस false;
	/* -----------------e-fuse one byte पढ़ो / ग_लिखो ---------------------*/
	क्रम (i = 0; i < cnts; i++) अणु
		अगर ((start_addr + i) > EFUSE_MAX_SIZE) अणु
			res = false;
			अवरोध;
		पूर्ण
		res = efuse_one_byte_rw(adapter, bRead, start_addr + i,
					data + i);
		अगर (!bRead && !res)
			अवरोध;
	पूर्ण
	अगर (!bRead)
		r8712_efuse_reg_uninit(adapter);
	वापस res;
पूर्ण

u8 r8712_efuse_map_पढ़ो(काष्ठा _adapter *adapter, u16 addr, u16 cnts, u8 *data)
अणु
	u8 offset, ret = true;
	u8 pktdata[PGPKT_DATA_SIZE];
	पूर्णांक i, idx;

	अगर ((addr + cnts) > EFUSE_MAP_MAX_SIZE)
		वापस false;
	अगर (efuse_is_empty(adapter, &offset) && offset) अणु
		क्रम (i = 0; i < cnts; i++)
			data[i] = 0xFF;
		वापस ret;
	पूर्ण
	offset = (addr >> 3) & 0xF;
	ret = r8712_efuse_pg_packet_पढ़ो(adapter, offset, pktdata);
	i = addr & 0x7;	/* pktdata index */
	idx = 0;	/* data index */

	करो अणु
		क्रम (; i < PGPKT_DATA_SIZE; i++) अणु
			data[idx++] = pktdata[i];
			अगर (idx == cnts)
				वापस ret;
		पूर्ण
		offset++;
		अगर (!r8712_efuse_pg_packet_पढ़ो(adapter, offset, pktdata))
			ret = false;
		i = 0;
	पूर्ण जबतक (1);
	वापस ret;
पूर्ण

u8 r8712_efuse_map_ग_लिखो(काष्ठा _adapter *adapter, u16 addr, u16 cnts,
			 u8 *data)
अणु
	u8 offset, word_en, empty;
	u8 pktdata[PGPKT_DATA_SIZE], newdata[PGPKT_DATA_SIZE];
	पूर्णांक i, j, idx;

	अगर ((addr + cnts) > EFUSE_MAP_MAX_SIZE)
		वापस false;
	/* check अगर E-Fuse Clock Enable and E-Fuse Clock is 40M */
	empty = r8712_पढ़ो8(adapter, EFUSE_CLK_CTRL);
	अगर (empty != 0x03)
		वापस false;
	अगर (efuse_is_empty(adapter, &empty)) अणु
		अगर (empty)
			स_रखो(pktdata, 0xFF, PGPKT_DATA_SIZE);
	पूर्ण अन्यथा अणु
		वापस false;
	पूर्ण
	offset = (addr >> 3) & 0xF;
	अगर (!empty)
		अगर (!r8712_efuse_pg_packet_पढ़ो(adapter, offset, pktdata))
			वापस false;
	word_en = 0xF;
	स_रखो(newdata, 0xFF, PGPKT_DATA_SIZE);
	i = addr & 0x7;	/* pktdata index */
	j = 0;		/* newdata index */
	idx = 0;	/* data index */

	अगर (i & 0x1) अणु
		/*  odd start */
		अगर (data[idx] != pktdata[i]) अणु
			word_en &= ~BIT(i >> 1);
			newdata[j++] = pktdata[i - 1];
			newdata[j++] = data[idx];
		पूर्ण
		i++;
		idx++;
	पूर्ण
	करो अणु
		क्रम (; i < PGPKT_DATA_SIZE; i += 2) अणु
			अगर ((cnts - idx) == 1) अणु
				अगर (data[idx] != pktdata[i]) अणु
					word_en &= ~BIT(i >> 1);
					newdata[j++] = data[idx];
					newdata[j++] = pktdata[1 + 1];
				पूर्ण
				idx++;
				अवरोध;
			पूर्ण

			अगर ((data[idx] != pktdata[i]) || (data[idx + 1] !=
			     pktdata[i + 1])) अणु
				word_en &= ~BIT(i >> 1);
				newdata[j++] = data[idx];
				newdata[j++] = data[idx + 1];
			पूर्ण
			idx += 2;

			अगर (idx == cnts)
				अवरोध;
		पूर्ण

		अगर (word_en != 0xF)
			अगर (!r8712_efuse_pg_packet_ग_लिखो(adapter, offset,
							 word_en, newdata))
				वापस false;
		अगर (idx == cnts)
			अवरोध;
		offset++;
		अगर (!empty)
			अगर (!r8712_efuse_pg_packet_पढ़ो(adapter, offset,
							pktdata))
				वापस false;
		i = 0;
		j = 0;
		word_en = 0xF;
		स_रखो(newdata, 0xFF, PGPKT_DATA_SIZE);
	पूर्ण जबतक (1);

	वापस true;
पूर्ण
