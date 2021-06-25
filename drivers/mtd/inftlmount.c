<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inftlmount.c -- INFTL mount code with extensive checks.
 *
 * Author: Greg Ungerer (gerg@snapgear.com)
 * Copyright तऊ 2002-2003, Greg Ungerer (gerg@snapgear.com)
 *
 * Based heavily on the nftlmount.c code which is:
 * Author: Fabrice Bellard (fabrice.bellard@netgem.com)
 * Copyright तऊ 2000 Netgem S.A.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nftl.h>
#समावेश <linux/mtd/inftl.h>

/*
 * find_boot_record: Find the INFTL Media Header and its Spare copy which
 *	contains the various device inक्रमmation of the INFTL partition and
 *	Bad Unit Table. Update the PUtable[] table according to the Bad
 *	Unit Table. PUtable[] is used क्रम management of Erase Unit in
 *	other routines in inftlcore.c and inftlmount.c.
 */
अटल पूर्णांक find_boot_record(काष्ठा INFTLrecord *inftl)
अणु
	काष्ठा inftl_unittail h1;
	//काष्ठा inftl_oob oob;
	अचिन्हित पूर्णांक i, block;
	u8 buf[SECTORSIZE];
	काष्ठा INFTLMediaHeader *mh = &inftl->MediaHdr;
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	काष्ठा INFTLPartition *ip;
	माप_प्रकार retlen;

	pr_debug("INFTL: find_boot_record(inftl=%p)\n", inftl);

        /*
	 * Assume logical EraseSize == physical erasesize क्रम starting the
	 * scan. We'll sort it out later अगर we find a MediaHeader which says
	 * otherwise.
	 */
	inftl->EraseSize = inftl->mbd.mtd->erasesize;
        inftl->nb_blocks = (u32)inftl->mbd.mtd->size / inftl->EraseSize;

	inftl->MediaUnit = BLOCK_NIL;

	/* Search क्रम a valid boot record */
	क्रम (block = 0; block < inftl->nb_blocks; block++) अणु
		पूर्णांक ret;

		/*
		 * Check क्रम Bन_अंकD header first. Then whinge अगर it's found
		 * but later checks fail.
		 */
		ret = mtd_पढ़ो(mtd, block * inftl->EraseSize, SECTORSIZE,
			       &retlen, buf);
		/* We ignore ret in हाल the ECC of the MediaHeader is invalid
		   (which is apparently acceptable) */
		अगर (retlen != SECTORSIZE) अणु
			अटल पूर्णांक warncount = 5;

			अगर (warncount) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: block read at 0x%x "
					"of mtd%d failed: %d\n",
					block * inftl->EraseSize,
					inftl->mbd.mtd->index, ret);
				अगर (!--warncount)
					prपूर्णांकk(KERN_WARNING "INFTL: further "
						"failures for this block will "
						"not be printed\n");
			पूर्ण
			जारी;
		पूर्ण

		अगर (retlen < 6 || स_भेद(buf, "BNAND", 6)) अणु
			/* Bन_अंकD\0 not found. Continue */
			जारी;
		पूर्ण

		/* To be safer with BIOS, also use erase mark as discriminant */
		ret = inftl_पढ़ो_oob(mtd,
				     block * inftl->EraseSize + SECTORSIZE + 8,
				     8, &retlen,(अक्षर *)&h1);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: ANAND header found at "
				"0x%x in mtd%d, but OOB data read failed "
				"(err %d)\n", block * inftl->EraseSize,
				inftl->mbd.mtd->index, ret);
			जारी;
		पूर्ण


		/*
		 * This is the first we've seen.
		 * Copy the media header काष्ठाure पूर्णांकo place.
		 */
		स_नकल(mh, buf, माप(काष्ठा INFTLMediaHeader));

		/* Read the spare media header at offset 4096 */
		mtd_पढ़ो(mtd, block * inftl->EraseSize + 4096, SECTORSIZE,
			 &retlen, buf);
		अगर (retlen != SECTORSIZE) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: Unable to read spare "
			       "Media Header\n");
			वापस -1;
		पूर्ण
		/* Check अगर this one is the same as the first one we found. */
		अगर (स_भेद(mh, buf, माप(काष्ठा INFTLMediaHeader))) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: Primary and spare Media "
			       "Headers disagree.\n");
			वापस -1;
		पूर्ण

		mh->NoOfBootImageBlocks = le32_to_cpu(mh->NoOfBootImageBlocks);
		mh->NoOfBinaryPartitions = le32_to_cpu(mh->NoOfBinaryPartitions);
		mh->NoOfBDTLPartitions = le32_to_cpu(mh->NoOfBDTLPartitions);
		mh->BlockMultiplierBits = le32_to_cpu(mh->BlockMultiplierBits);
		mh->FormatFlags = le32_to_cpu(mh->FormatFlags);
		mh->PercentUsed = le32_to_cpu(mh->PercentUsed);

		pr_debug("INFTL: Media Header ->\n"
			 "    bootRecordID          = %s\n"
			 "    NoOfBootImageBlocks   = %d\n"
			 "    NoOfBinaryPartitions  = %d\n"
			 "    NoOfBDTLPartitions    = %d\n"
			 "    BlockMultiplierBits   = %d\n"
			 "    FormatFlgs            = %d\n"
			 "    OsakVersion           = 0x%x\n"
			 "    PercentUsed           = %d\n",
			 mh->bootRecordID, mh->NoOfBootImageBlocks,
			 mh->NoOfBinaryPartitions,
			 mh->NoOfBDTLPartitions,
			 mh->BlockMultiplierBits, mh->FormatFlags,
			 mh->OsakVersion, mh->PercentUsed);

		अगर (mh->NoOfBDTLPartitions == 0) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: Media Header sanity check "
				"failed: NoOfBDTLPartitions (%d) == 0, "
				"must be at least 1\n", mh->NoOfBDTLPartitions);
			वापस -1;
		पूर्ण

		अगर ((mh->NoOfBDTLPartitions + mh->NoOfBinaryPartitions) > 4) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: Media Header sanity check "
				"failed: Total Partitions (%d) > 4, "
				"BDTL=%d Binary=%d\n", mh->NoOfBDTLPartitions +
				mh->NoOfBinaryPartitions,
				mh->NoOfBDTLPartitions,
				mh->NoOfBinaryPartitions);
			वापस -1;
		पूर्ण

		अगर (mh->BlockMultiplierBits > 1) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: sorry, we don't support "
				"UnitSizeFactor 0x%02x\n",
				mh->BlockMultiplierBits);
			वापस -1;
		पूर्ण अन्यथा अगर (mh->BlockMultiplierBits == 1) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: support for INFTL with "
				"UnitSizeFactor 0x%02x is experimental\n",
				mh->BlockMultiplierBits);
			inftl->EraseSize = inftl->mbd.mtd->erasesize <<
				mh->BlockMultiplierBits;
			inftl->nb_blocks = (u32)inftl->mbd.mtd->size / inftl->EraseSize;
			block >>= mh->BlockMultiplierBits;
		पूर्ण

		/* Scan the partitions */
		क्रम (i = 0; (i < 4); i++) अणु
			ip = &mh->Partitions[i];
			ip->भवUnits = le32_to_cpu(ip->भवUnits);
			ip->firstUnit = le32_to_cpu(ip->firstUnit);
			ip->lastUnit = le32_to_cpu(ip->lastUnit);
			ip->flags = le32_to_cpu(ip->flags);
			ip->spareUnits = le32_to_cpu(ip->spareUnits);
			ip->Reserved0 = le32_to_cpu(ip->Reserved0);

			pr_debug("    PARTITION[%d] ->\n"
				 "        virtualUnits    = %d\n"
				 "        firstUnit       = %d\n"
				 "        lastUnit        = %d\n"
				 "        flags           = 0x%x\n"
				 "        spareUnits      = %d\n",
				 i, ip->भवUnits, ip->firstUnit,
				 ip->lastUnit, ip->flags,
				 ip->spareUnits);

			अगर (ip->Reserved0 != ip->firstUnit) अणु
				काष्ठा erase_info *instr = &inftl->instr;

				/*
				 * 	Most likely this is using the
				 * 	unकरोcumented qiuck mount feature.
				 * 	We करोn't support that, we will need
				 * 	to erase the hidden block क्रम full
				 * 	compatibility.
				 */
				instr->addr = ip->Reserved0 * inftl->EraseSize;
				instr->len = inftl->EraseSize;
				mtd_erase(mtd, instr);
			पूर्ण
			अगर ((ip->lastUnit - ip->firstUnit + 1) < ip->भवUnits) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: Media Header "
					"Partition %d sanity check failed\n"
					"    firstUnit %d : lastUnit %d  >  "
					"virtualUnits %d\n", i, ip->lastUnit,
					ip->firstUnit, ip->Reserved0);
				वापस -1;
			पूर्ण
			अगर (ip->Reserved1 != 0) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: Media Header "
					"Partition %d sanity check failed: "
					"Reserved1 %d != 0\n",
					i, ip->Reserved1);
				वापस -1;
			पूर्ण

			अगर (ip->flags & INFTL_BDTL)
				अवरोध;
		पूर्ण

		अगर (i >= 4) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: Media Header Partition "
				"sanity check failed:\n       No partition "
				"marked as Disk Partition\n");
			वापस -1;
		पूर्ण

		inftl->nb_boot_blocks = ip->firstUnit;
		inftl->numvunits = ip->भवUnits;
		अगर (inftl->numvunits > (inftl->nb_blocks -
		    inftl->nb_boot_blocks - 2)) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: Media Header sanity check "
				"failed:\n        numvunits (%d) > nb_blocks "
				"(%d) - nb_boot_blocks(%d) - 2\n",
				inftl->numvunits, inftl->nb_blocks,
				inftl->nb_boot_blocks);
			वापस -1;
		पूर्ण

		inftl->mbd.size  = inftl->numvunits *
			(inftl->EraseSize / SECTORSIZE);

		/*
		 * Block count is set to last used EUN (we won't need to keep
		 * any meta-data past that poपूर्णांक).
		 */
		inftl->firstEUN = ip->firstUnit;
		inftl->lastEUN = ip->lastUnit;
		inftl->nb_blocks = ip->lastUnit + 1;

		/* Memory alloc */
		inftl->PUtable = kदो_स्मृति_array(inftl->nb_blocks, माप(u16),
					       GFP_KERNEL);
		अगर (!inftl->PUtable) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: allocation of PUtable "
				"failed (%zd bytes)\n",
				inftl->nb_blocks * माप(u16));
			वापस -ENOMEM;
		पूर्ण

		inftl->VUtable = kदो_स्मृति_array(inftl->nb_blocks, माप(u16),
					       GFP_KERNEL);
		अगर (!inftl->VUtable) अणु
			kमुक्त(inftl->PUtable);
			prपूर्णांकk(KERN_WARNING "INFTL: allocation of VUtable "
				"failed (%zd bytes)\n",
				inftl->nb_blocks * माप(u16));
			वापस -ENOMEM;
		पूर्ण

		/* Mark the blocks beक्रमe INFTL MediaHeader as reserved */
		क्रम (i = 0; i < inftl->nb_boot_blocks; i++)
			inftl->PUtable[i] = BLOCK_RESERVED;
		/* Mark all reमुख्यing blocks as potentially containing data */
		क्रम (; i < inftl->nb_blocks; i++)
			inftl->PUtable[i] = BLOCK_NOTEXPLORED;

		/* Mark this boot record (NFTL MediaHeader) block as reserved */
		inftl->PUtable[block] = BLOCK_RESERVED;

		/* Read Bad Erase Unit Table and modअगरy PUtable[] accordingly */
		क्रम (i = 0; i < inftl->nb_blocks; i++) अणु
			पूर्णांक physblock;
			/* If any of the physical eraseblocks are bad, करोn't
			   use the unit. */
			क्रम (physblock = 0; physblock < inftl->EraseSize; physblock += inftl->mbd.mtd->erasesize) अणु
				अगर (mtd_block_isbad(inftl->mbd.mtd,
						    i * inftl->EraseSize + physblock))
					inftl->PUtable[i] = BLOCK_RESERVED;
			पूर्ण
		पूर्ण

		inftl->MediaUnit = block;
		वापस 0;
	पूर्ण

	/* Not found. */
	वापस -1;
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

/*
 * check_मुक्त_sector: check अगर a मुक्त sector is actually FREE,
 *	i.e. All 0xff in data and oob area.
 */
अटल पूर्णांक check_मुक्त_sectors(काष्ठा INFTLrecord *inftl, अचिन्हित पूर्णांक address,
	पूर्णांक len, पूर्णांक check_oob)
अणु
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
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
			अगर(inftl_पढ़ो_oob(mtd, address, mtd->oobsize,
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

/*
 * INFTL_क्रमmat: क्रमmat a Erase Unit by erasing ALL Erase Zones in the Erase
 *		 Unit and Update INFTL metadata. Each erase operation is
 *		 checked with check_मुक्त_sectors.
 *
 * Return: 0 when succeed, -1 on error.
 *
 * ToDo: 1. Is it necessary to check_मुक्त_sector after erasing ??
 */
पूर्णांक INFTL_क्रमmatblock(काष्ठा INFTLrecord *inftl, पूर्णांक block)
अणु
	माप_प्रकार retlen;
	काष्ठा inftl_unittail uci;
	काष्ठा erase_info *instr = &inftl->instr;
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	पूर्णांक physblock;

	pr_debug("INFTL: INFTL_formatblock(inftl=%p,block=%d)\n", inftl, block);

	स_रखो(instr, 0, माप(काष्ठा erase_info));

	/* FIXME: Shouldn't we be setting the 'discarded' flag to zero
	   _first_? */

	/* Use async erase पूर्णांकerface, test वापस code */
	instr->addr = block * inftl->EraseSize;
	instr->len = inftl->mbd.mtd->erasesize;
	/* Erase one physical eraseblock at a समय, even though the न_अंकD api
	   allows us to group them.  This way we अगर we have a failure, we can
	   mark only the failed block in the bbt. */
	क्रम (physblock = 0; physblock < inftl->EraseSize;
	     physblock += instr->len, instr->addr += instr->len) अणु
		पूर्णांक ret;

		ret = mtd_erase(inftl->mbd.mtd, instr);
		अगर (ret) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: error while formatting block %d\n",
				block);
			जाओ fail;
		पूर्ण

		/*
		 * Check the "freeness" of Erase Unit beक्रमe updating metadata.
		 * FixMe: is this check really necessary? Since we have check
		 * the वापस code after the erase operation.
		 */
		अगर (check_मुक्त_sectors(inftl, instr->addr, instr->len, 1) != 0)
			जाओ fail;
	पूर्ण

	uci.EraseMark = cpu_to_le16(ERASE_MARK);
	uci.EraseMark1 = cpu_to_le16(ERASE_MARK);
	uci.Reserved[0] = 0;
	uci.Reserved[1] = 0;
	uci.Reserved[2] = 0;
	uci.Reserved[3] = 0;
	instr->addr = block * inftl->EraseSize + SECTORSIZE * 2;
	अगर (inftl_ग_लिखो_oob(mtd, instr->addr + 8, 8, &retlen, (अक्षर *)&uci) < 0)
		जाओ fail;
	वापस 0;
fail:
	/* could not क्रमmat, update the bad block table (caller is responsible
	   क्रम setting the PUtable to BLOCK_RESERVED on failure) */
	mtd_block_markbad(inftl->mbd.mtd, instr->addr);
	वापस -1;
पूर्ण

/*
 * क्रमmat_chain: Format an invalid Virtual Unit chain. It मुक्तs all the Erase
 *	Units in a Virtual Unit Chain, i.e. all the units are disconnected.
 *
 *	Since the chain is invalid then we will have to erase it from its
 *	head (normally क्रम INFTL we go from the oldest). But अगर it has a
 *	loop then there is no oldest...
 */
अटल व्योम क्रमmat_chain(काष्ठा INFTLrecord *inftl, अचिन्हित पूर्णांक first_block)
अणु
	अचिन्हित पूर्णांक block = first_block, block1;

	prपूर्णांकk(KERN_WARNING "INFTL: formatting chain at block %d\n",
		first_block);

	क्रम (;;) अणु
		block1 = inftl->PUtable[block];

		prपूर्णांकk(KERN_WARNING "INFTL: formatting block %d\n", block);
		अगर (INFTL_क्रमmatblock(inftl, block) < 0) अणु
			/*
			 * Cannot क्रमmat !!!! Mark it as Bad Unit,
			 */
			inftl->PUtable[block] = BLOCK_RESERVED;
		पूर्ण अन्यथा अणु
			inftl->PUtable[block] = BLOCK_FREE;
		पूर्ण

		/* Goto next block on the chain */
		block = block1;

		अगर (block == BLOCK_NIL || block >= inftl->lastEUN)
			अवरोध;
	पूर्ण
पूर्ण

व्योम INFTL_dumptables(काष्ठा INFTLrecord *s)
अणु
	पूर्णांक i;

	pr_debug("-------------------------------------------"
		"----------------------------------\n");

	pr_debug("VUtable[%d] ->", s->nb_blocks);
	क्रम (i = 0; i < s->nb_blocks; i++) अणु
		अगर ((i % 8) == 0)
			pr_debug("\n%04x: ", i);
		pr_debug("%04x ", s->VUtable[i]);
	पूर्ण

	pr_debug("\n-------------------------------------------"
		"----------------------------------\n");

	pr_debug("PUtable[%d-%d=%d] ->", s->firstEUN, s->lastEUN, s->nb_blocks);
	क्रम (i = 0; i <= s->lastEUN; i++) अणु
		अगर ((i % 8) == 0)
			pr_debug("\n%04x: ", i);
		pr_debug("%04x ", s->PUtable[i]);
	पूर्ण

	pr_debug("\n-------------------------------------------"
		"----------------------------------\n");

	pr_debug("INFTL ->\n"
		"  EraseSize       = %d\n"
		"  h/s/c           = %d/%d/%d\n"
		"  numvunits       = %d\n"
		"  firstEUN        = %d\n"
		"  lastEUN         = %d\n"
		"  numfreeEUNs     = %d\n"
		"  LastFreeEUN     = %d\n"
		"  nb_blocks       = %d\n"
		"  nb_boot_blocks  = %d",
		s->EraseSize, s->heads, s->sectors, s->cylinders,
		s->numvunits, s->firstEUN, s->lastEUN, s->numमुक्तEUNs,
		s->LastFreeEUN, s->nb_blocks, s->nb_boot_blocks);

	pr_debug("\n-------------------------------------------"
		"----------------------------------\n");
पूर्ण

व्योम INFTL_dumpVUchains(काष्ठा INFTLrecord *s)
अणु
	पूर्णांक logical, block, i;

	pr_debug("-------------------------------------------"
		"----------------------------------\n");

	pr_debug("INFTL Virtual Unit Chains:\n");
	क्रम (logical = 0; logical < s->nb_blocks; logical++) अणु
		block = s->VUtable[logical];
		अगर (block >= s->nb_blocks)
			जारी;
		pr_debug("  LOGICAL %d --> %d ", logical, block);
		क्रम (i = 0; i < s->nb_blocks; i++) अणु
			अगर (s->PUtable[block] == BLOCK_NIL)
				अवरोध;
			block = s->PUtable[block];
			pr_debug("%d ", block);
		पूर्ण
		pr_debug("\n");
	पूर्ण

	pr_debug("-------------------------------------------"
		"----------------------------------\n");
पूर्ण

पूर्णांक INFTL_mount(काष्ठा INFTLrecord *s)
अणु
	काष्ठा mtd_info *mtd = s->mbd.mtd;
	अचिन्हित पूर्णांक block, first_block, prev_block, last_block;
	अचिन्हित पूर्णांक first_logical_block, logical_block, erase_mark;
	पूर्णांक chain_length, करो_क्रमmat_chain;
	काष्ठा inftl_unithead1 h0;
	काष्ठा inftl_unittail h1;
	माप_प्रकार retlen;
	पूर्णांक i;
	u8 *ANACtable, ANAC;

	pr_debug("INFTL: INFTL_mount(inftl=%p)\n", s);

	/* Search क्रम INFTL MediaHeader and Spare INFTL Media Header */
	अगर (find_boot_record(s) < 0) अणु
		prपूर्णांकk(KERN_WARNING "INFTL: could not find valid boot record?\n");
		वापस -ENXIO;
	पूर्ण

	/* Init the logical to physical table */
	क्रम (i = 0; i < s->nb_blocks; i++)
		s->VUtable[i] = BLOCK_NIL;

	logical_block = block = BLOCK_NIL;

	/* Temporary buffer to store ANAC numbers. */
	ANACtable = kसुस्मृति(s->nb_blocks, माप(u8), GFP_KERNEL);
	अगर (!ANACtable) अणु
		prपूर्णांकk(KERN_WARNING "INFTL: allocation of ANACtable "
				"failed (%zd bytes)\n",
				s->nb_blocks * माप(u8));
		वापस -ENOMEM;
	पूर्ण

	/*
	 * First pass is to explore each physical unit, and स्थिरruct the
	 * भव chains that exist (newest physical unit goes पूर्णांकo VUtable).
	 * Any block that is in any way invalid will be left in the
	 * NOTEXPLORED state. Then at the end we will try to क्रमmat it and
	 * mark it as मुक्त.
	 */
	pr_debug("INFTL: pass 1, explore each unit\n");
	क्रम (first_block = s->firstEUN; first_block <= s->lastEUN; first_block++) अणु
		अगर (s->PUtable[first_block] != BLOCK_NOTEXPLORED)
			जारी;

		करो_क्रमmat_chain = 0;
		first_logical_block = BLOCK_NIL;
		last_block = BLOCK_NIL;
		block = first_block;

		क्रम (chain_length = 0; ; chain_length++) अणु

			अगर ((chain_length == 0) &&
			    (s->PUtable[block] != BLOCK_NOTEXPLORED)) अणु
				/* Nothing to करो here, onto next block */
				अवरोध;
			पूर्ण

			अगर (inftl_पढ़ो_oob(mtd, block * s->EraseSize + 8,
					   8, &retlen, (अक्षर *)&h0) < 0 ||
			    inftl_पढ़ो_oob(mtd, block * s->EraseSize +
					   2 * SECTORSIZE + 8, 8, &retlen,
					   (अक्षर *)&h1) < 0) अणु
				/* Should never happen? */
				करो_क्रमmat_chain++;
				अवरोध;
			पूर्ण

			logical_block = le16_to_cpu(h0.भवUnitNo);
			prev_block = le16_to_cpu(h0.prevUnitNo);
			erase_mark = le16_to_cpu((h1.EraseMark | h1.EraseMark1));
			ANACtable[block] = h0.ANAC;

			/* Previous block is relative to start of Partition */
			अगर (prev_block < s->nb_blocks)
				prev_block += s->firstEUN;

			/* Alपढ़ोy explored partial chain? */
			अगर (s->PUtable[block] != BLOCK_NOTEXPLORED) अणु
				/* Check अगर chain क्रम this logical */
				अगर (logical_block == first_logical_block) अणु
					अगर (last_block != BLOCK_NIL)
						s->PUtable[last_block] = block;
				पूर्ण
				अवरोध;
			पूर्ण

			/* Check क्रम invalid block */
			अगर (erase_mark != ERASE_MARK) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: corrupt block %d "
					"in chain %d, chain length %d, erase "
					"mark 0x%x?\n", block, first_block,
					chain_length, erase_mark);
				/*
				 * Assume end of chain, probably incomplete
				 * fold/erase...
				 */
				अगर (chain_length == 0)
					करो_क्रमmat_chain++;
				अवरोध;
			पूर्ण

			/* Check क्रम it being मुक्त alपढ़ोy then... */
			अगर ((logical_block == BLOCK_FREE) ||
			    (logical_block == BLOCK_NIL)) अणु
				s->PUtable[block] = BLOCK_FREE;
				अवरोध;
			पूर्ण

			/* Sanity checks on block numbers */
			अगर ((logical_block >= s->nb_blocks) ||
			    ((prev_block >= s->nb_blocks) &&
			     (prev_block != BLOCK_NIL))) अणु
				अगर (chain_length > 0) अणु
					prपूर्णांकk(KERN_WARNING "INFTL: corrupt "
						"block %d in chain %d?\n",
						block, first_block);
					करो_क्रमmat_chain++;
				पूर्ण
				अवरोध;
			पूर्ण

			अगर (first_logical_block == BLOCK_NIL) अणु
				first_logical_block = logical_block;
			पूर्ण अन्यथा अणु
				अगर (first_logical_block != logical_block) अणु
					/* Normal क्रम folded chain... */
					अवरोध;
				पूर्ण
			पूर्ण

			/*
			 * Current block is valid, so अगर we followed a भव
			 * chain to get here then we can set the previous
			 * block poपूर्णांकer in our PUtable now. Then move onto
			 * the previous block in the chain.
			 */
			s->PUtable[block] = BLOCK_NIL;
			अगर (last_block != BLOCK_NIL)
				s->PUtable[last_block] = block;
			last_block = block;
			block = prev_block;

			/* Check क्रम end of chain */
			अगर (block == BLOCK_NIL)
				अवरोध;

			/* Validate next block beक्रमe following it... */
			अगर (block > s->lastEUN) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: invalid previous "
					"block %d in chain %d?\n", block,
					first_block);
				करो_क्रमmat_chain++;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (करो_क्रमmat_chain) अणु
			क्रमmat_chain(s, first_block);
			जारी;
		पूर्ण

		/*
		 * Looks like a valid chain then. It may not really be the
		 * newest block in the chain, but it is the newest we have
		 * found so far. We might update it in later iterations of
		 * this loop अगर we find something newer.
		 */
		s->VUtable[first_logical_block] = first_block;
		logical_block = BLOCK_NIL;
	पूर्ण

	INFTL_dumptables(s);

	/*
	 * Second pass, check क्रम infinite loops in chains. These are
	 * possible because we करोn't update the previous poपूर्णांकers when
	 * we fold chains. No big deal, just fix them up in PUtable.
	 */
	pr_debug("INFTL: pass 2, validate virtual chains\n");
	क्रम (logical_block = 0; logical_block < s->numvunits; logical_block++) अणु
		block = s->VUtable[logical_block];
		last_block = BLOCK_NIL;

		/* Check क्रम मुक्त/reserved/nil */
		अगर (block >= BLOCK_RESERVED)
			जारी;

		ANAC = ANACtable[block];
		क्रम (i = 0; i < s->numvunits; i++) अणु
			अगर (s->PUtable[block] == BLOCK_NIL)
				अवरोध;
			अगर (s->PUtable[block] > s->lastEUN) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: invalid prev %d, "
					"in virtual chain %d\n",
					s->PUtable[block], logical_block);
				s->PUtable[block] = BLOCK_NIL;

			पूर्ण
			अगर (ANACtable[block] != ANAC) अणु
				/*
				 * Chain must poपूर्णांक back to itself. This is ok,
				 * but we will need adjust the tables with this
				 * newest block and oldest block.
				 */
				s->VUtable[logical_block] = block;
				s->PUtable[last_block] = BLOCK_NIL;
				अवरोध;
			पूर्ण

			ANAC--;
			last_block = block;
			block = s->PUtable[block];
		पूर्ण

		अगर (i >= s->nb_blocks) अणु
			/*
			 * Uhoo, infinite chain with valid ANACS!
			 * Format whole chain...
			 */
			क्रमmat_chain(s, first_block);
		पूर्ण
	पूर्ण

	INFTL_dumptables(s);
	INFTL_dumpVUchains(s);

	/*
	 * Third pass, क्रमmat unreferenced blocks and init मुक्त block count.
	 */
	s->numमुक्तEUNs = 0;
	s->LastFreeEUN = BLOCK_NIL;

	pr_debug("INFTL: pass 3, format unused blocks\n");
	क्रम (block = s->firstEUN; block <= s->lastEUN; block++) अणु
		अगर (s->PUtable[block] == BLOCK_NOTEXPLORED) अणु
			prपूर्णांकk("INFTL: unreferenced block %d, formatting it\n",
				block);
			अगर (INFTL_क्रमmatblock(s, block) < 0)
				s->PUtable[block] = BLOCK_RESERVED;
			अन्यथा
				s->PUtable[block] = BLOCK_FREE;
		पूर्ण
		अगर (s->PUtable[block] == BLOCK_FREE) अणु
			s->numमुक्तEUNs++;
			अगर (s->LastFreeEUN == BLOCK_NIL)
				s->LastFreeEUN = block;
		पूर्ण
	पूर्ण

	kमुक्त(ANACtable);
	वापस 0;
पूर्ण
