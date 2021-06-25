<शैली गुरु>
/*
	drivers/net/ethernet/dec/tulip/eeprom.c

	Copyright 2000,2001  The Linux Kernel Team
	Written/copyright 1994-2001 by Donald Becker.

	This software may be used and distributed according to the terms
	of the GNU General Public License, incorporated herein by reference.

	Please submit bug reports to http://bugzilla.kernel.org/.
*/

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश "tulip.h"
#समावेश <यंत्र/unaligned.h>



/* Serial EEPROM section. */
/* The मुख्य routine to parse the very complicated SROM काष्ठाure.
   Search www.digital.com क्रम "21X4 SROM" to get details.
   This code is very complex, and will require changes to support
   additional cards, so I'll be verbose about what is going on.
   */

/* Known cards that have old-style EEPROMs. */
अटल काष्ठा eeprom_fixup eeprom_fixups[] = अणु
  अणु"Asante", 0, 0, 0x94, अणु0x1e00, 0x0000, 0x0800, 0x0100, 0x018c,
			  0x0000, 0x0000, 0xe078, 0x0001, 0x0050, 0x0018 पूर्णपूर्ण,
  अणु"SMC9332DST", 0, 0, 0xC0, अणु 0x1e00, 0x0000, 0x0800, 0x041f,
			   0x0000, 0x009E, /* 10baseT */
			   0x0004, 0x009E, /* 10baseT-FD */
			   0x0903, 0x006D, /* 100baseTx */
			   0x0905, 0x006D, /* 100baseTx-FD */ पूर्णपूर्ण,
  अणु"Cogent EM100", 0, 0, 0x92, अणु 0x1e00, 0x0000, 0x0800, 0x063f,
				 0x0107, 0x8021, /* 100baseFx */
				 0x0108, 0x8021, /* 100baseFx-FD */
				 0x0100, 0x009E, /* 10baseT */
				 0x0104, 0x009E, /* 10baseT-FD */
				 0x0103, 0x006D, /* 100baseTx */
				 0x0105, 0x006D, /* 100baseTx-FD */ पूर्णपूर्ण,
  अणु"Maxtech NX-110", 0, 0, 0xE8, अणु 0x1e00, 0x0000, 0x0800, 0x0513,
				   0x1001, 0x009E, /* 10base2, CSR12 0x10*/
				   0x0000, 0x009E, /* 10baseT */
				   0x0004, 0x009E, /* 10baseT-FD */
				   0x0303, 0x006D, /* 100baseTx, CSR12 0x03 */
				   0x0305, 0x006D, /* 100baseTx-FD CSR12 0x03 */पूर्णपूर्ण,
  अणु"Accton EN1207", 0, 0, 0xE8, अणु 0x1e00, 0x0000, 0x0800, 0x051F,
				  0x1B01, 0x0000, /* 10base2,   CSR12 0x1B */
				  0x0B00, 0x009E, /* 10baseT,   CSR12 0x0B */
				  0x0B04, 0x009E, /* 10baseT-FD,CSR12 0x0B */
				  0x1B03, 0x006D, /* 100baseTx, CSR12 0x1B */
				  0x1B05, 0x006D, /* 100baseTx-FD CSR12 0x1B */
   पूर्णपूर्ण,
  अणु"NetWinder", 0x00, 0x10, 0x57,
	/* Default media = MII
	 * MII block, reset sequence (3) = 0x0821 0x0000 0x0001, capabilities 0x01e1
	 */
	अणु 0x1e00, 0x0000, 0x000b, 0x8f01, 0x0103, 0x0300, 0x0821, 0x000, 0x0001, 0x0000, 0x01e1 पूर्ण
  पूर्ण,
  अणु"Cobalt Microserver", 0, 0x10, 0xE0, अणु0x1e00, /* 0 == controller #, 1e == offset	*/
					 0x0000, /* 0 == high offset, 0 == gap		*/
					 0x0800, /* Default Autoselect			*/
					 0x8001, /* 1 leaf, extended type, bogus len	*/
					 0x0003, /* Type 3 (MII), PHY #0		*/
					 0x0400, /* 0 init instr, 4 reset instr		*/
					 0x0801, /* Set control mode, GP0 output	*/
					 0x0000, /* Drive GP0 Low (RST is active low)	*/
					 0x0800, /* control mode, GP0 input (undriven)	*/
					 0x0000, /* clear control mode			*/
					 0x7800, /* 100TX FDX + HDX, 10bT FDX + HDX	*/
					 0x01e0, /* Advertise all above			*/
					 0x5000, /* FDX all above			*/
					 0x1800, /* Set fast TTM in 100bt modes		*/
					 0x0000, /* PHY cannot be unplugged		*/
  पूर्णपूर्ण,
  अणुशून्यपूर्णपूर्ण;


अटल स्थिर अक्षर *स्थिर block_name[] = अणु
	"21140 non-MII",
	"21140 MII PHY",
	"21142 Serial PHY",
	"21142 MII PHY",
	"21143 SYM PHY",
	"21143 reset method"
पूर्ण;


/**
 * tulip_build_fake_mediatable - Build a fake mediatable entry.
 * @tp: Ptr to the tulip निजी data.
 *
 * Some cards like the 3x5 HSC cards (J3514A) करो not have a standard
 * srom and can not be handled under the fixup routine.  These cards
 * still need a valid mediatable entry क्रम correct csr12 setup and
 * mii handling.
 *
 * Since this is currently a parisc-linux specअगरic function, the
 * #अगर_घोषित __hppa__ should completely optimize this function away क्रम
 * non-parisc hardware.
 */
अटल व्योम tulip_build_fake_mediatable(काष्ठा tulip_निजी *tp)
अणु
#अगर_घोषित CONFIG_GSC
	अगर (tp->flags & NEEDS_FAKE_MEDIA_TABLE) अणु
		अटल अचिन्हित अक्षर leafdata[] =
			अणु 0x01,       /* phy number */
			  0x02,       /* gpr setup sequence length */
			  0x02, 0x00, /* gpr setup sequence */
			  0x02,       /* phy reset sequence length */
			  0x01, 0x00, /* phy reset sequence */
			  0x00, 0x78, /* media capabilities */
			  0x00, 0xe0, /* nway advertisement */
			  0x00, 0x05, /* fdx bit map */
			  0x00, 0x06  /* tपंचांग bit map */
			पूर्ण;

		tp->mtable = kदो_स्मृति(माप(काष्ठा mediatable) +
				     माप(काष्ठा medialeaf), GFP_KERNEL);

		अगर (tp->mtable == शून्य)
			वापस; /* Horrible, impossible failure. */

		tp->mtable->शेषmedia = 0x800;
		tp->mtable->leafcount = 1;
		tp->mtable->csr12dir = 0x3f; /* inमाला_दो on bit7 क्रम hsc-pci, bit6 क्रम pci-fx */
		tp->mtable->has_nonmii = 0;
		tp->mtable->has_reset = 0;
		tp->mtable->has_mii = 1;
		tp->mtable->csr15dir = tp->mtable->csr15val = 0;
		tp->mtable->mleaf[0].type = 1;
		tp->mtable->mleaf[0].media = 11;
		tp->mtable->mleaf[0].leafdata = &leafdata[0];
		tp->flags |= HAS_PHY_IRQ;
		tp->csr12_shaकरोw = -1;
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम tulip_parse_eeprom(काष्ठा net_device *dev)
अणु
	/*
	  dev is not रेजिस्टरed at this poपूर्णांक, so logging messages can't
	  use dev_<level> or netdev_<level> but dev->name is good via a
	  hack in the caller
	*/

	/* The last media info list parsed, क्रम multiport boards.  */
	अटल काष्ठा mediatable *last_mediatable;
	अटल अचिन्हित अक्षर *last_ee_data;
	अटल पूर्णांक controller_index;
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	अचिन्हित अक्षर *ee_data = tp->eeprom;
	पूर्णांक i;

	tp->mtable = शून्य;
	/* Detect an old-style (SA only) EEPROM layout:
	   स_भेद(eedata, eedata+16, 8). */
	क्रम (i = 0; i < 8; i ++)
		अगर (ee_data[i] != ee_data[16+i])
			अवरोध;
	अगर (i >= 8) अणु
		अगर (ee_data[0] == 0xff) अणु
			अगर (last_mediatable) अणु
				controller_index++;
				pr_info("%s: Controller %d of multiport board\n",
					dev->name, controller_index);
				tp->mtable = last_mediatable;
				ee_data = last_ee_data;
				जाओ subsequent_board;
			पूर्ण अन्यथा
				pr_info("%s: Missing EEPROM, this interface may not work correctly!\n",
					dev->name);
			वापस;
		पूर्ण
	  /* Do a fix-up based on the venकरोr half of the station address prefix. */
	  क्रम (i = 0; eeprom_fixups[i].name; i++) अणु
		  अगर (dev->dev_addr[0] == eeprom_fixups[i].addr0 &&
		      dev->dev_addr[1] == eeprom_fixups[i].addr1 &&
		      dev->dev_addr[2] == eeprom_fixups[i].addr2) अणु
		  अगर (dev->dev_addr[2] == 0xE8 && ee_data[0x1a] == 0x55)
			  i++;			/* An Accton EN1207, not an outlaw Maxtech. */
		  स_नकल(ee_data + 26, eeprom_fixups[i].newtable,
				 माप(eeprom_fixups[i].newtable));
		  pr_info("%s: Old format EEPROM on '%s' board.  Using substitute media control info\n",
			  dev->name, eeprom_fixups[i].name);
		  अवरोध;
		पूर्ण
	  पूर्ण
	  अगर (eeprom_fixups[i].name == शून्य) अणु /* No fixup found. */
		  pr_info("%s: Old style EEPROM with no media selection information\n",
			  dev->name);
		वापस;
	  पूर्ण
	पूर्ण

	controller_index = 0;
	अगर (ee_data[19] > 1) अणु		/* Multiport board. */
		last_ee_data = ee_data;
	पूर्ण
subsequent_board:

	अगर (ee_data[27] == 0) अणु		/* No valid media table. */
		tulip_build_fake_mediatable(tp);
	पूर्ण अन्यथा अणु
		अचिन्हित अक्षर *p = (व्योम *)ee_data + ee_data[27];
		अचिन्हित अक्षर csr12dir = 0;
		पूर्णांक count, new_advertise = 0;
		काष्ठा mediatable *mtable;
		u16 media = get_u16(p);

		p += 2;
		अगर (tp->flags & CSR12_IN_SROM)
			csr12dir = *p++;
		count = *p++;

	        /* there is no phy inक्रमmation, करोn't even try to build mtable */
	        अगर (count == 0) अणु
			अगर (tulip_debug > 0)
				pr_warn("%s: no phy info, aborting mtable build\n",
					dev->name);
		        वापस;
		पूर्ण

		mtable = kदो_स्मृति(काष्ठा_size(mtable, mleaf, count), GFP_KERNEL);
		अगर (mtable == शून्य)
			वापस;				/* Horrible, impossible failure. */
		last_mediatable = tp->mtable = mtable;
		mtable->शेषmedia = media;
		mtable->leafcount = count;
		mtable->csr12dir = csr12dir;
		mtable->has_nonmii = mtable->has_mii = mtable->has_reset = 0;
		mtable->csr15dir = mtable->csr15val = 0;

		pr_info("%s: EEPROM default media type %s\n",
			dev->name,
			media & 0x0800 ? "Autosense"
				       : medianame[media & MEDIA_MASK]);
		क्रम (i = 0; i < count; i++) अणु
			काष्ठा medialeaf *leaf = &mtable->mleaf[i];

			अगर ((p[0] & 0x80) == 0) अणु /* 21140 Compact block. */
				leaf->type = 0;
				leaf->media = p[0] & 0x3f;
				leaf->leafdata = p;
				अगर ((p[2] & 0x61) == 0x01)	/* Bogus, but Znyx boards करो it. */
					mtable->has_mii = 1;
				p += 4;
			पूर्ण अन्यथा अणु
				leaf->type = p[1];
				अगर (p[1] == 0x05) अणु
					mtable->has_reset = i;
					leaf->media = p[2] & 0x0f;
				पूर्ण अन्यथा अगर (tp->chip_id == DM910X && p[1] == 0x80) अणु
					/* Hack to ignore Davicom delay period block */
					mtable->leafcount--;
					count--;
					i--;
					leaf->leafdata = p + 2;
					p += (p[0] & 0x3f) + 1;
					जारी;
				पूर्ण अन्यथा अगर (p[1] & 1) अणु
					पूर्णांक gpr_len, reset_len;

					mtable->has_mii = 1;
					leaf->media = 11;
					gpr_len=p[3]*2;
					reset_len=p[4+gpr_len]*2;
					new_advertise |= get_u16(&p[7+gpr_len+reset_len]);
				पूर्ण अन्यथा अणु
					mtable->has_nonmii = 1;
					leaf->media = p[2] & MEDIA_MASK;
					/* Davicom's media number क्रम 100BaseTX is strange */
					अगर (tp->chip_id == DM910X && leaf->media == 1)
						leaf->media = 3;
					चयन (leaf->media) अणु
					हाल 0: new_advertise |= 0x0020; अवरोध;
					हाल 4: new_advertise |= 0x0040; अवरोध;
					हाल 3: new_advertise |= 0x0080; अवरोध;
					हाल 5: new_advertise |= 0x0100; अवरोध;
					हाल 6: new_advertise |= 0x0200; अवरोध;
					पूर्ण
					अगर (p[1] == 2  &&  leaf->media == 0) अणु
						अगर (p[2] & 0x40) अणु
							u32 base15 = get_unaligned((u16*)&p[7]);
							mtable->csr15dir =
								(get_unaligned((u16*)&p[9])<<16) + base15;
							mtable->csr15val =
								(get_unaligned((u16*)&p[11])<<16) + base15;
						पूर्ण अन्यथा अणु
							mtable->csr15dir = get_unaligned((u16*)&p[3])<<16;
							mtable->csr15val = get_unaligned((u16*)&p[5])<<16;
						पूर्ण
					पूर्ण
				पूर्ण
				leaf->leafdata = p + 2;
				p += (p[0] & 0x3f) + 1;
			पूर्ण
			अगर (tulip_debug > 1  &&  leaf->media == 11) अणु
				अचिन्हित अक्षर *bp = leaf->leafdata;
				pr_info("%s: MII interface PHY %d, setup/reset sequences %d/%d long, capabilities %02x %02x\n",
					dev->name,
					bp[0], bp[1], bp[2 + bp[1]*2],
					bp[5 + bp[2 + bp[1]*2]*2],
					bp[4 + bp[2 + bp[1]*2]*2]);
			पूर्ण
			pr_info("%s: Index #%d - Media %s (#%d) described by a %s (%d) block\n",
				dev->name,
				i, medianame[leaf->media & 15], leaf->media,
				leaf->type < ARRAY_SIZE(block_name) ? block_name[leaf->type] : "<unknown>",
				leaf->type);
		पूर्ण
		अगर (new_advertise)
			tp->sym_advertise = new_advertise;
	पूर्ण
पूर्ण
/* Reading a serial EEPROM is a "bit" grungy, but we work our way through:->.*/

/*  EEPROM_Ctrl bits. */
#घोषणा EE_SHIFT_CLK	0x02	/* EEPROM shअगरt घड़ी. */
#घोषणा EE_CS		0x01	/* EEPROM chip select. */
#घोषणा EE_DATA_WRITE	0x04	/* Data from the Tulip to EEPROM. */
#घोषणा EE_WRITE_0	0x01
#घोषणा EE_WRITE_1	0x05
#घोषणा EE_DATA_READ	0x08	/* Data from the EEPROM chip. */
#घोषणा EE_ENB		(0x4800 | EE_CS)

/* Delay between EEPROM घड़ी transitions.
   Even at 33Mhz current PCI implementations करोn't overrun the EEPROM घड़ी.
   We add a bus turn-around to insure that this reमुख्यs true. */
#घोषणा eeprom_delay()	ioपढ़ो32(ee_addr)

/* The EEPROM commands include the alway-set leading bit. */
#घोषणा EE_READ_CMD		(6)

/* Note: this routine वापसs extra data bits क्रम size detection. */
पूर्णांक tulip_पढ़ो_eeprom(काष्ठा net_device *dev, पूर्णांक location, पूर्णांक addr_len)
अणु
	पूर्णांक i;
	अचिन्हित retval = 0;
	काष्ठा tulip_निजी *tp = netdev_priv(dev);
	व्योम __iomem *ee_addr = tp->base_addr + CSR9;
	पूर्णांक पढ़ो_cmd = location | (EE_READ_CMD << addr_len);

	/* If location is past the end of what we can address, करोn't
	 * पढ़ो some other location (ie truncate). Just वापस zero.
	 */
	अगर (location > (1 << addr_len) - 1)
		वापस 0;

	ioग_लिखो32(EE_ENB & ~EE_CS, ee_addr);
	ioग_लिखो32(EE_ENB, ee_addr);

	/* Shअगरt the पढ़ो command bits out. */
	क्रम (i = 4 + addr_len; i >= 0; i--) अणु
		लघु dataval = (पढ़ो_cmd & (1 << i)) ? EE_DATA_WRITE : 0;
		ioग_लिखो32(EE_ENB | dataval, ee_addr);
		eeprom_delay();
		ioग_लिखो32(EE_ENB | dataval | EE_SHIFT_CLK, ee_addr);
		eeprom_delay();
		retval = (retval << 1) | ((ioपढ़ो32(ee_addr) & EE_DATA_READ) ? 1 : 0);
	पूर्ण
	ioग_लिखो32(EE_ENB, ee_addr);
	eeprom_delay();

	क्रम (i = 16; i > 0; i--) अणु
		ioग_लिखो32(EE_ENB | EE_SHIFT_CLK, ee_addr);
		eeprom_delay();
		retval = (retval << 1) | ((ioपढ़ो32(ee_addr) & EE_DATA_READ) ? 1 : 0);
		ioग_लिखो32(EE_ENB, ee_addr);
		eeprom_delay();
	पूर्ण

	/* Terminate the EEPROM access. */
	ioग_लिखो32(EE_ENB & ~EE_CS, ee_addr);
	वापस (tp->flags & HAS_SWAPPED_SEEPROM) ? swab16(retval) : retval;
पूर्ण

