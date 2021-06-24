<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Linux driver क्रम digital TV devices equipped with B2C2 FlexcopII(b)/III
 * flexcop-sram.c - functions क्रम controlling the SRAM
 * see flexcop.c क्रम copyright inक्रमmation
 */
#समावेश "flexcop.h"

अटल व्योम flexcop_sram_set_chip(काष्ठा flexcop_device *fc,
		flexcop_sram_type_t type)
अणु
	flexcop_set_ibi_value(wan_ctrl_reg_71c, sram_chip, type);
पूर्ण

पूर्णांक flexcop_sram_init(काष्ठा flexcop_device *fc)
अणु
	चयन (fc->rev) अणु
	हाल FLEXCOP_II:
	हाल FLEXCOP_IIB:
		flexcop_sram_set_chip(fc, FC_SRAM_1_32KB);
		अवरोध;
	हाल FLEXCOP_III:
		flexcop_sram_set_chip(fc, FC_SRAM_1_48KB);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक flexcop_sram_set_dest(काष्ठा flexcop_device *fc, flexcop_sram_dest_t dest,
		 flexcop_sram_dest_target_t target)
अणु
	flexcop_ibi_value v;
	v = fc->पढ़ो_ibi_reg(fc, sram_dest_reg_714);

	अगर (fc->rev != FLEXCOP_III && target == FC_SRAM_DEST_TARGET_FC3_CA) अणु
		err("SRAM destination target to available on FlexCopII(b)\n");
		वापस -EINVAL;
	पूर्ण
	deb_sram("sram dest: %x target: %x\n", dest, target);

	अगर (dest & FC_SRAM_DEST_NET)
		v.sram_dest_reg_714.NET_Dest = target;
	अगर (dest & FC_SRAM_DEST_CAI)
		v.sram_dest_reg_714.CAI_Dest = target;
	अगर (dest & FC_SRAM_DEST_CAO)
		v.sram_dest_reg_714.CAO_Dest = target;
	अगर (dest & FC_SRAM_DEST_MEDIA)
		v.sram_dest_reg_714.MEDIA_Dest = target;

	fc->ग_लिखो_ibi_reg(fc,sram_dest_reg_714,v);
	udelay(1000); /* TODO delay really necessary */

	वापस 0;
पूर्ण
EXPORT_SYMBOL(flexcop_sram_set_dest);

व्योम flexcop_wan_set_speed(काष्ठा flexcop_device *fc, flexcop_wan_speed_t s)
अणु
	flexcop_set_ibi_value(wan_ctrl_reg_71c,wan_speed_sig,s);
पूर्ण
EXPORT_SYMBOL(flexcop_wan_set_speed);

व्योम flexcop_sram_ctrl(काष्ठा flexcop_device *fc, पूर्णांक usb_wan, पूर्णांक sramdma, पूर्णांक maximumfill)
अणु
	flexcop_ibi_value v = fc->पढ़ो_ibi_reg(fc,sram_dest_reg_714);
	v.sram_dest_reg_714.ctrl_usb_wan = usb_wan;
	v.sram_dest_reg_714.ctrl_sramdma = sramdma;
	v.sram_dest_reg_714.ctrl_maximumfill = maximumfill;
	fc->ग_लिखो_ibi_reg(fc,sram_dest_reg_714,v);
पूर्ण
EXPORT_SYMBOL(flexcop_sram_ctrl);

#अगर 0
अटल व्योम flexcop_sram_ग_लिखो(काष्ठा adapter *adapter, u32 bank, u32 addr, u8 *buf, u32 len)
अणु
	पूर्णांक i, retries;
	u32 command;

	क्रम (i = 0; i < len; i++) अणु
		command = bank | addr | 0x04000000 | (*buf << 0x10);

		retries = 2;

		जबतक (((पढ़ो_reg_dw(adapter, 0x700) & 0x80000000) != 0) && (retries > 0)) अणु
			mdelay(1);
			retries--;
		पूर्ण

		अगर (retries == 0)
			prपूर्णांकk("%s: SRAM timeout\n", __func__);

		ग_लिखो_reg_dw(adapter, 0x700, command);

		buf++;
		addr++;
	पूर्ण
पूर्ण

अटल व्योम flex_sram_पढ़ो(काष्ठा adapter *adapter, u32 bank, u32 addr, u8 *buf, u32 len)
अणु
	पूर्णांक i, retries;
	u32 command, value;

	क्रम (i = 0; i < len; i++) अणु
		command = bank | addr | 0x04008000;

		retries = 10000;

		जबतक (((पढ़ो_reg_dw(adapter, 0x700) & 0x80000000) != 0) && (retries > 0)) अणु
			mdelay(1);
			retries--;
		पूर्ण

		अगर (retries == 0)
			prपूर्णांकk("%s: SRAM timeout\n", __func__);

		ग_लिखो_reg_dw(adapter, 0x700, command);

		retries = 10000;

		जबतक (((पढ़ो_reg_dw(adapter, 0x700) & 0x80000000) != 0) && (retries > 0)) अणु
			mdelay(1);
			retries--;
		पूर्ण

		अगर (retries == 0)
			prपूर्णांकk("%s: SRAM timeout\n", __func__);

		value = पढ़ो_reg_dw(adapter, 0x700) >> 0x10;

		*buf = (value & 0xff);

		addr++;
		buf++;
	पूर्ण
पूर्ण

अटल व्योम sram_ग_लिखो_chunk(काष्ठा adapter *adapter, u32 addr, u8 *buf, u16 len)
अणु
	u32 bank;

	bank = 0;

	अगर (adapter->dw_sram_type == 0x20000) अणु
		bank = (addr & 0x18000) << 0x0d;
	पूर्ण

	अगर (adapter->dw_sram_type == 0x00000) अणु
		अगर ((addr >> 0x0f) == 0)
			bank = 0x20000000;
		अन्यथा
			bank = 0x10000000;
	पूर्ण
	flex_sram_ग_लिखो(adapter, bank, addr & 0x7fff, buf, len);
पूर्ण

अटल व्योम sram_पढ़ो_chunk(काष्ठा adapter *adapter, u32 addr, u8 *buf, u16 len)
अणु
	u32 bank;
	bank = 0;

	अगर (adapter->dw_sram_type == 0x20000) अणु
		bank = (addr & 0x18000) << 0x0d;
	पूर्ण

	अगर (adapter->dw_sram_type == 0x00000) अणु
		अगर ((addr >> 0x0f) == 0)
			bank = 0x20000000;
		अन्यथा
			bank = 0x10000000;
	पूर्ण
	flex_sram_पढ़ो(adapter, bank, addr & 0x7fff, buf, len);
पूर्ण

अटल व्योम sram_पढ़ो(काष्ठा adapter *adapter, u32 addr, u8 *buf, u32 len)
अणु
	u32 length;
	जबतक (len != 0) अणु
		length = len;
		/* check अगर the address range beदीर्घs to the same
		 * 32K memory chip. If not, the data is पढ़ो
		 * from one chip at a समय */
		अगर ((addr >> 0x0f) != ((addr + len - 1) >> 0x0f)) अणु
			length = (((addr >> 0x0f) + 1) << 0x0f) - addr;
		पूर्ण

		sram_पढ़ो_chunk(adapter, addr, buf, length);
		addr = addr + length;
		buf = buf + length;
		len = len - length;
	पूर्ण
पूर्ण

अटल व्योम sram_ग_लिखो(काष्ठा adapter *adapter, u32 addr, u8 *buf, u32 len)
अणु
	u32 length;
	जबतक (len != 0) अणु
		length = len;

		/* check अगर the address range beदीर्घs to the same
		 * 32K memory chip. If not, the data is
		 * written to one chip at a समय */
		अगर ((addr >> 0x0f) != ((addr + len - 1) >> 0x0f)) अणु
			length = (((addr >> 0x0f) + 1) << 0x0f) - addr;
		पूर्ण

		sram_ग_लिखो_chunk(adapter, addr, buf, length);
		addr = addr + length;
		buf = buf + length;
		len = len - length;
	पूर्ण
पूर्ण

अटल व्योम sram_set_size(काष्ठा adapter *adapter, u32 mask)
अणु
	ग_लिखो_reg_dw(adapter, 0x71c,
			(mask | (~0x30000 & पढ़ो_reg_dw(adapter, 0x71c))));
पूर्ण

अटल व्योम sram_init(काष्ठा adapter *adapter)
अणु
	u32 पंचांगp;
	पंचांगp = पढ़ो_reg_dw(adapter, 0x71c);
	ग_लिखो_reg_dw(adapter, 0x71c, 1);

	अगर (पढ़ो_reg_dw(adapter, 0x71c) != 0) अणु
		ग_लिखो_reg_dw(adapter, 0x71c, पंचांगp);
		adapter->dw_sram_type = पंचांगp & 0x30000;
		ddprपूर्णांकk("%s: dw_sram_type = %x\n", __func__, adapter->dw_sram_type);
	पूर्ण अन्यथा अणु
		adapter->dw_sram_type = 0x10000;
		ddprपूर्णांकk("%s: dw_sram_type = %x\n", __func__, adapter->dw_sram_type);
	पूर्ण
पूर्ण

अटल पूर्णांक sram_test_location(काष्ठा adapter *adapter, u32 mask, u32 addr)
अणु
	u8 पंचांगp1, पंचांगp2;
	dprपूर्णांकk("%s: mask = %x, addr = %x\n", __func__, mask, addr);

	sram_set_size(adapter, mask);
	sram_init(adapter);

	पंचांगp2 = 0xa5;
	पंचांगp1 = 0x4f;

	sram_ग_लिखो(adapter, addr, &पंचांगp2, 1);
	sram_ग_लिखो(adapter, addr + 4, &पंचांगp1, 1);

	पंचांगp2 = 0;
	mdelay(20);

	sram_पढ़ो(adapter, addr, &पंचांगp2, 1);
	sram_पढ़ो(adapter, addr, &पंचांगp2, 1);

	dprपूर्णांकk("%s: wrote 0xa5, read 0x%2x\n", __func__, पंचांगp2);

	अगर (पंचांगp2 != 0xa5)
		वापस 0;

	पंचांगp2 = 0x5a;
	पंचांगp1 = 0xf4;

	sram_ग_लिखो(adapter, addr, &पंचांगp2, 1);
	sram_ग_लिखो(adapter, addr + 4, &पंचांगp1, 1);

	पंचांगp2 = 0;
	mdelay(20);

	sram_पढ़ो(adapter, addr, &पंचांगp2, 1);
	sram_पढ़ो(adapter, addr, &पंचांगp2, 1);

	dprपूर्णांकk("%s: wrote 0x5a, read 0x%2x\n", __func__, पंचांगp2);

	अगर (पंचांगp2 != 0x5a)
		वापस 0;
	वापस 1;
पूर्ण

अटल u32 sram_length(काष्ठा adapter *adapter)
अणु
	अगर (adapter->dw_sram_type == 0x10000)
		वापस 32768; /* 32K */
	अगर (adapter->dw_sram_type == 0x00000)
		वापस 65536; /* 64K */
	अगर (adapter->dw_sram_type == 0x20000)
		वापस 131072; /* 128K */
	वापस 32768; /* 32K */
पूर्ण

/* FlexcopII can work with 32K, 64K or 128K of बाह्यal SRAM memory.
   - क्रम 128K there are 4x32K chips at bank 0,1,2,3.
   - क्रम  64K there are 2x32K chips at bank 1,2.
   - क्रम  32K there is one 32K chip at bank 0.

   FlexCop works only with one bank at a समय. The bank is selected
   by bits 28-29 of the 0x700 रेजिस्टर.

   bank 0 covers addresses 0x00000-0x07fff
   bank 1 covers addresses 0x08000-0x0ffff
   bank 2 covers addresses 0x10000-0x17fff
   bank 3 covers addresses 0x18000-0x1ffff */

अटल पूर्णांक flexcop_sram_detect(काष्ठा flexcop_device *fc)
अणु
	flexcop_ibi_value r208, r71c_0, vr71c_1;
	r208 = fc->पढ़ो_ibi_reg(fc, ctrl_208);
	fc->ग_लिखो_ibi_reg(fc, ctrl_208, ibi_zero);

	r71c_0 = fc->पढ़ो_ibi_reg(fc, wan_ctrl_reg_71c);
	ग_लिखो_reg_dw(adapter, 0x71c, 1);
	पंचांगp3 = पढ़ो_reg_dw(adapter, 0x71c);
	dprपूर्णांकk("%s: tmp3 = %x\n", __func__, पंचांगp3);
	ग_लिखो_reg_dw(adapter, 0x71c, पंचांगp2);

	// check क्रम पूर्णांकernal SRAM ???
	पंचांगp3--;
	अगर (पंचांगp3 != 0) अणु
		sram_set_size(adapter, 0x10000);
		sram_init(adapter);
		ग_लिखो_reg_dw(adapter, 0x208, पंचांगp);
		dprपूर्णांकk("%s: sram size = 32K\n", __func__);
		वापस 32;
	पूर्ण

	अगर (sram_test_location(adapter, 0x20000, 0x18000) != 0) अणु
		sram_set_size(adapter, 0x20000);
		sram_init(adapter);
		ग_लिखो_reg_dw(adapter, 0x208, पंचांगp);
		dprपूर्णांकk("%s: sram size = 128K\n", __func__);
		वापस 128;
	पूर्ण

	अगर (sram_test_location(adapter, 0x00000, 0x10000) != 0) अणु
		sram_set_size(adapter, 0x00000);
		sram_init(adapter);
		ग_लिखो_reg_dw(adapter, 0x208, पंचांगp);
		dprपूर्णांकk("%s: sram size = 64K\n", __func__);
		वापस 64;
	पूर्ण

	अगर (sram_test_location(adapter, 0x10000, 0x00000) != 0) अणु
		sram_set_size(adapter, 0x10000);
		sram_init(adapter);
		ग_लिखो_reg_dw(adapter, 0x208, पंचांगp);
		dprपूर्णांकk("%s: sram size = 32K\n", __func__);
		वापस 32;
	पूर्ण

	sram_set_size(adapter, 0x10000);
	sram_init(adapter);
	ग_लिखो_reg_dw(adapter, 0x208, पंचांगp);
	dprपूर्णांकk("%s: SRAM detection failed. Set to 32K \n", __func__);
	वापस 0;
पूर्ण

अटल व्योम sll_detect_sram_size(काष्ठा adapter *adapter)
अणु
	sram_detect_क्रम_flex2(adapter);
पूर्ण

#पूर्ण_अगर
