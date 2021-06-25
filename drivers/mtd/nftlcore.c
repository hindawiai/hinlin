<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Linux driver क्रम न_अंकD Flash Translation Layer
 *
 * Copyright तऊ 1999 Machine Vision Holdings, Inc.
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 */

#घोषणा PRERELEASE

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/त्रुटिसं.स>
#समावेश <यंत्र/पन.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/blkdev.h>

#समावेश <linux/kmod.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/nftl.h>
#समावेश <linux/mtd/blktrans.h>

/* maximum number of loops जबतक examining next block, to have a
   chance to detect consistency problems (they should never happen
   because of the checks करोne in the mounting */

#घोषणा MAX_LOOPS 10000


अटल व्योम nftl_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा NFTLrecord *nftl;
	अचिन्हित दीर्घ temp;

	अगर (!mtd_type_is_nand(mtd) || mtd->size > अच_पूर्णांक_उच्च)
		वापस;
	/* OK, this is moderately ugly.  But probably safe.  Alternatives? */
	अगर (स_भेद(mtd->name, "DiskOnChip", 10))
		वापस;

	pr_debug("NFTL: add_mtd for %s\n", mtd->name);

	nftl = kzalloc(माप(काष्ठा NFTLrecord), GFP_KERNEL);

	अगर (!nftl)
		वापस;

	nftl->mbd.mtd = mtd;
	nftl->mbd.devnum = -1;

	nftl->mbd.tr = tr;

        अगर (NFTL_mount(nftl) < 0) अणु
		prपूर्णांकk(KERN_WARNING "NFTL: could not mount device\n");
		kमुक्त(nftl);
		वापस;
        पूर्ण

	/* OK, it's a new one. Set up all the data काष्ठाures. */

	/* Calculate geometry */
	nftl->cylinders = 1024;
	nftl->heads = 16;

	temp = nftl->cylinders * nftl->heads;
	nftl->sectors = nftl->mbd.size / temp;
	अगर (nftl->mbd.size % temp) अणु
		nftl->sectors++;
		temp = nftl->cylinders * nftl->sectors;
		nftl->heads = nftl->mbd.size / temp;

		अगर (nftl->mbd.size % temp) अणु
			nftl->heads++;
			temp = nftl->heads * nftl->sectors;
			nftl->cylinders = nftl->mbd.size / temp;
		पूर्ण
	पूर्ण

	अगर (nftl->mbd.size != nftl->heads * nftl->cylinders * nftl->sectors) अणु
		/*
		  Oh no we करोn't have
		   mbd.size == heads * cylinders * sectors
		*/
		prपूर्णांकk(KERN_WARNING "NFTL: cannot calculate a geometry to "
		       "match size of 0x%lx.\n", nftl->mbd.size);
		prपूर्णांकk(KERN_WARNING "NFTL: using C:%d H:%d S:%d "
			"(== 0x%lx sects)\n",
			nftl->cylinders, nftl->heads , nftl->sectors,
			(दीर्घ)nftl->cylinders * (दीर्घ)nftl->heads *
			(दीर्घ)nftl->sectors );
	पूर्ण

	अगर (add_mtd_blktrans_dev(&nftl->mbd)) अणु
		kमुक्त(nftl->ReplUnitTable);
		kमुक्त(nftl->EUNtable);
		kमुक्त(nftl);
		वापस;
	पूर्ण
#अगर_घोषित PSYCHO_DEBUG
	prपूर्णांकk(KERN_INFO "NFTL: Found new nftl%c\n", nftl->mbd.devnum + 'a');
#पूर्ण_अगर
पूर्ण

अटल व्योम nftl_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा NFTLrecord *nftl = (व्योम *)dev;

	pr_debug("NFTL: remove_dev (i=%d)\n", dev->devnum);

	del_mtd_blktrans_dev(dev);
	kमुक्त(nftl->ReplUnitTable);
	kमुक्त(nftl->EUNtable);
पूर्ण

/*
 * Read oob data from flash
 */
पूर्णांक nftl_पढ़ो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		  माप_प्रकार *retlen, uपूर्णांक8_t *buf)
अणु
	loff_t mask = mtd->ग_लिखोsize - 1;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = offs & mask;
	ops.ooblen = len;
	ops.oobbuf = buf;
	ops.datbuf = शून्य;

	res = mtd_पढ़ो_oob(mtd, offs & ~mask, &ops);
	*retlen = ops.oobretlen;
	वापस res;
पूर्ण

/*
 * Write oob data to flash
 */
पूर्णांक nftl_ग_लिखो_oob(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		   माप_प्रकार *retlen, uपूर्णांक8_t *buf)
अणु
	loff_t mask = mtd->ग_लिखोsize - 1;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = offs & mask;
	ops.ooblen = len;
	ops.oobbuf = buf;
	ops.datbuf = शून्य;

	res = mtd_ग_लिखो_oob(mtd, offs & ~mask, &ops);
	*retlen = ops.oobretlen;
	वापस res;
पूर्ण

#अगर_घोषित CONFIG_NFTL_RW

/*
 * Write data and oob to flash
 */
अटल पूर्णांक nftl_ग_लिखो(काष्ठा mtd_info *mtd, loff_t offs, माप_प्रकार len,
		      माप_प्रकार *retlen, uपूर्णांक8_t *buf, uपूर्णांक8_t *oob)
अणु
	loff_t mask = mtd->ग_लिखोsize - 1;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक res;

	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = offs & mask;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = oob;
	ops.datbuf = buf;
	ops.len = len;

	res = mtd_ग_लिखो_oob(mtd, offs & ~mask, &ops);
	*retlen = ops.retlen;
	वापस res;
पूर्ण

/* Actual NFTL access routines */
/* NFTL_findमुक्तblock: Find a मुक्त Erase Unit on the NFTL partition. This function is used
 *	when the give Virtual Unit Chain
 */
अटल u16 NFTL_findमुक्तblock(काष्ठा NFTLrecord *nftl, पूर्णांक desperate )
अणु
	/* For a given Virtual Unit Chain: find or create a मुक्त block and
	   add it to the chain */
	/* We're passed the number of the last EUN in the chain, to save us from
	   having to look it up again */
	u16 pot = nftl->LastFreeEUN;
	पूर्णांक silly = nftl->nb_blocks;

	/* Normally, we क्रमce a fold to happen beक्रमe we run out of मुक्त blocks completely */
	अगर (!desperate && nftl->numमुक्तEUNs < 2) अणु
		pr_debug("NFTL_findfreeblock: there are too few free EUNs\n");
		वापस BLOCK_NIL;
	पूर्ण

	/* Scan क्रम a मुक्त block */
	करो अणु
		अगर (nftl->ReplUnitTable[pot] == BLOCK_FREE) अणु
			nftl->LastFreeEUN = pot;
			nftl->numमुक्तEUNs--;
			वापस pot;
		पूर्ण

		/* This will probably poपूर्णांक to the MediaHdr unit itself,
		   right at the beginning of the partition. But that unit
		   (and the backup unit too) should have the UCI set
		   up so that it's not selected क्रम overwriting */
		अगर (++pot > nftl->lastEUN)
			pot = le16_to_cpu(nftl->MediaHdr.FirstPhysicalEUN);

		अगर (!silly--) अणु
			prपूर्णांकk("Argh! No free blocks found! LastFreeEUN = %d, "
			       "FirstEUN = %d\n", nftl->LastFreeEUN,
			       le16_to_cpu(nftl->MediaHdr.FirstPhysicalEUN));
			वापस BLOCK_NIL;
		पूर्ण
	पूर्ण जबतक (pot != nftl->LastFreeEUN);

	वापस BLOCK_NIL;
पूर्ण

अटल u16 NFTL_foldchain (काष्ठा NFTLrecord *nftl, अचिन्हित thisVUC, अचिन्हित pendingblock )
अणु
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	u16 BlockMap[MAX_SECTORS_PER_UNIT];
	अचिन्हित अक्षर BlockLastState[MAX_SECTORS_PER_UNIT];
	अचिन्हित अक्षर BlockFreeFound[MAX_SECTORS_PER_UNIT];
	अचिन्हित पूर्णांक thisEUN;
	पूर्णांक block;
	पूर्णांक silly;
	अचिन्हित पूर्णांक targetEUN;
	काष्ठा nftl_oob oob;
	पूर्णांक inplace = 1;
	माप_प्रकार retlen;

	स_रखो(BlockMap, 0xff, माप(BlockMap));
	स_रखो(BlockFreeFound, 0, माप(BlockFreeFound));

	thisEUN = nftl->EUNtable[thisVUC];

	अगर (thisEUN == BLOCK_NIL) अणु
		prपूर्णांकk(KERN_WARNING "Trying to fold non-existent "
		       "Virtual Unit Chain %d!\n", thisVUC);
		वापस BLOCK_NIL;
	पूर्ण

	/* Scan to find the Erase Unit which holds the actual data क्रम each
	   512-byte block within the Chain.
	*/
	silly = MAX_LOOPS;
	targetEUN = BLOCK_NIL;
	जबतक (thisEUN <= nftl->lastEUN ) अणु
		अचिन्हित पूर्णांक status, foldmark;

		targetEUN = thisEUN;
		क्रम (block = 0; block < nftl->EraseSize / 512; block ++) अणु
			nftl_पढ़ो_oob(mtd, (thisEUN * nftl->EraseSize) +
				      (block * 512), 16 , &retlen,
				      (अक्षर *)&oob);
			अगर (block == 2) अणु
				foldmark = oob.u.c.FoldMark | oob.u.c.FoldMark1;
				अगर (foldmark == FOLD_MARK_IN_PROGRESS) अणु
					pr_debug("Write Inhibited on EUN %d\n", thisEUN);
					inplace = 0;
				पूर्ण अन्यथा अणु
					/* There's no other reason not to करो inplace,
					   except ones that come later. So we करोn't need
					   to preserve inplace */
					inplace = 1;
				पूर्ण
			पूर्ण
			status = oob.b.Status | oob.b.Status1;
			BlockLastState[block] = status;

			चयन(status) अणु
			हाल SECTOR_FREE:
				BlockFreeFound[block] = 1;
				अवरोध;

			हाल SECTOR_USED:
				अगर (!BlockFreeFound[block])
					BlockMap[block] = thisEUN;
				अन्यथा
					prपूर्णांकk(KERN_WARNING
					       "SECTOR_USED found after SECTOR_FREE "
					       "in Virtual Unit Chain %d for block %d\n",
					       thisVUC, block);
				अवरोध;
			हाल SECTOR_DELETED:
				अगर (!BlockFreeFound[block])
					BlockMap[block] = BLOCK_NIL;
				अन्यथा
					prपूर्णांकk(KERN_WARNING
					       "SECTOR_DELETED found after SECTOR_FREE "
					       "in Virtual Unit Chain %d for block %d\n",
					       thisVUC, block);
				अवरोध;

			हाल SECTOR_IGNORE:
				अवरोध;
			शेष:
				prपूर्णांकk("Unknown status for block %d in EUN %d: %x\n",
				       block, thisEUN, status);
			पूर्ण
		पूर्ण

		अगर (!silly--) अणु
			prपूर्णांकk(KERN_WARNING "Infinite loop in Virtual Unit Chain 0x%x\n",
			       thisVUC);
			वापस BLOCK_NIL;
		पूर्ण

		thisEUN = nftl->ReplUnitTable[thisEUN];
	पूर्ण

	अगर (inplace) अणु
		/* We're being asked to be a fold-in-place. Check
		   that all blocks which actually have data associated
		   with them (i.e. BlockMap[block] != BLOCK_NIL) are
		   either alपढ़ोy present or SECTOR_FREE in the target
		   block. If not, we're going to have to fold out-of-place
		   anyway.
		*/
		क्रम (block = 0; block < nftl->EraseSize / 512 ; block++) अणु
			अगर (BlockLastState[block] != SECTOR_FREE &&
			    BlockMap[block] != BLOCK_NIL &&
			    BlockMap[block] != targetEUN) अणु
				pr_debug("Setting inplace to 0. VUC %d, "
				      "block %d was %x lastEUN, "
				      "and is in EUN %d (%s) %d\n",
				      thisVUC, block, BlockLastState[block],
				      BlockMap[block],
				      BlockMap[block]== targetEUN ? "==" : "!=",
				      targetEUN);
				inplace = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (pendingblock >= (thisVUC * (nftl->EraseSize / 512)) &&
		    pendingblock < ((thisVUC + 1)* (nftl->EraseSize / 512)) &&
		    BlockLastState[pendingblock - (thisVUC * (nftl->EraseSize / 512))] !=
		    SECTOR_FREE) अणु
			pr_debug("Pending write not free in EUN %d. "
			      "Folding out of place.\n", targetEUN);
			inplace = 0;
		पूर्ण
	पूर्ण

	अगर (!inplace) अणु
		pr_debug("Cannot fold Virtual Unit Chain %d in place. "
		      "Trying out-of-place\n", thisVUC);
		/* We need to find a targetEUN to fold पूर्णांकo. */
		targetEUN = NFTL_findमुक्तblock(nftl, 1);
		अगर (targetEUN == BLOCK_NIL) अणु
			/* Ouch. Now we're screwed. We need to करो a
			   fold-in-place of another chain to make room
			   क्रम this one. We need a better way of selecting
			   which chain to fold, because makeमुक्तblock will
			   only ask us to fold the same one again.
			*/
			prपूर्णांकk(KERN_WARNING
			       "NFTL_findfreeblock(desperate) returns 0xffff.\n");
			वापस BLOCK_NIL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We put a fold mark in the chain we are folding only अगर we
               fold in place to help the mount check code. If we करो not fold in
               place, it is possible to find the valid chain by selecting the
               दीर्घer one */
		oob.u.c.FoldMark = oob.u.c.FoldMark1 = cpu_to_le16(FOLD_MARK_IN_PROGRESS);
		oob.u.c.unused = 0xffffffff;
		nftl_ग_लिखो_oob(mtd, (nftl->EraseSize * targetEUN) + 2 * 512 + 8,
			       8, &retlen, (अक्षर *)&oob.u);
	पूर्ण

	/* OK. We now know the location of every block in the Virtual Unit Chain,
	   and the Erase Unit पूर्णांकo which we are supposed to be copying.
	   Go क्रम it.
	*/
	pr_debug("Folding chain %d into unit %d\n", thisVUC, targetEUN);
	क्रम (block = 0; block < nftl->EraseSize / 512 ; block++) अणु
		अचिन्हित अक्षर movebuf[512];
		पूर्णांक ret;

		/* If it's in the target EUN already, or if it's pending ग_लिखो, करो nothing */
		अगर (BlockMap[block] == targetEUN ||
		    (pendingblock == (thisVUC * (nftl->EraseSize / 512) + block))) अणु
			जारी;
		पूर्ण

		/* copy only in non मुक्त block (मुक्त blocks can only
                   happen in हाल of media errors or deleted blocks) */
		अगर (BlockMap[block] == BLOCK_NIL)
			जारी;

		ret = mtd_पढ़ो(mtd,
			       (nftl->EraseSize * BlockMap[block]) + (block * 512),
			       512,
			       &retlen,
			       movebuf);
		अगर (ret < 0 && !mtd_is_bitflip(ret)) अणु
			ret = mtd_पढ़ो(mtd,
				       (nftl->EraseSize * BlockMap[block]) + (block * 512),
				       512,
				       &retlen,
				       movebuf);
			अगर (ret != -EIO)
				prपूर्णांकk("Error went away on retry.\n");
		पूर्ण
		स_रखो(&oob, 0xff, माप(काष्ठा nftl_oob));
		oob.b.Status = oob.b.Status1 = SECTOR_USED;

		nftl_ग_लिखो(nftl->mbd.mtd, (nftl->EraseSize * targetEUN) +
			   (block * 512), 512, &retlen, movebuf, (अक्षर *)&oob);
	पूर्ण

	/* add the header so that it is now a valid chain */
	oob.u.a.VirtUnitNum = oob.u.a.SpareVirtUnitNum = cpu_to_le16(thisVUC);
	oob.u.a.ReplUnitNum = oob.u.a.SpareReplUnitNum = BLOCK_NIL;

	nftl_ग_लिखो_oob(mtd, (nftl->EraseSize * targetEUN) + 8,
		       8, &retlen, (अक्षर *)&oob.u);

	/* OK. We've moved the whole lot पूर्णांकo the new block. Now we have to मुक्त the original blocks. */

	/* At this poपूर्णांक, we have two dअगरferent chains क्रम this Virtual Unit, and no way to tell
	   them apart. If we crash now, we get confused. However, both contain the same data, so we
	   shouldn't actually lose data in this case. It's just that when we load up on a medium which
	   has duplicate chains, we need to मुक्त one of the chains because it's not necessary any more.
	*/
	thisEUN = nftl->EUNtable[thisVUC];
	pr_debug("Want to erase\n");

	/* For each block in the old chain (except the targetEUN of course),
	   मुक्त it and make it available क्रम future use */
	जबतक (thisEUN <= nftl->lastEUN && thisEUN != targetEUN) अणु
		अचिन्हित पूर्णांक EUNपंचांगp;

		EUNपंचांगp = nftl->ReplUnitTable[thisEUN];

		अगर (NFTL_क्रमmatblock(nftl, thisEUN) < 0) अणु
			/* could not erase : mark block as reserved
			 */
			nftl->ReplUnitTable[thisEUN] = BLOCK_RESERVED;
		पूर्ण अन्यथा अणु
			/* correctly erased : mark it as मुक्त */
			nftl->ReplUnitTable[thisEUN] = BLOCK_FREE;
			nftl->numमुक्तEUNs++;
		पूर्ण
		thisEUN = EUNपंचांगp;
	पूर्ण

	/* Make this the new start of chain क्रम thisVUC */
	nftl->ReplUnitTable[targetEUN] = BLOCK_NIL;
	nftl->EUNtable[thisVUC] = targetEUN;

	वापस targetEUN;
पूर्ण

अटल u16 NFTL_makeमुक्तblock( काष्ठा NFTLrecord *nftl , अचिन्हित pendingblock)
अणु
	/* This is the part that needs some cleverness applied.
	   For now, I'm करोing the minimum applicable to actually
	   get the thing to work.
	   Wear-levelling and other clever stuff needs to be implemented
	   and we also need to करो some assessment of the results when
	   the प्रणाली loses घातer half-way through the routine.
	*/
	u16 LongestChain = 0;
	u16 ChainLength = 0, thislen;
	u16 chain, EUN;

	क्रम (chain = 0; chain < le32_to_cpu(nftl->MediaHdr.FormattedSize) / nftl->EraseSize; chain++) अणु
		EUN = nftl->EUNtable[chain];
		thislen = 0;

		जबतक (EUN <= nftl->lastEUN) अणु
			thislen++;
			//prपूर्णांकk("VUC %d reaches len %d with EUN %d\n", chain, thislen, EUN);
			EUN = nftl->ReplUnitTable[EUN] & 0x7fff;
			अगर (thislen > 0xff00) अणु
				prपूर्णांकk("Endless loop in Virtual Chain %d: Unit %x\n",
				       chain, EUN);
			पूर्ण
			अगर (thislen > 0xff10) अणु
				/* Actually, करोn't वापस failure. Just ignore this chain and
				   get on with it. */
				thislen = 0;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (thislen > ChainLength) अणु
			//prपूर्णांकk("New longest chain is %d with length %d\n", chain, thislen);
			ChainLength = thislen;
			LongestChain = chain;
		पूर्ण
	पूर्ण

	अगर (ChainLength < 2) अणु
		prपूर्णांकk(KERN_WARNING "No Virtual Unit Chains available for folding. "
		       "Failing request\n");
		वापस BLOCK_NIL;
	पूर्ण

	वापस NFTL_foldchain (nftl, LongestChain, pendingblock);
पूर्ण

/* NFTL_findग_लिखोunit: Return the unit number पूर्णांकo which we can ग_लिखो
                       क्रम this block. Make it available अगर it isn't alपढ़ोy
*/
अटल अंतरभूत u16 NFTL_findग_लिखोunit(काष्ठा NFTLrecord *nftl, अचिन्हित block)
अणु
	u16 lastEUN;
	u16 thisVUC = block / (nftl->EraseSize / 512);
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	अचिन्हित पूर्णांक ग_लिखोEUN;
	अचिन्हित दीर्घ blockofs = (block * 512) & (nftl->EraseSize -1);
	माप_प्रकार retlen;
	पूर्णांक silly, silly2 = 3;
	काष्ठा nftl_oob oob;

	करो अणु
		/* Scan the media to find a unit in the VUC which has
		   a मुक्त space क्रम the block in question.
		*/

		/* This condition catches the 0x[7f]fff हालs, as well as
		   being a sanity check क्रम past-end-of-media access
		*/
		lastEUN = BLOCK_NIL;
		ग_लिखोEUN = nftl->EUNtable[thisVUC];
		silly = MAX_LOOPS;
		जबतक (ग_लिखोEUN <= nftl->lastEUN) अणु
			काष्ठा nftl_bci bci;
			माप_प्रकार retlen;
			अचिन्हित पूर्णांक status;

			lastEUN = ग_लिखोEUN;

			nftl_पढ़ो_oob(mtd,
				      (ग_लिखोEUN * nftl->EraseSize) + blockofs,
				      8, &retlen, (अक्षर *)&bci);

			pr_debug("Status of block %d in EUN %d is %x\n",
			      block , ग_लिखोEUN, le16_to_cpu(bci.Status));

			status = bci.Status | bci.Status1;
			चयन(status) अणु
			हाल SECTOR_FREE:
				वापस ग_लिखोEUN;

			हाल SECTOR_DELETED:
			हाल SECTOR_USED:
			हाल SECTOR_IGNORE:
				अवरोध;
			शेष:
				// Invalid block. Don't use it any more. Must implement.
				अवरोध;
			पूर्ण

			अगर (!silly--) अणु
				prपूर्णांकk(KERN_WARNING
				       "Infinite loop in Virtual Unit Chain 0x%x\n",
				       thisVUC);
				वापस BLOCK_NIL;
			पूर्ण

			/* Skip to next block in chain */
			ग_लिखोEUN = nftl->ReplUnitTable[ग_लिखोEUN];
		पूर्ण

		/* OK. We didn't find one in the existing chain, or there
		   is no existing chain. */

		/* Try to find an alपढ़ोy-मुक्त block */
		ग_लिखोEUN = NFTL_findमुक्तblock(nftl, 0);

		अगर (ग_लिखोEUN == BLOCK_NIL) अणु
			/* That didn't work - there were no मुक्त blocks just
			   रुकोing to be picked up. We're going to have to fold
			   a chain to make room.
			*/

			/* First remember the start of this chain */
			//u16 startEUN = nftl->EUNtable[thisVUC];

			//prपूर्णांकk("Write to VirtualUnitChain %d, calling makefreeblock()\n", thisVUC);
			ग_लिखोEUN = NFTL_makeमुक्तblock(nftl, BLOCK_NIL);

			अगर (ग_लिखोEUN == BLOCK_NIL) अणु
				/* OK, we accept that the above comment is
				   lying - there may have been मुक्त blocks
				   last समय we called NFTL_findमुक्तblock(),
				   but they are reserved क्रम when we're
				   desperate. Well, now we're desperate.
				*/
				pr_debug("Using desperate==1 to find free EUN to accommodate write to VUC %d\n", thisVUC);
				ग_लिखोEUN = NFTL_findमुक्तblock(nftl, 1);
			पूर्ण
			अगर (ग_लिखोEUN == BLOCK_NIL) अणु
				/* Ouch. This should never happen - we should
				   always be able to make some room somehow.
				   If we get here, we've allocated more storage
				   space than actual media, or our makeमुक्तblock
				   routine is missing something.
				*/
				prपूर्णांकk(KERN_WARNING "Cannot make free space.\n");
				वापस BLOCK_NIL;
			पूर्ण
			//prपूर्णांकk("Restarting scan\n");
			lastEUN = BLOCK_NIL;
			जारी;
		पूर्ण

		/* We've found a मुक्त block. Insert it पूर्णांकo the chain. */

		अगर (lastEUN != BLOCK_NIL) अणु
			thisVUC |= 0x8000; /* It's a replacement block */
		पूर्ण अन्यथा अणु
			/* The first block in a new chain */
			nftl->EUNtable[thisVUC] = ग_लिखोEUN;
		पूर्ण

		/* set up the actual EUN we're writing पूर्णांकo */
		/* Both in our cache... */
		nftl->ReplUnitTable[ग_लिखोEUN] = BLOCK_NIL;

		/* ... and on the flash itself */
		nftl_पढ़ो_oob(mtd, ग_लिखोEUN * nftl->EraseSize + 8, 8,
			      &retlen, (अक्षर *)&oob.u);

		oob.u.a.VirtUnitNum = oob.u.a.SpareVirtUnitNum = cpu_to_le16(thisVUC);

		nftl_ग_लिखो_oob(mtd, ग_लिखोEUN * nftl->EraseSize + 8, 8,
			       &retlen, (अक्षर *)&oob.u);

		/* we link the new block to the chain only after the
                   block is पढ़ोy. It aव्योमs the हाल where the chain
                   could poपूर्णांक to a मुक्त block */
		अगर (lastEUN != BLOCK_NIL) अणु
			/* Both in our cache... */
			nftl->ReplUnitTable[lastEUN] = ग_लिखोEUN;
			/* ... and on the flash itself */
			nftl_पढ़ो_oob(mtd, (lastEUN * nftl->EraseSize) + 8,
				      8, &retlen, (अक्षर *)&oob.u);

			oob.u.a.ReplUnitNum = oob.u.a.SpareReplUnitNum
				= cpu_to_le16(ग_लिखोEUN);

			nftl_ग_लिखो_oob(mtd, (lastEUN * nftl->EraseSize) + 8,
				       8, &retlen, (अक्षर *)&oob.u);
		पूर्ण

		वापस ग_लिखोEUN;

	पूर्ण जबतक (silly2--);

	prपूर्णांकk(KERN_WARNING "Error folding to make room for Virtual Unit Chain 0x%x\n",
	       thisVUC);
	वापस BLOCK_NIL;
पूर्ण

अटल पूर्णांक nftl_ग_लिखोblock(काष्ठा mtd_blktrans_dev *mbd, अचिन्हित दीर्घ block,
			   अक्षर *buffer)
अणु
	काष्ठा NFTLrecord *nftl = (व्योम *)mbd;
	u16 ग_लिखोEUN;
	अचिन्हित दीर्घ blockofs = (block * 512) & (nftl->EraseSize - 1);
	माप_प्रकार retlen;
	काष्ठा nftl_oob oob;

	ग_लिखोEUN = NFTL_findग_लिखोunit(nftl, block);

	अगर (ग_लिखोEUN == BLOCK_NIL) अणु
		prपूर्णांकk(KERN_WARNING
		       "NFTL_writeblock(): Cannot find block to write to\n");
		/* If we _still_ haven't got a block to use, we're screwed */
		वापस 1;
	पूर्ण

	स_रखो(&oob, 0xff, माप(काष्ठा nftl_oob));
	oob.b.Status = oob.b.Status1 = SECTOR_USED;

	nftl_ग_लिखो(nftl->mbd.mtd, (ग_लिखोEUN * nftl->EraseSize) + blockofs,
		   512, &retlen, (अक्षर *)buffer, (अक्षर *)&oob);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_NFTL_RW */

अटल पूर्णांक nftl_पढ़ोblock(काष्ठा mtd_blktrans_dev *mbd, अचिन्हित दीर्घ block,
			  अक्षर *buffer)
अणु
	काष्ठा NFTLrecord *nftl = (व्योम *)mbd;
	काष्ठा mtd_info *mtd = nftl->mbd.mtd;
	u16 lastgoodEUN;
	u16 thisEUN = nftl->EUNtable[block / (nftl->EraseSize / 512)];
	अचिन्हित दीर्घ blockofs = (block * 512) & (nftl->EraseSize - 1);
	अचिन्हित पूर्णांक status;
	पूर्णांक silly = MAX_LOOPS;
	माप_प्रकार retlen;
	काष्ठा nftl_bci bci;

	lastgoodEUN = BLOCK_NIL;

	अगर (thisEUN != BLOCK_NIL) अणु
		जबतक (thisEUN < nftl->nb_blocks) अणु
			अगर (nftl_पढ़ो_oob(mtd, (thisEUN * nftl->EraseSize) +
					  blockofs, 8, &retlen,
					  (अक्षर *)&bci) < 0)
				status = SECTOR_IGNORE;
			अन्यथा
				status = bci.Status | bci.Status1;

			चयन (status) अणु
			हाल SECTOR_FREE:
				/* no modअगरication of a sector should follow a मुक्त sector */
				जाओ the_end;
			हाल SECTOR_DELETED:
				lastgoodEUN = BLOCK_NIL;
				अवरोध;
			हाल SECTOR_USED:
				lastgoodEUN = thisEUN;
				अवरोध;
			हाल SECTOR_IGNORE:
				अवरोध;
			शेष:
				prपूर्णांकk("Unknown status for block %ld in EUN %d: %x\n",
				       block, thisEUN, status);
				अवरोध;
			पूर्ण

			अगर (!silly--) अणु
				prपूर्णांकk(KERN_WARNING "Infinite loop in Virtual Unit Chain 0x%lx\n",
				       block / (nftl->EraseSize / 512));
				वापस 1;
			पूर्ण
			thisEUN = nftl->ReplUnitTable[thisEUN];
		पूर्ण
	पूर्ण

 the_end:
	अगर (lastgoodEUN == BLOCK_NIL) अणु
		/* the requested block is not on the media, वापस all 0x00 */
		स_रखो(buffer, 0, 512);
	पूर्ण अन्यथा अणु
		loff_t ptr = (lastgoodEUN * nftl->EraseSize) + blockofs;
		माप_प्रकार retlen;
		पूर्णांक res = mtd_पढ़ो(mtd, ptr, 512, &retlen, buffer);

		अगर (res < 0 && !mtd_is_bitflip(res))
			वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nftl_getgeo(काष्ठा mtd_blktrans_dev *dev,  काष्ठा hd_geometry *geo)
अणु
	काष्ठा NFTLrecord *nftl = (व्योम *)dev;

	geo->heads = nftl->heads;
	geo->sectors = nftl->sectors;
	geo->cylinders = nftl->cylinders;

	वापस 0;
पूर्ण

/****************************************************************************
 *
 * Module stuff
 *
 ****************************************************************************/


अटल काष्ठा mtd_blktrans_ops nftl_tr = अणु
	.name		= "nftl",
	.major		= NFTL_MAJOR,
	.part_bits	= NFTL_PARTN_BITS,
	.blksize 	= 512,
	.getgeo		= nftl_getgeo,
	.पढ़ोsect	= nftl_पढ़ोblock,
#अगर_घोषित CONFIG_NFTL_RW
	.ग_लिखोsect	= nftl_ग_लिखोblock,
#पूर्ण_अगर
	.add_mtd	= nftl_add_mtd,
	.हटाओ_dev	= nftl_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(nftl_tr);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("David Woodhouse <dwmw2@infradead.org>, Fabrice Bellard <fabrice.bellard@netgem.com> et al.");
MODULE_DESCRIPTION("Support code for NAND Flash Translation Layer, used on M-Systems DiskOnChip 2000 and Millennium");
MODULE_ALIAS_BLOCKDEV_MAJOR(NFTL_MAJOR);
