<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2021 Intel Corporation
 */

#समावेश <drm/drm_displayid.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_prपूर्णांक.h>

अटल पूर्णांक validate_displayid(स्थिर u8 *displayid, पूर्णांक length, पूर्णांक idx)
अणु
	पूर्णांक i, dispid_length;
	u8 csum = 0;
	स्थिर काष्ठा displayid_header *base;

	base = (स्थिर काष्ठा displayid_header *)&displayid[idx];

	DRM_DEBUG_KMS("base revision 0x%x, length %d, %d %d\n",
		      base->rev, base->bytes, base->prod_id, base->ext_count);

	/* +1 क्रम DispID checksum */
	dispid_length = माप(*base) + base->bytes + 1;
	अगर (dispid_length > length - idx)
		वापस -EINVAL;

	क्रम (i = 0; i < dispid_length; i++)
		csum += displayid[idx + i];
	अगर (csum) अणु
		DRM_NOTE("DisplayID checksum invalid, remainder is %d\n", csum);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर u8 *drm_find_displayid_extension(स्थिर काष्ठा edid *edid,
					      पूर्णांक *length, पूर्णांक *idx,
					      पूर्णांक *ext_index)
अणु
	स्थिर u8 *displayid = drm_find_edid_extension(edid, DISPLAYID_EXT, ext_index);
	स्थिर काष्ठा displayid_header *base;
	पूर्णांक ret;

	अगर (!displayid)
		वापस शून्य;

	/* EDID extensions block checksum isn't क्रम us */
	*length = EDID_LENGTH - 1;
	*idx = 1;

	ret = validate_displayid(displayid, *length, *idx);
	अगर (ret)
		वापस शून्य;

	base = (स्थिर काष्ठा displayid_header *)&displayid[*idx];
	*length = *idx + माप(*base) + base->bytes;

	वापस displayid;
पूर्ण

व्योम displayid_iter_edid_begin(स्थिर काष्ठा edid *edid,
			       काष्ठा displayid_iter *iter)
अणु
	स_रखो(iter, 0, माप(*iter));

	iter->edid = edid;
पूर्ण

अटल स्थिर काष्ठा displayid_block *
displayid_iter_block(स्थिर काष्ठा displayid_iter *iter)
अणु
	स्थिर काष्ठा displayid_block *block;

	अगर (!iter->section)
		वापस शून्य;

	block = (स्थिर काष्ठा displayid_block *)&iter->section[iter->idx];

	अगर (iter->idx + माप(*block) <= iter->length &&
	    iter->idx + माप(*block) + block->num_bytes <= iter->length)
		वापस block;

	वापस शून्य;
पूर्ण

स्थिर काष्ठा displayid_block *
__displayid_iter_next(काष्ठा displayid_iter *iter)
अणु
	स्थिर काष्ठा displayid_block *block;

	अगर (!iter->edid)
		वापस शून्य;

	अगर (iter->section) अणु
		/* current block should always be valid */
		block = displayid_iter_block(iter);
		अगर (WARN_ON(!block)) अणु
			iter->section = शून्य;
			iter->edid = शून्य;
			वापस शून्य;
		पूर्ण

		/* next block in section */
		iter->idx += माप(*block) + block->num_bytes;

		block = displayid_iter_block(iter);
		अगर (block)
			वापस block;
	पूर्ण

	क्रम (;;) अणु
		iter->section = drm_find_displayid_extension(iter->edid,
							     &iter->length,
							     &iter->idx,
							     &iter->ext_index);
		अगर (!iter->section) अणु
			iter->edid = शून्य;
			वापस शून्य;
		पूर्ण

		iter->idx += माप(काष्ठा displayid_header);

		block = displayid_iter_block(iter);
		अगर (block)
			वापस block;
	पूर्ण
पूर्ण

व्योम displayid_iter_end(काष्ठा displayid_iter *iter)
अणु
	स_रखो(iter, 0, माप(*iter));
पूर्ण
