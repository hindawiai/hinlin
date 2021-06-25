<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  fs/partitions/atari.c
 *
 *  Code extracted from drivers/block/genhd.c
 *
 *  Copyright (C) 1991-1998  Linus Torvalds
 *  Re-organised Feb 1998 Russell King
 */

#समावेश <linux/प्रकार.स>
#समावेश "check.h"
#समावेश "atari.h"

/* ++guenther: this should be settable by the user ("make config")?.
 */
#घोषणा ICD_PARTS

/* check अगर a partition entry looks valid -- Atari क्रमmat is assumed अगर at
   least one of the primary entries is ok this way */
#घोषणा	VALID_PARTITION(pi,hdsiz)					     \
    (((pi)->flg & 1) &&							     \
     है_अक्षर_अंक((pi)->id[0]) && है_अक्षर_अंक((pi)->id[1]) && है_अक्षर_अंक((pi)->id[2]) && \
     be32_to_cpu((pi)->st) <= (hdsiz) &&				     \
     be32_to_cpu((pi)->st) + be32_to_cpu((pi)->siz) <= (hdsiz))

अटल अंतरभूत पूर्णांक OK_id(अक्षर *s)
अणु
	वापस  स_भेद (s, "GEM", 3) == 0 || स_भेद (s, "BGM", 3) == 0 ||
		स_भेद (s, "LNX", 3) == 0 || स_भेद (s, "SWP", 3) == 0 ||
		स_भेद (s, "RAW", 3) == 0 ;
पूर्ण

पूर्णांक atari_partition(काष्ठा parsed_partitions *state)
अणु
	Sector sect;
	काष्ठा rootsector *rs;
	काष्ठा partition_info *pi;
	u32 extensect;
	u32 hd_size;
	पूर्णांक slot;
#अगर_घोषित ICD_PARTS
	पूर्णांक part_fmt = 0; /* 0:unknown, 1:AHDI, 2:ICD/Supra */
#पूर्ण_अगर

	/*
	 * ATARI partition scheme supports 512 lba only.  If this is not
	 * the हाल, bail early to aव्योम miscalculating hd_size.
	 */
	अगर (bdev_logical_block_size(state->bdev) != 512)
		वापस 0;

	rs = पढ़ो_part_sector(state, 0, &sect);
	अगर (!rs)
		वापस -1;

	/* Verअगरy this is an Atari rootsector: */
	hd_size = state->bdev->bd_inode->i_size >> 9;
	अगर (!VALID_PARTITION(&rs->part[0], hd_size) &&
	    !VALID_PARTITION(&rs->part[1], hd_size) &&
	    !VALID_PARTITION(&rs->part[2], hd_size) &&
	    !VALID_PARTITION(&rs->part[3], hd_size)) अणु
		/*
		 * अगर there's no valid primary partition, assume that no Atari
		 * क्रमmat partition table (there's no reliable magic or the like
	         * :-()
		 */
		put_dev_sector(sect);
		वापस 0;
	पूर्ण

	pi = &rs->part[0];
	strlcat(state->pp_buf, " AHDI", PAGE_SIZE);
	क्रम (slot = 1; pi < &rs->part[4] && slot < state->limit; slot++, pi++) अणु
		काष्ठा rootsector *xrs;
		Sector sect2;
		uदीर्घ partsect;

		अगर ( !(pi->flg & 1) )
			जारी;
		/* active partition */
		अगर (स_भेद (pi->id, "XGM", 3) != 0) अणु
			/* we करोn't care about other id's */
			put_partition (state, slot, be32_to_cpu(pi->st),
					be32_to_cpu(pi->siz));
			जारी;
		पूर्ण
		/* extension partition */
#अगर_घोषित ICD_PARTS
		part_fmt = 1;
#पूर्ण_अगर
		strlcat(state->pp_buf, " XGM<", PAGE_SIZE);
		partsect = extensect = be32_to_cpu(pi->st);
		जबतक (1) अणु
			xrs = पढ़ो_part_sector(state, partsect, &sect2);
			अगर (!xrs) अणु
				prपूर्णांकk (" block %ld read failed\n", partsect);
				put_dev_sector(sect);
				वापस -1;
			पूर्ण

			/* ++roman: sanity check: bit 0 of flg field must be set */
			अगर (!(xrs->part[0].flg & 1)) अणु
				prपूर्णांकk( "\nFirst sub-partition in extended partition is not valid!\n" );
				put_dev_sector(sect2);
				अवरोध;
			पूर्ण

			put_partition(state, slot,
				   partsect + be32_to_cpu(xrs->part[0].st),
				   be32_to_cpu(xrs->part[0].siz));

			अगर (!(xrs->part[1].flg & 1)) अणु
				/* end of linked partition list */
				put_dev_sector(sect2);
				अवरोध;
			पूर्ण
			अगर (स_भेद( xrs->part[1].id, "XGM", 3 ) != 0) अणु
				prपूर्णांकk("\nID of extended partition is not XGM!\n");
				put_dev_sector(sect2);
				अवरोध;
			पूर्ण

			partsect = be32_to_cpu(xrs->part[1].st) + extensect;
			put_dev_sector(sect2);
			अगर (++slot == state->limit) अणु
				prपूर्णांकk( "\nMaximum number of partitions reached!\n" );
				अवरोध;
			पूर्ण
		पूर्ण
		strlcat(state->pp_buf, " >", PAGE_SIZE);
	पूर्ण
#अगर_घोषित ICD_PARTS
	अगर ( part_fmt!=1 ) अणु /* no extended partitions -> test ICD-क्रमmat */
		pi = &rs->icdpart[0];
		/* sanity check: no ICD क्रमmat अगर first partition invalid */
		अगर (OK_id(pi->id)) अणु
			strlcat(state->pp_buf, " ICD<", PAGE_SIZE);
			क्रम (; pi < &rs->icdpart[8] && slot < state->limit; slot++, pi++) अणु
				/* accept only GEM,BGM,RAW,LNX,SWP partitions */
				अगर (!((pi->flg & 1) && OK_id(pi->id)))
					जारी;
				part_fmt = 2;
				put_partition (state, slot,
						be32_to_cpu(pi->st),
						be32_to_cpu(pi->siz));
			पूर्ण
			strlcat(state->pp_buf, " >", PAGE_SIZE);
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	put_dev_sector(sect);

	strlcat(state->pp_buf, "\n", PAGE_SIZE);

	वापस 1;
पूर्ण
