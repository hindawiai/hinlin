<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/math64.h>
#समावेश <linux/slab.h>

#समावेश <linux/ceph/striper.h>
#समावेश <linux/ceph/types.h>

/*
 * Map a file extent to a stripe unit within an object.
 * Fill in objno, offset पूर्णांकo object, and object extent length (i.e. the
 * number of bytes mapped, less than or equal to @l->stripe_unit).
 *
 * Example क्रम stripe_count = 3, stripes_per_object = 4:
 *
 * blockno   |  0  3  6  9 |  1  4  7 10 |  2  5  8 11 | 12 15 18 21 | 13 16 19
 * stripeno  |  0  1  2  3 |  0  1  2  3 |  0  1  2  3 |  4  5  6  7 |  4  5  6
 * stripepos |      0      |      1      |      2      |      0      |      1
 * objno     |      0      |      1      |      2      |      3      |      4
 * objsetno  |                    0                    |                    1
 */
व्योम ceph_calc_file_object_mapping(काष्ठा ceph_file_layout *l,
				   u64 off, u64 len,
				   u64 *objno, u64 *objoff, u32 *xlen)
अणु
	u32 stripes_per_object = l->object_size / l->stripe_unit;
	u64 blockno;	/* which su in the file (i.e. globally) */
	u32 blockoff;	/* offset पूर्णांकo su */
	u64 stripeno;	/* which stripe */
	u32 stripepos;	/* which su in the stripe,
			   which object in the object set */
	u64 objsetno;	/* which object set */
	u32 objsetpos;	/* which stripe in the object set */

	blockno = भाग_u64_rem(off, l->stripe_unit, &blockoff);
	stripeno = भाग_u64_rem(blockno, l->stripe_count, &stripepos);
	objsetno = भाग_u64_rem(stripeno, stripes_per_object, &objsetpos);

	*objno = objsetno * l->stripe_count + stripepos;
	*objoff = objsetpos * l->stripe_unit + blockoff;
	*xlen = min_t(u64, len, l->stripe_unit - blockoff);
पूर्ण
EXPORT_SYMBOL(ceph_calc_file_object_mapping);

/*
 * Return the last extent with given objno (@object_extents is sorted
 * by objno).  If not found, वापस शून्य and set @add_pos so that the
 * new extent can be added with list_add(add_pos, new_ex).
 */
अटल काष्ठा ceph_object_extent *
lookup_last(काष्ठा list_head *object_extents, u64 objno,
	    काष्ठा list_head **add_pos)
अणु
	काष्ठा list_head *pos;

	list_क्रम_each_prev(pos, object_extents) अणु
		काष्ठा ceph_object_extent *ex =
		    list_entry(pos, typeof(*ex), oe_item);

		अगर (ex->oe_objno == objno)
			वापस ex;

		अगर (ex->oe_objno < objno)
			अवरोध;
	पूर्ण

	*add_pos = pos;
	वापस शून्य;
पूर्ण

अटल काष्ठा ceph_object_extent *
lookup_containing(काष्ठा list_head *object_extents, u64 objno,
		  u64 objoff, u32 xlen)
अणु
	काष्ठा ceph_object_extent *ex;

	list_क्रम_each_entry(ex, object_extents, oe_item) अणु
		अगर (ex->oe_objno == objno &&
		    ex->oe_off <= objoff &&
		    ex->oe_off + ex->oe_len >= objoff + xlen) /* paranoia */
			वापस ex;

		अगर (ex->oe_objno > objno)
			अवरोध;
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * Map a file extent to a sorted list of object extents.
 *
 * We want only one (or as few as possible) object extents per object.
 * Adjacent object extents will be merged together, each वापसed object
 * extent may reverse map to multiple dअगरferent file extents.
 *
 * Call @alloc_fn क्रम each new object extent and @action_fn क्रम each
 * mapped stripe unit, whether it was merged पूर्णांकo an alपढ़ोy allocated
 * object extent or started a new object extent.
 *
 * Newly allocated object extents are added to @object_extents.
 * To keep @object_extents sorted, successive calls to this function
 * must map successive file extents (i.e. the list of file extents that
 * are mapped using the same @object_extents must be sorted).
 *
 * The caller is responsible क्रम @object_extents.
 */
पूर्णांक ceph_file_to_extents(काष्ठा ceph_file_layout *l, u64 off, u64 len,
			 काष्ठा list_head *object_extents,
			 काष्ठा ceph_object_extent *alloc_fn(व्योम *arg),
			 व्योम *alloc_arg,
			 ceph_object_extent_fn_t action_fn,
			 व्योम *action_arg)
अणु
	काष्ठा ceph_object_extent *last_ex, *ex;

	जबतक (len) अणु
		काष्ठा list_head *add_pos = शून्य;
		u64 objno, objoff;
		u32 xlen;

		ceph_calc_file_object_mapping(l, off, len, &objno, &objoff,
					      &xlen);

		last_ex = lookup_last(object_extents, objno, &add_pos);
		अगर (!last_ex || last_ex->oe_off + last_ex->oe_len != objoff) अणु
			ex = alloc_fn(alloc_arg);
			अगर (!ex)
				वापस -ENOMEM;

			ex->oe_objno = objno;
			ex->oe_off = objoff;
			ex->oe_len = xlen;
			अगर (action_fn)
				action_fn(ex, xlen, action_arg);

			अगर (!last_ex)
				list_add(&ex->oe_item, add_pos);
			अन्यथा
				list_add(&ex->oe_item, &last_ex->oe_item);
		पूर्ण अन्यथा अणु
			last_ex->oe_len += xlen;
			अगर (action_fn)
				action_fn(last_ex, xlen, action_arg);
		पूर्ण

		off += xlen;
		len -= xlen;
	पूर्ण

	क्रम (last_ex = list_first_entry(object_extents, typeof(*ex), oe_item),
	     ex = list_next_entry(last_ex, oe_item);
	     &ex->oe_item != object_extents;
	     last_ex = ex, ex = list_next_entry(ex, oe_item)) अणु
		अगर (last_ex->oe_objno > ex->oe_objno ||
		    (last_ex->oe_objno == ex->oe_objno &&
		     last_ex->oe_off + last_ex->oe_len >= ex->oe_off)) अणु
			WARN(1, "%s: object_extents list not sorted!\n",
			     __func__);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_file_to_extents);

/*
 * A stripped करोwn, non-allocating version of ceph_file_to_extents(),
 * क्रम when @object_extents is alपढ़ोy populated.
 */
पूर्णांक ceph_iterate_extents(काष्ठा ceph_file_layout *l, u64 off, u64 len,
			 काष्ठा list_head *object_extents,
			 ceph_object_extent_fn_t action_fn,
			 व्योम *action_arg)
अणु
	जबतक (len) अणु
		काष्ठा ceph_object_extent *ex;
		u64 objno, objoff;
		u32 xlen;

		ceph_calc_file_object_mapping(l, off, len, &objno, &objoff,
					      &xlen);

		ex = lookup_containing(object_extents, objno, objoff, xlen);
		अगर (!ex) अणु
			WARN(1, "%s: objno %llu %llu~%u not found!\n",
			     __func__, objno, objoff, xlen);
			वापस -EINVAL;
		पूर्ण

		action_fn(ex, xlen, action_arg);

		off += xlen;
		len -= xlen;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_iterate_extents);

/*
 * Reverse map an object extent to a sorted list of file extents.
 *
 * On success, the caller is responsible क्रम:
 *
 *     kमुक्त(file_extents)
 */
पूर्णांक ceph_extent_to_file(काष्ठा ceph_file_layout *l,
			u64 objno, u64 objoff, u64 objlen,
			काष्ठा ceph_file_extent **file_extents,
			u32 *num_file_extents)
अणु
	u32 stripes_per_object = l->object_size / l->stripe_unit;
	u64 blockno;	/* which su */
	u32 blockoff;	/* offset पूर्णांकo su */
	u64 stripeno;	/* which stripe */
	u32 stripepos;	/* which su in the stripe,
			   which object in the object set */
	u64 objsetno;	/* which object set */
	u32 i = 0;

	अगर (!objlen) अणु
		*file_extents = शून्य;
		*num_file_extents = 0;
		वापस 0;
	पूर्ण

	*num_file_extents = DIV_ROUND_UP_ULL(objoff + objlen, l->stripe_unit) -
				     DIV_ROUND_DOWN_ULL(objoff, l->stripe_unit);
	*file_extents = kदो_स्मृति_array(*num_file_extents, माप(**file_extents),
				      GFP_NOIO);
	अगर (!*file_extents)
		वापस -ENOMEM;

	भाग_u64_rem(objoff, l->stripe_unit, &blockoff);
	जबतक (objlen) अणु
		u64 off, len;

		objsetno = भाग_u64_rem(objno, l->stripe_count, &stripepos);
		stripeno = भाग_u64(objoff, l->stripe_unit) +
						objsetno * stripes_per_object;
		blockno = stripeno * l->stripe_count + stripepos;
		off = blockno * l->stripe_unit + blockoff;
		len = min_t(u64, objlen, l->stripe_unit - blockoff);

		(*file_extents)[i].fe_off = off;
		(*file_extents)[i].fe_len = len;

		blockoff = 0;
		objoff += len;
		objlen -= len;
		i++;
	पूर्ण

	BUG_ON(i != *num_file_extents);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(ceph_extent_to_file);

u64 ceph_get_num_objects(काष्ठा ceph_file_layout *l, u64 size)
अणु
	u64 period = (u64)l->stripe_count * l->object_size;
	u64 num_periods = DIV64_U64_ROUND_UP(size, period);
	u64 reमुख्यder_bytes;
	u64 reमुख्यder_objs = 0;

	भाग64_u64_rem(size, period, &reमुख्यder_bytes);
	अगर (reमुख्यder_bytes > 0 &&
	    reमुख्यder_bytes < (u64)l->stripe_count * l->stripe_unit)
		reमुख्यder_objs = l->stripe_count -
			    DIV_ROUND_UP_ULL(reमुख्यder_bytes, l->stripe_unit);

	वापस num_periods * l->stripe_count - reमुख्यder_objs;
पूर्ण
EXPORT_SYMBOL(ceph_get_num_objects);
