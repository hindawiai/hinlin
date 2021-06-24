<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/fs/hpfs/hpfs.h
 *
 *  HPFS काष्ठाures by Chris Smith, 1993
 *
 *  a little bit modअगरied by Mikulas Patocka, 1998-1999
 */

/* The paper

     Duncan, Roy
     Design goals and implementation of the new High Perक्रमmance File System
     Microsoft Systems Journal  Sept 1989  v4 n5 p1(13)

   describes what HPFS looked like when it was new, and it is the source
   of most of the inक्रमmation given here.  The rest is conjecture.

   For definitive inक्रमmation on the Duncan paper, see it, not this file.
   For definitive inक्रमmation on HPFS, ask somebody अन्यथा -- this is guesswork.
   There are certain to be many mistakes. */

#अगर !defined(__LITTLE_ENDIAN) && !defined(__BIG_ENDIAN)
#त्रुटि unknown endian
#पूर्ण_अगर

/* Notation */

प्रकार u32 secno;			/* sector number, partition relative */

प्रकार secno dnode_secno;		/* sector number of a dnode */
प्रकार secno fnode_secno;		/* sector number of an fnode */
प्रकार secno anode_secno;		/* sector number of an anode */

प्रकार u32 समय32_t;		/* 32-bit समय_प्रकार type */

/* sector 0 */

/* The boot block is very like a FAT boot block, except that the
   29h signature byte is 28h instead, and the ID string is "HPFS". */

#घोषणा BB_MAGIC 0xaa55

काष्ठा hpfs_boot_block
अणु
  u8 jmp[3];
  u8 oem_id[8];
  u8 bytes_per_sector[2];	/* 512 */
  u8 sectors_per_cluster;
  u8 n_reserved_sectors[2];
  u8 n_fats;
  u8 n_rootdir_entries[2];
  u8 n_sectors_s[2];
  u8 media_byte;
  __le16 sectors_per_fat;
  __le16 sectors_per_track;
  __le16 heads_per_cyl;
  __le32 n_hidden_sectors;
  __le32 n_sectors_l;		/* size of partition */
  u8 drive_number;
  u8 mbz;
  u8 sig_28h;			/* 28h */
  u8 vol_serno[4];
  u8 vol_label[11];
  u8 sig_hpfs[8];		/* "HPFS    " */
  u8 pad[448];
  __le16 magic;			/* aa55 */
पूर्ण;


/* sector 16 */

/* The super block has the poपूर्णांकer to the root directory. */

#घोषणा SB_MAGIC 0xf995e849

काष्ठा hpfs_super_block
अणु
  __le32 magic;				/* f995 e849 */
  __le32 magic1;			/* fa53 e9c5, more magic? */
  u8 version;				/* version of a fileप्रणाली  usually 2 */
  u8 funcversion;			/* functional version - oldest version
  					   of fileप्रणाली that can understand
					   this disk */
  __le16 zero;				/* 0 */
  __le32 root;				/* fnode of root directory */
  __le32 n_sectors;			/* size of fileप्रणाली */
  __le32 n_badblocks;			/* number of bad blocks */
  __le32 biपंचांगaps;			/* poपूर्णांकers to मुक्त space bit maps */
  __le32 zero1;				/* 0 */
  __le32 badblocks;			/* bad block list */
  __le32 zero3;				/* 0 */
  __le32 last_chkdsk;			/* date last checked, 0 अगर never */
  __le32 last_optimize;			/* date last optimized, 0 अगर never */
  __le32 n_dir_band;			/* number of sectors in dir band */
  __le32 dir_band_start;			/* first sector in dir band */
  __le32 dir_band_end;			/* last sector in dir band */
  __le32 dir_band_biपंचांगap;		/* मुक्त space map, 1 dnode per bit */
  u8 volume_name[32];			/* not used */
  __le32 user_id_table;			/* 8 pपुनः_स्मृतिated sectors - user id */
  u32 zero6[103];			/* 0 */
पूर्ण;


/* sector 17 */

/* The spare block has poपूर्णांकers to spare sectors.  */

#घोषणा SP_MAGIC 0xf9911849

काष्ठा hpfs_spare_block
अणु
  __le32 magic;				/* f991 1849 */
  __le32 magic1;				/* fa52 29c5, more magic? */

#अगर_घोषित __LITTLE_ENDIAN
  u8 dirty: 1;				/* 0 clean, 1 "improperly stopped" */
  u8 sparedir_used: 1;			/* spare dirblks used */
  u8 hotfixes_used: 1;			/* hotfixes used */
  u8 bad_sector: 1;			/* bad sector, corrupted disk (???) */
  u8 bad_biपंचांगap: 1;			/* bad biपंचांगap */
  u8 fast: 1;				/* partition was fast क्रमmatted */
  u8 old_wrote: 1;			/* old version wrote to partition */
  u8 old_wrote_1: 1;			/* old version wrote to partition (?) */
#अन्यथा
  u8 old_wrote_1: 1;			/* old version wrote to partition (?) */
  u8 old_wrote: 1;			/* old version wrote to partition */
  u8 fast: 1;				/* partition was fast क्रमmatted */
  u8 bad_biपंचांगap: 1;			/* bad biपंचांगap */
  u8 bad_sector: 1;			/* bad sector, corrupted disk (???) */
  u8 hotfixes_used: 1;			/* hotfixes used */
  u8 sparedir_used: 1;			/* spare dirblks used */
  u8 dirty: 1;				/* 0 clean, 1 "improperly stopped" */
#पूर्ण_अगर

#अगर_घोषित __LITTLE_ENDIAN
  u8 install_dasd_limits: 1;		/* HPFS386 flags */
  u8 resynch_dasd_limits: 1;
  u8 dasd_limits_operational: 1;
  u8 mulसमयdia_active: 1;
  u8 dce_acls_active: 1;
  u8 dasd_limits_dirty: 1;
  u8 flag67: 2;
#अन्यथा
  u8 flag67: 2;
  u8 dasd_limits_dirty: 1;
  u8 dce_acls_active: 1;
  u8 mulसमयdia_active: 1;
  u8 dasd_limits_operational: 1;
  u8 resynch_dasd_limits: 1;
  u8 install_dasd_limits: 1;		/* HPFS386 flags */
#पूर्ण_अगर

  u8 mm_contlgulty;
  u8 unused;

  __le32 hotfix_map;			/* info about remapped bad sectors */
  __le32 n_spares_used;			/* number of hotfixes */
  __le32 n_spares;			/* number of spares in hotfix map */
  __le32 n_dnode_spares_मुक्त;		/* spare dnodes unused */
  __le32 n_dnode_spares;		/* length of spare_dnodes[] list,
					   follows in this block*/
  __le32 code_page_dir;			/* code page directory block */
  __le32 n_code_pages;			/* number of code pages */
  __le32 super_crc;			/* on HPFS386 and LAN Server this is
  					   checksum of superblock, on normal
					   OS/2 unused */
  __le32 spare_crc;			/* on HPFS386 checksum of spareblock */
  __le32 zero1[15];			/* unused */
  __le32 spare_dnodes[100];		/* emergency मुक्त dnode list */
  __le32 zero2[1];			/* room क्रम more? */
पूर्ण;

/* The bad block list is 4 sectors दीर्घ.  The first word must be zero,
   the reमुख्यing words give n_badblocks bad block numbers.
   I bet you can see it coming... */

#घोषणा BAD_MAGIC 0
       
/* The hotfix map is 4 sectors दीर्घ.  It looks like

       secno from[n_spares];
       secno to[n_spares];

   The to[] list is initialized to poपूर्णांक to n_spares pपुनः_स्मृतिated empty
   sectors.  The from[] list contains the sector numbers of bad blocks
   which have been remapped to corresponding sectors in the to[] list.
   n_spares_used gives the length of the from[] list. */


/* Sectors 18 and 19 are pपुनः_स्मृतिated and unused.
   Maybe they're spares क्रम 16 and 17, but simple substitution fails. */


/* The code page info poपूर्णांकed to by the spare block consists of an index
   block and blocks containing uppercasing tables.  I करोn't know what
   these are क्रम (CHKDSK, maybe?) -- OS/2 करोes not seem to use them
   itself.  Linux करोesn't use them either. */

/* block poपूर्णांकed to by spareblock->code_page_dir */

#घोषणा CP_सूची_MAGIC 0x494521f7

काष्ठा code_page_directory
अणु
  __le32 magic;				/* 4945 21f7 */
  __le32 n_code_pages;			/* number of poपूर्णांकers following */
  __le32 zero1[2];
  काष्ठा अणु
    __le16 ix;				/* index */
    __le16 code_page_number;		/* code page number */
    __le32 bounds;			/* matches corresponding word
					   in data block */
    __le32 code_page_data;		/* sector number of a code_page_data
					   containing c.p. array */
    __le16 index;			/* index in c.p. array in that sector*/
    __le16 unknown;			/* some unknown value; usually 0;
    					   2 in Japanese version */
  पूर्ण array[31];				/* unknown length */
पूर्ण;

/* blocks poपूर्णांकed to by code_page_directory */

#घोषणा CP_DATA_MAGIC 0x894521f7

काष्ठा code_page_data
अणु
  __le32 magic;				/* 8945 21f7 */
  __le32 n_used;			/* # elements used in c_p_data[] */
  __le32 bounds[3];			/* looks a bit like
					     (beg1,end1), (beg2,end2)
					   one byte each */
  __le16 offs[3];			/* offsets from start of sector
					   to start of c_p_data[ix] */
  काष्ठा अणु
    __le16 ix;				/* index */
    __le16 code_page_number;		/* code page number */
    __le16 unknown;			/* the same as in cp directory */
    u8 map[128];			/* upहाल table क्रम अक्षरs 80..ff */
    __le16 zero2;
  पूर्ण code_page[3];
  u8 incognita[78];
पूर्ण;


/* Free space biपंचांगaps are 4 sectors दीर्घ, which is 16384 bits.
   16384 sectors is 8 meg, and each 8 meg band has a 4-sector biपंचांगap.
   Bit order in the maps is little-endian.  0 means taken, 1 means मुक्त.

   Bit map sectors are marked allocated in the bit maps, and so are sectors 
   off the end of the partition.

   Band 0 is sectors 0-3fff, its map is in sectors 18-1b.
   Band 1 is 4000-7fff, its map is in 7ffc-7fff.
   Band 2 is 8000-ffff, its map is in 8000-8003.
   The reमुख्यing bands have maps in their first (even) or last (odd) 4 sectors
     -- अगर the last, partial, band is odd its map is in its last 4 sectors.

   The biपंचांगap locations are given in a table poपूर्णांकed to by the super block.
   No करोubt they aren't स्थिरrained to be at 18, 7ffc, 8000, ...; that is
   just where they usually are.

   The "directory band" is a bunch of sectors pपुनः_स्मृतिated क्रम dnodes.
   It has a 4-sector मुक्त space biपंचांगap of its own.  Each bit in the map
   corresponds to one 4-sector dnode, bit 0 of the map corresponding to
   the first 4 sectors of the directory band.  The entire band is marked
   allocated in the मुख्य biपंचांगap.   The super block gives the locations
   of the directory band and its biपंचांगap.  ("band" करोesn't mean it is
   8 meg दीर्घ; it isn't.)  */


/* dnode: directory.  4 sectors दीर्घ */

/* A directory is a tree of dnodes.  The fnode क्रम a directory
   contains one poपूर्णांकer, to the root dnode of the tree.  The fnode
   never moves, the dnodes करो the B-tree thing, splitting and merging
   as files are added and हटाओd.  */

#घोषणा DNODE_MAGIC   0x77e40aae

काष्ठा dnode अणु
  __le32 magic;				/* 77e4 0aae */
  __le32 first_मुक्त;			/* offset from start of dnode to
					   first मुक्त dir entry */
#अगर_घोषित __LITTLE_ENDIAN
  u8 root_dnode: 1;			/* Is it root dnode? */
  u8 increment_me: 7;			/* some kind of activity counter? */
					/* Neither HPFS.IFS nor CHKDSK cares
					   अगर you change this word */
#अन्यथा
  u8 increment_me: 7;			/* some kind of activity counter? */
					/* Neither HPFS.IFS nor CHKDSK cares
					   अगर you change this word */
  u8 root_dnode: 1;			/* Is it root dnode? */
#पूर्ण_अगर
  u8 increment_me2[3];
  __le32 up;				/* (root dnode) directory's fnode
					   (nonroot) parent dnode */
  __le32 self;			/* poपूर्णांकer to this dnode */
  u8 dirent[2028];			/* one or more dirents */
पूर्ण;

काष्ठा hpfs_dirent अणु
  __le16 length;			/* offset to next dirent */

#अगर_घोषित __LITTLE_ENDIAN
  u8 first: 1;				/* set on phony ^A^A (".") entry */
  u8 has_acl: 1;
  u8 करोwn: 1;				/* करोwn poपूर्णांकer present (after name) */
  u8 last: 1;				/* set on phony \377 entry */
  u8 has_ea: 1;				/* entry has EA */
  u8 has_xtd_perm: 1;			/* has extended perm list (???) */
  u8 has_explicit_acl: 1;
  u8 has_needea: 1;			/* ?? some EA has NEEDEA set
					   I have no idea why this is
					   पूर्णांकeresting in a dir entry */
#अन्यथा
  u8 has_needea: 1;			/* ?? some EA has NEEDEA set
					   I have no idea why this is
					   पूर्णांकeresting in a dir entry */
  u8 has_explicit_acl: 1;
  u8 has_xtd_perm: 1;			/* has extended perm list (???) */
  u8 has_ea: 1;				/* entry has EA */
  u8 last: 1;				/* set on phony \377 entry */
  u8 करोwn: 1;				/* करोwn poपूर्णांकer present (after name) */
  u8 has_acl: 1;
  u8 first: 1;				/* set on phony ^A^A (".") entry */
#पूर्ण_अगर

#अगर_घोषित __LITTLE_ENDIAN
  u8 पढ़ो_only: 1;			/* करोs attrib */
  u8 hidden: 1;				/* करोs attrib */
  u8 प्रणाली: 1;				/* करोs attrib */
  u8 flag11: 1;				/* would be volume label करोs attrib */
  u8 directory: 1;			/* करोs attrib */
  u8 archive: 1;			/* करोs attrib */
  u8 not_8x3: 1;			/* name is not 8.3 */
  u8 flag15: 1;
#अन्यथा
  u8 flag15: 1;
  u8 not_8x3: 1;			/* name is not 8.3 */
  u8 archive: 1;			/* करोs attrib */
  u8 directory: 1;			/* करोs attrib */
  u8 flag11: 1;				/* would be volume label करोs attrib */
  u8 प्रणाली: 1;				/* करोs attrib */
  u8 hidden: 1;				/* करोs attrib */
  u8 पढ़ो_only: 1;			/* करोs attrib */
#पूर्ण_अगर

  __le32 fnode;				/* fnode giving allocation info */
  __le32 ग_लिखो_date;			/* mसमय */
  __le32 file_size;			/* file length, bytes */
  __le32 पढ़ो_date;			/* aसमय */
  __le32 creation_date;			/* स_समय */
  __le32 ea_size;			/* total EA length, bytes */
  u8 no_of_acls;			/* number of ACL's (low 3 bits) */
  u8 ix;				/* code page index (of filename), see
					   काष्ठा code_page_data */
  u8 namelen;				/* file name length */
  u8 name[];				/* file name */
  /* dnode_secno करोwn;	  btree करोwn poपूर्णांकer, अगर present,
     			  follows name on next word boundary, or maybe it
			  precedes next dirent, which is on a word boundary. */
पूर्ण;


/* B+ tree: allocation info in fnodes and anodes */

/* dnodes poपूर्णांक to fnodes which are responsible क्रम listing the sectors
   asचिन्हित to the file.  This is करोne with trees of (length,address)
   pairs.  (Actually triples, of (length, file-address, disk-address)
   which can represent holes.  Find out अगर HPFS करोes that.)
   At any rate, fnodes contain a small tree; अगर subtrees are needed
   they occupy essentially a full block in anodes.  A leaf-level tree node
   has 3-word entries giving sector runs, a non-leaf node has 2-word
   entries giving subtree poपूर्णांकers.  A flag in the header says which. */

काष्ठा bplus_leaf_node
अणु
  __le32 file_secno;			/* first file sector in extent */
  __le32 length;			/* length, sectors */
  __le32 disk_secno;			/* first corresponding disk sector */
पूर्ण;

काष्ठा bplus_पूर्णांकernal_node
अणु
  __le32 file_secno;			/* subtree maps sectors < this  */
  __le32 करोwn;				/* poपूर्णांकer to subtree */
पूर्ण;

क्रमागत अणु
	BP_hbff = 1,
	BP_fnode_parent = 0x20,
	BP_binary_search = 0x40,
	BP_पूर्णांकernal = 0x80
पूर्ण;
काष्ठा bplus_header
अणु
  u8 flags;				/* bit 0 - high bit of first मुक्त entry offset
					   bit 5 - we're poपूर्णांकed to by an fnode,
					   the data btree or some ea or the
					   मुख्य ea bootage poपूर्णांकer ea_secno
					   bit 6 - suggest binary search (unused)
					   bit 7 - 1 -> (पूर्णांकernal) tree of anodes
						   0 -> (leaf) list of extents */
  u8 fill[3];
  u8 n_मुक्त_nodes;			/* मुक्त nodes in following array */
  u8 n_used_nodes;			/* used nodes in following array */
  __le16 first_मुक्त;			/* offset from start of header to
					   first मुक्त node in array */
  जोड़ अणु
    काष्ठा bplus_पूर्णांकernal_node पूर्णांकernal[0]; /* (पूर्णांकernal) 2-word entries giving
					       subtree poपूर्णांकers */
    काष्ठा bplus_leaf_node बाह्यal[0];	    /* (बाह्यal) 3-word entries giving
					       sector runs */
  पूर्ण u;
पूर्ण;

अटल अंतरभूत bool bp_पूर्णांकernal(काष्ठा bplus_header *bp)
अणु
	वापस bp->flags & BP_पूर्णांकernal;
पूर्ण

अटल अंतरभूत bool bp_fnode_parent(काष्ठा bplus_header *bp)
अणु
	वापस bp->flags & BP_fnode_parent;
पूर्ण

/* fnode: root of allocation b+ tree, and EA's */

/* Every file and every directory has one fnode, poपूर्णांकed to by the directory
   entry and poपूर्णांकing to the file's sectors or directory's root dnode.  EA's
   are also stored here, and there are said to be ACL's somewhere here too. */

#घोषणा FNODE_MAGIC 0xf7e40aae

क्रमागत अणुFNODE_anode = cpu_to_le16(2), FNODE_dir = cpu_to_le16(256)पूर्ण;
काष्ठा fnode
अणु
  __le32 magic;				/* f7e4 0aae */
  __le32 zero1[2];			/* पढ़ो history */
  u8 len, name[15];			/* true length, truncated name */
  __le32 up;				/* poपूर्णांकer to file's directory fnode */
  __le32 acl_size_l;
  __le32 acl_secno;
  __le16 acl_size_s;
  u8 acl_anode;
  u8 zero2;				/* history bit count */
  __le32 ea_size_l;			/* length of disk-resident ea's */
  __le32 ea_secno;			/* first sector of disk-resident ea's*/
  __le16 ea_size_s;			/* length of fnode-resident ea's */

  __le16 flags;				/* bit 1 set -> ea_secno is an anode */
					/* bit 8 set -> directory.  first & only extent
					   poपूर्णांकs to dnode. */
  काष्ठा bplus_header btree;		/* b+ tree, 8 extents or 12 subtrees */
  जोड़ अणु
    काष्ठा bplus_leaf_node बाह्यal[8];
    काष्ठा bplus_पूर्णांकernal_node पूर्णांकernal[12];
  पूर्ण u;

  __le32 file_size;			/* file length, bytes */
  __le32 n_needea;			/* number of EA's with NEEDEA set */
  u8 user_id[16];			/* unused */
  __le16 ea_offs;			/* offset from start of fnode
					   to first fnode-resident ea */
  u8 dasd_limit_treshhold;
  u8 dasd_limit_delta;
  __le32 dasd_limit;
  __le32 dasd_usage;
  u8 ea[316];				/* zero or more EA's, packed together
					   with no alignment padding.
					   (Do not use this name, get here
					   via fnode + ea_offs. I think.) */
पूर्ण;

अटल अंतरभूत bool fnode_in_anode(काष्ठा fnode *p)
अणु
	वापस (p->flags & FNODE_anode) != 0;
पूर्ण

अटल अंतरभूत bool fnode_is_dir(काष्ठा fnode *p)
अणु
	वापस (p->flags & FNODE_dir) != 0;
पूर्ण


/* anode: 99.44% pure allocation tree */

#घोषणा ANODE_MAGIC 0x37e40aae

काष्ठा anode
अणु
  __le32 magic;				/* 37e4 0aae */
  __le32 self;				/* poपूर्णांकer to this anode */
  __le32 up;				/* parent anode or fnode */

  काष्ठा bplus_header btree;		/* b+tree, 40 extents or 60 subtrees */
  जोड़ अणु
    काष्ठा bplus_leaf_node बाह्यal[40];
    काष्ठा bplus_पूर्णांकernal_node पूर्णांकernal[60];
  पूर्ण u;

  __le32 fill[3];			/* unused */
पूर्ण;


/* extended attributes.

   A file's EA info is stored as a list of (name,value) pairs.  It is
   usually in the fnode, but (अगर it's large) it is moved to a single
   sector run outside the fnode, or to multiple runs with an anode tree
   that poपूर्णांकs to them.

   The value of a single EA is stored aदीर्घ with the name, or (अगर large)
   it is moved to a single sector run, or multiple runs poपूर्णांकed to by an
   anode tree, poपूर्णांकed to by the value field of the (name,value) pair.

   Flags in the EA tell whether the value is immediate, in a single sector
   run, or in multiple runs.  Flags in the fnode tell whether the EA list
   is immediate, in a single run, or in multiple runs. */

क्रमागत अणुEA_indirect = 1, EA_anode = 2, EA_needea = 128 पूर्ण;
काष्ठा extended_attribute
अणु
  u8 flags;				/* bit 0 set -> value gives sector number
					   where real value starts */
					/* bit 1 set -> sector is an anode
					   that poपूर्णांकs to fragmented value */
					/* bit 7 set -> required ea */
  u8 namelen;				/* length of name, bytes */
  u8 valuelen_lo;			/* length of value, bytes */
  u8 valuelen_hi;			/* length of value, bytes */
  u8 name[];
  /*
    u8 name[namelen];			ascii attrib name
    u8 nul;				terminating '\0', not counted
    u8 value[valuelen];			value, arbitrary
      अगर this.flags & 1, valuelen is 8 and the value is
        u32 length;			real length of value, bytes
        secno secno;			sector address where it starts
      अगर this.anode, the above sector number is the root of an anode tree
        which poपूर्णांकs to the value.
  */
पूर्ण;

अटल अंतरभूत bool ea_indirect(काष्ठा extended_attribute *ea)
अणु
	वापस ea->flags & EA_indirect;
पूर्ण

अटल अंतरभूत bool ea_in_anode(काष्ठा extended_attribute *ea)
अणु
	वापस ea->flags & EA_anode;
पूर्ण

/*
   Local Variables:
   comment-column: 40
   End:
*/
