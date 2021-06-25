<शैली गुरु>
/*
 * MTD partitioning layer definitions
 *
 * (C) 2000 Nicolas Pitre <nico@fluxnic.net>
 *
 * This code is GPL
 */

#अगर_अघोषित MTD_PARTITIONS_H
#घोषणा MTD_PARTITIONS_H

#समावेश <linux/types.h>


/*
 * Partition definition काष्ठाure:
 *
 * An array of काष्ठा partition is passed aदीर्घ with a MTD object to
 * mtd_device_रेजिस्टर() to create them.
 *
 * For each partition, these fields are available:
 * name: string that will be used to label the partition's MTD device.
 * types: some partitions can be containers using specअगरic क्रमmat to describe
 *	embedded subpartitions / volumes. E.g. many home routers use "firmware"
 *	partition that contains at least kernel and rootfs. In such हाल an
 *	extra parser is needed that will detect these dynamic partitions and
 *	report them to the MTD subप्रणाली. If set this property stores an array
 *	of parser names to use when looking क्रम subpartitions.
 * size: the partition size; अगर defined as MTDPART_SIZ_FULL, the partition
 * 	will extend to the end of the master MTD device.
 * offset: असलolute starting position within the master MTD device; अगर
 * 	defined as MTDPART_OFS_APPEND, the partition will start where the
 *	previous one ended; अगर MTDPART_OFS_NXTBLK, at the next erase block;
 *	अगर MTDPART_OFS_RETAIN, consume as much as possible, leaving size
 *	after the end of partition.
 * mask_flags: contains flags that have to be masked (हटाओd) from the
 * 	master MTD flag set क्रम the corresponding MTD partition.
 * 	For example, to क्रमce a पढ़ो-only partition, simply adding
 * 	MTD_WRITEABLE to the mask_flags will करो the trick.
 * add_flags: contains flags to add to the parent flags
 *
 * Note: ग_लिखोable partitions require their size and offset be
 * erasesize aligned (e.g. use MTDPART_OFS_NEXTBLK).
 */

काष्ठा mtd_partition अणु
	स्थिर अक्षर *name;		/* identअगरier string */
	स्थिर अक्षर *स्थिर *types;	/* names of parsers to use अगर any */
	uपूर्णांक64_t size;			/* partition size */
	uपूर्णांक64_t offset;		/* offset within the master MTD space */
	uपूर्णांक32_t mask_flags;		/* master MTD flags to mask out क्रम this partition */
	uपूर्णांक32_t add_flags;		/* flags to add to the partition */
	काष्ठा device_node *of_node;
पूर्ण;

#घोषणा MTDPART_OFS_RETAIN	(-3)
#घोषणा MTDPART_OFS_NXTBLK	(-2)
#घोषणा MTDPART_OFS_APPEND	(-1)
#घोषणा MTDPART_SIZ_FULL	(0)


काष्ठा mtd_info;
काष्ठा device_node;

/**
 * काष्ठा mtd_part_parser_data - used to pass data to MTD partition parsers.
 * @origin: क्रम RedBoot, start address of MTD device
 */
काष्ठा mtd_part_parser_data अणु
	अचिन्हित दीर्घ origin;
पूर्ण;


/*
 * Functions dealing with the various ways of partitioning the space
 */

काष्ठा mtd_part_parser अणु
	काष्ठा list_head list;
	काष्ठा module *owner;
	स्थिर अक्षर *name;
	स्थिर काष्ठा of_device_id *of_match_table;
	पूर्णांक (*parse_fn)(काष्ठा mtd_info *, स्थिर काष्ठा mtd_partition **,
			काष्ठा mtd_part_parser_data *);
	व्योम (*cleanup)(स्थिर काष्ठा mtd_partition *pparts, पूर्णांक nr_parts);
पूर्ण;

/* Container क्रम passing around a set of parsed partitions */
काष्ठा mtd_partitions अणु
	स्थिर काष्ठा mtd_partition *parts;
	पूर्णांक nr_parts;
	स्थिर काष्ठा mtd_part_parser *parser;
पूर्ण;

बाह्य पूर्णांक __रेजिस्टर_mtd_parser(काष्ठा mtd_part_parser *parser,
				 काष्ठा module *owner);
#घोषणा रेजिस्टर_mtd_parser(parser) __रेजिस्टर_mtd_parser(parser, THIS_MODULE)

बाह्य व्योम deरेजिस्टर_mtd_parser(काष्ठा mtd_part_parser *parser);

/*
 * module_mtd_part_parser() - Helper macro क्रम MTD partition parsers that करोn't
 * करो anything special in module init/निकास. Each driver may only use this macro
 * once, and calling it replaces module_init() and module_निकास().
 */
#घोषणा module_mtd_part_parser(__mtd_part_parser) \
	module_driver(__mtd_part_parser, रेजिस्टर_mtd_parser, \
		      deरेजिस्टर_mtd_parser)

पूर्णांक mtd_add_partition(काष्ठा mtd_info *master, स्थिर अक्षर *name,
		      दीर्घ दीर्घ offset, दीर्घ दीर्घ length);
पूर्णांक mtd_del_partition(काष्ठा mtd_info *master, पूर्णांक partno);
uपूर्णांक64_t mtd_get_device_size(स्थिर काष्ठा mtd_info *mtd);

#पूर्ण_अगर
