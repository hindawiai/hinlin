<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * NFTL mount code with extensive checks
 *
 * Author: Fabrice Bellard (fabrice.bellard@netgem.com)
 * Copyright तऊ 2000 Netgem S.A.
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nftl.h>

#घोषणा SECTORSIZE 512

/* find_boot_record: Find the NFTL Media Header and its Spare copy which contains the
 *	various device inक्रमmation of the NFTL partition and Bad Unit Table. Update
 *	the ReplUnitTable[] table according to the Bad Unit Table. ReplUnitTable[]
 *	is used क्रम management of Erase Unit in other routines in nftl.c and nftlmount.c
 */
अटल पूर्णांक find_boot_record(काष्ठा NFTLrecord *nftl)
अणु
	काष्ठा nftl_uci1 h1;
	अचिन्हित पूर्णांक block, boot_record_count = 0;
	माप_प्रकार retlen;
	u8 buf[SECTORSIZE];
	काष्ठा NFTLMediaHeader *mh = &nftl->MediaHdr;
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	अचिन्हित पूर्णांक i;

        /* Assume logical EraseSize == physical erasesize क्रम starting the scan.
	   We'll sort it out later अगर we find a MediaHeader which says otherwise */
	/* Actually, we won't.  The new DiskOnChip driver has alपढ़ोy scanned
	   the MediaHeader and adjusted the भव erasesize it presents in
	   the mtd device accordingly.  We could even get rid of
	   nftl->EraseSize अगर there were any poपूर्णांक in करोing so. */
	nftl->EraseSize = nftl->mbd.mtd->erasesize;
        nftl->nb_blocks = (u32)nftl->mbd.mtd->size / nftl->EraseSize;

	nftl->MediaUnit = BLOCK_NIL;
	nftl->SpareMediaUnit = BLOCK_NIL;

	/* search क्रम a valid boot record */
	क्रम (block = 0; block < nftl->nb_blocks; block++) अणु
		पूर्णांक ret;

		/* Check क्रम Aन_अंकD header first. Then can whinge अगर it's found but later
		   checks fail */
		ret = mtd_पढ़ो(mtd, block * nftl->EraseSize, SECTORSIZE,
			       &retlen, buf);
		/* We ignore ret in हाल the ECC of the MediaHeader is invalid
		   (which is apparently acceptable) */
		अगर (retlen != SECTORSIZE) अणु
			अटल पूर्णांक warncount = 5;

			अगर (warncount) अणु
				prपूर्णांकk(KERN_WARNING "Block read at 0x%x of mtd%d failed: %d\n",
				       block * nftl->EraseSize, nftl->mbd.mtd->index, ret);
				अगर (!--warncount)
					prपूर्णांकk(KERN_WARNING "Further failures for this block will not be printed\n");
			पूर्ण
			जारी;
		पूर्ण

		अगर (retlen < 6 || स_भेद(buf, "ANAND", 6)) अणु
			/* Aन_अंकD\0 not found. Continue */
#अगर 0
			prपूर्णांकk(KERN_DEBUG "ANAND header not found at 0x%x in mtd%d\n",
			       block * nftl->EraseSize, nftl->mbd.mtd->index);
#पूर्ण_अगर
			जारी;
		पूर्ण

		/* To be safer with BIOS, also use erase mark as discriminant */
		ret = nftl_पढ़ो_oob(mtd, block * nftl->EraseSize +
					 SECTORSIZE + 8, 8, &retlen,
					 (अक्षर *)&h1);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_WARNING "ANAND header found at 0x%x in mtd%d, but OOB data read failed (err %d)\n",
			       block * nftl->EraseSize, nftl->mbd.mtd->index, ret);
			जारी;
		पूर्ण

#अगर 0 /* Some people seem to have devices without ECC or erase marks
	 on the Media Header blocks. There are enough other sanity
	 checks in here that we can probably करो without it.
      */
		अगर (le16_to_cpu(h1.EraseMark | h1.EraseMark1) != ERASE_MARK) अणु
			prपूर्णांकk(KERN_NOTICE "ANAND header found at 0x%x in mtd%d, but erase mark not present (0x%04x,0x%04x instead)\n",
			       block * nftl->EraseSize, nftl->mbd.mtd->index,
			       le16_to_cpu(h1.EraseMark), le16_to_cpu(h1.EraseMark1));
			जारी;
		पूर्ण

		/* Finally reपढ़ो to check ECC */
		ret = mtd->पढ़ो(mtd, block * nftl->EraseSize, SECTORSIZE,
				&retlen, buf);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_NOTICE "ANAND header found at 0x%x in mtd%d, but ECC read failed (err %d)\n",
			       block * nftl->EraseSize, nftl->mbd.mtd->index, ret);
			जारी;
		पूर्ण

		/* Paranoia. Check the Aन_अंकD header is still there after the ECC पढ़ो */
		अगर (स_भेद(buf, "ANAND", 6)) अणु
			prपूर्णांकk(KERN_NOTICE "ANAND header found at 0x%x in mtd%d, but went away on reread!\n",
			       block * nftl->EraseSize, nftl->mbd.mtd->index);
			prपूर्णांकk(KERN_NOTICE "New data are: %6ph\n", buf);
			जारी;
		पूर्ण
#पूर्ण_अगर
		/* OK, we like it. */

		अगर (boot_record_count) अणु
			/* We've alपढ़ोy processed one. So we just check अगर
			   this one is the same as the first one we found */
			अगर (स_भेद(mh, buf, माप(काष्ठा NFTLMediaHeader))) अणु
				prपूर्णांकk(KERN_NOTICE "NFTL Media Headers at 0x%x and 0x%x disagree.\n",
				       nftl->MediaUnit * nftl->EraseSize, block * nftl->EraseSize);
				/* अगर (debug) Prपूर्णांक both side by side */
				अगर (boot_record_count < 2) अणु
					/* We haven't yet seen two real ones */
					वापस -1;
				पूर्ण
				जारी;
			पूर्ण
			अगर (boot_record_count == 1)
				nftl->SpareMediaUnit = block;

			/* Mark this boot record (NFTL MediaHeader) block as reserved */
			nftl->ReplUnitTable[block] = BLOCK_RESERVED;


			boot_record_count++;
			जारी;
		पूर्ण

		/* This is the first we've seen. Copy the media header काष्ठाure पूर्णांकo place */
		स_नकल(mh, buf, माप(काष्ठा NFTLMediaHeader));

		/* Do some sanity checks on it */
#अगर 0
The new DiskOnChip driver scans the MediaHeader itself, and presents a भव
erasesize based on UnitSizeFactor.  So the erasesize we पढ़ो from the mtd
device is alपढ़ोy correct.
		अगर (mh->UnitSizeFactor == 0) अणु
			prपूर्णांकk(KERN_NOTICE "NFTL: UnitSizeFactor 0x00 detected. This violates the spec but we think we know what it means...\n");
		पूर्ण अन्यथा अगर (mh->UnitSizeFactor < 0xfc) अणु
			prपूर्णांकk(KERN_NOTICE "Sorry, we don't support UnitSizeFactor 0x%02x\n",
			       mh->UnitSizeFactor);
			वापस -1;
		पूर्ण अन्यथा अगर (mh->UnitSizeFactor != 0xff) अणु
			prपूर्णांकk(KERN_NOTICE "WARNING: Support for NFTL with UnitSizeFactor 0x%02x is experimental\n",
			       mh->UnitSizeFactor);
			nftl->EraseSize = nftl->mbd.mtd->erasesize << (0xff - mh->UnitSizeFactor);
			nftl->nb_blocks = (u32)nftl->mbd.mtd->size / nftl->EraseSize;
		पूर्ण
#पूर्ण_अगर
		nftl->nb_boot_blocks = le16_to_cpu(mh->FirstPhysicalEUN);
		अगर ((nftl->nb_boot_blocks + 2) >= nftl->nb_blocks) अणु
			prपूर्णांकk(KERN_NOTICE "NFTL Media Header sanity check failed:\n");
			prपूर्णांकk(KERN_NOTICE "nb_boot_blocks (%d) + 2 > nb_blocks (%d)\n",
			       nftl->nb_boot_blocks, nftl->nb_blocks);
			वापस -1;
		पूर्ण

		nftl->numvunits = le32_to_cpu(mh->FormattedSize) / nftl->EraseSize;
		अगर (nftl->numvunits > (nftl->nb_blocks - nftl->nb_boot_blocks - 2)) अणु
			prपूर्णांकk(KERN_NOTICE "NFTL Media Header sanity check failed:\n");
			prपूर्णांकk(KERN_NOTICE "numvunits (%d) > nb_blocks (%d) - nb_boot_blocks(%d) - 2\n",
			       nftl->numvunits, nftl->nb_blocks, nftl->nb_boot_blocks);
			वापस -1;
		पूर्ण

		nftl->mbd.size  = nftl->numvunits * (nftl->EraseSize / SECTORSIZE);

		/* If we're not using the last sectors in the device क्रम some reason,
		   reduce nb_blocks accordingly so we क्रमget they're there */
		nftl->nb_blocks = le16_to_cpu(mh->NumEraseUnits) + le16_to_cpu(mh->FirstPhysicalEUN);

		/* XXX: will be suppressed */
		nftl->lastEUN = nftl->nb_blocks - 1;

		/* memory alloc */
		nftl->EUNtable = kदो_स्मृति_array(nftl->nb_blocks, माप(u16),
					       GFP_KERNEL);
		अगर (!nftl->EUNtable) अणु
			prपूर्णांकk(KERN_NOTICE "NFTL: allocation of EUNtable failed\n");
			वापस -ENOMEM;
		पूर्ण

		nftl->ReplUnitTable = kदो_स्मृति_array(nftl->nb_blocks,
						    माप(u16),
						    GFP_KERNEL);
		अगर (!nftl->ReplUnitTable) अणु
			kमुक्त(nftl->EUNtable);
			prपूर्णांकk(KERN_NOTICE "NFTL: allocation of ReplUnitTable failed\n");
			वापस -ENOMEM;
		पूर्ण

		/* mark the bios blocks (blocks beक्रमe NFTL MediaHeader) as reserved */
		क्रम (i = 0; i < nftl->nb_boot_blocks; i++)
			nftl->ReplUnitTable[i] = BLOCK_RESERVED;
		/* mark all reमुख्यing blocks as potentially containing data */
		क्रम (; i < nftl->nb_blocks; i++) अणु
			nftl->ReplUnitTable[i] = BLOCK_NOTEXPLORED;
		पूर्ण

		/* Mark this boot record (NFTL MediaHeader) block as reserved */
		nftl->ReplUnitTable[block] = BLOCK_RESERVED;

		/* पढ़ो the Bad Erase Unit Table and modअगरy ReplUnitTable[] accordingly */
		क्रम (i = 0; i < nftl->nb_blocks; i++) अणु
#अगर 0
The new DiskOnChip driver alपढ़ोy scanned the bad block table.  Just query it.
			अगर ((i & (SECTORSIZE - 1)) == 0) अणु
				/* पढ़ो one sector क्रम every SECTORSIZE of blocks */
				ret = mtd->पढ़ो(nftl->mbd.mtd,
						block * nftl->EraseSize + i +
						SECTORSIZE, SECTORSIZE,
						&retlen, buf);
				अगर (ret < 0) अणु
					prपूर्णांकk(KERN_NOTICE "Read of bad sector table failed (err %d)\n",
					       ret);
					kमुक्त(nftl->ReplUnitTable);
					kमुक्त(nftl->EUNtable);
					वापस -1;
				पूर्ण
			पूर्ण
			/* mark the Bad Erase Unit as RESERVED in ReplUnitTable */
			अगर (buf[i & (SECTORSIZE - 1)] != 0xff)
				nftl->ReplUnitTable[i] = BLOCK_RESERVED;
#पूर्ण_अगर
			अगर (mtd_block_isbad(nftl->mbd.mtd,
					    i * nftl->EraseSize))
				nftl->ReplUnitTable[i] = BLOCK_RESERVED;
		पूर्ण

		nftl->MediaUnit = block;
		boot_record_count++;

	पूर्ण /* क्रमeach (block) */

	वापस boot_record_count?0:-1;
पूर्ण

अटल पूर्णांक स_भेदb(व्योम *a, पूर्णांक c, पूर्णांक n)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < n; i++) अणु
		अगर (c != ((अचिन्हित अक्षर *)a)[i])
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

/* check_मुक्त_sector: check अगर a मुक्त sector is actually FREE, i.e. All 0xff in data and oob area */
अटल पूर्णांक check_मुक्त_sectors(काष्ठा NFTLrecord *nftl, अचिन्हित पूर्णांक address, पूर्णांक len,
			      पूर्णांक check_oob)
अणु
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	माप_प्रकार retlen;
	पूर्णांक i, ret;
	u8 *buf;

	buf = kदो_स्मृति(SECTORSIZE + mtd->oobsize, GFP_KERNEL);
	अगर (!buf)
		वापस -1;

	ret = -1;
	क्रम (i = 0; i < len; i += SECTORSIZE) अणु
		अगर (mtd_पढ़ो(mtd, address, SECTORSIZE, &retlen, buf))
			जाओ out;
		अगर (स_भेदb(buf, 0xff, SECTORSIZE) != 0)
			जाओ out;

		अगर (check_oob) अणु
			अगर(nftl_पढ़ो_oob(mtd, address, mtd->oobsize,
					 &retlen, &buf[SECTORSIZE]) < 0)
				जाओ out;
			अगर (स_भेदb(buf + SECTORSIZE, 0xff, mtd->oobsize) != 0)
				जाओ out;
		पूर्ण
		address += SECTORSIZE;
	पूर्ण

	ret = 0;

out:
	kमुक्त(buf);
	वापस ret;
पूर्ण

/* NFTL_क्रमmat: क्रमmat a Erase Unit by erasing ALL Erase Zones in the Erase Unit and
 *              Update NFTL metadata. Each erase operation is checked with check_मुक्त_sectors
 *
 * Return: 0 when succeed, -1 on error.
 *
 *  ToDo: 1. Is it necessary to check_मुक्त_sector after erasing ??
 */
पूर्णांक NFTL_क्रमmatblock(काष्ठा NFTLrecord *nftl, पूर्णांक block)
अणु
	माप_प्रकार retlen;
	अचिन्हित पूर्णांक nb_erases, erase_mark;
	काष्ठा nftl_uci1 uci;
	काष्ठा erase_info *instr = &nftl->instr;
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;

	/* Read the Unit Control Inक्रमmation #1 क्रम Wear-Leveling */
	अगर (nftl_पढ़ो_oob(mtd, block * nftl->EraseSize + SECTORSIZE + 8,
			  8, &retlen, (अक्षर *)&uci) < 0)
		जाओ शेष_uci1;

	erase_mark = le16_to_cpu ((uci.EraseMark | uci.EraseMark1));
	अगर (erase_mark != ERASE_MARK) अणु
	शेष_uci1:
		uci.EraseMark = cpu_to_le16(ERASE_MARK);
		uci.EraseMark1 = cpu_to_le16(ERASE_MARK);
		uci.WearInfo = cpu_to_le32(0);
	पूर्ण

	स_रखो(instr, 0, माप(काष्ठा erase_info));

	/* XXX: use async erase पूर्णांकerface, XXX: test वापस code */
	instr->addr = block * nftl->EraseSize;
	instr->len = nftl->EraseSize;
	अगर (mtd_erase(mtd, instr)) अणु
		prपूर्णांकk("Error while formatting block %d\n", block);
		जाओ fail;
	पूर्ण

	/* increase and ग_लिखो Wear-Leveling info */
	nb_erases = le32_to_cpu(uci.WearInfo);
	nb_erases++;

	/* wrap (almost impossible with current flash) or मुक्त block */
	अगर (nb_erases == 0)
		nb_erases = 1;

	/* check the "freeness" of Erase Unit beक्रमe updating metadata
	 * FixMe:  is this check really necessary ? since we have check the
	 *         वापस code after the erase operation.
	 */
	अगर (check_मुक्त_sectors(nftl, instr->addr, nftl->EraseSize, 1) != 0)
		जाओ fail;

	uci.WearInfo = le32_to_cpu(nb_erases);
	अगर (nftl_ग_लिखो_oob(mtd, block * nftl->EraseSize + SECTORSIZE +
			   8, 8, &retlen, (अक्षर *)&uci) < 0)
		जाओ fail;
	वापस 0;
fail:
	/* could not क्रमmat, update the bad block table (caller is responsible
	   क्रम setting the ReplUnitTable to BLOCK_RESERVED on failure) */
	mtd_block_markbad(nftl->mbd.mtd, instr->addr);
	वापस -1;
पूर्ण

/* check_sectors_in_chain: Check that each sector of a Virtual Unit Chain is correct.
 *	Mark as 'IGNORE' each incorrect sector. This check is only करोne अगर the chain
 *	was being folded when NFTL was पूर्णांकerrupted.
 *
 *	The check_मुक्त_sectors in this function is necessary. There is a possible
 *	situation that after writing the Data area, the Block Control Inक्रमmation is
 *	not updated according (due to घातer failure or something) which leaves the block
 *	in an inconsistent state. So we have to check अगर a block is really FREE in this
 *	हाल. */
अटल व्योम check_sectors_in_chain(काष्ठा NFTLrecord *nftl, अचिन्हित पूर्णांक first_block)
अणु
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	अचिन्हित पूर्णांक block, i, status;
	काष्ठा nftl_bci bci;
	पूर्णांक sectors_per_block;
	माप_प्रकार retlen;

	sectors_per_block = nftl->EraseSize / SECTORSIZE;
	block = first_block;
	क्रम (;;) अणु
		क्रम (i = 0; i < sectors_per_block; i++) अणु
			अगर (nftl_पढ़ो_oob(mtd,
					  block * nftl->EraseSize + i * SECTORSIZE,
					  8, &retlen, (अक्षर *)&bci) < 0)
				status = SECTOR_IGNORE;
			अन्यथा
				status = bci.Status | bci.Status1;

			चयन(status) अणु
			हाल SECTOR_FREE:
				/* verअगरy that the sector is really मुक्त. If not, mark
				   as ignore */
				अगर (स_भेदb(&bci, 0xff, 8) != 0 ||
				    check_मुक्त_sectors(nftl, block * nftl->EraseSize + i * SECTORSIZE,
						       SECTORSIZE, 0) != 0) अणु
					prपूर्णांकk("Incorrect free sector %d in block %d: "
					       "marking it as ignored\n",
					       i, block);

					/* sector not मुक्त actually : mark it as SECTOR_IGNORE  */
					bci.Status = SECTOR_IGNORE;
					bci.Status1 = SECTOR_IGNORE;
					nftl_ग_लिखो_oob(mtd, block *
						       nftl->EraseSize +
						       i * SECTORSIZE, 8,
						       &retlen, (अक्षर *)&bci);
				पूर्ण
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण

		/* proceed to next Erase Unit on the chain */
		block = nftl->ReplUnitTable[block];
		अगर (!(block == BLOCK_NIL || block < nftl->nb_blocks))
			prपूर्णांकk("incorrect ReplUnitTable[] : %d\n", block);
		अगर (block == BLOCK_NIL || block >= nftl->nb_blocks)
			अवरोध;
	पूर्ण
पूर्ण

/* calc_chain_length: Walk through a Virtual Unit Chain and estimate chain length */
अटल पूर्णांक calc_chain_length(काष्ठा NFTLrecord *nftl, अचिन्हित पूर्णांक first_block)
अणु
	अचिन्हित पूर्णांक length = 0, block = first_block;

	क्रम (;;) अणु
		length++;
		/* aव्योम infinite loops, although this is guaranteed not to
		   happen because of the previous checks */
		अगर (length >= nftl->nb_blocks) अणु
			prपूर्णांकk("nftl: length too long %d !\n", length);
			अवरोध;
		पूर्ण

		block = nftl->ReplUnitTable[block];
		अगर (!(block == BLOCK_NIL || block < nftl->nb_blocks))
			prपूर्णांकk("incorrect ReplUnitTable[] : %d\n", block);
		अगर (block == BLOCK_NIL || block >= nftl->nb_blocks)
			अवरोध;
	पूर्ण
	वापस length;
पूर्ण

/* क्रमmat_chain: Format an invalid Virtual Unit chain. It मुक्तs all the Erase Units in a
 *	Virtual Unit Chain, i.e. all the units are disconnected.
 *
 *	It is not strictly correct to begin from the first block of the chain because
 *	अगर we stop the code, we may see again a valid chain अगर there was a first_block
 *	flag in a block inside it. But is it really a problem ?
 *
 * FixMe: Figure out what the last statement means. What अगर घातer failure when we are
 *	in the क्रम (;;) loop क्रमmatting blocks ??
 */
अटल व्योम क्रमmat_chain(काष्ठा NFTLrecord *nftl, अचिन्हित पूर्णांक first_block)
अणु
	अचिन्हित पूर्णांक block = first_block, block1;

	prपूर्णांकk("Formatting chain at block %d\n", first_block);

	क्रम (;;) अणु
		block1 = nftl->ReplUnitTable[block];

		prपूर्णांकk("Formatting block %d\n", block);
		अगर (NFTL_क्रमmatblock(nftl, block) < 0) अणु
			/* cannot क्रमmat !!!! Mark it as Bad Unit */
			nftl->ReplUnitTable[block] = BLOCK_RESERVED;
		पूर्ण अन्यथा अणु
			nftl->ReplUnitTable[block] = BLOCK_FREE;
		पूर्ण

		/* जाओ next block on the chain */
		block = block1;

		अगर (!(block == BLOCK_NIL || block < nftl->nb_blocks))
			prपूर्णांकk("incorrect ReplUnitTable[] : %d\n", block);
		अगर (block == BLOCK_NIL || block >= nftl->nb_blocks)
			अवरोध;
	पूर्ण
पूर्ण

/* check_and_mark_मुक्त_block: Verअगरy that a block is मुक्त in the NFTL sense (valid erase mark) or
 *	totally मुक्त (only 0xff).
 *
 * Definition: Free Erase Unit -- A properly erased/क्रमmatted Free Erase Unit should have meet the
 *	following criteria:
 *	1. */
अटल पूर्णांक check_and_mark_मुक्त_block(काष्ठा NFTLrecord *nftl, पूर्णांक block)
अणु
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	काष्ठा nftl_uci1 h1;
	अचिन्हित पूर्णांक erase_mark;
	माप_प्रकार retlen;

	/* check erase mark. */
	अगर (nftl_पढ़ो_oob(mtd, block * nftl->EraseSize + SECTORSIZE + 8, 8,
			  &retlen, (अक्षर *)&h1) < 0)
		वापस -1;

	erase_mark = le16_to_cpu ((h1.EraseMark | h1.EraseMark1));
	अगर (erase_mark != ERASE_MARK) अणु
		/* अगर no erase mark, the block must be totally मुक्त. This is
		   possible in two हालs : empty fileप्रणाली or पूर्णांकerrupted erase (very unlikely) */
		अगर (check_मुक्त_sectors (nftl, block * nftl->EraseSize, nftl->EraseSize, 1) != 0)
			वापस -1;

		/* मुक्त block : ग_लिखो erase mark */
		h1.EraseMark = cpu_to_le16(ERASE_MARK);
		h1.EraseMark1 = cpu_to_le16(ERASE_MARK);
		h1.WearInfo = cpu_to_le32(0);
		अगर (nftl_ग_लिखो_oob(mtd,
				   block * nftl->EraseSize + SECTORSIZE + 8, 8,
				   &retlen, (अक्षर *)&h1) < 0)
			वापस -1;
	पूर्ण अन्यथा अणु
#अगर 0
		/* अगर erase mark present, need to skip it when करोing check */
		क्रम (i = 0; i < nftl->EraseSize; i += SECTORSIZE) अणु
			/* check मुक्त sector */
			अगर (check_मुक्त_sectors (nftl, block * nftl->EraseSize + i,
						SECTORSIZE, 0) != 0)
				वापस -1;

			अगर (nftl_पढ़ो_oob(mtd, block * nftl->EraseSize + i,
					  16, &retlen, buf) < 0)
				वापस -1;
			अगर (i == SECTORSIZE) अणु
				/* skip erase mark */
				अगर (स_भेदb(buf, 0xff, 8))
					वापस -1;
			पूर्ण अन्यथा अणु
				अगर (स_भेदb(buf, 0xff, 16))
					वापस -1;
			पूर्ण
		पूर्ण
#पूर्ण_अगर
	पूर्ण

	वापस 0;
पूर्ण

/* get_fold_mark: Read fold mark from Unit Control Inक्रमmation #2, we use FOLD_MARK_IN_PROGRESS
 *	to indicate that we are in the progression of a Virtual Unit Chain folding. If the UCI #2
 *	is FOLD_MARK_IN_PROGRESS when mounting the NFTL, the (previous) folding process is पूर्णांकerrupted
 *	क्रम some reason. A clean up/check of the VUC is necessary in this हाल.
 *
 * WARNING: वापस 0 अगर पढ़ो error
 */
अटल पूर्णांक get_fold_mark(काष्ठा NFTLrecord *nftl, अचिन्हित पूर्णांक block)
अणु
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	काष्ठा nftl_uci2 uci;
	माप_प्रकार retlen;

	अगर (nftl_पढ़ो_oob(mtd, block * nftl->EraseSize + 2 * SECTORSIZE + 8,
			  8, &retlen, (अक्षर *)&uci) < 0)
		वापस 0;

	वापस le16_to_cpu((uci.FoldMark | uci.FoldMark1));
पूर्ण

पूर्णांक NFTL_mount(काष्ठा NFTLrecord *s)
अणु
	पूर्णांक i;
	अचिन्हित पूर्णांक first_logical_block, logical_block, rep_block, erase_mark;
	अचिन्हित पूर्णांक block, first_block, is_first_block;
	पूर्णांक chain_length, करो_क्रमmat_chain;
	काष्ठा nftl_uci0 h0;
	काष्ठा nftl_uci1 h1;
	काष्ठा mtd_info *mtd = s->mbd.mtd;
	माप_प्रकार retlen;

	/* search क्रम NFTL MediaHeader and Spare NFTL Media Header */
	अगर (find_boot_record(s) < 0) अणु
		prपूर्णांकk("Could not find valid boot record\n");
		वापस -1;
	पूर्ण

	/* init the logical to physical table */
	क्रम (i = 0; i < s->nb_blocks; i++) अणु
		s->EUNtable[i] = BLOCK_NIL;
	पूर्ण

	/* first pass : explore each block chain */
	first_logical_block = 0;
	क्रम (first_block = 0; first_block < s->nb_blocks; first_block++) अणु
		/* अगर the block was not alपढ़ोy explored, we can look at it */
		अगर (s->ReplUnitTable[first_block] == BLOCK_NOTEXPLORED) अणु
			block = first_block;
			chain_length = 0;
			करो_क्रमmat_chain = 0;

			क्रम (;;) अणु
				/* पढ़ो the block header. If error, we क्रमmat the chain */
				अगर (nftl_पढ़ो_oob(mtd,
						  block * s->EraseSize + 8, 8,
						  &retlen, (अक्षर *)&h0) < 0 ||
				    nftl_पढ़ो_oob(mtd,
						  block * s->EraseSize +
						  SECTORSIZE + 8, 8,
						  &retlen, (अक्षर *)&h1) < 0) अणु
					s->ReplUnitTable[block] = BLOCK_NIL;
					करो_क्रमmat_chain = 1;
					अवरोध;
				पूर्ण

				logical_block = le16_to_cpu ((h0.VirtUnitNum | h0.SpareVirtUnitNum));
				rep_block = le16_to_cpu ((h0.ReplUnitNum | h0.SpareReplUnitNum));
				erase_mark = le16_to_cpu ((h1.EraseMark | h1.EraseMark1));

				is_first_block = !(logical_block >> 15);
				logical_block = logical_block & 0x7fff;

				/* invalid/मुक्त block test */
				अगर (erase_mark != ERASE_MARK || logical_block >= s->nb_blocks) अणु
					अगर (chain_length == 0) अणु
						/* अगर not currently in a chain, we can handle it safely */
						अगर (check_and_mark_मुक्त_block(s, block) < 0) अणु
							/* not really मुक्त: क्रमmat it */
							prपूर्णांकk("Formatting block %d\n", block);
							अगर (NFTL_क्रमmatblock(s, block) < 0) अणु
								/* could not क्रमmat: reserve the block */
								s->ReplUnitTable[block] = BLOCK_RESERVED;
							पूर्ण अन्यथा अणु
								s->ReplUnitTable[block] = BLOCK_FREE;
							पूर्ण
						पूर्ण अन्यथा अणु
							/* मुक्त block: mark it */
							s->ReplUnitTable[block] = BLOCK_FREE;
						पूर्ण
						/* directly examine the next block. */
						जाओ examine_ReplUnitTable;
					पूर्ण अन्यथा अणु
						/* the block was in a chain : this is bad. We
						   must क्रमmat all the chain */
						prपूर्णांकk("Block %d: free but referenced in chain %d\n",
						       block, first_block);
						s->ReplUnitTable[block] = BLOCK_NIL;
						करो_क्रमmat_chain = 1;
						अवरोध;
					पूर्ण
				पूर्ण

				/* we accept only first blocks here */
				अगर (chain_length == 0) अणु
					/* this block is not the first block in chain :
					   ignore it, it will be included in a chain
					   later, or marked as not explored */
					अगर (!is_first_block)
						जाओ examine_ReplUnitTable;
					first_logical_block = logical_block;
				पूर्ण अन्यथा अणु
					अगर (logical_block != first_logical_block) अणु
						prपूर्णांकk("Block %d: incorrect logical block: %d expected: %d\n",
						       block, logical_block, first_logical_block);
						/* the chain is incorrect : we must क्रमmat it,
						   but we need to पढ़ो it completely */
						करो_क्रमmat_chain = 1;
					पूर्ण
					अगर (is_first_block) अणु
						/* we accept that a block is marked as first
						   block जबतक being last block in a chain
						   only अगर the chain is being folded */
						अगर (get_fold_mark(s, block) != FOLD_MARK_IN_PROGRESS ||
						    rep_block != 0xffff) अणु
							prपूर्णांकk("Block %d: incorrectly marked as first block in chain\n",
							       block);
							/* the chain is incorrect : we must क्रमmat it,
							   but we need to पढ़ो it completely */
							करो_क्रमmat_chain = 1;
						पूर्ण अन्यथा अणु
							prपूर्णांकk("Block %d: folding in progress - ignoring first block flag\n",
							       block);
						पूर्ण
					पूर्ण
				पूर्ण
				chain_length++;
				अगर (rep_block == 0xffff) अणु
					/* no more blocks after */
					s->ReplUnitTable[block] = BLOCK_NIL;
					अवरोध;
				पूर्ण अन्यथा अगर (rep_block >= s->nb_blocks) अणु
					prपूर्णांकk("Block %d: referencing invalid block %d\n",
					       block, rep_block);
					करो_क्रमmat_chain = 1;
					s->ReplUnitTable[block] = BLOCK_NIL;
					अवरोध;
				पूर्ण अन्यथा अगर (s->ReplUnitTable[rep_block] != BLOCK_NOTEXPLORED) अणु
					/* same problem as previous 'is_first_block' test:
					   we accept that the last block of a chain has
					   the first_block flag set अगर folding is in
					   progress. We handle here the हाल where the
					   last block appeared first */
					अगर (s->ReplUnitTable[rep_block] == BLOCK_NIL &&
					    s->EUNtable[first_logical_block] == rep_block &&
					    get_fold_mark(s, first_block) == FOLD_MARK_IN_PROGRESS) अणु
						/* EUNtable[] will be set after */
						prपूर्णांकk("Block %d: folding in progress - ignoring first block flag\n",
						       rep_block);
						s->ReplUnitTable[block] = rep_block;
						s->EUNtable[first_logical_block] = BLOCK_NIL;
					पूर्ण अन्यथा अणु
						prपूर्णांकk("Block %d: referencing block %d already in another chain\n",
						       block, rep_block);
						/* XXX: should handle correctly fold in progress chains */
						करो_क्रमmat_chain = 1;
						s->ReplUnitTable[block] = BLOCK_NIL;
					पूर्ण
					अवरोध;
				पूर्ण अन्यथा अणु
					/* this is OK */
					s->ReplUnitTable[block] = rep_block;
					block = rep_block;
				पूर्ण
			पूर्ण

			/* the chain was completely explored. Now we can decide
			   what to करो with it */
			अगर (करो_क्रमmat_chain) अणु
				/* invalid chain : क्रमmat it */
				क्रमmat_chain(s, first_block);
			पूर्ण अन्यथा अणु
				अचिन्हित पूर्णांक first_block1, chain_to_क्रमmat, chain_length1;
				पूर्णांक fold_mark;

				/* valid chain : get foldmark */
				fold_mark = get_fold_mark(s, first_block);
				अगर (fold_mark == 0) अणु
					/* cannot get foldmark : क्रमmat the chain */
					prपूर्णांकk("Could read foldmark at block %d\n", first_block);
					क्रमmat_chain(s, first_block);
				पूर्ण अन्यथा अणु
					अगर (fold_mark == FOLD_MARK_IN_PROGRESS)
						check_sectors_in_chain(s, first_block);

					/* now handle the हाल where we find two chains at the
					   same भव address : we select the दीर्घer one,
					   because the लघुer one is the one which was being
					   folded अगर the folding was not करोne in place */
					first_block1 = s->EUNtable[first_logical_block];
					अगर (first_block1 != BLOCK_NIL) अणु
						/* XXX: what to करो अगर same length ? */
						chain_length1 = calc_chain_length(s, first_block1);
						prपूर्णांकk("Two chains at blocks %d (len=%d) and %d (len=%d)\n",
						       first_block1, chain_length1, first_block, chain_length);

						अगर (chain_length >= chain_length1) अणु
							chain_to_क्रमmat = first_block1;
							s->EUNtable[first_logical_block] = first_block;
						पूर्ण अन्यथा अणु
							chain_to_क्रमmat = first_block;
						पूर्ण
						क्रमmat_chain(s, chain_to_क्रमmat);
					पूर्ण अन्यथा अणु
						s->EUNtable[first_logical_block] = first_block;
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	examine_ReplUnitTable:;
	पूर्ण

	/* second pass to क्रमmat unreferenced blocks  and init मुक्त block count */
	s->numमुक्तEUNs = 0;
	s->LastFreeEUN = le16_to_cpu(s->MediaHdr.FirstPhysicalEUN);

	क्रम (block = 0; block < s->nb_blocks; block++) अणु
		अगर (s->ReplUnitTable[block] == BLOCK_NOTEXPLORED) अणु
			prपूर्णांकk("Unreferenced block %d, formatting it\n", block);
			अगर (NFTL_क्रमmatblock(s, block) < 0)
				s->ReplUnitTable[block] = BLOCK_RESERVED;
			अन्यथा
				s->ReplUnitTable[block] = BLOCK_FREE;
		पूर्ण
		अगर (s->ReplUnitTable[block] == BLOCK_FREE) अणु
			s->numमुक्तEUNs++;
			s->LastFreeEUN = block;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
