<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Read flash partition table from command line
 *
 * Copyright तऊ 2002      SYSGO Real-Time Solutions GmbH
 * Copyright तऊ 2002-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * The क्रमmat क्रम the command line is as follows:
 *
 * mtdparts=<mtddef>[;<mtddef]
 * <mtddef>  := <mtd-id>:<partdef>[,<partdef>]
 * <partdef> := <size>[@<offset>][<name>][ro][lk][slc]
 * <mtd-id>  := unique name used in mapping driver/device (mtd->name)
 * <size>    := standard linux memsize OR "-" to denote all reमुख्यing space
 *              size is स्वतःmatically truncated at end of device
 *              अगर specअगरied or truncated size is 0 the part is skipped
 * <offset>  := standard linux memsize
 *              अगर omitted the part will immediately follow the previous part
 *              or 0 अगर the first part
 * <name>    := '(' NAME ')'
 *              NAME will appear in /proc/mtd
 *
 * <size> and <offset> can be specअगरied such that the parts are out of order
 * in physical memory and may even overlap.
 *
 * The parts are asचिन्हित MTD numbers in the order they are specअगरied in the
 * command line regardless of their order in physical memory.
 *
 * Examples:
 *
 * 1 NOR Flash, with 1 single writable partition:
 * edb7312-nor:-
 *
 * 1 NOR Flash with 2 partitions, 1 न_अंकD with one
 * edb7312-nor:256k(ARMboot)ro,-(root);edb7312-nand:-(home)
 */

#घोषणा pr_fmt(fmt)	"mtd: " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>

/* debug macro */
#अगर 0
#घोषणा dbg(x) करो अणु prपूर्णांकk("DEBUG-CMDLINE-PART: "); prपूर्णांकk x; पूर्ण जबतक(0)
#अन्यथा
#घोषणा dbg(x)
#पूर्ण_अगर


/* special size referring to all the reमुख्यing space in a partition */
#घोषणा SIZE_REMAINING ULदीर्घ_उच्च
#घोषणा OFFSET_CONTINUOUS ULदीर्घ_उच्च

काष्ठा cmdline_mtd_partition अणु
	काष्ठा cmdline_mtd_partition *next;
	अक्षर *mtd_id;
	पूर्णांक num_parts;
	काष्ठा mtd_partition *parts;
पूर्ण;

/* mtdpart_setup() parses पूर्णांकo here */
अटल काष्ठा cmdline_mtd_partition *partitions;

/* the command line passed to mtdpart_setup() */
अटल अक्षर *mtdparts;
अटल अक्षर *cmdline;
अटल पूर्णांक cmdline_parsed;

/*
 * Parse one partition definition क्रम an MTD. Since there can be many
 * comma separated partition definitions, this function calls itself
 * recursively until no more partition definitions are found. Nice side
 * effect: the memory to keep the mtd_partition काष्ठाs and the names
 * is allocated upon the last definition being found. At that poपूर्णांक the
 * syntax has been verअगरied ok.
 */
अटल काष्ठा mtd_partition * newpart(अक्षर *s,
				      अक्षर **retptr,
				      पूर्णांक *num_parts,
				      पूर्णांक this_part,
				      अचिन्हित अक्षर **extra_mem_ptr,
				      पूर्णांक extra_mem_size)
अणु
	काष्ठा mtd_partition *parts;
	अचिन्हित दीर्घ दीर्घ size, offset = OFFSET_CONTINUOUS;
	अक्षर *name;
	पूर्णांक name_len;
	अचिन्हित अक्षर *extra_mem;
	अक्षर delim;
	अचिन्हित पूर्णांक mask_flags, add_flags;

	/* fetch the partition size */
	अगर (*s == '-') अणु
		/* assign all reमुख्यing space to this partition */
		size = SIZE_REMAINING;
		s++;
	पूर्ण अन्यथा अणु
		size = memparse(s, &s);
		अगर (!size) अणु
			pr_err("partition has size 0\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
	पूर्ण

	/* fetch partition name and flags */
	mask_flags = 0; /* this is going to be a regular partition */
	add_flags = 0;
	delim = 0;

	/* check क्रम offset */
	अगर (*s == '@') अणु
		s++;
		offset = memparse(s, &s);
	पूर्ण

	/* now look क्रम name */
	अगर (*s == '(')
		delim = ')';

	अगर (delim) अणु
		अक्षर *p;

		name = ++s;
		p = म_अक्षर(name, delim);
		अगर (!p) अणु
			pr_err("no closing %c found in partition name\n", delim);
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		name_len = p - name;
		s = p + 1;
	पूर्ण अन्यथा अणु
		name = शून्य;
		name_len = 13; /* Partition_000 */
	पूर्ण

	/* record name length क्रम memory allocation later */
	extra_mem_size += name_len + 1;

	/* test क्रम options */
	अगर (म_भेदन(s, "ro", 2) == 0) अणु
		mask_flags |= MTD_WRITEABLE;
		s += 2;
	पूर्ण

	/* अगर lk is found करो NOT unlock the MTD partition*/
	अगर (म_भेदन(s, "lk", 2) == 0) अणु
		mask_flags |= MTD_POWERUP_LOCK;
		s += 2;
	पूर्ण

	/* अगर slc is found use emulated SLC mode on this partition*/
	अगर (!म_भेदन(s, "slc", 3)) अणु
		add_flags |= MTD_SLC_ON_MLC_EMULATION;
		s += 3;
	पूर्ण

	/* test अगर more partitions are following */
	अगर (*s == ',') अणु
		अगर (size == SIZE_REMAINING) अणु
			pr_err("no partitions allowed after a fill-up partition\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण
		/* more partitions follow, parse them */
		parts = newpart(s + 1, &s, num_parts, this_part + 1,
				&extra_mem, extra_mem_size);
		अगर (IS_ERR(parts))
			वापस parts;
	पूर्ण अन्यथा अणु
		/* this is the last partition: allocate space क्रम all */
		पूर्णांक alloc_size;

		*num_parts = this_part + 1;
		alloc_size = *num_parts * माप(काष्ठा mtd_partition) +
			     extra_mem_size;

		parts = kzalloc(alloc_size, GFP_KERNEL);
		अगर (!parts)
			वापस ERR_PTR(-ENOMEM);
		extra_mem = (अचिन्हित अक्षर *)(parts + *num_parts);
	पूर्ण

	/*
	 * enter this partition (offset will be calculated later अगर it is
	 * OFFSET_CONTINUOUS at this poपूर्णांक)
	 */
	parts[this_part].size = size;
	parts[this_part].offset = offset;
	parts[this_part].mask_flags = mask_flags;
	parts[this_part].add_flags = add_flags;
	अगर (name)
		strlcpy(extra_mem, name, name_len + 1);
	अन्यथा
		प्र_लिखो(extra_mem, "Partition_%03d", this_part);
	parts[this_part].name = extra_mem;
	extra_mem += name_len + 1;

	dbg(("partition %d: name <%s>, offset %llx, size %llx, mask flags %x\n",
	     this_part, parts[this_part].name, parts[this_part].offset,
	     parts[this_part].size, parts[this_part].mask_flags));

	/* वापस (updated) poपूर्णांकer to extra_mem memory */
	अगर (extra_mem_ptr)
		*extra_mem_ptr = extra_mem;

	/* वापस (updated) poपूर्णांकer command line string */
	*retptr = s;

	/* वापस partition table */
	वापस parts;
पूर्ण

/*
 * Parse the command line.
 */
अटल पूर्णांक mtdpart_setup_real(अक्षर *s)
अणु
	cmdline_parsed = 1;

	क्रम( ; s != शून्य; )
	अणु
		काष्ठा cmdline_mtd_partition *this_mtd;
		काष्ठा mtd_partition *parts;
		पूर्णांक mtd_id_len, num_parts;
		अक्षर *p, *mtd_id, *semicol, *खोलो_parenth;

		/*
		 * Replace the first ';' by a शून्य अक्षर so म_खोजप can work
		 * properly.
		 */
		semicol = म_अक्षर(s, ';');
		अगर (semicol)
			*semicol = '\0';

		/*
		 * make sure that part-names with ":" will not be handled as
		 * part of the mtd-id with an ":"
		 */
		खोलो_parenth = म_अक्षर(s, '(');
		अगर (खोलो_parenth)
			*खोलो_parenth = '\0';

		mtd_id = s;

		/*
		 * fetch <mtd-id>. We use म_खोजप to ignore all ':' that could
		 * be present in the MTD name, only the last one is पूर्णांकerpreted
		 * as an <mtd-id>/<part-definition> separator.
		 */
		p = म_खोजप(s, ':');

		/* Restore the '(' now. */
		अगर (खोलो_parenth)
			*खोलो_parenth = '(';

		/* Restore the ';' now. */
		अगर (semicol)
			*semicol = ';';

		अगर (!p) अणु
			pr_err("no mtd-id\n");
			वापस -EINVAL;
		पूर्ण
		mtd_id_len = p - mtd_id;

		dbg(("parsing <%s>\n", p+1));

		/*
		 * parse one mtd. have it reserve memory क्रम the
		 * काष्ठा cmdline_mtd_partition and the mtd-id string.
		 */
		parts = newpart(p + 1,		/* cmdline */
				&s,		/* out: updated cmdline ptr */
				&num_parts,	/* out: number of parts */
				0,		/* first partition */
				(अचिन्हित अक्षर**)&this_mtd, /* out: extra mem */
				mtd_id_len + 1 + माप(*this_mtd) +
				माप(व्योम*)-1 /*alignment*/);
		अगर (IS_ERR(parts)) अणु
			/*
			 * An error occurred. We're either:
			 * a) out of memory, or
			 * b) in the middle of the partition spec
			 * Either way, this mtd is hosed and we're
			 * unlikely to succeed in parsing any more
			 */
			 वापस PTR_ERR(parts);
		 पूर्ण

		/* align this_mtd */
		this_mtd = (काष्ठा cmdline_mtd_partition *)
				ALIGN((अचिन्हित दीर्घ)this_mtd, माप(व्योम *));
		/* enter results */
		this_mtd->parts = parts;
		this_mtd->num_parts = num_parts;
		this_mtd->mtd_id = (अक्षर*)(this_mtd + 1);
		strlcpy(this_mtd->mtd_id, mtd_id, mtd_id_len + 1);

		/* link पूर्णांकo chain */
		this_mtd->next = partitions;
		partitions = this_mtd;

		dbg(("mtdid=<%s> num_parts=<%d>\n",
		     this_mtd->mtd_id, this_mtd->num_parts));


		/* EOS - we're करोne */
		अगर (*s == 0)
			अवरोध;

		/* करोes another spec follow? */
		अगर (*s != ';') अणु
			pr_err("bad character after partition (%c)\n", *s);
			वापस -EINVAL;
		पूर्ण
		s++;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Main function to be called from the MTD mapping driver/device to
 * obtain the partitioning inक्रमmation. At this poपूर्णांक the command line
 * arguments will actually be parsed and turned to काष्ठा mtd_partition
 * inक्रमmation. It वापसs partitions क्रम the requested mtd device, or
 * the first one in the chain अगर a शून्य mtd_id is passed in.
 */
अटल पूर्णांक parse_cmdline_partitions(काष्ठा mtd_info *master,
				    स्थिर काष्ठा mtd_partition **pparts,
				    काष्ठा mtd_part_parser_data *data)
अणु
	अचिन्हित दीर्घ दीर्घ offset;
	पूर्णांक i, err;
	काष्ठा cmdline_mtd_partition *part;
	स्थिर अक्षर *mtd_id = master->name;

	/* parse command line */
	अगर (!cmdline_parsed) अणु
		err = mtdpart_setup_real(cmdline);
		अगर (err)
			वापस err;
	पूर्ण

	/*
	 * Search क्रम the partition definition matching master->name.
	 * If master->name is not set, stop at first partition definition.
	 */
	क्रम (part = partitions; part; part = part->next) अणु
		अगर ((!mtd_id) || (!म_भेद(part->mtd_id, mtd_id)))
			अवरोध;
	पूर्ण

	अगर (!part)
		वापस 0;

	क्रम (i = 0, offset = 0; i < part->num_parts; i++) अणु
		अगर (part->parts[i].offset == OFFSET_CONTINUOUS)
			part->parts[i].offset = offset;
		अन्यथा
			offset = part->parts[i].offset;

		अगर (part->parts[i].size == SIZE_REMAINING)
			part->parts[i].size = master->size - offset;

		अगर (offset + part->parts[i].size > master->size) अणु
			pr_warn("%s: partitioning exceeds flash size, truncating\n",
				part->mtd_id);
			part->parts[i].size = master->size - offset;
		पूर्ण
		offset += part->parts[i].size;

		अगर (part->parts[i].size == 0) अणु
			pr_warn("%s: skipping zero sized partition\n",
				part->mtd_id);
			part->num_parts--;
			स_हटाओ(&part->parts[i], &part->parts[i + 1],
				माप(*part->parts) * (part->num_parts - i));
			i--;
		पूर्ण
	पूर्ण

	*pparts = kmemdup(part->parts, माप(*part->parts) * part->num_parts,
			  GFP_KERNEL);
	अगर (!*pparts)
		वापस -ENOMEM;

	वापस part->num_parts;
पूर्ण


/*
 * This is the handler क्रम our kernel parameter, called from
 * मुख्य.c::checksetup(). Note that we can not yet kदो_स्मृति() anything,
 * so we only save the commandline क्रम later processing.
 *
 * This function needs to be visible क्रम bootloaders.
 */
अटल पूर्णांक __init mtdpart_setup(अक्षर *s)
अणु
	cmdline = s;
	वापस 1;
पूर्ण

__setup("mtdparts=", mtdpart_setup);

अटल काष्ठा mtd_part_parser cmdline_parser = अणु
	.parse_fn = parse_cmdline_partitions,
	.name = "cmdlinepart",
पूर्ण;

अटल पूर्णांक __init cmdline_parser_init(व्योम)
अणु
	अगर (mtdparts)
		mtdpart_setup(mtdparts);
	रेजिस्टर_mtd_parser(&cmdline_parser);
	वापस 0;
पूर्ण

अटल व्योम __निकास cmdline_parser_निकास(व्योम)
अणु
	deरेजिस्टर_mtd_parser(&cmdline_parser);
पूर्ण

module_init(cmdline_parser_init);
module_निकास(cmdline_parser_निकास);

MODULE_PARM_DESC(mtdparts, "Partitioning specification");
module_param(mtdparts, अक्षरp, 0);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marius Groeger <mag@sysgo.de>");
MODULE_DESCRIPTION("Command line configuration of MTD partitions");
