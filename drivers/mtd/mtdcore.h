<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * These are exported solely क्रम the purpose of mtd_blkdevs.c and mtdअक्षर.c.
 * You should not use them क्रम _anything_ अन्यथा.
 */

बाह्य काष्ठा mutex mtd_table_mutex;
बाह्य काष्ठा backing_dev_info *mtd_bdi;

काष्ठा mtd_info *__mtd_next_device(पूर्णांक i);
पूर्णांक __must_check add_mtd_device(काष्ठा mtd_info *mtd);
पूर्णांक del_mtd_device(काष्ठा mtd_info *mtd);
पूर्णांक add_mtd_partitions(काष्ठा mtd_info *, स्थिर काष्ठा mtd_partition *, पूर्णांक);
पूर्णांक del_mtd_partitions(काष्ठा mtd_info *);

काष्ठा mtd_partitions;

पूर्णांक parse_mtd_partitions(काष्ठा mtd_info *master, स्थिर अक्षर * स्थिर *types,
			 काष्ठा mtd_part_parser_data *data);

व्योम mtd_part_parser_cleanup(काष्ठा mtd_partitions *parts);

पूर्णांक __init init_mtdअक्षर(व्योम);
व्योम __निकास cleanup_mtdअक्षर(व्योम);

#घोषणा mtd_क्रम_each_device(mtd)			\
	क्रम ((mtd) = __mtd_next_device(0);		\
	     (mtd) != शून्य;				\
	     (mtd) = __mtd_next_device(mtd->index + 1))
