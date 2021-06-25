<शैली गुरु>
/*
 * Copyright (C) 2011 Red Hat, Inc.
 *
 * This file is released under the GPL.
 */

#अगर_अघोषित _LINUX_DM_SPACE_MAP_H
#घोषणा _LINUX_DM_SPACE_MAP_H

#समावेश "dm-block-manager.h"

प्रकार व्योम (*dm_sm_threshold_fn)(व्योम *context);

/*
 * काष्ठा dm_space_map keeps a record of how many बार each block in a device
 * is referenced.  It needs to be fixed on disk as part of the transaction.
 */
काष्ठा dm_space_map अणु
	व्योम (*destroy)(काष्ठा dm_space_map *sm);

	/*
	 * You must commit beक्रमe allocating the newly added space.
	 */
	पूर्णांक (*extend)(काष्ठा dm_space_map *sm, dm_block_t extra_blocks);

	/*
	 * Extensions करो not appear in this count until after commit has
	 * been called.
	 */
	पूर्णांक (*get_nr_blocks)(काष्ठा dm_space_map *sm, dm_block_t *count);

	/*
	 * Space maps must never allocate a block from the previous
	 * transaction, in हाल we need to rollback.  This complicates the
	 * semantics of get_nr_मुक्त(), it should वापस the number of blocks
	 * that are available क्रम allocation _now_.  For instance you may
	 * have blocks with a zero reference count that will not be
	 * available क्रम allocation until after the next commit.
	 */
	पूर्णांक (*get_nr_मुक्त)(काष्ठा dm_space_map *sm, dm_block_t *count);

	पूर्णांक (*get_count)(काष्ठा dm_space_map *sm, dm_block_t b, uपूर्णांक32_t *result);
	पूर्णांक (*count_is_more_than_one)(काष्ठा dm_space_map *sm, dm_block_t b,
				      पूर्णांक *result);
	पूर्णांक (*set_count)(काष्ठा dm_space_map *sm, dm_block_t b, uपूर्णांक32_t count);

	पूर्णांक (*commit)(काष्ठा dm_space_map *sm);

	पूर्णांक (*inc_block)(काष्ठा dm_space_map *sm, dm_block_t b);
	पूर्णांक (*dec_block)(काष्ठा dm_space_map *sm, dm_block_t b);

	/*
	 * new_block will increment the वापसed block.
	 */
	पूर्णांक (*new_block)(काष्ठा dm_space_map *sm, dm_block_t *b);

	/*
	 * The root contains all the inक्रमmation needed to fix the space map.
	 * Generally this info is small, so squirrel it away in a disk block
	 * aदीर्घ with other info.
	 */
	पूर्णांक (*root_size)(काष्ठा dm_space_map *sm, माप_प्रकार *result);
	पूर्णांक (*copy_root)(काष्ठा dm_space_map *sm, व्योम *copy_to_here_le, माप_प्रकार len);

	/*
	 * You can रेजिस्टर one threshold callback which is edge-triggered
	 * when the मुक्त space in the space map drops below the threshold.
	 */
	पूर्णांक (*रेजिस्टर_threshold_callback)(काष्ठा dm_space_map *sm,
					   dm_block_t threshold,
					   dm_sm_threshold_fn fn,
					   व्योम *context);
पूर्ण;

/*----------------------------------------------------------------*/

अटल अंतरभूत व्योम dm_sm_destroy(काष्ठा dm_space_map *sm)
अणु
	sm->destroy(sm);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_extend(काष्ठा dm_space_map *sm, dm_block_t extra_blocks)
अणु
	वापस sm->extend(sm, extra_blocks);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_get_nr_blocks(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	वापस sm->get_nr_blocks(sm, count);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_get_nr_मुक्त(काष्ठा dm_space_map *sm, dm_block_t *count)
अणु
	वापस sm->get_nr_मुक्त(sm, count);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_get_count(काष्ठा dm_space_map *sm, dm_block_t b,
				  uपूर्णांक32_t *result)
अणु
	वापस sm->get_count(sm, b, result);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_count_is_more_than_one(काष्ठा dm_space_map *sm,
					       dm_block_t b, पूर्णांक *result)
अणु
	वापस sm->count_is_more_than_one(sm, b, result);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_set_count(काष्ठा dm_space_map *sm, dm_block_t b,
				  uपूर्णांक32_t count)
अणु
	वापस sm->set_count(sm, b, count);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_commit(काष्ठा dm_space_map *sm)
अणु
	वापस sm->commit(sm);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_inc_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	वापस sm->inc_block(sm, b);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_dec_block(काष्ठा dm_space_map *sm, dm_block_t b)
अणु
	वापस sm->dec_block(sm, b);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_new_block(काष्ठा dm_space_map *sm, dm_block_t *b)
अणु
	वापस sm->new_block(sm, b);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_root_size(काष्ठा dm_space_map *sm, माप_प्रकार *result)
अणु
	वापस sm->root_size(sm, result);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_copy_root(काष्ठा dm_space_map *sm, व्योम *copy_to_here_le, माप_प्रकार len)
अणु
	वापस sm->copy_root(sm, copy_to_here_le, len);
पूर्ण

अटल अंतरभूत पूर्णांक dm_sm_रेजिस्टर_threshold_callback(काष्ठा dm_space_map *sm,
						    dm_block_t threshold,
						    dm_sm_threshold_fn fn,
						    व्योम *context)
अणु
	अगर (sm->रेजिस्टर_threshold_callback)
		वापस sm->रेजिस्टर_threshold_callback(sm, threshold, fn, context);

	वापस -EINVAL;
पूर्ण


#पूर्ण_अगर	/* _LINUX_DM_SPACE_MAP_H */
