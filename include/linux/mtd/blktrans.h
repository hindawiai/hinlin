<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2003-2010 David Woodhouse <dwmw2@infradead.org>
 */

#अगर_अघोषित __MTD_TRANS_H__
#घोषणा __MTD_TRANS_H__

#समावेश <linux/mutex.h>
#समावेश <linux/kref.h>
#समावेश <linux/sysfs.h>

काष्ठा hd_geometry;
काष्ठा mtd_info;
काष्ठा mtd_blktrans_ops;
काष्ठा file;
काष्ठा inode;

काष्ठा mtd_blktrans_dev अणु
	काष्ठा mtd_blktrans_ops *tr;
	काष्ठा list_head list;
	काष्ठा mtd_info *mtd;
	काष्ठा mutex lock;
	पूर्णांक devnum;
	bool bg_stop;
	अचिन्हित दीर्घ size;
	पूर्णांक पढ़ोonly;
	पूर्णांक खोलो;
	काष्ठा kref ref;
	काष्ठा gendisk *disk;
	काष्ठा attribute_group *disk_attributes;
	काष्ठा request_queue *rq;
	काष्ठा list_head rq_list;
	काष्ठा blk_mq_tag_set *tag_set;
	spinlock_t queue_lock;
	व्योम *priv;
	भ_शेषe_t file_mode;
पूर्ण;

काष्ठा mtd_blktrans_ops अणु
	अक्षर *name;
	पूर्णांक major;
	पूर्णांक part_bits;
	पूर्णांक blksize;
	पूर्णांक blkshअगरt;

	/* Access functions */
	पूर्णांक (*पढ़ोsect)(काष्ठा mtd_blktrans_dev *dev,
		    अचिन्हित दीर्घ block, अक्षर *buffer);
	पूर्णांक (*ग_लिखोsect)(काष्ठा mtd_blktrans_dev *dev,
		     अचिन्हित दीर्घ block, अक्षर *buffer);
	पूर्णांक (*discard)(काष्ठा mtd_blktrans_dev *dev,
		       अचिन्हित दीर्घ block, अचिन्हित nr_blocks);
	व्योम (*background)(काष्ठा mtd_blktrans_dev *dev);

	/* Block layer ioctls */
	पूर्णांक (*getgeo)(काष्ठा mtd_blktrans_dev *dev, काष्ठा hd_geometry *geo);
	पूर्णांक (*flush)(काष्ठा mtd_blktrans_dev *dev);

	/* Called with mtd_table_mutex held; no race with add/हटाओ */
	पूर्णांक (*खोलो)(काष्ठा mtd_blktrans_dev *dev);
	व्योम (*release)(काष्ठा mtd_blktrans_dev *dev);

	/* Called on अणुde,पूर्णregistration and on subsequent addition/removal
	   of devices, with mtd_table_mutex held. */
	व्योम (*add_mtd)(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd);
	व्योम (*हटाओ_dev)(काष्ठा mtd_blktrans_dev *dev);

	काष्ठा list_head devs;
	काष्ठा list_head list;
	काष्ठा module *owner;
पूर्ण;

बाह्य पूर्णांक रेजिस्टर_mtd_blktrans(काष्ठा mtd_blktrans_ops *tr);
बाह्य पूर्णांक deरेजिस्टर_mtd_blktrans(काष्ठा mtd_blktrans_ops *tr);
बाह्य पूर्णांक add_mtd_blktrans_dev(काष्ठा mtd_blktrans_dev *dev);
बाह्य पूर्णांक del_mtd_blktrans_dev(काष्ठा mtd_blktrans_dev *dev);
बाह्य पूर्णांक mtd_blktrans_cease_background(काष्ठा mtd_blktrans_dev *dev);

/**
 * module_mtd_blktrans() - Helper macro क्रम रेजिस्टरing a mtd blktrans driver
 * @__mtd_blktrans: mtd_blktrans_ops काष्ठा
 *
 * Helper macro क्रम mtd blktrans drivers which करो not करो anything special in
 * module init/निकास. This eliminates a lot of boilerplate. Each module may only
 * use this macro once, and calling it replaces module_init() and module_निकास()
 */
#घोषणा module_mtd_blktrans(__mtd_blktrans) \
	module_driver(__mtd_blktrans, रेजिस्टर_mtd_blktrans, \
					deरेजिस्टर_mtd_blktrans)

#पूर्ण_अगर /* __MTD_TRANS_H__ */
