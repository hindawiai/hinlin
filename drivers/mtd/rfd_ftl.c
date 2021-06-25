<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * rfd_ftl.c -- resident flash disk (flash translation layer)
 *
 * Copyright तऊ 2005  Sean Young <sean@mess.org>
 *
 * This type of flash translation layer (FTL) is used by the Embedded BIOS
 * by General Software. It is known as the Resident Flash Disk (RFD), see:
 *
 *	http://www.gensw.com/pages/prod/bios/rfd.hपंचांग
 *
 * based on ftl.c
 */

#समावेश <linux/hdreg.h>
#समावेश <linux/init.h>
#समावेश <linux/mtd/blktrans.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/slab.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/types.h>

अटल पूर्णांक block_size = 0;
module_param(block_size, पूर्णांक, 0);
MODULE_PARM_DESC(block_size, "Block size to use by RFD, defaults to erase unit size");

#घोषणा PREFIX "rfd_ftl: "

/* This major has been asचिन्हित by device@lanana.org */
#अगर_अघोषित RFD_FTL_MAJOR
#घोषणा RFD_FTL_MAJOR		256
#पूर्ण_अगर

/* Maximum number of partitions in an FTL region */
#घोषणा PART_BITS		4

/* An erase unit should start with this value */
#घोषणा RFD_MAGIC		0x9193

/* the second value is 0xffff or 0xffc8; function unknown */

/* the third value is always 0xffff, ignored */

/* next is an array of mapping क्रम each corresponding sector */
#घोषणा HEADER_MAP_OFFSET	3
#घोषणा SECTOR_DELETED		0x0000
#घोषणा SECTOR_ZERO		0xfffe
#घोषणा SECTOR_FREE		0xffff

#घोषणा SECTOR_SIZE		512

#घोषणा SECTORS_PER_TRACK	63

काष्ठा block अणु
	क्रमागत अणु
		BLOCK_OK,
		BLOCK_ERASING,
		BLOCK_ERASED,
		BLOCK_UNUSED,
		BLOCK_FAILED
	पूर्ण state;
	पूर्णांक मुक्त_sectors;
	पूर्णांक used_sectors;
	पूर्णांक erases;
	u_दीर्घ offset;
पूर्ण;

काष्ठा partition अणु
	काष्ठा mtd_blktrans_dev mbd;

	u_पूर्णांक block_size;		/* size of erase unit */
	u_पूर्णांक total_blocks;		/* number of erase units */
	u_पूर्णांक header_sectors_per_block;	/* header sectors in erase unit */
	u_पूर्णांक data_sectors_per_block;	/* data sectors in erase unit */
	u_पूर्णांक sector_count;		/* sectors in translated disk */
	u_पूर्णांक header_size;		/* bytes in header sector */
	पूर्णांक reserved_block;		/* block next up क्रम reclaim */
	पूर्णांक current_block;		/* block to ग_लिखो to */
	u16 *header_cache;		/* cached header */

	पूर्णांक is_reclaiming;
	पूर्णांक cylinders;
	पूर्णांक errors;
	u_दीर्घ *sector_map;
	काष्ठा block *blocks;
पूर्ण;

अटल पूर्णांक rfd_ftl_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev, u_दीर्घ sector, अक्षर *buf);

अटल पूर्णांक build_block_map(काष्ठा partition *part, पूर्णांक block_no)
अणु
	काष्ठा block *block = &part->blocks[block_no];
	पूर्णांक i;

	block->offset = part->block_size * block_no;

	अगर (le16_to_cpu(part->header_cache[0]) != RFD_MAGIC) अणु
		block->state = BLOCK_UNUSED;
		वापस -ENOENT;
	पूर्ण

	block->state = BLOCK_OK;

	क्रम (i=0; i<part->data_sectors_per_block; i++) अणु
		u16 entry;

		entry = le16_to_cpu(part->header_cache[HEADER_MAP_OFFSET + i]);

		अगर (entry == SECTOR_DELETED)
			जारी;

		अगर (entry == SECTOR_FREE) अणु
			block->मुक्त_sectors++;
			जारी;
		पूर्ण

		अगर (entry == SECTOR_ZERO)
			entry = 0;

		अगर (entry >= part->sector_count) अणु
			prपूर्णांकk(KERN_WARNING PREFIX
				"'%s': unit #%d: entry %d corrupt, "
				"sector %d out of range\n",
				part->mbd.mtd->name, block_no, i, entry);
			जारी;
		पूर्ण

		अगर (part->sector_map[entry] != -1) अणु
			prपूर्णांकk(KERN_WARNING PREFIX
				"'%s': more than one entry for sector %d\n",
				part->mbd.mtd->name, entry);
			part->errors = 1;
			जारी;
		पूर्ण

		part->sector_map[entry] = block->offset +
			(i + part->header_sectors_per_block) * SECTOR_SIZE;

		block->used_sectors++;
	पूर्ण

	अगर (block->मुक्त_sectors == part->data_sectors_per_block)
		part->reserved_block = block_no;

	वापस 0;
पूर्ण

अटल पूर्णांक scan_header(काष्ठा partition *part)
अणु
	पूर्णांक sectors_per_block;
	पूर्णांक i, rc = -ENOMEM;
	पूर्णांक blocks_found;
	माप_प्रकार retlen;

	sectors_per_block = part->block_size / SECTOR_SIZE;
	part->total_blocks = (u32)part->mbd.mtd->size / part->block_size;

	अगर (part->total_blocks < 2)
		वापस -ENOENT;

	/* each erase block has three bytes header, followed by the map */
	part->header_sectors_per_block =
			((HEADER_MAP_OFFSET + sectors_per_block) *
			माप(u16) + SECTOR_SIZE - 1) / SECTOR_SIZE;

	part->data_sectors_per_block = sectors_per_block -
			part->header_sectors_per_block;

	part->header_size = (HEADER_MAP_OFFSET +
			part->data_sectors_per_block) * माप(u16);

	part->cylinders = (part->data_sectors_per_block *
			(part->total_blocks - 1) - 1) / SECTORS_PER_TRACK;

	part->sector_count = part->cylinders * SECTORS_PER_TRACK;

	part->current_block = -1;
	part->reserved_block = -1;
	part->is_reclaiming = 0;

	part->header_cache = kदो_स्मृति(part->header_size, GFP_KERNEL);
	अगर (!part->header_cache)
		जाओ err;

	part->blocks = kसुस्मृति(part->total_blocks, माप(काष्ठा block),
			GFP_KERNEL);
	अगर (!part->blocks)
		जाओ err;

	part->sector_map = vदो_स्मृति(array_size(माप(u_दीर्घ),
					      part->sector_count));
	अगर (!part->sector_map) अणु
		prपूर्णांकk(KERN_ERR PREFIX "'%s': unable to allocate memory for "
			"sector map", part->mbd.mtd->name);
		जाओ err;
	पूर्ण

	क्रम (i=0; i<part->sector_count; i++)
		part->sector_map[i] = -1;

	क्रम (i=0, blocks_found=0; i<part->total_blocks; i++) अणु
		rc = mtd_पढ़ो(part->mbd.mtd, i * part->block_size,
			      part->header_size, &retlen,
			      (u_अक्षर *)part->header_cache);

		अगर (!rc && retlen != part->header_size)
			rc = -EIO;

		अगर (rc)
			जाओ err;

		अगर (!build_block_map(part, i))
			blocks_found++;
	पूर्ण

	अगर (blocks_found == 0) अणु
		prपूर्णांकk(KERN_NOTICE PREFIX "no RFD magic found in '%s'\n",
				part->mbd.mtd->name);
		rc = -ENOENT;
		जाओ err;
	पूर्ण

	अगर (part->reserved_block == -1) अणु
		prपूर्णांकk(KERN_WARNING PREFIX "'%s': no empty erase unit found\n",
				part->mbd.mtd->name);

		part->errors = 1;
	पूर्ण

	वापस 0;

err:
	vमुक्त(part->sector_map);
	kमुक्त(part->header_cache);
	kमुक्त(part->blocks);

	वापस rc;
पूर्ण

अटल पूर्णांक rfd_ftl_पढ़ोsect(काष्ठा mtd_blktrans_dev *dev, u_दीर्घ sector, अक्षर *buf)
अणु
	काष्ठा partition *part = (काष्ठा partition*)dev;
	u_दीर्घ addr;
	माप_प्रकार retlen;
	पूर्णांक rc;

	अगर (sector >= part->sector_count)
		वापस -EIO;

	addr = part->sector_map[sector];
	अगर (addr != -1) अणु
		rc = mtd_पढ़ो(part->mbd.mtd, addr, SECTOR_SIZE, &retlen,
			      (u_अक्षर *)buf);
		अगर (!rc && retlen != SECTOR_SIZE)
			rc = -EIO;

		अगर (rc) अणु
			prपूर्णांकk(KERN_WARNING PREFIX "error reading '%s' at "
				"0x%lx\n", part->mbd.mtd->name, addr);
			वापस rc;
		पूर्ण
	पूर्ण अन्यथा
		स_रखो(buf, 0, SECTOR_SIZE);

	वापस 0;
पूर्ण

अटल पूर्णांक erase_block(काष्ठा partition *part, पूर्णांक block)
अणु
	काष्ठा erase_info *erase;
	पूर्णांक rc;

	erase = kदो_स्मृति(माप(काष्ठा erase_info), GFP_KERNEL);
	अगर (!erase)
		वापस -ENOMEM;

	erase->addr = part->blocks[block].offset;
	erase->len = part->block_size;

	part->blocks[block].state = BLOCK_ERASING;
	part->blocks[block].मुक्त_sectors = 0;

	rc = mtd_erase(part->mbd.mtd, erase);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "erase of region %llx,%llx on '%s' "
				"failed\n", (अचिन्हित दीर्घ दीर्घ)erase->addr,
				(अचिन्हित दीर्घ दीर्घ)erase->len, part->mbd.mtd->name);
		part->blocks[block].state = BLOCK_FAILED;
		part->blocks[block].मुक्त_sectors = 0;
		part->blocks[block].used_sectors = 0;
	पूर्ण अन्यथा अणु
		u16 magic = cpu_to_le16(RFD_MAGIC);
		माप_प्रकार retlen;

		part->blocks[block].state = BLOCK_ERASED;
		part->blocks[block].मुक्त_sectors = part->data_sectors_per_block;
		part->blocks[block].used_sectors = 0;
		part->blocks[block].erases++;

		rc = mtd_ग_लिखो(part->mbd.mtd, part->blocks[block].offset,
			       माप(magic), &retlen, (u_अक्षर *)&magic);
		अगर (!rc && retlen != माप(magic))
			rc = -EIO;

		अगर (rc) अणु
			pr_err(PREFIX "'%s': unable to write RFD header at 0x%lx\n",
			       part->mbd.mtd->name, part->blocks[block].offset);
			part->blocks[block].state = BLOCK_FAILED;
		पूर्ण अन्यथा अणु
			part->blocks[block].state = BLOCK_OK;
		पूर्ण
	पूर्ण

	kमुक्त(erase);

	वापस rc;
पूर्ण

अटल पूर्णांक move_block_contents(काष्ठा partition *part, पूर्णांक block_no, u_दीर्घ *old_sector)
अणु
	व्योम *sector_data;
	u16 *map;
	माप_प्रकार retlen;
	पूर्णांक i, rc = -ENOMEM;

	part->is_reclaiming = 1;

	sector_data = kदो_स्मृति(SECTOR_SIZE, GFP_KERNEL);
	अगर (!sector_data)
		जाओ err3;

	map = kदो_स्मृति(part->header_size, GFP_KERNEL);
	अगर (!map)
		जाओ err2;

	rc = mtd_पढ़ो(part->mbd.mtd, part->blocks[block_no].offset,
		      part->header_size, &retlen, (u_अक्षर *)map);

	अगर (!rc && retlen != part->header_size)
		rc = -EIO;

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "error reading '%s' at "
			"0x%lx\n", part->mbd.mtd->name,
			part->blocks[block_no].offset);

		जाओ err;
	पूर्ण

	क्रम (i=0; i<part->data_sectors_per_block; i++) अणु
		u16 entry = le16_to_cpu(map[HEADER_MAP_OFFSET + i]);
		u_दीर्घ addr;


		अगर (entry == SECTOR_FREE || entry == SECTOR_DELETED)
			जारी;

		अगर (entry == SECTOR_ZERO)
			entry = 0;

		/* alपढ़ोy warned about and ignored in build_block_map() */
		अगर (entry >= part->sector_count)
			जारी;

		addr = part->blocks[block_no].offset +
			(i + part->header_sectors_per_block) * SECTOR_SIZE;

		अगर (*old_sector == addr) अणु
			*old_sector = -1;
			अगर (!part->blocks[block_no].used_sectors--) अणु
				rc = erase_block(part, block_no);
				अवरोध;
			पूर्ण
			जारी;
		पूर्ण
		rc = mtd_पढ़ो(part->mbd.mtd, addr, SECTOR_SIZE, &retlen,
			      sector_data);

		अगर (!rc && retlen != SECTOR_SIZE)
			rc = -EIO;

		अगर (rc) अणु
			prपूर्णांकk(KERN_ERR PREFIX "'%s': Unable to "
				"read sector for relocation\n",
				part->mbd.mtd->name);

			जाओ err;
		पूर्ण

		rc = rfd_ftl_ग_लिखोsect((काष्ठा mtd_blktrans_dev*)part,
				entry, sector_data);

		अगर (rc)
			जाओ err;
	पूर्ण

err:
	kमुक्त(map);
err2:
	kमुक्त(sector_data);
err3:
	part->is_reclaiming = 0;

	वापस rc;
पूर्ण

अटल पूर्णांक reclaim_block(काष्ठा partition *part, u_दीर्घ *old_sector)
अणु
	पूर्णांक block, best_block, score, old_sector_block;
	पूर्णांक rc;

	/* we have a race अगर sync करोesn't exist */
	mtd_sync(part->mbd.mtd);

	score = 0x7fffffff; /* MAX_INT */
	best_block = -1;
	अगर (*old_sector != -1)
		old_sector_block = *old_sector / part->block_size;
	अन्यथा
		old_sector_block = -1;

	क्रम (block=0; block<part->total_blocks; block++) अणु
		पूर्णांक this_score;

		अगर (block == part->reserved_block)
			जारी;

		/*
		 * Postpone reclaiming अगर there is a मुक्त sector as
		 * more हटाओd sectors is more efficient (have to move
		 * less).
		 */
		अगर (part->blocks[block].मुक्त_sectors)
			वापस 0;

		this_score = part->blocks[block].used_sectors;

		अगर (block == old_sector_block)
			this_score--;
		अन्यथा अणु
			/* no poपूर्णांक in moving a full block */
			अगर (part->blocks[block].used_sectors ==
					part->data_sectors_per_block)
				जारी;
		पूर्ण

		this_score += part->blocks[block].erases;

		अगर (this_score < score) अणु
			best_block = block;
			score = this_score;
		पूर्ण
	पूर्ण

	अगर (best_block == -1)
		वापस -ENOSPC;

	part->current_block = -1;
	part->reserved_block = best_block;

	pr_debug("reclaim_block: reclaiming block #%d with %d used "
		 "%d free sectors\n", best_block,
		 part->blocks[best_block].used_sectors,
		 part->blocks[best_block].मुक्त_sectors);

	अगर (part->blocks[best_block].used_sectors)
		rc = move_block_contents(part, best_block, old_sector);
	अन्यथा
		rc = erase_block(part, best_block);

	वापस rc;
पूर्ण

/*
 * IMPROVE: It would be best to choose the block with the most deleted sectors,
 * because अगर we fill that one up first it'll have the most chance of having
 * the least live sectors at reclaim.
 */
अटल पूर्णांक find_मुक्त_block(काष्ठा partition *part)
अणु
	पूर्णांक block, stop;

	block = part->current_block == -1 ?
			jअगरfies % part->total_blocks : part->current_block;
	stop = block;

	करो अणु
		अगर (part->blocks[block].मुक्त_sectors &&
				block != part->reserved_block)
			वापस block;

		अगर (part->blocks[block].state == BLOCK_UNUSED)
			erase_block(part, block);

		अगर (++block >= part->total_blocks)
			block = 0;

	पूर्ण जबतक (block != stop);

	वापस -1;
पूर्ण

अटल पूर्णांक find_writable_block(काष्ठा partition *part, u_दीर्घ *old_sector)
अणु
	पूर्णांक rc, block;
	माप_प्रकार retlen;

	block = find_मुक्त_block(part);

	अगर (block == -1) अणु
		अगर (!part->is_reclaiming) अणु
			rc = reclaim_block(part, old_sector);
			अगर (rc)
				जाओ err;

			block = find_मुक्त_block(part);
		पूर्ण

		अगर (block == -1) अणु
			rc = -ENOSPC;
			जाओ err;
		पूर्ण
	पूर्ण

	rc = mtd_पढ़ो(part->mbd.mtd, part->blocks[block].offset,
		      part->header_size, &retlen,
		      (u_अक्षर *)part->header_cache);

	अगर (!rc && retlen != part->header_size)
		rc = -EIO;

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "'%s': unable to read header at "
				"0x%lx\n", part->mbd.mtd->name,
				part->blocks[block].offset);
		जाओ err;
	पूर्ण

	part->current_block = block;

err:
	वापस rc;
पूर्ण

अटल पूर्णांक mark_sector_deleted(काष्ठा partition *part, u_दीर्घ old_addr)
अणु
	पूर्णांक block, offset, rc;
	u_दीर्घ addr;
	माप_प्रकार retlen;
	u16 del = cpu_to_le16(SECTOR_DELETED);

	block = old_addr / part->block_size;
	offset = (old_addr % part->block_size) / SECTOR_SIZE -
		part->header_sectors_per_block;

	addr = part->blocks[block].offset +
			(HEADER_MAP_OFFSET + offset) * माप(u16);
	rc = mtd_ग_लिखो(part->mbd.mtd, addr, माप(del), &retlen,
		       (u_अक्षर *)&del);

	अगर (!rc && retlen != माप(del))
		rc = -EIO;

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "error writing '%s' at "
			"0x%lx\n", part->mbd.mtd->name, addr);
		जाओ err;
	पूर्ण
	अगर (block == part->current_block)
		part->header_cache[offset + HEADER_MAP_OFFSET] = del;

	part->blocks[block].used_sectors--;

	अगर (!part->blocks[block].used_sectors &&
	    !part->blocks[block].मुक्त_sectors)
		rc = erase_block(part, block);

err:
	वापस rc;
पूर्ण

अटल पूर्णांक find_मुक्त_sector(स्थिर काष्ठा partition *part, स्थिर काष्ठा block *block)
अणु
	पूर्णांक i, stop;

	i = stop = part->data_sectors_per_block - block->मुक्त_sectors;

	करो अणु
		अगर (le16_to_cpu(part->header_cache[HEADER_MAP_OFFSET + i])
				== SECTOR_FREE)
			वापस i;

		अगर (++i == part->data_sectors_per_block)
			i = 0;
	पूर्ण
	जबतक(i != stop);

	वापस -1;
पूर्ण

अटल पूर्णांक करो_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev, u_दीर्घ sector, अक्षर *buf, uदीर्घ *old_addr)
अणु
	काष्ठा partition *part = (काष्ठा partition*)dev;
	काष्ठा block *block;
	u_दीर्घ addr;
	पूर्णांक i;
	पूर्णांक rc;
	माप_प्रकार retlen;
	u16 entry;

	अगर (part->current_block == -1 ||
		!part->blocks[part->current_block].मुक्त_sectors) अणु

		rc = find_writable_block(part, old_addr);
		अगर (rc)
			जाओ err;
	पूर्ण

	block = &part->blocks[part->current_block];

	i = find_मुक्त_sector(part, block);

	अगर (i < 0) अणु
		rc = -ENOSPC;
		जाओ err;
	पूर्ण

	addr = (i + part->header_sectors_per_block) * SECTOR_SIZE +
		block->offset;
	rc = mtd_ग_लिखो(part->mbd.mtd, addr, SECTOR_SIZE, &retlen,
		       (u_अक्षर *)buf);

	अगर (!rc && retlen != SECTOR_SIZE)
		rc = -EIO;

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "error writing '%s' at 0x%lx\n",
				part->mbd.mtd->name, addr);
		जाओ err;
	पूर्ण

	part->sector_map[sector] = addr;

	entry = cpu_to_le16(sector == 0 ? SECTOR_ZERO : sector);

	part->header_cache[i + HEADER_MAP_OFFSET] = entry;

	addr = block->offset + (HEADER_MAP_OFFSET + i) * माप(u16);
	rc = mtd_ग_लिखो(part->mbd.mtd, addr, माप(entry), &retlen,
		       (u_अक्षर *)&entry);

	अगर (!rc && retlen != माप(entry))
		rc = -EIO;

	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR PREFIX "error writing '%s' at 0x%lx\n",
				part->mbd.mtd->name, addr);
		जाओ err;
	पूर्ण
	block->used_sectors++;
	block->मुक्त_sectors--;

err:
	वापस rc;
पूर्ण

अटल पूर्णांक rfd_ftl_ग_लिखोsect(काष्ठा mtd_blktrans_dev *dev, u_दीर्घ sector, अक्षर *buf)
अणु
	काष्ठा partition *part = (काष्ठा partition*)dev;
	u_दीर्घ old_addr;
	पूर्णांक i;
	पूर्णांक rc = 0;

	pr_debug("rfd_ftl_writesect(sector=0x%lx)\n", sector);

	अगर (part->reserved_block == -1) अणु
		rc = -EACCES;
		जाओ err;
	पूर्ण

	अगर (sector >= part->sector_count) अणु
		rc = -EIO;
		जाओ err;
	पूर्ण

	old_addr = part->sector_map[sector];

	क्रम (i=0; i<SECTOR_SIZE; i++) अणु
		अगर (!buf[i])
			जारी;

		rc = करो_ग_लिखोsect(dev, sector, buf, &old_addr);
		अगर (rc)
			जाओ err;
		अवरोध;
	पूर्ण

	अगर (i == SECTOR_SIZE)
		part->sector_map[sector] = -1;

	अगर (old_addr != -1)
		rc = mark_sector_deleted(part, old_addr);

err:
	वापस rc;
पूर्ण

अटल पूर्णांक rfd_ftl_getgeo(काष्ठा mtd_blktrans_dev *dev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा partition *part = (काष्ठा partition*)dev;

	geo->heads = 1;
	geo->sectors = SECTORS_PER_TRACK;
	geo->cylinders = part->cylinders;

	वापस 0;
पूर्ण

अटल व्योम rfd_ftl_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा partition *part;

	अगर (mtd->type != MTD_NORFLASH || mtd->size > अच_पूर्णांक_उच्च)
		वापस;

	part = kzalloc(माप(काष्ठा partition), GFP_KERNEL);
	अगर (!part)
		वापस;

	part->mbd.mtd = mtd;

	अगर (block_size)
		part->block_size = block_size;
	अन्यथा अणु
		अगर (!mtd->erasesize) अणु
			prपूर्णांकk(KERN_WARNING PREFIX "please provide block_size");
			जाओ out;
		पूर्ण अन्यथा
			part->block_size = mtd->erasesize;
	पूर्ण

	अगर (scan_header(part) == 0) अणु
		part->mbd.size = part->sector_count;
		part->mbd.tr = tr;
		part->mbd.devnum = -1;
		अगर (!(mtd->flags & MTD_WRITEABLE))
			part->mbd.पढ़ोonly = 1;
		अन्यथा अगर (part->errors) अणु
			prपूर्णांकk(KERN_WARNING PREFIX "'%s': errors found, "
					"setting read-only\n", mtd->name);
			part->mbd.पढ़ोonly = 1;
		पूर्ण

		prपूर्णांकk(KERN_INFO PREFIX "name: '%s' type: %d flags %x\n",
				mtd->name, mtd->type, mtd->flags);

		अगर (!add_mtd_blktrans_dev((व्योम*)part))
			वापस;
	पूर्ण
out:
	kमुक्त(part);
पूर्ण

अटल व्योम rfd_ftl_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा partition *part = (काष्ठा partition*)dev;
	पूर्णांक i;

	क्रम (i=0; i<part->total_blocks; i++) अणु
		pr_debug("rfd_ftl_remove_dev:'%s': erase unit #%02d: %d erases\n",
			part->mbd.mtd->name, i, part->blocks[i].erases);
	पूर्ण

	del_mtd_blktrans_dev(dev);
	vमुक्त(part->sector_map);
	kमुक्त(part->header_cache);
	kमुक्त(part->blocks);
पूर्ण

अटल काष्ठा mtd_blktrans_ops rfd_ftl_tr = अणु
	.name		= "rfd",
	.major		= RFD_FTL_MAJOR,
	.part_bits	= PART_BITS,
	.blksize 	= SECTOR_SIZE,

	.पढ़ोsect	= rfd_ftl_पढ़ोsect,
	.ग_लिखोsect	= rfd_ftl_ग_लिखोsect,
	.getgeo		= rfd_ftl_getgeo,
	.add_mtd	= rfd_ftl_add_mtd,
	.हटाओ_dev	= rfd_ftl_हटाओ_dev,
	.owner		= THIS_MODULE,
पूर्ण;

module_mtd_blktrans(rfd_ftl_tr);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sean Young <sean@mess.org>");
MODULE_DESCRIPTION("Support code for RFD Flash Translation Layer, "
		"used by General Software's Embedded BIOS");

