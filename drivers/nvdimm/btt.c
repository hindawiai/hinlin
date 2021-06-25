<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Block Translation Table
 * Copyright (c) 2014-2015, Intel Corporation.
 */
#समावेश <linux/highस्मृति.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/genhd.h>
#समावेश <linux/sizes.h>
#समावेश <linux/ndctl.h>
#समावेश <linux/fs.h>
#समावेश <linux/nd.h>
#समावेश <linux/backing-dev.h>
#समावेश "btt.h"
#समावेश "nd.h"

क्रमागत log_ent_request अणु
	LOG_NEW_ENT = 0,
	LOG_OLD_ENT
पूर्ण;

अटल काष्ठा device *to_dev(काष्ठा arena_info *arena)
अणु
	वापस &arena->nd_btt->dev;
पूर्ण

अटल u64 adjust_initial_offset(काष्ठा nd_btt *nd_btt, u64 offset)
अणु
	वापस offset + nd_btt->initial_offset;
पूर्ण

अटल पूर्णांक arena_पढ़ो_bytes(काष्ठा arena_info *arena, resource_माप_प्रकार offset,
		व्योम *buf, माप_प्रकार n, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nd_btt *nd_btt = arena->nd_btt;
	काष्ठा nd_namespace_common *ndns = nd_btt->ndns;

	/* arena offsets may be shअगरted from the base of the device */
	offset = adjust_initial_offset(nd_btt, offset);
	वापस nvdimm_पढ़ो_bytes(ndns, offset, buf, n, flags);
पूर्ण

अटल पूर्णांक arena_ग_लिखो_bytes(काष्ठा arena_info *arena, resource_माप_प्रकार offset,
		व्योम *buf, माप_प्रकार n, अचिन्हित दीर्घ flags)
अणु
	काष्ठा nd_btt *nd_btt = arena->nd_btt;
	काष्ठा nd_namespace_common *ndns = nd_btt->ndns;

	/* arena offsets may be shअगरted from the base of the device */
	offset = adjust_initial_offset(nd_btt, offset);
	वापस nvdimm_ग_लिखो_bytes(ndns, offset, buf, n, flags);
पूर्ण

अटल पूर्णांक btt_info_ग_लिखो(काष्ठा arena_info *arena, काष्ठा btt_sb *super)
अणु
	पूर्णांक ret;

	/*
	 * infooff and info2off should always be at least 512B aligned.
	 * We rely on that to make sure rw_bytes करोes error clearing
	 * correctly, so make sure that is the हाल.
	 */
	dev_WARN_ONCE(to_dev(arena), !IS_ALIGNED(arena->infooff, 512),
		"arena->infooff: %#llx is unaligned\n", arena->infooff);
	dev_WARN_ONCE(to_dev(arena), !IS_ALIGNED(arena->info2off, 512),
		"arena->info2off: %#llx is unaligned\n", arena->info2off);

	ret = arena_ग_लिखो_bytes(arena, arena->info2off, super,
			माप(काष्ठा btt_sb), 0);
	अगर (ret)
		वापस ret;

	वापस arena_ग_लिखो_bytes(arena, arena->infooff, super,
			माप(काष्ठा btt_sb), 0);
पूर्ण

अटल पूर्णांक btt_info_पढ़ो(काष्ठा arena_info *arena, काष्ठा btt_sb *super)
अणु
	वापस arena_पढ़ो_bytes(arena, arena->infooff, super,
			माप(काष्ठा btt_sb), 0);
पूर्ण

/*
 * 'raw' version of btt_map ग_लिखो
 * Assumptions:
 *   mapping is in little-endian
 *   mapping contains 'E' and 'Z' flags as desired
 */
अटल पूर्णांक __btt_map_ग_लिखो(काष्ठा arena_info *arena, u32 lba, __le32 mapping,
		अचिन्हित दीर्घ flags)
अणु
	u64 ns_off = arena->mapoff + (lba * MAP_ENT_SIZE);

	अगर (unlikely(lba >= arena->बाह्यal_nlba))
		dev_err_ratelimited(to_dev(arena),
			"%s: lba %#x out of range (max: %#x)\n",
			__func__, lba, arena->बाह्यal_nlba);
	वापस arena_ग_लिखो_bytes(arena, ns_off, &mapping, MAP_ENT_SIZE, flags);
पूर्ण

अटल पूर्णांक btt_map_ग_लिखो(काष्ठा arena_info *arena, u32 lba, u32 mapping,
			u32 z_flag, u32 e_flag, अचिन्हित दीर्घ rwb_flags)
अणु
	u32 ze;
	__le32 mapping_le;

	/*
	 * This 'mapping' is supposed to be just the LBA mapping, without
	 * any flags set, so strip the flag bits.
	 */
	mapping = ent_lba(mapping);

	ze = (z_flag << 1) + e_flag;
	चयन (ze) अणु
	हाल 0:
		/*
		 * We want to set neither of the Z or E flags, and
		 * in the actual layout, this means setting the bit
		 * positions of both to '1' to indicate a 'normal'
		 * map entry
		 */
		mapping |= MAP_ENT_NORMAL;
		अवरोध;
	हाल 1:
		mapping |= (1 << MAP_ERR_SHIFT);
		अवरोध;
	हाल 2:
		mapping |= (1 << MAP_TRIM_SHIFT);
		अवरोध;
	शेष:
		/*
		 * The हाल where Z and E are both sent in as '1' could be
		 * स्थिरrued as a valid 'normal' हाल, but we decide not to,
		 * to aव्योम confusion
		 */
		dev_err_ratelimited(to_dev(arena),
			"Invalid use of Z and E flags\n");
		वापस -EIO;
	पूर्ण

	mapping_le = cpu_to_le32(mapping);
	वापस __btt_map_ग_लिखो(arena, lba, mapping_le, rwb_flags);
पूर्ण

अटल पूर्णांक btt_map_पढ़ो(काष्ठा arena_info *arena, u32 lba, u32 *mapping,
			पूर्णांक *trim, पूर्णांक *error, अचिन्हित दीर्घ rwb_flags)
अणु
	पूर्णांक ret;
	__le32 in;
	u32 raw_mapping, posपंचांगap, ze, z_flag, e_flag;
	u64 ns_off = arena->mapoff + (lba * MAP_ENT_SIZE);

	अगर (unlikely(lba >= arena->बाह्यal_nlba))
		dev_err_ratelimited(to_dev(arena),
			"%s: lba %#x out of range (max: %#x)\n",
			__func__, lba, arena->बाह्यal_nlba);

	ret = arena_पढ़ो_bytes(arena, ns_off, &in, MAP_ENT_SIZE, rwb_flags);
	अगर (ret)
		वापस ret;

	raw_mapping = le32_to_cpu(in);

	z_flag = ent_z_flag(raw_mapping);
	e_flag = ent_e_flag(raw_mapping);
	ze = (z_flag << 1) + e_flag;
	posपंचांगap = ent_lba(raw_mapping);

	/* Reuse the अणुz,eपूर्ण_flag variables क्रम *trim and *error */
	z_flag = 0;
	e_flag = 0;

	चयन (ze) अणु
	हाल 0:
		/* Initial state. Return posपंचांगap = premap */
		*mapping = lba;
		अवरोध;
	हाल 1:
		*mapping = posपंचांगap;
		e_flag = 1;
		अवरोध;
	हाल 2:
		*mapping = posपंचांगap;
		z_flag = 1;
		अवरोध;
	हाल 3:
		*mapping = posपंचांगap;
		अवरोध;
	शेष:
		वापस -EIO;
	पूर्ण

	अगर (trim)
		*trim = z_flag;
	अगर (error)
		*error = e_flag;

	वापस ret;
पूर्ण

अटल पूर्णांक btt_log_group_पढ़ो(काष्ठा arena_info *arena, u32 lane,
			काष्ठा log_group *log)
अणु
	वापस arena_पढ़ो_bytes(arena,
			arena->logoff + (lane * LOG_GRP_SIZE), log,
			LOG_GRP_SIZE, 0);
पूर्ण

अटल काष्ठा dentry *debugfs_root;

अटल व्योम arena_debugfs_init(काष्ठा arena_info *a, काष्ठा dentry *parent,
				पूर्णांक idx)
अणु
	अक्षर स_नाम[32];
	काष्ठा dentry *d;

	/* If क्रम some reason, parent bttN was not created, निकास */
	अगर (!parent)
		वापस;

	snम_लिखो(स_नाम, 32, "arena%d", idx);
	d = debugfs_create_dir(स_नाम, parent);
	अगर (IS_ERR_OR_शून्य(d))
		वापस;
	a->debugfs_dir = d;

	debugfs_create_x64("size", S_IRUGO, d, &a->size);
	debugfs_create_x64("external_lba_start", S_IRUGO, d,
				&a->बाह्यal_lba_start);
	debugfs_create_x32("internal_nlba", S_IRUGO, d, &a->पूर्णांकernal_nlba);
	debugfs_create_u32("internal_lbasize", S_IRUGO, d,
				&a->पूर्णांकernal_lbasize);
	debugfs_create_x32("external_nlba", S_IRUGO, d, &a->बाह्यal_nlba);
	debugfs_create_u32("external_lbasize", S_IRUGO, d,
				&a->बाह्यal_lbasize);
	debugfs_create_u32("nfree", S_IRUGO, d, &a->nमुक्त);
	debugfs_create_u16("version_major", S_IRUGO, d, &a->version_major);
	debugfs_create_u16("version_minor", S_IRUGO, d, &a->version_minor);
	debugfs_create_x64("nextoff", S_IRUGO, d, &a->nextoff);
	debugfs_create_x64("infooff", S_IRUGO, d, &a->infooff);
	debugfs_create_x64("dataoff", S_IRUGO, d, &a->dataoff);
	debugfs_create_x64("mapoff", S_IRUGO, d, &a->mapoff);
	debugfs_create_x64("logoff", S_IRUGO, d, &a->logoff);
	debugfs_create_x64("info2off", S_IRUGO, d, &a->info2off);
	debugfs_create_x32("flags", S_IRUGO, d, &a->flags);
	debugfs_create_u32("log_index_0", S_IRUGO, d, &a->log_index[0]);
	debugfs_create_u32("log_index_1", S_IRUGO, d, &a->log_index[1]);
पूर्ण

अटल व्योम btt_debugfs_init(काष्ठा btt *btt)
अणु
	पूर्णांक i = 0;
	काष्ठा arena_info *arena;

	btt->debugfs_dir = debugfs_create_dir(dev_name(&btt->nd_btt->dev),
						debugfs_root);
	अगर (IS_ERR_OR_शून्य(btt->debugfs_dir))
		वापस;

	list_क्रम_each_entry(arena, &btt->arena_list, list) अणु
		arena_debugfs_init(arena, btt->debugfs_dir, i);
		i++;
	पूर्ण
पूर्ण

अटल u32 log_seq(काष्ठा log_group *log, पूर्णांक log_idx)
अणु
	वापस le32_to_cpu(log->ent[log_idx].seq);
पूर्ण

/*
 * This function accepts two log entries, and uses the
 * sequence number to find the 'older' entry.
 * It also updates the sequence number in this old entry to
 * make it the 'new' one अगर the mark_flag is set.
 * Finally, it वापसs which of the entries was the older one.
 *
 * TODO The logic feels a bit kludge-y. make it better..
 */
अटल पूर्णांक btt_log_get_old(काष्ठा arena_info *a, काष्ठा log_group *log)
अणु
	पूर्णांक idx0 = a->log_index[0];
	पूर्णांक idx1 = a->log_index[1];
	पूर्णांक old;

	/*
	 * the first ever समय this is seen, the entry goes पूर्णांकo [0]
	 * the next समय, the following logic works out to put this
	 * (next) entry पूर्णांकo [1]
	 */
	अगर (log_seq(log, idx0) == 0) अणु
		log->ent[idx0].seq = cpu_to_le32(1);
		वापस 0;
	पूर्ण

	अगर (log_seq(log, idx0) == log_seq(log, idx1))
		वापस -EINVAL;
	अगर (log_seq(log, idx0) + log_seq(log, idx1) > 5)
		वापस -EINVAL;

	अगर (log_seq(log, idx0) < log_seq(log, idx1)) अणु
		अगर ((log_seq(log, idx1) - log_seq(log, idx0)) == 1)
			old = 0;
		अन्यथा
			old = 1;
	पूर्ण अन्यथा अणु
		अगर ((log_seq(log, idx0) - log_seq(log, idx1)) == 1)
			old = 1;
		अन्यथा
			old = 0;
	पूर्ण

	वापस old;
पूर्ण

/*
 * This function copies the desired (old/new) log entry पूर्णांकo ent अगर
 * it is not शून्य. It वापसs the sub-slot number (0 or 1)
 * where the desired log entry was found. Negative वापस values
 * indicate errors.
 */
अटल पूर्णांक btt_log_पढ़ो(काष्ठा arena_info *arena, u32 lane,
			काष्ठा log_entry *ent, पूर्णांक old_flag)
अणु
	पूर्णांक ret;
	पूर्णांक old_ent, ret_ent;
	काष्ठा log_group log;

	ret = btt_log_group_पढ़ो(arena, lane, &log);
	अगर (ret)
		वापस -EIO;

	old_ent = btt_log_get_old(arena, &log);
	अगर (old_ent < 0 || old_ent > 1) अणु
		dev_err(to_dev(arena),
				"log corruption (%d): lane %d seq [%d, %d]\n",
				old_ent, lane, log.ent[arena->log_index[0]].seq,
				log.ent[arena->log_index[1]].seq);
		/* TODO set error state? */
		वापस -EIO;
	पूर्ण

	ret_ent = (old_flag ? old_ent : (1 - old_ent));

	अगर (ent != शून्य)
		स_नकल(ent, &log.ent[arena->log_index[ret_ent]], LOG_ENT_SIZE);

	वापस ret_ent;
पूर्ण

/*
 * This function commits a log entry to media
 * It करोes _not_ prepare the मुक्तlist entry क्रम the next ग_लिखो
 * btt_flog_ग_लिखो is the wrapper क्रम updating the मुक्तlist elements
 */
अटल पूर्णांक __btt_log_ग_लिखो(काष्ठा arena_info *arena, u32 lane,
			u32 sub, काष्ठा log_entry *ent, अचिन्हित दीर्घ flags)
अणु
	पूर्णांक ret;
	u32 group_slot = arena->log_index[sub];
	अचिन्हित पूर्णांक log_half = LOG_ENT_SIZE / 2;
	व्योम *src = ent;
	u64 ns_off;

	ns_off = arena->logoff + (lane * LOG_GRP_SIZE) +
		(group_slot * LOG_ENT_SIZE);
	/* split the 16B ग_लिखो पूर्णांकo atomic, durable halves */
	ret = arena_ग_लिखो_bytes(arena, ns_off, src, log_half, flags);
	अगर (ret)
		वापस ret;

	ns_off += log_half;
	src += log_half;
	वापस arena_ग_लिखो_bytes(arena, ns_off, src, log_half, flags);
पूर्ण

अटल पूर्णांक btt_flog_ग_लिखो(काष्ठा arena_info *arena, u32 lane, u32 sub,
			काष्ठा log_entry *ent)
अणु
	पूर्णांक ret;

	ret = __btt_log_ग_लिखो(arena, lane, sub, ent, NVDIMM_IO_ATOMIC);
	अगर (ret)
		वापस ret;

	/* prepare the next मुक्त entry */
	arena->मुक्तlist[lane].sub = 1 - arena->मुक्तlist[lane].sub;
	अगर (++(arena->मुक्तlist[lane].seq) == 4)
		arena->मुक्तlist[lane].seq = 1;
	अगर (ent_e_flag(le32_to_cpu(ent->old_map)))
		arena->मुक्तlist[lane].has_err = 1;
	arena->मुक्तlist[lane].block = ent_lba(le32_to_cpu(ent->old_map));

	वापस ret;
पूर्ण

/*
 * This function initializes the BTT map to the initial state, which is
 * all-zeroes, and indicates an identity mapping
 */
अटल पूर्णांक btt_map_init(काष्ठा arena_info *arena)
अणु
	पूर्णांक ret = -EINVAL;
	व्योम *zerobuf;
	माप_प्रकार offset = 0;
	माप_प्रकार chunk_size = SZ_2M;
	माप_प्रकार mapsize = arena->logoff - arena->mapoff;

	zerobuf = kzalloc(chunk_size, GFP_KERNEL);
	अगर (!zerobuf)
		वापस -ENOMEM;

	/*
	 * mapoff should always be at least 512B  aligned. We rely on that to
	 * make sure rw_bytes करोes error clearing correctly, so make sure that
	 * is the हाल.
	 */
	dev_WARN_ONCE(to_dev(arena), !IS_ALIGNED(arena->mapoff, 512),
		"arena->mapoff: %#llx is unaligned\n", arena->mapoff);

	जबतक (mapsize) अणु
		माप_प्रकार size = min(mapsize, chunk_size);

		dev_WARN_ONCE(to_dev(arena), size < 512,
			"chunk size: %#zx is unaligned\n", size);
		ret = arena_ग_लिखो_bytes(arena, arena->mapoff + offset, zerobuf,
				size, 0);
		अगर (ret)
			जाओ मुक्त;

		offset += size;
		mapsize -= size;
		cond_resched();
	पूर्ण

 मुक्त:
	kमुक्त(zerobuf);
	वापस ret;
पूर्ण

/*
 * This function initializes the BTT log with 'fake' entries poपूर्णांकing
 * to the initial reserved set of blocks as being मुक्त
 */
अटल पूर्णांक btt_log_init(काष्ठा arena_info *arena)
अणु
	माप_प्रकार logsize = arena->info2off - arena->logoff;
	माप_प्रकार chunk_size = SZ_4K, offset = 0;
	काष्ठा log_entry ent;
	व्योम *zerobuf;
	पूर्णांक ret;
	u32 i;

	zerobuf = kzalloc(chunk_size, GFP_KERNEL);
	अगर (!zerobuf)
		वापस -ENOMEM;
	/*
	 * logoff should always be at least 512B  aligned. We rely on that to
	 * make sure rw_bytes करोes error clearing correctly, so make sure that
	 * is the हाल.
	 */
	dev_WARN_ONCE(to_dev(arena), !IS_ALIGNED(arena->logoff, 512),
		"arena->logoff: %#llx is unaligned\n", arena->logoff);

	जबतक (logsize) अणु
		माप_प्रकार size = min(logsize, chunk_size);

		dev_WARN_ONCE(to_dev(arena), size < 512,
			"chunk size: %#zx is unaligned\n", size);
		ret = arena_ग_लिखो_bytes(arena, arena->logoff + offset, zerobuf,
				size, 0);
		अगर (ret)
			जाओ मुक्त;

		offset += size;
		logsize -= size;
		cond_resched();
	पूर्ण

	क्रम (i = 0; i < arena->nमुक्त; i++) अणु
		ent.lba = cpu_to_le32(i);
		ent.old_map = cpu_to_le32(arena->बाह्यal_nlba + i);
		ent.new_map = cpu_to_le32(arena->बाह्यal_nlba + i);
		ent.seq = cpu_to_le32(LOG_SEQ_INIT);
		ret = __btt_log_ग_लिखो(arena, i, 0, &ent, 0);
		अगर (ret)
			जाओ मुक्त;
	पूर्ण

 मुक्त:
	kमुक्त(zerobuf);
	वापस ret;
पूर्ण

अटल u64 to_namespace_offset(काष्ठा arena_info *arena, u64 lba)
अणु
	वापस arena->dataoff + ((u64)lba * arena->पूर्णांकernal_lbasize);
पूर्ण

अटल पूर्णांक arena_clear_मुक्तlist_error(काष्ठा arena_info *arena, u32 lane)
अणु
	पूर्णांक ret = 0;

	अगर (arena->मुक्तlist[lane].has_err) अणु
		व्योम *zero_page = page_address(ZERO_PAGE(0));
		u32 lba = arena->मुक्तlist[lane].block;
		u64 nsoff = to_namespace_offset(arena, lba);
		अचिन्हित दीर्घ len = arena->sector_size;

		mutex_lock(&arena->err_lock);

		जबतक (len) अणु
			अचिन्हित दीर्घ chunk = min(len, PAGE_SIZE);

			ret = arena_ग_लिखो_bytes(arena, nsoff, zero_page,
				chunk, 0);
			अगर (ret)
				अवरोध;
			len -= chunk;
			nsoff += chunk;
			अगर (len == 0)
				arena->मुक्तlist[lane].has_err = 0;
		पूर्ण
		mutex_unlock(&arena->err_lock);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक btt_मुक्तlist_init(काष्ठा arena_info *arena)
अणु
	पूर्णांक new, ret;
	काष्ठा log_entry log_new;
	u32 i, map_entry, log_oldmap, log_newmap;

	arena->मुक्तlist = kसुस्मृति(arena->nमुक्त, माप(काष्ठा मुक्त_entry),
					GFP_KERNEL);
	अगर (!arena->मुक्तlist)
		वापस -ENOMEM;

	क्रम (i = 0; i < arena->nमुक्त; i++) अणु
		new = btt_log_पढ़ो(arena, i, &log_new, LOG_NEW_ENT);
		अगर (new < 0)
			वापस new;

		/* old and new map entries with any flags stripped out */
		log_oldmap = ent_lba(le32_to_cpu(log_new.old_map));
		log_newmap = ent_lba(le32_to_cpu(log_new.new_map));

		/* sub poपूर्णांकs to the next one to be overwritten */
		arena->मुक्तlist[i].sub = 1 - new;
		arena->मुक्तlist[i].seq = nd_inc_seq(le32_to_cpu(log_new.seq));
		arena->मुक्तlist[i].block = log_oldmap;

		/*
		 * FIXME: अगर error clearing fails during init, we want to make
		 * the BTT पढ़ो-only
		 */
		अगर (ent_e_flag(le32_to_cpu(log_new.old_map)) &&
		    !ent_normal(le32_to_cpu(log_new.old_map))) अणु
			arena->मुक्तlist[i].has_err = 1;
			ret = arena_clear_मुक्तlist_error(arena, i);
			अगर (ret)
				dev_err_ratelimited(to_dev(arena),
					"Unable to clear known errors\n");
		पूर्ण

		/* This implies a newly created or untouched flog entry */
		अगर (log_oldmap == log_newmap)
			जारी;

		/* Check अगर map recovery is needed */
		ret = btt_map_पढ़ो(arena, le32_to_cpu(log_new.lba), &map_entry,
				शून्य, शून्य, 0);
		अगर (ret)
			वापस ret;

		/*
		 * The map_entry from btt_पढ़ो_map is stripped of any flag bits,
		 * so use the stripped out versions from the log as well क्रम
		 * testing whether recovery is needed. For restoration, use the
		 * 'raw' version of the log entries as that captured what we
		 * were going to ग_लिखो originally.
		 */
		अगर ((log_newmap != map_entry) && (log_oldmap == map_entry)) अणु
			/*
			 * Last transaction wrote the flog, but wasn't able
			 * to complete the map ग_लिखो. So fix up the map.
			 */
			ret = btt_map_ग_लिखो(arena, le32_to_cpu(log_new.lba),
					le32_to_cpu(log_new.new_map), 0, 0, 0);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool ent_is_padding(काष्ठा log_entry *ent)
अणु
	वापस (ent->lba == 0) && (ent->old_map == 0) && (ent->new_map == 0)
		&& (ent->seq == 0);
पूर्ण

/*
 * Detecting valid log indices: We पढ़ो a log group (see the comments in btt.h
 * क्रम a description of a 'log_group' and its 'slots'), and iterate over its
 * four slots. We expect that a padding slot will be all-zeroes, and use this
 * to detect a padding slot vs. an actual entry.
 *
 * If a log_group is in the initial state, i.e. hasn't been used since the
 * creation of this BTT layout, it will have three of the four slots with
 * zeroes. We skip over these log_groups क्रम the detection of log_index. If
 * all log_groups are in the initial state (i.e. the BTT has never been
 * written to), it is safe to assume the 'new format' of log entries in slots
 * (0, 1).
 */
अटल पूर्णांक log_set_indices(काष्ठा arena_info *arena)
अणु
	bool idx_set = false, initial_state = true;
	पूर्णांक ret, log_index[2] = अणु-1, -1पूर्ण;
	u32 i, j, next_idx = 0;
	काष्ठा log_group log;
	u32 pad_count = 0;

	क्रम (i = 0; i < arena->nमुक्त; i++) अणु
		ret = btt_log_group_पढ़ो(arena, i, &log);
		अगर (ret < 0)
			वापस ret;

		क्रम (j = 0; j < 4; j++) अणु
			अगर (!idx_set) अणु
				अगर (ent_is_padding(&log.ent[j])) अणु
					pad_count++;
					जारी;
				पूर्ण अन्यथा अणु
					/* Skip अगर index has been recorded */
					अगर ((next_idx == 1) &&
						(j == log_index[0]))
						जारी;
					/* valid entry, record index */
					log_index[next_idx] = j;
					next_idx++;
				पूर्ण
				अगर (next_idx == 2) अणु
					/* two valid entries found */
					idx_set = true;
				पूर्ण अन्यथा अगर (next_idx > 2) अणु
					/* too many valid indices */
					वापस -ENXIO;
				पूर्ण
			पूर्ण अन्यथा अणु
				/*
				 * once the indices have been set, just verअगरy
				 * that all subsequent log groups are either in
				 * their initial state or follow the same
				 * indices.
				 */
				अगर (j == log_index[0]) अणु
					/* entry must be 'valid' */
					अगर (ent_is_padding(&log.ent[j]))
						वापस -ENXIO;
				पूर्ण अन्यथा अगर (j == log_index[1]) अणु
					;
					/*
					 * log_index[1] can be padding अगर the
					 * lane never got used and it is still
					 * in the initial state (three 'padding'
					 * entries)
					 */
				पूर्ण अन्यथा अणु
					/* entry must be invalid (padding) */
					अगर (!ent_is_padding(&log.ent[j]))
						वापस -ENXIO;
				पूर्ण
			पूर्ण
		पूर्ण
		/*
		 * If any of the log_groups have more than one valid,
		 * non-padding entry, then the we are no दीर्घer in the
		 * initial_state
		 */
		अगर (pad_count < 3)
			initial_state = false;
		pad_count = 0;
	पूर्ण

	अगर (!initial_state && !idx_set)
		वापस -ENXIO;

	/*
	 * If all the entries in the log were in the initial state,
	 * assume new padding scheme
	 */
	अगर (initial_state)
		log_index[1] = 1;

	/*
	 * Only allow the known permutations of log/padding indices,
	 * i.e. (0, 1), and (0, 2)
	 */
	अगर ((log_index[0] == 0) && ((log_index[1] == 1) || (log_index[1] == 2)))
		; /* known index possibilities */
	अन्यथा अणु
		dev_err(to_dev(arena), "Found an unknown padding scheme\n");
		वापस -ENXIO;
	पूर्ण

	arena->log_index[0] = log_index[0];
	arena->log_index[1] = log_index[1];
	dev_dbg(to_dev(arena), "log_index_0 = %d\n", log_index[0]);
	dev_dbg(to_dev(arena), "log_index_1 = %d\n", log_index[1]);
	वापस 0;
पूर्ण

अटल पूर्णांक btt_rtt_init(काष्ठा arena_info *arena)
अणु
	arena->rtt = kसुस्मृति(arena->nमुक्त, माप(u32), GFP_KERNEL);
	अगर (arena->rtt == शून्य)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक btt_maplocks_init(काष्ठा arena_info *arena)
अणु
	u32 i;

	arena->map_locks = kसुस्मृति(arena->nमुक्त, माप(काष्ठा aligned_lock),
				GFP_KERNEL);
	अगर (!arena->map_locks)
		वापस -ENOMEM;

	क्रम (i = 0; i < arena->nमुक्त; i++)
		spin_lock_init(&arena->map_locks[i].lock);

	वापस 0;
पूर्ण

अटल काष्ठा arena_info *alloc_arena(काष्ठा btt *btt, माप_प्रकार size,
				माप_प्रकार start, माप_प्रकार arena_off)
अणु
	काष्ठा arena_info *arena;
	u64 logsize, mapsize, datasize;
	u64 available = size;

	arena = kzalloc(माप(काष्ठा arena_info), GFP_KERNEL);
	अगर (!arena)
		वापस शून्य;
	arena->nd_btt = btt->nd_btt;
	arena->sector_size = btt->sector_size;
	mutex_init(&arena->err_lock);

	अगर (!size)
		वापस arena;

	arena->size = size;
	arena->बाह्यal_lba_start = start;
	arena->बाह्यal_lbasize = btt->lbasize;
	arena->पूर्णांकernal_lbasize = roundup(arena->बाह्यal_lbasize,
					INT_LBASIZE_ALIGNMENT);
	arena->nमुक्त = BTT_DEFAULT_NFREE;
	arena->version_major = btt->nd_btt->version_major;
	arena->version_minor = btt->nd_btt->version_minor;

	अगर (available % BTT_PG_SIZE)
		available -= (available % BTT_PG_SIZE);

	/* Two pages are reserved क्रम the super block and its copy */
	available -= 2 * BTT_PG_SIZE;

	/* The log takes a fixed amount of space based on nमुक्त */
	logsize = roundup(arena->nमुक्त * LOG_GRP_SIZE, BTT_PG_SIZE);
	available -= logsize;

	/* Calculate optimal split between map and data area */
	arena->पूर्णांकernal_nlba = भाग_u64(available - BTT_PG_SIZE,
			arena->पूर्णांकernal_lbasize + MAP_ENT_SIZE);
	arena->बाह्यal_nlba = arena->पूर्णांकernal_nlba - arena->nमुक्त;

	mapsize = roundup((arena->बाह्यal_nlba * MAP_ENT_SIZE), BTT_PG_SIZE);
	datasize = available - mapsize;

	/* 'Absolute' values, relative to start of storage space */
	arena->infooff = arena_off;
	arena->dataoff = arena->infooff + BTT_PG_SIZE;
	arena->mapoff = arena->dataoff + datasize;
	arena->logoff = arena->mapoff + mapsize;
	arena->info2off = arena->logoff + logsize;

	/* Default log indices are (0,1) */
	arena->log_index[0] = 0;
	arena->log_index[1] = 1;
	वापस arena;
पूर्ण

अटल व्योम मुक्त_arenas(काष्ठा btt *btt)
अणु
	काष्ठा arena_info *arena, *next;

	list_क्रम_each_entry_safe(arena, next, &btt->arena_list, list) अणु
		list_del(&arena->list);
		kमुक्त(arena->rtt);
		kमुक्त(arena->map_locks);
		kमुक्त(arena->मुक्तlist);
		debugfs_हटाओ_recursive(arena->debugfs_dir);
		kमुक्त(arena);
	पूर्ण
पूर्ण

/*
 * This function पढ़ोs an existing valid btt superblock and
 * populates the corresponding arena_info काष्ठा
 */
अटल व्योम parse_arena_meta(काष्ठा arena_info *arena, काष्ठा btt_sb *super,
				u64 arena_off)
अणु
	arena->पूर्णांकernal_nlba = le32_to_cpu(super->पूर्णांकernal_nlba);
	arena->पूर्णांकernal_lbasize = le32_to_cpu(super->पूर्णांकernal_lbasize);
	arena->बाह्यal_nlba = le32_to_cpu(super->बाह्यal_nlba);
	arena->बाह्यal_lbasize = le32_to_cpu(super->बाह्यal_lbasize);
	arena->nमुक्त = le32_to_cpu(super->nमुक्त);
	arena->version_major = le16_to_cpu(super->version_major);
	arena->version_minor = le16_to_cpu(super->version_minor);

	arena->nextoff = (super->nextoff == 0) ? 0 : (arena_off +
			le64_to_cpu(super->nextoff));
	arena->infooff = arena_off;
	arena->dataoff = arena_off + le64_to_cpu(super->dataoff);
	arena->mapoff = arena_off + le64_to_cpu(super->mapoff);
	arena->logoff = arena_off + le64_to_cpu(super->logoff);
	arena->info2off = arena_off + le64_to_cpu(super->info2off);

	arena->size = (le64_to_cpu(super->nextoff) > 0)
		? (le64_to_cpu(super->nextoff))
		: (arena->info2off - arena->infooff + BTT_PG_SIZE);

	arena->flags = le32_to_cpu(super->flags);
पूर्ण

अटल पूर्णांक discover_arenas(काष्ठा btt *btt)
अणु
	पूर्णांक ret = 0;
	काष्ठा arena_info *arena;
	काष्ठा btt_sb *super;
	माप_प्रकार reमुख्यing = btt->rawsize;
	u64 cur_nlba = 0;
	माप_प्रकार cur_off = 0;
	पूर्णांक num_arenas = 0;

	super = kzalloc(माप(*super), GFP_KERNEL);
	अगर (!super)
		वापस -ENOMEM;

	जबतक (reमुख्यing) अणु
		/* Alloc memory क्रम arena */
		arena = alloc_arena(btt, 0, 0, 0);
		अगर (!arena) अणु
			ret = -ENOMEM;
			जाओ out_super;
		पूर्ण

		arena->infooff = cur_off;
		ret = btt_info_पढ़ो(arena, super);
		अगर (ret)
			जाओ out;

		अगर (!nd_btt_arena_is_valid(btt->nd_btt, super)) अणु
			अगर (reमुख्यing == btt->rawsize) अणु
				btt->init_state = INIT_NOTFOUND;
				dev_info(to_dev(arena), "No existing arenas\n");
				जाओ out;
			पूर्ण अन्यथा अणु
				dev_err(to_dev(arena),
						"Found corrupted metadata!\n");
				ret = -ENODEV;
				जाओ out;
			पूर्ण
		पूर्ण

		arena->बाह्यal_lba_start = cur_nlba;
		parse_arena_meta(arena, super, cur_off);

		ret = log_set_indices(arena);
		अगर (ret) अणु
			dev_err(to_dev(arena),
				"Unable to deduce log/padding indices\n");
			जाओ out;
		पूर्ण

		ret = btt_मुक्तlist_init(arena);
		अगर (ret)
			जाओ out;

		ret = btt_rtt_init(arena);
		अगर (ret)
			जाओ out;

		ret = btt_maplocks_init(arena);
		अगर (ret)
			जाओ out;

		list_add_tail(&arena->list, &btt->arena_list);

		reमुख्यing -= arena->size;
		cur_off += arena->size;
		cur_nlba += arena->बाह्यal_nlba;
		num_arenas++;

		अगर (arena->nextoff == 0)
			अवरोध;
	पूर्ण
	btt->num_arenas = num_arenas;
	btt->nlba = cur_nlba;
	btt->init_state = INIT_READY;

	kमुक्त(super);
	वापस ret;

 out:
	kमुक्त(arena);
	मुक्त_arenas(btt);
 out_super:
	kमुक्त(super);
	वापस ret;
पूर्ण

अटल पूर्णांक create_arenas(काष्ठा btt *btt)
अणु
	माप_प्रकार reमुख्यing = btt->rawsize;
	माप_प्रकार cur_off = 0;

	जबतक (reमुख्यing) अणु
		काष्ठा arena_info *arena;
		माप_प्रकार arena_size = min_t(u64, ARENA_MAX_SIZE, reमुख्यing);

		reमुख्यing -= arena_size;
		अगर (arena_size < ARENA_MIN_SIZE)
			अवरोध;

		arena = alloc_arena(btt, arena_size, btt->nlba, cur_off);
		अगर (!arena) अणु
			मुक्त_arenas(btt);
			वापस -ENOMEM;
		पूर्ण
		btt->nlba += arena->बाह्यal_nlba;
		अगर (reमुख्यing >= ARENA_MIN_SIZE)
			arena->nextoff = arena->size;
		अन्यथा
			arena->nextoff = 0;
		cur_off += arena_size;
		list_add_tail(&arena->list, &btt->arena_list);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function completes arena initialization by writing
 * all the metadata.
 * It is only called क्रम an uninitialized arena when a ग_लिखो
 * to that arena occurs क्रम the first समय.
 */
अटल पूर्णांक btt_arena_ग_लिखो_layout(काष्ठा arena_info *arena)
अणु
	पूर्णांक ret;
	u64 sum;
	काष्ठा btt_sb *super;
	काष्ठा nd_btt *nd_btt = arena->nd_btt;
	स्थिर u8 *parent_uuid = nd_dev_to_uuid(&nd_btt->ndns->dev);

	ret = btt_map_init(arena);
	अगर (ret)
		वापस ret;

	ret = btt_log_init(arena);
	अगर (ret)
		वापस ret;

	super = kzalloc(माप(काष्ठा btt_sb), GFP_NOIO);
	अगर (!super)
		वापस -ENOMEM;

	म_नकलन(super->signature, BTT_SIG, BTT_SIG_LEN);
	स_नकल(super->uuid, nd_btt->uuid, 16);
	स_नकल(super->parent_uuid, parent_uuid, 16);
	super->flags = cpu_to_le32(arena->flags);
	super->version_major = cpu_to_le16(arena->version_major);
	super->version_minor = cpu_to_le16(arena->version_minor);
	super->बाह्यal_lbasize = cpu_to_le32(arena->बाह्यal_lbasize);
	super->बाह्यal_nlba = cpu_to_le32(arena->बाह्यal_nlba);
	super->पूर्णांकernal_lbasize = cpu_to_le32(arena->पूर्णांकernal_lbasize);
	super->पूर्णांकernal_nlba = cpu_to_le32(arena->पूर्णांकernal_nlba);
	super->nमुक्त = cpu_to_le32(arena->nमुक्त);
	super->infosize = cpu_to_le32(माप(काष्ठा btt_sb));
	super->nextoff = cpu_to_le64(arena->nextoff);
	/*
	 * Subtract arena->infooff (arena start) so numbers are relative
	 * to 'this' arena
	 */
	super->dataoff = cpu_to_le64(arena->dataoff - arena->infooff);
	super->mapoff = cpu_to_le64(arena->mapoff - arena->infooff);
	super->logoff = cpu_to_le64(arena->logoff - arena->infooff);
	super->info2off = cpu_to_le64(arena->info2off - arena->infooff);

	super->flags = 0;
	sum = nd_sb_checksum((काष्ठा nd_gen_sb *) super);
	super->checksum = cpu_to_le64(sum);

	ret = btt_info_ग_लिखो(arena, super);

	kमुक्त(super);
	वापस ret;
पूर्ण

/*
 * This function completes the initialization क्रम the BTT namespace
 * such that it is पढ़ोy to accept IOs
 */
अटल पूर्णांक btt_meta_init(काष्ठा btt *btt)
अणु
	पूर्णांक ret = 0;
	काष्ठा arena_info *arena;

	mutex_lock(&btt->init_lock);
	list_क्रम_each_entry(arena, &btt->arena_list, list) अणु
		ret = btt_arena_ग_लिखो_layout(arena);
		अगर (ret)
			जाओ unlock;

		ret = btt_मुक्तlist_init(arena);
		अगर (ret)
			जाओ unlock;

		ret = btt_rtt_init(arena);
		अगर (ret)
			जाओ unlock;

		ret = btt_maplocks_init(arena);
		अगर (ret)
			जाओ unlock;
	पूर्ण

	btt->init_state = INIT_READY;

 unlock:
	mutex_unlock(&btt->init_lock);
	वापस ret;
पूर्ण

अटल u32 btt_meta_size(काष्ठा btt *btt)
अणु
	वापस btt->lbasize - btt->sector_size;
पूर्ण

/*
 * This function calculates the arena in which the given LBA lies
 * by करोing a linear walk. This is acceptable since we expect only
 * a few arenas. If we have backing devices that get much larger,
 * we can स्थिरruct a balanced binary tree of arenas at init समय
 * so that this range search becomes faster.
 */
अटल पूर्णांक lba_to_arena(काष्ठा btt *btt, sector_t sector, __u32 *premap,
				काष्ठा arena_info **arena)
अणु
	काष्ठा arena_info *arena_list;
	__u64 lba = भाग_u64(sector << SECTOR_SHIFT, btt->sector_size);

	list_क्रम_each_entry(arena_list, &btt->arena_list, list) अणु
		अगर (lba < arena_list->बाह्यal_nlba) अणु
			*arena = arena_list;
			*premap = lba;
			वापस 0;
		पूर्ण
		lba -= arena_list->बाह्यal_nlba;
	पूर्ण

	वापस -EIO;
पूर्ण

/*
 * The following (lock_map, unlock_map) are mostly just to improve
 * पढ़ोability, since they index पूर्णांकo an array of locks
 */
अटल व्योम lock_map(काष्ठा arena_info *arena, u32 premap)
		__acquires(&arena->map_locks[idx].lock)
अणु
	u32 idx = (premap * MAP_ENT_SIZE / L1_CACHE_BYTES) % arena->nमुक्त;

	spin_lock(&arena->map_locks[idx].lock);
पूर्ण

अटल व्योम unlock_map(काष्ठा arena_info *arena, u32 premap)
		__releases(&arena->map_locks[idx].lock)
अणु
	u32 idx = (premap * MAP_ENT_SIZE / L1_CACHE_BYTES) % arena->nमुक्त;

	spin_unlock(&arena->map_locks[idx].lock);
पूर्ण

अटल पूर्णांक btt_data_पढ़ो(काष्ठा arena_info *arena, काष्ठा page *page,
			अचिन्हित पूर्णांक off, u32 lba, u32 len)
अणु
	पूर्णांक ret;
	u64 nsoff = to_namespace_offset(arena, lba);
	व्योम *mem = kmap_atomic(page);

	ret = arena_पढ़ो_bytes(arena, nsoff, mem + off, len, NVDIMM_IO_ATOMIC);
	kunmap_atomic(mem);

	वापस ret;
पूर्ण

अटल पूर्णांक btt_data_ग_लिखो(काष्ठा arena_info *arena, u32 lba,
			काष्ठा page *page, अचिन्हित पूर्णांक off, u32 len)
अणु
	पूर्णांक ret;
	u64 nsoff = to_namespace_offset(arena, lba);
	व्योम *mem = kmap_atomic(page);

	ret = arena_ग_लिखो_bytes(arena, nsoff, mem + off, len, NVDIMM_IO_ATOMIC);
	kunmap_atomic(mem);

	वापस ret;
पूर्ण

अटल व्योम zero_fill_data(काष्ठा page *page, अचिन्हित पूर्णांक off, u32 len)
अणु
	व्योम *mem = kmap_atomic(page);

	स_रखो(mem + off, 0, len);
	kunmap_atomic(mem);
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_INTEGRITY
अटल पूर्णांक btt_rw_पूर्णांकegrity(काष्ठा btt *btt, काष्ठा bio_पूर्णांकegrity_payload *bip,
			काष्ठा arena_info *arena, u32 posपंचांगap, पूर्णांक rw)
अणु
	अचिन्हित पूर्णांक len = btt_meta_size(btt);
	u64 meta_nsoff;
	पूर्णांक ret = 0;

	अगर (bip == शून्य)
		वापस 0;

	meta_nsoff = to_namespace_offset(arena, posपंचांगap) + btt->sector_size;

	जबतक (len) अणु
		अचिन्हित पूर्णांक cur_len;
		काष्ठा bio_vec bv;
		व्योम *mem;

		bv = bvec_iter_bvec(bip->bip_vec, bip->bip_iter);
		/*
		 * The 'bv' obtained from bvec_iter_bvec has its .bv_len and
		 * .bv_offset alपढ़ोy adjusted क्रम iter->bi_bvec_करोne, and we
		 * can use those directly
		 */

		cur_len = min(len, bv.bv_len);
		mem = kmap_atomic(bv.bv_page);
		अगर (rw)
			ret = arena_ग_लिखो_bytes(arena, meta_nsoff,
					mem + bv.bv_offset, cur_len,
					NVDIMM_IO_ATOMIC);
		अन्यथा
			ret = arena_पढ़ो_bytes(arena, meta_nsoff,
					mem + bv.bv_offset, cur_len,
					NVDIMM_IO_ATOMIC);

		kunmap_atomic(mem);
		अगर (ret)
			वापस ret;

		len -= cur_len;
		meta_nsoff += cur_len;
		अगर (!bvec_iter_advance(bip->bip_vec, &bip->bip_iter, cur_len))
			वापस -EIO;
	पूर्ण

	वापस ret;
पूर्ण

#अन्यथा /* CONFIG_BLK_DEV_INTEGRITY */
अटल पूर्णांक btt_rw_पूर्णांकegrity(काष्ठा btt *btt, काष्ठा bio_पूर्णांकegrity_payload *bip,
			काष्ठा arena_info *arena, u32 posपंचांगap, पूर्णांक rw)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक btt_पढ़ो_pg(काष्ठा btt *btt, काष्ठा bio_पूर्णांकegrity_payload *bip,
			काष्ठा page *page, अचिन्हित पूर्णांक off, sector_t sector,
			अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	पूर्णांक t_flag, e_flag;
	काष्ठा arena_info *arena = शून्य;
	u32 lane = 0, premap, posपंचांगap;

	जबतक (len) अणु
		u32 cur_len;

		lane = nd_region_acquire_lane(btt->nd_region);

		ret = lba_to_arena(btt, sector, &premap, &arena);
		अगर (ret)
			जाओ out_lane;

		cur_len = min(btt->sector_size, len);

		ret = btt_map_पढ़ो(arena, premap, &posपंचांगap, &t_flag, &e_flag,
				NVDIMM_IO_ATOMIC);
		अगर (ret)
			जाओ out_lane;

		/*
		 * We loop to make sure that the post map LBA didn't change
		 * from under us between writing the RTT and करोing the actual
		 * पढ़ो.
		 */
		जबतक (1) अणु
			u32 new_map;
			पूर्णांक new_t, new_e;

			अगर (t_flag) अणु
				zero_fill_data(page, off, cur_len);
				जाओ out_lane;
			पूर्ण

			अगर (e_flag) अणु
				ret = -EIO;
				जाओ out_lane;
			पूर्ण

			arena->rtt[lane] = RTT_VALID | posपंचांगap;
			/*
			 * Barrier to make sure this ग_लिखो is not reordered
			 * to करो the verअगरication map_पढ़ो beक्रमe the RTT store
			 */
			barrier();

			ret = btt_map_पढ़ो(arena, premap, &new_map, &new_t,
						&new_e, NVDIMM_IO_ATOMIC);
			अगर (ret)
				जाओ out_rtt;

			अगर ((posपंचांगap == new_map) && (t_flag == new_t) &&
					(e_flag == new_e))
				अवरोध;

			posपंचांगap = new_map;
			t_flag = new_t;
			e_flag = new_e;
		पूर्ण

		ret = btt_data_पढ़ो(arena, page, off, posपंचांगap, cur_len);
		अगर (ret) अणु
			/* Media error - set the e_flag */
			अगर (btt_map_ग_लिखो(arena, premap, posपंचांगap, 0, 1, NVDIMM_IO_ATOMIC))
				dev_warn_ratelimited(to_dev(arena),
					"Error persistently tracking bad blocks at %#x\n",
					premap);
			जाओ out_rtt;
		पूर्ण

		अगर (bip) अणु
			ret = btt_rw_पूर्णांकegrity(btt, bip, arena, posपंचांगap, READ);
			अगर (ret)
				जाओ out_rtt;
		पूर्ण

		arena->rtt[lane] = RTT_INVALID;
		nd_region_release_lane(btt->nd_region, lane);

		len -= cur_len;
		off += cur_len;
		sector += btt->sector_size >> SECTOR_SHIFT;
	पूर्ण

	वापस 0;

 out_rtt:
	arena->rtt[lane] = RTT_INVALID;
 out_lane:
	nd_region_release_lane(btt->nd_region, lane);
	वापस ret;
पूर्ण

/*
 * Normally, arena_अणुपढ़ो,ग_लिखोपूर्ण_bytes will take care of the initial offset
 * adjusपंचांगent, but in the हाल of btt_is_badblock, where we query is_bad_pmem,
 * we need the final, raw namespace offset here
 */
अटल bool btt_is_badblock(काष्ठा btt *btt, काष्ठा arena_info *arena,
		u32 posपंचांगap)
अणु
	u64 nsoff = adjust_initial_offset(arena->nd_btt,
			to_namespace_offset(arena, posपंचांगap));
	sector_t phys_sector = nsoff >> 9;

	वापस is_bad_pmem(btt->phys_bb, phys_sector, arena->पूर्णांकernal_lbasize);
पूर्ण

अटल पूर्णांक btt_ग_लिखो_pg(काष्ठा btt *btt, काष्ठा bio_पूर्णांकegrity_payload *bip,
			sector_t sector, काष्ठा page *page, अचिन्हित पूर्णांक off,
			अचिन्हित पूर्णांक len)
अणु
	पूर्णांक ret = 0;
	काष्ठा arena_info *arena = शून्य;
	u32 premap = 0, old_posपंचांगap, new_posपंचांगap, lane = 0, i;
	काष्ठा log_entry log;
	पूर्णांक sub;

	जबतक (len) अणु
		u32 cur_len;
		पूर्णांक e_flag;

 retry:
		lane = nd_region_acquire_lane(btt->nd_region);

		ret = lba_to_arena(btt, sector, &premap, &arena);
		अगर (ret)
			जाओ out_lane;
		cur_len = min(btt->sector_size, len);

		अगर ((arena->flags & IB_FLAG_ERROR_MASK) != 0) अणु
			ret = -EIO;
			जाओ out_lane;
		पूर्ण

		अगर (btt_is_badblock(btt, arena, arena->मुक्तlist[lane].block))
			arena->मुक्तlist[lane].has_err = 1;

		अगर (mutex_is_locked(&arena->err_lock)
				|| arena->मुक्तlist[lane].has_err) अणु
			nd_region_release_lane(btt->nd_region, lane);

			ret = arena_clear_मुक्तlist_error(arena, lane);
			अगर (ret)
				वापस ret;

			/* OK to acquire a dअगरferent lane/मुक्त block */
			जाओ retry;
		पूर्ण

		new_posपंचांगap = arena->मुक्तlist[lane].block;

		/* Wait अगर the new block is being पढ़ो from */
		क्रम (i = 0; i < arena->nमुक्त; i++)
			जबतक (arena->rtt[i] == (RTT_VALID | new_posपंचांगap))
				cpu_relax();


		अगर (new_posपंचांगap >= arena->पूर्णांकernal_nlba) अणु
			ret = -EIO;
			जाओ out_lane;
		पूर्ण

		ret = btt_data_ग_लिखो(arena, new_posपंचांगap, page, off, cur_len);
		अगर (ret)
			जाओ out_lane;

		अगर (bip) अणु
			ret = btt_rw_पूर्णांकegrity(btt, bip, arena, new_posपंचांगap,
						WRITE);
			अगर (ret)
				जाओ out_lane;
		पूर्ण

		lock_map(arena, premap);
		ret = btt_map_पढ़ो(arena, premap, &old_posपंचांगap, शून्य, &e_flag,
				NVDIMM_IO_ATOMIC);
		अगर (ret)
			जाओ out_map;
		अगर (old_posपंचांगap >= arena->पूर्णांकernal_nlba) अणु
			ret = -EIO;
			जाओ out_map;
		पूर्ण
		अगर (e_flag)
			set_e_flag(old_posपंचांगap);

		log.lba = cpu_to_le32(premap);
		log.old_map = cpu_to_le32(old_posपंचांगap);
		log.new_map = cpu_to_le32(new_posपंचांगap);
		log.seq = cpu_to_le32(arena->मुक्तlist[lane].seq);
		sub = arena->मुक्तlist[lane].sub;
		ret = btt_flog_ग_लिखो(arena, lane, sub, &log);
		अगर (ret)
			जाओ out_map;

		ret = btt_map_ग_लिखो(arena, premap, new_posपंचांगap, 0, 0,
			NVDIMM_IO_ATOMIC);
		अगर (ret)
			जाओ out_map;

		unlock_map(arena, premap);
		nd_region_release_lane(btt->nd_region, lane);

		अगर (e_flag) अणु
			ret = arena_clear_मुक्तlist_error(arena, lane);
			अगर (ret)
				वापस ret;
		पूर्ण

		len -= cur_len;
		off += cur_len;
		sector += btt->sector_size >> SECTOR_SHIFT;
	पूर्ण

	वापस 0;

 out_map:
	unlock_map(arena, premap);
 out_lane:
	nd_region_release_lane(btt->nd_region, lane);
	वापस ret;
पूर्ण

अटल पूर्णांक btt_करो_bvec(काष्ठा btt *btt, काष्ठा bio_पूर्णांकegrity_payload *bip,
			काष्ठा page *page, अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक off,
			अचिन्हित पूर्णांक op, sector_t sector)
अणु
	पूर्णांक ret;

	अगर (!op_is_ग_लिखो(op)) अणु
		ret = btt_पढ़ो_pg(btt, bip, page, off, sector, len);
		flush_dcache_page(page);
	पूर्ण अन्यथा अणु
		flush_dcache_page(page);
		ret = btt_ग_लिखो_pg(btt, bip, sector, page, off, len);
	पूर्ण

	वापस ret;
पूर्ण

अटल blk_qc_t btt_submit_bio(काष्ठा bio *bio)
अणु
	काष्ठा bio_पूर्णांकegrity_payload *bip = bio_पूर्णांकegrity(bio);
	काष्ठा btt *btt = bio->bi_bdev->bd_disk->निजी_data;
	काष्ठा bvec_iter iter;
	अचिन्हित दीर्घ start;
	काष्ठा bio_vec bvec;
	पूर्णांक err = 0;
	bool करो_acct;

	अगर (!bio_पूर्णांकegrity_prep(bio))
		वापस BLK_QC_T_NONE;

	करो_acct = blk_queue_io_stat(bio->bi_bdev->bd_disk->queue);
	अगर (करो_acct)
		start = bio_start_io_acct(bio);
	bio_क्रम_each_segment(bvec, bio, iter) अणु
		अचिन्हित पूर्णांक len = bvec.bv_len;

		अगर (len > PAGE_SIZE || len < btt->sector_size ||
				len % btt->sector_size) अणु
			dev_err_ratelimited(&btt->nd_btt->dev,
				"unaligned bio segment (len: %d)\n", len);
			bio->bi_status = BLK_STS_IOERR;
			अवरोध;
		पूर्ण

		err = btt_करो_bvec(btt, bip, bvec.bv_page, len, bvec.bv_offset,
				  bio_op(bio), iter.bi_sector);
		अगर (err) अणु
			dev_err(&btt->nd_btt->dev,
					"io error in %s sector %lld, len %d,\n",
					(op_is_ग_लिखो(bio_op(bio))) ? "WRITE" :
					"READ",
					(अचिन्हित दीर्घ दीर्घ) iter.bi_sector, len);
			bio->bi_status = त्रुटि_सं_to_blk_status(err);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (करो_acct)
		bio_end_io_acct(bio, start);

	bio_endio(bio);
	वापस BLK_QC_T_NONE;
पूर्ण

अटल पूर्णांक btt_rw_page(काष्ठा block_device *bdev, sector_t sector,
		काष्ठा page *page, अचिन्हित पूर्णांक op)
अणु
	काष्ठा btt *btt = bdev->bd_disk->निजी_data;
	पूर्णांक rc;

	rc = btt_करो_bvec(btt, शून्य, page, thp_size(page), 0, op, sector);
	अगर (rc == 0)
		page_endio(page, op_is_ग_लिखो(op), 0);

	वापस rc;
पूर्ण


अटल पूर्णांक btt_getgeo(काष्ठा block_device *bd, काष्ठा hd_geometry *geo)
अणु
	/* some standard values */
	geo->heads = 1 << 6;
	geo->sectors = 1 << 5;
	geo->cylinders = get_capacity(bd->bd_disk) >> 11;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations btt_fops = अणु
	.owner =		THIS_MODULE,
	.submit_bio =		btt_submit_bio,
	.rw_page =		btt_rw_page,
	.getgeo =		btt_getgeo,
पूर्ण;

अटल पूर्णांक btt_blk_init(काष्ठा btt *btt)
अणु
	काष्ठा nd_btt *nd_btt = btt->nd_btt;
	काष्ठा nd_namespace_common *ndns = nd_btt->ndns;

	/* create a new disk and request queue क्रम btt */
	btt->btt_queue = blk_alloc_queue(NUMA_NO_NODE);
	अगर (!btt->btt_queue)
		वापस -ENOMEM;

	btt->btt_disk = alloc_disk(0);
	अगर (!btt->btt_disk) अणु
		blk_cleanup_queue(btt->btt_queue);
		वापस -ENOMEM;
	पूर्ण

	nvdimm_namespace_disk_name(ndns, btt->btt_disk->disk_name);
	btt->btt_disk->first_minor = 0;
	btt->btt_disk->fops = &btt_fops;
	btt->btt_disk->निजी_data = btt;
	btt->btt_disk->queue = btt->btt_queue;
	btt->btt_disk->flags = GENHD_FL_EXT_DEVT;

	blk_queue_logical_block_size(btt->btt_queue, btt->sector_size);
	blk_queue_max_hw_sectors(btt->btt_queue, अच_पूर्णांक_उच्च);
	blk_queue_flag_set(QUEUE_FLAG_NONROT, btt->btt_queue);

	अगर (btt_meta_size(btt)) अणु
		पूर्णांक rc = nd_पूर्णांकegrity_init(btt->btt_disk, btt_meta_size(btt));

		अगर (rc) अणु
			del_gendisk(btt->btt_disk);
			put_disk(btt->btt_disk);
			blk_cleanup_queue(btt->btt_queue);
			वापस rc;
		पूर्ण
	पूर्ण
	set_capacity(btt->btt_disk, btt->nlba * btt->sector_size >> 9);
	device_add_disk(&btt->nd_btt->dev, btt->btt_disk, शून्य);
	btt->nd_btt->size = btt->nlba * (u64)btt->sector_size;
	nvdimm_check_and_set_ro(btt->btt_disk);

	वापस 0;
पूर्ण

अटल व्योम btt_blk_cleanup(काष्ठा btt *btt)
अणु
	del_gendisk(btt->btt_disk);
	put_disk(btt->btt_disk);
	blk_cleanup_queue(btt->btt_queue);
पूर्ण

/**
 * btt_init - initialize a block translation table क्रम the given device
 * @nd_btt:	device with BTT geometry and backing device info
 * @rawsize:	raw size in bytes of the backing device
 * @lbasize:	lba size of the backing device
 * @uuid:	A uuid क्रम the backing device - this is stored on media
 * @maxlane:	maximum number of parallel requests the device can handle
 *
 * Initialize a Block Translation Table on a backing device to provide
 * single sector घातer fail atomicity.
 *
 * Context:
 * Might sleep.
 *
 * Returns:
 * Poपूर्णांकer to a new काष्ठा btt on success, शून्य on failure.
 */
अटल काष्ठा btt *btt_init(काष्ठा nd_btt *nd_btt, अचिन्हित दीर्घ दीर्घ rawsize,
		u32 lbasize, u8 *uuid, काष्ठा nd_region *nd_region)
अणु
	पूर्णांक ret;
	काष्ठा btt *btt;
	काष्ठा nd_namespace_io *nsio;
	काष्ठा device *dev = &nd_btt->dev;

	btt = devm_kzalloc(dev, माप(काष्ठा btt), GFP_KERNEL);
	अगर (!btt)
		वापस शून्य;

	btt->nd_btt = nd_btt;
	btt->rawsize = rawsize;
	btt->lbasize = lbasize;
	btt->sector_size = ((lbasize >= 4096) ? 4096 : 512);
	INIT_LIST_HEAD(&btt->arena_list);
	mutex_init(&btt->init_lock);
	btt->nd_region = nd_region;
	nsio = to_nd_namespace_io(&nd_btt->ndns->dev);
	btt->phys_bb = &nsio->bb;

	ret = discover_arenas(btt);
	अगर (ret) अणु
		dev_err(dev, "init: error in arena_discover: %d\n", ret);
		वापस शून्य;
	पूर्ण

	अगर (btt->init_state != INIT_READY && nd_region->ro) अणु
		dev_warn(dev, "%s is read-only, unable to init btt metadata\n",
				dev_name(&nd_region->dev));
		वापस शून्य;
	पूर्ण अन्यथा अगर (btt->init_state != INIT_READY) अणु
		btt->num_arenas = (rawsize / ARENA_MAX_SIZE) +
			((rawsize % ARENA_MAX_SIZE) ? 1 : 0);
		dev_dbg(dev, "init: %d arenas for %llu rawsize\n",
				btt->num_arenas, rawsize);

		ret = create_arenas(btt);
		अगर (ret) अणु
			dev_info(dev, "init: create_arenas: %d\n", ret);
			वापस शून्य;
		पूर्ण

		ret = btt_meta_init(btt);
		अगर (ret) अणु
			dev_err(dev, "init: error in meta_init: %d\n", ret);
			वापस शून्य;
		पूर्ण
	पूर्ण

	ret = btt_blk_init(btt);
	अगर (ret) अणु
		dev_err(dev, "init: error in blk_init: %d\n", ret);
		वापस शून्य;
	पूर्ण

	btt_debugfs_init(btt);

	वापस btt;
पूर्ण

/**
 * btt_fini - de-initialize a BTT
 * @btt:	the BTT handle that was generated by btt_init
 *
 * De-initialize a Block Translation Table on device removal
 *
 * Context:
 * Might sleep.
 */
अटल व्योम btt_fini(काष्ठा btt *btt)
अणु
	अगर (btt) अणु
		btt_blk_cleanup(btt);
		मुक्त_arenas(btt);
		debugfs_हटाओ_recursive(btt->debugfs_dir);
	पूर्ण
पूर्ण

पूर्णांक nvdimm_namespace_attach_btt(काष्ठा nd_namespace_common *ndns)
अणु
	काष्ठा nd_btt *nd_btt = to_nd_btt(ndns->claim);
	काष्ठा nd_region *nd_region;
	काष्ठा btt_sb *btt_sb;
	काष्ठा btt *btt;
	माप_प्रकार size, rawsize;
	पूर्णांक rc;

	अगर (!nd_btt->uuid || !nd_btt->ndns || !nd_btt->lbasize) अणु
		dev_dbg(&nd_btt->dev, "incomplete btt configuration\n");
		वापस -ENODEV;
	पूर्ण

	btt_sb = devm_kzalloc(&nd_btt->dev, माप(*btt_sb), GFP_KERNEL);
	अगर (!btt_sb)
		वापस -ENOMEM;

	size = nvdimm_namespace_capacity(ndns);
	rc = devm_namespace_enable(&nd_btt->dev, ndns, size);
	अगर (rc)
		वापस rc;

	/*
	 * If this वापसs < 0, that is ok as it just means there wasn't
	 * an existing BTT, and we're creating a new one. We still need to
	 * call this as we need the version dependent fields in nd_btt to be
	 * set correctly based on the holder class
	 */
	nd_btt_version(nd_btt, ndns, btt_sb);

	rawsize = size - nd_btt->initial_offset;
	अगर (rawsize < ARENA_MIN_SIZE) अणु
		dev_dbg(&nd_btt->dev, "%s must be at least %ld bytes\n",
				dev_name(&ndns->dev),
				ARENA_MIN_SIZE + nd_btt->initial_offset);
		वापस -ENXIO;
	पूर्ण
	nd_region = to_nd_region(nd_btt->dev.parent);
	btt = btt_init(nd_btt, rawsize, nd_btt->lbasize, nd_btt->uuid,
			nd_region);
	अगर (!btt)
		वापस -ENOMEM;
	nd_btt->btt = btt;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nvdimm_namespace_attach_btt);

पूर्णांक nvdimm_namespace_detach_btt(काष्ठा nd_btt *nd_btt)
अणु
	काष्ठा btt *btt = nd_btt->btt;

	btt_fini(btt);
	nd_btt->btt = शून्य;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(nvdimm_namespace_detach_btt);

अटल पूर्णांक __init nd_btt_init(व्योम)
अणु
	पूर्णांक rc = 0;

	debugfs_root = debugfs_create_dir("btt", शून्य);
	अगर (IS_ERR_OR_शून्य(debugfs_root))
		rc = -ENXIO;

	वापस rc;
पूर्ण

अटल व्योम __निकास nd_btt_निकास(व्योम)
अणु
	debugfs_हटाओ_recursive(debugfs_root);
पूर्ण

MODULE_ALIAS_ND_DEVICE(ND_DEVICE_BTT);
MODULE_AUTHOR("Vishal Verma <vishal.l.verma@linux.intel.com>");
MODULE_LICENSE("GPL v2");
module_init(nd_btt_init);
module_निकास(nd_btt_निकास);
