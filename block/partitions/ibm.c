<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author(s)......: Holger Smolinski <Holger.Smolinski@de.ibm.com>
 *                  Volker Sameske <sameske@de.ibm.com>
 * Bugreports.to..: <Linux390@de.ibm.com>
 * Copyright IBM Corp. 1999, 2012
 */

#समावेश <linux/buffer_head.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/dasd.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/vtoc.h>
#समावेश <linux/module.h>
#समावेश <linux/dasd_mod.h>

#समावेश "check.h"

जोड़ label_t अणु
	काष्ठा vtoc_volume_label_cdl vol;
	काष्ठा vtoc_volume_label_ldl lnx;
	काष्ठा vtoc_cms_label cms;
पूर्ण;

/*
 * compute the block number from a
 * cyl-cyl-head-head काष्ठाure
 */
अटल sector_t cchh2blk(काष्ठा vtoc_cchh *ptr, काष्ठा hd_geometry *geo)
अणु
	sector_t cyl;
	__u16 head;

	/* decode cylinder and heads क्रम large volumes */
	cyl = ptr->hh & 0xFFF0;
	cyl <<= 12;
	cyl |= ptr->cc;
	head = ptr->hh & 0x000F;
	वापस cyl * geo->heads * geo->sectors +
	       head * geo->sectors;
पूर्ण

/*
 * compute the block number from a
 * cyl-cyl-head-head-block काष्ठाure
 */
अटल sector_t cchhb2blk(काष्ठा vtoc_cchhb *ptr, काष्ठा hd_geometry *geo)
अणु
	sector_t cyl;
	__u16 head;

	/* decode cylinder and heads क्रम large volumes */
	cyl = ptr->hh & 0xFFF0;
	cyl <<= 12;
	cyl |= ptr->cc;
	head = ptr->hh & 0x000F;
	वापस	cyl * geo->heads * geo->sectors +
		head * geo->sectors +
		ptr->b;
पूर्ण

अटल पूर्णांक find_label(काष्ठा parsed_partitions *state,
		      dasd_inक्रमmation2_t *info,
		      काष्ठा hd_geometry *geo,
		      पूर्णांक blocksize,
		      sector_t *labअन्यथाct,
		      अक्षर name[],
		      अक्षर type[],
		      जोड़ label_t *label)
अणु
	Sector sect;
	अचिन्हित अक्षर *data;
	sector_t testsect[3];
	अचिन्हित अक्षर temp[5];
	पूर्णांक found = 0;
	पूर्णांक i, testcount;

	/* There a three places where we may find a valid label:
	 * - on an ECKD disk it's block 2
	 * - on an FBA disk it's block 1
	 * - on an CMS क्रमmatted FBA disk it is sector 1, even अगर the block size
	 *   is larger than 512 bytes (possible अगर the DIAG discipline is used)
	 * If we have a valid info काष्ठाure, then we know exactly which हाल we
	 * have, otherwise we just search through all possebilities.
	 */
	अगर (info) अणु
		अगर ((info->cu_type == 0x6310 && info->dev_type == 0x9336) ||
		    (info->cu_type == 0x3880 && info->dev_type == 0x3370))
			testsect[0] = info->label_block;
		अन्यथा
			testsect[0] = info->label_block * (blocksize >> 9);
		testcount = 1;
	पूर्ण अन्यथा अणु
		testsect[0] = 1;
		testsect[1] = (blocksize >> 9);
		testsect[2] = 2 * (blocksize >> 9);
		testcount = 3;
	पूर्ण
	क्रम (i = 0; i < testcount; ++i) अणु
		data = पढ़ो_part_sector(state, testsect[i], &sect);
		अगर (data == शून्य)
			जारी;
		स_नकल(label, data, माप(*label));
		स_नकल(temp, data, 4);
		temp[4] = 0;
		EBCASC(temp, 4);
		put_dev_sector(sect);
		अगर (!म_भेद(temp, "VOL1") ||
		    !म_भेद(temp, "LNX1") ||
		    !म_भेद(temp, "CMS1")) अणु
			अगर (!म_भेद(temp, "VOL1")) अणु
				म_नकलन(type, label->vol.vollbl, 4);
				म_नकलन(name, label->vol.volid, 6);
			पूर्ण अन्यथा अणु
				म_नकलन(type, label->lnx.vollbl, 4);
				म_नकलन(name, label->lnx.volid, 6);
			पूर्ण
			EBCASC(type, 4);
			EBCASC(name, 6);
			*labअन्यथाct = testsect[i];
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		स_रखो(label, 0, माप(*label));

	वापस found;
पूर्ण

अटल पूर्णांक find_vol1_partitions(काष्ठा parsed_partitions *state,
				काष्ठा hd_geometry *geo,
				पूर्णांक blocksize,
				अक्षर name[],
				जोड़ label_t *label)
अणु
	sector_t blk;
	पूर्णांक counter;
	अक्षर पंचांगp[64];
	Sector sect;
	अचिन्हित अक्षर *data;
	loff_t offset, size;
	काष्ठा vtoc_क्रमmat1_label f1;
	पूर्णांक secperblk;

	snम_लिखो(पंचांगp, माप(पंचांगp), "VOL1/%8s:", name);
	strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	/*
	 * get start of VTOC from the disk label and then search क्रम क्रमmat1
	 * and क्रमmat8 labels
	 */
	secperblk = blocksize >> 9;
	blk = cchhb2blk(&label->vol.vtoc, geo) + 1;
	counter = 0;
	data = पढ़ो_part_sector(state, blk * secperblk, &sect);
	जबतक (data != शून्य) अणु
		स_नकल(&f1, data, माप(काष्ठा vtoc_क्रमmat1_label));
		put_dev_sector(sect);
		/* skip FMT4 / FMT5 / FMT7 labels */
		अगर (f1.DS1FMTID == _ascebc['4']
		    || f1.DS1FMTID == _ascebc['5']
		    || f1.DS1FMTID == _ascebc['7']
		    || f1.DS1FMTID == _ascebc['9']) अणु
			blk++;
			data = पढ़ो_part_sector(state, blk * secperblk, &sect);
			जारी;
		पूर्ण
		/* only FMT1 and 8 labels valid at this poपूर्णांक */
		अगर (f1.DS1FMTID != _ascebc['1'] &&
		    f1.DS1FMTID != _ascebc['8'])
			अवरोध;
		/* OK, we got valid partition data */
		offset = cchh2blk(&f1.DS1EXT1.llimit, geo);
		size  = cchh2blk(&f1.DS1EXT1.ulimit, geo) -
			offset + geo->sectors;
		offset *= secperblk;
		size *= secperblk;
		अगर (counter >= state->limit)
			अवरोध;
		put_partition(state, counter + 1, offset, size);
		counter++;
		blk++;
		data = पढ़ो_part_sector(state, blk * secperblk, &sect);
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);

	अगर (!data)
		वापस -1;

	वापस 1;
पूर्ण

अटल पूर्णांक find_lnx1_partitions(काष्ठा parsed_partitions *state,
				काष्ठा hd_geometry *geo,
				पूर्णांक blocksize,
				अक्षर name[],
				जोड़ label_t *label,
				sector_t labअन्यथाct,
				loff_t i_size,
				dasd_inक्रमmation2_t *info)
अणु
	loff_t offset, geo_size, size;
	अक्षर पंचांगp[64];
	पूर्णांक secperblk;

	snम_लिखो(पंचांगp, माप(पंचांगp), "LNX1/%8s:", name);
	strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
	secperblk = blocksize >> 9;
	अगर (label->lnx.ldl_version == 0xf2) अणु
		size = label->lnx.क्रमmatted_blocks * secperblk;
	पूर्ण अन्यथा अणु
		/*
		 * Formated w/o large volume support. If the sanity check
		 * 'size based on geo == size based on i_size' is true, then
		 * we can safely assume that we know the क्रमmatted size of
		 * the disk, otherwise we need additional inक्रमmation
		 * that we can only get from a real DASD device.
		 */
		geo_size = geo->cylinders * geo->heads
			* geo->sectors * secperblk;
		size = i_size >> 9;
		अगर (size != geo_size) अणु
			अगर (!info) अणु
				strlcat(state->pp_buf, "\n", PAGE_SIZE);
				वापस 1;
			पूर्ण
			अगर (!म_भेद(info->type, "ECKD"))
				अगर (geo_size < size)
					size = geo_size;
			/* अन्यथा keep size based on i_size */
		पूर्ण
	पूर्ण
	/* first and only partition starts in the first block after the label */
	offset = labअन्यथाct + secperblk;
	put_partition(state, 1, offset, size - offset);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण

अटल पूर्णांक find_cms1_partitions(काष्ठा parsed_partitions *state,
				काष्ठा hd_geometry *geo,
				पूर्णांक blocksize,
				अक्षर name[],
				जोड़ label_t *label,
				sector_t labअन्यथाct)
अणु
	loff_t offset, size;
	अक्षर पंचांगp[64];
	पूर्णांक secperblk;

	/*
	 * VM style CMS1 labeled disk
	 */
	blocksize = label->cms.block_size;
	secperblk = blocksize >> 9;
	अगर (label->cms.disk_offset != 0) अणु
		snम_लिखो(पंचांगp, माप(पंचांगp), "CMS1/%8s(MDSK):", name);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		/* disk is reserved minidisk */
		offset = label->cms.disk_offset * secperblk;
		size = (label->cms.block_count - 1) * secperblk;
	पूर्ण अन्यथा अणु
		snम_लिखो(पंचांगp, माप(पंचांगp), "CMS1/%8s:", name);
		strlcat(state->pp_buf, पंचांगp, PAGE_SIZE);
		/*
		 * Special हाल क्रम FBA devices:
		 * If an FBA device is CMS क्रमmatted with blocksize > 512 byte
		 * and the DIAG discipline is used, then the CMS label is found
		 * in sector 1 instead of block 1. However, the partition is
		 * still supposed to start in block 2.
		 */
		अगर (labअन्यथाct == 1)
			offset = 2 * secperblk;
		अन्यथा
			offset = labअन्यथाct + secperblk;
		size = label->cms.block_count * secperblk;
	पूर्ण

	put_partition(state, 1, offset, size-offset);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण


/*
 * This is the मुख्य function, called by check.c
 */
पूर्णांक ibm_partition(काष्ठा parsed_partitions *state)
अणु
	पूर्णांक (*fn)(काष्ठा gendisk *disk, dasd_inक्रमmation2_t *info);
	काष्ठा block_device *bdev = state->bdev;
	काष्ठा gendisk *disk = bdev->bd_disk;
	पूर्णांक blocksize, res;
	loff_t i_size, offset, size;
	dasd_inक्रमmation2_t *info;
	काष्ठा hd_geometry *geo;
	अक्षर type[5] = अणु0,पूर्ण;
	अक्षर name[7] = अणु0,पूर्ण;
	sector_t labअन्यथाct;
	जोड़ label_t *label;

	res = 0;
	अगर (!disk->fops->getgeo)
		जाओ out_निकास;
	fn = symbol_get(dasd_biodasdinfo);
	blocksize = bdev_logical_block_size(bdev);
	अगर (blocksize <= 0)
		जाओ out_symbol;
	i_size = i_size_पढ़ो(bdev->bd_inode);
	अगर (i_size == 0)
		जाओ out_symbol;
	info = kदो_स्मृति(माप(dasd_inक्रमmation2_t), GFP_KERNEL);
	अगर (info == शून्य)
		जाओ out_symbol;
	geo = kदो_स्मृति(माप(काष्ठा hd_geometry), GFP_KERNEL);
	अगर (geo == शून्य)
		जाओ out_nogeo;
	label = kदो_स्मृति(माप(जोड़ label_t), GFP_KERNEL);
	अगर (label == शून्य)
		जाओ out_nolab;
	/* set start अगर not filled by getgeo function e.g. virtblk */
	geo->start = get_start_sect(bdev);
	अगर (disk->fops->getgeo(bdev, geo))
		जाओ out_मुक्तall;
	अगर (!fn || fn(disk, info)) अणु
		kमुक्त(info);
		info = शून्य;
	पूर्ण

	अगर (find_label(state, info, geo, blocksize, &labअन्यथाct, name, type,
		       label)) अणु
		अगर (!म_भेदन(type, "VOL1", 4)) अणु
			res = find_vol1_partitions(state, geo, blocksize, name,
						   label);
		पूर्ण अन्यथा अगर (!म_भेदन(type, "LNX1", 4)) अणु
			res = find_lnx1_partitions(state, geo, blocksize, name,
						   label, labअन्यथाct, i_size,
						   info);
		पूर्ण अन्यथा अगर (!म_भेदन(type, "CMS1", 4)) अणु
			res = find_cms1_partitions(state, geo, blocksize, name,
						   label, labअन्यथाct);
		पूर्ण
	पूर्ण अन्यथा अगर (info) अणु
		/*
		 * ugly but needed क्रम backward compatibility:
		 * If the block device is a DASD (i.e. BIODASDINFO2 works),
		 * then we claim it in any हाल, even though it has no valid
		 * label. If it has the LDL क्रमmat, then we simply define a
		 * partition as अगर it had an LNX1 label.
		 */
		res = 1;
		अगर (info->क्रमmat == DASD_FORMAT_LDL) अणु
			strlcat(state->pp_buf, "(nonl)", PAGE_SIZE);
			size = i_size >> 9;
			offset = (info->label_block + 1) * (blocksize >> 9);
			put_partition(state, 1, offset, size-offset);
			strlcat(state->pp_buf, "\n", PAGE_SIZE);
		पूर्ण
	पूर्ण अन्यथा
		res = 0;

out_मुक्तall:
	kमुक्त(label);
out_nolab:
	kमुक्त(geo);
out_nogeo:
	kमुक्त(info);
out_symbol:
	अगर (fn)
		symbol_put(dasd_biodasdinfo);
out_निकास:
	वापस res;
पूर्ण
