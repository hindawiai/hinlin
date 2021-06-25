<शैली गुरु>
/*
 * Hermes करोwnload helper.
 *
 * This helper:
 *  - is capable of writing to the अस्थिर area of the hermes device
 *  - is currently not capable of writing to non-अस्थिर areas
 *  - provide helpers to identअगरy and update plugin data
 *  - is not capable of पूर्णांकerpreting a fw image directly. That is up to
 *    the मुख्य card driver.
 *  - deals with Hermes I devices. It can probably be modअगरied to deal
 *    with Hermes II devices
 *
 * Copyright (C) 2007, David Kilroy
 *
 * Plug data code slightly modअगरied from spectrum_cs driver
 *    Copyright (C) 2002-2005 Pavel Roskin <proski@gnu.org>
 * Portions based on inक्रमmation in wl_lkm_718 Agere driver
 *    COPYRIGHT (C) 2001-2004 by Agere Systems Inc. All Rights Reserved
 *
 * The contents of this file are subject to the Mozilla Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License
 * at http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS"
 * basis, WITHOUT WARRANTY OF ANY KIND, either express or implied. See
 * the License क्रम the specअगरic language governing rights and
 * limitations under the License.
 *
 * Alternatively, the contents of this file may be used under the
 * terms of the GNU General Public License version 2 (the "GPL"), in
 * which हाल the provisions of the GPL are applicable instead of the
 * above.  If you wish to allow the use of your version of this file
 * only under the terms of the GPL and not to allow others to use your
 * version of this file under the MPL, indicate your decision by
 * deleting the provisions above and replace them with the notice and
 * other provisions required by the GPL.  If you करो not delete the
 * provisions above, a recipient may use your version of this file
 * under either the MPL or the GPL.
 */

#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश "hermes.h"
#समावेश "hermes_dld.h"

#घोषणा PFX "hermes_dld: "

/* End markers used in dblocks */
#घोषणा PDI_END		0x00000000	/* End of PDA */
#घोषणा BLOCK_END	0xFFFFFFFF	/* Last image block */
#घोषणा TEXT_END	0x1A		/* End of text header */

/*
 * The following काष्ठाures have little-endian fields denoted by
 * the leading underscore.  Don't access them directly - use अंतरभूत
 * functions defined below.
 */

/*
 * The binary image to be करोwnloaded consists of series of data blocks.
 * Each block has the following काष्ठाure.
 */
काष्ठा dblock अणु
	__le32 addr;		/* adapter address where to ग_लिखो the block */
	__le16 len;		/* length of the data only, in bytes */
	अक्षर data[];		/* data to be written */
पूर्ण __packed;

/*
 * Plug Data References are located in the image after the last data
 * block.  They refer to areas in the adapter memory where the plug data
 * items with matching ID should be written.
 */
काष्ठा pdr अणु
	__le32 id;		/* record ID */
	__le32 addr;		/* adapter address where to ग_लिखो the data */
	__le32 len;		/* expected length of the data, in bytes */
	अक्षर next[];		/* next PDR starts here */
पूर्ण __packed;

/*
 * Plug Data Items are located in the EEPROM पढ़ो from the adapter by
 * primary firmware.  They refer to the device-specअगरic data that should
 * be plugged पूर्णांकo the secondary firmware.
 */
काष्ठा pdi अणु
	__le16 len;		/* length of ID and data, in words */
	__le16 id;		/* record ID */
	अक्षर data[];		/* plug data */
पूर्ण __packed;

/*** FW data block access functions ***/

अटल अंतरभूत u32
dblock_addr(स्थिर काष्ठा dblock *blk)
अणु
	वापस le32_to_cpu(blk->addr);
पूर्ण

अटल अंतरभूत u32
dblock_len(स्थिर काष्ठा dblock *blk)
अणु
	वापस le16_to_cpu(blk->len);
पूर्ण

/*** PDR Access functions ***/

अटल अंतरभूत u32
pdr_id(स्थिर काष्ठा pdr *pdr)
अणु
	वापस le32_to_cpu(pdr->id);
पूर्ण

अटल अंतरभूत u32
pdr_addr(स्थिर काष्ठा pdr *pdr)
अणु
	वापस le32_to_cpu(pdr->addr);
पूर्ण

अटल अंतरभूत u32
pdr_len(स्थिर काष्ठा pdr *pdr)
अणु
	वापस le32_to_cpu(pdr->len);
पूर्ण

/*** PDI Access functions ***/

अटल अंतरभूत u32
pdi_id(स्थिर काष्ठा pdi *pdi)
अणु
	वापस le16_to_cpu(pdi->id);
पूर्ण

/* Return length of the data only, in bytes */
अटल अंतरभूत u32
pdi_len(स्थिर काष्ठा pdi *pdi)
अणु
	वापस 2 * (le16_to_cpu(pdi->len) - 1);
पूर्ण

/*** Plug Data Functions ***/

/*
 * Scan PDR क्रम the record with the specअगरied RECORD_ID.
 * If it's not found, वापस शून्य.
 */
अटल स्थिर काष्ठा pdr *
hermes_find_pdr(स्थिर काष्ठा pdr *first_pdr, u32 record_id, स्थिर व्योम *end)
अणु
	स्थिर काष्ठा pdr *pdr = first_pdr;

	end -= माप(काष्ठा pdr);

	जबतक (((व्योम *) pdr <= end) &&
	       (pdr_id(pdr) != PDI_END)) अणु
		/*
		 * PDR area is currently not terminated by PDI_END.
		 * It's followed by CRC records, which have the type
		 * field where PDR has length.  The type can be 0 or 1.
		 */
		अगर (pdr_len(pdr) < 2)
			वापस शून्य;

		/* If the record ID matches, we are करोne */
		अगर (pdr_id(pdr) == record_id)
			वापस pdr;

		pdr = (काष्ठा pdr *) pdr->next;
	पूर्ण
	वापस शून्य;
पूर्ण

/* Scan production data items क्रम a particular entry */
अटल स्थिर काष्ठा pdi *
hermes_find_pdi(स्थिर काष्ठा pdi *first_pdi, u32 record_id, स्थिर व्योम *end)
अणु
	स्थिर काष्ठा pdi *pdi = first_pdi;

	end -= माप(काष्ठा pdi);

	जबतक (((व्योम *) pdi <= end) &&
	       (pdi_id(pdi) != PDI_END)) अणु

		/* If the record ID matches, we are करोne */
		अगर (pdi_id(pdi) == record_id)
			वापस pdi;

		pdi = (काष्ठा pdi *) &pdi->data[pdi_len(pdi)];
	पूर्ण
	वापस शून्य;
पूर्ण

/* Process one Plug Data Item - find corresponding PDR and plug it */
अटल पूर्णांक
hermes_plug_pdi(काष्ठा hermes *hw, स्थिर काष्ठा pdr *first_pdr,
		स्थिर काष्ठा pdi *pdi, स्थिर व्योम *pdr_end)
अणु
	स्थिर काष्ठा pdr *pdr;

	/* Find the PDR corresponding to this PDI */
	pdr = hermes_find_pdr(first_pdr, pdi_id(pdi), pdr_end);

	/* No match is found, safe to ignore */
	अगर (!pdr)
		वापस 0;

	/* Lengths of the data in PDI and PDR must match */
	अगर (pdi_len(pdi) != pdr_len(pdr))
		वापस -EINVAL;

	/* करो the actual plugging */
	hw->ops->program(hw, pdi->data, pdr_addr(pdr), pdi_len(pdi));

	वापस 0;
पूर्ण

/* Parse PDA and ग_लिखो the records पूर्णांकo the adapter
 *
 * Attempt to ग_लिखो every records that is in the specअगरied pda
 * which also has a valid production data record क्रम the firmware.
 */
पूर्णांक hermes_apply_pda(काष्ठा hermes *hw,
		     स्थिर अक्षर *first_pdr,
		     स्थिर व्योम *pdr_end,
		     स्थिर __le16 *pda,
		     स्थिर व्योम *pda_end)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा pdi *pdi;
	स्थिर काष्ठा pdr *pdr;

	pdr = (स्थिर काष्ठा pdr *) first_pdr;
	pda_end -= माप(काष्ठा pdi);

	/* Go through every PDI and plug them पूर्णांकo the adapter */
	pdi = (स्थिर काष्ठा pdi *) (pda + 2);
	जबतक (((व्योम *) pdi <= pda_end) &&
	       (pdi_id(pdi) != PDI_END)) अणु
		ret = hermes_plug_pdi(hw, pdr, pdi, pdr_end);
		अगर (ret)
			वापस ret;

		/* Increment to the next PDI */
		pdi = (स्थिर काष्ठा pdi *) &pdi->data[pdi_len(pdi)];
	पूर्ण
	वापस 0;
पूर्ण

/* Identअगरy the total number of bytes in all blocks
 * including the header data.
 */
माप_प्रकार
hermes_blocks_length(स्थिर अक्षर *first_block, स्थिर व्योम *end)
अणु
	स्थिर काष्ठा dblock *blk = (स्थिर काष्ठा dblock *) first_block;
	पूर्णांक total_len = 0;
	पूर्णांक len;

	end -= माप(*blk);

	/* Skip all blocks to locate Plug Data References
	 * (Spectrum CS) */
	जबतक (((व्योम *) blk <= end) &&
	       (dblock_addr(blk) != BLOCK_END)) अणु
		len = dblock_len(blk);
		total_len += माप(*blk) + len;
		blk = (काष्ठा dblock *) &blk->data[len];
	पूर्ण

	वापस total_len;
पूर्ण

/*** Hermes programming ***/

/* Program the data blocks */
पूर्णांक hermes_program(काष्ठा hermes *hw, स्थिर अक्षर *first_block, स्थिर व्योम *end)
अणु
	स्थिर काष्ठा dblock *blk;
	u32 blkaddr;
	u32 blklen;
	पूर्णांक err = 0;

	blk = (स्थिर काष्ठा dblock *) first_block;

	अगर ((व्योम *) blk > (end - माप(*blk)))
		वापस -EIO;

	blkaddr = dblock_addr(blk);
	blklen = dblock_len(blk);

	जबतक ((blkaddr != BLOCK_END) &&
	       (((व्योम *) blk + blklen) <= end)) अणु
		pr_debug(PFX "Programming block of length %d "
			 "to address 0x%08x\n", blklen, blkaddr);

		err = hw->ops->program(hw, blk->data, blkaddr, blklen);
		अगर (err)
			अवरोध;

		blk = (स्थिर काष्ठा dblock *) &blk->data[blklen];

		अगर ((व्योम *) blk > (end - माप(*blk)))
			वापस -EIO;

		blkaddr = dblock_addr(blk);
		blklen = dblock_len(blk);
	पूर्ण
	वापस err;
पूर्ण

/*** Default plugging data क्रम Hermes I ***/
/* Values from wl_lkm_718/hcf/dhf.c */

#घोषणा DEFINE_DEFAULT_PDR(pid, length, data)				\
अटल स्थिर काष्ठा अणु							\
	__le16 len;							\
	__le16 id;							\
	u8 val[length];							\
पूर्ण __packed शेष_pdr_data_##pid = अणु			\
	cpu_to_le16((माप(शेष_pdr_data_##pid)/			\
				माप(__le16)) - 1),			\
	cpu_to_le16(pid),						\
	data								\
पूर्ण

#घोषणा DEFAULT_PDR(pid) शेष_pdr_data_##pid

/*  HWIF Compatibility */
DEFINE_DEFAULT_PDR(0x0005, 10, "\x00\x00\x06\x00\x01\x00\x01\x00\x01\x00");

/* PPPPSign */
DEFINE_DEFAULT_PDR(0x0108, 4, "\x00\x00\x00\x00");

/* PPPPProf */
DEFINE_DEFAULT_PDR(0x0109, 10, "\x00\x00\x00\x00\x03\x00\x00\x00\x00\x00");

/* Antenna भागersity */
DEFINE_DEFAULT_PDR(0x0150, 2, "\x00\x3F");

/* Modem VCO band Set-up */
DEFINE_DEFAULT_PDR(0x0160, 28,
		   "\x00\x00\x00\x00\x00\x00\x00\x00"
		   "\x00\x00\x00\x00\x00\x00\x00\x00"
		   "\x00\x00\x00\x00\x00\x00\x00\x00"
		   "\x00\x00\x00\x00");

/* Modem Rx Gain Table Values */
DEFINE_DEFAULT_PDR(0x0161, 256,
		   "\x3F\x01\x3F\01\x3F\x01\x3F\x01"
		   "\x3F\x01\x3F\01\x3F\x01\x3F\x01"
		   "\x3F\x01\x3F\01\x3F\x01\x3F\x01"
		   "\x3F\x01\x3F\01\x3F\x01\x3F\x01"
		   "\x3F\x01\x3E\01\x3E\x01\x3D\x01"
		   "\x3D\x01\x3C\01\x3C\x01\x3B\x01"
		   "\x3B\x01\x3A\01\x3A\x01\x39\x01"
		   "\x39\x01\x38\01\x38\x01\x37\x01"
		   "\x37\x01\x36\01\x36\x01\x35\x01"
		   "\x35\x01\x34\01\x34\x01\x33\x01"
		   "\x33\x01\x32\x01\x32\x01\x31\x01"
		   "\x31\x01\x30\x01\x30\x01\x7B\x01"
		   "\x7B\x01\x7A\x01\x7A\x01\x79\x01"
		   "\x79\x01\x78\x01\x78\x01\x77\x01"
		   "\x77\x01\x76\x01\x76\x01\x75\x01"
		   "\x75\x01\x74\x01\x74\x01\x73\x01"
		   "\x73\x01\x72\x01\x72\x01\x71\x01"
		   "\x71\x01\x70\x01\x70\x01\x68\x01"
		   "\x68\x01\x67\x01\x67\x01\x66\x01"
		   "\x66\x01\x65\x01\x65\x01\x57\x01"
		   "\x57\x01\x56\x01\x56\x01\x55\x01"
		   "\x55\x01\x54\x01\x54\x01\x53\x01"
		   "\x53\x01\x52\x01\x52\x01\x51\x01"
		   "\x51\x01\x50\x01\x50\x01\x48\x01"
		   "\x48\x01\x47\x01\x47\x01\x46\x01"
		   "\x46\x01\x45\x01\x45\x01\x44\x01"
		   "\x44\x01\x43\x01\x43\x01\x42\x01"
		   "\x42\x01\x41\x01\x41\x01\x40\x01"
		   "\x40\x01\x40\x01\x40\x01\x40\x01"
		   "\x40\x01\x40\x01\x40\x01\x40\x01"
		   "\x40\x01\x40\x01\x40\x01\x40\x01"
		   "\x40\x01\x40\x01\x40\x01\x40\x01");

/* Write PDA according to certain rules.
 *
 * For every production data record, look क्रम a previous setting in
 * the pda, and use that.
 *
 * For certain records, use शेषs अगर they are not found in pda.
 */
पूर्णांक hermes_apply_pda_with_शेषs(काष्ठा hermes *hw,
				   स्थिर अक्षर *first_pdr,
				   स्थिर व्योम *pdr_end,
				   स्थिर __le16 *pda,
				   स्थिर व्योम *pda_end)
अणु
	स्थिर काष्ठा pdr *pdr = (स्थिर काष्ठा pdr *) first_pdr;
	स्थिर काष्ठा pdi *first_pdi = (स्थिर काष्ठा pdi *) &pda[2];
	स्थिर काष्ठा pdi *pdi;
	स्थिर काष्ठा pdi *शेष_pdi = शून्य;
	स्थिर काष्ठा pdi *outकरोor_pdi;
	पूर्णांक record_id;

	pdr_end -= माप(काष्ठा pdr);

	जबतक (((व्योम *) pdr <= pdr_end) &&
	       (pdr_id(pdr) != PDI_END)) अणु
		/*
		 * For spectrum_cs firmwares,
		 * PDR area is currently not terminated by PDI_END.
		 * It's followed by CRC records, which have the type
		 * field where PDR has length.  The type can be 0 or 1.
		 */
		अगर (pdr_len(pdr) < 2)
			अवरोध;
		record_id = pdr_id(pdr);

		pdi = hermes_find_pdi(first_pdi, record_id, pda_end);
		अगर (pdi)
			pr_debug(PFX "Found record 0x%04x at %p\n",
				 record_id, pdi);

		चयन (record_id) अणु
		हाल 0x110: /* Modem REFDAC values */
		हाल 0x120: /* Modem VGDAC values */
			outकरोor_pdi = hermes_find_pdi(first_pdi, record_id + 1,
						      pda_end);
			शेष_pdi = शून्य;
			अगर (outकरोor_pdi) अणु
				pdi = outकरोor_pdi;
				pr_debug(PFX
					 "Using outdoor record 0x%04x at %p\n",
					 record_id + 1, pdi);
			पूर्ण
			अवरोध;
		हाल 0x5: /*  HWIF Compatibility */
			शेष_pdi = (काष्ठा pdi *) &DEFAULT_PDR(0x0005);
			अवरोध;
		हाल 0x108: /* PPPPSign */
			शेष_pdi = (काष्ठा pdi *) &DEFAULT_PDR(0x0108);
			अवरोध;
		हाल 0x109: /* PPPPProf */
			शेष_pdi = (काष्ठा pdi *) &DEFAULT_PDR(0x0109);
			अवरोध;
		हाल 0x150: /* Antenna भागersity */
			शेष_pdi = (काष्ठा pdi *) &DEFAULT_PDR(0x0150);
			अवरोध;
		हाल 0x160: /* Modem VCO band Set-up */
			शेष_pdi = (काष्ठा pdi *) &DEFAULT_PDR(0x0160);
			अवरोध;
		हाल 0x161: /* Modem Rx Gain Table Values */
			शेष_pdi = (काष्ठा pdi *) &DEFAULT_PDR(0x0161);
			अवरोध;
		शेष:
			शेष_pdi = शून्य;
			अवरोध;
		पूर्ण
		अगर (!pdi && शेष_pdi) अणु
			/* Use शेष */
			pdi = शेष_pdi;
			pr_debug(PFX "Using default record 0x%04x at %p\n",
				 record_id, pdi);
		पूर्ण

		अगर (pdi) अणु
			/* Lengths of the data in PDI and PDR must match */
			अगर ((pdi_len(pdi) == pdr_len(pdr)) &&
			    ((व्योम *) pdi->data + pdi_len(pdi) < pda_end)) अणु
				/* करो the actual plugging */
				hw->ops->program(hw, pdi->data, pdr_addr(pdr),
						 pdi_len(pdi));
			पूर्ण
		पूर्ण

		pdr++;
	पूर्ण
	वापस 0;
पूर्ण
