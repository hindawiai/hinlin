<शैली गुरु>
/* This version ported to the Linux-MTD प्रणाली by dwmw2@infradead.org
 *
 * Fixes: Arnalकरो Carvalho de Melo <acme@conectiva.com.br>
 * - fixes some leaks on failure in build_maps and ftl_notअगरy_add, cleanups
 *
 * Based on:
 */
/*======================================================================

    A Flash Translation Layer memory card driver

    This driver implements a disk-like block device driver with an
    apparent block size of 512 bytes क्रम flash memory cards.

    ftl_cs.c 1.62 2000/02/01 00:59:04

    The contents of this file are subject to the Mozilla Public
    License Version 1.1 (the "License"); you may not use this file
    except in compliance with the License. You may obtain a copy of
    the License at http://www.mozilla.org/MPL/

    Software distributed under the License is distributed on an "AS
    IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
    implied. See the License क्रम the specअगरic language governing
    rights and limitations under the License.

    The initial developer of the original code is David A. Hinds
    <dahinds@users.sourceक्रमge.net>.  Portions created by David A. Hinds
    are Copyright तऊ 1999 David A. Hinds.  All Rights Reserved.

    Alternatively, the contents of this file may be used under the
    terms of the GNU General Public License version 2 (the "GPL"), in
    which हाल the provisions of the GPL are applicable instead of the
    above.  If you wish to allow the use of your version of this file
    only under the terms of the GPL and not to allow others to use
    your version of this file under the MPL, indicate your decision
    by deleting the provisions above and replace them with the notice
    and other provisions required by the GPL.  If you करो not delete
    the provisions above, a recipient may use your version of this
    file under either the MPL or the GPL.

    LEGAL NOTE: The FTL क्रमmat is patented by M-Systems.  They have
    granted a license क्रम its use with PCMCIA devices:

     "M-Systems grants a royalty-मुक्त, non-exclusive license under
      any presently existing M-Systems पूर्णांकellectual property rights
      necessary क्रम the design and development of FTL-compatible
      drivers, file प्रणालीs and utilities using the data क्रमmats with
      PCMCIA PC Cards as described in the PCMCIA Flash Translation
      Layer (FTL) Specअगरication."

    Use of the FTL क्रमmat क्रम non-PCMCIA applications may be an
    infringement of these patents.  For additional inक्रमmation,
    contact M-Systems directly. M-Systems since acquired by Sandisk. 

======================================================================*/
#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/module.h>
#समावेश <linux/mtd/mtd.h>
/*#घोषणा PSYCHO_DEBUG */

#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/mtd/ftl.h>

/*====================================================================*/

/* Parameters that can be set with 'insmod' */
अटल पूर्णांक shuffle_freq = 50;
module_param(shuffle_freq, पूर्णांक, 0);

/*====================================================================*/

/* Major device # क्रम FTL device */
#अगर_अघोषित FTL_MAJOR
#घोषणा FTL_MAJOR	44
#पूर्ण_अगर


/*====================================================================*/

/* Maximum number of separate memory devices we'll allow */
#घोषणा MAX_DEV		4

/* Maximum number of regions per device */
#घोषणा MAX_REGION	4

/* Maximum number of partitions in an FTL region */
#घोषणा PART_BITS	4

/* Maximum number of outstanding erase requests per socket */
#घोषणा MAX_ERASE	8

/* Sector size -- shouldn't need to change */
#घोषणा SECTOR_SIZE	512


/* Each memory region corresponds to a minor device */
प्रकार काष्ठा partition_t अणु
    काष्ठा mtd_blktrans_dev mbd;
    uपूर्णांक32_t		state;
    uपूर्णांक32_t		*VirtualBlockMap;
    uपूर्णांक32_t		FreeTotal;
    काष्ठा eun_info_t अणु
	uपूर्णांक32_t		Offset;
	uपूर्णांक32_t		EraseCount;
	uपूर्णांक32_t		Free;
	uपूर्णांक32_t		Deleted;
    पूर्ण *EUNInfo;
    काष्ठा xfer_info_t अणु
	uपूर्णांक32_t		Offset;
	uपूर्णांक32_t		EraseCount;
	uपूर्णांक16_t		state;
    पूर्ण *XferInfo;
    uपूर्णांक16_t		bam_index;
    uपूर्णांक32_t		*bam_cache;
    uपूर्णांक16_t		DataUnits;
    uपूर्णांक32_t		BlocksPerUnit;
    erase_unit_header_t	header;
पूर्ण partition_t;

/* Partition state flags */
#घोषणा FTL_FORMATTED	0x01

/* Transfer unit states */
#घोषणा XFER_UNKNOWN	0x00
#घोषणा XFER_ERASING	0x01
#घोषणा XFER_ERASED	0x02
#घोषणा XFER_PREPARED	0x03
#घोषणा XFER_FAILED	0x04

/*======================================================================

    Scan_header() checks to see अगर a memory region contains an FTL
    partition.  build_maps() पढ़ोs all the erase unit headers, builds
    the erase unit map, and then builds the भव page map.

======================================================================*/

अटल पूर्णांक scan_header(partition_t *part)
अणु
    erase_unit_header_t header;
    loff_t offset, max_offset;
    माप_प्रकार ret;
    पूर्णांक err;
    part->header.FormattedSize = 0;
    max_offset = (0x100000<part->mbd.mtd->size)?0x100000:part->mbd.mtd->size;
    /* Search first megabyte क्रम a valid FTL header */
    क्रम (offset = 0;
	 (offset + माप(header)) < max_offset;
	 offset += part->mbd.mtd->erasesize ? : 0x2000) अणु

	err = mtd_पढ़ो(part->mbd.mtd, offset, माप(header), &ret,
                       (अचिन्हित अक्षर *)&header);

	अगर (err)
	    वापस err;

	अगर (म_भेद(header.DataOrgTuple+3, "FTL100") == 0) अवरोध;
    पूर्ण

    अगर (offset == max_offset) अणु
	prपूर्णांकk(KERN_NOTICE "ftl_cs: FTL header not found.\n");
	वापस -ENOENT;
    पूर्ण
    अगर (header.BlockSize != 9 ||
	(header.EraseUnitSize < 10) || (header.EraseUnitSize > 31) ||
	(header.NumTransferUnits >= le16_to_cpu(header.NumEraseUnits))) अणु
	prपूर्णांकk(KERN_NOTICE "ftl_cs: FTL header corrupt!\n");
	वापस -1;
    पूर्ण
    अगर ((1 << header.EraseUnitSize) != part->mbd.mtd->erasesize) अणु
	prपूर्णांकk(KERN_NOTICE "ftl: FTL EraseUnitSize %x != MTD erasesize %x\n",
	       1 << header.EraseUnitSize,part->mbd.mtd->erasesize);
	वापस -1;
    पूर्ण
    part->header = header;
    वापस 0;
पूर्ण

अटल पूर्णांक build_maps(partition_t *part)
अणु
    erase_unit_header_t header;
    uपूर्णांक16_t xvalid, xtrans, i;
    अचिन्हित blocks, j;
    पूर्णांक hdr_ok, ret = -1;
    sमाप_प्रकार retval;
    loff_t offset;

    /* Set up erase unit maps */
    part->DataUnits = le16_to_cpu(part->header.NumEraseUnits) -
	part->header.NumTransferUnits;
    part->EUNInfo = kदो_स्मृति_array(part->DataUnits, माप(काष्ठा eun_info_t),
                                  GFP_KERNEL);
    अगर (!part->EUNInfo)
	    जाओ out;
    क्रम (i = 0; i < part->DataUnits; i++)
	part->EUNInfo[i].Offset = 0xffffffff;
    part->XferInfo =
	kदो_स्मृति_array(part->header.NumTransferUnits,
                      माप(काष्ठा xfer_info_t),
                      GFP_KERNEL);
    अगर (!part->XferInfo)
	    जाओ out_EUNInfo;

    xvalid = xtrans = 0;
    क्रम (i = 0; i < le16_to_cpu(part->header.NumEraseUnits); i++) अणु
	offset = ((i + le16_to_cpu(part->header.FirstPhysicalEUN))
		      << part->header.EraseUnitSize);
	ret = mtd_पढ़ो(part->mbd.mtd, offset, माप(header), &retval,
                       (अचिन्हित अक्षर *)&header);

	अगर (ret)
	    जाओ out_XferInfo;

	ret = -1;
	/* Is this a transfer partition? */
	hdr_ok = (म_भेद(header.DataOrgTuple+3, "FTL100") == 0);
	अगर (hdr_ok && (le16_to_cpu(header.LogicalEUN) < part->DataUnits) &&
	    (part->EUNInfo[le16_to_cpu(header.LogicalEUN)].Offset == 0xffffffff)) अणु
	    part->EUNInfo[le16_to_cpu(header.LogicalEUN)].Offset = offset;
	    part->EUNInfo[le16_to_cpu(header.LogicalEUN)].EraseCount =
		le32_to_cpu(header.EraseCount);
	    xvalid++;
	पूर्ण अन्यथा अणु
	    अगर (xtrans == part->header.NumTransferUnits) अणु
		prपूर्णांकk(KERN_NOTICE "ftl_cs: format error: too many "
		       "transfer units!\n");
		जाओ out_XferInfo;
	    पूर्ण
	    अगर (hdr_ok && (le16_to_cpu(header.LogicalEUN) == 0xffff)) अणु
		part->XferInfo[xtrans].state = XFER_PREPARED;
		part->XferInfo[xtrans].EraseCount = le32_to_cpu(header.EraseCount);
	    पूर्ण अन्यथा अणु
		part->XferInfo[xtrans].state = XFER_UNKNOWN;
		/* Pick anything reasonable क्रम the erase count */
		part->XferInfo[xtrans].EraseCount =
		    le32_to_cpu(part->header.EraseCount);
	    पूर्ण
	    part->XferInfo[xtrans].Offset = offset;
	    xtrans++;
	पूर्ण
    पूर्ण
    /* Check क्रम क्रमmat trouble */
    header = part->header;
    अगर ((xtrans != header.NumTransferUnits) ||
	(xvalid+xtrans != le16_to_cpu(header.NumEraseUnits))) अणु
	prपूर्णांकk(KERN_NOTICE "ftl_cs: format error: erase units "
	       "don't add up!\n");
	जाओ out_XferInfo;
    पूर्ण

    /* Set up भव page map */
    blocks = le32_to_cpu(header.FormattedSize) >> header.BlockSize;
    part->VirtualBlockMap = vदो_स्मृति(array_size(blocks, माप(uपूर्णांक32_t)));
    अगर (!part->VirtualBlockMap)
	    जाओ out_XferInfo;

    स_रखो(part->VirtualBlockMap, 0xff, blocks * माप(uपूर्णांक32_t));
    part->BlocksPerUnit = (1 << header.EraseUnitSize) >> header.BlockSize;

    part->bam_cache = kदो_स्मृति_array(part->BlocksPerUnit, माप(uपूर्णांक32_t),
                                    GFP_KERNEL);
    अगर (!part->bam_cache)
	    जाओ out_VirtualBlockMap;

    part->bam_index = 0xffff;
    part->FreeTotal = 0;

    क्रम (i = 0; i < part->DataUnits; i++) अणु
	part->EUNInfo[i].Free = 0;
	part->EUNInfo[i].Deleted = 0;
	offset = part->EUNInfo[i].Offset + le32_to_cpu(header.BAMOffset);

	ret = mtd_पढ़ो(part->mbd.mtd, offset,
                       part->BlocksPerUnit * माप(uपूर्णांक32_t), &retval,
                       (अचिन्हित अक्षर *)part->bam_cache);

	अगर (ret)
		जाओ out_bam_cache;

	क्रम (j = 0; j < part->BlocksPerUnit; j++) अणु
	    अगर (BLOCK_FREE(le32_to_cpu(part->bam_cache[j]))) अणु
		part->EUNInfo[i].Free++;
		part->FreeTotal++;
	    पूर्ण अन्यथा अगर ((BLOCK_TYPE(le32_to_cpu(part->bam_cache[j])) == BLOCK_DATA) &&
		     (BLOCK_NUMBER(le32_to_cpu(part->bam_cache[j])) < blocks))
		part->VirtualBlockMap[BLOCK_NUMBER(le32_to_cpu(part->bam_cache[j]))] =
		    (i << header.EraseUnitSize) + (j << header.BlockSize);
	    अन्यथा अगर (BLOCK_DELETED(le32_to_cpu(part->bam_cache[j])))
		part->EUNInfo[i].Deleted++;
	पूर्ण
    पूर्ण

    ret = 0;
    जाओ out;

out_bam_cache:
    kमुक्त(part->bam_cache);
out_VirtualBlockMap:
    vमुक्त(part->VirtualBlockMap);
out_XferInfo:
    kमुक्त(part->XferInfo);
out_EUNInfo:
    kमुक्त(part->EUNInfo);
out:
    वापस ret;
पूर्ण /* build_maps */

/*======================================================================

    Erase_xfer() schedules an asynchronous erase operation क्रम a
    transfer unit.

======================================================================*/

अटल पूर्णांक erase_xfer(partition_t *part,
		      uपूर्णांक16_t xfernum)
अणु
    पूर्णांक ret;
    काष्ठा xfer_info_t *xfer;
    काष्ठा erase_info *erase;

    xfer = &part->XferInfo[xfernum];
    pr_debug("ftl_cs: erasing xfer unit at 0x%x\n", xfer->Offset);
    xfer->state = XFER_ERASING;

    /* Is there a मुक्त erase slot? Always in MTD. */


    erase=kदो_स्मृति(माप(काष्ठा erase_info), GFP_KERNEL);
    अगर (!erase)
            वापस -ENOMEM;

    erase->addr = xfer->Offset;
    erase->len = 1 << part->header.EraseUnitSize;

    ret = mtd_erase(part->mbd.mtd, erase);
    अगर (!ret) अणु
	xfer->state = XFER_ERASED;
	xfer->EraseCount++;
    पूर्ण अन्यथा अणु
	xfer->state = XFER_FAILED;
	pr_notice("ftl_cs: erase failed: err = %d\n", ret);
    पूर्ण

    kमुक्त(erase);

    वापस ret;
पूर्ण /* erase_xfer */

/*======================================================================

    Prepare_xfer() takes a freshly erased transfer unit and gives
    it an appropriate header.

======================================================================*/

अटल पूर्णांक prepare_xfer(partition_t *part, पूर्णांक i)
अणु
    erase_unit_header_t header;
    काष्ठा xfer_info_t *xfer;
    पूर्णांक nbam, ret;
    uपूर्णांक32_t ctl;
    sमाप_प्रकार retlen;
    loff_t offset;

    xfer = &part->XferInfo[i];
    xfer->state = XFER_FAILED;

    pr_debug("ftl_cs: preparing xfer unit at 0x%x\n", xfer->Offset);

    /* Write the transfer unit header */
    header = part->header;
    header.LogicalEUN = cpu_to_le16(0xffff);
    header.EraseCount = cpu_to_le32(xfer->EraseCount);

    ret = mtd_ग_लिखो(part->mbd.mtd, xfer->Offset, माप(header), &retlen,
                    (u_अक्षर *)&header);

    अगर (ret) अणु
	वापस ret;
    पूर्ण

    /* Write the BAM stub */
    nbam = DIV_ROUND_UP(part->BlocksPerUnit * माप(uपूर्णांक32_t) +
			le32_to_cpu(part->header.BAMOffset), SECTOR_SIZE);

    offset = xfer->Offset + le32_to_cpu(part->header.BAMOffset);
    ctl = cpu_to_le32(BLOCK_CONTROL);

    क्रम (i = 0; i < nbam; i++, offset += माप(uपूर्णांक32_t)) अणु

	ret = mtd_ग_लिखो(part->mbd.mtd, offset, माप(uपूर्णांक32_t), &retlen,
                        (u_अक्षर *)&ctl);

	अगर (ret)
	    वापस ret;
    पूर्ण
    xfer->state = XFER_PREPARED;
    वापस 0;

पूर्ण /* prepare_xfer */

/*======================================================================

    Copy_erase_unit() takes a full erase block and a transfer unit,
    copies everything to the transfer unit, then swaps the block
    poपूर्णांकers.

    All data blocks are copied to the corresponding blocks in the
    target unit, so the भव block map करोes not need to be
    updated.

======================================================================*/

अटल पूर्णांक copy_erase_unit(partition_t *part, uपूर्णांक16_t srcunit,
			   uपूर्णांक16_t xferunit)
अणु
    u_अक्षर buf[SECTOR_SIZE];
    काष्ठा eun_info_t *eun;
    काष्ठा xfer_info_t *xfer;
    uपूर्णांक32_t src, dest, मुक्त, i;
    uपूर्णांक16_t unit;
    पूर्णांक ret;
    sमाप_प्रकार retlen;
    loff_t offset;
    uपूर्णांक16_t srcunitswap = cpu_to_le16(srcunit);

    eun = &part->EUNInfo[srcunit];
    xfer = &part->XferInfo[xferunit];
    pr_debug("ftl_cs: copying block 0x%x to 0x%x\n",
	  eun->Offset, xfer->Offset);


    /* Read current BAM */
    अगर (part->bam_index != srcunit) अणु

	offset = eun->Offset + le32_to_cpu(part->header.BAMOffset);

	ret = mtd_पढ़ो(part->mbd.mtd, offset,
                       part->BlocksPerUnit * माप(uपूर्णांक32_t), &retlen,
                       (u_अक्षर *)(part->bam_cache));

	/* mark the cache bad, in हाल we get an error later */
	part->bam_index = 0xffff;

	अगर (ret) अणु
	    prपूर्णांकk( KERN_WARNING "ftl: Failed to read BAM cache in copy_erase_unit()!\n");
	    वापस ret;
	पूर्ण
    पूर्ण

    /* Write the LogicalEUN क्रम the transfer unit */
    xfer->state = XFER_UNKNOWN;
    offset = xfer->Offset + 20; /* Bad! */
    unit = cpu_to_le16(0x7fff);

    ret = mtd_ग_लिखो(part->mbd.mtd, offset, माप(uपूर्णांक16_t), &retlen,
                    (u_अक्षर *)&unit);

    अगर (ret) अणु
	prपूर्णांकk( KERN_WARNING "ftl: Failed to write back to BAM cache in copy_erase_unit()!\n");
	वापस ret;
    पूर्ण

    /* Copy all data blocks from source unit to transfer unit */
    src = eun->Offset; dest = xfer->Offset;

    मुक्त = 0;
    ret = 0;
    क्रम (i = 0; i < part->BlocksPerUnit; i++) अणु
	चयन (BLOCK_TYPE(le32_to_cpu(part->bam_cache[i]))) अणु
	हाल BLOCK_CONTROL:
	    /* This माला_लो updated later */
	    अवरोध;
	हाल BLOCK_DATA:
	हाल BLOCK_REPLACEMENT:
	    ret = mtd_पढ़ो(part->mbd.mtd, src, SECTOR_SIZE, &retlen,
                           (u_अक्षर *)buf);
	    अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "ftl: Error reading old xfer unit in copy_erase_unit\n");
		वापस ret;
            पूर्ण


	    ret = mtd_ग_लिखो(part->mbd.mtd, dest, SECTOR_SIZE, &retlen,
                            (u_अक्षर *)buf);
	    अगर (ret)  अणु
		prपूर्णांकk(KERN_WARNING "ftl: Error writing new xfer unit in copy_erase_unit\n");
		वापस ret;
            पूर्ण

	    अवरोध;
	शेष:
	    /* All other blocks must be मुक्त */
	    part->bam_cache[i] = cpu_to_le32(0xffffffff);
	    मुक्त++;
	    अवरोध;
	पूर्ण
	src += SECTOR_SIZE;
	dest += SECTOR_SIZE;
    पूर्ण

    /* Write the BAM to the transfer unit */
    ret = mtd_ग_लिखो(part->mbd.mtd,
                    xfer->Offset + le32_to_cpu(part->header.BAMOffset),
                    part->BlocksPerUnit * माप(पूर्णांक32_t),
                    &retlen,
                    (u_अक्षर *)part->bam_cache);
    अगर (ret) अणु
	prपूर्णांकk( KERN_WARNING "ftl: Error writing BAM in copy_erase_unit\n");
	वापस ret;
    पूर्ण


    /* All clear? Then update the LogicalEUN again */
    ret = mtd_ग_लिखो(part->mbd.mtd, xfer->Offset + 20, माप(uपूर्णांक16_t),
                    &retlen, (u_अक्षर *)&srcunitswap);

    अगर (ret) अणु
	prपूर्णांकk(KERN_WARNING "ftl: Error writing new LogicalEUN in copy_erase_unit\n");
	वापस ret;
    पूर्ण


    /* Update the maps and usage stats*/
    swap(xfer->EraseCount, eun->EraseCount);
    swap(xfer->Offset, eun->Offset);
    part->FreeTotal -= eun->Free;
    part->FreeTotal += मुक्त;
    eun->Free = मुक्त;
    eun->Deleted = 0;

    /* Now, the cache should be valid क्रम the new block */
    part->bam_index = srcunit;

    वापस 0;
पूर्ण /* copy_erase_unit */

/*======================================================================

    reclaim_block() picks a full erase unit and a transfer unit and
    then calls copy_erase_unit() to copy one to the other.  Then, it
    schedules an erase on the expired block.

    What's a good way to decide which transfer unit and which erase
    unit to use?  Beats me.  My way is to always pick the transfer
    unit with the fewest erases, and usually pick the data unit with
    the most deleted blocks.  But with a small probability, pick the
    oldest data unit instead.  This means that we generally postpone
    the next reclamation as दीर्घ as possible, but shuffle अटल
    stuff around a bit क्रम wear leveling.

======================================================================*/

अटल पूर्णांक reclaim_block(partition_t *part)
अणु
    uपूर्णांक16_t i, eun, xfer;
    uपूर्णांक32_t best;
    पूर्णांक queued, ret;

    pr_debug("ftl_cs: reclaiming space...\n");
    pr_debug("NumTransferUnits == %x\n", part->header.NumTransferUnits);
    /* Pick the least erased transfer unit */
    best = 0xffffffff; xfer = 0xffff;
    करो अणु
	queued = 0;
	क्रम (i = 0; i < part->header.NumTransferUnits; i++) अणु
	    पूर्णांक n=0;
	    अगर (part->XferInfo[i].state == XFER_UNKNOWN) अणु
		pr_debug("XferInfo[%d].state == XFER_UNKNOWN\n",i);
		n=1;
		erase_xfer(part, i);
	    पूर्ण
	    अगर (part->XferInfo[i].state == XFER_ERASING) अणु
		pr_debug("XferInfo[%d].state == XFER_ERASING\n",i);
		n=1;
		queued = 1;
	    पूर्ण
	    अन्यथा अगर (part->XferInfo[i].state == XFER_ERASED) अणु
		pr_debug("XferInfo[%d].state == XFER_ERASED\n",i);
		n=1;
		prepare_xfer(part, i);
	    पूर्ण
	    अगर (part->XferInfo[i].state == XFER_PREPARED) अणु
		pr_debug("XferInfo[%d].state == XFER_PREPARED\n",i);
		n=1;
		अगर (part->XferInfo[i].EraseCount <= best) अणु
		    best = part->XferInfo[i].EraseCount;
		    xfer = i;
		पूर्ण
	    पूर्ण
		अगर (!n)
		    pr_debug("XferInfo[%d].state == %x\n",i, part->XferInfo[i].state);

	पूर्ण
	अगर (xfer == 0xffff) अणु
	    अगर (queued) अणु
		pr_debug("ftl_cs: waiting for transfer "
		      "unit to be prepared...\n");
		mtd_sync(part->mbd.mtd);
	    पूर्ण अन्यथा अणु
		अटल पूर्णांक ne = 0;
		अगर (++ne < 5)
		    prपूर्णांकk(KERN_NOTICE "ftl_cs: reclaim failed: no "
			   "suitable transfer units!\n");
		अन्यथा
		    pr_debug("ftl_cs: reclaim failed: no "
			  "suitable transfer units!\n");

		वापस -EIO;
	    पूर्ण
	पूर्ण
    पूर्ण जबतक (xfer == 0xffff);

    eun = 0;
    अगर ((jअगरfies % shuffle_freq) == 0) अणु
	pr_debug("ftl_cs: recycling freshest block...\n");
	best = 0xffffffff;
	क्रम (i = 0; i < part->DataUnits; i++)
	    अगर (part->EUNInfo[i].EraseCount <= best) अणु
		best = part->EUNInfo[i].EraseCount;
		eun = i;
	    पूर्ण
    पूर्ण अन्यथा अणु
	best = 0;
	क्रम (i = 0; i < part->DataUnits; i++)
	    अगर (part->EUNInfo[i].Deleted >= best) अणु
		best = part->EUNInfo[i].Deleted;
		eun = i;
	    पूर्ण
	अगर (best == 0) अणु
	    अटल पूर्णांक ne = 0;
	    अगर (++ne < 5)
		prपूर्णांकk(KERN_NOTICE "ftl_cs: reclaim failed: "
		       "no free blocks!\n");
	    अन्यथा
		pr_debug("ftl_cs: reclaim failed: "
		       "no free blocks!\n");

	    वापस -EIO;
	पूर्ण
    पूर्ण
    ret = copy_erase_unit(part, eun, xfer);
    अगर (!ret)
	erase_xfer(part, xfer);
    अन्यथा
	prपूर्णांकk(KERN_NOTICE "ftl_cs: copy_erase_unit failed!\n");
    वापस ret;
पूर्ण /* reclaim_block */

/*======================================================================

    Find_मुक्त() searches क्रम a मुक्त block.  If necessary, it updates
    the BAM cache क्रम the erase unit containing the मुक्त block.  It
    वापसs the block index -- the erase unit is just the currently
    cached unit.  If there are no मुक्त blocks, it वापसs 0 -- this
    is never a valid data block because it contains the header.

======================================================================*/

#अगर_घोषित PSYCHO_DEBUG
अटल व्योम dump_lists(partition_t *part)
अणु
    पूर्णांक i;
    prपूर्णांकk(KERN_DEBUG "ftl_cs: Free total = %d\n", part->FreeTotal);
    क्रम (i = 0; i < part->DataUnits; i++)
	prपूर्णांकk(KERN_DEBUG "ftl_cs:   unit %d: %d phys, %d free, "
	       "%d deleted\n", i,
	       part->EUNInfo[i].Offset >> part->header.EraseUnitSize,
	       part->EUNInfo[i].Free, part->EUNInfo[i].Deleted);
पूर्ण
#पूर्ण_अगर

अटल uपूर्णांक32_t find_मुक्त(partition_t *part)
अणु
    uपूर्णांक16_t stop, eun;
    uपूर्णांक32_t blk;
    माप_प्रकार retlen;
    पूर्णांक ret;

    /* Find an erase unit with some मुक्त space */
    stop = (part->bam_index == 0xffff) ? 0 : part->bam_index;
    eun = stop;
    करो अणु
	अगर (part->EUNInfo[eun].Free != 0) अवरोध;
	/* Wrap around at end of table */
	अगर (++eun == part->DataUnits) eun = 0;
    पूर्ण जबतक (eun != stop);

    अगर (part->EUNInfo[eun].Free == 0)
	वापस 0;

    /* Is this unit's BAM cached? */
    अगर (eun != part->bam_index) अणु
	/* Invalidate cache */
	part->bam_index = 0xffff;

	ret = mtd_पढ़ो(part->mbd.mtd,
                       part->EUNInfo[eun].Offset + le32_to_cpu(part->header.BAMOffset),
                       part->BlocksPerUnit * माप(uपूर्णांक32_t),
                       &retlen,
                       (u_अक्षर *)(part->bam_cache));

	अगर (ret) अणु
	    prपूर्णांकk(KERN_WARNING"ftl: Error reading BAM in find_free\n");
	    वापस 0;
	पूर्ण
	part->bam_index = eun;
    पूर्ण

    /* Find a मुक्त block */
    क्रम (blk = 0; blk < part->BlocksPerUnit; blk++)
	अगर (BLOCK_FREE(le32_to_cpu(part->bam_cache[blk]))) अवरोध;
    अगर (blk == part->BlocksPerUnit) अणु
#अगर_घोषित PSYCHO_DEBUG
	अटल पूर्णांक ne = 0;
	अगर (++ne == 1)
	    dump_lists(part);
#पूर्ण_अगर
	prपूर्णांकk(KERN_NOTICE "ftl_cs: bad free list!\n");
	वापस 0;
    पूर्ण
    pr_debug("ftl_cs: found free block at %d in %d\n", blk, eun);
    वापस blk;

पूर्ण /* find_मुक्त */


/*======================================================================

    Read a series of sectors from an FTL partition.

======================================================================*/

अटल पूर्णांक ftl_पढ़ो(partition_t *part, caddr_t buffer,
		    u_दीर्घ sector, u_दीर्घ nblocks)
अणु
    uपूर्णांक32_t log_addr, bsize;
    u_दीर्घ i;
    पूर्णांक ret;
    माप_प्रकार offset, retlen;

    pr_debug("ftl_cs: ftl_read(0x%p, 0x%lx, %ld)\n",
	  part, sector, nblocks);
    अगर (!(part->state & FTL_FORMATTED)) अणु
	prपूर्णांकk(KERN_NOTICE "ftl_cs: bad partition\n");
	वापस -EIO;
    पूर्ण
    bsize = 1 << part->header.EraseUnitSize;

    क्रम (i = 0; i < nblocks; i++) अणु
	अगर (((sector+i) * SECTOR_SIZE) >= le32_to_cpu(part->header.FormattedSize)) अणु
	    prपूर्णांकk(KERN_NOTICE "ftl_cs: bad read offset\n");
	    वापस -EIO;
	पूर्ण
	log_addr = part->VirtualBlockMap[sector+i];
	अगर (log_addr == 0xffffffff)
	    स_रखो(buffer, 0, SECTOR_SIZE);
	अन्यथा अणु
	    offset = (part->EUNInfo[log_addr / bsize].Offset
			  + (log_addr % bsize));
	    ret = mtd_पढ़ो(part->mbd.mtd, offset, SECTOR_SIZE, &retlen,
                           (u_अक्षर *)buffer);

	    अगर (ret) अणु
		prपूर्णांकk(KERN_WARNING "Error reading MTD device in ftl_read()\n");
		वापस ret;
	    पूर्ण
	पूर्ण
	buffer += SECTOR_SIZE;
    पूर्ण
    वापस 0;
पूर्ण /* ftl_पढ़ो */

/*======================================================================

    Write a series of sectors to an FTL partition

======================================================================*/

अटल पूर्णांक set_bam_entry(partition_t *part, uपूर्णांक32_t log_addr,
			 uपूर्णांक32_t virt_addr)
अणु
    uपूर्णांक32_t bsize, blk, le_virt_addr;
#अगर_घोषित PSYCHO_DEBUG
    uपूर्णांक32_t old_addr;
#पूर्ण_अगर
    uपूर्णांक16_t eun;
    पूर्णांक ret;
    माप_प्रकार retlen, offset;

    pr_debug("ftl_cs: set_bam_entry(0x%p, 0x%x, 0x%x)\n",
	  part, log_addr, virt_addr);
    bsize = 1 << part->header.EraseUnitSize;
    eun = log_addr / bsize;
    blk = (log_addr % bsize) / SECTOR_SIZE;
    offset = (part->EUNInfo[eun].Offset + blk * माप(uपूर्णांक32_t) +
		  le32_to_cpu(part->header.BAMOffset));

#अगर_घोषित PSYCHO_DEBUG
    ret = mtd_पढ़ो(part->mbd.mtd, offset, माप(uपूर्णांक32_t), &retlen,
                   (u_अक्षर *)&old_addr);
    अगर (ret) अणु
	prपूर्णांकk(KERN_WARNING"ftl: Error reading old_addr in set_bam_entry: %d\n",ret);
	वापस ret;
    पूर्ण
    old_addr = le32_to_cpu(old_addr);

    अगर (((virt_addr == 0xfffffffe) && !BLOCK_FREE(old_addr)) ||
	((virt_addr == 0) && (BLOCK_TYPE(old_addr) != BLOCK_DATA)) ||
	(!BLOCK_DELETED(virt_addr) && (old_addr != 0xfffffffe))) अणु
	अटल पूर्णांक ne = 0;
	अगर (++ne < 5) अणु
	    prपूर्णांकk(KERN_NOTICE "ftl_cs: set_bam_entry() inconsistency!\n");
	    prपूर्णांकk(KERN_NOTICE "ftl_cs:   log_addr = 0x%x, old = 0x%x"
		   ", new = 0x%x\n", log_addr, old_addr, virt_addr);
	पूर्ण
	वापस -EIO;
    पूर्ण
#पूर्ण_अगर
    le_virt_addr = cpu_to_le32(virt_addr);
    अगर (part->bam_index == eun) अणु
#अगर_घोषित PSYCHO_DEBUG
	अगर (le32_to_cpu(part->bam_cache[blk]) != old_addr) अणु
	    अटल पूर्णांक ne = 0;
	    अगर (++ne < 5) अणु
		prपूर्णांकk(KERN_NOTICE "ftl_cs: set_bam_entry() "
		       "inconsistency!\n");
		prपूर्णांकk(KERN_NOTICE "ftl_cs:   log_addr = 0x%x, cache"
		       " = 0x%x\n",
		       le32_to_cpu(part->bam_cache[blk]), old_addr);
	    पूर्ण
	    वापस -EIO;
	पूर्ण
#पूर्ण_अगर
	part->bam_cache[blk] = le_virt_addr;
    पूर्ण
    ret = mtd_ग_लिखो(part->mbd.mtd, offset, माप(uपूर्णांक32_t), &retlen,
                    (u_अक्षर *)&le_virt_addr);

    अगर (ret) अणु
	prपूर्णांकk(KERN_NOTICE "ftl_cs: set_bam_entry() failed!\n");
	prपूर्णांकk(KERN_NOTICE "ftl_cs:   log_addr = 0x%x, new = 0x%x\n",
	       log_addr, virt_addr);
    पूर्ण
    वापस ret;
पूर्ण /* set_bam_entry */

अटल पूर्णांक ftl_ग_लिखो(partition_t *part, caddr_t buffer,
		     u_दीर्घ sector, u_दीर्घ nblocks)
अणु
    uपूर्णांक32_t bsize, log_addr, virt_addr, old_addr, blk;
    u_दीर्घ i;
    पूर्णांक ret;
    माप_प्रकार retlen, offset;

    pr_debug("ftl_cs: ftl_write(0x%p, %ld, %ld)\n",
	  part, sector, nblocks);
    अगर (!(part->state & FTL_FORMATTED)) अणु
	prपूर्णांकk(KERN_NOTICE "ftl_cs: bad partition\n");
	वापस -EIO;
    पूर्ण
    /* See अगर we need to reclaim space, beक्रमe we start */
    जबतक (part->FreeTotal < nblocks) अणु
	ret = reclaim_block(part);
	अगर (ret)
	    वापस ret;
    पूर्ण

    bsize = 1 << part->header.EraseUnitSize;

    virt_addr = sector * SECTOR_SIZE | BLOCK_DATA;
    क्रम (i = 0; i < nblocks; i++) अणु
	अगर (virt_addr >= le32_to_cpu(part->header.FormattedSize)) अणु
	    prपूर्णांकk(KERN_NOTICE "ftl_cs: bad write offset\n");
	    वापस -EIO;
	पूर्ण

	/* Grab a मुक्त block */
	blk = find_मुक्त(part);
	अगर (blk == 0) अणु
	    अटल पूर्णांक ne = 0;
	    अगर (++ne < 5)
		prपूर्णांकk(KERN_NOTICE "ftl_cs: internal error: "
		       "no free blocks!\n");
	    वापस -ENOSPC;
	पूर्ण

	/* Tag the BAM entry, and ग_लिखो the new block */
	log_addr = part->bam_index * bsize + blk * SECTOR_SIZE;
	part->EUNInfo[part->bam_index].Free--;
	part->FreeTotal--;
	अगर (set_bam_entry(part, log_addr, 0xfffffffe))
	    वापस -EIO;
	part->EUNInfo[part->bam_index].Deleted++;
	offset = (part->EUNInfo[part->bam_index].Offset +
		      blk * SECTOR_SIZE);
	ret = mtd_ग_लिखो(part->mbd.mtd, offset, SECTOR_SIZE, &retlen, buffer);

	अगर (ret) अणु
	    prपूर्णांकk(KERN_NOTICE "ftl_cs: block write failed!\n");
	    prपूर्णांकk(KERN_NOTICE "ftl_cs:   log_addr = 0x%x, virt_addr"
		   " = 0x%x, Offset = 0x%zx\n", log_addr, virt_addr,
		   offset);
	    वापस -EIO;
	पूर्ण

	/* Only delete the old entry when the new entry is पढ़ोy */
	old_addr = part->VirtualBlockMap[sector+i];
	अगर (old_addr != 0xffffffff) अणु
	    part->VirtualBlockMap[sector+i] = 0xffffffff;
	    part->EUNInfo[old_addr/bsize].Deleted++;
	    अगर (set_bam_entry(part, old_addr, 0))
		वापस -EIO;
	पूर्ण

	/* Finally, set up the new poपूर्णांकers */
	अगर (set_bam_entry(part, log_addr, virt_addr))
	    वापस -EIO;
	part->VirtualBlockMap[sector+i] = log_addr;
	part->EUNInfo[part->bam_index].Deleted--;

	buffer += SECTOR_SIZE;
	virt_addr += SECTOR_SIZE;
    पूर्ण
    वापस 0;
पूर्ण /* ftl_ग_लिखो */

अटल पूर्णांक ftl_getgeo(काष्ठा mtd_blktrans_dev *dev, काष्ठा hd_geometry *geo)
अणु
	partition_t *part = (व्योम *)dev;
	u_दीर्घ sect;

	/* Sort of arbitrary: round size करोwn to 4KiB boundary */
	sect = le32_to_cpu(part->header.FormattedSize)/SECTOR_SIZE;

	geo->heads = 1;
	geo->sectors = 8;
	geo->cylinders = sect >> 3;

	वापस 0;
पूर्ण

अटल पूर्णांक ftl_पढ़ोsect(काष्ठा mtd_blktrans_dev *dev,
			      अचिन्हित दीर्घ block, अक्षर *buf)
अणु
	वापस ftl_पढ़ो((व्योम *)dev, buf, block, 1);
पूर्ण

अटल पूर्णांक ftl_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev,
			      अचिन्हित दीर्घ block, अक्षर *buf)
अणु
	वापस ftl_ग_लिखो((व्योम *)dev, buf, block, 1);
पूर्ण

अटल पूर्णांक ftl_discardsect(काष्ठा mtd_blktrans_dev *dev,
			   अचिन्हित दीर्घ sector, अचिन्हित nr_sects)
अणु
	partition_t *part = (व्योम *)dev;
	uपूर्णांक32_t bsize = 1 << part->header.EraseUnitSize;

	pr_debug("FTL erase sector %ld for %d sectors\n",
	      sector, nr_sects);

	जबतक (nr_sects) अणु
		uपूर्णांक32_t old_addr = part->VirtualBlockMap[sector];
		अगर (old_addr != 0xffffffff) अणु
			part->VirtualBlockMap[sector] = 0xffffffff;
			part->EUNInfo[old_addr/bsize].Deleted++;
			अगर (set_bam_entry(part, old_addr, 0))
				वापस -EIO;
		पूर्ण
		nr_sects--;
		sector++;
	पूर्ण

	वापस 0;
पूर्ण
/*====================================================================*/

अटल व्योम ftl_मुक्तpart(partition_t *part)
अणु
	vमुक्त(part->VirtualBlockMap);
	part->VirtualBlockMap = शून्य;
	kमुक्त(part->EUNInfo);
	part->EUNInfo = शून्य;
	kमुक्त(part->XferInfo);
	part->XferInfo = शून्य;
	kमुक्त(part->bam_cache);
	part->bam_cache = शून्य;
पूर्ण /* ftl_मुक्तpart */

अटल व्योम ftl_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	partition_t *partition;

	partition = kzalloc(माप(partition_t), GFP_KERNEL);

	अगर (!partition) अणु
		prपूर्णांकk(KERN_WARNING "No memory to scan for FTL on %s\n",
		       mtd->name);
		वापस;
	पूर्ण

	partition->mbd.mtd = mtd;

	अगर ((scan_header(partition) == 0) &&
	    (build_maps(partition) == 0)) अणु

		partition->state = FTL_FORMATTED;
#अगर_घोषित PCMCIA_DEBUG
		prपूर्णांकk(KERN_INFO "ftl_cs: opening %d KiB FTL partition\n",
		       le32_to_cpu(partition->header.FormattedSize) >> 10);
#पूर्ण_अगर
		partition->mbd.size = le32_to_cpu(partition->header.FormattedSize) >> 9;

		partition->mbd.tr = tr;
		partition->mbd.devnum = -1;
		अगर (!add_mtd_blktrans_dev((व्योम *)partition))
			वापस;
	पूर्ण

	kमुक्त(partition);
पूर्ण

अटल व्योम ftl_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	del_mtd_blktrans_dev(dev);
	ftl_मुक्तpart((partition_t *)dev);
पूर्ण

अटल काष्ठा mtd_blktrans_ops ftl_tr = अणु
	.name		= "ftl",
	.major		= FTL_MAJOR,
	.part_bits	= PART_BITS,
	.blksize 	= SECTOR_SIZE,
	.पढ़ोsect	= ftl_पढ़ोsect,
	.ग_लिखोsect	= ftl_ग_लिखोsect,
	.discard	= ftl_discardsect,
	.getgeo		= ftl_getgeo,
	.add_mtd	= ftl_add_mtd,
	.हटाओ_dev	= ftl_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(ftl_tr);

MODULE_LICENSE("Dual MPL/GPL");
MODULE_AUTHOR("David Hinds <dahinds@users.sourceforge.net>");
MODULE_DESCRIPTION("Support code for Flash Translation Layer, used on PCMCIA devices");
