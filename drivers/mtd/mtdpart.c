<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Simple MTD partitioning layer
 *
 * Copyright तऊ 2000 Nicolas Pitre <nico@fluxnic.net>
 * Copyright तऊ 2002 Thomas Gleixner <gleixner@linutronix.de>
 * Copyright तऊ 2000-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/kmod.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/err.h>
#समावेश <linux/of.h>

#समावेश "mtdcore.h"

/*
 * MTD methods which simply translate the effective address and pass through
 * to the _real_ device.
 */

अटल अंतरभूत व्योम मुक्त_partition(काष्ठा mtd_info *mtd)
अणु
	kमुक्त(mtd->name);
	kमुक्त(mtd);
पूर्ण

अटल काष्ठा mtd_info *allocate_partition(काष्ठा mtd_info *parent,
					   स्थिर काष्ठा mtd_partition *part,
					   पूर्णांक partno, uपूर्णांक64_t cur_offset)
अणु
	काष्ठा mtd_info *master = mtd_get_master(parent);
	पूर्णांक wr_alignment = (parent->flags & MTD_NO_ERASE) ?
			   master->ग_लिखोsize : master->erasesize;
	u64 parent_size = mtd_is_partition(parent) ?
			  parent->part.size : parent->size;
	काष्ठा mtd_info *child;
	u32 reमुख्यder;
	अक्षर *name;
	u64 पंचांगp;

	/* allocate the partition काष्ठाure */
	child = kzalloc(माप(*child), GFP_KERNEL);
	name = kstrdup(part->name, GFP_KERNEL);
	अगर (!name || !child) अणु
		prपूर्णांकk(KERN_ERR"memory allocation error while creating partitions for \"%s\"\n",
		       parent->name);
		kमुक्त(name);
		kमुक्त(child);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* set up the MTD object क्रम this partition */
	child->type = parent->type;
	child->part.flags = parent->flags & ~part->mask_flags;
	child->part.flags |= part->add_flags;
	child->flags = child->part.flags;
	child->part.size = part->size;
	child->ग_लिखोsize = parent->ग_लिखोsize;
	child->ग_लिखोbufsize = parent->ग_लिखोbufsize;
	child->oobsize = parent->oobsize;
	child->oobavail = parent->oobavail;
	child->subpage_sft = parent->subpage_sft;

	child->name = name;
	child->owner = parent->owner;

	/* NOTE: Historically, we didn't arrange MTDs as a tree out of
	 * concern क्रम showing the same data in multiple partitions.
	 * However, it is very useful to have the master node present,
	 * so the MTD_PARTITIONED_MASTER option allows that. The master
	 * will have device nodes etc only अगर this is set, so make the
	 * parent conditional on that option. Note, this is a way to
	 * distinguish between the parent and its partitions in sysfs.
	 */
	child->dev.parent = IS_ENABLED(CONFIG_MTD_PARTITIONED_MASTER) || mtd_is_partition(parent) ?
			    &parent->dev : parent->dev.parent;
	child->dev.of_node = part->of_node;
	child->parent = parent;
	child->part.offset = part->offset;
	INIT_LIST_HEAD(&child->partitions);

	अगर (child->part.offset == MTDPART_OFS_APPEND)
		child->part.offset = cur_offset;
	अगर (child->part.offset == MTDPART_OFS_NXTBLK) अणु
		पंचांगp = cur_offset;
		child->part.offset = cur_offset;
		reमुख्यder = करो_भाग(पंचांगp, wr_alignment);
		अगर (reमुख्यder) अणु
			child->part.offset += wr_alignment - reमुख्यder;
			prपूर्णांकk(KERN_NOTICE "Moving partition %d: "
			       "0x%012llx -> 0x%012llx\n", partno,
			       (अचिन्हित दीर्घ दीर्घ)cur_offset,
			       child->part.offset);
		पूर्ण
	पूर्ण
	अगर (child->part.offset == MTDPART_OFS_RETAIN) अणु
		child->part.offset = cur_offset;
		अगर (parent_size - child->part.offset >= child->part.size) अणु
			child->part.size = parent_size - child->part.offset -
					   child->part.size;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_ERR "mtd partition \"%s\" doesn't have enough space: %#llx < %#llx, disabled\n",
				part->name, parent_size - child->part.offset,
				child->part.size);
			/* रेजिस्टर to preserve ordering */
			जाओ out_रेजिस्टर;
		पूर्ण
	पूर्ण
	अगर (child->part.size == MTDPART_SIZ_FULL)
		child->part.size = parent_size - child->part.offset;

	prपूर्णांकk(KERN_NOTICE "0x%012llx-0x%012llx : \"%s\"\n",
	       child->part.offset, child->part.offset + child->part.size,
	       child->name);

	/* let's करो some sanity checks */
	अगर (child->part.offset >= parent_size) अणु
		/* let's रेजिस्टर it anyway to preserve ordering */
		child->part.offset = 0;
		child->part.size = 0;

		/* Initialize ->erasesize to make add_mtd_device() happy. */
		child->erasesize = parent->erasesize;
		prपूर्णांकk(KERN_ERR"mtd: partition \"%s\" is out of reach -- disabled\n",
			part->name);
		जाओ out_रेजिस्टर;
	पूर्ण
	अगर (child->part.offset + child->part.size > parent->size) अणु
		child->part.size = parent_size - child->part.offset;
		prपूर्णांकk(KERN_WARNING"mtd: partition \"%s\" extends beyond the end of device \"%s\" -- size truncated to %#llx\n",
			part->name, parent->name, child->part.size);
	पूर्ण

	अगर (parent->numeraseregions > 1) अणु
		/* Deal with variable erase size stuff */
		पूर्णांक i, max = parent->numeraseregions;
		u64 end = child->part.offset + child->part.size;
		काष्ठा mtd_erase_region_info *regions = parent->eraseregions;

		/* Find the first erase regions which is part of this
		 * partition. */
		क्रम (i = 0; i < max && regions[i].offset <= child->part.offset;
		     i++)
			;
		/* The loop searched क्रम the region _behind_ the first one */
		अगर (i > 0)
			i--;

		/* Pick biggest erasesize */
		क्रम (; i < max && regions[i].offset < end; i++) अणु
			अगर (child->erasesize < regions[i].erasesize)
				child->erasesize = regions[i].erasesize;
		पूर्ण
		BUG_ON(child->erasesize == 0);
	पूर्ण अन्यथा अणु
		/* Single erase size */
		child->erasesize = master->erasesize;
	पूर्ण

	/*
	 * Child erasesize might dअगरfer from the parent one अगर the parent
	 * exposes several regions with dअगरferent erasesize. Adjust
	 * wr_alignment accordingly.
	 */
	अगर (!(child->flags & MTD_NO_ERASE))
		wr_alignment = child->erasesize;

	पंचांगp = mtd_get_master_ofs(child, 0);
	reमुख्यder = करो_भाग(पंचांगp, wr_alignment);
	अगर ((child->flags & MTD_WRITEABLE) && reमुख्यder) अणु
		/* Doesn't start on a boundary of major erase size */
		/* FIXME: Let it be writable अगर it is on a boundary of
		 * _minor_ erase size though */
		child->flags &= ~MTD_WRITEABLE;
		prपूर्णांकk(KERN_WARNING"mtd: partition \"%s\" doesn't start on an erase/write block boundary -- force read-only\n",
			part->name);
	पूर्ण

	पंचांगp = mtd_get_master_ofs(child, 0) + child->part.size;
	reमुख्यder = करो_भाग(पंचांगp, wr_alignment);
	अगर ((child->flags & MTD_WRITEABLE) && reमुख्यder) अणु
		child->flags &= ~MTD_WRITEABLE;
		prपूर्णांकk(KERN_WARNING"mtd: partition \"%s\" doesn't end on an erase/write block -- force read-only\n",
			part->name);
	पूर्ण

	child->size = child->part.size;
	child->ecc_step_size = parent->ecc_step_size;
	child->ecc_strength = parent->ecc_strength;
	child->bitflip_threshold = parent->bitflip_threshold;

	अगर (master->_block_isbad) अणु
		uपूर्णांक64_t offs = 0;

		जबतक (offs < child->part.size) अणु
			अगर (mtd_block_isreserved(child, offs))
				child->ecc_stats.bbtblocks++;
			अन्यथा अगर (mtd_block_isbad(child, offs))
				child->ecc_stats.badblocks++;
			offs += child->erasesize;
		पूर्ण
	पूर्ण

out_रेजिस्टर:
	वापस child;
पूर्ण

अटल sमाप_प्रकार mtd_partition_offset_show(काष्ठा device *dev,
		काष्ठा device_attribute *attr, अक्षर *buf)
अणु
	काष्ठा mtd_info *mtd = dev_get_drvdata(dev);

	वापस snम_लिखो(buf, PAGE_SIZE, "%lld\n", mtd->part.offset);
पूर्ण

अटल DEVICE_ATTR(offset, S_IRUGO, mtd_partition_offset_show, शून्य);

अटल स्थिर काष्ठा attribute *mtd_partition_attrs[] = अणु
	&dev_attr_offset.attr,
	शून्य
पूर्ण;

अटल पूर्णांक mtd_add_partition_attrs(काष्ठा mtd_info *new)
अणु
	पूर्णांक ret = sysfs_create_files(&new->dev.kobj, mtd_partition_attrs);
	अगर (ret)
		prपूर्णांकk(KERN_WARNING
		       "mtd: failed to create partition attrs, err=%d\n", ret);
	वापस ret;
पूर्ण

पूर्णांक mtd_add_partition(काष्ठा mtd_info *parent, स्थिर अक्षर *name,
		      दीर्घ दीर्घ offset, दीर्घ दीर्घ length)
अणु
	काष्ठा mtd_info *master = mtd_get_master(parent);
	u64 parent_size = mtd_is_partition(parent) ?
			  parent->part.size : parent->size;
	काष्ठा mtd_partition part;
	काष्ठा mtd_info *child;
	पूर्णांक ret = 0;

	/* the direct offset is expected */
	अगर (offset == MTDPART_OFS_APPEND ||
	    offset == MTDPART_OFS_NXTBLK)
		वापस -EINVAL;

	अगर (length == MTDPART_SIZ_FULL)
		length = parent_size - offset;

	अगर (length <= 0)
		वापस -EINVAL;

	स_रखो(&part, 0, माप(part));
	part.name = name;
	part.size = length;
	part.offset = offset;

	child = allocate_partition(parent, &part, -1, offset);
	अगर (IS_ERR(child))
		वापस PTR_ERR(child);

	mutex_lock(&master->master.partitions_lock);
	list_add_tail(&child->part.node, &parent->partitions);
	mutex_unlock(&master->master.partitions_lock);

	ret = add_mtd_device(child);
	अगर (ret)
		जाओ err_हटाओ_part;

	mtd_add_partition_attrs(child);

	वापस 0;

err_हटाओ_part:
	mutex_lock(&master->master.partitions_lock);
	list_del(&child->part.node);
	mutex_unlock(&master->master.partitions_lock);

	मुक्त_partition(child);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_add_partition);

/**
 * __mtd_del_partition - delete MTD partition
 *
 * @mtd: MTD काष्ठाure to be deleted
 *
 * This function must be called with the partitions mutex locked.
 */
अटल पूर्णांक __mtd_del_partition(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *child, *next;
	पूर्णांक err;

	list_क्रम_each_entry_safe(child, next, &mtd->partitions, part.node) अणु
		err = __mtd_del_partition(child);
		अगर (err)
			वापस err;
	पूर्ण

	sysfs_हटाओ_files(&mtd->dev.kobj, mtd_partition_attrs);

	err = del_mtd_device(mtd);
	अगर (err)
		वापस err;

	list_del(&child->part.node);
	मुक्त_partition(mtd);

	वापस 0;
पूर्ण

/*
 * This function unरेजिस्टरs and destroy all slave MTD objects which are
 * attached to the given MTD object, recursively.
 */
अटल पूर्णांक __del_mtd_partitions(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *child, *next;
	LIST_HEAD(पंचांगp_list);
	पूर्णांक ret, err = 0;

	list_क्रम_each_entry_safe(child, next, &mtd->partitions, part.node) अणु
		अगर (mtd_has_partitions(child))
			__del_mtd_partitions(child);

		pr_info("Deleting %s MTD partition\n", child->name);
		ret = del_mtd_device(child);
		अगर (ret < 0) अणु
			pr_err("Error when deleting partition \"%s\" (%d)\n",
			       child->name, ret);
			err = ret;
			जारी;
		पूर्ण

		list_del(&child->part.node);
		मुक्त_partition(child);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक del_mtd_partitions(काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	pr_info("Deleting MTD partitions on \"%s\":\n", mtd->name);

	mutex_lock(&master->master.partitions_lock);
	ret = __del_mtd_partitions(mtd);
	mutex_unlock(&master->master.partitions_lock);

	वापस ret;
पूर्ण

पूर्णांक mtd_del_partition(काष्ठा mtd_info *mtd, पूर्णांक partno)
अणु
	काष्ठा mtd_info *child, *master = mtd_get_master(mtd);
	पूर्णांक ret = -EINVAL;

	mutex_lock(&master->master.partitions_lock);
	list_क्रम_each_entry(child, &mtd->partitions, part.node) अणु
		अगर (child->index == partno) अणु
			ret = __mtd_del_partition(child);
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&master->master.partitions_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_del_partition);

/*
 * This function, given a parent MTD object and a partition table, creates
 * and रेजिस्टरs the child MTD objects which are bound to the parent according
 * to the partition definitions.
 *
 * For historical reasons, this function's caller only रेजिस्टरs the parent
 * अगर the MTD_PARTITIONED_MASTER config option is set.
 */

पूर्णांक add_mtd_partitions(काष्ठा mtd_info *parent,
		       स्थिर काष्ठा mtd_partition *parts,
		       पूर्णांक nbparts)
अणु
	काष्ठा mtd_info *child, *master = mtd_get_master(parent);
	uपूर्णांक64_t cur_offset = 0;
	पूर्णांक i, ret;

	prपूर्णांकk(KERN_NOTICE "Creating %d MTD partitions on \"%s\":\n",
	       nbparts, parent->name);

	क्रम (i = 0; i < nbparts; i++) अणु
		child = allocate_partition(parent, parts + i, i, cur_offset);
		अगर (IS_ERR(child)) अणु
			ret = PTR_ERR(child);
			जाओ err_del_partitions;
		पूर्ण

		mutex_lock(&master->master.partitions_lock);
		list_add_tail(&child->part.node, &parent->partitions);
		mutex_unlock(&master->master.partitions_lock);

		ret = add_mtd_device(child);
		अगर (ret) अणु
			mutex_lock(&master->master.partitions_lock);
			list_del(&child->part.node);
			mutex_unlock(&master->master.partitions_lock);

			मुक्त_partition(child);
			जाओ err_del_partitions;
		पूर्ण

		mtd_add_partition_attrs(child);

		/* Look क्रम subpartitions */
		parse_mtd_partitions(child, parts[i].types, शून्य);

		cur_offset = child->part.offset + child->part.size;
	पूर्ण

	वापस 0;

err_del_partitions:
	del_mtd_partitions(master);

	वापस ret;
पूर्ण

अटल DEFINE_SPINLOCK(part_parser_lock);
अटल LIST_HEAD(part_parsers);

अटल काष्ठा mtd_part_parser *mtd_part_parser_get(स्थिर अक्षर *name)
अणु
	काष्ठा mtd_part_parser *p, *ret = शून्य;

	spin_lock(&part_parser_lock);

	list_क्रम_each_entry(p, &part_parsers, list)
		अगर (!म_भेद(p->name, name) && try_module_get(p->owner)) अणु
			ret = p;
			अवरोध;
		पूर्ण

	spin_unlock(&part_parser_lock);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम mtd_part_parser_put(स्थिर काष्ठा mtd_part_parser *p)
अणु
	module_put(p->owner);
पूर्ण

/*
 * Many partition parsers just expected the core to kमुक्त() all their data in
 * one chunk. Do that by शेष.
 */
अटल व्योम mtd_part_parser_cleanup_शेष(स्थिर काष्ठा mtd_partition *pparts,
					    पूर्णांक nr_parts)
अणु
	kमुक्त(pparts);
पूर्ण

पूर्णांक __रेजिस्टर_mtd_parser(काष्ठा mtd_part_parser *p, काष्ठा module *owner)
अणु
	p->owner = owner;

	अगर (!p->cleanup)
		p->cleanup = &mtd_part_parser_cleanup_शेष;

	spin_lock(&part_parser_lock);
	list_add(&p->list, &part_parsers);
	spin_unlock(&part_parser_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__रेजिस्टर_mtd_parser);

व्योम deरेजिस्टर_mtd_parser(काष्ठा mtd_part_parser *p)
अणु
	spin_lock(&part_parser_lock);
	list_del(&p->list);
	spin_unlock(&part_parser_lock);
पूर्ण
EXPORT_SYMBOL_GPL(deरेजिस्टर_mtd_parser);

/*
 * Do not क्रमget to update 'parse_mtd_partitions()' kernelकरोc comment अगर you
 * are changing this array!
 */
अटल स्थिर अक्षर * स्थिर शेष_mtd_part_types[] = अणु
	"cmdlinepart",
	"ofpart",
	शून्य
पूर्ण;

/* Check DT only when looking क्रम subpartitions. */
अटल स्थिर अक्षर * स्थिर शेष_subpartition_types[] = अणु
	"ofpart",
	शून्य
पूर्ण;

अटल पूर्णांक mtd_part_करो_parse(काष्ठा mtd_part_parser *parser,
			     काष्ठा mtd_info *master,
			     काष्ठा mtd_partitions *pparts,
			     काष्ठा mtd_part_parser_data *data)
अणु
	पूर्णांक ret;

	ret = (*parser->parse_fn)(master, &pparts->parts, data);
	pr_debug("%s: parser %s: %i\n", master->name, parser->name, ret);
	अगर (ret <= 0)
		वापस ret;

	pr_notice("%d %s partitions found on MTD device %s\n", ret,
		  parser->name, master->name);

	pparts->nr_parts = ret;
	pparts->parser = parser;

	वापस ret;
पूर्ण

/**
 * mtd_part_get_compatible_parser - find MTD parser by a compatible string
 *
 * @compat: compatible string describing partitions in a device tree
 *
 * MTD parsers can specअगरy supported partitions by providing a table of
 * compatibility strings. This function finds a parser that advertises support
 * क्रम a passed value of "compatible".
 */
अटल काष्ठा mtd_part_parser *mtd_part_get_compatible_parser(स्थिर अक्षर *compat)
अणु
	काष्ठा mtd_part_parser *p, *ret = शून्य;

	spin_lock(&part_parser_lock);

	list_क्रम_each_entry(p, &part_parsers, list) अणु
		स्थिर काष्ठा of_device_id *matches;

		matches = p->of_match_table;
		अगर (!matches)
			जारी;

		क्रम (; matches->compatible[0]; matches++) अणु
			अगर (!म_भेद(matches->compatible, compat) &&
			    try_module_get(p->owner)) अणु
				ret = p;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (ret)
			अवरोध;
	पूर्ण

	spin_unlock(&part_parser_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक mtd_part_of_parse(काष्ठा mtd_info *master,
			     काष्ठा mtd_partitions *pparts)
अणु
	काष्ठा mtd_part_parser *parser;
	काष्ठा device_node *np;
	काष्ठा property *prop;
	स्थिर अक्षर *compat;
	स्थिर अक्षर *fixed = "fixed-partitions";
	पूर्णांक ret, err = 0;

	np = mtd_get_of_node(master);
	अगर (mtd_is_partition(master))
		of_node_get(np);
	अन्यथा
		np = of_get_child_by_name(np, "partitions");

	of_property_क्रम_each_string(np, "compatible", prop, compat) अणु
		parser = mtd_part_get_compatible_parser(compat);
		अगर (!parser)
			जारी;
		ret = mtd_part_करो_parse(parser, master, pparts, शून्य);
		अगर (ret > 0) अणु
			of_node_put(np);
			वापस ret;
		पूर्ण
		mtd_part_parser_put(parser);
		अगर (ret < 0 && !err)
			err = ret;
	पूर्ण
	of_node_put(np);

	/*
	 * For backward compatibility we have to try the "fixed-partitions"
	 * parser. It supports old DT क्रमmat with partitions specअगरied as a
	 * direct subnodes of a flash device DT node without any compatibility
	 * specअगरied we could match.
	 */
	parser = mtd_part_parser_get(fixed);
	अगर (!parser && !request_module("%s", fixed))
		parser = mtd_part_parser_get(fixed);
	अगर (parser) अणु
		ret = mtd_part_करो_parse(parser, master, pparts, शून्य);
		अगर (ret > 0)
			वापस ret;
		mtd_part_parser_put(parser);
		अगर (ret < 0 && !err)
			err = ret;
	पूर्ण

	वापस err;
पूर्ण

/**
 * parse_mtd_partitions - parse and रेजिस्टर MTD partitions
 *
 * @master: the master partition (describes whole MTD device)
 * @types: names of partition parsers to try or %शून्य
 * @data: MTD partition parser-specअगरic data
 *
 * This function tries to find & रेजिस्टर partitions on MTD device @master. It
 * uses MTD partition parsers, specअगरied in @types. However, अगर @types is %शून्य,
 * then the शेष list of parsers is used. The शेष list contains only the
 * "cmdlinepart" and "ofpart" parsers ATM.
 * Note: If there are more then one parser in @types, the kernel only takes the
 * partitions parsed out by the first parser.
 *
 * This function may वापस:
 * o a negative error code in हाल of failure
 * o number of found partitions otherwise
 */
पूर्णांक parse_mtd_partitions(काष्ठा mtd_info *master, स्थिर अक्षर *स्थिर *types,
			 काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा mtd_partitions pparts = अणु पूर्ण;
	काष्ठा mtd_part_parser *parser;
	पूर्णांक ret, err = 0;

	अगर (!types)
		types = mtd_is_partition(master) ? शेष_subpartition_types :
			शेष_mtd_part_types;

	क्रम ( ; *types; types++) अणु
		/*
		 * ofpart is a special type that means OF partitioning info
		 * should be used. It requires a bit dअगरferent logic so it is
		 * handled in a separated function.
		 */
		अगर (!म_भेद(*types, "ofpart")) अणु
			ret = mtd_part_of_parse(master, &pparts);
		पूर्ण अन्यथा अणु
			pr_debug("%s: parsing partitions %s\n", master->name,
				 *types);
			parser = mtd_part_parser_get(*types);
			अगर (!parser && !request_module("%s", *types))
				parser = mtd_part_parser_get(*types);
			pr_debug("%s: got parser %s\n", master->name,
				parser ? parser->name : शून्य);
			अगर (!parser)
				जारी;
			ret = mtd_part_करो_parse(parser, master, &pparts, data);
			अगर (ret <= 0)
				mtd_part_parser_put(parser);
		पूर्ण
		/* Found partitions! */
		अगर (ret > 0) अणु
			err = add_mtd_partitions(master, pparts.parts,
						 pparts.nr_parts);
			mtd_part_parser_cleanup(&pparts);
			वापस err ? err : pparts.nr_parts;
		पूर्ण
		/*
		 * Stash the first error we see; only report it अगर no parser
		 * succeeds
		 */
		अगर (ret < 0 && !err)
			err = ret;
	पूर्ण
	वापस err;
पूर्ण

व्योम mtd_part_parser_cleanup(काष्ठा mtd_partitions *parts)
अणु
	स्थिर काष्ठा mtd_part_parser *parser;

	अगर (!parts)
		वापस;

	parser = parts->parser;
	अगर (parser) अणु
		अगर (parser->cleanup)
			parser->cleanup(parts->parts, parts->nr_parts);

		mtd_part_parser_put(parser);
	पूर्ण
पूर्ण

/* Returns the size of the entire flash chip */
uपूर्णांक64_t mtd_get_device_size(स्थिर काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_info *master = mtd_get_master((काष्ठा mtd_info *)mtd);

	वापस master->size;
पूर्ण
EXPORT_SYMBOL_GPL(mtd_get_device_size);
