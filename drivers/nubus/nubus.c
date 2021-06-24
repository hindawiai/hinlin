<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Macपूर्णांकosh Nubus Interface Code
 *
 *      Originally by Alan Cox
 *
 *      Mostly rewritten by David Huggins-Daines, C. Scott Ananian,
 *      and others.
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/माला.स>
#समावेश <linux/nubus.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/hwtest.h>

/* Constants */

/* This is, of course, the size in bytelanes, rather than the size in
   actual bytes */
#घोषणा FORMAT_BLOCK_SIZE 20
#घोषणा ROM_सूची_OFFSET 0x24

#घोषणा NUBUS_TEST_PATTERN 0x5A932BC7

/* Globals */

LIST_HEAD(nubus_func_rsrcs);

/* Meaning of "bytelanes":

   The card ROM may appear on any or all bytes of each दीर्घ word in
   NuBus memory.  The low 4 bits of the "map" value found in the
   क्रमmat block (at the top of the slot address space, as well as at
   the top of the MacOS ROM) tells us which bytelanes, i.e. which byte
   offsets within each दीर्घword, are valid.  Thus:

   A map of 0x0f, as found in the MacOS ROM, means that all bytelanes
   are valid.

   A map of 0xf0 means that no bytelanes are valid (We pray that we
   will never encounter this, but stranger things have happened)

   A map of 0xe1 means that only the MSB of each दीर्घ word is actually
   part of the card ROM.  (We hope to never encounter NuBus on a
   little-endian machine.  Again, stranger things have happened)

   A map of 0x78 means that only the LSB of each दीर्घ word is valid.

   Etcetera, etcetera.  Hopefully this clears up some confusion over
   what the following code actually करोes.  */

अटल अंतरभूत पूर्णांक not_useful(व्योम *p, पूर्णांक map)
अणु
	अचिन्हित दीर्घ pv = (अचिन्हित दीर्घ)p;

	pv &= 3;
	अगर (map & (1 << pv))
		वापस 0;
	वापस 1;
पूर्ण

अटल अचिन्हित दीर्घ nubus_get_rom(अचिन्हित अक्षर **ptr, पूर्णांक len, पूर्णांक map)
अणु
	/* This will hold the result */
	अचिन्हित दीर्घ v = 0;
	अचिन्हित अक्षर *p = *ptr;

	जबतक (len) अणु
		v <<= 8;
		जबतक (not_useful(p, map))
			p++;
		v |= *p++;
		len--;
	पूर्ण
	*ptr = p;
	वापस v;
पूर्ण

अटल व्योम nubus_शुरुआत(अचिन्हित अक्षर **ptr, पूर्णांक len, पूर्णांक map)
अणु
	अचिन्हित अक्षर *p = *ptr;

	जबतक (len) अणु
		करो अणु
			p--;
		पूर्ण जबतक (not_useful(p, map));
		len--;
	पूर्ण
	*ptr = p;
पूर्ण

अटल व्योम nubus_advance(अचिन्हित अक्षर **ptr, पूर्णांक len, पूर्णांक map)
अणु
	अचिन्हित अक्षर *p = *ptr;

	जबतक (len) अणु
		जबतक (not_useful(p, map))
			p++;
		p++;
		len--;
	पूर्ण
	*ptr = p;
पूर्ण

अटल व्योम nubus_move(अचिन्हित अक्षर **ptr, पूर्णांक len, पूर्णांक map)
अणु
	अचिन्हित दीर्घ slot_space = (अचिन्हित दीर्घ)*ptr & 0xFF000000;

	अगर (len > 0)
		nubus_advance(ptr, len, map);
	अन्यथा अगर (len < 0)
		nubus_शुरुआत(ptr, -len, map);

	अगर (((अचिन्हित दीर्घ)*ptr & 0xFF000000) != slot_space)
		pr_err("%s: moved out of slot address space!\n", __func__);
पूर्ण

/* Now, functions to पढ़ो the sResource tree */

/* Each sResource entry consists of a 1-byte ID and a 3-byte data
   field.  If that data field contains an offset, then obviously we
   have to expand it from a 24-bit चिन्हित number to a 32-bit चिन्हित
   number. */

अटल अंतरभूत दीर्घ nubus_expand32(दीर्घ foo)
अणु
	अगर (foo & 0x00800000)	/* 24bit negative */
		foo |= 0xFF000000;
	वापस foo;
पूर्ण

अटल अंतरभूत व्योम *nubus_rom_addr(पूर्णांक slot)
अणु
	/*
	 *	Returns the first byte after the card. We then walk
	 *	backwards to get the lane रेजिस्टर and the config
	 */
	वापस (व्योम *)(0xF1000000 + (slot << 24));
पूर्ण

अचिन्हित अक्षर *nubus_dirptr(स्थिर काष्ठा nubus_dirent *nd)
अणु
	अचिन्हित अक्षर *p = nd->base;

	/* Essentially, just step over the bytelanes using whatever
	   offset we might have found */
	nubus_move(&p, nubus_expand32(nd->data), nd->mask);
	/* And वापस the value */
	वापस p;
पूर्ण

/* These two are क्रम pulling resource data blocks (i.e. stuff that's
   poपूर्णांकed to with offsets) out of the card ROM. */

व्योम nubus_get_rsrc_mem(व्योम *dest, स्थिर काष्ठा nubus_dirent *dirent,
			अचिन्हित पूर्णांक len)
अणु
	अचिन्हित अक्षर *t = dest;
	अचिन्हित अक्षर *p = nubus_dirptr(dirent);

	जबतक (len) अणु
		*t++ = nubus_get_rom(&p, 1, dirent->mask);
		len--;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(nubus_get_rsrc_mem);

अचिन्हित पूर्णांक nubus_get_rsrc_str(अक्षर *dest, स्थिर काष्ठा nubus_dirent *dirent,
				अचिन्हित पूर्णांक len)
अणु
	अक्षर *t = dest;
	अचिन्हित अक्षर *p = nubus_dirptr(dirent);

	जबतक (len > 1) अणु
		अचिन्हित अक्षर c = nubus_get_rom(&p, 1, dirent->mask);

		अगर (!c)
			अवरोध;
		*t++ = c;
		len--;
	पूर्ण
	अगर (len > 0)
		*t = '\0';
	वापस t - dest;
पूर्ण
EXPORT_SYMBOL(nubus_get_rsrc_str);

व्योम nubus_seq_ग_लिखो_rsrc_mem(काष्ठा seq_file *m,
			      स्थिर काष्ठा nubus_dirent *dirent,
			      अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ buf[32];
	अचिन्हित पूर्णांक buf_size = माप(buf);
	अचिन्हित अक्षर *p = nubus_dirptr(dirent);

	/* If possible, ग_लिखो out full buffers */
	जबतक (len >= buf_size) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ARRAY_SIZE(buf); i++)
			buf[i] = nubus_get_rom(&p, माप(buf[0]),
					       dirent->mask);
		seq_ग_लिखो(m, buf, buf_size);
		len -= buf_size;
	पूर्ण
	/* If not, ग_लिखो out inभागidual bytes */
	जबतक (len--)
		seq_अ_दो(m, nubus_get_rom(&p, 1, dirent->mask));
पूर्ण

पूर्णांक nubus_get_root_dir(स्थिर काष्ठा nubus_board *board,
		       काष्ठा nubus_dir *dir)
अणु
	dir->ptr = dir->base = board->directory;
	dir->करोne = 0;
	dir->mask = board->lanes;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nubus_get_root_dir);

/* This is a slyly नामd version of the above */
पूर्णांक nubus_get_func_dir(स्थिर काष्ठा nubus_rsrc *fres, काष्ठा nubus_dir *dir)
अणु
	dir->ptr = dir->base = fres->directory;
	dir->करोne = 0;
	dir->mask = fres->board->lanes;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nubus_get_func_dir);

पूर्णांक nubus_get_board_dir(स्थिर काष्ठा nubus_board *board,
			काष्ठा nubus_dir *dir)
अणु
	काष्ठा nubus_dirent ent;

	dir->ptr = dir->base = board->directory;
	dir->करोne = 0;
	dir->mask = board->lanes;

	/* Now dereference it (the first directory is always the board
	   directory) */
	अगर (nubus_सूची_पढ़ो(dir, &ent) == -1)
		वापस -1;
	अगर (nubus_get_subdir(&ent, dir) == -1)
		वापस -1;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nubus_get_board_dir);

पूर्णांक nubus_get_subdir(स्थिर काष्ठा nubus_dirent *ent,
		     काष्ठा nubus_dir *dir)
अणु
	dir->ptr = dir->base = nubus_dirptr(ent);
	dir->करोne = 0;
	dir->mask = ent->mask;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nubus_get_subdir);

पूर्णांक nubus_सूची_पढ़ो(काष्ठा nubus_dir *nd, काष्ठा nubus_dirent *ent)
अणु
	u32 resid;

	अगर (nd->करोne)
		वापस -1;

	/* Do this first, otherwise nubus_शुरुआत & co are off by 4 */
	ent->base = nd->ptr;

	/* This moves nd->ptr क्रमward */
	resid = nubus_get_rom(&nd->ptr, 4, nd->mask);

	/* EOL marker, as per the Apple करोcs */
	अगर ((resid & 0xff000000) == 0xff000000) अणु
		/* Mark it as करोne */
		nd->करोne = 1;
		वापस -1;
	पूर्ण

	/* First byte is the resource ID */
	ent->type = resid >> 24;
	/* Low 3 bytes might contain data (or might not) */
	ent->data = resid & 0xffffff;
	ent->mask = nd->mask;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nubus_सूची_पढ़ो);

पूर्णांक nubus_सूची_शुरु(काष्ठा nubus_dir *dir)
अणु
	dir->ptr = dir->base;
	dir->करोne = 0;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(nubus_सूची_शुरु);

/* Driver पूर्णांकerface functions, more or less like in pci.c */

काष्ठा nubus_rsrc *nubus_first_rsrc_or_null(व्योम)
अणु
	वापस list_first_entry_or_null(&nubus_func_rsrcs, काष्ठा nubus_rsrc,
					list);
पूर्ण
EXPORT_SYMBOL(nubus_first_rsrc_or_null);

काष्ठा nubus_rsrc *nubus_next_rsrc_or_null(काष्ठा nubus_rsrc *from)
अणु
	अगर (list_is_last(&from->list, &nubus_func_rsrcs))
		वापस शून्य;
	वापस list_next_entry(from, list);
पूर्ण
EXPORT_SYMBOL(nubus_next_rsrc_or_null);

पूर्णांक
nubus_find_rsrc(काष्ठा nubus_dir *dir, अचिन्हित अक्षर rsrc_type,
		काष्ठा nubus_dirent *ent)
अणु
	जबतक (nubus_सूची_पढ़ो(dir, ent) != -1) अणु
		अगर (ent->type == rsrc_type)
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण
EXPORT_SYMBOL(nubus_find_rsrc);

/* Initialization functions - decide which slots contain stuff worth
   looking at, and prपूर्णांक out lots and lots of inक्रमmation from the
   resource blocks. */

अटल पूर्णांक __init nubus_get_block_rsrc_dir(काष्ठा nubus_board *board,
					   काष्ठा proc_dir_entry *procdir,
					   स्थिर काष्ठा nubus_dirent *parent)
अणु
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;

	nubus_get_subdir(parent, &dir);
	dir.procdir = nubus_proc_add_rsrc_dir(procdir, parent, board);

	जबतक (nubus_सूची_पढ़ो(&dir, &ent) != -1) अणु
		u32 size;

		nubus_get_rsrc_mem(&size, &ent, 4);
		pr_debug("        block (0x%x), size %d\n", ent.type, size);
		nubus_proc_add_rsrc_mem(dir.procdir, &ent, size);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_display_vidmode(काष्ठा nubus_board *board,
					    काष्ठा proc_dir_entry *procdir,
					    स्थिर काष्ठा nubus_dirent *parent)
अणु
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;

	nubus_get_subdir(parent, &dir);
	dir.procdir = nubus_proc_add_rsrc_dir(procdir, parent, board);

	जबतक (nubus_सूची_पढ़ो(&dir, &ent) != -1) अणु
		चयन (ent.type) अणु
		हाल 1: /* mVidParams */
		हाल 2: /* mTable */
		अणु
			u32 size;

			nubus_get_rsrc_mem(&size, &ent, 4);
			pr_debug("        block (0x%x), size %d\n", ent.type,
				size);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, size);
			अवरोध;
		पूर्ण
		शेष:
			pr_debug("        unknown resource 0x%02x, data 0x%06x\n",
				ent.type, ent.data);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_display_resource(काष्ठा nubus_rsrc *fres,
					     काष्ठा proc_dir_entry *procdir,
					     स्थिर काष्ठा nubus_dirent *ent)
अणु
	चयन (ent->type) अणु
	हाल NUBUS_RESID_GAMMAसूची:
		pr_debug("    gamma directory offset: 0x%06x\n", ent->data);
		nubus_get_block_rsrc_dir(fres->board, procdir, ent);
		अवरोध;
	हाल 0x0080 ... 0x0085:
		pr_debug("    mode 0x%02x info offset: 0x%06x\n",
			ent->type, ent->data);
		nubus_get_display_vidmode(fres->board, procdir, ent);
		अवरोध;
	शेष:
		pr_debug("    unknown resource 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_proc_add_rsrc_mem(procdir, ent, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_network_resource(काष्ठा nubus_rsrc *fres,
					     काष्ठा proc_dir_entry *procdir,
					     स्थिर काष्ठा nubus_dirent *ent)
अणु
	चयन (ent->type) अणु
	हाल NUBUS_RESID_MAC_ADDRESS:
	अणु
		अक्षर addr[6];

		nubus_get_rsrc_mem(addr, ent, 6);
		pr_debug("    MAC address: %pM\n", addr);
		nubus_proc_add_rsrc_mem(procdir, ent, 6);
		अवरोध;
	पूर्ण
	शेष:
		pr_debug("    unknown resource 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_proc_add_rsrc_mem(procdir, ent, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_cpu_resource(काष्ठा nubus_rsrc *fres,
					 काष्ठा proc_dir_entry *procdir,
					 स्थिर काष्ठा nubus_dirent *ent)
अणु
	चयन (ent->type) अणु
	हाल NUBUS_RESID_MEMINFO:
	अणु
		अचिन्हित दीर्घ meminfo[2];

		nubus_get_rsrc_mem(&meminfo, ent, 8);
		pr_debug("    memory: [ 0x%08lx 0x%08lx ]\n",
			meminfo[0], meminfo[1]);
		nubus_proc_add_rsrc_mem(procdir, ent, 8);
		अवरोध;
	पूर्ण
	हाल NUBUS_RESID_ROMINFO:
	अणु
		अचिन्हित दीर्घ rominfo[2];

		nubus_get_rsrc_mem(&rominfo, ent, 8);
		pr_debug("    ROM:    [ 0x%08lx 0x%08lx ]\n",
			rominfo[0], rominfo[1]);
		nubus_proc_add_rsrc_mem(procdir, ent, 8);
		अवरोध;
	पूर्ण
	शेष:
		pr_debug("    unknown resource 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_proc_add_rsrc_mem(procdir, ent, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_निजी_resource(काष्ठा nubus_rsrc *fres,
					     काष्ठा proc_dir_entry *procdir,
					     स्थिर काष्ठा nubus_dirent *ent)
अणु
	चयन (fres->category) अणु
	हाल NUBUS_CAT_DISPLAY:
		nubus_get_display_resource(fres, procdir, ent);
		अवरोध;
	हाल NUBUS_CAT_NETWORK:
		nubus_get_network_resource(fres, procdir, ent);
		अवरोध;
	हाल NUBUS_CAT_CPU:
		nubus_get_cpu_resource(fres, procdir, ent);
		अवरोध;
	शेष:
		pr_debug("    unknown resource 0x%02x, data 0x%06x\n",
			ent->type, ent->data);
		nubus_proc_add_rsrc_mem(procdir, ent, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा nubus_rsrc * __init
nubus_get_functional_resource(काष्ठा nubus_board *board, पूर्णांक slot,
			      स्थिर काष्ठा nubus_dirent *parent)
अणु
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;
	काष्ठा nubus_rsrc *fres;

	pr_debug("  Functional resource 0x%02x:\n", parent->type);
	nubus_get_subdir(parent, &dir);
	dir.procdir = nubus_proc_add_rsrc_dir(board->procdir, parent, board);

	/* Actually we should probably panic अगर this fails */
	fres = kzalloc(माप(*fres), GFP_ATOMIC);
	अगर (!fres)
		वापस शून्य;
	fres->resid = parent->type;
	fres->directory = dir.base;
	fres->board = board;

	जबतक (nubus_सूची_पढ़ो(&dir, &ent) != -1) अणु
		चयन (ent.type) अणु
		हाल NUBUS_RESID_TYPE:
		अणु
			अचिन्हित लघु nbtdata[4];

			nubus_get_rsrc_mem(nbtdata, &ent, 8);
			fres->category = nbtdata[0];
			fres->type     = nbtdata[1];
			fres->dr_sw    = nbtdata[2];
			fres->dr_hw    = nbtdata[3];
			pr_debug("    type: [cat 0x%x type 0x%x sw 0x%x hw 0x%x]\n",
				nbtdata[0], nbtdata[1], nbtdata[2], nbtdata[3]);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, 8);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_NAME:
		अणु
			अक्षर name[64];
			अचिन्हित पूर्णांक len;

			len = nubus_get_rsrc_str(name, &ent, माप(name));
			pr_debug("    name: %s\n", name);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, len + 1);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_DRVRसूची:
		अणु
			/* MacOS driver.  If we were NetBSD we might
			   use this :-) */
			pr_debug("    driver directory offset: 0x%06x\n",
				ent.data);
			nubus_get_block_rsrc_dir(board, dir.procdir, &ent);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_MINOR_BASEOS:
		अणु
			/* We will need this in order to support
			   multiple framebuffers.  It might be handy
			   क्रम Ethernet as well */
			u32 base_offset;

			nubus_get_rsrc_mem(&base_offset, &ent, 4);
			pr_debug("    memory offset: 0x%08x\n", base_offset);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, 4);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_MINOR_LENGTH:
		अणु
			/* Ditto */
			u32 length;

			nubus_get_rsrc_mem(&length, &ent, 4);
			pr_debug("    memory length: 0x%08x\n", length);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, 4);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_FLAGS:
			pr_debug("    flags: 0x%06x\n", ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_HWDEVID:
			pr_debug("    hwdevid: 0x%06x\n", ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		शेष:
			/* Local/Private resources have their own
			   function */
			nubus_get_निजी_resource(fres, dir.procdir, &ent);
		पूर्ण
	पूर्ण

	वापस fres;
पूर्ण

/* This is *really* cool. */
अटल पूर्णांक __init nubus_get_icon(काष्ठा nubus_board *board,
				 काष्ठा proc_dir_entry *procdir,
				 स्थिर काष्ठा nubus_dirent *ent)
अणु
	/* Should be 32x32 अगर my memory serves me correctly */
	u32 icon[32];
	पूर्णांक i;

	nubus_get_rsrc_mem(&icon, ent, 128);
	pr_debug("    icon:\n");
	क्रम (i = 0; i < 8; i++)
		pr_debug("        %08x %08x %08x %08x\n",
			icon[i * 4 + 0], icon[i * 4 + 1],
			icon[i * 4 + 2], icon[i * 4 + 3]);
	nubus_proc_add_rsrc_mem(procdir, ent, 128);

	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_venकरोrinfo(काष्ठा nubus_board *board,
				       काष्ठा proc_dir_entry *procdir,
				       स्थिर काष्ठा nubus_dirent *parent)
अणु
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;
	अटल अक्षर *venकरोr_fields[6] = अणु "ID", "serial", "revision",
	                                  "part", "date", "unknown field" पूर्ण;

	pr_debug("    vendor info:\n");
	nubus_get_subdir(parent, &dir);
	dir.procdir = nubus_proc_add_rsrc_dir(procdir, parent, board);

	जबतक (nubus_सूची_पढ़ो(&dir, &ent) != -1) अणु
		अक्षर name[64];
		अचिन्हित पूर्णांक len;

		/* These are all strings, we think */
		len = nubus_get_rsrc_str(name, &ent, माप(name));
		अगर (ent.type < 1 || ent.type > 5)
			ent.type = 5;
		pr_debug("    %s: %s\n", venकरोr_fields[ent.type - 1], name);
		nubus_proc_add_rsrc_mem(dir.procdir, &ent, len + 1);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक __init nubus_get_board_resource(काष्ठा nubus_board *board, पूर्णांक slot,
					   स्थिर काष्ठा nubus_dirent *parent)
अणु
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;

	pr_debug("  Board resource 0x%02x:\n", parent->type);
	nubus_get_subdir(parent, &dir);
	dir.procdir = nubus_proc_add_rsrc_dir(board->procdir, parent, board);

	जबतक (nubus_सूची_पढ़ो(&dir, &ent) != -1) अणु
		चयन (ent.type) अणु
		हाल NUBUS_RESID_TYPE:
		अणु
			अचिन्हित लघु nbtdata[4];
			/* This type is always the same, and is not
			   useful except insofar as it tells us that
			   we really are looking at a board resource. */
			nubus_get_rsrc_mem(nbtdata, &ent, 8);
			pr_debug("    type: [cat 0x%x type 0x%x sw 0x%x hw 0x%x]\n",
				nbtdata[0], nbtdata[1], nbtdata[2], nbtdata[3]);
			अगर (nbtdata[0] != 1 || nbtdata[1] != 0 ||
			    nbtdata[2] != 0 || nbtdata[3] != 0)
				pr_err("Slot %X: sResource is not a board resource!\n",
				       slot);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, 8);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_NAME:
		अणु
			अचिन्हित पूर्णांक len;

			len = nubus_get_rsrc_str(board->name, &ent,
						 माप(board->name));
			pr_debug("    name: %s\n", board->name);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, len + 1);
			अवरोध;
		पूर्ण
		हाल NUBUS_RESID_ICON:
			nubus_get_icon(board, dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_BOARDID:
			pr_debug("    board id: 0x%x\n", ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_PRIMARYINIT:
			pr_debug("    primary init offset: 0x%06x\n", ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_VENDORINFO:
			nubus_get_venकरोrinfo(board, dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_FLAGS:
			pr_debug("    flags: 0x%06x\n", ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_HWDEVID:
			pr_debug("    hwdevid: 0x%06x\n", ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		हाल NUBUS_RESID_SECONDINIT:
			pr_debug("    secondary init offset: 0x%06x\n",
				 ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
			/* WTF isn't this in the functional resources? */
		हाल NUBUS_RESID_VIDNAMES:
			pr_debug("    vidnames directory offset: 0x%06x\n",
				ent.data);
			nubus_get_block_rsrc_dir(board, dir.procdir, &ent);
			अवरोध;
			/* Same goes क्रम this */
		हाल NUBUS_RESID_VIDMODES:
			pr_debug("    video mode parameter directory offset: 0x%06x\n",
				ent.data);
			nubus_proc_add_rsrc(dir.procdir, &ent);
			अवरोध;
		शेष:
			pr_debug("    unknown resource 0x%02x, data 0x%06x\n",
				ent.type, ent.data);
			nubus_proc_add_rsrc_mem(dir.procdir, &ent, 0);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __init nubus_add_board(पूर्णांक slot, पूर्णांक bytelanes)
अणु
	काष्ठा nubus_board *board;
	अचिन्हित अक्षर *rp;
	अचिन्हित दीर्घ dpat;
	काष्ठा nubus_dir dir;
	काष्ठा nubus_dirent ent;
	पूर्णांक prev_resid = -1;

	/* Move to the start of the क्रमmat block */
	rp = nubus_rom_addr(slot);
	nubus_शुरुआत(&rp, FORMAT_BLOCK_SIZE, bytelanes);

	/* Actually we should probably panic अगर this fails */
	अगर ((board = kzalloc(माप(*board), GFP_ATOMIC)) == शून्य)
		वापस;
	board->fblock = rp;

	/* Dump the क्रमmat block क्रम debugging purposes */
	pr_debug("Slot %X, format block at 0x%p:\n", slot, rp);
	pr_debug("%08lx\n", nubus_get_rom(&rp, 4, bytelanes));
	pr_debug("%08lx\n", nubus_get_rom(&rp, 4, bytelanes));
	pr_debug("%08lx\n", nubus_get_rom(&rp, 4, bytelanes));
	pr_debug("%02lx\n", nubus_get_rom(&rp, 1, bytelanes));
	pr_debug("%02lx\n", nubus_get_rom(&rp, 1, bytelanes));
	pr_debug("%08lx\n", nubus_get_rom(&rp, 4, bytelanes));
	pr_debug("%02lx\n", nubus_get_rom(&rp, 1, bytelanes));
	pr_debug("%02lx\n", nubus_get_rom(&rp, 1, bytelanes));
	rp = board->fblock;

	board->slot = slot;
	board->slot_addr = (अचिन्हित दीर्घ)nubus_slot_addr(slot);
	board->करोffset = nubus_get_rom(&rp, 4, bytelanes);
	/* rom_length is *supposed* to be the total length of the
	 * ROM.  In practice it is the "amount of ROM used to compute
	 * the CRC."  So some jokers decide to set it to zero and
	 * set the crc to zero so they करोn't have to करो any math.
	 * See the Perक्रमma 460 ROM, क्रम example.  Those Apple "engineers".
	 */
	board->rom_length = nubus_get_rom(&rp, 4, bytelanes);
	board->crc = nubus_get_rom(&rp, 4, bytelanes);
	board->rev = nubus_get_rom(&rp, 1, bytelanes);
	board->क्रमmat = nubus_get_rom(&rp, 1, bytelanes);
	board->lanes = bytelanes;

	/* Directory offset should be small and negative... */
	अगर (!(board->करोffset & 0x00FF0000))
		pr_warn("Slot %X: Dodgy doffset!\n", slot);
	dpat = nubus_get_rom(&rp, 4, bytelanes);
	अगर (dpat != NUBUS_TEST_PATTERN)
		pr_warn("Slot %X: Wrong test pattern %08lx!\n", slot, dpat);

	/*
	 *	I wonder how the CRC is meant to work -
	 *		any takers ?
	 * CSA: According to MAC करोcs, not all cards pass the CRC anyway,
	 * since the initial Macपूर्णांकosh ROM releases skipped the check.
	 */

	/* Set up the directory poपूर्णांकer */
	board->directory = board->fblock;
	nubus_move(&board->directory, nubus_expand32(board->करोffset),
	           board->lanes);

	nubus_get_root_dir(board, &dir);

	/* We're पढ़ोy to rock */
	pr_debug("Slot %X resources:\n", slot);

	/* Each slot should have one board resource and any number of
	 * functional resources.  So we'll fill in some fields in the
	 * काष्ठा nubus_board from the board resource, then walk करोwn
	 * the list of functional resources, spinning out a nubus_rsrc
	 * क्रम each of them.
	 */
	अगर (nubus_सूची_पढ़ो(&dir, &ent) == -1) अणु
		/* We can't have this! */
		pr_err("Slot %X: Board resource not found!\n", slot);
		kमुक्त(board);
		वापस;
	पूर्ण

	अगर (ent.type < 1 || ent.type > 127)
		pr_warn("Slot %X: Board resource ID is invalid!\n", slot);

	board->procdir = nubus_proc_add_board(board);

	nubus_get_board_resource(board, slot, &ent);

	जबतक (nubus_सूची_पढ़ो(&dir, &ent) != -1) अणु
		काष्ठा nubus_rsrc *fres;

		fres = nubus_get_functional_resource(board, slot, &ent);
		अगर (fres == शून्य)
			जारी;

		/* Resources should appear in ascending ID order. This sanity
		 * check prevents duplicate resource IDs.
		 */
		अगर (fres->resid <= prev_resid) अणु
			kमुक्त(fres);
			जारी;
		पूर्ण
		prev_resid = fres->resid;

		list_add_tail(&fres->list, &nubus_func_rsrcs);
	पूर्ण

	अगर (nubus_device_रेजिस्टर(board))
		put_device(&board->dev);
पूर्ण

अटल व्योम __init nubus_probe_slot(पूर्णांक slot)
अणु
	अचिन्हित अक्षर dp;
	अचिन्हित अक्षर *rp;
	पूर्णांक i;

	rp = nubus_rom_addr(slot);
	क्रम (i = 4; i; i--) अणु
		rp--;
		अगर (!hwreg_present(rp))
			जारी;

		dp = *rp;

		/* The last byte of the क्रमmat block consists of two
		   nybbles which are "mirror images" of each other.
		   These show us the valid bytelanes */
		अगर ((((dp >> 4) ^ dp) & 0x0F) != 0x0F)
			जारी;
		/* Check that this value is actually *on* one of the
		   bytelanes it claims are valid! */
		अगर (not_useful(rp, dp))
			जारी;

		/* Looks promising.  Let's put it on the list. */
		nubus_add_board(slot, dp);

		वापस;
	पूर्ण
पूर्ण

अटल व्योम __init nubus_scan_bus(व्योम)
अणु
	पूर्णांक slot;

	pr_info("NuBus: Scanning NuBus slots.\n");
	क्रम (slot = 9; slot < 15; slot++) अणु
		nubus_probe_slot(slot);
	पूर्ण
पूर्ण

अटल पूर्णांक __init nubus_init(व्योम)
अणु
	पूर्णांक err;

	अगर (!MACH_IS_MAC)
		वापस 0;

	nubus_proc_init();
	err = nubus_parent_device_रेजिस्टर();
	अगर (err)
		वापस err;
	nubus_scan_bus();
	वापस 0;
पूर्ण

subsys_initcall(nubus_init);
