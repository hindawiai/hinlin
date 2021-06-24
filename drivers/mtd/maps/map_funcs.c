<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Out-of-line map I/O functions क्रम simple maps when CONFIG_COMPLEX_MAPPINGS
 * is enabled.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>

#समावेश <linux/mtd/map.h>
#समावेश <linux/mtd/xip.h>

अटल map_word __xipram simple_map_पढ़ो(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	वापस अंतरभूत_map_पढ़ो(map, ofs);
पूर्ण

अटल व्योम __xipram simple_map_ग_लिखो(काष्ठा map_info *map, स्थिर map_word datum, अचिन्हित दीर्घ ofs)
अणु
	अंतरभूत_map_ग_लिखो(map, datum, ofs);
पूर्ण

अटल व्योम __xipram simple_map_copy_from(काष्ठा map_info *map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	अंतरभूत_map_copy_from(map, to, from, len);
पूर्ण

अटल व्योम __xipram simple_map_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	अंतरभूत_map_copy_to(map, to, from, len);
पूर्ण

व्योम simple_map_init(काष्ठा map_info *map)
अणु
	BUG_ON(!map_bankwidth_supported(map->bankwidth));

	map->पढ़ो = simple_map_पढ़ो;
	map->ग_लिखो = simple_map_ग_लिखो;
	map->copy_from = simple_map_copy_from;
	map->copy_to = simple_map_copy_to;
पूर्ण

EXPORT_SYMBOL(simple_map_init);
MODULE_LICENSE("GPL");
