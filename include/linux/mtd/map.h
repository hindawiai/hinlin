<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright तऊ 2000-2010 David Woodhouse <dwmw2@infradead.org> et al.
 */

/* Overhauled routines क्रम dealing with dअगरferent mmap regions of flash */

#अगर_अघोषित __LINUX_MTD_MAP_H__
#घोषणा __LINUX_MTD_MAP_H__

#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/bug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/unaligned.h>
#समावेश <यंत्र/barrier.h>

#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_1
#घोषणा map_bankwidth(map) 1
#घोषणा map_bankwidth_is_1(map) (map_bankwidth(map) == 1)
#घोषणा map_bankwidth_is_large(map) (0)
#घोषणा map_words(map) (1)
#घोषणा MAX_MAP_BANKWIDTH 1
#अन्यथा
#घोषणा map_bankwidth_is_1(map) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_2
# अगरdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
# अन्यथा
#  define map_bankwidth(map) 2
#  define map_bankwidth_is_large(map) (0)
#  define map_words(map) (1)
# endअगर
#घोषणा map_bankwidth_is_2(map) (map_bankwidth(map) == 2)
#अघोषित MAX_MAP_BANKWIDTH
#घोषणा MAX_MAP_BANKWIDTH 2
#अन्यथा
#घोषणा map_bankwidth_is_2(map) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_4
# अगरdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
# अन्यथा
#  define map_bankwidth(map) 4
#  define map_bankwidth_is_large(map) (0)
#  define map_words(map) (1)
# endअगर
#घोषणा map_bankwidth_is_4(map) (map_bankwidth(map) == 4)
#अघोषित MAX_MAP_BANKWIDTH
#घोषणा MAX_MAP_BANKWIDTH 4
#अन्यथा
#घोषणा map_bankwidth_is_4(map) (0)
#पूर्ण_अगर

/* ensure we never evaluate anything लघुed than an अचिन्हित दीर्घ
 * to zero, and ensure we'll never miss the end of an comparison (bjd) */

#घोषणा map_calc_words(map) ((map_bankwidth(map) + (माप(अचिन्हित दीर्घ)-1)) / माप(अचिन्हित दीर्घ))

#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_8
# अगरdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
#  अगर BITS_PER_LONG < 64
#   undef map_bankwidth_is_large
#   define map_bankwidth_is_large(map) (map_bankwidth(map) > BITS_PER_LONG/8)
#   undef map_words
#   define map_words(map) map_calc_words(map)
#  endअगर
# अन्यथा
#  define map_bankwidth(map) 8
#  define map_bankwidth_is_large(map) (BITS_PER_LONG < 64)
#  define map_words(map) map_calc_words(map)
# endअगर
#घोषणा map_bankwidth_is_8(map) (map_bankwidth(map) == 8)
#अघोषित MAX_MAP_BANKWIDTH
#घोषणा MAX_MAP_BANKWIDTH 8
#अन्यथा
#घोषणा map_bankwidth_is_8(map) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_16
# अगरdef map_bankwidth
#  undef map_bankwidth
#  define map_bankwidth(map) ((map)->bankwidth)
#  undef map_bankwidth_is_large
#  define map_bankwidth_is_large(map) (map_bankwidth(map) > BITS_PER_LONG/8)
#  undef map_words
#  define map_words(map) map_calc_words(map)
# अन्यथा
#  define map_bankwidth(map) 16
#  define map_bankwidth_is_large(map) (1)
#  define map_words(map) map_calc_words(map)
# endअगर
#घोषणा map_bankwidth_is_16(map) (map_bankwidth(map) == 16)
#अघोषित MAX_MAP_BANKWIDTH
#घोषणा MAX_MAP_BANKWIDTH 16
#अन्यथा
#घोषणा map_bankwidth_is_16(map) (0)
#पूर्ण_अगर

#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_32
/* always use indirect access क्रम 256-bit to preserve kernel stack */
# undef map_bankwidth
# define map_bankwidth(map) ((map)->bankwidth)
# undef map_bankwidth_is_large
# define map_bankwidth_is_large(map) (map_bankwidth(map) > BITS_PER_LONG/8)
# undef map_words
# define map_words(map) map_calc_words(map)
#घोषणा map_bankwidth_is_32(map) (map_bankwidth(map) == 32)
#अघोषित MAX_MAP_BANKWIDTH
#घोषणा MAX_MAP_BANKWIDTH 32
#अन्यथा
#घोषणा map_bankwidth_is_32(map) (0)
#पूर्ण_अगर

#अगर_अघोषित map_bankwidth
#अगर_घोषित CONFIG_MTD
#warning "No CONFIG_MTD_MAP_BANK_WIDTH_xx selected. No NOR chip support can work"
#पूर्ण_अगर
अटल अंतरभूत पूर्णांक map_bankwidth(व्योम *map)
अणु
	BUG();
	वापस 0;
पूर्ण
#घोषणा map_bankwidth_is_large(map) (0)
#घोषणा map_words(map) (0)
#घोषणा MAX_MAP_BANKWIDTH 1
#पूर्ण_अगर

अटल अंतरभूत पूर्णांक map_bankwidth_supported(पूर्णांक w)
अणु
	चयन (w) अणु
#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_1
	हाल 1:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_2
	हाल 2:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_4
	हाल 4:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_8
	हाल 8:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_16
	हाल 16:
#पूर्ण_अगर
#अगर_घोषित CONFIG_MTD_MAP_BANK_WIDTH_32
	हाल 32:
#पूर्ण_अगर
		वापस 1;

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

#घोषणा MAX_MAP_LONGS (((MAX_MAP_BANKWIDTH * 8) + BITS_PER_LONG - 1) / BITS_PER_LONG)

प्रकार जोड़ अणु
	अचिन्हित दीर्घ x[MAX_MAP_LONGS];
पूर्ण map_word;

/* The map stuff is very simple. You fill in your काष्ठा map_info with
   a handful of routines क्रम accessing the device, making sure they handle
   paging etc. correctly अगर your device needs it. Then you pass it off
   to a chip probe routine -- either JEDEC or CFI probe or both -- via
   करो_map_probe(). If a chip is recognised, the probe code will invoke the
   appropriate chip driver (अगर present) and वापस a काष्ठा mtd_info.
   At which poपूर्णांक, you fill in the mtd->module with your own module
   address, and रेजिस्टर it with the MTD core code. Or you could partition
   it and रेजिस्टर the partitions instead, or keep it क्रम your own निजी
   use; whatever.

   The mtd->priv field will poपूर्णांक to the काष्ठा map_info, and any further
   निजी data required by the chip driver is linked from the
   mtd->priv->fldrv_priv field. This allows the map driver to get at
   the deकाष्ठाor function map->fldrv_destroy() when it's tired
   of living.
*/

काष्ठा map_info अणु
	स्थिर अक्षर *name;
	अचिन्हित दीर्घ size;
	resource_माप_प्रकार phys;
#घोषणा NO_XIP (-1UL)

	व्योम __iomem *virt;
	व्योम *cached;

	पूर्णांक swap; /* this mapping's byte-swapping requirement */
	पूर्णांक bankwidth; /* in octets. This isn't necessarily the width
		       of actual bus cycles -- it's the repeat पूर्णांकerval
		      in bytes, beक्रमe you are talking to the first chip again.
		      */

#अगर_घोषित CONFIG_MTD_COMPLEX_MAPPINGS
	map_word (*पढ़ो)(काष्ठा map_info *, अचिन्हित दीर्घ);
	व्योम (*copy_from)(काष्ठा map_info *, व्योम *, अचिन्हित दीर्घ, sमाप_प्रकार);

	व्योम (*ग_लिखो)(काष्ठा map_info *, स्थिर map_word, अचिन्हित दीर्घ);
	व्योम (*copy_to)(काष्ठा map_info *, अचिन्हित दीर्घ, स्थिर व्योम *, sमाप_प्रकार);

	/* We can perhaps put in 'point' and 'unpoint' methods, अगर we really
	   want to enable XIP क्रम non-linear mappings. Not yet though. */
#पूर्ण_अगर
	/* It's possible क्रम the map driver to use cached memory in its
	   copy_from implementation (and _only_ with copy_from).  However,
	   when the chip driver knows some flash area has changed contents,
	   it will संकेत it to the map driver through this routine to let
	   the map driver invalidate the corresponding cache as needed.
	   If there is no cache to care about this can be set to शून्य. */
	व्योम (*inval_cache)(काष्ठा map_info *, अचिन्हित दीर्घ, sमाप_प्रकार);

	/* This will be called with 1 as parameter when the first map user
	 * needs VPP, and called with 0 when the last user निकासs. The map
	 * core मुख्यtains a reference counter, and assumes that VPP is a
	 * global resource applying to all mapped flash chips on the प्रणाली.
	 */
	व्योम (*set_vpp)(काष्ठा map_info *, पूर्णांक);

	अचिन्हित दीर्घ pfow_base;
	अचिन्हित दीर्घ map_priv_1;
	अचिन्हित दीर्घ map_priv_2;
	काष्ठा device_node *device_node;
	व्योम *fldrv_priv;
	काष्ठा mtd_chip_driver *fldrv;
पूर्ण;

काष्ठा mtd_chip_driver अणु
	काष्ठा mtd_info *(*probe)(काष्ठा map_info *map);
	व्योम (*destroy)(काष्ठा mtd_info *);
	काष्ठा module *module;
	अक्षर *name;
	काष्ठा list_head list;
पूर्ण;

व्योम रेजिस्टर_mtd_chip_driver(काष्ठा mtd_chip_driver *);
व्योम unरेजिस्टर_mtd_chip_driver(काष्ठा mtd_chip_driver *);

काष्ठा mtd_info *करो_map_probe(स्थिर अक्षर *name, काष्ठा map_info *map);
व्योम map_destroy(काष्ठा mtd_info *mtd);

#घोषणा ENABLE_VPP(map) करो अणु अगर (map->set_vpp) map->set_vpp(map, 1); पूर्ण जबतक (0)
#घोषणा DISABLE_VPP(map) करो अणु अगर (map->set_vpp) map->set_vpp(map, 0); पूर्ण जबतक (0)

#घोषणा INVALIDATE_CACHED_RANGE(map, from, size) \
	करो अणु अगर (map->inval_cache) map->inval_cache(map, from, size); पूर्ण जबतक (0)

#घोषणा map_word_equal(map, val1, val2)					\
(अणु									\
	पूर्णांक i, ret = 1;							\
	क्रम (i = 0; i < map_words(map); i++)				\
		अगर ((val1).x[i] != (val2).x[i]) अणु			\
			ret = 0;					\
			अवरोध;						\
		पूर्ण							\
	ret;								\
पूर्ण)

#घोषणा map_word_and(map, val1, val2)					\
(अणु									\
	map_word r;							\
	पूर्णांक i;								\
	क्रम (i = 0; i < map_words(map); i++)				\
		r.x[i] = (val1).x[i] & (val2).x[i];			\
	r;								\
पूर्ण)

#घोषणा map_word_clr(map, val1, val2)					\
(अणु									\
	map_word r;							\
	पूर्णांक i;								\
	क्रम (i = 0; i < map_words(map); i++)				\
		r.x[i] = (val1).x[i] & ~(val2).x[i];			\
	r;								\
पूर्ण)

#घोषणा map_word_or(map, val1, val2)					\
(अणु									\
	map_word r;							\
	पूर्णांक i;								\
	क्रम (i = 0; i < map_words(map); i++)				\
		r.x[i] = (val1).x[i] | (val2).x[i];			\
	r;								\
पूर्ण)

#घोषणा map_word_andequal(map, val1, val2, val3)			\
(अणु									\
	पूर्णांक i, ret = 1;							\
	क्रम (i = 0; i < map_words(map); i++) अणु				\
		अगर (((val1).x[i] & (val2).x[i]) != (val3).x[i]) अणु	\
			ret = 0;					\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	ret;								\
पूर्ण)

#घोषणा map_word_bitsset(map, val1, val2)				\
(अणु									\
	पूर्णांक i, ret = 0;							\
	क्रम (i = 0; i < map_words(map); i++) अणु				\
		अगर ((val1).x[i] & (val2).x[i]) अणु			\
			ret = 1;					\
			अवरोध;						\
		पूर्ण							\
	पूर्ण								\
	ret;								\
पूर्ण)

अटल अंतरभूत map_word map_word_load(काष्ठा map_info *map, स्थिर व्योम *ptr)
अणु
	map_word r;

	अगर (map_bankwidth_is_1(map))
		r.x[0] = *(अचिन्हित अक्षर *)ptr;
	अन्यथा अगर (map_bankwidth_is_2(map))
		r.x[0] = get_unaligned((uपूर्णांक16_t *)ptr);
	अन्यथा अगर (map_bankwidth_is_4(map))
		r.x[0] = get_unaligned((uपूर्णांक32_t *)ptr);
#अगर BITS_PER_LONG >= 64
	अन्यथा अगर (map_bankwidth_is_8(map))
		r.x[0] = get_unaligned((uपूर्णांक64_t *)ptr);
#पूर्ण_अगर
	अन्यथा अगर (map_bankwidth_is_large(map))
		स_नकल(r.x, ptr, map->bankwidth);
	अन्यथा
		BUG();

	वापस r;
पूर्ण

अटल अंतरभूत map_word map_word_load_partial(काष्ठा map_info *map, map_word orig, स्थिर अचिन्हित अक्षर *buf, पूर्णांक start, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (map_bankwidth_is_large(map)) अणु
		अक्षर *dest = (अक्षर *)&orig;

		स_नकल(dest+start, buf, len);
	पूर्ण अन्यथा अणु
		क्रम (i = start; i < start+len; i++) अणु
			पूर्णांक bitpos;

#अगर_घोषित __LITTLE_ENDIAN
			bitpos = i * 8;
#अन्यथा /* __BIG_ENDIAN */
			bitpos = (map_bankwidth(map) - 1 - i) * 8;
#पूर्ण_अगर
			orig.x[0] &= ~(0xff << bitpos);
			orig.x[0] |= (अचिन्हित दीर्घ)buf[i-start] << bitpos;
		पूर्ण
	पूर्ण
	वापस orig;
पूर्ण

#अगर BITS_PER_LONG < 64
#घोषणा MAP_FF_LIMIT 4
#अन्यथा
#घोषणा MAP_FF_LIMIT 8
#पूर्ण_अगर

अटल अंतरभूत map_word map_word_ff(काष्ठा map_info *map)
अणु
	map_word r;
	पूर्णांक i;

	अगर (map_bankwidth(map) < MAP_FF_LIMIT) अणु
		पूर्णांक bw = 8 * map_bankwidth(map);

		r.x[0] = (1UL << bw) - 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < map_words(map); i++)
			r.x[i] = ~0UL;
	पूर्ण
	वापस r;
पूर्ण

अटल अंतरभूत map_word अंतरभूत_map_पढ़ो(काष्ठा map_info *map, अचिन्हित दीर्घ ofs)
अणु
	map_word r;

	अगर (map_bankwidth_is_1(map))
		r.x[0] = __raw_पढ़ोb(map->virt + ofs);
	अन्यथा अगर (map_bankwidth_is_2(map))
		r.x[0] = __raw_पढ़ोw(map->virt + ofs);
	अन्यथा अगर (map_bankwidth_is_4(map))
		r.x[0] = __raw_पढ़ोl(map->virt + ofs);
#अगर BITS_PER_LONG >= 64
	अन्यथा अगर (map_bankwidth_is_8(map))
		r.x[0] = __raw_पढ़ोq(map->virt + ofs);
#पूर्ण_अगर
	अन्यथा अगर (map_bankwidth_is_large(map))
		स_नकल_fromio(r.x, map->virt + ofs, map->bankwidth);
	अन्यथा
		BUG();

	वापस r;
पूर्ण

अटल अंतरभूत व्योम अंतरभूत_map_ग_लिखो(काष्ठा map_info *map, स्थिर map_word datum, अचिन्हित दीर्घ ofs)
अणु
	अगर (map_bankwidth_is_1(map))
		__raw_ग_लिखोb(datum.x[0], map->virt + ofs);
	अन्यथा अगर (map_bankwidth_is_2(map))
		__raw_ग_लिखोw(datum.x[0], map->virt + ofs);
	अन्यथा अगर (map_bankwidth_is_4(map))
		__raw_ग_लिखोl(datum.x[0], map->virt + ofs);
#अगर BITS_PER_LONG >= 64
	अन्यथा अगर (map_bankwidth_is_8(map))
		__raw_ग_लिखोq(datum.x[0], map->virt + ofs);
#पूर्ण_अगर
	अन्यथा अगर (map_bankwidth_is_large(map))
		स_नकल_toio(map->virt+ofs, datum.x, map->bankwidth);
	अन्यथा
		BUG();
	mb();
पूर्ण

अटल अंतरभूत व्योम अंतरभूत_map_copy_from(काष्ठा map_info *map, व्योम *to, अचिन्हित दीर्घ from, sमाप_प्रकार len)
अणु
	अगर (map->cached)
		स_नकल(to, (अक्षर *)map->cached + from, len);
	अन्यथा
		स_नकल_fromio(to, map->virt + from, len);
पूर्ण

अटल अंतरभूत व्योम अंतरभूत_map_copy_to(काष्ठा map_info *map, अचिन्हित दीर्घ to, स्थिर व्योम *from, sमाप_प्रकार len)
अणु
	स_नकल_toio(map->virt + to, from, len);
पूर्ण

#अगर_घोषित CONFIG_MTD_COMPLEX_MAPPINGS
#घोषणा map_पढ़ो(map, ofs) (map)->पढ़ो(map, ofs)
#घोषणा map_copy_from(map, to, from, len) (map)->copy_from(map, to, from, len)
#घोषणा map_ग_लिखो(map, datum, ofs) (map)->ग_लिखो(map, datum, ofs)
#घोषणा map_copy_to(map, to, from, len) (map)->copy_to(map, to, from, len)

बाह्य व्योम simple_map_init(काष्ठा map_info *);
#घोषणा map_is_linear(map) (map->phys != NO_XIP)

#अन्यथा
#घोषणा map_पढ़ो(map, ofs) अंतरभूत_map_पढ़ो(map, ofs)
#घोषणा map_copy_from(map, to, from, len) अंतरभूत_map_copy_from(map, to, from, len)
#घोषणा map_ग_लिखो(map, datum, ofs) अंतरभूत_map_ग_लिखो(map, datum, ofs)
#घोषणा map_copy_to(map, to, from, len) अंतरभूत_map_copy_to(map, to, from, len)


#घोषणा simple_map_init(map) BUG_ON(!map_bankwidth_supported((map)->bankwidth))
#घोषणा map_is_linear(map) (अणु (व्योम)(map); 1; पूर्ण)

#पूर्ण_अगर /* !CONFIG_MTD_COMPLEX_MAPPINGS */

#पूर्ण_अगर /* __LINUX_MTD_MAP_H__ */
