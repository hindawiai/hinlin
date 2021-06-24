<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (c) 1996-2000 Russell King.
 *
 *  Scan ADFS partitions on hard disk drives.  Unक्रमtunately, there
 *  isn't a standard क्रम partitioning drives on Acorn machines, so
 *  every single manufacturer of SCSI and IDE cards created their own
 *  method.
 */
#समावेश <linux/buffer_head.h>
#समावेश <linux/adfs_fs.h>

#समावेश "check.h"

/*
 * Partition types. (Oh क्रम reusability)
 */
#घोषणा PARTITION_RISCIX_MFM	1
#घोषणा PARTITION_RISCIX_SCSI	2
#घोषणा PARTITION_LINUX		9

#अगर defined(CONFIG_ACORN_PARTITION_CUMANA) || \
	defined(CONFIG_ACORN_PARTITION_ADFS)
अटल काष्ठा adfs_discrecord *
adfs_partition(काष्ठा parsed_partitions *state, अक्षर *name, अक्षर *data,
	       अचिन्हित दीर्घ first_sector, पूर्णांक slot)
अणु
	काष्ठा adfs_discrecord *dr;
	अचिन्हित पूर्णांक nr_sects;

	अगर (adfs_checkbblk(data))
		वापस शून्य;

	dr = (काष्ठा adfs_discrecord *)(data + 0x1c0);

	अगर (dr->disc_size == 0 && dr->disc_size_high == 0)
		वापस शून्य;

	nr_sects = (le32_to_cpu(dr->disc_size_high) << 23) |
		   (le32_to_cpu(dr->disc_size) >> 9);

	अगर (name) अणु
		strlcat(state->pp_buf, " [", PAGE_SIZE);
		strlcat(state->pp_buf, name, PAGE_SIZE);
		strlcat(state->pp_buf, "]", PAGE_SIZE);
	पूर्ण
	put_partition(state, slot, first_sector, nr_sects);
	वापस dr;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACORN_PARTITION_RISCIX

काष्ठा riscix_part अणु
	__le32	start;
	__le32	length;
	__le32	one;
	अक्षर	name[16];
पूर्ण;

काष्ठा riscix_record अणु
	__le32	magic;
#घोषणा RISCIX_MAGIC	cpu_to_le32(0x4a657320)
	__le32	date;
	काष्ठा riscix_part part[8];
पूर्ण;

#अगर defined(CONFIG_ACORN_PARTITION_CUMANA) || \
	defined(CONFIG_ACORN_PARTITION_ADFS)
अटल पूर्णांक riscix_partition(काष्ठा parsed_partitions *state,
			    अचिन्हित दीर्घ first_sect, पूर्णांक slot,
			    अचिन्हित दीर्घ nr_sects)
अणु
	Sector sect;
	काष्ठा riscix_record *rr;
	
	rr = पढ़ो_part_sector(state, first_sect, &sect);
	अगर (!rr)
		वापस -1;

	strlcat(state->pp_buf, " [RISCiX]", PAGE_SIZE);


	अगर (rr->magic == RISCIX_MAGIC) अणु
		अचिन्हित दीर्घ size = nr_sects > 2 ? 2 : nr_sects;
		पूर्णांक part;

		strlcat(state->pp_buf, " <", PAGE_SIZE);

		put_partition(state, slot++, first_sect, size);
		क्रम (part = 0; part < 8; part++) अणु
			अगर (rr->part[part].one &&
			    स_भेद(rr->part[part].name, "All\0", 4)) अणु
				put_partition(state, slot++,
					le32_to_cpu(rr->part[part].start),
					le32_to_cpu(rr->part[part].length));
				strlcat(state->pp_buf, "(", PAGE_SIZE);
				strlcat(state->pp_buf, rr->part[part].name, PAGE_SIZE);
				strlcat(state->pp_buf, ")", PAGE_SIZE);
			पूर्ण
		पूर्ण

		strlcat(state->pp_buf, " >\n", PAGE_SIZE);
	पूर्ण अन्यथा अणु
		put_partition(state, slot++, first_sect, nr_sects);
	पूर्ण

	put_dev_sector(sect);
	वापस slot;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर

#घोषणा LINUX_NATIVE_MAGIC 0xdeafa1de
#घोषणा LINUX_SWAP_MAGIC   0xdeafab1e

काष्ठा linux_part अणु
	__le32 magic;
	__le32 start_sect;
	__le32 nr_sects;
पूर्ण;

#अगर defined(CONFIG_ACORN_PARTITION_CUMANA) || \
	defined(CONFIG_ACORN_PARTITION_ADFS)
अटल पूर्णांक linux_partition(काष्ठा parsed_partitions *state,
			   अचिन्हित दीर्घ first_sect, पूर्णांक slot,
			   अचिन्हित दीर्घ nr_sects)
अणु
	Sector sect;
	काष्ठा linux_part *linuxp;
	अचिन्हित दीर्घ size = nr_sects > 2 ? 2 : nr_sects;

	strlcat(state->pp_buf, " [Linux]", PAGE_SIZE);

	put_partition(state, slot++, first_sect, size);

	linuxp = पढ़ो_part_sector(state, first_sect, &sect);
	अगर (!linuxp)
		वापस -1;

	strlcat(state->pp_buf, " <", PAGE_SIZE);
	जबतक (linuxp->magic == cpu_to_le32(LINUX_NATIVE_MAGIC) ||
	       linuxp->magic == cpu_to_le32(LINUX_SWAP_MAGIC)) अणु
		अगर (slot == state->limit)
			अवरोध;
		put_partition(state, slot++, first_sect +
				 le32_to_cpu(linuxp->start_sect),
				 le32_to_cpu(linuxp->nr_sects));
		linuxp ++;
	पूर्ण
	strlcat(state->pp_buf, " >", PAGE_SIZE);

	put_dev_sector(sect);
	वापस slot;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACORN_PARTITION_CUMANA
पूर्णांक adfspart_check_CUMANA(काष्ठा parsed_partitions *state)
अणु
	अचिन्हित दीर्घ first_sector = 0;
	अचिन्हित पूर्णांक start_blk = 0;
	Sector sect;
	अचिन्हित अक्षर *data;
	अक्षर *name = "CUMANA/ADFS";
	पूर्णांक first = 1;
	पूर्णांक slot = 1;

	/*
	 * Try Cumana style partitions - sector 6 contains ADFS boot block
	 * with poपूर्णांकer to next 'drive'.
	 *
	 * There are unknowns in this code - is the 'cylinder number' of the
	 * next partition relative to the start of this one - I'm assuming
	 * it is.
	 *
	 * Also, which ID did Cumana use?
	 *
	 * This is totally unfinished, and will require more work to get it
	 * going. Hence it is totally untested.
	 */
	करो अणु
		काष्ठा adfs_discrecord *dr;
		अचिन्हित पूर्णांक nr_sects;

		data = पढ़ो_part_sector(state, start_blk * 2 + 6, &sect);
		अगर (!data)
			वापस -1;

		अगर (slot == state->limit)
			अवरोध;

		dr = adfs_partition(state, name, data, first_sector, slot++);
		अगर (!dr)
			अवरोध;

		name = शून्य;

		nr_sects = (data[0x1fd] + (data[0x1fe] << 8)) *
			   (dr->heads + (dr->lowsector & 0x40 ? 1 : 0)) *
			   dr->secspertrack;

		अगर (!nr_sects)
			अवरोध;

		first = 0;
		first_sector += nr_sects;
		start_blk += nr_sects >> (BLOCK_SIZE_BITS - 9);
		nr_sects = 0; /* hmm - should be partition size */

		चयन (data[0x1fc] & 15) अणु
		हाल 0: /* No partition / ADFS? */
			अवरोध;

#अगर_घोषित CONFIG_ACORN_PARTITION_RISCIX
		हाल PARTITION_RISCIX_SCSI:
			/* RISCiX - we करोn't know how to find the next one. */
			slot = riscix_partition(state, first_sector, slot,
						nr_sects);
			अवरोध;
#पूर्ण_अगर

		हाल PARTITION_LINUX:
			slot = linux_partition(state, first_sector, slot,
					       nr_sects);
			अवरोध;
		पूर्ण
		put_dev_sector(sect);
		अगर (slot == -1)
			वापस -1;
	पूर्ण जबतक (1);
	put_dev_sector(sect);
	वापस first ? 0 : 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACORN_PARTITION_ADFS
/*
 * Purpose: allocate ADFS partitions.
 *
 * Params : hd		- poपूर्णांकer to gendisk काष्ठाure to store partition info.
 *	    dev		- device number to access.
 *
 * Returns: -1 on error, 0 क्रम no ADFS boot sector, 1 क्रम ok.
 *
 * Alloc  : hda  = whole drive
 *	    hda1 = ADFS partition on first drive.
 *	    hda2 = non-ADFS partition.
 */
पूर्णांक adfspart_check_ADFS(काष्ठा parsed_partitions *state)
अणु
	अचिन्हित दीर्घ start_sect, nr_sects, sectscyl, heads;
	Sector sect;
	अचिन्हित अक्षर *data;
	काष्ठा adfs_discrecord *dr;
	अचिन्हित अक्षर id;
	पूर्णांक slot = 1;

	data = पढ़ो_part_sector(state, 6, &sect);
	अगर (!data)
		वापस -1;

	dr = adfs_partition(state, "ADFS", data, 0, slot++);
	अगर (!dr) अणु
		put_dev_sector(sect);
    		वापस 0;
	पूर्ण

	heads = dr->heads + ((dr->lowsector >> 6) & 1);
	sectscyl = dr->secspertrack * heads;
	start_sect = ((data[0x1fe] << 8) + data[0x1fd]) * sectscyl;
	id = data[0x1fc] & 15;
	put_dev_sector(sect);

	/*
	 * Work out start of non-adfs partition.
	 */
	nr_sects = (state->bdev->bd_inode->i_size >> 9) - start_sect;

	अगर (start_sect) अणु
		चयन (id) अणु
#अगर_घोषित CONFIG_ACORN_PARTITION_RISCIX
		हाल PARTITION_RISCIX_SCSI:
		हाल PARTITION_RISCIX_MFM:
			slot = riscix_partition(state, start_sect, slot,
						nr_sects);
			अवरोध;
#पूर्ण_अगर

		हाल PARTITION_LINUX:
			slot = linux_partition(state, start_sect, slot,
					       nr_sects);
			अवरोध;
		पूर्ण
	पूर्ण
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACORN_PARTITION_ICS

काष्ठा ics_part अणु
	__le32 start;
	__le32 size;
पूर्ण;

अटल पूर्णांक adfspart_check_ICSLinux(काष्ठा parsed_partitions *state,
				   अचिन्हित दीर्घ block)
अणु
	Sector sect;
	अचिन्हित अक्षर *data = पढ़ो_part_sector(state, block, &sect);
	पूर्णांक result = 0;

	अगर (data) अणु
		अगर (स_भेद(data, "LinuxPart", 9) == 0)
			result = 1;
		put_dev_sector(sect);
	पूर्ण

	वापस result;
पूर्ण

/*
 * Check क्रम a valid ICS partition using the checksum.
 */
अटल अंतरभूत पूर्णांक valid_ics_sector(स्थिर अचिन्हित अक्षर *data)
अणु
	अचिन्हित दीर्घ sum;
	पूर्णांक i;

	क्रम (i = 0, sum = 0x50617274; i < 508; i++)
		sum += data[i];

	sum -= le32_to_cpu(*(__le32 *)(&data[508]));

	वापस sum == 0;
पूर्ण

/*
 * Purpose: allocate ICS partitions.
 * Params : hd		- poपूर्णांकer to gendisk काष्ठाure to store partition info.
 *	    dev		- device number to access.
 * Returns: -1 on error, 0 क्रम no ICS table, 1 क्रम partitions ok.
 * Alloc  : hda  = whole drive
 *	    hda1 = ADFS partition 0 on first drive.
 *	    hda2 = ADFS partition 1 on first drive.
 *		..etc..
 */
पूर्णांक adfspart_check_ICS(काष्ठा parsed_partitions *state)
अणु
	स्थिर अचिन्हित अक्षर *data;
	स्थिर काष्ठा ics_part *p;
	पूर्णांक slot;
	Sector sect;

	/*
	 * Try ICS style partitions - sector 0 contains partition info.
	 */
	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data)
	    	वापस -1;

	अगर (!valid_ics_sector(data)) अणु
	    	put_dev_sector(sect);
		वापस 0;
	पूर्ण

	strlcat(state->pp_buf, " [ICS]", PAGE_SIZE);

	क्रम (slot = 1, p = (स्थिर काष्ठा ics_part *)data; p->size; p++) अणु
		u32 start = le32_to_cpu(p->start);
		s32 size = le32_to_cpu(p->size); /* yes, it's चिन्हित. */

		अगर (slot == state->limit)
			अवरोध;

		/*
		 * Negative sizes tell the RISC OS ICS driver to ignore
		 * this partition - in effect it says that this करोes not
		 * contain an ADFS fileप्रणाली.
		 */
		अगर (size < 0) अणु
			size = -size;

			/*
			 * Our own extension - We use the first sector
			 * of the partition to identअगरy what type this
			 * partition is.  We must not make this visible
			 * to the fileप्रणाली.
			 */
			अगर (size > 1 && adfspart_check_ICSLinux(state, start)) अणु
				start += 1;
				size -= 1;
			पूर्ण
		पूर्ण

		अगर (size)
			put_partition(state, slot++, start, size);
	पूर्ण

	put_dev_sector(sect);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACORN_PARTITION_POWERTEC
काष्ठा ptec_part अणु
	__le32 unused1;
	__le32 unused2;
	__le32 start;
	__le32 size;
	__le32 unused5;
	अक्षर type[8];
पूर्ण;

अटल अंतरभूत पूर्णांक valid_ptec_sector(स्थिर अचिन्हित अक्षर *data)
अणु
	अचिन्हित अक्षर checksum = 0x2a;
	पूर्णांक i;

	/*
	 * If it looks like a PC/BIOS partition, then it
	 * probably isn't PowerTec.
	 */
	अगर (data[510] == 0x55 && data[511] == 0xaa)
		वापस 0;

	क्रम (i = 0; i < 511; i++)
		checksum += data[i];

	वापस checksum == data[511];
पूर्ण

/*
 * Purpose: allocate ICS partitions.
 * Params : hd		- poपूर्णांकer to gendisk काष्ठाure to store partition info.
 *	    dev		- device number to access.
 * Returns: -1 on error, 0 क्रम no ICS table, 1 क्रम partitions ok.
 * Alloc  : hda  = whole drive
 *	    hda1 = ADFS partition 0 on first drive.
 *	    hda2 = ADFS partition 1 on first drive.
 *		..etc..
 */
पूर्णांक adfspart_check_POWERTEC(काष्ठा parsed_partitions *state)
अणु
	Sector sect;
	स्थिर अचिन्हित अक्षर *data;
	स्थिर काष्ठा ptec_part *p;
	पूर्णांक slot = 1;
	पूर्णांक i;

	data = पढ़ो_part_sector(state, 0, &sect);
	अगर (!data)
		वापस -1;

	अगर (!valid_ptec_sector(data)) अणु
		put_dev_sector(sect);
		वापस 0;
	पूर्ण

	strlcat(state->pp_buf, " [POWERTEC]", PAGE_SIZE);

	क्रम (i = 0, p = (स्थिर काष्ठा ptec_part *)data; i < 12; i++, p++) अणु
		u32 start = le32_to_cpu(p->start);
		u32 size = le32_to_cpu(p->size);

		अगर (size)
			put_partition(state, slot++, start, size);
	पूर्ण

	put_dev_sector(sect);
	strlcat(state->pp_buf, "\n", PAGE_SIZE);
	वापस 1;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_ACORN_PARTITION_EESOX
काष्ठा eesox_part अणु
	अक्षर	magic[6];
	अक्षर	name[10];
	__le32	start;
	__le32	unused6;
	__le32	unused7;
	__le32	unused8;
पूर्ण;

/*
 * Guess who created this क्रमmat?
 */
अटल स्थिर अक्षर eesox_name[] = अणु
	'N', 'e', 'i', 'l', ' ',
	'C', 'r', 'i', 't', 'c', 'h', 'e', 'l', 'l', ' ', ' '
पूर्ण;

/*
 * EESOX SCSI partition क्रमmat.
 *
 * This is a goddamned awful partition क्रमmat.  We करोn't seem to store
 * the size of the partition in this table, only the start addresses.
 *
 * There are two possibilities where the size comes from:
 *  1. The inभागidual ADFS boot block entries that are placed on the disk.
 *  2. The start address of the next entry.
 */
पूर्णांक adfspart_check_EESOX(काष्ठा parsed_partitions *state)
अणु
	Sector sect;
	स्थिर अचिन्हित अक्षर *data;
	अचिन्हित अक्षर buffer[256];
	काष्ठा eesox_part *p;
	sector_t start = 0;
	पूर्णांक i, slot = 1;

	data = पढ़ो_part_sector(state, 7, &sect);
	अगर (!data)
		वापस -1;

	/*
	 * "Decrypt" the partition table.  God knows why...
	 */
	क्रम (i = 0; i < 256; i++)
		buffer[i] = data[i] ^ eesox_name[i & 15];

	put_dev_sector(sect);

	क्रम (i = 0, p = (काष्ठा eesox_part *)buffer; i < 8; i++, p++) अणु
		sector_t next;

		अगर (स_भेद(p->magic, "Eesox", 6))
			अवरोध;

		next = le32_to_cpu(p->start);
		अगर (i)
			put_partition(state, slot++, start, next - start);
		start = next;
	पूर्ण

	अगर (i != 0) अणु
		sector_t size;

		size = get_capacity(state->bdev->bd_disk);
		put_partition(state, slot++, start, size - start);
		strlcat(state->pp_buf, "\n", PAGE_SIZE);
	पूर्ण

	वापस i ? 1 : 0;
पूर्ण
#पूर्ण_अगर
