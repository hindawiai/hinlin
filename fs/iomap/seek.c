<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2017 Red Hat, Inc.
 * Copyright (c) 2018 Christoph Hellwig.
 */
#समावेश <linux/module.h>
#समावेश <linux/compiler.h>
#समावेश <linux/fs.h>
#समावेश <linux/iomap.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/pagevec.h>

अटल loff_t
iomap_seek_hole_actor(काष्ठा inode *inode, loff_t start, loff_t length,
		      व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	loff_t offset = start;

	चयन (iomap->type) अणु
	हाल IOMAP_UNWRITTEN:
		offset = mapping_seek_hole_data(inode->i_mapping, start,
				start + length, SEEK_HOLE);
		अगर (offset == start + length)
			वापस length;
		fallthrough;
	हाल IOMAP_HOLE:
		*(loff_t *)data = offset;
		वापस 0;
	शेष:
		वापस length;
	पूर्ण
पूर्ण

loff_t
iomap_seek_hole(काष्ठा inode *inode, loff_t offset, स्थिर काष्ठा iomap_ops *ops)
अणु
	loff_t size = i_size_पढ़ो(inode);
	loff_t length = size - offset;
	loff_t ret;

	/* Nothing to be found beक्रमe or beyond the end of the file. */
	अगर (offset < 0 || offset >= size)
		वापस -ENXIO;

	जबतक (length > 0) अणु
		ret = iomap_apply(inode, offset, length, IOMAP_REPORT, ops,
				  &offset, iomap_seek_hole_actor);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0)
			अवरोध;

		offset += ret;
		length -= ret;
	पूर्ण

	वापस offset;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_seek_hole);

अटल loff_t
iomap_seek_data_actor(काष्ठा inode *inode, loff_t start, loff_t length,
		      व्योम *data, काष्ठा iomap *iomap, काष्ठा iomap *srcmap)
अणु
	loff_t offset = start;

	चयन (iomap->type) अणु
	हाल IOMAP_HOLE:
		वापस length;
	हाल IOMAP_UNWRITTEN:
		offset = mapping_seek_hole_data(inode->i_mapping, start,
				start + length, SEEK_DATA);
		अगर (offset < 0)
			वापस length;
		fallthrough;
	शेष:
		*(loff_t *)data = offset;
		वापस 0;
	पूर्ण
पूर्ण

loff_t
iomap_seek_data(काष्ठा inode *inode, loff_t offset, स्थिर काष्ठा iomap_ops *ops)
अणु
	loff_t size = i_size_पढ़ो(inode);
	loff_t length = size - offset;
	loff_t ret;

	/* Nothing to be found beक्रमe or beyond the end of the file. */
	अगर (offset < 0 || offset >= size)
		वापस -ENXIO;

	जबतक (length > 0) अणु
		ret = iomap_apply(inode, offset, length, IOMAP_REPORT, ops,
				  &offset, iomap_seek_data_actor);
		अगर (ret < 0)
			वापस ret;
		अगर (ret == 0)
			अवरोध;

		offset += ret;
		length -= ret;
	पूर्ण

	अगर (length <= 0)
		वापस -ENXIO;
	वापस offset;
पूर्ण
EXPORT_SYMBOL_GPL(iomap_seek_data);
