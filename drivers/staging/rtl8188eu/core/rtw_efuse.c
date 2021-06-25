<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#घोषणा _RTW_EFUSE_C_

#समावेश <osdep_service.h>
#समावेश <drv_types.h>
#समावेश <rtw_efuse.h>
#समावेश <usb_ops_linux.h>
#समावेश <rtl8188e_hal.h>
#समावेश <rtw_iol.h>

#घोषणा REG_EFUSE_CTRL		0x0030
#घोषणा EFUSE_CTRL			REG_EFUSE_CTRL		/*  E-Fuse Control. */

क्रमागतअणु
		VOLTAGE_V25						= 0x03,
		LDOE25_SHIFT						= 28,
	पूर्ण;

/*
 * When we want to enable ग_लिखो operation, we should change to pwr on state.
 * When we stop ग_लिखो, we should चयन to 500k mode and disable LDO 2.5V.
 */
अटल व्योम efuse_घातer_चयन(काष्ठा adapter *pAdapter, u8 ग_लिखो, u8 pwrstate)
अणु
	u8 tempval;
	u16 पंचांगpv16;

	अगर (pwrstate) अणु
		usb_ग_लिखो8(pAdapter, REG_EFUSE_ACCESS, EFUSE_ACCESS_ON);

		/*  1.2V Power: From VDDON with Power Cut(0x0000h[15]), शेष valid */
		पंचांगpv16 = usb_पढ़ो16(pAdapter, REG_SYS_ISO_CTRL);
		अगर (!(पंचांगpv16 & PWC_EV12V)) अणु
			पंचांगpv16 |= PWC_EV12V;
			usb_ग_लिखो16(pAdapter, REG_SYS_ISO_CTRL, पंचांगpv16);
		पूर्ण
		/*  Reset: 0x0000h[28], शेष valid */
		पंचांगpv16 =  usb_पढ़ो16(pAdapter, REG_SYS_FUNC_EN);
		अगर (!(पंचांगpv16 & FEN_ELDR)) अणु
			पंचांगpv16 |= FEN_ELDR;
			usb_ग_लिखो16(pAdapter, REG_SYS_FUNC_EN, पंचांगpv16);
		पूर्ण

		/*  Clock: Gated(0x0008h[5]) 8M(0x0008h[1]) घड़ी from ANA, शेष valid */
		पंचांगpv16 = usb_पढ़ो16(pAdapter, REG_SYS_CLKR);
		अगर ((!(पंचांगpv16 & LOADER_CLK_EN))  || (!(पंचांगpv16 & ANA8M))) अणु
			पंचांगpv16 |= (LOADER_CLK_EN | ANA8M);
			usb_ग_लिखो16(pAdapter, REG_SYS_CLKR, पंचांगpv16);
		पूर्ण

		अगर (ग_लिखो) अणु
			/*  Enable LDO 2.5V beक्रमe पढ़ो/ग_लिखो action */
			tempval = usb_पढ़ो8(pAdapter, EFUSE_TEST + 3);
			tempval &= 0x0F;
			tempval |= (VOLTAGE_V25 << 4);
			usb_ग_लिखो8(pAdapter, EFUSE_TEST + 3, (tempval | 0x80));
		पूर्ण
	पूर्ण अन्यथा अणु
		usb_ग_लिखो8(pAdapter, REG_EFUSE_ACCESS, EFUSE_ACCESS_OFF);

		अगर (ग_लिखो) अणु
			/*  Disable LDO 2.5V after पढ़ो/ग_लिखो action */
			tempval = usb_पढ़ो8(pAdapter, EFUSE_TEST + 3);
			usb_ग_लिखो8(pAdapter, EFUSE_TEST + 3, (tempval & 0x7F));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
efuse_phymap_to_logical(u8 *phymap, u16 _offset, u16 _size_byte, u8  *pbuf)
अणु
	u8 *efuseTbl = शून्य;
	u8 rtemp8;
	u16	eFuse_Addr = 0;
	u8 offset, wren;
	u16	i, j;
	u16	**eFuseWord = शून्य;
	u16	efuse_utilized = 0;
	u8 u1temp = 0;
	व्योम **पंचांगp = शून्य;

	efuseTbl = kzalloc(EFUSE_MAP_LEN_88E, GFP_KERNEL);
	अगर (!efuseTbl)
		वापस;

	पंचांगp = kसुस्मृति(EFUSE_MAX_SECTION_88E,
		      माप(व्योम *) + EFUSE_MAX_WORD_UNIT * माप(u16),
		      GFP_KERNEL);
	अगर (!पंचांगp) अणु
		DBG_88E("%s: alloc eFuseWord fail!\n", __func__);
		जाओ eFuseWord_failed;
	पूर्ण
	क्रम (i = 0; i < EFUSE_MAX_SECTION_88E; i++)
		पंचांगp[i] = ((अक्षर *)(पंचांगp + EFUSE_MAX_SECTION_88E)) + i * EFUSE_MAX_WORD_UNIT * माप(u16);
	eFuseWord = (u16 **)पंचांगp;

	/*  0. Refresh efuse init map as all oxFF. */
	क्रम (i = 0; i < EFUSE_MAX_SECTION_88E; i++)
		क्रम (j = 0; j < EFUSE_MAX_WORD_UNIT; j++)
			eFuseWord[i][j] = 0xFFFF;

	/*  */
	/*  1. Read the first byte to check अगर efuse is empty!!! */
	/*  */
	/*  */
	rtemp8 = *(phymap + eFuse_Addr);
	अगर (rtemp8 != 0xFF) अणु
		efuse_utilized++;
		eFuse_Addr++;
	पूर्ण अन्यथा अणु
		DBG_88E("EFUSE is empty efuse_Addr-%d efuse_data =%x\n", eFuse_Addr, rtemp8);
		जाओ निकास;
	पूर्ण

	/*  */
	/*  2. Read real efuse content. Filter PG header and every section data. */
	/*  */
	जबतक ((rtemp8 != 0xFF) && (eFuse_Addr < EFUSE_REAL_CONTENT_LEN_88E)) अणु
		/*  Check PG header क्रम section num. */
		अगर ((rtemp8 & 0x1F) == 0x0F) अणु		/* extended header */
			u1temp = (rtemp8 & 0xE0) >> 5;
			rtemp8 = *(phymap + eFuse_Addr);
			अगर ((rtemp8 & 0x0F) == 0x0F) अणु
				eFuse_Addr++;
				rtemp8 = *(phymap + eFuse_Addr);

				अगर (rtemp8 != 0xFF && (eFuse_Addr < EFUSE_REAL_CONTENT_LEN_88E))
					eFuse_Addr++;
				जारी;
			पूर्ण अन्यथा अणु
				offset = ((rtemp8 & 0xF0) >> 1) | u1temp;
				wren = rtemp8 & 0x0F;
				eFuse_Addr++;
			पूर्ण
		पूर्ण अन्यथा अणु
			offset = (rtemp8 >> 4) & 0x0f;
			wren = rtemp8 & 0x0f;
		पूर्ण

		अगर (offset < EFUSE_MAX_SECTION_88E) अणु
			/*  Get word enable value from PG header */
			क्रम (i = 0; i < EFUSE_MAX_WORD_UNIT; i++) अणु
				/*  Check word enable condition in the section */
				अगर (!(wren & 0x01)) अणु
					rtemp8 = *(phymap + eFuse_Addr);
					eFuse_Addr++;
					efuse_utilized++;
					eFuseWord[offset][i] = (rtemp8 & 0xff);
					अगर (eFuse_Addr >= EFUSE_REAL_CONTENT_LEN_88E)
						अवरोध;
					rtemp8 = *(phymap + eFuse_Addr);
					eFuse_Addr++;
					efuse_utilized++;
					eFuseWord[offset][i] |= (((u16)rtemp8 << 8) & 0xff00);

					अगर (eFuse_Addr >= EFUSE_REAL_CONTENT_LEN_88E)
						अवरोध;
				पूर्ण
				wren >>= 1;
			पूर्ण
		पूर्ण
		/*  Read next PG header */
		rtemp8 = *(phymap + eFuse_Addr);

		अगर (rtemp8 != 0xFF && (eFuse_Addr < EFUSE_REAL_CONTENT_LEN_88E)) अणु
			efuse_utilized++;
			eFuse_Addr++;
		पूर्ण
	पूर्ण

	/*  */
	/*  3. Collect 16 sections and 4 word unit पूर्णांकo Efuse map. */
	/*  */
	क्रम (i = 0; i < EFUSE_MAX_SECTION_88E; i++) अणु
		क्रम (j = 0; j < EFUSE_MAX_WORD_UNIT; j++) अणु
			efuseTbl[(i * 8) + (j * 2)] = (eFuseWord[i][j] & 0xff);
			efuseTbl[(i * 8) + ((j * 2) + 1)] = ((eFuseWord[i][j] >> 8) & 0xff);
		पूर्ण
	पूर्ण

	/*  */
	/*  4. Copy from Efuse map to output poपूर्णांकer memory!!! */
	/*  */
	क्रम (i = 0; i < _size_byte; i++)
		pbuf[i] = efuseTbl[_offset + i];

	/*  */
	/*  5. Calculate Efuse utilization. */
	/*  */

निकास:
	kमुक्त(eFuseWord);

eFuseWord_failed:
	kमुक्त(efuseTbl);
पूर्ण

अटल व्योम efuse_पढ़ो_phymap_from_txpktbuf(
	काष्ठा adapter  *adapter,
	पूर्णांक bcnhead,	/* beacon head, where FW store len(2-byte) and efuse physical map. */
	u8 *content,	/* buffer to store efuse physical map */
	u16 *size	/* क्रम efuse content: the max byte to पढ़ो. will update to byte पढ़ो */
	)
अणु
	u16 dbg_addr = 0;
	अचिन्हित दीर्घ start = 0;
	u8 reg_0x143 = 0;
	u32 lo32 = 0, hi32 = 0;
	u16 len = 0, count = 0;
	पूर्णांक i = 0;
	u16 limit = *size;

	u8 *pos = content;

	अगर (bcnhead < 0) /* अगर not valid */
		bcnhead = usb_पढ़ो8(adapter, REG_TDECTRL + 1);

	DBG_88E("%s bcnhead:%d\n", __func__, bcnhead);

	usb_ग_लिखो8(adapter, REG_PKT_BUFF_ACCESS_CTRL, TXPKT_BUF_SELECT);

	dbg_addr = bcnhead * 128 / 8; /* 8-bytes addressing */

	जबतक (1) अणु
		usb_ग_लिखो16(adapter, REG_PKTBUF_DBG_ADDR, dbg_addr + i);

		usb_ग_लिखो8(adapter, REG_TXPKTBUF_DBG, 0);
		start = jअगरfies;
		जबतक (!(reg_0x143 = usb_पढ़ो8(adapter, REG_TXPKTBUF_DBG)) &&
		       jअगरfies_to_msecs(jअगरfies - start) < 1000) अणु
			DBG_88E("%s polling reg_0x143:0x%02x, reg_0x106:0x%02x\n", __func__, reg_0x143, usb_पढ़ो8(adapter, 0x106));
			usleep_range(1000, 2000);
		पूर्ण

		lo32 = usb_पढ़ो32(adapter, REG_PKTBUF_DBG_DATA_L);
		hi32 = usb_पढ़ो32(adapter, REG_PKTBUF_DBG_DATA_H);

		अगर (i == 0) अणु
			u8 lenc[2];
			u16 lenbak, aaabak;
			u16 aaa;

			lenc[0] = usb_पढ़ो8(adapter, REG_PKTBUF_DBG_DATA_L);
			lenc[1] = usb_पढ़ो8(adapter, REG_PKTBUF_DBG_DATA_L + 1);

			aaabak = le16_to_cpup((__le16 *)lenc);
			lenbak = le16_to_cpu(*((__le16 *)lenc));
			aaa = le16_to_cpup((__le16 *)&lo32);
			len = le16_to_cpu(*((__le16 *)&lo32));

			limit = min_t(u16, len - 2, limit);

			DBG_88E("%s len:%u, lenbak:%u, aaa:%u, aaabak:%u\n", __func__, len, lenbak, aaa, aaabak);

			स_नकल(pos, ((u8 *)&lo32) + 2, (limit >= count + 2) ? 2 : limit - count);
			count += (limit >= count + 2) ? 2 : limit - count;
			pos = content + count;

		पूर्ण अन्यथा अणु
			स_नकल(pos, ((u8 *)&lo32), (limit >= count + 4) ? 4 : limit - count);
			count += (limit >= count + 4) ? 4 : limit - count;
			pos = content + count;
		पूर्ण

		अगर (limit > count && len - 2 > count) अणु
			स_नकल(pos, (u8 *)&hi32, (limit >= count + 4) ? 4 : limit - count);
			count += (limit >= count + 4) ? 4 : limit - count;
			pos = content + count;
		पूर्ण

		अगर (limit <= count || len - 2 <= count)
			अवरोध;
		i++;
	पूर्ण
	usb_ग_लिखो8(adapter, REG_PKT_BUFF_ACCESS_CTRL, DISABLE_TRXPKT_BUF_ACCESS);
	DBG_88E("%s read count:%u\n", __func__, count);
	*size = count;
पूर्ण

अटल s32 iol_पढ़ो_efuse(काष्ठा adapter *padapter, u8 txpktbuf_bndy, u16 offset, u16 size_byte, u8 *logical_map)
अणु
	s32 status = _FAIL;
	u8 physical_map[512];
	u16 size = 512;

	usb_ग_लिखो8(padapter, REG_TDECTRL + 1, txpktbuf_bndy);
	स_रखो(physical_map, 0xFF, 512);
	usb_ग_लिखो8(padapter, REG_PKT_BUFF_ACCESS_CTRL, TXPKT_BUF_SELECT);
	status = iol_execute(padapter, CMD_READ_EFUSE_MAP);
	अगर (status == _SUCCESS)
		efuse_पढ़ो_phymap_from_txpktbuf(padapter, txpktbuf_bndy, physical_map, &size);
	efuse_phymap_to_logical(physical_map, offset, size_byte, logical_map);
	वापस status;
पूर्ण

व्योम efuse_ReadEFuse(काष्ठा adapter *Adapter, u8 efuseType, u16 _offset, u16 _size_byte, u8 *pbuf)
अणु
	अगर (rtw_iol_applied(Adapter)) अणु
		rtw_hal_घातer_on(Adapter);
		iol_mode_enable(Adapter, 1);
		iol_पढ़ो_efuse(Adapter, 0, _offset, _size_byte, pbuf);
		iol_mode_enable(Adapter, 0);
	पूर्ण
पूर्ण

u8 Efuse_WordEnableDataWrite(काष्ठा adapter *pAdapter, u16 efuse_addr, u8 word_en, u8 *data)
अणु
	u16	पंचांगpaddr = 0;
	u16	start_addr = efuse_addr;
	u8 badworden = 0x0F;
	u8 पंचांगpdata[8];

	स_रखो(पंचांगpdata, 0xff, PGPKT_DATA_SIZE);

	अगर (!(word_en & BIT(0))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(pAdapter, start_addr++, data[0]);
		efuse_OneByteWrite(pAdapter, start_addr++, data[1]);

		efuse_OneByteRead(pAdapter, पंचांगpaddr, &पंचांगpdata[0]);
		efuse_OneByteRead(pAdapter, पंचांगpaddr + 1, &पंचांगpdata[1]);
		अगर ((data[0] != पंचांगpdata[0]) || (data[1] != पंचांगpdata[1]))
			badworden &= (~BIT(0));
	पूर्ण
	अगर (!(word_en & BIT(1))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(pAdapter, start_addr++, data[2]);
		efuse_OneByteWrite(pAdapter, start_addr++, data[3]);

		efuse_OneByteRead(pAdapter, पंचांगpaddr, &पंचांगpdata[2]);
		efuse_OneByteRead(pAdapter, पंचांगpaddr + 1, &पंचांगpdata[3]);
		अगर ((data[2] != पंचांगpdata[2]) || (data[3] != पंचांगpdata[3]))
			badworden &= (~BIT(1));
	पूर्ण
	अगर (!(word_en & BIT(2))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(pAdapter, start_addr++, data[4]);
		efuse_OneByteWrite(pAdapter, start_addr++, data[5]);

		efuse_OneByteRead(pAdapter, पंचांगpaddr, &पंचांगpdata[4]);
		efuse_OneByteRead(pAdapter, पंचांगpaddr + 1, &पंचांगpdata[5]);
		अगर ((data[4] != पंचांगpdata[4]) || (data[5] != पंचांगpdata[5]))
			badworden &= (~BIT(2));
	पूर्ण
	अगर (!(word_en & BIT(3))) अणु
		पंचांगpaddr = start_addr;
		efuse_OneByteWrite(pAdapter, start_addr++, data[6]);
		efuse_OneByteWrite(pAdapter, start_addr++, data[7]);

		efuse_OneByteRead(pAdapter, पंचांगpaddr, &पंचांगpdata[6]);
		efuse_OneByteRead(pAdapter, पंचांगpaddr + 1, &पंचांगpdata[7]);
		अगर ((data[6] != पंचांगpdata[6]) || (data[7] != पंचांगpdata[7]))
			badworden &= (~BIT(3));
	पूर्ण
	वापस badworden;
पूर्ण

अटल u16 Efuse_GetCurrentSize(काष्ठा adapter *pAdapter)
अणु
	u16	efuse_addr = 0;
	u8 hoffset = 0, hworden = 0;
	u8 efuse_data, word_cnts = 0;

	rtw_hal_get_hwreg(pAdapter, HW_VAR_EFUSE_BYTES, (u8 *)&efuse_addr);

	जबतक (efuse_OneByteRead(pAdapter, efuse_addr, &efuse_data) &&
	       AVAILABLE_EFUSE_ADDR(efuse_addr)) अणु
		अगर (efuse_data == 0xFF)
			अवरोध;
		अगर ((efuse_data & 0x1F) == 0x0F) अणु /* extended header */
			hoffset = efuse_data;
			efuse_addr++;
			efuse_OneByteRead(pAdapter, efuse_addr, &efuse_data);
			अगर ((efuse_data & 0x0F) == 0x0F) अणु
				efuse_addr++;
				जारी;
			पूर्ण अन्यथा अणु
				hoffset = ((hoffset & 0xE0) >> 5) |
					  ((efuse_data & 0xF0) >> 1);
				hworden = efuse_data & 0x0F;
			पूर्ण
		पूर्ण अन्यथा अणु
			hoffset = (efuse_data >> 4) & 0x0F;
			hworden =  efuse_data & 0x0F;
		पूर्ण
		word_cnts = Efuse_CalculateWordCnts(hworden);
		/* पढ़ो next header */
		efuse_addr = efuse_addr + (word_cnts * 2) + 1;
	पूर्ण

	rtw_hal_set_hwreg(pAdapter, HW_VAR_EFUSE_BYTES, (u8 *)&efuse_addr);

	वापस efuse_addr;
पूर्ण

पूर्णांक Efuse_PgPacketRead(काष्ठा adapter *pAdapter, u8 offset, u8 *data)
अणु
	u8 ReadState = PG_STATE_HEADER;
	पूर्णांक	bDataEmpty = true;
	u8 efuse_data, word_cnts = 0;
	u16	efuse_addr = 0;
	u8 hoffset = 0, hworden = 0;
	u8 पंचांगpidx = 0;
	u8 पंचांगpdata[8];
	u8 पंचांगp_header = 0;

	अगर (!data)
		वापस false;
	अगर (offset > EFUSE_MAX_SECTION_88E)
		वापस false;

	स_रखो(data, 0xff, माप(u8) * PGPKT_DATA_SIZE);
	स_रखो(पंचांगpdata, 0xff, माप(u8) * PGPKT_DATA_SIZE);

	/*  <Roger_TODO> Efuse has been pre-programmed dummy 5Bytes at the end of Efuse by CP. */
	/*  Skip dummy parts to prevent unexpected data पढ़ो from Efuse. */
	/*  By pass right now. 2009.02.19. */
	जबतक (AVAILABLE_EFUSE_ADDR(efuse_addr)) अणु
		/*   Header Read ------------- */
		अगर (ReadState & PG_STATE_HEADER) अणु
			अगर (efuse_OneByteRead(pAdapter, efuse_addr, &efuse_data) && (efuse_data != 0xFF)) अणु
				अगर (EXT_HEADER(efuse_data)) अणु
					पंचांगp_header = efuse_data;
					efuse_addr++;
					efuse_OneByteRead(pAdapter, efuse_addr, &efuse_data);
					अगर (!ALL_WORDS_DISABLED(efuse_data)) अणु
						hoffset = ((पंचांगp_header & 0xE0) >> 5) | ((efuse_data & 0xF0) >> 1);
						hworden = efuse_data & 0x0F;
					पूर्ण अन्यथा अणु
						DBG_88E("Error, All words disabled\n");
						efuse_addr++;
						जारी;
					पूर्ण
				पूर्ण अन्यथा अणु
					hoffset = (efuse_data >> 4) & 0x0F;
					hworden =  efuse_data & 0x0F;
				पूर्ण
				word_cnts = Efuse_CalculateWordCnts(hworden);
				bDataEmpty = true;

				अगर (hoffset == offset) अणु
					क्रम (पंचांगpidx = 0; पंचांगpidx < word_cnts * 2; पंचांगpidx++) अणु
						अगर (efuse_OneByteRead(pAdapter, efuse_addr + 1 + पंचांगpidx, &efuse_data)) अणु
							पंचांगpdata[पंचांगpidx] = efuse_data;
							अगर (efuse_data != 0xff)
								bDataEmpty = false;
						पूर्ण
					पूर्ण
					अगर (!bDataEmpty) अणु
						ReadState = PG_STATE_DATA;
					पूर्ण अन्यथा अणु/* पढ़ो next header */
						efuse_addr = efuse_addr + (word_cnts * 2) + 1;
						ReadState = PG_STATE_HEADER;
					पूर्ण
				पूर्ण अन्यथा अणु/* पढ़ो next header */
					efuse_addr = efuse_addr + (word_cnts * 2) + 1;
					ReadState = PG_STATE_HEADER;
				पूर्ण
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ReadState & PG_STATE_DATA) अणु
			/*   Data section Read ------------- */
			efuse_WordEnableDataRead(hworden, पंचांगpdata, data);
			efuse_addr = efuse_addr + (word_cnts * 2) + 1;
			ReadState = PG_STATE_HEADER;
		पूर्ण
	पूर्ण

	अगर ((data[0] == 0xff) && (data[1] == 0xff) && (data[2] == 0xff)  && (data[3] == 0xff) &&
	    (data[4] == 0xff) && (data[5] == 0xff) && (data[6] == 0xff)  && (data[7] == 0xff))
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल bool hal_EfuseFixHeaderProcess(काष्ठा adapter *pAdapter, u8 efuseType, काष्ठा pgpkt *pFixPkt, u16 *pAddr)
अणु
	u8 originaldata[8], badworden = 0;
	u16	efuse_addr = *pAddr;
	u32	PgWriteSuccess = 0;

	स_रखो(originaldata, 0xff, 8);

	अगर (Efuse_PgPacketRead(pAdapter, pFixPkt->offset, originaldata)) अणु
		/* check अगर data exist */
		badworden = Efuse_WordEnableDataWrite(pAdapter, efuse_addr + 1, pFixPkt->word_en, originaldata);

		अगर (badworden != 0xf) अणु	/*  ग_लिखो fail */
			PgWriteSuccess = Efuse_PgPacketWrite(pAdapter, pFixPkt->offset, badworden, originaldata);

			अगर (!PgWriteSuccess)
				वापस false;

			efuse_addr = Efuse_GetCurrentSize(pAdapter);
		पूर्ण अन्यथा अणु
			efuse_addr = efuse_addr + (pFixPkt->word_cnts * 2) + 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		efuse_addr = efuse_addr + (pFixPkt->word_cnts * 2) + 1;
	पूर्ण
	*pAddr = efuse_addr;
	वापस true;
पूर्ण

अटल bool hal_EfusePgPacketWrite2ByteHeader(काष्ठा adapter *pAdapter, u8 efuseType, u16 *pAddr, काष्ठा pgpkt *pTargetPkt)
अणु
	bool ret = false;
	u16 efuse_addr = *pAddr;
	u16 efuse_max_available_len =
		EFUSE_REAL_CONTENT_LEN_88E - EFUSE_OOB_PROTECT_BYTES_88E;
	u8 pg_header = 0, पंचांगp_header = 0, pg_header_temp = 0;
	u8 repeatcnt = 0;

	जबतक (efuse_addr < efuse_max_available_len) अणु
		pg_header = ((pTargetPkt->offset & 0x07) << 5) | 0x0F;
		efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
		efuse_OneByteRead(pAdapter, efuse_addr, &पंचांगp_header);

		जबतक (पंचांगp_header == 0xFF) अणु
			अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
				वापस false;

			efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
			efuse_OneByteRead(pAdapter, efuse_addr, &पंचांगp_header);
		पूर्ण

		/* to ग_लिखो ext_header */
		अगर (पंचांगp_header == pg_header) अणु
			efuse_addr++;
			pg_header_temp = pg_header;
			pg_header = ((pTargetPkt->offset & 0x78) << 1) | pTargetPkt->word_en;

			efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
			efuse_OneByteRead(pAdapter, efuse_addr, &पंचांगp_header);

			जबतक (पंचांगp_header == 0xFF) अणु
				अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
					वापस false;

				efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
				efuse_OneByteRead(pAdapter, efuse_addr, &पंचांगp_header);
			पूर्ण

			अगर ((पंचांगp_header & 0x0F) == 0x0F) अणु	/* word_en PG fail */
				अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
					वापस false;

				efuse_addr++;
				जारी;
			पूर्ण अन्यथा अगर (pg_header != पंचांगp_header) अणु	/* offset PG fail */
				काष्ठा pgpkt	fixPkt;

				fixPkt.offset = ((pg_header_temp & 0xE0) >> 5) | ((पंचांगp_header & 0xF0) >> 1);
				fixPkt.word_en = पंचांगp_header & 0x0F;
				fixPkt.word_cnts = Efuse_CalculateWordCnts(fixPkt.word_en);
				अगर (!hal_EfuseFixHeaderProcess(pAdapter, efuseType, &fixPkt, &efuse_addr))
					वापस false;
			पूर्ण अन्यथा अणु
				ret = true;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर ((पंचांगp_header & 0x1F) == 0x0F) अणु		/* wrong extended header */
			efuse_addr += 2;
			जारी;
		पूर्ण
	पूर्ण

	*pAddr = efuse_addr;
	वापस ret;
पूर्ण

अटल bool hal_EfusePgPacketWrite1ByteHeader(काष्ठा adapter *pAdapter, u8 efuseType, u16 *pAddr, काष्ठा pgpkt *pTargetPkt)
अणु
	bool ret = false;
	u8 pg_header = 0, पंचांगp_header = 0;
	u16	efuse_addr = *pAddr;
	u8 repeatcnt = 0;

	pg_header = ((pTargetPkt->offset << 4) & 0xf0) | pTargetPkt->word_en;

	efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
	efuse_OneByteRead(pAdapter, efuse_addr, &पंचांगp_header);

	जबतक (पंचांगp_header == 0xFF) अणु
		अगर (repeatcnt++ > EFUSE_REPEAT_THRESHOLD_)
			वापस false;
		efuse_OneByteWrite(pAdapter, efuse_addr, pg_header);
		efuse_OneByteRead(pAdapter, efuse_addr, &पंचांगp_header);
	पूर्ण

	अगर (pg_header == पंचांगp_header) अणु
		ret = true;
	पूर्ण अन्यथा अणु
		काष्ठा pgpkt	fixPkt;

		fixPkt.offset = (पंचांगp_header >> 4) & 0x0F;
		fixPkt.word_en = पंचांगp_header & 0x0F;
		fixPkt.word_cnts = Efuse_CalculateWordCnts(fixPkt.word_en);
		अगर (!hal_EfuseFixHeaderProcess(pAdapter, efuseType, &fixPkt, &efuse_addr))
			वापस false;
	पूर्ण

	*pAddr = efuse_addr;
	वापस ret;
पूर्ण

अटल bool hal_EfusePgPacketWriteData(काष्ठा adapter *pAdapter, u8 efuseType, u16 *pAddr, काष्ठा pgpkt *pTargetPkt)
अणु
	u16	efuse_addr = *pAddr;
	u8 badworden;
	u32	PgWriteSuccess = 0;

	badworden = Efuse_WordEnableDataWrite(pAdapter, efuse_addr + 1, pTargetPkt->word_en, pTargetPkt->data);
	अगर (badworden == 0x0F) अणु
		/*  ग_लिखो ok */
		वापस true;
	पूर्ण
	/* reorganize other pg packet */
	PgWriteSuccess = Efuse_PgPacketWrite(pAdapter, pTargetPkt->offset, badworden, pTargetPkt->data);
	अगर (!PgWriteSuccess)
		वापस false;
	अन्यथा
		वापस true;
पूर्ण

अटल bool
hal_EfusePgPacketWriteHeader(
				काष्ठा adapter *pAdapter,
				u8 efuseType,
				u16				*pAddr,
				काष्ठा pgpkt *pTargetPkt)
अणु
	bool ret = false;

	अगर (pTargetPkt->offset >= EFUSE_MAX_SECTION_BASE)
		ret = hal_EfusePgPacketWrite2ByteHeader(pAdapter, efuseType, pAddr, pTargetPkt);
	अन्यथा
		ret = hal_EfusePgPacketWrite1ByteHeader(pAdapter, efuseType, pAddr, pTargetPkt);

	वापस ret;
पूर्ण

अटल bool wordEnMatched(काष्ठा pgpkt *pTargetPkt, काष्ठा pgpkt *pCurPkt,
			  u8 *pWden)
अणु
	u8 match_word_en = 0x0F;	/*  शेष all words are disabled */

	/*  check अगर the same words are enabled both target and current PG packet */
	अगर (((pTargetPkt->word_en & BIT(0)) == 0) &&
	    ((pCurPkt->word_en & BIT(0)) == 0))
		match_word_en &= ~BIT(0);				/*  enable word 0 */
	अगर (((pTargetPkt->word_en & BIT(1)) == 0) &&
	    ((pCurPkt->word_en & BIT(1)) == 0))
		match_word_en &= ~BIT(1);				/*  enable word 1 */
	अगर (((pTargetPkt->word_en & BIT(2)) == 0) &&
	    ((pCurPkt->word_en & BIT(2)) == 0))
		match_word_en &= ~BIT(2);				/*  enable word 2 */
	अगर (((pTargetPkt->word_en & BIT(3)) == 0) &&
	    ((pCurPkt->word_en & BIT(3)) == 0))
		match_word_en &= ~BIT(3);				/*  enable word 3 */

	*pWden = match_word_en;

	अगर (match_word_en != 0xf)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

अटल bool hal_EfuseCheckIfDatafollowed(काष्ठा adapter *pAdapter, u8 word_cnts, u16 startAddr)
अणु
	bool ret = false;
	u8 i, efuse_data;

	क्रम (i = 0; i < (word_cnts * 2); i++) अणु
		अगर (efuse_OneByteRead(pAdapter, (startAddr + i), &efuse_data) && (efuse_data != 0xFF))
			ret = true;
	पूर्ण
	वापस ret;
पूर्ण

अटल bool hal_EfusePartialWriteCheck(काष्ठा adapter *pAdapter, u8 efuseType, u16 *pAddr, काष्ठा pgpkt *pTargetPkt)
अणु
	bool ret = false;
	u8 i, efuse_data = 0, cur_header = 0;
	u8 matched_wden = 0, badworden = 0;
	u16 startAddr = 0;
	u16 efuse_max_available_len =
		EFUSE_REAL_CONTENT_LEN_88E - EFUSE_OOB_PROTECT_BYTES_88E;
	काष्ठा pgpkt curPkt;

	rtw_hal_get_hwreg(pAdapter, HW_VAR_EFUSE_BYTES, (u8 *)&startAddr);
	startAddr %= EFUSE_REAL_CONTENT_LEN;

	जबतक (1) अणु
		अगर (startAddr >= efuse_max_available_len) अणु
			ret = false;
			अवरोध;
		पूर्ण

		अगर (efuse_OneByteRead(pAdapter, startAddr, &efuse_data) && (efuse_data != 0xFF)) अणु
			अगर (EXT_HEADER(efuse_data)) अणु
				cur_header = efuse_data;
				startAddr++;
				efuse_OneByteRead(pAdapter, startAddr, &efuse_data);
				अगर (ALL_WORDS_DISABLED(efuse_data)) अणु
					ret = false;
					अवरोध;
				पूर्ण
				curPkt.offset = ((cur_header & 0xE0) >> 5) | ((efuse_data & 0xF0) >> 1);
				curPkt.word_en = efuse_data & 0x0F;
			पूर्ण अन्यथा अणु
				cur_header  =  efuse_data;
				curPkt.offset = (cur_header >> 4) & 0x0F;
				curPkt.word_en = cur_header & 0x0F;
			पूर्ण

			curPkt.word_cnts = Efuse_CalculateWordCnts(curPkt.word_en);
			/*  अगर same header is found but no data followed */
			/*  ग_लिखो some part of data followed by the header. */
			अगर ((curPkt.offset == pTargetPkt->offset) &&
			    (!hal_EfuseCheckIfDatafollowed(pAdapter, curPkt.word_cnts, startAddr + 1)) &&
			    wordEnMatched(pTargetPkt, &curPkt, &matched_wden)) अणु
				/*  Here to ग_लिखो partial data */
				badworden = Efuse_WordEnableDataWrite(pAdapter, startAddr + 1, matched_wden, pTargetPkt->data);
				अगर (badworden != 0x0F) अणु
					u32	PgWriteSuccess = 0;
					/*  अगर ग_लिखो fail on some words, ग_लिखो these bad words again */

					PgWriteSuccess = Efuse_PgPacketWrite(pAdapter, pTargetPkt->offset, badworden, pTargetPkt->data);

					अगर (!PgWriteSuccess) अणु
						ret = false;	/*  ग_लिखो fail, वापस */
						अवरोध;
					पूर्ण
				पूर्ण
				/*  partial ग_लिखो ok, update the target packet क्रम later use */
				क्रम (i = 0; i < 4; i++) अणु
					अगर ((matched_wden & (0x1 << i)) == 0)	/*  this word has been written */
						pTargetPkt->word_en |= (0x1 << i);	/*  disable the word */
				पूर्ण
				pTargetPkt->word_cnts = Efuse_CalculateWordCnts(pTargetPkt->word_en);
			पूर्ण
			/*  पढ़ो from next header */
			startAddr = startAddr + (curPkt.word_cnts * 2) + 1;
		पूर्ण अन्यथा अणु
			/*  not used header, 0xff */
			*pAddr = startAddr;
			ret = true;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम hal_EfuseConकाष्ठाPGPkt(u8 offset, u8 word_en, u8 *pData, काष्ठा pgpkt *pTargetPkt)
अणु
	स_रखो((व्योम *)pTargetPkt->data, 0xFF, माप(u8) * 8);
	pTargetPkt->offset = offset;
	pTargetPkt->word_en = word_en;
	efuse_WordEnableDataRead(word_en, pData, pTargetPkt->data);
	pTargetPkt->word_cnts = Efuse_CalculateWordCnts(pTargetPkt->word_en);
पूर्ण

bool Efuse_PgPacketWrite(काष्ठा adapter *pAdapter, u8 offset, u8 word_en, u8 *pData)
अणु
	काष्ठा pgpkt	targetPkt;
	u16			startAddr = 0;
	u8 efuseType = EFUSE_WIFI;

	अगर (Efuse_GetCurrentSize(pAdapter) >= EFUSE_MAP_LEN_88E)
		वापस false;

	hal_EfuseConकाष्ठाPGPkt(offset, word_en, pData, &targetPkt);

	अगर (!hal_EfusePartialWriteCheck(pAdapter, efuseType, &startAddr, &targetPkt))
		वापस false;

	अगर (!hal_EfusePgPacketWriteHeader(pAdapter, efuseType, &startAddr, &targetPkt))
		वापस false;

	अगर (!hal_EfusePgPacketWriteData(pAdapter, efuseType, &startAddr, &targetPkt))
		वापस false;

	वापस true;
पूर्ण

u8 Efuse_CalculateWordCnts(u8 word_en)
अणु
	u8 word_cnts = 0;

	अगर (!(word_en & BIT(0)))
		word_cnts++; /*  0 : ग_लिखो enable */
	अगर (!(word_en & BIT(1)))
		word_cnts++;
	अगर (!(word_en & BIT(2)))
		word_cnts++;
	अगर (!(word_en & BIT(3)))
		word_cnts++;
	वापस word_cnts;
पूर्ण

u8 efuse_OneByteRead(काष्ठा adapter *pAdapter, u16 addr, u8 *data)
अणु
	u8 पंचांगpidx = 0;
	u8 result;

	usb_ग_लिखो8(pAdapter, EFUSE_CTRL + 1, (u8)(addr & 0xff));
	usb_ग_लिखो8(pAdapter, EFUSE_CTRL + 2, ((u8)((addr >> 8) & 0x03)) |
		   (usb_पढ़ो8(pAdapter, EFUSE_CTRL + 2) & 0xFC));

	usb_ग_लिखो8(pAdapter, EFUSE_CTRL + 3,  0x72);/* पढ़ो cmd */

	जबतक (!(0x80 & usb_पढ़ो8(pAdapter, EFUSE_CTRL + 3)) && (पंचांगpidx < 100))
		पंचांगpidx++;
	अगर (पंचांगpidx < 100) अणु
		*data = usb_पढ़ो8(pAdapter, EFUSE_CTRL);
		result = true;
	पूर्ण अन्यथा अणु
		*data = 0xff;
		result = false;
	पूर्ण
	वापस result;
पूर्ण

u8 efuse_OneByteWrite(काष्ठा adapter *pAdapter, u16 addr, u8 data)
अणु
	u8 पंचांगpidx = 0;
	u8 result;

	usb_ग_लिखो8(pAdapter, EFUSE_CTRL + 1, (u8)(addr & 0xff));
	usb_ग_लिखो8(pAdapter, EFUSE_CTRL + 2,
		   (usb_पढ़ो8(pAdapter, EFUSE_CTRL + 2) & 0xFC) |
		   (u8)((addr >> 8) & 0x03));
	usb_ग_लिखो8(pAdapter, EFUSE_CTRL, data);/* data */

	usb_ग_लिखो8(pAdapter, EFUSE_CTRL + 3, 0xF2);/* ग_लिखो cmd */

	जबतक ((0x80 &  usb_पढ़ो8(pAdapter, EFUSE_CTRL + 3)) && (पंचांगpidx < 100))
		पंचांगpidx++;

	अगर (पंचांगpidx < 100)
		result = true;
	अन्यथा
		result = false;

	वापस result;
पूर्ण

/* Read allowed word in current efuse section data. */
व्योम efuse_WordEnableDataRead(u8 word_en, u8 *sourdata, u8 *targetdata)
अणु
	अगर (!(word_en & BIT(0))) अणु
		targetdata[0] = sourdata[0];
		targetdata[1] = sourdata[1];
	पूर्ण
	अगर (!(word_en & BIT(1))) अणु
		targetdata[2] = sourdata[2];
		targetdata[3] = sourdata[3];
	पूर्ण
	अगर (!(word_en & BIT(2))) अणु
		targetdata[4] = sourdata[4];
		targetdata[5] = sourdata[5];
	पूर्ण
	अगर (!(word_en & BIT(3))) अणु
		targetdata[6] = sourdata[6];
		targetdata[7] = sourdata[7];
	पूर्ण
पूर्ण

/* Read All Efuse content */
अटल व्योम Efuse_ReadAllMap(काष्ठा adapter *pAdapter, u8 efuseType, u8 *Efuse)
अणु
	efuse_घातer_चयन(pAdapter, false, true);

	efuse_ReadEFuse(pAdapter, efuseType, 0, EFUSE_MAP_LEN_88E, Efuse);

	efuse_घातer_चयन(pAdapter, false, false);
पूर्ण

/* Transfer current EFUSE content to shaकरोw init and modअगरy map. */
व्योम EFUSE_ShaकरोwMapUpdate(काष्ठा adapter *pAdapter, u8 efuseType)
अणु
	काष्ठा eeprom_priv *pEEPROM = GET_EEPROM_EFUSE_PRIV(pAdapter);

	अगर (pEEPROM->bस्वतःload_fail_flag)
		स_रखो(pEEPROM->efuse_eeprom_data, 0xFF, EFUSE_MAP_LEN_88E);
	अन्यथा
		Efuse_ReadAllMap(pAdapter, efuseType, pEEPROM->efuse_eeprom_data);
पूर्ण
