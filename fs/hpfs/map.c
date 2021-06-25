<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/map.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  mapping काष्ठाures to memory with some minimal checks
 */

#समावेश "hpfs_fn.h"

__le32 *hpfs_map_dnode_biपंचांगap(काष्ठा super_block *s, काष्ठा quad_buffer_head *qbh)
अणु
	वापस hpfs_map_4sectors(s, hpfs_sb(s)->sb_dmap, qbh, 0);
पूर्ण

__le32 *hpfs_map_biपंचांगap(काष्ठा super_block *s, अचिन्हित bmp_block,
			 काष्ठा quad_buffer_head *qbh, अक्षर *id)
अणु
	secno sec;
	__le32 *ret;
	अचिन्हित n_bands = (hpfs_sb(s)->sb_fs_size + 0x3fff) >> 14;
	अगर (hpfs_sb(s)->sb_chk) अगर (bmp_block >= n_bands) अणु
		hpfs_error(s, "hpfs_map_bitmap called with bad parameter: %08x at %s", bmp_block, id);
		वापस शून्य;
	पूर्ण
	sec = le32_to_cpu(hpfs_sb(s)->sb_bmp_dir[bmp_block]);
	अगर (!sec || sec > hpfs_sb(s)->sb_fs_size-4) अणु
		hpfs_error(s, "invalid bitmap block pointer %08x -> %08x at %s", bmp_block, sec, id);
		वापस शून्य;
	पूर्ण
	ret = hpfs_map_4sectors(s, sec, qbh, 4);
	अगर (ret) hpfs_prefetch_biपंचांगap(s, bmp_block + 1);
	वापस ret;
पूर्ण

व्योम hpfs_prefetch_biपंचांगap(काष्ठा super_block *s, अचिन्हित bmp_block)
अणु
	अचिन्हित to_prefetch, next_prefetch;
	अचिन्हित n_bands = (hpfs_sb(s)->sb_fs_size + 0x3fff) >> 14;
	अगर (unlikely(bmp_block >= n_bands))
		वापस;
	to_prefetch = le32_to_cpu(hpfs_sb(s)->sb_bmp_dir[bmp_block]);
	अगर (unlikely(bmp_block + 1 >= n_bands))
		next_prefetch = 0;
	अन्यथा
		next_prefetch = le32_to_cpu(hpfs_sb(s)->sb_bmp_dir[bmp_block + 1]);
	hpfs_prefetch_sectors(s, to_prefetch, 4 + 4 * (to_prefetch + 4 == next_prefetch));
पूर्ण

/*
 * Load first code page पूर्णांकo kernel memory, वापस poपूर्णांकer to 256-byte array,
 * first 128 bytes are uppercasing table क्रम अक्षरs 128-255, next 128 bytes are
 * lowercasing table
 */

अचिन्हित अक्षर *hpfs_load_code_page(काष्ठा super_block *s, secno cps)
अणु
	काष्ठा buffer_head *bh;
	secno cpds;
	अचिन्हित cpi;
	अचिन्हित अक्षर *ptr;
	अचिन्हित अक्षर *cp_table;
	पूर्णांक i;
	काष्ठा code_page_data *cpd;
	काष्ठा code_page_directory *cp = hpfs_map_sector(s, cps, &bh, 0);
	अगर (!cp) वापस शून्य;
	अगर (le32_to_cpu(cp->magic) != CP_सूची_MAGIC) अणु
		pr_err("Code page directory magic doesn't match (magic = %08x)\n",
			le32_to_cpu(cp->magic));
		brअन्यथा(bh);
		वापस शून्य;
	पूर्ण
	अगर (!le32_to_cpu(cp->n_code_pages)) अणु
		pr_err("n_code_pages == 0\n");
		brअन्यथा(bh);
		वापस शून्य;
	पूर्ण
	cpds = le32_to_cpu(cp->array[0].code_page_data);
	cpi = le16_to_cpu(cp->array[0].index);
	brअन्यथा(bh);

	अगर (cpi >= 3) अणु
		pr_err("Code page index out of array\n");
		वापस शून्य;
	पूर्ण
	
	अगर (!(cpd = hpfs_map_sector(s, cpds, &bh, 0))) वापस शून्य;
	अगर (le16_to_cpu(cpd->offs[cpi]) > 0x178) अणु
		pr_err("Code page index out of sector\n");
		brअन्यथा(bh);
		वापस शून्य;
	पूर्ण
	ptr = (अचिन्हित अक्षर *)cpd + le16_to_cpu(cpd->offs[cpi]) + 6;
	अगर (!(cp_table = kदो_स्मृति(256, GFP_KERNEL))) अणु
		pr_err("out of memory for code page table\n");
		brअन्यथा(bh);
		वापस शून्य;
	पूर्ण
	स_नकल(cp_table, ptr, 128);
	brअन्यथा(bh);

	/* Try to build lowercasing table from uppercasing one */

	क्रम (i=128; i<256; i++) cp_table[i]=i;
	क्रम (i=128; i<256; i++) अगर (cp_table[i-128]!=i && cp_table[i-128]>=128)
		cp_table[cp_table[i-128]] = i;
	
	वापस cp_table;
पूर्ण

__le32 *hpfs_load_biपंचांगap_directory(काष्ठा super_block *s, secno bmp)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक n = (hpfs_sb(s)->sb_fs_size + 0x200000 - 1) >> 21;
	पूर्णांक i;
	__le32 *b;
	अगर (!(b = kदो_स्मृति_array(n, 512, GFP_KERNEL))) अणु
		pr_err("can't allocate memory for bitmap directory\n");
		वापस शून्य;
	पूर्ण	
	क्रम (i=0;i<n;i++) अणु
		__le32 *d = hpfs_map_sector(s, bmp+i, &bh, n - i - 1);
		अगर (!d) अणु
			kमुक्त(b);
			वापस शून्य;
		पूर्ण
		स_नकल((अक्षर *)b + 512 * i, d, 512);
		brअन्यथा(bh);
	पूर्ण
	वापस b;
पूर्ण

व्योम hpfs_load_hotfix_map(काष्ठा super_block *s, काष्ठा hpfs_spare_block *spareblock)
अणु
	काष्ठा quad_buffer_head qbh;
	__le32 *directory;
	u32 n_hotfixes, n_used_hotfixes;
	अचिन्हित i;

	n_hotfixes = le32_to_cpu(spareblock->n_spares);
	n_used_hotfixes = le32_to_cpu(spareblock->n_spares_used);

	अगर (n_hotfixes > 256 || n_used_hotfixes > n_hotfixes) अणु
		hpfs_error(s, "invalid number of hotfixes: %u, used: %u", n_hotfixes, n_used_hotfixes);
		वापस;
	पूर्ण
	अगर (!(directory = hpfs_map_4sectors(s, le32_to_cpu(spareblock->hotfix_map), &qbh, 0))) अणु
		hpfs_error(s, "can't load hotfix map");
		वापस;
	पूर्ण
	क्रम (i = 0; i < n_used_hotfixes; i++) अणु
		hpfs_sb(s)->hotfix_from[i] = le32_to_cpu(directory[i]);
		hpfs_sb(s)->hotfix_to[i] = le32_to_cpu(directory[n_hotfixes + i]);
	पूर्ण
	hpfs_sb(s)->n_hotfixes = n_used_hotfixes;
	hpfs_brअन्यथा4(&qbh);
पूर्ण

/*
 * Load fnode to memory
 */

काष्ठा fnode *hpfs_map_fnode(काष्ठा super_block *s, ino_t ino, काष्ठा buffer_head **bhp)
अणु
	काष्ठा fnode *fnode;
	अगर (hpfs_sb(s)->sb_chk) अगर (hpfs_chk_sectors(s, ino, 1, "fnode")) अणु
		वापस शून्य;
	पूर्ण
	अगर ((fnode = hpfs_map_sector(s, ino, bhp, FNODE_RD_AHEAD))) अणु
		अगर (hpfs_sb(s)->sb_chk) अणु
			काष्ठा extended_attribute *ea;
			काष्ठा extended_attribute *ea_end;
			अगर (le32_to_cpu(fnode->magic) != FNODE_MAGIC) अणु
				hpfs_error(s, "bad magic on fnode %08lx",
					(अचिन्हित दीर्घ)ino);
				जाओ bail;
			पूर्ण
			अगर (!fnode_is_dir(fnode)) अणु
				अगर ((अचिन्हित)fnode->btree.n_used_nodes + (अचिन्हित)fnode->btree.n_मुक्त_nodes !=
				    (bp_पूर्णांकernal(&fnode->btree) ? 12 : 8)) अणु
					hpfs_error(s,
					   "bad number of nodes in fnode %08lx",
					    (अचिन्हित दीर्घ)ino);
					जाओ bail;
				पूर्ण
				अगर (le16_to_cpu(fnode->btree.first_मुक्त) !=
				    8 + fnode->btree.n_used_nodes * (bp_पूर्णांकernal(&fnode->btree) ? 8 : 12)) अणु
					hpfs_error(s,
					    "bad first_free pointer in fnode %08lx",
					    (अचिन्हित दीर्घ)ino);
					जाओ bail;
				पूर्ण
			पूर्ण
			अगर (le16_to_cpu(fnode->ea_size_s) && (le16_to_cpu(fnode->ea_offs) < 0xc4 ||
			   le16_to_cpu(fnode->ea_offs) + le16_to_cpu(fnode->acl_size_s) + le16_to_cpu(fnode->ea_size_s) > 0x200)) अणु
				hpfs_error(s,
					"bad EA info in fnode %08lx: ea_offs == %04x ea_size_s == %04x",
					(अचिन्हित दीर्घ)ino,
					le16_to_cpu(fnode->ea_offs), le16_to_cpu(fnode->ea_size_s));
				जाओ bail;
			पूर्ण
			ea = fnode_ea(fnode);
			ea_end = fnode_end_ea(fnode);
			जबतक (ea != ea_end) अणु
				अगर (ea > ea_end) अणु
					hpfs_error(s, "bad EA in fnode %08lx",
						(अचिन्हित दीर्घ)ino);
					जाओ bail;
				पूर्ण
				ea = next_ea(ea);
			पूर्ण
		पूर्ण
	पूर्ण
	वापस fnode;
	bail:
	brअन्यथा(*bhp);
	वापस शून्य;
पूर्ण

काष्ठा anode *hpfs_map_anode(काष्ठा super_block *s, anode_secno ano, काष्ठा buffer_head **bhp)
अणु
	काष्ठा anode *anode;
	अगर (hpfs_sb(s)->sb_chk) अगर (hpfs_chk_sectors(s, ano, 1, "anode")) वापस शून्य;
	अगर ((anode = hpfs_map_sector(s, ano, bhp, ANODE_RD_AHEAD)))
		अगर (hpfs_sb(s)->sb_chk) अणु
			अगर (le32_to_cpu(anode->magic) != ANODE_MAGIC) अणु
				hpfs_error(s, "bad magic on anode %08x", ano);
				जाओ bail;
			पूर्ण
			अगर (le32_to_cpu(anode->self) != ano) अणु
				hpfs_error(s, "self pointer invalid on anode %08x", ano);
				जाओ bail;
			पूर्ण
			अगर ((अचिन्हित)anode->btree.n_used_nodes + (अचिन्हित)anode->btree.n_मुक्त_nodes !=
			    (bp_पूर्णांकernal(&anode->btree) ? 60 : 40)) अणु
				hpfs_error(s, "bad number of nodes in anode %08x", ano);
				जाओ bail;
			पूर्ण
			अगर (le16_to_cpu(anode->btree.first_मुक्त) !=
			    8 + anode->btree.n_used_nodes * (bp_पूर्णांकernal(&anode->btree) ? 8 : 12)) अणु
				hpfs_error(s, "bad first_free pointer in anode %08x", ano);
				जाओ bail;
			पूर्ण
		पूर्ण
	वापस anode;
	bail:
	brअन्यथा(*bhp);
	वापस शून्य;
पूर्ण

/*
 * Load dnode to memory and करो some checks
 */

काष्ठा dnode *hpfs_map_dnode(काष्ठा super_block *s, अचिन्हित secno,
			     काष्ठा quad_buffer_head *qbh)
अणु
	काष्ठा dnode *dnode;
	अगर (hpfs_sb(s)->sb_chk) अणु
		अगर (hpfs_chk_sectors(s, secno, 4, "dnode")) वापस शून्य;
		अगर (secno & 3) अणु
			hpfs_error(s, "dnode %08x not byte-aligned", secno);
			वापस शून्य;
		पूर्ण	
	पूर्ण
	अगर ((dnode = hpfs_map_4sectors(s, secno, qbh, DNODE_RD_AHEAD)))
		अगर (hpfs_sb(s)->sb_chk) अणु
			अचिन्हित p, pp = 0;
			अचिन्हित अक्षर *d = (अचिन्हित अक्षर *)dnode;
			पूर्णांक b = 0;
			अगर (le32_to_cpu(dnode->magic) != DNODE_MAGIC) अणु
				hpfs_error(s, "bad magic on dnode %08x", secno);
				जाओ bail;
			पूर्ण
			अगर (le32_to_cpu(dnode->self) != secno)
				hpfs_error(s, "bad self pointer on dnode %08x self = %08x", secno, le32_to_cpu(dnode->self));
			/* Check dirents - bad dirents would cause infinite
			   loops or shooting to memory */
			अगर (le32_to_cpu(dnode->first_मुक्त) > 2048) अणु
				hpfs_error(s, "dnode %08x has first_free == %08x", secno, le32_to_cpu(dnode->first_मुक्त));
				जाओ bail;
			पूर्ण
			क्रम (p = 20; p < le32_to_cpu(dnode->first_मुक्त); p += d[p] + (d[p+1] << 8)) अणु
				काष्ठा hpfs_dirent *de = (काष्ठा hpfs_dirent *)((अक्षर *)dnode + p);
				अगर (le16_to_cpu(de->length) > 292 || (le16_to_cpu(de->length) < 32) || (le16_to_cpu(de->length) & 3) || p + le16_to_cpu(de->length) > 2048) अणु
					hpfs_error(s, "bad dirent size in dnode %08x, dirent %03x, last %03x", secno, p, pp);
					जाओ bail;
				पूर्ण
				अगर (((31 + de->namelen + de->करोwn*4 + 3) & ~3) != le16_to_cpu(de->length)) अणु
					अगर (((31 + de->namelen + de->करोwn*4 + 3) & ~3) < le16_to_cpu(de->length) && s->s_flags & SB_RDONLY) जाओ ok;
					hpfs_error(s, "namelen does not match dirent size in dnode %08x, dirent %03x, last %03x", secno, p, pp);
					जाओ bail;
				पूर्ण
				ok:
				अगर (hpfs_sb(s)->sb_chk >= 2) b |= 1 << de->करोwn;
				अगर (de->करोwn) अगर (de_करोwn_poपूर्णांकer(de) < 0x10) अणु
					hpfs_error(s, "bad down pointer in dnode %08x, dirent %03x, last %03x", secno, p, pp);
					जाओ bail;
				पूर्ण
				pp = p;
				
			पूर्ण
			अगर (p != le32_to_cpu(dnode->first_मुक्त)) अणु
				hpfs_error(s, "size on last dirent does not match first_free; dnode %08x", secno);
				जाओ bail;
			पूर्ण
			अगर (d[pp + 30] != 1 || d[pp + 31] != 255) अणु
				hpfs_error(s, "dnode %08x does not end with \\377 entry", secno);
				जाओ bail;
			पूर्ण
			अगर (b == 3)
				pr_err("unbalanced dnode tree, dnode %08x; see hpfs.txt 4 more info\n",
					secno);
		पूर्ण
	वापस dnode;
	bail:
	hpfs_brअन्यथा4(qbh);
	वापस शून्य;
पूर्ण

dnode_secno hpfs_fnode_dno(काष्ठा super_block *s, ino_t ino)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	dnode_secno dno;

	fnode = hpfs_map_fnode(s, ino, &bh);
	अगर (!fnode)
		वापस 0;

	dno = le32_to_cpu(fnode->u.बाह्यal[0].disk_secno);
	brअन्यथा(bh);
	वापस dno;
पूर्ण
