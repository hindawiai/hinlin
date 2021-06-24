<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/adfs/map.c
 *
 *  Copyright (C) 1997-2002 Russell King
 */
#समावेश <linux/slab.h>
#समावेश <linux/statfs.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "adfs.h"

/*
 * The ADFS map is basically a set of sectors.  Each sector is called a
 * zone which contains a bitstream made up of variable sized fragments.
 * Each bit refers to a set of bytes in the fileप्रणाली, defined by
 * log2bpmb.  This may be larger or smaller than the sector size, but
 * the overall size it describes will always be a round number of
 * sectors.  A fragment id is always idlen bits दीर्घ.
 *
 *  < idlen > <       n        > <1>
 * +---------+-------//---------+---+
 * | frag id |  0000....000000  | 1 |
 * +---------+-------//---------+---+
 *
 * The physical disk space used by a fragment is taken from the start of
 * the fragment id up to and including the '1' bit - ie, idlen + n + 1
 * bits.
 *
 * A fragment id can be repeated multiple बार in the whole map क्रम
 * large or fragmented files.  The first map zone a fragment starts in
 * is given by fragment id / ids_per_zone - this allows objects to start
 * from any zone on the disk.
 *
 * Free space is described by a linked list of fragments.  Each मुक्त
 * fragment describes मुक्त space in the same way as the other fragments,
 * however, the frag id specअगरies an offset (in map bits) from the end
 * of this fragment to the start of the next मुक्त fragment.
 *
 * Objects stored on the disk are allocated object ids (we use these as
 * our inode numbers.)  Object ids contain a fragment id and an optional
 * offset.  This allows a directory fragment to contain small files
 * associated with that directory.
 */

/*
 * For the future...
 */
अटल DEFINE_RWLOCK(adfs_map_lock);

/*
 * This is fun.  We need to load up to 19 bits from the map at an
 * arbitrary bit alignment.  (We're limited to 19 bits by F+ version 2).
 */
#घोषणा GET_FRAG_ID(_map,_start,_idmask)				\
	(अणु								\
		अचिन्हित अक्षर *_m = _map + (_start >> 3);		\
		u32 _frag = get_unaligned_le32(_m);			\
		_frag >>= (_start & 7);					\
		_frag & _idmask;					\
	पूर्ण)

/*
 * वापस the map bit offset of the fragment frag_id in the zone dm.
 * Note that the loop is optimised क्रम best यंत्र code - look at the
 * output of:
 *  gcc -D__KERNEL__ -O2 -I../../include -o - -S map.c
 */
अटल पूर्णांक lookup_zone(स्थिर काष्ठा adfs_discmap *dm, स्थिर अचिन्हित पूर्णांक idlen,
		       स्थिर u32 frag_id, अचिन्हित पूर्णांक *offset)
अणु
	स्थिर अचिन्हित पूर्णांक endbit = dm->dm_endbit;
	स्थिर u32 idmask = (1 << idlen) - 1;
	अचिन्हित अक्षर *map = dm->dm_bh->b_data;
	अचिन्हित पूर्णांक start = dm->dm_startbit;
	अचिन्हित पूर्णांक मुक्तlink, fragend;
	u32 frag;

	frag = GET_FRAG_ID(map, 8, idmask & 0x7fff);
	मुक्तlink = frag ? 8 + frag : 0;

	करो अणु
		frag = GET_FRAG_ID(map, start, idmask);

		fragend = find_next_bit_le(map, endbit, start + idlen);
		अगर (fragend >= endbit)
			जाओ error;

		अगर (start == मुक्तlink) अणु
			मुक्तlink += frag & 0x7fff;
		पूर्ण अन्यथा अगर (frag == frag_id) अणु
			अचिन्हित पूर्णांक length = fragend + 1 - start;

			अगर (*offset < length)
				वापस start + *offset;
			*offset -= length;
		पूर्ण

		start = fragend + 1;
	पूर्ण जबतक (start < endbit);
	वापस -1;

error:
	prपूर्णांकk(KERN_ERR "adfs: oversized fragment 0x%x at 0x%x-0x%x\n",
		frag, start, fragend);
	वापस -1;
पूर्ण

/*
 * Scan the मुक्त space map, क्रम this zone, calculating the total
 * number of map bits in each मुक्त space fragment.
 *
 * Note: idmask is limited to 15 bits [3.2]
 */
अटल अचिन्हित पूर्णांक
scan_मुक्त_map(काष्ठा adfs_sb_info *asb, काष्ठा adfs_discmap *dm)
अणु
	स्थिर अचिन्हित पूर्णांक endbit = dm->dm_endbit;
	स्थिर अचिन्हित पूर्णांक idlen  = asb->s_idlen;
	स्थिर अचिन्हित पूर्णांक frag_idlen = idlen <= 15 ? idlen : 15;
	स्थिर u32 idmask = (1 << frag_idlen) - 1;
	अचिन्हित अक्षर *map = dm->dm_bh->b_data;
	अचिन्हित पूर्णांक start = 8, fragend;
	u32 frag;
	अचिन्हित दीर्घ total = 0;

	/*
	 * get fragment id
	 */
	frag = GET_FRAG_ID(map, start, idmask);

	/*
	 * If the मुक्तlink is null, then no मुक्त fragments
	 * exist in this zone.
	 */
	अगर (frag == 0)
		वापस 0;

	करो अणु
		start += frag;

		frag = GET_FRAG_ID(map, start, idmask);

		fragend = find_next_bit_le(map, endbit, start + idlen);
		अगर (fragend >= endbit)
			जाओ error;

		total += fragend + 1 - start;
	पूर्ण जबतक (frag >= idlen + 1);

	अगर (frag != 0)
		prपूर्णांकk(KERN_ERR "adfs: undersized free fragment\n");

	वापस total;
error:
	prपूर्णांकk(KERN_ERR "adfs: oversized free fragment\n");
	वापस 0;
पूर्ण

अटल पूर्णांक scan_map(काष्ठा adfs_sb_info *asb, अचिन्हित पूर्णांक zone,
		    स्थिर u32 frag_id, अचिन्हित पूर्णांक mapoff)
अणु
	स्थिर अचिन्हित पूर्णांक idlen = asb->s_idlen;
	काष्ठा adfs_discmap *dm, *dm_end;
	पूर्णांक result;

	dm	= asb->s_map + zone;
	zone	= asb->s_map_size;
	dm_end	= asb->s_map + zone;

	करो अणु
		result = lookup_zone(dm, idlen, frag_id, &mapoff);

		अगर (result != -1)
			जाओ found;

		dm ++;
		अगर (dm == dm_end)
			dm = asb->s_map;
	पूर्ण जबतक (--zone > 0);

	वापस -1;
found:
	result -= dm->dm_startbit;
	result += dm->dm_startblk;

	वापस result;
पूर्ण

/*
 * calculate the amount of मुक्त blocks in the map.
 *
 *              n=1
 *  total_मुक्त = E(मुक्त_in_zone_n)
 *              nzones
 */
व्योम adfs_map_statfs(काष्ठा super_block *sb, काष्ठा kstatfs *buf)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);
	काष्ठा adfs_discrecord *dr = adfs_map_discrecord(asb->s_map);
	काष्ठा adfs_discmap *dm;
	अचिन्हित पूर्णांक total = 0;
	अचिन्हित पूर्णांक zone;

	dm   = asb->s_map;
	zone = asb->s_map_size;

	करो अणु
		total += scan_मुक्त_map(asb, dm++);
	पूर्ण जबतक (--zone > 0);

	buf->f_blocks  = adfs_disc_size(dr) >> sb->s_blocksize_bits;
	buf->f_files   = asb->s_ids_per_zone * asb->s_map_size;
	buf->f_bavail  =
	buf->f_bमुक्त   = चिन्हित_asl(total, asb->s_map2blk);
पूर्ण

पूर्णांक adfs_map_lookup(काष्ठा super_block *sb, u32 frag_id, अचिन्हित पूर्णांक offset)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);
	अचिन्हित पूर्णांक zone, mapoff;
	पूर्णांक result;

	/*
	 * map & root fragment is special - it starts in the center of the
	 * disk.  The other fragments start at zone (frag / ids_per_zone)
	 */
	अगर (frag_id == ADFS_ROOT_FRAG)
		zone = asb->s_map_size >> 1;
	अन्यथा
		zone = frag_id / asb->s_ids_per_zone;

	अगर (zone >= asb->s_map_size)
		जाओ bad_fragment;

	/* Convert sector offset to map offset */
	mapoff = चिन्हित_asl(offset, -asb->s_map2blk);

	पढ़ो_lock(&adfs_map_lock);
	result = scan_map(asb, zone, frag_id, mapoff);
	पढ़ो_unlock(&adfs_map_lock);

	अगर (result > 0) अणु
		अचिन्हित पूर्णांक secoff;

		/* Calculate sector offset पूर्णांकo map block */
		secoff = offset - चिन्हित_asl(mapoff, asb->s_map2blk);
		वापस secoff + चिन्हित_asl(result, asb->s_map2blk);
	पूर्ण

	adfs_error(sb, "fragment 0x%04x at offset %d not found in map",
		   frag_id, offset);
	वापस 0;

bad_fragment:
	adfs_error(sb, "invalid fragment 0x%04x (zone = %d, max = %d)",
		   frag_id, zone, asb->s_map_size);
	वापस 0;
पूर्ण

अटल अचिन्हित अक्षर adfs_calczonecheck(काष्ठा super_block *sb, अचिन्हित अक्षर *map)
अणु
	अचिन्हित पूर्णांक v0, v1, v2, v3;
	पूर्णांक i;

	v0 = v1 = v2 = v3 = 0;
	क्रम (i = sb->s_blocksize - 4; i; i -= 4) अणु
		v0 += map[i]     + (v3 >> 8);
		v3 &= 0xff;
		v1 += map[i + 1] + (v0 >> 8);
		v0 &= 0xff;
		v2 += map[i + 2] + (v1 >> 8);
		v1 &= 0xff;
		v3 += map[i + 3] + (v2 >> 8);
		v2 &= 0xff;
	पूर्ण
	v0 +=           v3 >> 8;
	v1 += map[1] + (v0 >> 8);
	v2 += map[2] + (v1 >> 8);
	v3 += map[3] + (v2 >> 8);

	वापस v0 ^ v1 ^ v2 ^ v3;
पूर्ण

अटल पूर्णांक adfs_checkmap(काष्ठा super_block *sb, काष्ठा adfs_discmap *dm)
अणु
	अचिन्हित अक्षर crosscheck = 0, zonecheck = 1;
	पूर्णांक i;

	क्रम (i = 0; i < ADFS_SB(sb)->s_map_size; i++) अणु
		अचिन्हित अक्षर *map;

		map = dm[i].dm_bh->b_data;

		अगर (adfs_calczonecheck(sb, map) != map[0]) अणु
			adfs_error(sb, "zone %d fails zonecheck", i);
			zonecheck = 0;
		पूर्ण
		crosscheck ^= map[3];
	पूर्ण
	अगर (crosscheck != 0xff)
		adfs_error(sb, "crosscheck != 0xff");
	वापस crosscheck == 0xff && zonecheck;
पूर्ण

/*
 * Layout the map - the first zone contains a copy of the disc record,
 * and the last zone must be limited to the size of the fileप्रणाली.
 */
अटल व्योम adfs_map_layout(काष्ठा adfs_discmap *dm, अचिन्हित पूर्णांक nzones,
			    काष्ठा adfs_discrecord *dr)
अणु
	अचिन्हित पूर्णांक zone, zone_size;
	u64 size;

	zone_size = (8 << dr->log2secsize) - le16_to_cpu(dr->zone_spare);

	dm[0].dm_bh       = शून्य;
	dm[0].dm_startblk = 0;
	dm[0].dm_startbit = 32 + ADFS_DR_SIZE_BITS;
	dm[0].dm_endbit   = 32 + zone_size;

	क्रम (zone = 1; zone < nzones; zone++) अणु
		dm[zone].dm_bh       = शून्य;
		dm[zone].dm_startblk = zone * zone_size - ADFS_DR_SIZE_BITS;
		dm[zone].dm_startbit = 32;
		dm[zone].dm_endbit   = 32 + zone_size;
	पूर्ण

	size = adfs_disc_size(dr) >> dr->log2bpmb;
	size -= (nzones - 1) * zone_size - ADFS_DR_SIZE_BITS;
	dm[nzones - 1].dm_endbit = 32 + size;
पूर्ण

अटल पूर्णांक adfs_map_पढ़ो(काष्ठा adfs_discmap *dm, काष्ठा super_block *sb,
			 अचिन्हित पूर्णांक map_addr, अचिन्हित पूर्णांक nzones)
अणु
	अचिन्हित पूर्णांक zone;

	क्रम (zone = 0; zone < nzones; zone++) अणु
		dm[zone].dm_bh = sb_bपढ़ो(sb, map_addr + zone);
		अगर (!dm[zone].dm_bh)
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम adfs_map_rअन्यथा(काष्ठा adfs_discmap *dm, अचिन्हित पूर्णांक nzones)
अणु
	अचिन्हित पूर्णांक zone;

	क्रम (zone = 0; zone < nzones; zone++)
		brअन्यथा(dm[zone].dm_bh);
पूर्ण

काष्ठा adfs_discmap *adfs_पढ़ो_map(काष्ठा super_block *sb, काष्ठा adfs_discrecord *dr)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);
	काष्ठा adfs_discmap *dm;
	अचिन्हित पूर्णांक map_addr, zone_size, nzones;
	पूर्णांक ret;

	nzones    = dr->nzones | dr->nzones_high << 8;
	zone_size = (8 << dr->log2secsize) - le16_to_cpu(dr->zone_spare);

	asb->s_idlen = dr->idlen;
	asb->s_map_size = nzones;
	asb->s_map2blk = dr->log2bpmb - dr->log2secsize;
	asb->s_log2sharesize = dr->log2sharesize;
	asb->s_ids_per_zone = zone_size / (asb->s_idlen + 1);

	map_addr = (nzones >> 1) * zone_size -
		     ((nzones > 1) ? ADFS_DR_SIZE_BITS : 0);
	map_addr = चिन्हित_asl(map_addr, asb->s_map2blk);

	dm = kदो_स्मृति_array(nzones, माप(*dm), GFP_KERNEL);
	अगर (dm == शून्य) अणु
		adfs_error(sb, "not enough memory");
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	adfs_map_layout(dm, nzones, dr);

	ret = adfs_map_पढ़ो(dm, sb, map_addr, nzones);
	अगर (ret) अणु
		adfs_error(sb, "unable to read map");
		जाओ error_मुक्त;
	पूर्ण

	अगर (adfs_checkmap(sb, dm))
		वापस dm;

	adfs_error(sb, "map corrupted");

error_मुक्त:
	adfs_map_rअन्यथा(dm, nzones);
	kमुक्त(dm);
	वापस ERR_PTR(-EIO);
पूर्ण

व्योम adfs_मुक्त_map(काष्ठा super_block *sb)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);

	adfs_map_rअन्यथा(asb->s_map, asb->s_map_size);
	kमुक्त(asb->s_map);
पूर्ण
