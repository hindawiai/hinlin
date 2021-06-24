<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bitext.c: kernel little helper (of bit shuffling variety).
 *
 * Copyright (C) 2002 Pete Zaitcev <zaitcev@yahoo.com>
 *
 * The algorithm to search a zero bit string is geared towards its application.
 * We expect a couple of fixed sizes of requests, so a rotating counter, reset
 * by align size, should provide fast enough search जबतक मुख्यtaining low
 * fragmentation.
 */

#समावेश <linux/माला.स>
#समावेश <linux/biपंचांगap.h>

#समावेश <यंत्र/bitext.h>

/**
 * bit_map_string_get - find and set a bit string in bit map.
 * @t: the bit map.
 * @len: requested string length
 * @align: requested alignment
 *
 * Returns offset in the map or -1 अगर out of space.
 *
 * Not safe to call from an पूर्णांकerrupt (uses spin_lock).
 */
पूर्णांक bit_map_string_get(काष्ठा bit_map *t, पूर्णांक len, पूर्णांक align)
अणु
	पूर्णांक offset, count;	/* siamese twins */
	पूर्णांक off_new;
	पूर्णांक align1;
	पूर्णांक i, color;

	अगर (t->num_colors) अणु
		/* align is overloaded to be the page color */
		color = align;
		align = t->num_colors;
	पूर्ण अन्यथा अणु
		color = 0;
		अगर (align == 0)
			align = 1;
	पूर्ण
	align1 = align - 1;
	अगर ((align & align1) != 0)
		BUG();
	अगर (align < 0 || align >= t->size)
		BUG();
	अगर (len <= 0 || len > t->size)
		BUG();
	color &= align1;

	spin_lock(&t->lock);
	अगर (len < t->last_size)
		offset = t->first_मुक्त;
	अन्यथा
		offset = t->last_off & ~align1;
	count = 0;
	क्रम (;;) अणु
		off_new = find_next_zero_bit(t->map, t->size, offset);
		off_new = ((off_new + align1) & ~align1) + color;
		count += off_new - offset;
		offset = off_new;
		अगर (offset >= t->size)
			offset = 0;
		अगर (count + len > t->size) अणु
			spin_unlock(&t->lock);
/* P3 */ prपूर्णांकk(KERN_ERR
  "bitmap out: size %d used %d off %d len %d align %d count %d\n",
  t->size, t->used, offset, len, align, count);
			वापस -1;
		पूर्ण

		अगर (offset + len > t->size) अणु
			count += t->size - offset;
			offset = 0;
			जारी;
		पूर्ण

		i = 0;
		जबतक (test_bit(offset + i, t->map) == 0) अणु
			i++;
			अगर (i == len) अणु
				biपंचांगap_set(t->map, offset, len);
				अगर (offset == t->first_मुक्त)
					t->first_मुक्त = find_next_zero_bit
							(t->map, t->size,
							 t->first_मुक्त + len);
				अगर ((t->last_off = offset + len) >= t->size)
					t->last_off = 0;
				t->used += len;
				t->last_size = len;
				spin_unlock(&t->lock);
				वापस offset;
			पूर्ण
		पूर्ण
		count += i + 1;
		अगर ((offset += i + 1) >= t->size)
			offset = 0;
	पूर्ण
पूर्ण

व्योम bit_map_clear(काष्ठा bit_map *t, पूर्णांक offset, पूर्णांक len)
अणु
	पूर्णांक i;

	अगर (t->used < len)
		BUG();		/* Much too late to करो any good, but alas... */
	spin_lock(&t->lock);
	क्रम (i = 0; i < len; i++) अणु
		अगर (test_bit(offset + i, t->map) == 0)
			BUG();
		__clear_bit(offset + i, t->map);
	पूर्ण
	अगर (offset < t->first_मुक्त)
		t->first_मुक्त = offset;
	t->used -= len;
	spin_unlock(&t->lock);
पूर्ण

व्योम bit_map_init(काष्ठा bit_map *t, अचिन्हित दीर्घ *map, पूर्णांक size)
अणु
	biपंचांगap_zero(map, size);
	स_रखो(t, 0, माप *t);
	spin_lock_init(&t->lock);
	t->map = map;
	t->size = size;
पूर्ण
