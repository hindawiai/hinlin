<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * inftlcore.c -- Linux driver क्रम Inverse Flash Translation Layer (INFTL)
 *
 * Copyright तऊ 2002, Greg Ungerer (gerg@snapgear.com)
 *
 * Based heavily on the nftlcore.c code which is:
 * Copyright तऊ 1999 Machine Vision Holdings, Inc.
 * Copyright तऊ 1999 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/kmod.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/nftl.h>
#समावेश <linux/mtd/inftl.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/पन.स>

/*
 * Maximum number of loops जबतक examining next block, to have a
 * chance to detect consistency problems (they should never happen
 * because of the checks करोne in the mounting.
 */
#घोषणा MAX_LOOPS 10000

अटल व्योम inftl_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा INFTLrecord *inftl;
	अचिन्हित दीर्घ temp;

	अगर (!mtd_type_is_nand(mtd) || mtd->size > अच_पूर्णांक_उच्च)
		वापस;
	/* OK, this is moderately ugly.  But probably safe.  Alternatives? */
	अगर (स_भेद(mtd->name, "DiskOnChip", 10))
		वापस;

	अगर (!mtd->_block_isbad) अणु
		prपूर्णांकk(KERN_ERR
"INFTL no longer supports the old DiskOnChip drivers loaded via docprobe.\n"
"Please use the new diskonchip driver under the NAND subsystem.\n");
		वापस;
	पूर्ण

	pr_debug("INFTL: add_mtd for %s\n", mtd->name);

	inftl = kzalloc(माप(*inftl), GFP_KERNEL);

	अगर (!inftl)
		वापस;

	inftl->mbd.mtd = mtd;
	inftl->mbd.devnum = -1;

	inftl->mbd.tr = tr;

	अगर (INFTL_mount(inftl) < 0) अणु
		prपूर्णांकk(KERN_WARNING "INFTL: could not mount device\n");
		kमुक्त(inftl);
		वापस;
	पूर्ण

	/* OK, it's a new one. Set up all the data काष्ठाures. */

	/* Calculate geometry */
	inftl->cylinders = 1024;
	inftl->heads = 16;

	temp = inftl->cylinders * inftl->heads;
	inftl->sectors = inftl->mbd.size / temp;
	अगर (inftl->mbd.size % temp) अणु
		inftl->sectors++;
		temp = inftl->cylinders * inftl->sectors;
		inftl->heads = inftl->mbd.size / temp;

		अगर (inftl->mbd.size % temp) अणु
			inftl->heads++;
			temp = inftl->heads * inftl->sectors;
			inftl->cylinders = inftl->mbd.size / temp;
		पूर्ण
	पूर्ण

	अगर (inftl->mbd.size != inftl->heads * inftl->cylinders * inftl->sectors) अणु
		/*
		  Oh no we करोn't have
		   mbd.size == heads * cylinders * sectors
		*/
		prपूर्णांकk(KERN_WARNING "INFTL: cannot calculate a geometry to "
		       "match size of 0x%lx.\n", inftl->mbd.size);
		prपूर्णांकk(KERN_WARNING "INFTL: using C:%d H:%d S:%d "
			"(== 0x%lx sects)\n",
			inftl->cylinders, inftl->heads , inftl->sectors,
			(दीर्घ)inftl->cylinders * (दीर्घ)inftl->heads *
			(दीर्घ)inftl->sectors );
	पूर्ण

	अगर (add_mtd_blktrans_dev(&inftl->mbd)) अणु
		kमुक्त(inftl->PUtable);
		kमुक्त(inftl->VUtable);
		kमुक्त(inftl);
		वापस;
	पूर्ण
#अगर_घोषित PSYCHO_DEBUG
	prपूर्णांकk(KERN_INFO "INFTL: Found new inftl%c\n", inftl->mbd.devnum + 'a');
#पूर्ण_अगर
	वापस;
पूर्ण

अटल व्योम inftl_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा INFTLrecord *inftl = (व्योम *)dev;

	pr_debug("INFTL: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);

	kमुक्त(inftl->PUtable);
	kमुक्त(inftl->VUtable);
पूर्ण

/*
 * Actual INFTL access routines.
 */

/*
 * Read oob data from flash
 */
पूर्णांक inftl_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		   माप_प्रकार *retlen, uपूर्णांक8_t *buf)
अणु
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = offs & (mtd->ग_लिखोsize - 1);
	ops.ooblen = len;
	ops.oobbuf = buf;
	ops.datbuf = शून्य;

	res = mtd_पढ़ो_oob(mtd, offs & ~(mtd->ग_लिखोsize - 1), &ops);
	*retlen = ops.oobretlen;
	वापस res;
पूर्ण

/*
 * Write oob data to flash
 */
पूर्णांक inftl_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		    माप_प्रकार *retlen, uपूर्णांक8_t *buf)
अणु
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = offs & (mtd->ग_लिखोsize - 1);
	ops.ooblen = len;
	ops.oobbuf = buf;
	ops.datbuf = शून्य;

	res = mtd_ग_लिखो_oob(mtd, offs & ~(mtd->ग_लिखोsize - 1), &ops);
	*retlen = ops.oobretlen;
	वापस res;
पूर्ण

/*
 * Write data and oob to flash
 */
अटल पूर्णांक inftl_ग_लिखो(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		       माप_प्रकार *retlen, uपूर्णांक8_t *buf, uपूर्णांक8_t *oob)
अणु
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = offs;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = oob;
	ops.datbuf = buf;
	ops.len = len;

	res = mtd_ग_लिखो_oob(mtd, offs & ~(mtd->ग_लिखोsize - 1), &ops);
	*retlen = ops.retlen;
	वापस res;
पूर्ण

/*
 * INFTL_findमुक्तblock: Find a मुक्त Erase Unit on the INFTL partition.
 *	This function is used when the give Virtual Unit Chain.
 */
अटल u16 INFTL_findमुक्तblock(काष्ठा INFTLrecord *inftl, पूर्णांक desperate)
अणु
	u16 pot = inftl->LastFreeEUN;
	पूर्णांक silly = inftl->nb_blocks;

	pr_debug("INFTL: INFTL_findfreeblock(inftl=%p,desperate=%d)\n",
			inftl, desperate);

	/*
	 * Normally, we क्रमce a fold to happen beक्रमe we run out of मुक्त
	 * blocks completely.
	 */
	अगर (!desperate && inftl->numमुक्तEUNs < 2) अणु
		pr_debug("INFTL: there are too few free EUNs (%d)\n",
				inftl->numमुक्तEUNs);
		वापस BLOCK_NIL;
	पूर्ण

	/* Scan क्रम a मुक्त block */
	करो अणु
		अगर (inftl->PUtable[pot] == BLOCK_FREE) अणु
			inftl->LastFreeEUN = pot;
			वापस pot;
		पूर्ण

		अगर (++pot > inftl->lastEUN)
			pot = 0;

		अगर (!silly--) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: no free blocks found!  "
				"EUN range = %d - %d\n", 0, inftl->LastFreeEUN);
			वापस BLOCK_NIL;
		पूर्ण
	पूर्ण जबतक (pot != inftl->LastFreeEUN);

	वापस BLOCK_NIL;
पूर्ण

अटल u16 INFTL_foldchain(काष्ठा INFTLrecord *inftl, अचिन्हित thisVUC, अचिन्हित pendingblock)
अणु
	u16 BlockMap[MAX_SECTORS_PER_UNIT];
	अचिन्हित अक्षर BlockDeleted[MAX_SECTORS_PER_UNIT];
	अचिन्हित पूर्णांक thisEUN, prevEUN, status;
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	पूर्णांक block, silly;
	अचिन्हित पूर्णांक targetEUN;
	काष्ठा inftl_oob oob;
	माप_प्रकार retlen;

	pr_debug("INFTL: INFTL_foldchain(inftl=%p,thisVUC=%d,pending=%d)\n",
			inftl, thisVUC, pendingblock);

	स_रखो(BlockMap, 0xff, माप(BlockMap));
	स_रखो(BlockDeleted, 0, माप(BlockDeleted));

	thisEUN = targetEUN = inftl->VUtable[thisVUC];

	अगर (thisEUN == BLOCK_NIL) अणु
		prपूर्णांकk(KERN_WARNING "INFTL: trying to fold non-existent "
		       "Virtual Unit Chain %d!\n", thisVUC);
		वापस BLOCK_NIL;
	पूर्ण

	/*
	 * Scan to find the Erase Unit which holds the actual data क्रम each
	 * 512-byte block within the Chain.
	 */
	silly = MAX_LOOPS;
	जबतक (thisEUN < inftl->nb_blocks) अणु
		क्रम (block = 0; block < inftl->EraseSize/SECTORSIZE; block ++) अणु
			अगर ((BlockMap[block] != BLOCK_NIL) ||
			    BlockDeleted[block])
				जारी;

			अगर (inftl_पढ़ो_oob(mtd, (thisEUN * inftl->EraseSize)
					   + (block * SECTORSIZE), 16, &retlen,
					   (अक्षर *)&oob) < 0)
				status = SECTOR_IGNORE;
			अन्यथा
				status = oob.b.Status | oob.b.Status1;

			चयन(status) अणु
			हाल SECTOR_FREE:
			हाल SECTOR_IGNORE:
				अवरोध;
			हाल SECTOR_USED:
				BlockMap[block] = thisEUN;
				जारी;
			हाल SECTOR_DELETED:
				BlockDeleted[block] = 1;
				जारी;
			शेष:
				prपूर्णांकk(KERN_WARNING "INFTL: unknown status "
					"for block %d in EUN %d: %x\n",
					block, thisEUN, status);
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!silly--) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: infinite loop in Virtual "
				"Unit Chain 0x%x\n", thisVUC);
			वापस BLOCK_NIL;
		पूर्ण

		thisEUN = inftl->PUtable[thisEUN];
	पूर्ण

	/*
	 * OK. We now know the location of every block in the Virtual Unit
	 * Chain, and the Erase Unit पूर्णांकo which we are supposed to be copying.
	 * Go क्रम it.
	 */
	pr_debug("INFTL: folding chain %d into unit %d\n", thisVUC, targetEUN);

	क्रम (block = 0; block < inftl->EraseSize/SECTORSIZE ; block++) अणु
		अचिन्हित अक्षर movebuf[SECTORSIZE];
		पूर्णांक ret;

		/*
		 * If it's in the target EUN already, or if it's pending ग_लिखो,
		 * करो nothing.
		 */
		अगर (BlockMap[block] == targetEUN || (pendingblock ==
		    (thisVUC * (inftl->EraseSize / SECTORSIZE) + block))) अणु
			जारी;
		पूर्ण

		/*
		 * Copy only in non मुक्त block (मुक्त blocks can only
                 * happen in हाल of media errors or deleted blocks).
		 */
		अगर (BlockMap[block] == BLOCK_NIL)
			जारी;

		ret = mtd_पढ़ो(mtd,
			       (inftl->EraseSize * BlockMap[block]) + (block * SECTORSIZE),
			       SECTORSIZE,
			       &retlen,
			       movebuf);
		अगर (ret < 0 && !mtd_is_bitflip(ret)) अणु
			ret = mtd_पढ़ो(mtd,
				       (inftl->EraseSize * BlockMap[block]) + (block * SECTORSIZE),
				       SECTORSIZE,
				       &retlen,
				       movebuf);
			अगर (ret != -EIO)
				pr_debug("INFTL: error went away on retry?\n");
		पूर्ण
		स_रखो(&oob, 0xff, माप(काष्ठा inftl_oob));
		oob.b.Status = oob.b.Status1 = SECTOR_USED;

		inftl_ग_लिखो(inftl->mbd.mtd, (inftl->EraseSize * targetEUN) +
			    (block * SECTORSIZE), SECTORSIZE, &retlen,
			    movebuf, (अक्षर *)&oob);
	पूर्ण

	/*
	 * Newest unit in chain now contains data from _all_ older units.
	 * So go through and erase each unit in chain, oldest first. (This
	 * is important, by करोing oldest first अगर we crash/reboot then it
	 * it is relatively simple to clean up the mess).
	 */
	pr_debug("INFTL: want to erase virtual chain %d\n", thisVUC);

	क्रम (;;) अणु
		/* Find oldest unit in chain. */
		thisEUN = inftl->VUtable[thisVUC];
		prevEUN = BLOCK_NIL;
		जबतक (inftl->PUtable[thisEUN] != BLOCK_NIL) अणु
			prevEUN = thisEUN;
			thisEUN = inftl->PUtable[thisEUN];
		पूर्ण

		/* Check अगर we are all करोne */
		अगर (thisEUN == targetEUN)
			अवरोध;

		/* Unlink the last block from the chain. */
		inftl->PUtable[prevEUN] = BLOCK_NIL;

		/* Now try to erase it. */
		अगर (INFTL_क्रमmatblock(inftl, thisEUN) < 0) अणु
			/*
			 * Could not erase : mark block as reserved.
			 */
			inftl->PUtable[thisEUN] = BLOCK_RESERVED;
		पूर्ण अन्यथा अणु
			/* Correctly erased : mark it as मुक्त */
			inftl->PUtable[thisEUN] = BLOCK_FREE;
			inftl->numमुक्तEUNs++;
		पूर्ण
	पूर्ण

	वापस targetEUN;
पूर्ण

अटल u16 INFTL_makeमुक्तblock(काष्ठा INFTLrecord *inftl, अचिन्हित pendingblock)
अणु
	/*
	 * This is the part that needs some cleverness applied.
	 * For now, I'm करोing the minimum applicable to actually
	 * get the thing to work.
	 * Wear-levelling and other clever stuff needs to be implemented
	 * and we also need to करो some assessment of the results when
	 * the प्रणाली loses घातer half-way through the routine.
	 */
	u16 LongestChain = 0;
	u16 ChainLength = 0, thislen;
	u16 chain, EUN;

	pr_debug("INFTL: INFTL_makefreeblock(inftl=%p,"
		"pending=%d)\n", inftl, pendingblock);

	क्रम (chain = 0; chain < inftl->nb_blocks; chain++) अणु
		EUN = inftl->VUtable[chain];
		thislen = 0;

		जबतक (EUN <= inftl->lastEUN) अणु
			thislen++;
			EUN = inftl->PUtable[EUN];
			अगर (thislen > 0xff00) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: endless loop in "
					"Virtual Chain %d: Unit %x\n",
					chain, EUN);
				/*
				 * Actually, करोn't वापस failure.
				 * Just ignore this chain and get on with it.
				 */
				thislen = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (thislen > ChainLength) अणु
			ChainLength = thislen;
			LongestChain = chain;
		पूर्ण
	पूर्ण

	अगर (ChainLength < 2) अणु
		prपूर्णांकk(KERN_WARNING "INFTL: no Virtual Unit Chains available "
			"for folding. Failing request\n");
		वापस BLOCK_NIL;
	पूर्ण

	वापस INFTL_foldchain(inftl, LongestChain, pendingblock);
पूर्ण

अटल पूर्णांक nrbits(अचिन्हित पूर्णांक val, पूर्णांक bitcount)
अणु
	पूर्णांक i, total = 0;

	क्रम (i = 0; (i < bitcount); i++)
		total += (((0x1 << i) & val) ? 1 : 0);
	वापस total;
पूर्ण

/*
 * INFTL_findग_लिखोunit: Return the unit number पूर्णांकo which we can ग_लिखो
 *                      क्रम this block. Make it available अगर it isn't alपढ़ोy.
 */
अटल अंतरभूत u16 INFTL_findग_लिखोunit(काष्ठा INFTLrecord *inftl, अचिन्हित block)
अणु
	अचिन्हित पूर्णांक thisVUC = block / (inftl->EraseSize / SECTORSIZE);
	अचिन्हित पूर्णांक thisEUN, ग_लिखोEUN, prev_block, status;
	अचिन्हित दीर्घ blockofs = (block * SECTORSIZE) & (inftl->EraseSize -1);
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	काष्ठा inftl_oob oob;
	काष्ठा inftl_bci bci;
	अचिन्हित अक्षर anac, nacs, parity;
	माप_प्रकार retlen;
	पूर्णांक silly, silly2 = 3;

	pr_debug("INFTL: INFTL_findwriteunit(inftl=%p,block=%d)\n",
			inftl, block);

	करो अणु
		/*
		 * Scan the media to find a unit in the VUC which has
		 * a मुक्त space क्रम the block in question.
		 */
		ग_लिखोEUN = BLOCK_NIL;
		thisEUN = inftl->VUtable[thisVUC];
		silly = MAX_LOOPS;

		जबतक (thisEUN <= inftl->lastEUN) अणु
			inftl_पढ़ो_oob(mtd, (thisEUN * inftl->EraseSize) +
				       blockofs, 8, &retlen, (अक्षर *)&bci);

			status = bci.Status | bci.Status1;
			pr_debug("INFTL: status of block %d in EUN %d is %x\n",
					block , ग_लिखोEUN, status);

			चयन(status) अणु
			हाल SECTOR_FREE:
				ग_लिखोEUN = thisEUN;
				अवरोध;
			हाल SECTOR_DELETED:
			हाल SECTOR_USED:
				/* Can't go any further */
				जाओ hitused;
			हाल SECTOR_IGNORE:
				अवरोध;
			शेष:
				/*
				 * Invalid block. Don't use it any more.
				 * Must implement.
				 */
				अवरोध;
			पूर्ण

			अगर (!silly--) अणु
				prपूर्णांकk(KERN_WARNING "INFTL: infinite loop in "
					"Virtual Unit Chain 0x%x\n", thisVUC);
				वापस BLOCK_NIL;
			पूर्ण

			/* Skip to next block in chain */
			thisEUN = inftl->PUtable[thisEUN];
		पूर्ण

hitused:
		अगर (ग_लिखोEUN != BLOCK_NIL)
			वापस ग_लिखोEUN;


		/*
		 * OK. We didn't find one in the existing chain, or there
		 * is no existing chain. Allocate a new one.
		 */
		ग_लिखोEUN = INFTL_findमुक्तblock(inftl, 0);

		अगर (ग_लिखोEUN == BLOCK_NIL) अणु
			/*
			 * That didn't work - there were no मुक्त blocks just
			 * रुकोing to be picked up. We're going to have to fold
			 * a chain to make room.
			 */
			thisEUN = INFTL_makeमुक्तblock(inftl, block);

			/*
			 * Hopefully we मुक्त something, lets try again.
			 * This समय we are desperate...
			 */
			pr_debug("INFTL: using desperate==1 to find free EUN "
					"to accommodate write to VUC %d\n",
					thisVUC);
			ग_लिखोEUN = INFTL_findमुक्तblock(inftl, 1);
			अगर (ग_लिखोEUN == BLOCK_NIL) अणु
				/*
				 * Ouch. This should never happen - we should
				 * always be able to make some room somehow.
				 * If we get here, we've allocated more storage
				 * space than actual media, or our makeमुक्तblock
				 * routine is missing something.
				 */
				prपूर्णांकk(KERN_WARNING "INFTL: cannot make free "
					"space.\n");
#अगर_घोषित DEBUG
				INFTL_dumptables(inftl);
				INFTL_dumpVUchains(inftl);
#पूर्ण_अगर
				वापस BLOCK_NIL;
			पूर्ण
		पूर्ण

		/*
		 * Insert new block पूर्णांकo भव chain. Firstly update the
		 * block headers in flash...
		 */
		anac = 0;
		nacs = 0;
		thisEUN = inftl->VUtable[thisVUC];
		अगर (thisEUN != BLOCK_NIL) अणु
			inftl_पढ़ो_oob(mtd, thisEUN * inftl->EraseSize
				       + 8, 8, &retlen, (अक्षर *)&oob.u);
			anac = oob.u.a.ANAC + 1;
			nacs = oob.u.a.NACs + 1;
		पूर्ण

		prev_block = inftl->VUtable[thisVUC];
		अगर (prev_block < inftl->nb_blocks)
			prev_block -= inftl->firstEUN;

		parity = (nrbits(thisVUC, 16) & 0x1) ? 0x1 : 0;
		parity |= (nrbits(prev_block, 16) & 0x1) ? 0x2 : 0;
		parity |= (nrbits(anac, 8) & 0x1) ? 0x4 : 0;
		parity |= (nrbits(nacs, 8) & 0x1) ? 0x8 : 0;

		oob.u.a.भवUnitNo = cpu_to_le16(thisVUC);
		oob.u.a.prevUnitNo = cpu_to_le16(prev_block);
		oob.u.a.ANAC = anac;
		oob.u.a.NACs = nacs;
		oob.u.a.parityPerField = parity;
		oob.u.a.discarded = 0xaa;

		inftl_ग_लिखो_oob(mtd, ग_लिखोEUN * inftl->EraseSize + 8, 8,
				&retlen, (अक्षर *)&oob.u);

		/* Also back up header... */
		oob.u.b.भवUnitNo = cpu_to_le16(thisVUC);
		oob.u.b.prevUnitNo = cpu_to_le16(prev_block);
		oob.u.b.ANAC = anac;
		oob.u.b.NACs = nacs;
		oob.u.b.parityPerField = parity;
		oob.u.b.discarded = 0xaa;

		inftl_ग_लिखो_oob(mtd, ग_लिखोEUN * inftl->EraseSize +
				SECTORSIZE * 4 + 8, 8, &retlen, (अक्षर *)&oob.u);

		inftl->PUtable[ग_लिखोEUN] = inftl->VUtable[thisVUC];
		inftl->VUtable[thisVUC] = ग_लिखोEUN;

		inftl->numमुक्तEUNs--;
		वापस ग_लिखोEUN;

	पूर्ण जबतक (silly2--);

	prपूर्णांकk(KERN_WARNING "INFTL: error folding to make room for Virtual "
		"Unit Chain 0x%x\n", thisVUC);
	वापस BLOCK_NIL;
पूर्ण

/*
 * Given a Virtual Unit Chain, see अगर it can be deleted, and अगर so करो it.
 */
अटल व्योम INFTL_trydeletechain(काष्ठा INFTLrecord *inftl, अचिन्हित thisVUC)
अणु
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	अचिन्हित अक्षर BlockUsed[MAX_SECTORS_PER_UNIT];
	अचिन्हित अक्षर BlockDeleted[MAX_SECTORS_PER_UNIT];
	अचिन्हित पूर्णांक thisEUN, status;
	पूर्णांक block, silly;
	काष्ठा inftl_bci bci;
	माप_प्रकार retlen;

	pr_debug("INFTL: INFTL_trydeletechain(inftl=%p,"
		"thisVUC=%d)\n", inftl, thisVUC);

	स_रखो(BlockUsed, 0, माप(BlockUsed));
	स_रखो(BlockDeleted, 0, माप(BlockDeleted));

	thisEUN = inftl->VUtable[thisVUC];
	अगर (thisEUN == BLOCK_NIL) अणु
		prपूर्णांकk(KERN_WARNING "INFTL: trying to delete non-existent "
		       "Virtual Unit Chain %d!\n", thisVUC);
		वापस;
	पूर्ण

	/*
	 * Scan through the Erase Units to determine whether any data is in
	 * each of the 512-byte blocks within the Chain.
	 */
	silly = MAX_LOOPS;
	जबतक (thisEUN < inftl->nb_blocks) अणु
		क्रम (block = 0; block < inftl->EraseSize/SECTORSIZE; block++) अणु
			अगर (BlockUsed[block] || BlockDeleted[block])
				जारी;

			अगर (inftl_पढ़ो_oob(mtd, (thisEUN * inftl->EraseSize)
					   + (block * SECTORSIZE), 8 , &retlen,
					  (अक्षर *)&bci) < 0)
				status = SECTOR_IGNORE;
			अन्यथा
				status = bci.Status | bci.Status1;

			चयन(status) अणु
			हाल SECTOR_FREE:
			हाल SECTOR_IGNORE:
				अवरोध;
			हाल SECTOR_USED:
				BlockUsed[block] = 1;
				जारी;
			हाल SECTOR_DELETED:
				BlockDeleted[block] = 1;
				जारी;
			शेष:
				prपूर्णांकk(KERN_WARNING "INFTL: unknown status "
					"for block %d in EUN %d: 0x%x\n",
					block, thisEUN, status);
			पूर्ण
		पूर्ण

		अगर (!silly--) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: infinite loop in Virtual "
				"Unit Chain 0x%x\n", thisVUC);
			वापस;
		पूर्ण

		thisEUN = inftl->PUtable[thisEUN];
	पूर्ण

	क्रम (block = 0; block < inftl->EraseSize/SECTORSIZE; block++)
		अगर (BlockUsed[block])
			वापस;

	/*
	 * For each block in the chain मुक्त it and make it available
	 * क्रम future use. Erase from the oldest unit first.
	 */
	pr_debug("INFTL: deleting empty VUC %d\n", thisVUC);

	क्रम (;;) अणु
		u16 *prevEUN = &inftl->VUtable[thisVUC];
		thisEUN = *prevEUN;

		/* If the chain is all gone alपढ़ोy, we're करोne */
		अगर (thisEUN == BLOCK_NIL) अणु
			pr_debug("INFTL: Empty VUC %d for deletion was already absent\n", thisEUN);
			वापस;
		पूर्ण

		/* Find oldest unit in chain. */
		जबतक (inftl->PUtable[thisEUN] != BLOCK_NIL) अणु
			BUG_ON(thisEUN >= inftl->nb_blocks);

			prevEUN = &inftl->PUtable[thisEUN];
			thisEUN = *prevEUN;
		पूर्ण

		pr_debug("Deleting EUN %d from VUC %d\n",
		      thisEUN, thisVUC);

		अगर (INFTL_क्रमmatblock(inftl, thisEUN) < 0) अणु
			/*
			 * Could not erase : mark block as reserved.
			 */
			inftl->PUtable[thisEUN] = BLOCK_RESERVED;
		पूर्ण अन्यथा अणु
			/* Correctly erased : mark it as मुक्त */
			inftl->PUtable[thisEUN] = BLOCK_FREE;
			inftl->numमुक्तEUNs++;
		पूर्ण

		/* Now sort out whatever was poपूर्णांकing to it... */
		*prevEUN = BLOCK_NIL;

		/* Ideally we'd actually be responsive to new
		   requests जबतक we're doing this -- if there's
		   मुक्त space why should others be made to रुको? */
		cond_resched();
	पूर्ण

	inftl->VUtable[thisVUC] = BLOCK_NIL;
पूर्ण

अटल पूर्णांक INFTL_deleteblock(काष्ठा INFTLrecord *inftl, अचिन्हित block)
अणु
	अचिन्हित पूर्णांक thisEUN = inftl->VUtable[block / (inftl->EraseSize / SECTORSIZE)];
	अचिन्हित दीर्घ blockofs = (block * SECTORSIZE) & (inftl->EraseSize - 1);
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	अचिन्हित पूर्णांक status;
	पूर्णांक silly = MAX_LOOPS;
	माप_प्रकार retlen;
	काष्ठा inftl_bci bci;

	pr_debug("INFTL: INFTL_deleteblock(inftl=%p,"
		"block=%d)\n", inftl, block);

	जबतक (thisEUN < inftl->nb_blocks) अणु
		अगर (inftl_पढ़ो_oob(mtd, (thisEUN * inftl->EraseSize) +
				   blockofs, 8, &retlen, (अक्षर *)&bci) < 0)
			status = SECTOR_IGNORE;
		अन्यथा
			status = bci.Status | bci.Status1;

		चयन (status) अणु
		हाल SECTOR_FREE:
		हाल SECTOR_IGNORE:
			अवरोध;
		हाल SECTOR_DELETED:
			thisEUN = BLOCK_NIL;
			जाओ foundit;
		हाल SECTOR_USED:
			जाओ foundit;
		शेष:
			prपूर्णांकk(KERN_WARNING "INFTL: unknown status for "
				"block %d in EUN %d: 0x%x\n",
				block, thisEUN, status);
			अवरोध;
		पूर्ण

		अगर (!silly--) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: infinite loop in Virtual "
				"Unit Chain 0x%x\n",
				block / (inftl->EraseSize / SECTORSIZE));
			वापस 1;
		पूर्ण
		thisEUN = inftl->PUtable[thisEUN];
	पूर्ण

foundit:
	अगर (thisEUN != BLOCK_NIL) अणु
		loff_t ptr = (thisEUN * inftl->EraseSize) + blockofs;

		अगर (inftl_पढ़ो_oob(mtd, ptr, 8, &retlen, (अक्षर *)&bci) < 0)
			वापस -EIO;
		bci.Status = bci.Status1 = SECTOR_DELETED;
		अगर (inftl_ग_लिखो_oob(mtd, ptr, 8, &retlen, (अक्षर *)&bci) < 0)
			वापस -EIO;
		INFTL_trydeletechain(inftl, block / (inftl->EraseSize / SECTORSIZE));
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक inftl_ग_लिखोblock(काष्ठा mtd_blktrans_dev *mbd, अचिन्हित दीर्घ block,
			    अक्षर *buffer)
अणु
	काष्ठा INFTLrecord *inftl = (व्योम *)mbd;
	अचिन्हित पूर्णांक ग_लिखोEUN;
	अचिन्हित दीर्घ blockofs = (block * SECTORSIZE) & (inftl->EraseSize - 1);
	माप_प्रकार retlen;
	काष्ठा inftl_oob oob;
	अक्षर *p, *pend;

	pr_debug("INFTL: inftl_writeblock(inftl=%p,block=%ld,"
		"buffer=%p)\n", inftl, block, buffer);

	/* Is block all zero? */
	pend = buffer + SECTORSIZE;
	क्रम (p = buffer; p < pend && !*p; p++)
		;

	अगर (p < pend) अणु
		ग_लिखोEUN = INFTL_findग_लिखोunit(inftl, block);

		अगर (ग_लिखोEUN == BLOCK_NIL) अणु
			prपूर्णांकk(KERN_WARNING "inftl_writeblock(): cannot find "
				"block to write to\n");
			/*
			 * If we _still_ haven't got a block to use,
			 * we're screwed.
			 */
			वापस 1;
		पूर्ण

		स_रखो(&oob, 0xff, माप(काष्ठा inftl_oob));
		oob.b.Status = oob.b.Status1 = SECTOR_USED;

		inftl_ग_लिखो(inftl->mbd.mtd, (ग_लिखोEUN * inftl->EraseSize) +
			    blockofs, SECTORSIZE, &retlen, (अक्षर *)buffer,
			    (अक्षर *)&oob);
		/*
		 * need to ग_लिखो SECTOR_USED flags since they are not written
		 * in mtd_ग_लिखोecc
		 */
	पूर्ण अन्यथा अणु
		INFTL_deleteblock(inftl, block);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक inftl_पढ़ोblock(काष्ठा mtd_blktrans_dev *mbd, अचिन्हित दीर्घ block,
			   अक्षर *buffer)
अणु
	काष्ठा INFTLrecord *inftl = (व्योम *)mbd;
	अचिन्हित पूर्णांक thisEUN = inftl->VUtable[block / (inftl->EraseSize / SECTORSIZE)];
	अचिन्हित दीर्घ blockofs = (block * SECTORSIZE) & (inftl->EraseSize - 1);
	काष्ठा mtd_info *mtd = inftl->mbd.mtd;
	अचिन्हित पूर्णांक status;
	पूर्णांक silly = MAX_LOOPS;
	काष्ठा inftl_bci bci;
	माप_प्रकार retlen;

	pr_debug("INFTL: inftl_readblock(inftl=%p,block=%ld,"
		"buffer=%p)\n", inftl, block, buffer);

	जबतक (thisEUN < inftl->nb_blocks) अणु
		अगर (inftl_पढ़ो_oob(mtd, (thisEUN * inftl->EraseSize) +
				  blockofs, 8, &retlen, (अक्षर *)&bci) < 0)
			status = SECTOR_IGNORE;
		अन्यथा
			status = bci.Status | bci.Status1;

		चयन (status) अणु
		हाल SECTOR_DELETED:
			thisEUN = BLOCK_NIL;
			जाओ foundit;
		हाल SECTOR_USED:
			जाओ foundit;
		हाल SECTOR_FREE:
		हाल SECTOR_IGNORE:
			अवरोध;
		शेष:
			prपूर्णांकk(KERN_WARNING "INFTL: unknown status for "
				"block %ld in EUN %d: 0x%04x\n",
				block, thisEUN, status);
			अवरोध;
		पूर्ण

		अगर (!silly--) अणु
			prपूर्णांकk(KERN_WARNING "INFTL: infinite loop in "
				"Virtual Unit Chain 0x%lx\n",
				block / (inftl->EraseSize / SECTORSIZE));
			वापस 1;
		पूर्ण

		thisEUN = inftl->PUtable[thisEUN];
	पूर्ण

foundit:
	अगर (thisEUN == BLOCK_NIL) अणु
		/* The requested block is not on the media, वापस all 0x00 */
		स_रखो(buffer, 0, SECTORSIZE);
	पूर्ण अन्यथा अणु
		माप_प्रकार retlen;
		loff_t ptr = (thisEUN * inftl->EraseSize) + blockofs;
		पूर्णांक ret = mtd_पढ़ो(mtd, ptr, SECTORSIZE, &retlen, buffer);

		/* Handle corrected bit flips gracefully */
		अगर (ret < 0 && !mtd_is_bitflip(ret))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक inftl_getgeo(काष्ठा mtd_blktrans_dev *dev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा INFTLrecord *inftl = (व्योम *)dev;

	geo->heads = inftl->heads;
	geo->sectors = inftl->sectors;
	geo->cylinders = inftl->cylinders;

	वापस 0;
पूर्ण

अटल काष्ठा mtd_blktrans_ops inftl_tr = अणु
	.name		= "inftl",
	.major		= INFTL_MAJOR,
	.part_bits	= INFTL_PARTN_BITS,
	.blksize 	= 512,
	.getgeo		= inftl_getgeo,
	.पढ़ोsect	= inftl_पढ़ोblock,
	.ग_लिखोsect	= inftl_ग_लिखोblock,
	.add_mtd	= inftl_add_mtd,
	.हटाओ_dev	= inftl_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(inftl_tr);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Greg Ungerer <gerg@snapgear.com>, David Woodhouse <dwmw2@infradead.org>, Fabrice Bellard <fabrice.bellard@netgem.com> et al.");
MODULE_DESCRIPTION("Support code for Inverse Flash Translation Layer, used on M-Systems DiskOnChip 2000, Millennium and Millennium Plus");
