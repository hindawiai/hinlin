<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Flash partitions described by the OF (or flattened) device tree
 *
 * Copyright तऊ 2006 MontaVista Software Inc.
 * Author: Vitaly Wool <vwool@ru.mvista.com>
 *
 * Revised to handle newer style flash binding by:
 *   Copyright तऊ 2007 David Gibson, IBM Corporation.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/partitions.h>

#समावेश "ofpart_bcm4908.h"
#समावेश "ofpart_linksys_ns.h"

काष्ठा fixed_partitions_quirks अणु
	पूर्णांक (*post_parse)(काष्ठा mtd_info *mtd, काष्ठा mtd_partition *parts, पूर्णांक nr_parts);
पूर्ण;

अटल काष्ठा fixed_partitions_quirks bcm4908_partitions_quirks = अणु
	.post_parse = bcm4908_partitions_post_parse,
पूर्ण;

अटल काष्ठा fixed_partitions_quirks linksys_ns_partitions_quirks = अणु
	.post_parse = linksys_ns_partitions_post_parse,
पूर्ण;

अटल स्थिर काष्ठा of_device_id parse_ofpart_match_table[];

अटल bool node_has_compatible(काष्ठा device_node *pp)
अणु
	वापस of_get_property(pp, "compatible", शून्य);
पूर्ण

अटल पूर्णांक parse_fixed_partitions(काष्ठा mtd_info *master,
				  स्थिर काष्ठा mtd_partition **pparts,
				  काष्ठा mtd_part_parser_data *data)
अणु
	स्थिर काष्ठा fixed_partitions_quirks *quirks;
	स्थिर काष्ठा of_device_id *of_id;
	काष्ठा mtd_partition *parts;
	काष्ठा device_node *mtd_node;
	काष्ठा device_node *ofpart_node;
	स्थिर अक्षर *partname;
	काष्ठा device_node *pp;
	पूर्णांक nr_parts, i, ret = 0;
	bool dedicated = true;

	/* Pull of_node from the master device node */
	mtd_node = mtd_get_of_node(master);
	अगर (!mtd_node)
		वापस 0;

	अगर (!master->parent) अणु /* Master */
		ofpart_node = of_get_child_by_name(mtd_node, "partitions");
		अगर (!ofpart_node) अणु
			/*
			 * We might get here even when ofpart isn't used at all (e.g.,
			 * when using another parser), so करोn't be louder than
			 * KERN_DEBUG
			 */
			pr_debug("%s: 'partitions' subnode not found on %pOF. Trying to parse direct subnodes as partitions.\n",
				master->name, mtd_node);
			ofpart_node = mtd_node;
			dedicated = false;
		पूर्ण
	पूर्ण अन्यथा अणु /* Partition */
		ofpart_node = mtd_node;
	पूर्ण

	of_id = of_match_node(parse_ofpart_match_table, ofpart_node);
	अगर (dedicated && !of_id) अणु
		/* The 'partitions' subnode might be used by another parser */
		वापस 0;
	पूर्ण

	quirks = of_id ? of_id->data : शून्य;

	/* First count the subnodes */
	nr_parts = 0;
	क्रम_each_child_of_node(ofpart_node,  pp) अणु
		अगर (!dedicated && node_has_compatible(pp))
			जारी;

		nr_parts++;
	पूर्ण

	अगर (nr_parts == 0)
		वापस 0;

	parts = kसुस्मृति(nr_parts, माप(*parts), GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	i = 0;
	क्रम_each_child_of_node(ofpart_node,  pp) अणु
		स्थिर __be32 *reg;
		पूर्णांक len;
		पूर्णांक a_cells, s_cells;

		अगर (!dedicated && node_has_compatible(pp))
			जारी;

		reg = of_get_property(pp, "reg", &len);
		अगर (!reg) अणु
			अगर (dedicated) अणु
				pr_debug("%s: ofpart partition %pOF (%pOF) missing reg property.\n",
					 master->name, pp,
					 mtd_node);
				जाओ ofpart_fail;
			पूर्ण अन्यथा अणु
				nr_parts--;
				जारी;
			पूर्ण
		पूर्ण

		a_cells = of_n_addr_cells(pp);
		s_cells = of_n_size_cells(pp);
		अगर (len / 4 != a_cells + s_cells) अणु
			pr_debug("%s: ofpart partition %pOF (%pOF) error parsing reg property.\n",
				 master->name, pp,
				 mtd_node);
			जाओ ofpart_fail;
		पूर्ण

		parts[i].offset = of_पढ़ो_number(reg, a_cells);
		parts[i].size = of_पढ़ो_number(reg + a_cells, s_cells);
		parts[i].of_node = pp;

		partname = of_get_property(pp, "label", &len);
		अगर (!partname)
			partname = of_get_property(pp, "name", &len);
		parts[i].name = partname;

		अगर (of_get_property(pp, "read-only", &len))
			parts[i].mask_flags |= MTD_WRITEABLE;

		अगर (of_get_property(pp, "lock", &len))
			parts[i].mask_flags |= MTD_POWERUP_LOCK;

		अगर (of_property_पढ़ो_bool(pp, "slc-mode"))
			parts[i].add_flags |= MTD_SLC_ON_MLC_EMULATION;

		i++;
	पूर्ण

	अगर (!nr_parts)
		जाओ ofpart_none;

	अगर (quirks && quirks->post_parse)
		quirks->post_parse(master, parts, nr_parts);

	*pparts = parts;
	वापस nr_parts;

ofpart_fail:
	pr_err("%s: error parsing ofpart partition %pOF (%pOF)\n",
	       master->name, pp, mtd_node);
	ret = -EINVAL;
ofpart_none:
	of_node_put(pp);
	kमुक्त(parts);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id parse_ofpart_match_table[] = अणु
	/* Generic */
	अणु .compatible = "fixed-partitions" पूर्ण,
	/* Customized */
	अणु .compatible = "brcm,bcm4908-partitions", .data = &bcm4908_partitions_quirks, पूर्ण,
	अणु .compatible = "linksys,ns-partitions", .data = &linksys_ns_partitions_quirks, पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, parse_ofpart_match_table);

अटल काष्ठा mtd_part_parser ofpart_parser = अणु
	.parse_fn = parse_fixed_partitions,
	.name = "fixed-partitions",
	.of_match_table = parse_ofpart_match_table,
पूर्ण;

अटल पूर्णांक parse_ofoldpart_partitions(काष्ठा mtd_info *master,
				      स्थिर काष्ठा mtd_partition **pparts,
				      काष्ठा mtd_part_parser_data *data)
अणु
	काष्ठा mtd_partition *parts;
	काष्ठा device_node *dp;
	पूर्णांक i, plen, nr_parts;
	स्थिर काष्ठा अणु
		__be32 offset, len;
	पूर्ण *part;
	स्थिर अक्षर *names;

	/* Pull of_node from the master device node */
	dp = mtd_get_of_node(master);
	अगर (!dp)
		वापस 0;

	part = of_get_property(dp, "partitions", &plen);
	अगर (!part)
		वापस 0; /* No partitions found */

	pr_warn("Device tree uses obsolete partition map binding: %pOF\n", dp);

	nr_parts = plen / माप(part[0]);

	parts = kसुस्मृति(nr_parts, माप(*parts), GFP_KERNEL);
	अगर (!parts)
		वापस -ENOMEM;

	names = of_get_property(dp, "partition-names", &plen);

	क्रम (i = 0; i < nr_parts; i++) अणु
		parts[i].offset = be32_to_cpu(part->offset);
		parts[i].size   = be32_to_cpu(part->len) & ~1;
		/* bit 0 set signअगरies पढ़ो only partition */
		अगर (be32_to_cpu(part->len) & 1)
			parts[i].mask_flags = MTD_WRITEABLE;

		अगर (names && (plen > 0)) अणु
			पूर्णांक len = म_माप(names) + 1;

			parts[i].name = names;
			plen -= len;
			names += len;
		पूर्ण अन्यथा अणु
			parts[i].name = "unnamed";
		पूर्ण

		part++;
	पूर्ण

	*pparts = parts;
	वापस nr_parts;
पूर्ण

अटल काष्ठा mtd_part_parser ofoldpart_parser = अणु
	.parse_fn = parse_ofoldpart_partitions,
	.name = "ofoldpart",
पूर्ण;

अटल पूर्णांक __init ofpart_parser_init(व्योम)
अणु
	रेजिस्टर_mtd_parser(&ofpart_parser);
	रेजिस्टर_mtd_parser(&ofoldpart_parser);
	वापस 0;
पूर्ण

अटल व्योम __निकास ofpart_parser_निकास(व्योम)
अणु
	deरेजिस्टर_mtd_parser(&ofpart_parser);
	deरेजिस्टर_mtd_parser(&ofoldpart_parser);
पूर्ण

module_init(ofpart_parser_init);
module_निकास(ofpart_parser_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Parser for MTD partitioning information in device tree");
MODULE_AUTHOR("Vitaly Wool, David Gibson");
/*
 * When MTD core cannot find the requested parser, it tries to load the module
 * with the same name. Since we provide the ofoldpart parser, we should have
 * the corresponding alias.
 */
MODULE_ALIAS("fixed-partitions");
MODULE_ALIAS("ofoldpart");
