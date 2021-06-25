<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * (C) 2003 Red Hat, Inc.
 * (C) 2004 Dan Brown <dan_brown@ieee.org>
 * (C) 2004 Kalev Lember <kalev@smartlink.ee>
 *
 * Author: David Woodhouse <dwmw2@infradead.org>
 * Additional Diskonchip 2000 and Millennium support by Dan Brown <dan_brown@ieee.org>
 * Diskonchip Millennium Plus support by Kalev Lember <kalev@smartlink.ee>
 *
 * Error correction code lअगरted from the old करोcecc code
 * Author: Fabrice Bellard (fabrice.bellard@netgem.com)
 * Copyright (C) 2000 Netgem S.A.
 * converted to the generic Reed-Solomon library by Thomas Gleixner <tglx@linutronix.de>
 *
 * Interface to generic न_अंकD code क्रम M-Systems DiskOnChip devices
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/rslib.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/करोc2000.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/inftl.h>
#समावेश <linux/module.h>

/* Where to look क्रम the devices? */
#अगर_अघोषित CONFIG_MTD_न_अंकD_DISKONCHIP_PROBE_ADDRESS
#घोषणा CONFIG_MTD_न_अंकD_DISKONCHIP_PROBE_ADDRESS 0
#पूर्ण_अगर

अटल अचिन्हित दीर्घ करोc_locations[] __initdata = अणु
#अगर defined (__alpha__) || defined(__i386__) || defined(__x86_64__)
#अगर_घोषित CONFIG_MTD_न_अंकD_DISKONCHIP_PROBE_HIGH
	0xfffc8000, 0xfffca000, 0xfffcc000, 0xfffce000,
	0xfffd0000, 0xfffd2000, 0xfffd4000, 0xfffd6000,
	0xfffd8000, 0xfffda000, 0xfffdc000, 0xfffde000,
	0xfffe0000, 0xfffe2000, 0xfffe4000, 0xfffe6000,
	0xfffe8000, 0xfffea000, 0xfffec000, 0xfffee000,
#अन्यथा
	0xc8000, 0xca000, 0xcc000, 0xce000,
	0xd0000, 0xd2000, 0xd4000, 0xd6000,
	0xd8000, 0xda000, 0xdc000, 0xde000,
	0xe0000, 0xe2000, 0xe4000, 0xe6000,
	0xe8000, 0xea000, 0xec000, 0xee000,
#पूर्ण_अगर
#पूर्ण_अगर
	0xffffffff पूर्ण;

अटल काष्ठा mtd_info *करोclist = शून्य;

काष्ठा करोc_priv अणु
	काष्ठा nand_controller base;
	व्योम __iomem *virtadr;
	अचिन्हित दीर्घ physadr;
	u_अक्षर ChipID;
	u_अक्षर CDSNControl;
	पूर्णांक chips_per_न्यूनमान;	/* The number of chips detected on each न्यूनमान */
	पूर्णांक curन्यूनमान;
	पूर्णांक curchip;
	पूर्णांक mh0_page;
	पूर्णांक mh1_page;
	काष्ठा rs_control *rs_decoder;
	काष्ठा mtd_info *nextकरोc;
	bool supports_32b_पढ़ोs;

	/* Handle the last stage of initialization (BBT scan, partitioning) */
	पूर्णांक (*late_init)(काष्ठा mtd_info *mtd);
पूर्ण;

/* This is the ecc value computed by the HW ecc generator upon writing an empty
   page, one with all 0xff क्रम data. */
अटल u_अक्षर empty_ग_लिखो_ecc[6] = अणु 0x4b, 0x00, 0xe2, 0x0e, 0x93, 0xf7 पूर्ण;

#घोषणा INFTL_BBT_RESERVED_BLOCKS 4

#घोषणा DoC_is_MillenniumPlus(करोc) ((करोc)->ChipID == DOC_ChipID_DocMilPlus16 || (करोc)->ChipID == DOC_ChipID_DocMilPlus32)
#घोषणा DoC_is_Millennium(करोc) ((करोc)->ChipID == DOC_ChipID_DocMil)
#घोषणा DoC_is_2000(करोc) ((करोc)->ChipID == DOC_ChipID_Doc2k)

अटल पूर्णांक debug = 0;
module_param(debug, पूर्णांक, 0);

अटल पूर्णांक try_dword = 1;
module_param(try_dword, पूर्णांक, 0);

अटल पूर्णांक no_ecc_failures = 0;
module_param(no_ecc_failures, पूर्णांक, 0);

अटल पूर्णांक no_स्वतःpart = 0;
module_param(no_स्वतःpart, पूर्णांक, 0);

अटल पूर्णांक show_firmware_partition = 0;
module_param(show_firmware_partition, पूर्णांक, 0);

#अगर_घोषित CONFIG_MTD_न_अंकD_DISKONCHIP_BBTWRITE
अटल पूर्णांक inftl_bbt_ग_लिखो = 1;
#अन्यथा
अटल पूर्णांक inftl_bbt_ग_लिखो = 0;
#पूर्ण_अगर
module_param(inftl_bbt_ग_लिखो, पूर्णांक, 0);

अटल अचिन्हित दीर्घ करोc_config_location = CONFIG_MTD_न_अंकD_DISKONCHIP_PROBE_ADDRESS;
module_param(करोc_config_location, uदीर्घ, 0);
MODULE_PARM_DESC(करोc_config_location, "Physical memory address at which to probe for DiskOnChip");

/* Sector size क्रम HW ECC */
#घोषणा SECTOR_SIZE 512
/* The sector bytes are packed पूर्णांकo NB_DATA 10 bit words */
#घोषणा NB_DATA (((SECTOR_SIZE + 1) * 8 + 6) / 10)
/* Number of roots */
#घोषणा NROOTS 4
/* First consective root */
#घोषणा FCR 510
/* Number of symbols */
#घोषणा NN 1023

/*
 * The HW decoder in the DoC ASIC's provides us a error syndrome,
 * which we must convert to a standard syndrome usable by the generic
 * Reed-Solomon library code.
 *
 * Fabrice Bellard figured this out in the old करोcecc code. I added
 * some comments, improved a minor bit and converted it to make use
 * of the generic Reed-Solomon library. tglx
 */
अटल पूर्णांक करोc_ecc_decode(काष्ठा rs_control *rs, uपूर्णांक8_t *data, uपूर्णांक8_t *ecc)
अणु
	पूर्णांक i, j, nerr, errpos[8];
	uपूर्णांक8_t parity;
	uपूर्णांक16_t ds[4], s[5], पंचांगp, errval[8], syn[4];
	काष्ठा rs_codec *cd = rs->codec;

	स_रखो(syn, 0, माप(syn));
	/* Convert the ecc bytes पूर्णांकo words */
	ds[0] = ((ecc[4] & 0xff) >> 0) | ((ecc[5] & 0x03) << 8);
	ds[1] = ((ecc[5] & 0xfc) >> 2) | ((ecc[2] & 0x0f) << 6);
	ds[2] = ((ecc[2] & 0xf0) >> 4) | ((ecc[3] & 0x3f) << 4);
	ds[3] = ((ecc[3] & 0xc0) >> 6) | ((ecc[0] & 0xff) << 2);
	parity = ecc[1];

	/* Initialize the syndrome buffer */
	क्रम (i = 0; i < NROOTS; i++)
		s[i] = ds[0];
	/*
	 *  Evaluate
	 *  s[i] = ds[3]x^3 + ds[2]x^2 + ds[1]x^1 + ds[0]
	 *  where x = alpha^(FCR + i)
	 */
	क्रम (j = 1; j < NROOTS; j++) अणु
		अगर (ds[j] == 0)
			जारी;
		पंचांगp = cd->index_of[ds[j]];
		क्रम (i = 0; i < NROOTS; i++)
			s[i] ^= cd->alpha_to[rs_modnn(cd, पंचांगp + (FCR + i) * j)];
	पूर्ण

	/* Calc syn[i] = s[i] / alpha^(v + i) */
	क्रम (i = 0; i < NROOTS; i++) अणु
		अगर (s[i])
			syn[i] = rs_modnn(cd, cd->index_of[s[i]] + (NN - FCR - i));
	पूर्ण
	/* Call the decoder library */
	nerr = decode_rs16(rs, शून्य, शून्य, 1019, syn, 0, errpos, 0, errval);

	/* Incorrectable errors ? */
	अगर (nerr < 0)
		वापस nerr;

	/*
	 * Correct the errors. The bitpositions are a bit of magic,
	 * but they are given by the design of the de/encoder circuit
	 * in the DoC ASIC's.
	 */
	क्रम (i = 0; i < nerr; i++) अणु
		पूर्णांक index, bitpos, pos = 1015 - errpos[i];
		uपूर्णांक8_t val;
		अगर (pos >= NB_DATA && pos < 1019)
			जारी;
		अगर (pos < NB_DATA) अणु
			/* extract bit position (MSB first) */
			pos = 10 * (NB_DATA - 1 - pos) - 6;
			/* now correct the following 10 bits. At most two bytes
			   can be modअगरied since pos is even */
			index = (pos >> 3) ^ 1;
			bitpos = pos & 7;
			अगर ((index >= 0 && index < SECTOR_SIZE) || index == (SECTOR_SIZE + 1)) अणु
				val = (uपूर्णांक8_t) (errval[i] >> (2 + bitpos));
				parity ^= val;
				अगर (index < SECTOR_SIZE)
					data[index] ^= val;
			पूर्ण
			index = ((pos >> 3) + 1) ^ 1;
			bitpos = (bitpos + 10) & 7;
			अगर (bitpos == 0)
				bitpos = 8;
			अगर ((index >= 0 && index < SECTOR_SIZE) || index == (SECTOR_SIZE + 1)) अणु
				val = (uपूर्णांक8_t) (errval[i] << (8 - bitpos));
				parity ^= val;
				अगर (index < SECTOR_SIZE)
					data[index] ^= val;
			पूर्ण
		पूर्ण
	पूर्ण
	/* If the parity is wrong, no rescue possible */
	वापस parity ? -EBADMSG : nerr;
पूर्ण

अटल व्योम DoC_Delay(काष्ठा करोc_priv *करोc, अचिन्हित लघु cycles)
अणु
	अस्थिर अक्षर __always_unused dummy;
	पूर्णांक i;

	क्रम (i = 0; i < cycles; i++) अणु
		अगर (DoC_is_Millennium(करोc))
			dummy = ReadDOC(करोc->virtadr, NOP);
		अन्यथा अगर (DoC_is_MillenniumPlus(करोc))
			dummy = ReadDOC(करोc->virtadr, Mplus_NOP);
		अन्यथा
			dummy = ReadDOC(करोc->virtadr, DOCStatus);
	पूर्ण

पूर्ण

#घोषणा CDSN_CTRL_FR_B_MASK	(CDSN_CTRL_FR_B0 | CDSN_CTRL_FR_B1)

/* DOC_WaitReady: Wait क्रम RDY line to be निश्चितed by the flash chip */
अटल पूर्णांक _DoC_WaitReady(काष्ठा करोc_priv *करोc)
अणु
	व्योम __iomem *करोcptr = करोc->virtadr;
	अचिन्हित दीर्घ समयo = jअगरfies + (HZ * 10);

	अगर (debug)
		prपूर्णांकk("_DoC_WaitReady...\n");
	/* Out-of-line routine to रुको क्रम chip response */
	अगर (DoC_is_MillenniumPlus(करोc)) अणु
		जबतक ((ReadDOC(करोcptr, Mplus_FlashControl) & CDSN_CTRL_FR_B_MASK) != CDSN_CTRL_FR_B_MASK) अणु
			अगर (समय_after(jअगरfies, समयo)) अणु
				prपूर्णांकk("_DoC_WaitReady timed out.\n");
				वापस -EIO;
			पूर्ण
			udelay(1);
			cond_resched();
		पूर्ण
	पूर्ण अन्यथा अणु
		जबतक (!(ReadDOC(करोcptr, CDSNControl) & CDSN_CTRL_FR_B)) अणु
			अगर (समय_after(jअगरfies, समयo)) अणु
				prपूर्णांकk("_DoC_WaitReady timed out.\n");
				वापस -EIO;
			पूर्ण
			udelay(1);
			cond_resched();
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक DoC_WaitReady(काष्ठा करोc_priv *करोc)
अणु
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक ret = 0;

	अगर (DoC_is_MillenniumPlus(करोc)) अणु
		DoC_Delay(करोc, 4);

		अगर ((ReadDOC(करोcptr, Mplus_FlashControl) & CDSN_CTRL_FR_B_MASK) != CDSN_CTRL_FR_B_MASK)
			/* Call the out-of-line routine to रुको */
			ret = _DoC_WaitReady(करोc);
	पूर्ण अन्यथा अणु
		DoC_Delay(करोc, 4);

		अगर (!(ReadDOC(करोcptr, CDSNControl) & CDSN_CTRL_FR_B))
			/* Call the out-of-line routine to रुको */
			ret = _DoC_WaitReady(करोc);
		DoC_Delay(करोc, 2);
	पूर्ण

	अगर (debug)
		prपूर्णांकk("DoC_WaitReady OK\n");
	वापस ret;
पूर्ण

अटल व्योम करोc2000_ग_लिखो_byte(काष्ठा nand_chip *this, u_अक्षर datum)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;

	अगर (debug)
		prपूर्णांकk("write_byte %02x\n", datum);
	WriteDOC(datum, करोcptr, CDSNSlowIO);
	WriteDOC(datum, करोcptr, 2k_CDSN_IO);
पूर्ण

अटल व्योम करोc2000_ग_लिखोbuf(काष्ठा nand_chip *this, स्थिर u_अक्षर *buf,
			     पूर्णांक len)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक i;
	अगर (debug)
		prपूर्णांकk("writebuf of %d bytes: ", len);
	क्रम (i = 0; i < len; i++) अणु
		WriteDOC_(buf[i], करोcptr, DoC_2k_CDSN_IO + i);
		अगर (debug && i < 16)
			prपूर्णांकk("%02x ", buf[i]);
	पूर्ण
	अगर (debug)
		prपूर्णांकk("\n");
पूर्ण

अटल व्योम करोc2000_पढ़ोbuf(काष्ठा nand_chip *this, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	u32 *buf32 = (u32 *)buf;
	पूर्णांक i;

	अगर (debug)
		prपूर्णांकk("readbuf of %d bytes: ", len);

	अगर (!करोc->supports_32b_पढ़ोs ||
	    ((((अचिन्हित दीर्घ)buf) | len) & 3)) अणु
		क्रम (i = 0; i < len; i++)
			buf[i] = ReadDOC(करोcptr, 2k_CDSN_IO + i);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < len / 4; i++)
			buf32[i] = पढ़ोl(करोcptr + DoC_2k_CDSN_IO + i);
	पूर्ण
पूर्ण

/*
 * We need our own पढ़ोid() here because it's called beक्रमe the न_अंकD chip
 * has been initialized, and calling nand_op_पढ़ोid() would lead to a शून्य
 * poपूर्णांकer exception when dereferencing the न_अंकD timings.
 */
अटल व्योम करोc200x_पढ़ोid(काष्ठा nand_chip *this, अचिन्हित पूर्णांक cs, u8 *id)
अणु
	u8 addr = 0;
	काष्ठा nand_op_instr instrs[] = अणु
		न_अंकD_OP_CMD(न_अंकD_CMD_READID, 0),
		न_अंकD_OP_ADDR(1, &addr, 50),
		न_अंकD_OP_8BIT_DATA_IN(2, id, 0),
	पूर्ण;

	काष्ठा nand_operation op = न_अंकD_OPERATION(cs, instrs);

	अगर (!id)
		op.ninstrs--;

	this->controller->ops->exec_op(this, &op, false);
पूर्ण

अटल uपूर्णांक16_t __init करोc200x_ident_chip(काष्ठा mtd_info *mtd, पूर्णांक nr)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	uपूर्णांक16_t ret;
	u8 id[2];

	करोc200x_पढ़ोid(this, nr, id);

	ret = ((u16)id[0] << 8) | id[1];

	अगर (करोc->ChipID == DOC_ChipID_Doc2k && try_dword && !nr) अणु
		/* First chip probe. See अगर we get same results by 32-bit access */
		जोड़ अणु
			uपूर्णांक32_t dword;
			uपूर्णांक8_t byte[4];
		पूर्ण ident;
		व्योम __iomem *करोcptr = करोc->virtadr;

		करोc200x_पढ़ोid(this, nr, शून्य);

		ident.dword = पढ़ोl(करोcptr + DoC_2k_CDSN_IO);
		अगर (((ident.byte[0] << 8) | ident.byte[1]) == ret) अणु
			pr_info("DiskOnChip 2000 responds to DWORD access\n");
			करोc->supports_32b_पढ़ोs = true;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम __init करोc2000_count_chips(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	uपूर्णांक16_t mfrid;
	पूर्णांक i;

	/* Max 4 chips per न्यूनमान on DiskOnChip 2000 */
	करोc->chips_per_न्यूनमान = 4;

	/* Find out what the first chip is */
	mfrid = करोc200x_ident_chip(mtd, 0);

	/* Find how many chips in each न्यूनमान. */
	क्रम (i = 1; i < 4; i++) अणु
		अगर (करोc200x_ident_chip(mtd, i) != mfrid)
			अवरोध;
	पूर्ण
	करोc->chips_per_न्यूनमान = i;
	pr_debug("Detected %d chips per floor.\n", i);
पूर्ण

अटल व्योम करोc2001_ग_लिखो_byte(काष्ठा nand_chip *this, u_अक्षर datum)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;

	WriteDOC(datum, करोcptr, CDSNSlowIO);
	WriteDOC(datum, करोcptr, Mil_CDSN_IO);
	WriteDOC(datum, करोcptr, WritePipeTerm);
पूर्ण

अटल व्योम करोc2001_ग_लिखोbuf(काष्ठा nand_chip *this, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		WriteDOC_(buf[i], करोcptr, DoC_Mil_CDSN_IO + i);
	/* Terminate ग_लिखो pipeline */
	WriteDOC(0x00, करोcptr, WritePipeTerm);
पूर्ण

अटल व्योम करोc2001_पढ़ोbuf(काष्ठा nand_chip *this, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक i;

	/* Start पढ़ो pipeline */
	ReadDOC(करोcptr, ReadPipeInit);

	क्रम (i = 0; i < len - 1; i++)
		buf[i] = ReadDOC(करोcptr, Mil_CDSN_IO + (i & 0xff));

	/* Terminate पढ़ो pipeline */
	buf[i] = ReadDOC(करोcptr, LastDataRead);
पूर्ण

अटल व्योम करोc2001plus_ग_लिखोbuf(काष्ठा nand_chip *this, स्थिर u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक i;

	अगर (debug)
		prपूर्णांकk("writebuf of %d bytes: ", len);
	क्रम (i = 0; i < len; i++) अणु
		WriteDOC_(buf[i], करोcptr, DoC_Mil_CDSN_IO + i);
		अगर (debug && i < 16)
			prपूर्णांकk("%02x ", buf[i]);
	पूर्ण
	अगर (debug)
		prपूर्णांकk("\n");
पूर्ण

अटल व्योम करोc2001plus_पढ़ोbuf(काष्ठा nand_chip *this, u_अक्षर *buf, पूर्णांक len)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक i;

	अगर (debug)
		prपूर्णांकk("readbuf of %d bytes: ", len);

	/* Start पढ़ो pipeline */
	ReadDOC(करोcptr, Mplus_ReadPipeInit);
	ReadDOC(करोcptr, Mplus_ReadPipeInit);

	क्रम (i = 0; i < len - 2; i++) अणु
		buf[i] = ReadDOC(करोcptr, Mil_CDSN_IO);
		अगर (debug && i < 16)
			prपूर्णांकk("%02x ", buf[i]);
	पूर्ण

	/* Terminate पढ़ो pipeline */
	अगर (len >= 2) अणु
		buf[len - 2] = ReadDOC(करोcptr, Mplus_LastDataRead);
		अगर (debug && i < 16)
			prपूर्णांकk("%02x ", buf[len - 2]);
	पूर्ण

	buf[len - 1] = ReadDOC(करोcptr, Mplus_LastDataRead);
	अगर (debug && i < 16)
		prपूर्णांकk("%02x ", buf[len - 1]);
	अगर (debug)
		prपूर्णांकk("\n");
पूर्ण

अटल व्योम करोc200x_ग_लिखो_control(काष्ठा करोc_priv *करोc, u8 value)
अणु
	WriteDOC(value, करोc->virtadr, CDSNControl);
	/* 11.4.3 -- 4 NOPs after CSDNControl ग_लिखो */
	DoC_Delay(करोc, 4);
पूर्ण

अटल व्योम करोc200x_exec_instr(काष्ठा nand_chip *this,
			       स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	अचिन्हित पूर्णांक i;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		करोc200x_ग_लिखो_control(करोc, CDSN_CTRL_CE | CDSN_CTRL_CLE);
		करोc2000_ग_लिखो_byte(this, instr->ctx.cmd.opcode);
		अवरोध;

	हाल न_अंकD_OP_ADDR_INSTR:
		करोc200x_ग_लिखो_control(करोc, CDSN_CTRL_CE | CDSN_CTRL_ALE);
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
			u8 addr = instr->ctx.addr.addrs[i];

			अगर (DoC_is_2000(करोc))
				करोc2000_ग_लिखो_byte(this, addr);
			अन्यथा
				करोc2001_ग_लिखो_byte(this, addr);
		पूर्ण
		अवरोध;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		करोc200x_ग_लिखो_control(करोc, CDSN_CTRL_CE);
		अगर (DoC_is_2000(करोc))
			करोc2000_पढ़ोbuf(this, instr->ctx.data.buf.in,
					instr->ctx.data.len);
		अन्यथा
			करोc2001_पढ़ोbuf(this, instr->ctx.data.buf.in,
					instr->ctx.data.len);
		अवरोध;

	हाल न_अंकD_OP_DATA_OUT_INSTR:
		करोc200x_ग_लिखो_control(करोc, CDSN_CTRL_CE);
		अगर (DoC_is_2000(करोc))
			करोc2000_ग_लिखोbuf(this, instr->ctx.data.buf.out,
					 instr->ctx.data.len);
		अन्यथा
			करोc2001_ग_लिखोbuf(this, instr->ctx.data.buf.out,
					 instr->ctx.data.len);
		अवरोध;

	हाल न_अंकD_OP_WAITRDY_INSTR:
		DoC_WaitReady(करोc);
		अवरोध;
	पूर्ण

	अगर (instr->delay_ns)
		ndelay(instr->delay_ns);
पूर्ण

अटल पूर्णांक करोc200x_exec_op(काष्ठा nand_chip *this,
			   स्थिर काष्ठा nand_operation *op,
			   bool check_only)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	अचिन्हित पूर्णांक i;

	अगर (check_only)
		वापस true;

	करोc->curchip = op->cs % करोc->chips_per_न्यूनमान;
	करोc->curन्यूनमान = op->cs / करोc->chips_per_न्यूनमान;

	WriteDOC(करोc->curन्यूनमान, करोc->virtadr, FloorSelect);
	WriteDOC(करोc->curchip, करोc->virtadr, CDSNDeviceSelect);

	/* Assert CE pin */
	करोc200x_ग_लिखो_control(करोc, CDSN_CTRL_CE);

	क्रम (i = 0; i < op->ninstrs; i++)
		करोc200x_exec_instr(this, &op->instrs[i]);

	/* De-निश्चित CE pin */
	करोc200x_ग_लिखो_control(करोc, 0);

	वापस 0;
पूर्ण

अटल व्योम करोc2001plus_ग_लिखो_pipe_term(काष्ठा करोc_priv *करोc)
अणु
	WriteDOC(0x00, करोc->virtadr, Mplus_WritePipeTerm);
	WriteDOC(0x00, करोc->virtadr, Mplus_WritePipeTerm);
पूर्ण

अटल व्योम करोc2001plus_exec_instr(काष्ठा nand_chip *this,
				   स्थिर काष्ठा nand_op_instr *instr)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	अचिन्हित पूर्णांक i;

	चयन (instr->type) अणु
	हाल न_अंकD_OP_CMD_INSTR:
		WriteDOC(instr->ctx.cmd.opcode, करोc->virtadr, Mplus_FlashCmd);
		करोc2001plus_ग_लिखो_pipe_term(करोc);
		अवरोध;

	हाल न_अंकD_OP_ADDR_INSTR:
		क्रम (i = 0; i < instr->ctx.addr.naddrs; i++) अणु
			u8 addr = instr->ctx.addr.addrs[i];

			WriteDOC(addr, करोc->virtadr, Mplus_FlashAddress);
		पूर्ण
		करोc2001plus_ग_लिखो_pipe_term(करोc);
		/* deनिश्चित ALE */
		WriteDOC(0, करोc->virtadr, Mplus_FlashControl);
		अवरोध;

	हाल न_अंकD_OP_DATA_IN_INSTR:
		करोc2001plus_पढ़ोbuf(this, instr->ctx.data.buf.in,
				    instr->ctx.data.len);
		अवरोध;
	हाल न_अंकD_OP_DATA_OUT_INSTR:
		करोc2001plus_ग_लिखोbuf(this, instr->ctx.data.buf.out,
				     instr->ctx.data.len);
		करोc2001plus_ग_लिखो_pipe_term(करोc);
		अवरोध;
	हाल न_अंकD_OP_WAITRDY_INSTR:
		DoC_WaitReady(करोc);
		अवरोध;
	पूर्ण

	अगर (instr->delay_ns)
		ndelay(instr->delay_ns);
पूर्ण

अटल पूर्णांक करोc2001plus_exec_op(काष्ठा nand_chip *this,
			       स्थिर काष्ठा nand_operation *op,
			       bool check_only)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	अचिन्हित पूर्णांक i;

	अगर (check_only)
		वापस true;

	करोc->curchip = op->cs % करोc->chips_per_न्यूनमान;
	करोc->curन्यूनमान = op->cs / करोc->chips_per_न्यूनमान;

	/* Assert ChipEnable and deनिश्चित WriteProtect */
	WriteDOC(DOC_FLASH_CE, करोc->virtadr, Mplus_FlashSelect);

	क्रम (i = 0; i < op->ninstrs; i++)
		करोc2001plus_exec_instr(this, &op->instrs[i]);

	/* De-निश्चित ChipEnable */
	WriteDOC(0, करोc->virtadr, Mplus_FlashSelect);

	वापस 0;
पूर्ण

अटल व्योम करोc200x_enable_hwecc(काष्ठा nand_chip *this, पूर्णांक mode)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;

	/* Prime the ECC engine */
	चयन (mode) अणु
	हाल न_अंकD_ECC_READ:
		WriteDOC(DOC_ECC_RESET, करोcptr, ECCConf);
		WriteDOC(DOC_ECC_EN, करोcptr, ECCConf);
		अवरोध;
	हाल न_अंकD_ECC_WRITE:
		WriteDOC(DOC_ECC_RESET, करोcptr, ECCConf);
		WriteDOC(DOC_ECC_EN | DOC_ECC_RW, करोcptr, ECCConf);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम करोc2001plus_enable_hwecc(काष्ठा nand_chip *this, पूर्णांक mode)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;

	/* Prime the ECC engine */
	चयन (mode) अणु
	हाल न_अंकD_ECC_READ:
		WriteDOC(DOC_ECC_RESET, करोcptr, Mplus_ECCConf);
		WriteDOC(DOC_ECC_EN, करोcptr, Mplus_ECCConf);
		अवरोध;
	हाल न_अंकD_ECC_WRITE:
		WriteDOC(DOC_ECC_RESET, करोcptr, Mplus_ECCConf);
		WriteDOC(DOC_ECC_EN | DOC_ECC_RW, करोcptr, Mplus_ECCConf);
		अवरोध;
	पूर्ण
पूर्ण

/* This code is only called on ग_लिखो */
अटल पूर्णांक करोc200x_calculate_ecc(काष्ठा nand_chip *this, स्थिर u_अक्षर *dat,
				 अचिन्हित अक्षर *ecc_code)
अणु
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	पूर्णांक i;
	पूर्णांक __always_unused emptymatch = 1;

	/* flush the pipeline */
	अगर (DoC_is_2000(करोc)) अणु
		WriteDOC(करोc->CDSNControl & ~CDSN_CTRL_FLASH_IO, करोcptr, CDSNControl);
		WriteDOC(0, करोcptr, 2k_CDSN_IO);
		WriteDOC(0, करोcptr, 2k_CDSN_IO);
		WriteDOC(0, करोcptr, 2k_CDSN_IO);
		WriteDOC(करोc->CDSNControl, करोcptr, CDSNControl);
	पूर्ण अन्यथा अगर (DoC_is_MillenniumPlus(करोc)) अणु
		WriteDOC(0, करोcptr, Mplus_NOP);
		WriteDOC(0, करोcptr, Mplus_NOP);
		WriteDOC(0, करोcptr, Mplus_NOP);
	पूर्ण अन्यथा अणु
		WriteDOC(0, करोcptr, NOP);
		WriteDOC(0, करोcptr, NOP);
		WriteDOC(0, करोcptr, NOP);
	पूर्ण

	क्रम (i = 0; i < 6; i++) अणु
		अगर (DoC_is_MillenniumPlus(करोc))
			ecc_code[i] = ReadDOC_(करोcptr, DoC_Mplus_ECCSyndrome0 + i);
		अन्यथा
			ecc_code[i] = ReadDOC_(करोcptr, DoC_ECCSyndrome0 + i);
		अगर (ecc_code[i] != empty_ग_लिखो_ecc[i])
			emptymatch = 0;
	पूर्ण
	अगर (DoC_is_MillenniumPlus(करोc))
		WriteDOC(DOC_ECC_DIS, करोcptr, Mplus_ECCConf);
	अन्यथा
		WriteDOC(DOC_ECC_DIS, करोcptr, ECCConf);
#अगर 0
	/* If emptymatch=1, we might have an all-0xff data buffer.  Check. */
	अगर (emptymatch) अणु
		/* Note: this somewhat expensive test should not be triggered
		   often.  It could be optimized away by examining the data in
		   the ग_लिखोbuf routine, and remembering the result. */
		क्रम (i = 0; i < 512; i++) अणु
			अगर (dat[i] == 0xff)
				जारी;
			emptymatch = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	/* If emptymatch still =1, we करो have an all-0xff data buffer.
	   Return all-0xff ecc value instead of the computed one, so
	   it'll look just like a freshly-erased page. */
	अगर (emptymatch)
		स_रखो(ecc_code, 0xff, 6);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक करोc200x_correct_data(काष्ठा nand_chip *this, u_अक्षर *dat,
				u_अक्षर *पढ़ो_ecc, u_अक्षर *isnull)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	व्योम __iomem *करोcptr = करोc->virtadr;
	uपूर्णांक8_t calc_ecc[6];
	अस्थिर u_अक्षर dummy;

	/* flush the pipeline */
	अगर (DoC_is_2000(करोc)) अणु
		dummy = ReadDOC(करोcptr, 2k_ECCStatus);
		dummy = ReadDOC(करोcptr, 2k_ECCStatus);
		dummy = ReadDOC(करोcptr, 2k_ECCStatus);
	पूर्ण अन्यथा अगर (DoC_is_MillenniumPlus(करोc)) अणु
		dummy = ReadDOC(करोcptr, Mplus_ECCConf);
		dummy = ReadDOC(करोcptr, Mplus_ECCConf);
		dummy = ReadDOC(करोcptr, Mplus_ECCConf);
	पूर्ण अन्यथा अणु
		dummy = ReadDOC(करोcptr, ECCConf);
		dummy = ReadDOC(करोcptr, ECCConf);
		dummy = ReadDOC(करोcptr, ECCConf);
	पूर्ण

	/* Error occurred ? */
	अगर (dummy & 0x80) अणु
		क्रम (i = 0; i < 6; i++) अणु
			अगर (DoC_is_MillenniumPlus(करोc))
				calc_ecc[i] = ReadDOC_(करोcptr, DoC_Mplus_ECCSyndrome0 + i);
			अन्यथा
				calc_ecc[i] = ReadDOC_(करोcptr, DoC_ECCSyndrome0 + i);
		पूर्ण

		ret = करोc_ecc_decode(करोc->rs_decoder, dat, calc_ecc);
		अगर (ret > 0)
			pr_err("doc200x_correct_data corrected %d errors\n",
			       ret);
	पूर्ण
	अगर (DoC_is_MillenniumPlus(करोc))
		WriteDOC(DOC_ECC_DIS, करोcptr, Mplus_ECCConf);
	अन्यथा
		WriteDOC(DOC_ECC_DIS, करोcptr, ECCConf);
	अगर (no_ecc_failures && mtd_is_eccerr(ret)) अणु
		pr_err("suppressing ECC failure\n");
		ret = 0;
	पूर्ण
	वापस ret;
पूर्ण

//u_अक्षर mydatabuf[528];

अटल पूर्णांक करोc200x_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 0;
	oobregion->length = 6;

	वापस 0;
पूर्ण

अटल पूर्णांक करोc200x_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 1)
		वापस -दुस्फल;

	/*
	 * The strange out-of-order मुक्त bytes definition is a (possibly
	 * unneeded) attempt to retain compatibility.  It used to पढ़ो:
	 *	.oobमुक्त = अणु अणु8, 8पूर्ण पूर्ण
	 * Since that leaves two bytes unusable, it was changed.  But the
	 * following scheme might affect existing jffs2 installs by moving the
	 * cleanmarker:
	 *	.oobमुक्त = अणु अणु6, 10पूर्ण पूर्ण
	 * jffs2 seems to handle the above gracefully, but the current scheme
	 * seems safer. The only problem with it is that any code retrieving
	 * मुक्त bytes position must be able to handle out-of-order segments.
	 */
	अगर (!section) अणु
		oobregion->offset = 8;
		oobregion->length = 8;
	पूर्ण अन्यथा अणु
		oobregion->offset = 6;
		oobregion->length = 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops करोc200x_ooblayout_ops = अणु
	.ecc = करोc200x_ooblayout_ecc,
	.मुक्त = करोc200x_ooblayout_मुक्त,
पूर्ण;

/* Find the (I)NFTL Media Header, and optionally also the mirror media header.
   On successful वापस, buf will contain a copy of the media header क्रम
   further processing.  id is the string to scan क्रम, and will presumably be
   either "ANAND" or "BNAND".  If findmirror=1, also look क्रम the mirror media
   header.  The page #s of the found media headers are placed in mh0_page and
   mh1_page in the DOC निजी काष्ठाure. */
अटल पूर्णांक __init find_media_headers(काष्ठा mtd_info *mtd, u_अक्षर *buf, स्थिर अक्षर *id, पूर्णांक findmirror)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	अचिन्हित offs;
	पूर्णांक ret;
	माप_प्रकार retlen;

	क्रम (offs = 0; offs < mtd->size; offs += mtd->erasesize) अणु
		ret = mtd_पढ़ो(mtd, offs, mtd->ग_लिखोsize, &retlen, buf);
		अगर (retlen != mtd->ग_लिखोsize)
			जारी;
		अगर (ret) अणु
			pr_warn("ECC error scanning DOC at 0x%x\n", offs);
		पूर्ण
		अगर (स_भेद(buf, id, 6))
			जारी;
		pr_info("Found DiskOnChip %s Media Header at 0x%x\n", id, offs);
		अगर (करोc->mh0_page == -1) अणु
			करोc->mh0_page = offs >> this->page_shअगरt;
			अगर (!findmirror)
				वापस 1;
			जारी;
		पूर्ण
		करोc->mh1_page = offs >> this->page_shअगरt;
		वापस 2;
	पूर्ण
	अगर (करोc->mh0_page == -1) अणु
		pr_warn("DiskOnChip %s Media Header not found.\n", id);
		वापस 0;
	पूर्ण
	/* Only one mediaheader was found.  We want buf to contain a
	   mediaheader on वापस, so we'll have to re-पढ़ो the one we found. */
	offs = करोc->mh0_page << this->page_shअगरt;
	ret = mtd_पढ़ो(mtd, offs, mtd->ग_लिखोsize, &retlen, buf);
	अगर (retlen != mtd->ग_लिखोsize) अणु
		/* Insanity.  Give up. */
		pr_err("Read DiskOnChip Media Header once, but can't reread it???\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक __init nftl_partscan(काष्ठा mtd_info *mtd, काष्ठा mtd_partition *parts)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	काष्ठा nand_memory_organization *memorg;
	पूर्णांक ret = 0;
	u_अक्षर *buf;
	काष्ठा NFTLMediaHeader *mh;
	स्थिर अचिन्हित psize = 1 << this->page_shअगरt;
	पूर्णांक numparts = 0;
	अचिन्हित blocks, maxblocks;
	पूर्णांक offs, numheaders;

	memorg = nanddev_get_memorg(&this->base);

	buf = kदो_स्मृति(mtd->ग_लिखोsize, GFP_KERNEL);
	अगर (!buf) अणु
		वापस 0;
	पूर्ण
	अगर (!(numheaders = find_media_headers(mtd, buf, "ANAND", 1)))
		जाओ out;
	mh = (काष्ठा NFTLMediaHeader *)buf;

	le16_to_cpus(&mh->NumEraseUnits);
	le16_to_cpus(&mh->FirstPhysicalEUN);
	le32_to_cpus(&mh->FormattedSize);

	pr_info("    DataOrgID        = %s\n"
		"    NumEraseUnits    = %d\n"
		"    FirstPhysicalEUN = %d\n"
		"    FormattedSize    = %d\n"
		"    UnitSizeFactor   = %d\n",
		mh->DataOrgID, mh->NumEraseUnits,
		mh->FirstPhysicalEUN, mh->FormattedSize,
		mh->UnitSizeFactor);

	blocks = mtd->size >> this->phys_erase_shअगरt;
	maxblocks = min(32768U, mtd->erasesize - psize);

	अगर (mh->UnitSizeFactor == 0x00) अणु
		/* Auto-determine UnitSizeFactor.  The स्थिरraपूर्णांकs are:
		   - There can be at most 32768 भव blocks.
		   - There can be at most (भव block size - page size)
		   भव blocks (because MediaHeader+BBT must fit in 1).
		 */
		mh->UnitSizeFactor = 0xff;
		जबतक (blocks > maxblocks) अणु
			blocks >>= 1;
			maxblocks = min(32768U, (maxblocks << 1) + psize);
			mh->UnitSizeFactor--;
		पूर्ण
		pr_warn("UnitSizeFactor=0x00 detected.  Correct value is assumed to be 0x%02x.\n", mh->UnitSizeFactor);
	पूर्ण

	/* NOTE: The lines below modअगरy पूर्णांकernal variables of the न_अंकD and MTD
	   layers; variables with have alपढ़ोy been configured by nand_scan.
	   Unक्रमtunately, we didn't know beक्रमe this poपूर्णांक what these values
	   should be.  Thus, this code is somewhat dependent on the exact
	   implementation of the न_अंकD layer.  */
	अगर (mh->UnitSizeFactor != 0xff) अणु
		this->bbt_erase_shअगरt += (0xff - mh->UnitSizeFactor);
		memorg->pages_per_eraseblock <<= (0xff - mh->UnitSizeFactor);
		mtd->erasesize <<= (0xff - mh->UnitSizeFactor);
		pr_info("Setting virtual erase size to %d\n", mtd->erasesize);
		blocks = mtd->size >> this->bbt_erase_shअगरt;
		maxblocks = min(32768U, mtd->erasesize - psize);
	पूर्ण

	अगर (blocks > maxblocks) अणु
		pr_err("UnitSizeFactor of 0x%02x is inconsistent with device size.  Aborting.\n", mh->UnitSizeFactor);
		जाओ out;
	पूर्ण

	/* Skip past the media headers. */
	offs = max(करोc->mh0_page, करोc->mh1_page);
	offs <<= this->page_shअगरt;
	offs += mtd->erasesize;

	अगर (show_firmware_partition == 1) अणु
		parts[0].name = " DiskOnChip Firmware / Media Header partition";
		parts[0].offset = 0;
		parts[0].size = offs;
		numparts = 1;
	पूर्ण

	parts[numparts].name = " DiskOnChip BDTL partition";
	parts[numparts].offset = offs;
	parts[numparts].size = (mh->NumEraseUnits - numheaders) << this->bbt_erase_shअगरt;

	offs += parts[numparts].size;
	numparts++;

	अगर (offs < mtd->size) अणु
		parts[numparts].name = " DiskOnChip Remainder partition";
		parts[numparts].offset = offs;
		parts[numparts].size = mtd->size - offs;
		numparts++;
	पूर्ण

	ret = numparts;
 out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* This is a stripped-करोwn copy of the code in inftlmount.c */
अटल अंतरभूत पूर्णांक __init inftl_partscan(काष्ठा mtd_info *mtd, काष्ठा mtd_partition *parts)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	पूर्णांक ret = 0;
	u_अक्षर *buf;
	काष्ठा INFTLMediaHeader *mh;
	काष्ठा INFTLPartition *ip;
	पूर्णांक numparts = 0;
	पूर्णांक blocks;
	पूर्णांक vshअगरt, lastvunit = 0;
	पूर्णांक i;
	पूर्णांक end = mtd->size;

	अगर (inftl_bbt_ग_लिखो)
		end -= (INFTL_BBT_RESERVED_BLOCKS << this->phys_erase_shअगरt);

	buf = kदो_स्मृति(mtd->ग_लिखोsize, GFP_KERNEL);
	अगर (!buf) अणु
		वापस 0;
	पूर्ण

	अगर (!find_media_headers(mtd, buf, "BNAND", 0))
		जाओ out;
	करोc->mh1_page = करोc->mh0_page + (4096 >> this->page_shअगरt);
	mh = (काष्ठा INFTLMediaHeader *)buf;

	le32_to_cpus(&mh->NoOfBootImageBlocks);
	le32_to_cpus(&mh->NoOfBinaryPartitions);
	le32_to_cpus(&mh->NoOfBDTLPartitions);
	le32_to_cpus(&mh->BlockMultiplierBits);
	le32_to_cpus(&mh->FormatFlags);
	le32_to_cpus(&mh->PercentUsed);

	pr_info("    bootRecordID          = %s\n"
		"    NoOfBootImageBlocks   = %d\n"
		"    NoOfBinaryPartitions  = %d\n"
		"    NoOfBDTLPartitions    = %d\n"
		"    BlockMultiplierBits   = %d\n"
		"    FormatFlgs            = %d\n"
		"    OsakVersion           = %d.%d.%d.%d\n"
		"    PercentUsed           = %d\n",
		mh->bootRecordID, mh->NoOfBootImageBlocks,
		mh->NoOfBinaryPartitions,
		mh->NoOfBDTLPartitions,
		mh->BlockMultiplierBits, mh->FormatFlags,
		((अचिन्हित अक्षर *) &mh->OsakVersion)[0] & 0xf,
		((अचिन्हित अक्षर *) &mh->OsakVersion)[1] & 0xf,
		((अचिन्हित अक्षर *) &mh->OsakVersion)[2] & 0xf,
		((अचिन्हित अक्षर *) &mh->OsakVersion)[3] & 0xf,
		mh->PercentUsed);

	vshअगरt = this->phys_erase_shअगरt + mh->BlockMultiplierBits;

	blocks = mtd->size >> vshअगरt;
	अगर (blocks > 32768) अणु
		pr_err("BlockMultiplierBits=%d is inconsistent with device size.  Aborting.\n", mh->BlockMultiplierBits);
		जाओ out;
	पूर्ण

	blocks = करोc->chips_per_न्यूनमान << (this->chip_shअगरt - this->phys_erase_shअगरt);
	अगर (inftl_bbt_ग_लिखो && (blocks > mtd->erasesize)) अणु
		pr_err("Writeable BBTs spanning more than one erase block are not yet supported.  FIX ME!\n");
		जाओ out;
	पूर्ण

	/* Scan the partitions */
	क्रम (i = 0; (i < 4); i++) अणु
		ip = &(mh->Partitions[i]);
		le32_to_cpus(&ip->भवUnits);
		le32_to_cpus(&ip->firstUnit);
		le32_to_cpus(&ip->lastUnit);
		le32_to_cpus(&ip->flags);
		le32_to_cpus(&ip->spareUnits);
		le32_to_cpus(&ip->Reserved0);

		pr_info("    PARTITION[%d] ->\n"
			"        virtualUnits    = %d\n"
			"        firstUnit       = %d\n"
			"        lastUnit        = %d\n"
			"        flags           = 0x%x\n"
			"        spareUnits      = %d\n",
			i, ip->भवUnits, ip->firstUnit,
			ip->lastUnit, ip->flags,
			ip->spareUnits);

		अगर ((show_firmware_partition == 1) &&
		    (i == 0) && (ip->firstUnit > 0)) अणु
			parts[0].name = " DiskOnChip IPL / Media Header partition";
			parts[0].offset = 0;
			parts[0].size = mtd->erasesize * ip->firstUnit;
			numparts = 1;
		पूर्ण

		अगर (ip->flags & INFTL_BINARY)
			parts[numparts].name = " DiskOnChip BDK partition";
		अन्यथा
			parts[numparts].name = " DiskOnChip BDTL partition";
		parts[numparts].offset = ip->firstUnit << vshअगरt;
		parts[numparts].size = (1 + ip->lastUnit - ip->firstUnit) << vshअगरt;
		numparts++;
		अगर (ip->lastUnit > lastvunit)
			lastvunit = ip->lastUnit;
		अगर (ip->flags & INFTL_LAST)
			अवरोध;
	पूर्ण
	lastvunit++;
	अगर ((lastvunit << vshअगरt) < end) अणु
		parts[numparts].name = " DiskOnChip Remainder partition";
		parts[numparts].offset = lastvunit << vshअगरt;
		parts[numparts].size = end - parts[numparts].offset;
		numparts++;
	पूर्ण
	ret = numparts;
 out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

अटल पूर्णांक __init nftl_scan_bbt(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक ret, numparts;
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	काष्ठा mtd_partition parts[2];

	स_रखो((अक्षर *)parts, 0, माप(parts));
	/* On NFTL, we have to find the media headers beक्रमe we can पढ़ो the
	   BBTs, since they're stored in the media header eraseblocks. */
	numparts = nftl_partscan(mtd, parts);
	अगर (!numparts)
		वापस -EIO;
	this->bbt_td->options = न_अंकD_BBT_ABSPAGE | न_अंकD_BBT_8BIT |
				न_अंकD_BBT_SAVECONTENT | न_अंकD_BBT_WRITE |
				न_अंकD_BBT_VERSION;
	this->bbt_td->veroffs = 7;
	this->bbt_td->pages[0] = करोc->mh0_page + 1;
	अगर (करोc->mh1_page != -1) अणु
		this->bbt_md->options = न_अंकD_BBT_ABSPAGE | न_अंकD_BBT_8BIT |
					न_अंकD_BBT_SAVECONTENT | न_अंकD_BBT_WRITE |
					न_अंकD_BBT_VERSION;
		this->bbt_md->veroffs = 7;
		this->bbt_md->pages[0] = करोc->mh1_page + 1;
	पूर्ण अन्यथा अणु
		this->bbt_md = शून्य;
	पूर्ण

	ret = nand_create_bbt(this);
	अगर (ret)
		वापस ret;

	वापस mtd_device_रेजिस्टर(mtd, parts, no_स्वतःpart ? 0 : numparts);
पूर्ण

अटल पूर्णांक __init inftl_scan_bbt(काष्ठा mtd_info *mtd)
अणु
	पूर्णांक ret, numparts;
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);
	काष्ठा mtd_partition parts[5];

	अगर (nanddev_ntarमाला_लो(&this->base) > करोc->chips_per_न्यूनमान) अणु
		pr_err("Multi-floor INFTL devices not yet supported.\n");
		वापस -EIO;
	पूर्ण

	अगर (DoC_is_MillenniumPlus(करोc)) अणु
		this->bbt_td->options = न_अंकD_BBT_2BIT | न_अंकD_BBT_ABSPAGE;
		अगर (inftl_bbt_ग_लिखो)
			this->bbt_td->options |= न_अंकD_BBT_WRITE;
		this->bbt_td->pages[0] = 2;
		this->bbt_md = शून्य;
	पूर्ण अन्यथा अणु
		this->bbt_td->options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_8BIT | न_अंकD_BBT_VERSION;
		अगर (inftl_bbt_ग_लिखो)
			this->bbt_td->options |= न_अंकD_BBT_WRITE;
		this->bbt_td->offs = 8;
		this->bbt_td->len = 8;
		this->bbt_td->veroffs = 7;
		this->bbt_td->maxblocks = INFTL_BBT_RESERVED_BLOCKS;
		this->bbt_td->reserved_block_code = 0x01;
		this->bbt_td->pattern = "MSYS_BBT";

		this->bbt_md->options = न_अंकD_BBT_LASTBLOCK | न_अंकD_BBT_8BIT | न_अंकD_BBT_VERSION;
		अगर (inftl_bbt_ग_लिखो)
			this->bbt_md->options |= न_अंकD_BBT_WRITE;
		this->bbt_md->offs = 8;
		this->bbt_md->len = 8;
		this->bbt_md->veroffs = 7;
		this->bbt_md->maxblocks = INFTL_BBT_RESERVED_BLOCKS;
		this->bbt_md->reserved_block_code = 0x01;
		this->bbt_md->pattern = "TBB_SYSM";
	पूर्ण

	ret = nand_create_bbt(this);
	अगर (ret)
		वापस ret;

	स_रखो((अक्षर *)parts, 0, माप(parts));
	numparts = inftl_partscan(mtd, parts);
	/* At least क्रम now, require the INFTL Media Header.  We could probably
	   करो without it क्रम non-INFTL use, since all it gives us is
	   स्वतःpartitioning, but I want to give it more thought. */
	अगर (!numparts)
		वापस -EIO;
	वापस mtd_device_रेजिस्टर(mtd, parts, no_स्वतःpart ? 0 : numparts);
पूर्ण

अटल अंतरभूत पूर्णांक __init करोc2000_init(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);

	करोc->late_init = nftl_scan_bbt;

	करोc->CDSNControl = CDSN_CTRL_FLASH_IO | CDSN_CTRL_ECC_IO;
	करोc2000_count_chips(mtd);
	mtd->name = "DiskOnChip 2000 (NFTL Model)";
	वापस (4 * करोc->chips_per_न्यूनमान);
पूर्ण

अटल अंतरभूत पूर्णांक __init करोc2001_init(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);

	ReadDOC(करोc->virtadr, ChipID);
	ReadDOC(करोc->virtadr, ChipID);
	ReadDOC(करोc->virtadr, ChipID);
	अगर (ReadDOC(करोc->virtadr, ChipID) != DOC_ChipID_DocMil) अणु
		/* It's not a Millennium; it's one of the newer
		   DiskOnChip 2000 units with a similar ASIC.
		   Treat it like a Millennium, except that it
		   can have multiple chips. */
		करोc2000_count_chips(mtd);
		mtd->name = "DiskOnChip 2000 (INFTL Model)";
		करोc->late_init = inftl_scan_bbt;
		वापस (4 * करोc->chips_per_न्यूनमान);
	पूर्ण अन्यथा अणु
		/* Bog-standard Millennium */
		करोc->chips_per_न्यूनमान = 1;
		mtd->name = "DiskOnChip Millennium";
		करोc->late_init = nftl_scan_bbt;
		वापस 1;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक __init करोc2001plus_init(काष्ठा mtd_info *mtd)
अणु
	काष्ठा nand_chip *this = mtd_to_nand(mtd);
	काष्ठा करोc_priv *करोc = nand_get_controller_data(this);

	करोc->late_init = inftl_scan_bbt;
	this->ecc.hwctl = करोc2001plus_enable_hwecc;

	करोc->chips_per_न्यूनमान = 1;
	mtd->name = "DiskOnChip Millennium Plus";

	वापस 1;
पूर्ण

अटल पूर्णांक करोc200x_attach_chip(काष्ठा nand_chip *chip)
अणु
	अगर (chip->ecc.engine_type != न_अंकD_ECC_ENGINE_TYPE_ON_HOST)
		वापस 0;

	chip->ecc.placement = न_अंकD_ECC_PLACEMENT_INTERLEAVED;
	chip->ecc.size = 512;
	chip->ecc.bytes = 6;
	chip->ecc.strength = 2;
	chip->ecc.options = न_अंकD_ECC_GENERIC_ERASED_CHECK;
	chip->ecc.hwctl = करोc200x_enable_hwecc;
	chip->ecc.calculate = करोc200x_calculate_ecc;
	chip->ecc.correct = करोc200x_correct_data;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops करोc200x_ops = अणु
	.exec_op = करोc200x_exec_op,
	.attach_chip = करोc200x_attach_chip,
पूर्ण;

अटल स्थिर काष्ठा nand_controller_ops करोc2001plus_ops = अणु
	.exec_op = करोc2001plus_exec_op,
	.attach_chip = करोc200x_attach_chip,
पूर्ण;

अटल पूर्णांक __init करोc_probe(अचिन्हित दीर्घ physadr)
अणु
	काष्ठा nand_chip *nand = शून्य;
	काष्ठा करोc_priv *करोc = शून्य;
	अचिन्हित अक्षर ChipID;
	काष्ठा mtd_info *mtd;
	व्योम __iomem *virtadr;
	अचिन्हित अक्षर save_control;
	अचिन्हित अक्षर पंचांगp, पंचांगpb, पंचांगpc;
	पूर्णांक reg, len, numchips;
	पूर्णांक ret = 0;

	अगर (!request_mem_region(physadr, DOC_IOREMAP_LEN, "DiskOnChip"))
		वापस -EBUSY;
	virtadr = ioremap(physadr, DOC_IOREMAP_LEN);
	अगर (!virtadr) अणु
		pr_err("Diskonchip ioremap failed: 0x%x bytes at 0x%lx\n",
		       DOC_IOREMAP_LEN, physadr);
		ret = -EIO;
		जाओ error_ioremap;
	पूर्ण

	/* It's not possible to cleanly detect the DiskOnChip - the
	 * bootup procedure will put the device पूर्णांकo reset mode, and
	 * it's not possible to talk to it without actually writing
	 * to the DOCControl रेजिस्टर. So we store the current contents
	 * of the DOCControl रेजिस्टर's location, in हाल we later decide
	 * that it's not a DiskOnChip, and want to put it back how we
	 * found it.
	 */
	save_control = ReadDOC(virtadr, DOCControl);

	/* Reset the DiskOnChip ASIC */
	WriteDOC(DOC_MODE_CLR_ERR | DOC_MODE_MDWREN | DOC_MODE_RESET, virtadr, DOCControl);
	WriteDOC(DOC_MODE_CLR_ERR | DOC_MODE_MDWREN | DOC_MODE_RESET, virtadr, DOCControl);

	/* Enable the DiskOnChip ASIC */
	WriteDOC(DOC_MODE_CLR_ERR | DOC_MODE_MDWREN | DOC_MODE_NORMAL, virtadr, DOCControl);
	WriteDOC(DOC_MODE_CLR_ERR | DOC_MODE_MDWREN | DOC_MODE_NORMAL, virtadr, DOCControl);

	ChipID = ReadDOC(virtadr, ChipID);

	चयन (ChipID) अणु
	हाल DOC_ChipID_Doc2k:
		reg = DoC_2k_ECCStatus;
		अवरोध;
	हाल DOC_ChipID_DocMil:
		reg = DoC_ECCConf;
		अवरोध;
	हाल DOC_ChipID_DocMilPlus16:
	हाल DOC_ChipID_DocMilPlus32:
	हाल 0:
		/* Possible Millennium Plus, need to करो more checks */
		/* Possibly release from घातer करोwn mode */
		क्रम (पंचांगp = 0; (पंचांगp < 4); पंचांगp++)
			ReadDOC(virtadr, Mplus_Power);

		/* Reset the Millennium Plus ASIC */
		पंचांगp = DOC_MODE_RESET | DOC_MODE_MDWREN | DOC_MODE_RST_LAT | DOC_MODE_BDECT;
		WriteDOC(पंचांगp, virtadr, Mplus_DOCControl);
		WriteDOC(~पंचांगp, virtadr, Mplus_CtrlConfirm);

		usleep_range(1000, 2000);
		/* Enable the Millennium Plus ASIC */
		पंचांगp = DOC_MODE_NORMAL | DOC_MODE_MDWREN | DOC_MODE_RST_LAT | DOC_MODE_BDECT;
		WriteDOC(पंचांगp, virtadr, Mplus_DOCControl);
		WriteDOC(~पंचांगp, virtadr, Mplus_CtrlConfirm);
		usleep_range(1000, 2000);

		ChipID = ReadDOC(virtadr, ChipID);

		चयन (ChipID) अणु
		हाल DOC_ChipID_DocMilPlus16:
			reg = DoC_Mplus_Toggle;
			अवरोध;
		हाल DOC_ChipID_DocMilPlus32:
			pr_err("DiskOnChip Millennium Plus 32MB is not supported, ignoring.\n");
			fallthrough;
		शेष:
			ret = -ENODEV;
			जाओ notfound;
		पूर्ण
		अवरोध;

	शेष:
		ret = -ENODEV;
		जाओ notfound;
	पूर्ण
	/* Check the TOGGLE bit in the ECC रेजिस्टर */
	पंचांगp = ReadDOC_(virtadr, reg) & DOC_TOGGLE_BIT;
	पंचांगpb = ReadDOC_(virtadr, reg) & DOC_TOGGLE_BIT;
	पंचांगpc = ReadDOC_(virtadr, reg) & DOC_TOGGLE_BIT;
	अगर ((पंचांगp == पंचांगpb) || (पंचांगp != पंचांगpc)) अणु
		pr_warn("Possible DiskOnChip at 0x%lx failed TOGGLE test, dropping.\n", physadr);
		ret = -ENODEV;
		जाओ notfound;
	पूर्ण

	क्रम (mtd = करोclist; mtd; mtd = करोc->nextकरोc) अणु
		अचिन्हित अक्षर oldval;
		अचिन्हित अक्षर newval;
		nand = mtd_to_nand(mtd);
		करोc = nand_get_controller_data(nand);
		/* Use the alias resolution रेजिस्टर to determine अगर this is
		   in fact the same DOC aliased to a new address.  If ग_लिखोs
		   to one chip's alias resolution रेजिस्टर change the value on
		   the other chip, they're the same chip. */
		अगर (ChipID == DOC_ChipID_DocMilPlus16) अणु
			oldval = ReadDOC(करोc->virtadr, Mplus_AliasResolution);
			newval = ReadDOC(virtadr, Mplus_AliasResolution);
		पूर्ण अन्यथा अणु
			oldval = ReadDOC(करोc->virtadr, AliasResolution);
			newval = ReadDOC(virtadr, AliasResolution);
		पूर्ण
		अगर (oldval != newval)
			जारी;
		अगर (ChipID == DOC_ChipID_DocMilPlus16) अणु
			WriteDOC(~newval, virtadr, Mplus_AliasResolution);
			oldval = ReadDOC(करोc->virtadr, Mplus_AliasResolution);
			WriteDOC(newval, virtadr, Mplus_AliasResolution);	// restore it
		पूर्ण अन्यथा अणु
			WriteDOC(~newval, virtadr, AliasResolution);
			oldval = ReadDOC(करोc->virtadr, AliasResolution);
			WriteDOC(newval, virtadr, AliasResolution);	// restore it
		पूर्ण
		newval = ~newval;
		अगर (oldval == newval) अणु
			pr_debug("Found alias of DOC at 0x%lx to 0x%lx\n",
				 करोc->physadr, physadr);
			जाओ notfound;
		पूर्ण
	पूर्ण

	pr_notice("DiskOnChip found at 0x%lx\n", physadr);

	len = माप(काष्ठा nand_chip) + माप(काष्ठा करोc_priv) +
	      (2 * माप(काष्ठा nand_bbt_descr));
	nand = kzalloc(len, GFP_KERNEL);
	अगर (!nand) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/*
	 * Allocate a RS codec instance
	 *
	 * Symbolsize is 10 (bits)
	 * Primitve polynomial is x^10+x^3+1
	 * First consecutive root is 510
	 * Primitve element to generate roots = 1
	 * Generator polinomial degree = 4
	 */
	करोc = (काष्ठा करोc_priv *) (nand + 1);
	करोc->rs_decoder = init_rs(10, 0x409, FCR, 1, NROOTS);
	अगर (!करोc->rs_decoder) अणु
		pr_err("DiskOnChip: Could not create a RS codec\n");
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	nand_controller_init(&करोc->base);
	अगर (ChipID == DOC_ChipID_DocMilPlus16)
		करोc->base.ops = &करोc2001plus_ops;
	अन्यथा
		करोc->base.ops = &करोc200x_ops;

	mtd			= nand_to_mtd(nand);
	nand->bbt_td		= (काष्ठा nand_bbt_descr *) (करोc + 1);
	nand->bbt_md		= nand->bbt_td + 1;

	mtd->owner		= THIS_MODULE;
	mtd_set_ooblayout(mtd, &करोc200x_ooblayout_ops);

	nand->controller	= &करोc->base;
	nand_set_controller_data(nand, करोc);
	nand->bbt_options	= न_अंकD_BBT_USE_FLASH;
	/* Skip the स्वतःmatic BBT scan so we can run it manually */
	nand->options		|= न_अंकD_SKIP_BBTSCAN | न_अंकD_NO_BBM_QUIRK;

	करोc->physadr		= physadr;
	करोc->virtadr		= virtadr;
	करोc->ChipID		= ChipID;
	करोc->curन्यूनमान		= -1;
	करोc->curchip		= -1;
	करोc->mh0_page		= -1;
	करोc->mh1_page		= -1;
	करोc->nextकरोc		= करोclist;

	अगर (ChipID == DOC_ChipID_Doc2k)
		numchips = करोc2000_init(mtd);
	अन्यथा अगर (ChipID == DOC_ChipID_DocMilPlus16)
		numchips = करोc2001plus_init(mtd);
	अन्यथा
		numchips = करोc2001_init(mtd);

	अगर ((ret = nand_scan(nand, numchips)) || (ret = करोc->late_init(mtd))) अणु
		/* DBB note: i believe nand_cleanup is necessary here, as
		   buffers may have been allocated in nand_base.  Check with
		   Thomas. FIX ME! */
		nand_cleanup(nand);
		जाओ fail;
	पूर्ण

	/* Success! */
	करोclist = mtd;
	वापस 0;

 notfound:
	/* Put back the contents of the DOCControl रेजिस्टर, in हाल it's not
	   actually a DiskOnChip.  */
	WriteDOC(save_control, virtadr, DOCControl);
 fail:
	अगर (करोc)
		मुक्त_rs(करोc->rs_decoder);
	kमुक्त(nand);
	iounmap(virtadr);

error_ioremap:
	release_mem_region(physadr, DOC_IOREMAP_LEN);

	वापस ret;
पूर्ण

अटल व्योम release_nandकरोc(व्योम)
अणु
	काष्ठा mtd_info *mtd, *nexपंचांगtd;
	काष्ठा nand_chip *nand;
	काष्ठा करोc_priv *करोc;
	पूर्णांक ret;

	क्रम (mtd = करोclist; mtd; mtd = nexपंचांगtd) अणु
		nand = mtd_to_nand(mtd);
		करोc = nand_get_controller_data(nand);

		nexपंचांगtd = करोc->nextकरोc;
		ret = mtd_device_unरेजिस्टर(mtd);
		WARN_ON(ret);
		nand_cleanup(nand);
		iounmap(करोc->virtadr);
		release_mem_region(करोc->physadr, DOC_IOREMAP_LEN);
		मुक्त_rs(करोc->rs_decoder);
		kमुक्त(nand);
	पूर्ण
पूर्ण

अटल पूर्णांक __init init_nandकरोc(व्योम)
अणु
	पूर्णांक i, ret = 0;

	अगर (करोc_config_location) अणु
		pr_info("Using configured DiskOnChip probe address 0x%lx\n",
			करोc_config_location);
		ret = करोc_probe(करोc_config_location);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; (करोc_locations[i] != 0xffffffff); i++) अणु
			करोc_probe(करोc_locations[i]);
		पूर्ण
	पूर्ण
	/* No banner message any more. Prपूर्णांक a message अगर no DiskOnChip
	   found, so the user knows we at least tried. */
	अगर (!करोclist) अणु
		pr_info("No valid DiskOnChip devices found\n");
		ret = -ENODEV;
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम __निकास cleanup_nandकरोc(व्योम)
अणु
	/* Cleanup the nand/DoC resources */
	release_nandकरोc();
पूर्ण

module_init(init_nandकरोc);
module_निकास(cleanup_nandकरोc);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>");
MODULE_DESCRIPTION("M-Systems DiskOnChip 2000, Millennium and Millennium Plus device driver");
