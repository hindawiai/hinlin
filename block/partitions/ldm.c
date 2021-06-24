<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/**
 * ldm - Support क्रम Winकरोws Logical Disk Manager (Dynamic Disks)
 *
 * Copyright (C) 2001,2002 Riअक्षरd Russon <ldm@flatcap.org>
 * Copyright (c) 2001-2012 Anton Altaparmakov
 * Copyright (C) 2001,2002 Jakob Kemi <jakob.kemi@telia.com>
 *
 * Documentation is available at http://www.linux-ntfs.org/करोku.php?id=करोwnloads 
 */

#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/kernel.h>
#समावेश <linux/uuid.h>
#समावेश <linux/msकरोs_partition.h>

#समावेश "ldm.h"
#समावेश "check.h"

/*
 * ldm_debug/info/error/crit - Output an error message
 * @f:    A म_लिखो क्रमmat string containing the message
 * @...:  Variables to substitute पूर्णांकo @f
 *
 * ldm_debug() ग_लिखोs a DEBUG level message to the syslog but only अगर the
 * driver was compiled with debug enabled. Otherwise, the call turns पूर्णांकo a NOP.
 */
#अगर_अघोषित CONFIG_LDM_DEBUG
#घोषणा ldm_debug(...)	करो अणुपूर्ण जबतक (0)
#अन्यथा
#घोषणा ldm_debug(f, a...) _ldm_prपूर्णांकk (KERN_DEBUG, __func__, f, ##a)
#पूर्ण_अगर

#घोषणा ldm_crit(f, a...)  _ldm_prपूर्णांकk (KERN_CRIT,  __func__, f, ##a)
#घोषणा ldm_error(f, a...) _ldm_prपूर्णांकk (KERN_ERR,   __func__, f, ##a)
#घोषणा ldm_info(f, a...)  _ldm_prपूर्णांकk (KERN_INFO,  __func__, f, ##a)

अटल __म_लिखो(3, 4)
व्योम _ldm_prपूर्णांकk(स्थिर अक्षर *level, स्थिर अक्षर *function, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा va_क्रमmat vaf;
	बहु_सूची args;

	बहु_शुरू (args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	prपूर्णांकk("%s%s(): %pV\n", level, function, &vaf);

	बहु_पूर्ण(args);
पूर्ण

/**
 * ldm_parse_privhead - Read the LDM Database PRIVHEAD काष्ठाure
 * @data:  Raw database PRIVHEAD काष्ठाure loaded from the device
 * @ph:    In-memory privhead काष्ठाure in which to वापस parsed inक्रमmation
 *
 * This parses the LDM database PRIVHEAD काष्ठाure supplied in @data and
 * sets up the in-memory privhead काष्ठाure @ph with the obtained inक्रमmation.
 *
 * Return:  'true'   @ph contains the PRIVHEAD data
 *          'false'  @ph contents are undefined
 */
अटल bool ldm_parse_privhead(स्थिर u8 *data, काष्ठा privhead *ph)
अणु
	bool is_vista = false;

	BUG_ON(!data || !ph);
	अगर (MAGIC_PRIVHEAD != get_unaligned_be64(data)) अणु
		ldm_error("Cannot find PRIVHEAD structure. LDM database is"
			" corrupt. Aborting.");
		वापस false;
	पूर्ण
	ph->ver_major = get_unaligned_be16(data + 0x000C);
	ph->ver_minor = get_unaligned_be16(data + 0x000E);
	ph->logical_disk_start = get_unaligned_be64(data + 0x011B);
	ph->logical_disk_size = get_unaligned_be64(data + 0x0123);
	ph->config_start = get_unaligned_be64(data + 0x012B);
	ph->config_size = get_unaligned_be64(data + 0x0133);
	/* Version 2.11 is Win2k/XP and version 2.12 is Vista. */
	अगर (ph->ver_major == 2 && ph->ver_minor == 12)
		is_vista = true;
	अगर (!is_vista && (ph->ver_major != 2 || ph->ver_minor != 11)) अणु
		ldm_error("Expected PRIVHEAD version 2.11 or 2.12, got %d.%d."
			" Aborting.", ph->ver_major, ph->ver_minor);
		वापस false;
	पूर्ण
	ldm_debug("PRIVHEAD version %d.%d (Windows %s).", ph->ver_major,
			ph->ver_minor, is_vista ? "Vista" : "2000/XP");
	अगर (ph->config_size != LDM_DB_SIZE) अणु	/* 1 MiB in sectors. */
		/* Warn the user and जारी, carefully. */
		ldm_info("Database is normally %u bytes, it claims to "
			"be %llu bytes.", LDM_DB_SIZE,
			(अचिन्हित दीर्घ दीर्घ)ph->config_size);
	पूर्ण
	अगर ((ph->logical_disk_size == 0) || (ph->logical_disk_start +
			ph->logical_disk_size > ph->config_start)) अणु
		ldm_error("PRIVHEAD disk size doesn't match real disk size");
		वापस false;
	पूर्ण
	अगर (uuid_parse(data + 0x0030, &ph->disk_id)) अणु
		ldm_error("PRIVHEAD contains an invalid GUID.");
		वापस false;
	पूर्ण
	ldm_debug("Parsed PRIVHEAD successfully.");
	वापस true;
पूर्ण

/**
 * ldm_parse_tocblock - Read the LDM Database TOCBLOCK काष्ठाure
 * @data:  Raw database TOCBLOCK काष्ठाure loaded from the device
 * @toc:   In-memory toc काष्ठाure in which to वापस parsed inक्रमmation
 *
 * This parses the LDM Database TOCBLOCK (table of contents) काष्ठाure supplied
 * in @data and sets up the in-memory tocblock काष्ठाure @toc with the obtained
 * inक्रमmation.
 *
 * N.B.  The *_start and *_size values वापसed in @toc are not range-checked.
 *
 * Return:  'true'   @toc contains the TOCBLOCK data
 *          'false'  @toc contents are undefined
 */
अटल bool ldm_parse_tocblock (स्थिर u8 *data, काष्ठा tocblock *toc)
अणु
	BUG_ON (!data || !toc);

	अगर (MAGIC_TOCBLOCK != get_unaligned_be64(data)) अणु
		ldm_crit ("Cannot find TOCBLOCK, database may be corrupt.");
		वापस false;
	पूर्ण
	म_नकलन (toc->biपंचांगap1_name, data + 0x24, माप (toc->biपंचांगap1_name));
	toc->biपंचांगap1_name[माप (toc->biपंचांगap1_name) - 1] = 0;
	toc->biपंचांगap1_start = get_unaligned_be64(data + 0x2E);
	toc->biपंचांगap1_size  = get_unaligned_be64(data + 0x36);

	अगर (म_भेदन (toc->biपंचांगap1_name, TOC_BITMAP1,
			माप (toc->biपंचांगap1_name)) != 0) अणु
		ldm_crit ("TOCBLOCK's first bitmap is '%s', should be '%s'.",
				TOC_BITMAP1, toc->biपंचांगap1_name);
		वापस false;
	पूर्ण
	म_नकलन (toc->biपंचांगap2_name, data + 0x46, माप (toc->biपंचांगap2_name));
	toc->biपंचांगap2_name[माप (toc->biपंचांगap2_name) - 1] = 0;
	toc->biपंचांगap2_start = get_unaligned_be64(data + 0x50);
	toc->biपंचांगap2_size  = get_unaligned_be64(data + 0x58);
	अगर (म_भेदन (toc->biपंचांगap2_name, TOC_BITMAP2,
			माप (toc->biपंचांगap2_name)) != 0) अणु
		ldm_crit ("TOCBLOCK's second bitmap is '%s', should be '%s'.",
				TOC_BITMAP2, toc->biपंचांगap2_name);
		वापस false;
	पूर्ण
	ldm_debug ("Parsed TOCBLOCK successfully.");
	वापस true;
पूर्ण

/**
 * ldm_parse_vmdb - Read the LDM Database VMDB काष्ठाure
 * @data:  Raw database VMDB काष्ठाure loaded from the device
 * @vm:    In-memory vmdb काष्ठाure in which to वापस parsed inक्रमmation
 *
 * This parses the LDM Database VMDB काष्ठाure supplied in @data and sets up
 * the in-memory vmdb काष्ठाure @vm with the obtained inक्रमmation.
 *
 * N.B.  The *_start, *_size and *_seq values will be range-checked later.
 *
 * Return:  'true'   @vm contains VMDB info
 *          'false'  @vm contents are undefined
 */
अटल bool ldm_parse_vmdb (स्थिर u8 *data, काष्ठा vmdb *vm)
अणु
	BUG_ON (!data || !vm);

	अगर (MAGIC_VMDB != get_unaligned_be32(data)) अणु
		ldm_crit ("Cannot find the VMDB, database may be corrupt.");
		वापस false;
	पूर्ण

	vm->ver_major = get_unaligned_be16(data + 0x12);
	vm->ver_minor = get_unaligned_be16(data + 0x14);
	अगर ((vm->ver_major != 4) || (vm->ver_minor != 10)) अणु
		ldm_error ("Expected VMDB version %d.%d, got %d.%d. "
			"Aborting.", 4, 10, vm->ver_major, vm->ver_minor);
		वापस false;
	पूर्ण

	vm->vblk_size     = get_unaligned_be32(data + 0x08);
	अगर (vm->vblk_size == 0) अणु
		ldm_error ("Illegal VBLK size");
		वापस false;
	पूर्ण

	vm->vblk_offset   = get_unaligned_be32(data + 0x0C);
	vm->last_vblk_seq = get_unaligned_be32(data + 0x04);

	ldm_debug ("Parsed VMDB successfully.");
	वापस true;
पूर्ण

/**
 * ldm_compare_privheads - Compare two privhead objects
 * @ph1:  First privhead
 * @ph2:  Second privhead
 *
 * This compares the two privhead काष्ठाures @ph1 and @ph2.
 *
 * Return:  'true'   Identical
 *          'false'  Dअगरferent
 */
अटल bool ldm_compare_privheads (स्थिर काष्ठा privhead *ph1,
				   स्थिर काष्ठा privhead *ph2)
अणु
	BUG_ON (!ph1 || !ph2);

	वापस ((ph1->ver_major          == ph2->ver_major)		&&
		(ph1->ver_minor          == ph2->ver_minor)		&&
		(ph1->logical_disk_start == ph2->logical_disk_start)	&&
		(ph1->logical_disk_size  == ph2->logical_disk_size)	&&
		(ph1->config_start       == ph2->config_start)		&&
		(ph1->config_size        == ph2->config_size)		&&
		uuid_equal(&ph1->disk_id, &ph2->disk_id));
पूर्ण

/**
 * ldm_compare_tocblocks - Compare two tocblock objects
 * @toc1:  First toc
 * @toc2:  Second toc
 *
 * This compares the two tocblock काष्ठाures @toc1 and @toc2.
 *
 * Return:  'true'   Identical
 *          'false'  Dअगरferent
 */
अटल bool ldm_compare_tocblocks (स्थिर काष्ठा tocblock *toc1,
				   स्थिर काष्ठा tocblock *toc2)
अणु
	BUG_ON (!toc1 || !toc2);

	वापस ((toc1->biपंचांगap1_start == toc2->biपंचांगap1_start)	&&
		(toc1->biपंचांगap1_size  == toc2->biपंचांगap1_size)	&&
		(toc1->biपंचांगap2_start == toc2->biपंचांगap2_start)	&&
		(toc1->biपंचांगap2_size  == toc2->biपंचांगap2_size)	&&
		!म_भेदन (toc1->biपंचांगap1_name, toc2->biपंचांगap1_name,
			माप (toc1->biपंचांगap1_name))		&&
		!म_भेदन (toc1->biपंचांगap2_name, toc2->biपंचांगap2_name,
			माप (toc1->biपंचांगap2_name)));
पूर्ण

/**
 * ldm_validate_privheads - Compare the primary privhead with its backups
 * @state: Partition check state including device holding the LDM Database
 * @ph1:   Memory काष्ठा to fill with ph contents
 *
 * Read and compare all three privheads from disk.
 *
 * The privheads on disk show the size and location of the मुख्य disk area and
 * the configuration area (the database).  The values are range-checked against
 * @hd, which contains the real size of the disk.
 *
 * Return:  'true'   Success
 *          'false'  Error
 */
अटल bool ldm_validate_privheads(काष्ठा parsed_partitions *state,
				   काष्ठा privhead *ph1)
अणु
	अटल स्थिर पूर्णांक off[3] = अणु OFF_PRIV1, OFF_PRIV2, OFF_PRIV3 पूर्ण;
	काष्ठा privhead *ph[3] = अणु ph1 पूर्ण;
	Sector sect;
	u8 *data;
	bool result = false;
	दीर्घ num_sects;
	पूर्णांक i;

	BUG_ON (!state || !ph1);

	ph[1] = kदो_स्मृति (माप (*ph[1]), GFP_KERNEL);
	ph[2] = kदो_स्मृति (माप (*ph[2]), GFP_KERNEL);
	अगर (!ph[1] || !ph[2]) अणु
		ldm_crit ("Out of memory.");
		जाओ out;
	पूर्ण

	/* off[1 & 2] are relative to ph[0]->config_start */
	ph[0]->config_start = 0;

	/* Read and parse privheads */
	क्रम (i = 0; i < 3; i++) अणु
		data = पढ़ो_part_sector(state, ph[0]->config_start + off[i],
					&sect);
		अगर (!data) अणु
			ldm_crit ("Disk read failed.");
			जाओ out;
		पूर्ण
		result = ldm_parse_privhead (data, ph[i]);
		put_dev_sector (sect);
		अगर (!result) अणु
			ldm_error ("Cannot find PRIVHEAD %d.", i+1); /* Log again */
			अगर (i < 2)
				जाओ out;	/* Alपढ़ोy logged */
			अन्यथा
				अवरोध;	/* FIXME ignore क्रम now, 3rd PH can fail on odd-sized disks */
		पूर्ण
	पूर्ण

	num_sects = state->bdev->bd_inode->i_size >> 9;

	अगर ((ph[0]->config_start > num_sects) ||
	   ((ph[0]->config_start + ph[0]->config_size) > num_sects)) अणु
		ldm_crit ("Database extends beyond the end of the disk.");
		जाओ out;
	पूर्ण

	अगर ((ph[0]->logical_disk_start > ph[0]->config_start) ||
	   ((ph[0]->logical_disk_start + ph[0]->logical_disk_size)
		    > ph[0]->config_start)) अणु
		ldm_crit ("Disk and database overlap.");
		जाओ out;
	पूर्ण

	अगर (!ldm_compare_privheads (ph[0], ph[1])) अणु
		ldm_crit ("Primary and backup PRIVHEADs don't match.");
		जाओ out;
	पूर्ण
	/* FIXME ignore this क्रम now
	अगर (!ldm_compare_privheads (ph[0], ph[2])) अणु
		ldm_crit ("Primary and backup PRIVHEADs don't match.");
		जाओ out;
	पूर्ण*/
	ldm_debug ("Validated PRIVHEADs successfully.");
	result = true;
out:
	kमुक्त (ph[1]);
	kमुक्त (ph[2]);
	वापस result;
पूर्ण

/**
 * ldm_validate_tocblocks - Validate the table of contents and its backups
 * @state: Partition check state including device holding the LDM Database
 * @base:  Offset, पूर्णांकo @state->bdev, of the database
 * @ldb:   Cache of the database काष्ठाures
 *
 * Find and compare the four tables of contents of the LDM Database stored on
 * @state->bdev and वापस the parsed inक्रमmation पूर्णांकo @toc1.
 *
 * The offsets and sizes of the configs are range-checked against a privhead.
 *
 * Return:  'true'   @toc1 contains validated TOCBLOCK info
 *          'false'  @toc1 contents are undefined
 */
अटल bool ldm_validate_tocblocks(काष्ठा parsed_partitions *state,
				   अचिन्हित दीर्घ base, काष्ठा ldmdb *ldb)
अणु
	अटल स्थिर पूर्णांक off[4] = अणु OFF_TOCB1, OFF_TOCB2, OFF_TOCB3, OFF_TOCB4पूर्ण;
	काष्ठा tocblock *tb[4];
	काष्ठा privhead *ph;
	Sector sect;
	u8 *data;
	पूर्णांक i, nr_tbs;
	bool result = false;

	BUG_ON(!state || !ldb);
	ph = &ldb->ph;
	tb[0] = &ldb->toc;
	tb[1] = kदो_स्मृति_array(3, माप(*tb[1]), GFP_KERNEL);
	अगर (!tb[1]) अणु
		ldm_crit("Out of memory.");
		जाओ err;
	पूर्ण
	tb[2] = (काष्ठा tocblock*)((u8*)tb[1] + माप(*tb[1]));
	tb[3] = (काष्ठा tocblock*)((u8*)tb[2] + माप(*tb[2]));
	/*
	 * Try to पढ़ो and parse all four TOCBLOCKs.
	 *
	 * Winकरोws Vista LDM v2.12 करोes not always have all four TOCBLOCKs so
	 * skip any that fail as दीर्घ as we get at least one valid TOCBLOCK.
	 */
	क्रम (nr_tbs = i = 0; i < 4; i++) अणु
		data = पढ़ो_part_sector(state, base + off[i], &sect);
		अगर (!data) अणु
			ldm_error("Disk read failed for TOCBLOCK %d.", i);
			जारी;
		पूर्ण
		अगर (ldm_parse_tocblock(data, tb[nr_tbs]))
			nr_tbs++;
		put_dev_sector(sect);
	पूर्ण
	अगर (!nr_tbs) अणु
		ldm_crit("Failed to find a valid TOCBLOCK.");
		जाओ err;
	पूर्ण
	/* Range check the TOCBLOCK against a privhead. */
	अगर (((tb[0]->biपंचांगap1_start + tb[0]->biपंचांगap1_size) > ph->config_size) ||
			((tb[0]->biपंचांगap2_start + tb[0]->biपंचांगap2_size) >
			ph->config_size)) अणु
		ldm_crit("The bitmaps are out of range.  Giving up.");
		जाओ err;
	पूर्ण
	/* Compare all loaded TOCBLOCKs. */
	क्रम (i = 1; i < nr_tbs; i++) अणु
		अगर (!ldm_compare_tocblocks(tb[0], tb[i])) अणु
			ldm_crit("TOCBLOCKs 0 and %d do not match.", i);
			जाओ err;
		पूर्ण
	पूर्ण
	ldm_debug("Validated %d TOCBLOCKs successfully.", nr_tbs);
	result = true;
err:
	kमुक्त(tb[1]);
	वापस result;
पूर्ण

/**
 * ldm_validate_vmdb - Read the VMDB and validate it
 * @state: Partition check state including device holding the LDM Database
 * @base:  Offset, पूर्णांकo @bdev, of the database
 * @ldb:   Cache of the database काष्ठाures
 *
 * Find the vmdb of the LDM Database stored on @bdev and वापस the parsed
 * inक्रमmation in @ldb.
 *
 * Return:  'true'   @ldb contains validated VBDB info
 *          'false'  @ldb contents are undefined
 */
अटल bool ldm_validate_vmdb(काष्ठा parsed_partitions *state,
			      अचिन्हित दीर्घ base, काष्ठा ldmdb *ldb)
अणु
	Sector sect;
	u8 *data;
	bool result = false;
	काष्ठा vmdb *vm;
	काष्ठा tocblock *toc;

	BUG_ON (!state || !ldb);

	vm  = &ldb->vm;
	toc = &ldb->toc;

	data = पढ़ो_part_sector(state, base + OFF_VMDB, &sect);
	अगर (!data) अणु
		ldm_crit ("Disk read failed.");
		वापस false;
	पूर्ण

	अगर (!ldm_parse_vmdb (data, vm))
		जाओ out;				/* Alपढ़ोy logged */

	/* Are there uncommitted transactions? */
	अगर (get_unaligned_be16(data + 0x10) != 0x01) अणु
		ldm_crit ("Database is not in a consistent state.  Aborting.");
		जाओ out;
	पूर्ण

	अगर (vm->vblk_offset != 512)
		ldm_info ("VBLKs start at offset 0x%04x.", vm->vblk_offset);

	/*
	 * The last_vblkd_seq can be beक्रमe the end of the vmdb, just make sure
	 * it is not out of bounds.
	 */
	अगर ((vm->vblk_size * vm->last_vblk_seq) > (toc->biपंचांगap1_size << 9)) अणु
		ldm_crit ("VMDB exceeds allowed size specified by TOCBLOCK.  "
				"Database is corrupt.  Aborting.");
		जाओ out;
	पूर्ण

	result = true;
out:
	put_dev_sector (sect);
	वापस result;
पूर्ण


/**
 * ldm_validate_partition_table - Determine whether bdev might be a dynamic disk
 * @state: Partition check state including device holding the LDM Database
 *
 * This function provides a weak test to decide whether the device is a dynamic
 * disk or not.  It looks क्रम an MS-DOS-style partition table containing at
 * least one partition of type 0x42 (क्रमmerly SFS, now used by Winकरोws क्रम
 * dynamic disks).
 *
 * N.B.  The only possible error can come from the पढ़ो_part_sector and that is
 *       only likely to happen अगर the underlying device is strange.  If that IS
 *       the हाल we should वापस zero to let someone अन्यथा try.
 *
 * Return:  'true'   @state->bdev is a dynamic disk
 *          'false'  @state->bdev is not a dynamic disk, or an error occurred
 */
अटल bool ldm_validate_partition_table(काष्ठा parsed_partitions *state)
अणु
	Sector sect;
	u8 *data;
	काष्ठा msकरोs_partition *p;
	पूर्णांक i;
	bool result = false;

	BUG_ON(!state);

	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data) अणु
		ldm_info ("Disk read failed.");
		वापस false;
	पूर्ण

	अगर (*(__le16*) (data + 0x01FE) != cpu_to_le16 (MSDOS_LABEL_MAGIC))
		जाओ out;

	p = (काष्ठा msकरोs_partition *)(data + 0x01BE);
	क्रम (i = 0; i < 4; i++, p++)
		अगर (SYS_IND (p) == LDM_PARTITION) अणु
			result = true;
			अवरोध;
		पूर्ण

	अगर (result)
		ldm_debug ("Found W2K dynamic disk partition type.");

out:
	put_dev_sector (sect);
	वापस result;
पूर्ण

/**
 * ldm_get_disk_objid - Search a linked list of vblk's क्रम a given Disk Id
 * @ldb:  Cache of the database काष्ठाures
 *
 * The LDM Database contains a list of all partitions on all dynamic disks.
 * The primary PRIVHEAD, at the beginning of the physical disk, tells us
 * the GUID of this disk.  This function searches क्रम the GUID in a linked
 * list of vblk's.
 *
 * Return:  Poपूर्णांकer, A matching vblk was found
 *          शून्य,    No match, or an error
 */
अटल काष्ठा vblk * ldm_get_disk_objid (स्थिर काष्ठा ldmdb *ldb)
अणु
	काष्ठा list_head *item;

	BUG_ON (!ldb);

	list_क्रम_each (item, &ldb->v_disk) अणु
		काष्ठा vblk *v = list_entry (item, काष्ठा vblk, list);
		अगर (uuid_equal(&v->vblk.disk.disk_id, &ldb->ph.disk_id))
			वापस v;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ldm_create_data_partitions - Create data partitions क्रम this device
 * @pp:   List of the partitions parsed so far
 * @ldb:  Cache of the database काष्ठाures
 *
 * The database contains ALL the partitions क्रम ALL disk groups, so we need to
 * filter out this specअगरic disk. Using the disk's object id, we can find all
 * the partitions in the database that beदीर्घ to this disk.
 *
 * Add each partition in our database, to the parsed_partitions काष्ठाure.
 *
 * N.B.  This function creates the partitions in the order it finds partition
 *       objects in the linked list.
 *
 * Return:  'true'   Partition created
 *          'false'  Error, probably a range checking problem
 */
अटल bool ldm_create_data_partitions (काष्ठा parsed_partitions *pp,
					स्थिर काष्ठा ldmdb *ldb)
अणु
	काष्ठा list_head *item;
	काष्ठा vblk *vb;
	काष्ठा vblk *disk;
	काष्ठा vblk_part *part;
	पूर्णांक part_num = 1;

	BUG_ON (!pp || !ldb);

	disk = ldm_get_disk_objid (ldb);
	अगर (!disk) अणु
		ldm_crit ("Can't find the ID of this disk in the database.");
		वापस false;
	पूर्ण

	strlcat(pp->pp_buf, " [LDM]", PAGE_SIZE);

	/* Create the data partitions */
	list_क्रम_each (item, &ldb->v_part) अणु
		vb = list_entry (item, काष्ठा vblk, list);
		part = &vb->vblk.part;

		अगर (part->disk_id != disk->obj_id)
			जारी;

		put_partition (pp, part_num, ldb->ph.logical_disk_start +
				part->start, part->size);
		part_num++;
	पूर्ण

	strlcat(pp->pp_buf, "\n", PAGE_SIZE);
	वापस true;
पूर्ण


/**
 * ldm_relative - Calculate the next relative offset
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @base:    Size of the previous fixed width fields
 * @offset:  Cumulative size of the previous variable-width fields
 *
 * Because many of the VBLK fields are variable-width, it's necessary
 * to calculate each offset based on the previous one and the length
 * of the field it poपूर्णांकed to.
 *
 * Return:  -1 Error, the calculated offset exceeded the size of the buffer
 *           n OK, a range-checked offset पूर्णांकo buffer
 */
अटल पूर्णांक ldm_relative(स्थिर u8 *buffer, पूर्णांक buflen, पूर्णांक base, पूर्णांक offset)
अणु

	base += offset;
	अगर (!buffer || offset < 0 || base > buflen) अणु
		अगर (!buffer)
			ldm_error("!buffer");
		अगर (offset < 0)
			ldm_error("offset (%d) < 0", offset);
		अगर (base > buflen)
			ldm_error("base (%d) > buflen (%d)", base, buflen);
		वापस -1;
	पूर्ण
	अगर (base + buffer[base] >= buflen) अणु
		ldm_error("base (%d) + buffer[base] (%d) >= buflen (%d)", base,
				buffer[base], buflen);
		वापस -1;
	पूर्ण
	वापस buffer[base] + offset + 1;
पूर्ण

/**
 * ldm_get_vnum - Convert a variable-width, big endian number, पूर्णांकo cpu order
 * @block:  Poपूर्णांकer to the variable-width number to convert
 *
 * Large numbers in the LDM Database are often stored in a packed क्रमmat.  Each
 * number is prefixed by a one byte width marker.  All numbers in the database
 * are stored in big-endian byte order.  This function पढ़ोs one of these
 * numbers and वापसs the result
 *
 * N.B.  This function DOES NOT perक्रमm any range checking, though the most
 *       it will पढ़ो is eight bytes.
 *
 * Return:  n A number
 *          0 Zero, or an error occurred
 */
अटल u64 ldm_get_vnum (स्थिर u8 *block)
अणु
	u64 पंचांगp = 0;
	u8 length;

	BUG_ON (!block);

	length = *block++;

	अगर (length && length <= 8)
		जबतक (length--)
			पंचांगp = (पंचांगp << 8) | *block++;
	अन्यथा
		ldm_error ("Illegal length %d.", length);

	वापस पंचांगp;
पूर्ण

/**
 * ldm_get_vstr - Read a length-prefixed string पूर्णांकo a buffer
 * @block:   Poपूर्णांकer to the length marker
 * @buffer:  Location to copy string to
 * @buflen:  Size of the output buffer
 *
 * Many of the strings in the LDM Database are not शून्य terminated.  Instead
 * they are prefixed by a one byte length marker.  This function copies one of
 * these strings पूर्णांकo a buffer.
 *
 * N.B.  This function DOES NOT perक्रमm any range checking on the input.
 *       If the buffer is too small, the output will be truncated.
 *
 * Return:  0, Error and @buffer contents are undefined
 *          n, String length in अक्षरacters (excluding शून्य)
 *          buflen-1, String was truncated.
 */
अटल पूर्णांक ldm_get_vstr (स्थिर u8 *block, u8 *buffer, पूर्णांक buflen)
अणु
	पूर्णांक length;

	BUG_ON (!block || !buffer);

	length = block[0];
	अगर (length >= buflen) अणु
		ldm_error ("Truncating string %d -> %d.", length, buflen);
		length = buflen - 1;
	पूर्ण
	स_नकल (buffer, block + 1, length);
	buffer[length] = 0;
	वापस length;
पूर्ण


/**
 * ldm_parse_cmp3 - Read a raw VBLK Component object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Component object (version 3) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Component VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_cmp3 (स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	पूर्णांक r_objid, r_name, r_vstate, r_child, r_parent, r_stripe, r_cols, len;
	काष्ठा vblk_comp *comp;

	BUG_ON (!buffer || !vb);

	r_objid  = ldm_relative (buffer, buflen, 0x18, 0);
	r_name   = ldm_relative (buffer, buflen, 0x18, r_objid);
	r_vstate = ldm_relative (buffer, buflen, 0x18, r_name);
	r_child  = ldm_relative (buffer, buflen, 0x1D, r_vstate);
	r_parent = ldm_relative (buffer, buflen, 0x2D, r_child);

	अगर (buffer[0x12] & VBLK_FLAG_COMP_STRIPE) अणु
		r_stripe = ldm_relative (buffer, buflen, 0x2E, r_parent);
		r_cols   = ldm_relative (buffer, buflen, 0x2E, r_stripe);
		len = r_cols;
	पूर्ण अन्यथा अणु
		r_stripe = 0;
		r_cols   = 0;
		len = r_parent;
	पूर्ण
	अगर (len < 0)
		वापस false;

	len += VBLK_SIZE_CMP3;
	अगर (len != get_unaligned_be32(buffer + 0x14))
		वापस false;

	comp = &vb->vblk.comp;
	ldm_get_vstr (buffer + 0x18 + r_name, comp->state,
		माप (comp->state));
	comp->type      = buffer[0x18 + r_vstate];
	comp->children  = ldm_get_vnum (buffer + 0x1D + r_vstate);
	comp->parent_id = ldm_get_vnum (buffer + 0x2D + r_child);
	comp->chunksize = r_stripe ? ldm_get_vnum (buffer+r_parent+0x2E) : 0;

	वापस true;
पूर्ण

/**
 * ldm_parse_dgr3 - Read a raw VBLK Disk Group object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Disk Group object (version 3) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Disk Group VBLK
 *          'false'  @vb contents are not defined
 */
अटल पूर्णांक ldm_parse_dgr3 (स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	पूर्णांक r_objid, r_name, r_diskid, r_id1, r_id2, len;
	काष्ठा vblk_dgrp *dgrp;

	BUG_ON (!buffer || !vb);

	r_objid  = ldm_relative (buffer, buflen, 0x18, 0);
	r_name   = ldm_relative (buffer, buflen, 0x18, r_objid);
	r_diskid = ldm_relative (buffer, buflen, 0x18, r_name);

	अगर (buffer[0x12] & VBLK_FLAG_DGR3_IDS) अणु
		r_id1 = ldm_relative (buffer, buflen, 0x24, r_diskid);
		r_id2 = ldm_relative (buffer, buflen, 0x24, r_id1);
		len = r_id2;
	पूर्ण अन्यथा अणु
		r_id1 = 0;
		r_id2 = 0;
		len = r_diskid;
	पूर्ण
	अगर (len < 0)
		वापस false;

	len += VBLK_SIZE_DGR3;
	अगर (len != get_unaligned_be32(buffer + 0x14))
		वापस false;

	dgrp = &vb->vblk.dgrp;
	ldm_get_vstr (buffer + 0x18 + r_name, dgrp->disk_id,
		माप (dgrp->disk_id));
	वापस true;
पूर्ण

/**
 * ldm_parse_dgr4 - Read a raw VBLK Disk Group object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Disk Group object (version 4) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Disk Group VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_dgr4 (स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	अक्षर buf[64];
	पूर्णांक r_objid, r_name, r_id1, r_id2, len;

	BUG_ON (!buffer || !vb);

	r_objid  = ldm_relative (buffer, buflen, 0x18, 0);
	r_name   = ldm_relative (buffer, buflen, 0x18, r_objid);

	अगर (buffer[0x12] & VBLK_FLAG_DGR4_IDS) अणु
		r_id1 = ldm_relative (buffer, buflen, 0x44, r_name);
		r_id2 = ldm_relative (buffer, buflen, 0x44, r_id1);
		len = r_id2;
	पूर्ण अन्यथा अणु
		r_id1 = 0;
		r_id2 = 0;
		len = r_name;
	पूर्ण
	अगर (len < 0)
		वापस false;

	len += VBLK_SIZE_DGR4;
	अगर (len != get_unaligned_be32(buffer + 0x14))
		वापस false;

	ldm_get_vstr (buffer + 0x18 + r_objid, buf, माप (buf));
	वापस true;
पूर्ण

/**
 * ldm_parse_dsk3 - Read a raw VBLK Disk object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Disk object (version 3) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Disk VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_dsk3 (स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	पूर्णांक r_objid, r_name, r_diskid, r_altname, len;
	काष्ठा vblk_disk *disk;

	BUG_ON (!buffer || !vb);

	r_objid   = ldm_relative (buffer, buflen, 0x18, 0);
	r_name    = ldm_relative (buffer, buflen, 0x18, r_objid);
	r_diskid  = ldm_relative (buffer, buflen, 0x18, r_name);
	r_altname = ldm_relative (buffer, buflen, 0x18, r_diskid);
	len = r_altname;
	अगर (len < 0)
		वापस false;

	len += VBLK_SIZE_DSK3;
	अगर (len != get_unaligned_be32(buffer + 0x14))
		वापस false;

	disk = &vb->vblk.disk;
	ldm_get_vstr (buffer + 0x18 + r_diskid, disk->alt_name,
		माप (disk->alt_name));
	अगर (uuid_parse(buffer + 0x19 + r_name, &disk->disk_id))
		वापस false;

	वापस true;
पूर्ण

/**
 * ldm_parse_dsk4 - Read a raw VBLK Disk object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Disk object (version 4) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Disk VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_dsk4 (स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	पूर्णांक r_objid, r_name, len;
	काष्ठा vblk_disk *disk;

	BUG_ON (!buffer || !vb);

	r_objid = ldm_relative (buffer, buflen, 0x18, 0);
	r_name  = ldm_relative (buffer, buflen, 0x18, r_objid);
	len     = r_name;
	अगर (len < 0)
		वापस false;

	len += VBLK_SIZE_DSK4;
	अगर (len != get_unaligned_be32(buffer + 0x14))
		वापस false;

	disk = &vb->vblk.disk;
	import_uuid(&disk->disk_id, buffer + 0x18 + r_name);
	वापस true;
पूर्ण

/**
 * ldm_parse_prt3 - Read a raw VBLK Partition object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Partition object (version 3) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Partition VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_prt3(स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	पूर्णांक r_objid, r_name, r_size, r_parent, r_diskid, r_index, len;
	काष्ठा vblk_part *part;

	BUG_ON(!buffer || !vb);
	r_objid = ldm_relative(buffer, buflen, 0x18, 0);
	अगर (r_objid < 0) अणु
		ldm_error("r_objid %d < 0", r_objid);
		वापस false;
	पूर्ण
	r_name = ldm_relative(buffer, buflen, 0x18, r_objid);
	अगर (r_name < 0) अणु
		ldm_error("r_name %d < 0", r_name);
		वापस false;
	पूर्ण
	r_size = ldm_relative(buffer, buflen, 0x34, r_name);
	अगर (r_size < 0) अणु
		ldm_error("r_size %d < 0", r_size);
		वापस false;
	पूर्ण
	r_parent = ldm_relative(buffer, buflen, 0x34, r_size);
	अगर (r_parent < 0) अणु
		ldm_error("r_parent %d < 0", r_parent);
		वापस false;
	पूर्ण
	r_diskid = ldm_relative(buffer, buflen, 0x34, r_parent);
	अगर (r_diskid < 0) अणु
		ldm_error("r_diskid %d < 0", r_diskid);
		वापस false;
	पूर्ण
	अगर (buffer[0x12] & VBLK_FLAG_PART_INDEX) अणु
		r_index = ldm_relative(buffer, buflen, 0x34, r_diskid);
		अगर (r_index < 0) अणु
			ldm_error("r_index %d < 0", r_index);
			वापस false;
		पूर्ण
		len = r_index;
	पूर्ण अन्यथा अणु
		r_index = 0;
		len = r_diskid;
	पूर्ण
	अगर (len < 0) अणु
		ldm_error("len %d < 0", len);
		वापस false;
	पूर्ण
	len += VBLK_SIZE_PRT3;
	अगर (len > get_unaligned_be32(buffer + 0x14)) अणु
		ldm_error("len %d > BE32(buffer + 0x14) %d", len,
				get_unaligned_be32(buffer + 0x14));
		वापस false;
	पूर्ण
	part = &vb->vblk.part;
	part->start = get_unaligned_be64(buffer + 0x24 + r_name);
	part->volume_offset = get_unaligned_be64(buffer + 0x2C + r_name);
	part->size = ldm_get_vnum(buffer + 0x34 + r_name);
	part->parent_id = ldm_get_vnum(buffer + 0x34 + r_size);
	part->disk_id = ldm_get_vnum(buffer + 0x34 + r_parent);
	अगर (vb->flags & VBLK_FLAG_PART_INDEX)
		part->partnum = buffer[0x35 + r_diskid];
	अन्यथा
		part->partnum = 0;
	वापस true;
पूर्ण

/**
 * ldm_parse_vol5 - Read a raw VBLK Volume object पूर्णांकo a vblk काष्ठाure
 * @buffer:  Block of data being worked on
 * @buflen:  Size of the block of data
 * @vb:      In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK Volume object (version 5) पूर्णांकo a vblk काष्ठाure.
 *
 * Return:  'true'   @vb contains a Volume VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_vol5(स्थिर u8 *buffer, पूर्णांक buflen, काष्ठा vblk *vb)
अणु
	पूर्णांक r_objid, r_name, r_vtype, r_disable_drive_letter, r_child, r_size;
	पूर्णांक r_id1, r_id2, r_size2, r_drive, len;
	काष्ठा vblk_volu *volu;

	BUG_ON(!buffer || !vb);
	r_objid = ldm_relative(buffer, buflen, 0x18, 0);
	अगर (r_objid < 0) अणु
		ldm_error("r_objid %d < 0", r_objid);
		वापस false;
	पूर्ण
	r_name = ldm_relative(buffer, buflen, 0x18, r_objid);
	अगर (r_name < 0) अणु
		ldm_error("r_name %d < 0", r_name);
		वापस false;
	पूर्ण
	r_vtype = ldm_relative(buffer, buflen, 0x18, r_name);
	अगर (r_vtype < 0) अणु
		ldm_error("r_vtype %d < 0", r_vtype);
		वापस false;
	पूर्ण
	r_disable_drive_letter = ldm_relative(buffer, buflen, 0x18, r_vtype);
	अगर (r_disable_drive_letter < 0) अणु
		ldm_error("r_disable_drive_letter %d < 0",
				r_disable_drive_letter);
		वापस false;
	पूर्ण
	r_child = ldm_relative(buffer, buflen, 0x2D, r_disable_drive_letter);
	अगर (r_child < 0) अणु
		ldm_error("r_child %d < 0", r_child);
		वापस false;
	पूर्ण
	r_size = ldm_relative(buffer, buflen, 0x3D, r_child);
	अगर (r_size < 0) अणु
		ldm_error("r_size %d < 0", r_size);
		वापस false;
	पूर्ण
	अगर (buffer[0x12] & VBLK_FLAG_VOLU_ID1) अणु
		r_id1 = ldm_relative(buffer, buflen, 0x52, r_size);
		अगर (r_id1 < 0) अणु
			ldm_error("r_id1 %d < 0", r_id1);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा
		r_id1 = r_size;
	अगर (buffer[0x12] & VBLK_FLAG_VOLU_ID2) अणु
		r_id2 = ldm_relative(buffer, buflen, 0x52, r_id1);
		अगर (r_id2 < 0) अणु
			ldm_error("r_id2 %d < 0", r_id2);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा
		r_id2 = r_id1;
	अगर (buffer[0x12] & VBLK_FLAG_VOLU_SIZE) अणु
		r_size2 = ldm_relative(buffer, buflen, 0x52, r_id2);
		अगर (r_size2 < 0) अणु
			ldm_error("r_size2 %d < 0", r_size2);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा
		r_size2 = r_id2;
	अगर (buffer[0x12] & VBLK_FLAG_VOLU_DRIVE) अणु
		r_drive = ldm_relative(buffer, buflen, 0x52, r_size2);
		अगर (r_drive < 0) अणु
			ldm_error("r_drive %d < 0", r_drive);
			वापस false;
		पूर्ण
	पूर्ण अन्यथा
		r_drive = r_size2;
	len = r_drive;
	अगर (len < 0) अणु
		ldm_error("len %d < 0", len);
		वापस false;
	पूर्ण
	len += VBLK_SIZE_VOL5;
	अगर (len > get_unaligned_be32(buffer + 0x14)) अणु
		ldm_error("len %d > BE32(buffer + 0x14) %d", len,
				get_unaligned_be32(buffer + 0x14));
		वापस false;
	पूर्ण
	volu = &vb->vblk.volu;
	ldm_get_vstr(buffer + 0x18 + r_name, volu->volume_type,
			माप(volu->volume_type));
	स_नकल(volu->volume_state, buffer + 0x18 + r_disable_drive_letter,
			माप(volu->volume_state));
	volu->size = ldm_get_vnum(buffer + 0x3D + r_child);
	volu->partition_type = buffer[0x41 + r_size];
	स_नकल(volu->guid, buffer + 0x42 + r_size, माप(volu->guid));
	अगर (buffer[0x12] & VBLK_FLAG_VOLU_DRIVE) अणु
		ldm_get_vstr(buffer + 0x52 + r_size, volu->drive_hपूर्णांक,
				माप(volu->drive_hपूर्णांक));
	पूर्ण
	वापस true;
पूर्ण

/**
 * ldm_parse_vblk - Read a raw VBLK object पूर्णांकo a vblk काष्ठाure
 * @buf:  Block of data being worked on
 * @len:  Size of the block of data
 * @vb:   In-memory vblk in which to वापस inक्रमmation
 *
 * Read a raw VBLK object पूर्णांकo a vblk काष्ठाure.  This function just पढ़ोs the
 * inक्रमmation common to all VBLK types, then delegates the rest of the work to
 * helper functions: ldm_parse_*.
 *
 * Return:  'true'   @vb contains a VBLK
 *          'false'  @vb contents are not defined
 */
अटल bool ldm_parse_vblk (स्थिर u8 *buf, पूर्णांक len, काष्ठा vblk *vb)
अणु
	bool result = false;
	पूर्णांक r_objid;

	BUG_ON (!buf || !vb);

	r_objid = ldm_relative (buf, len, 0x18, 0);
	अगर (r_objid < 0) अणु
		ldm_error ("VBLK header is corrupt.");
		वापस false;
	पूर्ण

	vb->flags  = buf[0x12];
	vb->type   = buf[0x13];
	vb->obj_id = ldm_get_vnum (buf + 0x18);
	ldm_get_vstr (buf+0x18+r_objid, vb->name, माप (vb->name));

	चयन (vb->type) अणु
		हाल VBLK_CMP3:  result = ldm_parse_cmp3 (buf, len, vb); अवरोध;
		हाल VBLK_DSK3:  result = ldm_parse_dsk3 (buf, len, vb); अवरोध;
		हाल VBLK_DSK4:  result = ldm_parse_dsk4 (buf, len, vb); अवरोध;
		हाल VBLK_DGR3:  result = ldm_parse_dgr3 (buf, len, vb); अवरोध;
		हाल VBLK_DGR4:  result = ldm_parse_dgr4 (buf, len, vb); अवरोध;
		हाल VBLK_PRT3:  result = ldm_parse_prt3 (buf, len, vb); अवरोध;
		हाल VBLK_VOL5:  result = ldm_parse_vol5 (buf, len, vb); अवरोध;
	पूर्ण

	अगर (result)
		ldm_debug ("Parsed VBLK 0x%llx (type: 0x%02x) ok.",
			 (अचिन्हित दीर्घ दीर्घ) vb->obj_id, vb->type);
	अन्यथा
		ldm_error ("Failed to parse VBLK 0x%llx (type: 0x%02x).",
			(अचिन्हित दीर्घ दीर्घ) vb->obj_id, vb->type);

	वापस result;
पूर्ण


/**
 * ldm_ldmdb_add - Adds a raw VBLK entry to the ldmdb database
 * @data:  Raw VBLK to add to the database
 * @len:   Size of the raw VBLK
 * @ldb:   Cache of the database काष्ठाures
 *
 * The VBLKs are sorted पूर्णांकo categories.  Partitions are also sorted by offset.
 *
 * N.B.  This function करोes not check the validity of the VBLKs.
 *
 * Return:  'true'   The VBLK was added
 *          'false'  An error occurred
 */
अटल bool ldm_ldmdb_add (u8 *data, पूर्णांक len, काष्ठा ldmdb *ldb)
अणु
	काष्ठा vblk *vb;
	काष्ठा list_head *item;

	BUG_ON (!data || !ldb);

	vb = kदो_स्मृति (माप (*vb), GFP_KERNEL);
	अगर (!vb) अणु
		ldm_crit ("Out of memory.");
		वापस false;
	पूर्ण

	अगर (!ldm_parse_vblk (data, len, vb)) अणु
		kमुक्त(vb);
		वापस false;			/* Alपढ़ोy logged */
	पूर्ण

	/* Put vblk पूर्णांकo the correct list. */
	चयन (vb->type) अणु
	हाल VBLK_DGR3:
	हाल VBLK_DGR4:
		list_add (&vb->list, &ldb->v_dgrp);
		अवरोध;
	हाल VBLK_DSK3:
	हाल VBLK_DSK4:
		list_add (&vb->list, &ldb->v_disk);
		अवरोध;
	हाल VBLK_VOL5:
		list_add (&vb->list, &ldb->v_volu);
		अवरोध;
	हाल VBLK_CMP3:
		list_add (&vb->list, &ldb->v_comp);
		अवरोध;
	हाल VBLK_PRT3:
		/* Sort by the partition's start sector. */
		list_क्रम_each (item, &ldb->v_part) अणु
			काष्ठा vblk *v = list_entry (item, काष्ठा vblk, list);
			अगर ((v->vblk.part.disk_id == vb->vblk.part.disk_id) &&
			    (v->vblk.part.start > vb->vblk.part.start)) अणु
				list_add_tail (&vb->list, &v->list);
				वापस true;
			पूर्ण
		पूर्ण
		list_add_tail (&vb->list, &ldb->v_part);
		अवरोध;
	पूर्ण
	वापस true;
पूर्ण

/**
 * ldm_frag_add - Add a VBLK fragment to a list
 * @data:   Raw fragment to be added to the list
 * @size:   Size of the raw fragment
 * @frags:  Linked list of VBLK fragments
 *
 * Fragmented VBLKs may not be consecutive in the database, so they are placed
 * in a list so they can be pieced together later.
 *
 * Return:  'true'   Success, the VBLK was added to the list
 *          'false'  Error, a problem occurred
 */
अटल bool ldm_frag_add (स्थिर u8 *data, पूर्णांक size, काष्ठा list_head *frags)
अणु
	काष्ठा frag *f;
	काष्ठा list_head *item;
	पूर्णांक rec, num, group;

	BUG_ON (!data || !frags);

	अगर (size < 2 * VBLK_SIZE_HEAD) अणु
		ldm_error("Value of size is too small.");
		वापस false;
	पूर्ण

	group = get_unaligned_be32(data + 0x08);
	rec   = get_unaligned_be16(data + 0x0C);
	num   = get_unaligned_be16(data + 0x0E);
	अगर ((num < 1) || (num > 4)) अणु
		ldm_error ("A VBLK claims to have %d parts.", num);
		वापस false;
	पूर्ण
	अगर (rec >= num) अणु
		ldm_error("REC value (%d) exceeds NUM value (%d)", rec, num);
		वापस false;
	पूर्ण

	list_क्रम_each (item, frags) अणु
		f = list_entry (item, काष्ठा frag, list);
		अगर (f->group == group)
			जाओ found;
	पूर्ण

	f = kदो_स्मृति (माप (*f) + size*num, GFP_KERNEL);
	अगर (!f) अणु
		ldm_crit ("Out of memory.");
		वापस false;
	पूर्ण

	f->group = group;
	f->num   = num;
	f->rec   = rec;
	f->map   = 0xFF << num;

	list_add_tail (&f->list, frags);
found:
	अगर (rec >= f->num) अणु
		ldm_error("REC value (%d) exceeds NUM value (%d)", rec, f->num);
		वापस false;
	पूर्ण
	अगर (f->map & (1 << rec)) अणु
		ldm_error ("Duplicate VBLK, part %d.", rec);
		f->map &= 0x7F;			/* Mark the group as broken */
		वापस false;
	पूर्ण
	f->map |= (1 << rec);
	अगर (!rec)
		स_नकल(f->data, data, VBLK_SIZE_HEAD);
	data += VBLK_SIZE_HEAD;
	size -= VBLK_SIZE_HEAD;
	स_नकल(f->data + VBLK_SIZE_HEAD + rec * size, data, size);
	वापस true;
पूर्ण

/**
 * ldm_frag_मुक्त - Free a linked list of VBLK fragments
 * @list:  Linked list of fragments
 *
 * Free a linked list of VBLK fragments
 *
 * Return:  none
 */
अटल व्योम ldm_frag_मुक्त (काष्ठा list_head *list)
अणु
	काष्ठा list_head *item, *पंचांगp;

	BUG_ON (!list);

	list_क्रम_each_safe (item, पंचांगp, list)
		kमुक्त (list_entry (item, काष्ठा frag, list));
पूर्ण

/**
 * ldm_frag_commit - Validate fragmented VBLKs and add them to the database
 * @frags:  Linked list of VBLK fragments
 * @ldb:    Cache of the database काष्ठाures
 *
 * Now that all the fragmented VBLKs have been collected, they must be added to
 * the database क्रम later use.
 *
 * Return:  'true'   All the fragments we added successfully
 *          'false'  One or more of the fragments we invalid
 */
अटल bool ldm_frag_commit (काष्ठा list_head *frags, काष्ठा ldmdb *ldb)
अणु
	काष्ठा frag *f;
	काष्ठा list_head *item;

	BUG_ON (!frags || !ldb);

	list_क्रम_each (item, frags) अणु
		f = list_entry (item, काष्ठा frag, list);

		अगर (f->map != 0xFF) अणु
			ldm_error ("VBLK group %d is incomplete (0x%02x).",
				f->group, f->map);
			वापस false;
		पूर्ण

		अगर (!ldm_ldmdb_add (f->data, f->num*ldb->vm.vblk_size, ldb))
			वापस false;		/* Alपढ़ोy logged */
	पूर्ण
	वापस true;
पूर्ण

/**
 * ldm_get_vblks - Read the on-disk database of VBLKs पूर्णांकo memory
 * @state: Partition check state including device holding the LDM Database
 * @base:  Offset, पूर्णांकo @state->bdev, of the database
 * @ldb:   Cache of the database काष्ठाures
 *
 * To use the inक्रमmation from the VBLKs, they need to be पढ़ो from the disk,
 * unpacked and validated.  We cache them in @ldb according to their type.
 *
 * Return:  'true'   All the VBLKs were पढ़ो successfully
 *          'false'  An error occurred
 */
अटल bool ldm_get_vblks(काष्ठा parsed_partitions *state, अचिन्हित दीर्घ base,
			  काष्ठा ldmdb *ldb)
अणु
	पूर्णांक size, perbuf, skip, finish, s, v, recs;
	u8 *data = शून्य;
	Sector sect;
	bool result = false;
	LIST_HEAD (frags);

	BUG_ON(!state || !ldb);

	size   = ldb->vm.vblk_size;
	perbuf = 512 / size;
	skip   = ldb->vm.vblk_offset >> 9;		/* Bytes to sectors */
	finish = (size * ldb->vm.last_vblk_seq) >> 9;

	क्रम (s = skip; s < finish; s++) अणु		/* For each sector */
		data = पढ़ो_part_sector(state, base + OFF_VMDB + s, &sect);
		अगर (!data) अणु
			ldm_crit ("Disk read failed.");
			जाओ out;
		पूर्ण

		क्रम (v = 0; v < perbuf; v++, data+=size) अणु  /* For each vblk */
			अगर (MAGIC_VBLK != get_unaligned_be32(data)) अणु
				ldm_error ("Expected to find a VBLK.");
				जाओ out;
			पूर्ण

			recs = get_unaligned_be16(data + 0x0E);	/* Number of records */
			अगर (recs == 1) अणु
				अगर (!ldm_ldmdb_add (data, size, ldb))
					जाओ out;	/* Alपढ़ोy logged */
			पूर्ण अन्यथा अगर (recs > 1) अणु
				अगर (!ldm_frag_add (data, size, &frags))
					जाओ out;	/* Alपढ़ोy logged */
			पूर्ण
			/* अन्यथा Record is not in use, ignore it. */
		पूर्ण
		put_dev_sector (sect);
		data = शून्य;
	पूर्ण

	result = ldm_frag_commit (&frags, ldb);	/* Failures, alपढ़ोy logged */
out:
	अगर (data)
		put_dev_sector (sect);
	ldm_frag_मुक्त (&frags);

	वापस result;
पूर्ण

/**
 * ldm_मुक्त_vblks - Free a linked list of vblk's
 * @lh:  Head of a linked list of काष्ठा vblk
 *
 * Free a list of vblk's and मुक्त the memory used to मुख्यtain the list.
 *
 * Return:  none
 */
अटल व्योम ldm_मुक्त_vblks (काष्ठा list_head *lh)
अणु
	काष्ठा list_head *item, *पंचांगp;

	BUG_ON (!lh);

	list_क्रम_each_safe (item, पंचांगp, lh)
		kमुक्त (list_entry (item, काष्ठा vblk, list));
पूर्ण


/**
 * ldm_partition - Find out whether a device is a dynamic disk and handle it
 * @state: Partition check state including device holding the LDM Database
 *
 * This determines whether the device @bdev is a dynamic disk and अगर so creates
 * the partitions necessary in the gendisk काष्ठाure poपूर्णांकed to by @hd.
 *
 * We create a dummy device 1, which contains the LDM database, and then create
 * each partition described by the LDM database in sequence as devices 2+. For
 * example, अगर the device is hda, we would have: hda1: LDM database, hda2, hda3,
 * and so on: the actual data containing partitions.
 *
 * Return:  1 Success, @state->bdev is a dynamic disk and we handled it
 *          0 Success, @state->bdev is not a dynamic disk
 *         -1 An error occurred beक्रमe enough inक्रमmation had been पढ़ो
 *            Or @state->bdev is a dynamic disk, but it may be corrupted
 */
पूर्णांक ldm_partition(काष्ठा parsed_partitions *state)
अणु
	काष्ठा ldmdb  *ldb;
	अचिन्हित दीर्घ base;
	पूर्णांक result = -1;

	BUG_ON(!state);

	/* Look क्रम signs of a Dynamic Disk */
	अगर (!ldm_validate_partition_table(state))
		वापस 0;

	ldb = kदो_स्मृति (माप (*ldb), GFP_KERNEL);
	अगर (!ldb) अणु
		ldm_crit ("Out of memory.");
		जाओ out;
	पूर्ण

	/* Parse and check privheads. */
	अगर (!ldm_validate_privheads(state, &ldb->ph))
		जाओ out;		/* Alपढ़ोy logged */

	/* All further references are relative to base (database start). */
	base = ldb->ph.config_start;

	/* Parse and check tocs and vmdb. */
	अगर (!ldm_validate_tocblocks(state, base, ldb) ||
	    !ldm_validate_vmdb(state, base, ldb))
	    	जाओ out;		/* Alपढ़ोy logged */

	/* Initialize vblk lists in ldmdb काष्ठा */
	INIT_LIST_HEAD (&ldb->v_dgrp);
	INIT_LIST_HEAD (&ldb->v_disk);
	INIT_LIST_HEAD (&ldb->v_volu);
	INIT_LIST_HEAD (&ldb->v_comp);
	INIT_LIST_HEAD (&ldb->v_part);

	अगर (!ldm_get_vblks(state, base, ldb)) अणु
		ldm_crit ("Failed to read the VBLKs from the database.");
		जाओ cleanup;
	पूर्ण

	/* Finally, create the data partition devices. */
	अगर (ldm_create_data_partitions(state, ldb)) अणु
		ldm_debug ("Parsed LDM database successfully.");
		result = 1;
	पूर्ण
	/* अन्यथा Alपढ़ोy logged */

cleanup:
	ldm_मुक्त_vblks (&ldb->v_dgrp);
	ldm_मुक्त_vblks (&ldb->v_disk);
	ldm_मुक्त_vblks (&ldb->v_volu);
	ldm_मुक्त_vblks (&ldb->v_comp);
	ldm_मुक्त_vblks (&ldb->v_part);
out:
	kमुक्त (ldb);
	वापस result;
पूर्ण
