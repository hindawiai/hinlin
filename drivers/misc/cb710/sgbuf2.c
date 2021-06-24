<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cb710/sgbuf2.c
 *
 *  Copyright by Michaध Mirosधaw, 2008-2009
 */
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/cb710.h>

अटल bool sg_dwiter_next(काष्ठा sg_mapping_iter *miter)
अणु
	अगर (sg_miter_next(miter)) अणु
		miter->consumed = 0;
		वापस true;
	पूर्ण अन्यथा
		वापस false;
पूर्ण

अटल bool sg_dwiter_is_at_end(काष्ठा sg_mapping_iter *miter)
अणु
	वापस miter->length == miter->consumed && !sg_dwiter_next(miter);
पूर्ण

अटल uपूर्णांक32_t sg_dwiter_पढ़ो_buffer(काष्ठा sg_mapping_iter *miter)
अणु
	माप_प्रकार len, left = 4;
	uपूर्णांक32_t data;
	व्योम *addr = &data;

	करो अणु
		len = min(miter->length - miter->consumed, left);
		स_नकल(addr, miter->addr + miter->consumed, len);
		miter->consumed += len;
		left -= len;
		अगर (!left)
			वापस data;
		addr += len;
	पूर्ण जबतक (sg_dwiter_next(miter));

	स_रखो(addr, 0, left);
	वापस data;
पूर्ण

अटल अंतरभूत bool needs_unaligned_copy(स्थिर व्योम *ptr)
अणु
#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	वापस false;
#अन्यथा
	वापस ((ptr - शून्य) & 3) != 0;
#पूर्ण_अगर
पूर्ण

अटल bool sg_dwiter_get_next_block(काष्ठा sg_mapping_iter *miter, uपूर्णांक32_t **ptr)
अणु
	माप_प्रकार len;

	अगर (sg_dwiter_is_at_end(miter))
		वापस true;

	len = miter->length - miter->consumed;

	अगर (likely(len >= 4 && !needs_unaligned_copy(
			miter->addr + miter->consumed))) अणु
		*ptr = miter->addr + miter->consumed;
		miter->consumed += 4;
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * cb710_sg_dwiter_पढ़ो_next_block() - get next 32-bit word from sg buffer
 * @miter: sg mapping iterator used क्रम पढ़ोing
 *
 * Description:
 *   Returns 32-bit word starting at byte poपूर्णांकed to by @miter@
 *   handling any alignment issues.  Bytes past the buffer's end
 *   are not accessed (पढ़ो) but are वापसed as zeroes.  @miter@
 *   is advanced by 4 bytes or to the end of buffer whichever is
 *   बंदr.
 *
 * Context:
 *   Same requirements as in sg_miter_next().
 *
 * Returns:
 *   32-bit word just पढ़ो.
 */
uपूर्णांक32_t cb710_sg_dwiter_पढ़ो_next_block(काष्ठा sg_mapping_iter *miter)
अणु
	uपूर्णांक32_t *ptr = शून्य;

	अगर (likely(sg_dwiter_get_next_block(miter, &ptr)))
		वापस ptr ? *ptr : 0;

	वापस sg_dwiter_पढ़ो_buffer(miter);
पूर्ण
EXPORT_SYMBOL_GPL(cb710_sg_dwiter_पढ़ो_next_block);

अटल व्योम sg_dwiter_ग_लिखो_slow(काष्ठा sg_mapping_iter *miter, uपूर्णांक32_t data)
अणु
	माप_प्रकार len, left = 4;
	व्योम *addr = &data;

	करो अणु
		len = min(miter->length - miter->consumed, left);
		स_नकल(miter->addr, addr, len);
		miter->consumed += len;
		left -= len;
		अगर (!left)
			वापस;
		addr += len;
	पूर्ण जबतक (sg_dwiter_next(miter));
पूर्ण

/**
 * cb710_sg_dwiter_ग_लिखो_next_block() - ग_लिखो next 32-bit word to sg buffer
 * @miter: sg mapping iterator used क्रम writing
 * @data: data to ग_लिखो to sg buffer
 *
 * Description:
 *   Writes 32-bit word starting at byte poपूर्णांकed to by @miter@
 *   handling any alignment issues.  Bytes which would be written
 *   past the buffer's end are silently discarded. @miter@ is
 *   advanced by 4 bytes or to the end of buffer whichever is बंदr.
 *
 * Context:
 *   Same requirements as in sg_miter_next().
 */
व्योम cb710_sg_dwiter_ग_लिखो_next_block(काष्ठा sg_mapping_iter *miter, uपूर्णांक32_t data)
अणु
	uपूर्णांक32_t *ptr = शून्य;

	अगर (likely(sg_dwiter_get_next_block(miter, &ptr))) अणु
		अगर (ptr)
			*ptr = data;
		अन्यथा
			वापस;
	पूर्ण अन्यथा
		sg_dwiter_ग_लिखो_slow(miter, data);
पूर्ण
EXPORT_SYMBOL_GPL(cb710_sg_dwiter_ग_लिखो_next_block);

