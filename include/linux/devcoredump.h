<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright(c) 2015 Intel Deutschland GmbH
 */
#अगर_अघोषित __DEVCOREDUMP_H
#घोषणा __DEVCOREDUMP_H

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <linux/scatterlist.h>
#समावेश <linux/slab.h>

/*
 * _devcd_मुक्त_sgtable - मुक्त all the memory of the given scatterlist table
 * (i.e. both pages and scatterlist instances)
 * NOTE: अगर two tables allocated and chained using the sg_chain function then
 * this function should be called only once on the first table
 * @table: poपूर्णांकer to sg_table to मुक्त
 */
अटल अंतरभूत व्योम _devcd_मुक्त_sgtable(काष्ठा scatterlist *table)
अणु
	पूर्णांक i;
	काष्ठा page *page;
	काष्ठा scatterlist *iter;
	काष्ठा scatterlist *delete_iter;

	/* मुक्त pages */
	iter = table;
	क्रम_each_sg(table, iter, sg_nents(table), i) अणु
		page = sg_page(iter);
		अगर (page)
			__मुक्त_page(page);
	पूर्ण

	/* then मुक्त all chained tables */
	iter = table;
	delete_iter = table;	/* always poपूर्णांकs on a head of a table */
	जबतक (!sg_is_last(iter)) अणु
		iter++;
		अगर (sg_is_chain(iter)) अणु
			iter = sg_chain_ptr(iter);
			kमुक्त(delete_iter);
			delete_iter = iter;
		पूर्ण
	पूर्ण

	/* मुक्त the last table */
	kमुक्त(delete_iter);
पूर्ण


#अगर_घोषित CONFIG_DEV_COREDUMP
व्योम dev_coredumpv(काष्ठा device *dev, व्योम *data, माप_प्रकार datalen,
		   gfp_t gfp);

व्योम dev_coredumpm(काष्ठा device *dev, काष्ठा module *owner,
		   व्योम *data, माप_प्रकार datalen, gfp_t gfp,
		   sमाप_प्रकार (*पढ़ो)(अक्षर *buffer, loff_t offset, माप_प्रकार count,
				   व्योम *data, माप_प्रकार datalen),
		   व्योम (*मुक्त)(व्योम *data));

व्योम dev_coredumpsg(काष्ठा device *dev, काष्ठा scatterlist *table,
		    माप_प्रकार datalen, gfp_t gfp);
#अन्यथा
अटल अंतरभूत व्योम dev_coredumpv(काष्ठा device *dev, व्योम *data,
				 माप_प्रकार datalen, gfp_t gfp)
अणु
	vमुक्त(data);
पूर्ण

अटल अंतरभूत व्योम
dev_coredumpm(काष्ठा device *dev, काष्ठा module *owner,
	      व्योम *data, माप_प्रकार datalen, gfp_t gfp,
	      sमाप_प्रकार (*पढ़ो)(अक्षर *buffer, loff_t offset, माप_प्रकार count,
			      व्योम *data, माप_प्रकार datalen),
	      व्योम (*मुक्त)(व्योम *data))
अणु
	मुक्त(data);
पूर्ण

अटल अंतरभूत व्योम dev_coredumpsg(काष्ठा device *dev, काष्ठा scatterlist *table,
				  माप_प्रकार datalen, gfp_t gfp)
अणु
	_devcd_मुक्त_sgtable(table);
पूर्ण
#पूर्ण_अगर /* CONFIG_DEV_COREDUMP */

#पूर्ण_अगर /* __DEVCOREDUMP_H */
