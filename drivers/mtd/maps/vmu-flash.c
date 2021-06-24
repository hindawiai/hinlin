<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* vmu-flash.c
 * Driver क्रम SEGA Dreamcast Visual Memory Unit
 *
 * Copyright (c) Adrian McMenamin 2002 - 2009
 * Copyright (c) Paul Mundt 2001
 */
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/delay.h>
#समावेश <linux/maple.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/map.h>

काष्ठा vmu_cache अणु
	अचिन्हित अक्षर *buffer;		/* Cache */
	अचिन्हित पूर्णांक block;		/* Which block was cached */
	अचिन्हित दीर्घ jअगरfies_atc;	/* When was it cached? */
	पूर्णांक valid;
पूर्ण;

काष्ठा mdev_part अणु
	काष्ठा maple_device *mdev;
	पूर्णांक partition;
पूर्ण;

काष्ठा vmupart अणु
	u16 user_blocks;
	u16 root_block;
	u16 numblocks;
	अक्षर *name;
	काष्ठा vmu_cache *pcache;
पूर्ण;

काष्ठा memcard अणु
	u16 tempA;
	u16 tempB;
	u32 partitions;
	u32 blocklen;
	u32 ग_लिखोcnt;
	u32 पढ़ोcnt;
	u32 removable;
	पूर्णांक partition;
	पूर्णांक पढ़ो;
	अचिन्हित अक्षर *blockपढ़ो;
	काष्ठा vmupart *parts;
	काष्ठा mtd_info *mtd;
पूर्ण;

काष्ठा vmu_block अणु
	अचिन्हित पूर्णांक num; /* block number */
	अचिन्हित पूर्णांक ofs; /* block offset */
पूर्ण;

अटल काष्ठा vmu_block *ofs_to_block(अचिन्हित दीर्घ src_ofs,
	काष्ठा mtd_info *mtd, पूर्णांक partition)
अणु
	काष्ठा vmu_block *vblock;
	काष्ठा maple_device *mdev;
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	पूर्णांक num;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	card = maple_get_drvdata(mdev);

	अगर (src_ofs >= card->parts[partition].numblocks * card->blocklen)
		जाओ failed;

	num = src_ofs / card->blocklen;
	अगर (num > card->parts[partition].numblocks)
		जाओ failed;

	vblock = kदो_स्मृति(माप(काष्ठा vmu_block), GFP_KERNEL);
	अगर (!vblock)
		जाओ failed;

	vblock->num = num;
	vblock->ofs = src_ofs % card->blocklen;
	वापस vblock;

failed:
	वापस शून्य;
पूर्ण

/* Maple bus callback function क्रम पढ़ोs */
अटल व्योम vmu_blockपढ़ो(काष्ठा mapleq *mq)
अणु
	काष्ठा maple_device *mdev;
	काष्ठा memcard *card;

	mdev = mq->dev;
	card = maple_get_drvdata(mdev);
	/* copy the पढ़ो in data */

	अगर (unlikely(!card->blockपढ़ो))
		वापस;

	स_नकल(card->blockपढ़ो, mq->recvbuf->buf + 12,
		card->blocklen/card->पढ़ोcnt);

पूर्ण

/* Interface with maple bus to पढ़ो blocks
 * caching the results so that other parts
 * of the driver can access block पढ़ोs */
अटल पूर्णांक maple_vmu_पढ़ो_block(अचिन्हित पूर्णांक num, अचिन्हित अक्षर *buf,
	काष्ठा mtd_info *mtd)
अणु
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	काष्ठा maple_device *mdev;
	पूर्णांक partition, error = 0, x, रुको;
	अचिन्हित अक्षर *blockपढ़ो = शून्य;
	काष्ठा vmu_cache *pcache;
	__be32 sendbuf;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);
	pcache = card->parts[partition].pcache;
	pcache->valid = 0;

	/* prepare the cache क्रम this block */
	अगर (!pcache->buffer) अणु
		pcache->buffer = kदो_स्मृति(card->blocklen, GFP_KERNEL);
		अगर (!pcache->buffer) अणु
			dev_err(&mdev->dev, "VMU at (%d, %d) - read fails due"
				" to lack of memory\n", mdev->port,
				mdev->unit);
			error = -ENOMEM;
			जाओ outB;
		पूर्ण
	पूर्ण

	/*
	* Reads may be phased - again the hardware spec
	* supports this - though may not be any devices in
	* the wild that implement it, but we will here
	*/
	क्रम (x = 0; x < card->पढ़ोcnt; x++) अणु
		sendbuf = cpu_to_be32(partition << 24 | x << 16 | num);

		अगर (atomic_पढ़ो(&mdev->busy) == 1) अणु
			रुको_event_पूर्णांकerruptible_समयout(mdev->maple_रुको,
				atomic_पढ़ो(&mdev->busy) == 0, HZ);
			अगर (atomic_पढ़ो(&mdev->busy) == 1) अणु
				dev_notice(&mdev->dev, "VMU at (%d, %d)"
					" is busy\n", mdev->port, mdev->unit);
				error = -EAGAIN;
				जाओ outB;
			पूर्ण
		पूर्ण

		atomic_set(&mdev->busy, 1);
		blockपढ़ो = kदो_स्मृति(card->blocklen/card->पढ़ोcnt, GFP_KERNEL);
		अगर (!blockपढ़ो) अणु
			error = -ENOMEM;
			atomic_set(&mdev->busy, 0);
			जाओ outB;
		पूर्ण
		card->blockपढ़ो = blockपढ़ो;

		maple_अ_लोond_callback(mdev, vmu_blockपढ़ो, 0,
			MAPLE_FUNC_MEMCARD);
		error = maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
				MAPLE_COMMAND_BREAD, 2, &sendbuf);
		/* Very दीर्घ समयouts seem to be needed when box is stressed */
		रुको = रुको_event_पूर्णांकerruptible_समयout(mdev->maple_रुको,
			(atomic_पढ़ो(&mdev->busy) == 0 ||
			atomic_पढ़ो(&mdev->busy) == 2), HZ * 3);
		/*
		* MTD layer करोes not handle hotplugging well
		* so have to वापस errors when VMU is unplugged
		* in the middle of a पढ़ो (busy == 2)
		*/
		अगर (error || atomic_पढ़ो(&mdev->busy) == 2) अणु
			अगर (atomic_पढ़ो(&mdev->busy) == 2)
				error = -ENXIO;
			atomic_set(&mdev->busy, 0);
			card->blockपढ़ो = शून्य;
			जाओ outA;
		पूर्ण
		अगर (रुको == 0 || रुको == -ERESTARTSYS) अणु
			card->blockपढ़ो = शून्य;
			atomic_set(&mdev->busy, 0);
			error = -EIO;
			list_del_init(&(mdev->mq->list));
			kमुक्त(mdev->mq->sendbuf);
			mdev->mq->sendbuf = शून्य;
			अगर (रुको == -ERESTARTSYS) अणु
				dev_warn(&mdev->dev, "VMU read on (%d, %d)"
					" interrupted on block 0x%X\n",
					mdev->port, mdev->unit, num);
			पूर्ण अन्यथा
				dev_notice(&mdev->dev, "VMU read on (%d, %d)"
					" timed out on block 0x%X\n",
					mdev->port, mdev->unit, num);
			जाओ outA;
		पूर्ण

		स_नकल(buf + (card->blocklen/card->पढ़ोcnt) * x, blockपढ़ो,
			card->blocklen/card->पढ़ोcnt);

		स_नकल(pcache->buffer + (card->blocklen/card->पढ़ोcnt) * x,
			card->blockपढ़ो, card->blocklen/card->पढ़ोcnt);
		card->blockपढ़ो = शून्य;
		pcache->block = num;
		pcache->jअगरfies_atc = jअगरfies;
		pcache->valid = 1;
		kमुक्त(blockपढ़ो);
	पूर्ण

	वापस error;

outA:
	kमुक्त(blockपढ़ो);
outB:
	वापस error;
पूर्ण

/* communicate with maple bus क्रम phased writing */
अटल पूर्णांक maple_vmu_ग_लिखो_block(अचिन्हित पूर्णांक num, स्थिर अचिन्हित अक्षर *buf,
	काष्ठा mtd_info *mtd)
अणु
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	काष्ठा maple_device *mdev;
	पूर्णांक partition, error, locking, x, phaselen, रुको;
	__be32 *sendbuf;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);

	phaselen = card->blocklen/card->ग_लिखोcnt;

	sendbuf = kदो_स्मृति(phaselen + 4, GFP_KERNEL);
	अगर (!sendbuf) अणु
		error = -ENOMEM;
		जाओ fail_nosendbuf;
	पूर्ण
	क्रम (x = 0; x < card->ग_लिखोcnt; x++) अणु
		sendbuf[0] = cpu_to_be32(partition << 24 | x << 16 | num);
		स_नकल(&sendbuf[1], buf + phaselen * x, phaselen);
		/* रुको until the device is not busy करोing something अन्यथा
		* or 1 second - which ever is दीर्घer */
		अगर (atomic_पढ़ो(&mdev->busy) == 1) अणु
			रुको_event_पूर्णांकerruptible_समयout(mdev->maple_रुको,
				atomic_पढ़ो(&mdev->busy) == 0, HZ);
			अगर (atomic_पढ़ो(&mdev->busy) == 1) अणु
				error = -EBUSY;
				dev_notice(&mdev->dev, "VMU write at (%d, %d)"
					"failed - device is busy\n",
					mdev->port, mdev->unit);
				जाओ fail_nolock;
			पूर्ण
		पूर्ण
		atomic_set(&mdev->busy, 1);

		locking = maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
			MAPLE_COMMAND_BWRITE, phaselen / 4 + 2, sendbuf);
		रुको = रुको_event_पूर्णांकerruptible_समयout(mdev->maple_रुको,
			atomic_पढ़ो(&mdev->busy) == 0, HZ/10);
		अगर (locking) अणु
			error = -EIO;
			atomic_set(&mdev->busy, 0);
			जाओ fail_nolock;
		पूर्ण
		अगर (atomic_पढ़ो(&mdev->busy) == 2) अणु
			atomic_set(&mdev->busy, 0);
		पूर्ण अन्यथा अगर (रुको == 0 || रुको == -ERESTARTSYS) अणु
			error = -EIO;
			dev_warn(&mdev->dev, "Write at (%d, %d) of block"
				" 0x%X at phase %d failed: could not"
				" communicate with VMU", mdev->port,
				mdev->unit, num, x);
			atomic_set(&mdev->busy, 0);
			kमुक्त(mdev->mq->sendbuf);
			mdev->mq->sendbuf = शून्य;
			list_del_init(&(mdev->mq->list));
			जाओ fail_nolock;
		पूर्ण
	पूर्ण
	kमुक्त(sendbuf);

	वापस card->blocklen;

fail_nolock:
	kमुक्त(sendbuf);
fail_nosendbuf:
	dev_err(&mdev->dev, "VMU (%d, %d): write failed\n", mdev->port,
		mdev->unit);
	वापस error;
पूर्ण

/* mtd function to simulate पढ़ोing byte by byte */
अटल अचिन्हित अक्षर vmu_flash_पढ़ो_अक्षर(अचिन्हित दीर्घ ofs, पूर्णांक *retval,
	काष्ठा mtd_info *mtd)
अणु
	काष्ठा vmu_block *vblock;
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	काष्ठा maple_device *mdev;
	अचिन्हित अक्षर *buf, ret;
	पूर्णांक partition, error;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);
	*retval =  0;

	buf = kदो_स्मृति(card->blocklen, GFP_KERNEL);
	अगर (!buf) अणु
		*retval = 1;
		ret = -ENOMEM;
		जाओ finish;
	पूर्ण

	vblock = ofs_to_block(ofs, mtd, partition);
	अगर (!vblock) अणु
		*retval = 3;
		ret = -ENOMEM;
		जाओ out_buf;
	पूर्ण

	error = maple_vmu_पढ़ो_block(vblock->num, buf, mtd);
	अगर (error) अणु
		ret = error;
		*retval = 2;
		जाओ out_vblock;
	पूर्ण

	ret = buf[vblock->ofs];

out_vblock:
	kमुक्त(vblock);
out_buf:
	kमुक्त(buf);
finish:
	वापस ret;
पूर्ण

/* mtd higher order function to पढ़ो flash */
अटल पूर्णांक vmu_flash_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
	माप_प्रकार *retlen,  u_अक्षर *buf)
अणु
	काष्ठा maple_device *mdev;
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	काष्ठा vmu_cache *pcache;
	काष्ठा vmu_block *vblock;
	पूर्णांक index = 0, retval, partition, leftover, numblocks;
	अचिन्हित अक्षर cx;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);

	numblocks = card->parts[partition].numblocks;
	अगर (from + len > numblocks * card->blocklen)
		len = numblocks * card->blocklen - from;
	अगर (len == 0)
		वापस -EIO;
	/* Have we cached this bit alपढ़ोy? */
	pcache = card->parts[partition].pcache;
	करो अणु
		vblock =  ofs_to_block(from + index, mtd, partition);
		अगर (!vblock)
			वापस -ENOMEM;
		/* Have we cached this and is the cache valid and समयly? */
		अगर (pcache->valid &&
			समय_beक्रमe(jअगरfies, pcache->jअगरfies_atc + HZ) &&
			(pcache->block == vblock->num)) अणु
			/* we have cached it, so करो necessary copying */
			leftover = card->blocklen - vblock->ofs;
			अगर (vblock->ofs + len - index < card->blocklen) अणु
				/* only a bit of this block to copy */
				स_नकल(buf + index,
					pcache->buffer + vblock->ofs,
					len - index);
				index = len;
			पूर्ण अन्यथा अणु
				/* otherwise copy reमुख्यder of whole block */
				स_नकल(buf + index, pcache->buffer +
					vblock->ofs, leftover);
				index += leftover;
			पूर्ण
		पूर्ण अन्यथा अणु
			/*
			* Not cached so पढ़ो one byte -
			* but cache the rest of the block
			*/
			cx = vmu_flash_पढ़ो_अक्षर(from + index, &retval, mtd);
			अगर (retval) अणु
				*retlen = index;
				kमुक्त(vblock);
				वापस cx;
			पूर्ण
			स_रखो(buf + index, cx, 1);
			index++;
		पूर्ण
		kमुक्त(vblock);
	पूर्ण जबतक (len > index);
	*retlen = index;

	वापस 0;
पूर्ण

अटल पूर्णांक vmu_flash_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
	माप_प्रकार *retlen, स्थिर u_अक्षर *buf)
अणु
	काष्ठा maple_device *mdev;
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	पूर्णांक index = 0, partition, error = 0, numblocks;
	काष्ठा vmu_cache *pcache;
	काष्ठा vmu_block *vblock;
	अचिन्हित अक्षर *buffer;

	mpart = mtd->priv;
	mdev = mpart->mdev;
	partition = mpart->partition;
	card = maple_get_drvdata(mdev);

	numblocks = card->parts[partition].numblocks;
	अगर (to + len > numblocks * card->blocklen)
		len = numblocks * card->blocklen - to;
	अगर (len == 0) अणु
		error = -EIO;
		जाओ failed;
	पूर्ण

	vblock = ofs_to_block(to, mtd, partition);
	अगर (!vblock) अणु
		error = -ENOMEM;
		जाओ failed;
	पूर्ण

	buffer = kदो_स्मृति(card->blocklen, GFP_KERNEL);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ fail_buffer;
	पूर्ण

	करो अणु
		/* Read in the block we are to ग_लिखो to */
		error = maple_vmu_पढ़ो_block(vblock->num, buffer, mtd);
		अगर (error)
			जाओ fail_io;

		करो अणु
			buffer[vblock->ofs] = buf[index];
			vblock->ofs++;
			index++;
			अगर (index >= len)
				अवरोध;
		पूर्ण जबतक (vblock->ofs < card->blocklen);

		/* ग_लिखो out new buffer */
		error = maple_vmu_ग_लिखो_block(vblock->num, buffer, mtd);
		/* invalidate the cache */
		pcache = card->parts[partition].pcache;
		pcache->valid = 0;

		अगर (error != card->blocklen)
			जाओ fail_io;

		vblock->num++;
		vblock->ofs = 0;
	पूर्ण जबतक (len > index);

	kमुक्त(buffer);
	*retlen = index;
	kमुक्त(vblock);
	वापस 0;

fail_io:
	kमुक्त(buffer);
fail_buffer:
	kमुक्त(vblock);
failed:
	dev_err(&mdev->dev, "VMU write failing with error %d\n", error);
	वापस error;
पूर्ण

अटल व्योम vmu_flash_sync(काष्ठा mtd_info *mtd)
अणु
	/* Do nothing here */
पूर्ण

/* Maple bus callback function to recursively query hardware details */
अटल व्योम vmu_queryblocks(काष्ठा mapleq *mq)
अणु
	काष्ठा maple_device *mdev;
	अचिन्हित लघु *res;
	काष्ठा memcard *card;
	__be32 partnum;
	काष्ठा vmu_cache *pcache;
	काष्ठा mdev_part *mpart;
	काष्ठा mtd_info *mtd_cur;
	काष्ठा vmupart *part_cur;
	पूर्णांक error;

	mdev = mq->dev;
	card = maple_get_drvdata(mdev);
	res = (अचिन्हित लघु *) (mq->recvbuf->buf);
	card->tempA = res[12];
	card->tempB = res[6];

	dev_info(&mdev->dev, "VMU device at partition %d has %d user "
		"blocks with a root block at %d\n", card->partition,
		card->tempA, card->tempB);

	part_cur = &card->parts[card->partition];
	part_cur->user_blocks = card->tempA;
	part_cur->root_block = card->tempB;
	part_cur->numblocks = card->tempB + 1;
	part_cur->name = kदो_स्मृति(12, GFP_KERNEL);
	अगर (!part_cur->name)
		जाओ fail_name;

	प्र_लिखो(part_cur->name, "vmu%d.%d.%d",
		mdev->port, mdev->unit, card->partition);
	mtd_cur = &card->mtd[card->partition];
	mtd_cur->name = part_cur->name;
	mtd_cur->type = 8;
	mtd_cur->flags = MTD_WRITEABLE|MTD_NO_ERASE;
	mtd_cur->size = part_cur->numblocks * card->blocklen;
	mtd_cur->erasesize = card->blocklen;
	mtd_cur->_ग_लिखो = vmu_flash_ग_लिखो;
	mtd_cur->_पढ़ो = vmu_flash_पढ़ो;
	mtd_cur->_sync = vmu_flash_sync;
	mtd_cur->ग_लिखोsize = card->blocklen;

	mpart = kदो_स्मृति(माप(काष्ठा mdev_part), GFP_KERNEL);
	अगर (!mpart)
		जाओ fail_mpart;

	mpart->mdev = mdev;
	mpart->partition = card->partition;
	mtd_cur->priv = mpart;
	mtd_cur->owner = THIS_MODULE;

	pcache = kzalloc(माप(काष्ठा vmu_cache), GFP_KERNEL);
	अगर (!pcache)
		जाओ fail_cache_create;
	part_cur->pcache = pcache;

	error = mtd_device_रेजिस्टर(mtd_cur, शून्य, 0);
	अगर (error)
		जाओ fail_mtd_रेजिस्टर;

	maple_अ_लोond_callback(mdev, शून्य, 0,
		MAPLE_FUNC_MEMCARD);

	/*
	* Set up a recursive call to the (probably theoretical)
	* second or more partition
	*/
	अगर (++card->partition < card->partitions) अणु
		partnum = cpu_to_be32(card->partition << 24);
		maple_अ_लोond_callback(mdev, vmu_queryblocks, 0,
			MAPLE_FUNC_MEMCARD);
		maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
			MAPLE_COMMAND_GETMINFO, 2, &partnum);
	पूर्ण
	वापस;

fail_mtd_रेजिस्टर:
	dev_err(&mdev->dev, "Could not register maple device at (%d, %d)"
		"error is 0x%X\n", mdev->port, mdev->unit, error);
	क्रम (error = 0; error <= card->partition; error++) अणु
		kमुक्त(((card->parts)[error]).pcache);
		((card->parts)[error]).pcache = शून्य;
	पूर्ण
fail_cache_create:
fail_mpart:
	क्रम (error = 0; error <= card->partition; error++) अणु
		kमुक्त(((card->mtd)[error]).priv);
		((card->mtd)[error]).priv = शून्य;
	पूर्ण
	maple_अ_लोond_callback(mdev, शून्य, 0,
		MAPLE_FUNC_MEMCARD);
	kमुक्त(part_cur->name);
fail_name:
	वापस;
पूर्ण

/* Handles very basic info about the flash, queries क्रम details */
अटल पूर्णांक vmu_connect(काष्ठा maple_device *mdev)
अणु
	अचिन्हित दीर्घ test_flash_data, basic_flash_data;
	पूर्णांक c, error;
	काष्ठा memcard *card;
	u32 partnum = 0;

	test_flash_data = be32_to_cpu(mdev->devinfo.function);
	/* Need to count how many bits are set - to find out which
	 * function_data element has details of the memory card
	 */
	c = hweight_दीर्घ(test_flash_data);

	basic_flash_data = be32_to_cpu(mdev->devinfo.function_data[c - 1]);

	card = kदो_स्मृति(माप(काष्ठा memcard), GFP_KERNEL);
	अगर (!card) अणु
		error = -ENOMEM;
		जाओ fail_nomem;
	पूर्ण

	card->partitions = (basic_flash_data >> 24 & 0xFF) + 1;
	card->blocklen = ((basic_flash_data >> 16 & 0xFF) + 1) << 5;
	card->ग_लिखोcnt = basic_flash_data >> 12 & 0xF;
	card->पढ़ोcnt = basic_flash_data >> 8 & 0xF;
	card->removable = basic_flash_data >> 7 & 1;

	card->partition = 0;

	/*
	* Not sure there are actually any multi-partition devices in the
	* real world, but the hardware supports them, so, so will we
	*/
	card->parts = kदो_स्मृति_array(card->partitions, माप(काष्ठा vmupart),
				    GFP_KERNEL);
	अगर (!card->parts) अणु
		error = -ENOMEM;
		जाओ fail_partitions;
	पूर्ण

	card->mtd = kदो_स्मृति_array(card->partitions, माप(काष्ठा mtd_info),
				  GFP_KERNEL);
	अगर (!card->mtd) अणु
		error = -ENOMEM;
		जाओ fail_mtd_info;
	पूर्ण

	maple_set_drvdata(mdev, card);

	/*
	* We want to trap meminfo not get cond
	* so set पूर्णांकerval to zero, but rely on maple bus
	* driver to pass back the results of the meminfo
	*/
	maple_अ_लोond_callback(mdev, vmu_queryblocks, 0,
		MAPLE_FUNC_MEMCARD);

	/* Make sure we are clear to go */
	अगर (atomic_पढ़ो(&mdev->busy) == 1) अणु
		रुको_event_पूर्णांकerruptible_समयout(mdev->maple_रुको,
			atomic_पढ़ो(&mdev->busy) == 0, HZ);
		अगर (atomic_पढ़ो(&mdev->busy) == 1) अणु
			dev_notice(&mdev->dev, "VMU at (%d, %d) is busy\n",
				mdev->port, mdev->unit);
			error = -EAGAIN;
			जाओ fail_device_busy;
		पूर्ण
	पूर्ण

	atomic_set(&mdev->busy, 1);

	/*
	* Set up the minfo call: vmu_queryblocks will handle
	* the inक्रमmation passed back
	*/
	error = maple_add_packet(mdev, MAPLE_FUNC_MEMCARD,
		MAPLE_COMMAND_GETMINFO, 2, &partnum);
	अगर (error) अणु
		dev_err(&mdev->dev, "Could not lock VMU at (%d, %d)"
			" error is 0x%X\n", mdev->port, mdev->unit, error);
		जाओ fail_mtd_info;
	पूर्ण
	वापस 0;

fail_device_busy:
	kमुक्त(card->mtd);
fail_mtd_info:
	kमुक्त(card->parts);
fail_partitions:
	kमुक्त(card);
fail_nomem:
	वापस error;
पूर्ण

अटल व्योम vmu_disconnect(काष्ठा maple_device *mdev)
अणु
	काष्ठा memcard *card;
	काष्ठा mdev_part *mpart;
	पूर्णांक x;

	mdev->callback = शून्य;
	card = maple_get_drvdata(mdev);
	क्रम (x = 0; x < card->partitions; x++) अणु
		mpart = ((card->mtd)[x]).priv;
		mpart->mdev = शून्य;
		mtd_device_unरेजिस्टर(&((card->mtd)[x]));
		kमुक्त(((card->parts)[x]).name);
	पूर्ण
	kमुक्त(card->parts);
	kमुक्त(card->mtd);
	kमुक्त(card);
पूर्ण

/* Callback to handle eccentricities of both mtd subप्रणाली
 * and general flakyness of Dreamcast VMUs
 */
अटल पूर्णांक vmu_can_unload(काष्ठा maple_device *mdev)
अणु
	काष्ठा memcard *card;
	पूर्णांक x;
	काष्ठा mtd_info *mtd;

	card = maple_get_drvdata(mdev);
	क्रम (x = 0; x < card->partitions; x++) अणु
		mtd = &((card->mtd)[x]);
		अगर (mtd->usecount > 0)
			वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

#घोषणा ERRSTR "VMU at (%d, %d) file error -"

अटल व्योम vmu_file_error(काष्ठा maple_device *mdev, व्योम *recvbuf)
अणु
	क्रमागत maple_file_errors error = ((पूर्णांक *)recvbuf)[1];

	चयन (error) अणु

	हाल MAPLE_खाताERR_INVALID_PARTITION:
		dev_notice(&mdev->dev, ERRSTR " invalid partition number\n",
			mdev->port, mdev->unit);
		अवरोध;

	हाल MAPLE_खाताERR_PHASE_ERROR:
		dev_notice(&mdev->dev, ERRSTR " phase error\n",
			mdev->port, mdev->unit);
		अवरोध;

	हाल MAPLE_खाताERR_INVALID_BLOCK:
		dev_notice(&mdev->dev, ERRSTR " invalid block number\n",
			mdev->port, mdev->unit);
		अवरोध;

	हाल MAPLE_खाताERR_WRITE_ERROR:
		dev_notice(&mdev->dev, ERRSTR " write error\n",
			mdev->port, mdev->unit);
		अवरोध;

	हाल MAPLE_खाताERR_INVALID_WRITE_LENGTH:
		dev_notice(&mdev->dev, ERRSTR " invalid write length\n",
			mdev->port, mdev->unit);
		अवरोध;

	हाल MAPLE_खाताERR_BAD_CRC:
		dev_notice(&mdev->dev, ERRSTR " bad CRC\n",
			mdev->port, mdev->unit);
		अवरोध;

	शेष:
		dev_notice(&mdev->dev, ERRSTR " 0x%X\n",
			mdev->port, mdev->unit, error);
	पूर्ण
पूर्ण


अटल पूर्णांक probe_maple_vmu(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev = to_maple_dev(dev);
	काष्ठा maple_driver *mdrv = to_maple_driver(dev->driver);

	mdev->can_unload = vmu_can_unload;
	mdev->fileerr_handler = vmu_file_error;
	mdev->driver = mdrv;

	वापस vmu_connect(mdev);
पूर्ण

अटल पूर्णांक हटाओ_maple_vmu(काष्ठा device *dev)
अणु
	काष्ठा maple_device *mdev = to_maple_dev(dev);

	vmu_disconnect(mdev);
	वापस 0;
पूर्ण

अटल काष्ठा maple_driver vmu_flash_driver = अणु
	.function =	MAPLE_FUNC_MEMCARD,
	.drv = अणु
		.name =		"Dreamcast_visual_memory",
		.probe =	probe_maple_vmu,
		.हटाओ =	हटाओ_maple_vmu,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init vmu_flash_map_init(व्योम)
अणु
	वापस maple_driver_रेजिस्टर(&vmu_flash_driver);
पूर्ण

अटल व्योम __निकास vmu_flash_map_निकास(व्योम)
अणु
	maple_driver_unरेजिस्टर(&vmu_flash_driver);
पूर्ण

module_init(vmu_flash_map_init);
module_निकास(vmu_flash_map_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Adrian McMenamin");
MODULE_DESCRIPTION("Flash mapping for Sega Dreamcast visual memory");
