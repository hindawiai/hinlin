<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2004 Topspin Communications. All rights reserved.
 * Copyright (c) 2005 - 2008 Mellanox Technologies. All rights reserved.
 * Copyright (c) 2006 - 2007 Cisco Systems, Inc. All rights reserved.
 * Copyright (c) 2020 NVIDIA CORPORATION. All rights reserved.
 */

#समावेश "dr_types.h"

पूर्णांक mlx5dr_buddy_init(काष्ठा mlx5dr_icm_buddy_mem *buddy,
		      अचिन्हित पूर्णांक max_order)
अणु
	पूर्णांक i;

	buddy->max_order = max_order;

	INIT_LIST_HEAD(&buddy->list_node);
	INIT_LIST_HEAD(&buddy->used_list);
	INIT_LIST_HEAD(&buddy->hot_list);

	buddy->biपंचांगap = kसुस्मृति(buddy->max_order + 1,
				माप(*buddy->biपंचांगap),
				GFP_KERNEL);
	buddy->num_मुक्त = kसुस्मृति(buddy->max_order + 1,
				  माप(*buddy->num_मुक्त),
				  GFP_KERNEL);

	अगर (!buddy->biपंचांगap || !buddy->num_मुक्त)
		जाओ err_मुक्त_all;

	/* Allocating max_order biपंचांगaps, one क्रम each order */

	क्रम (i = 0; i <= buddy->max_order; ++i) अणु
		अचिन्हित पूर्णांक size = 1 << (buddy->max_order - i);

		buddy->biपंचांगap[i] = biपंचांगap_zalloc(size, GFP_KERNEL);
		अगर (!buddy->biपंचांगap[i])
			जाओ err_out_मुक्त_each_bit_per_order;
	पूर्ण

	/* In the beginning, we have only one order that is available क्रम
	 * use (the biggest one), so mark the first bit in both biपंचांगaps.
	 */

	biपंचांगap_set(buddy->biपंचांगap[buddy->max_order], 0, 1);

	buddy->num_मुक्त[buddy->max_order] = 1;

	वापस 0;

err_out_मुक्त_each_bit_per_order:
	क्रम (i = 0; i <= buddy->max_order; ++i)
		biपंचांगap_मुक्त(buddy->biपंचांगap[i]);

err_मुक्त_all:
	kमुक्त(buddy->num_मुक्त);
	kमुक्त(buddy->biपंचांगap);
	वापस -ENOMEM;
पूर्ण

व्योम mlx5dr_buddy_cleanup(काष्ठा mlx5dr_icm_buddy_mem *buddy)
अणु
	पूर्णांक i;

	list_del(&buddy->list_node);

	क्रम (i = 0; i <= buddy->max_order; ++i)
		biपंचांगap_मुक्त(buddy->biपंचांगap[i]);

	kमुक्त(buddy->num_मुक्त);
	kमुक्त(buddy->biपंचांगap);
पूर्ण

अटल पूर्णांक dr_buddy_find_मुक्त_seg(काष्ठा mlx5dr_icm_buddy_mem *buddy,
				  अचिन्हित पूर्णांक start_order,
				  अचिन्हित पूर्णांक *segment,
				  अचिन्हित पूर्णांक *order)
अणु
	अचिन्हित पूर्णांक seg, order_iter, m;

	क्रम (order_iter = start_order;
	     order_iter <= buddy->max_order; ++order_iter) अणु
		अगर (!buddy->num_मुक्त[order_iter])
			जारी;

		m = 1 << (buddy->max_order - order_iter);
		seg = find_first_bit(buddy->biपंचांगap[order_iter], m);

		अगर (WARN(seg >= m,
			 "ICM Buddy: failed finding free mem for order %d\n",
			 order_iter))
			वापस -ENOMEM;

		अवरोध;
	पूर्ण

	अगर (order_iter > buddy->max_order)
		वापस -ENOMEM;

	*segment = seg;
	*order = order_iter;
	वापस 0;
पूर्ण

/**
 * mlx5dr_buddy_alloc_mem() - Update second level biपंचांगap.
 * @buddy: Buddy to update.
 * @order: Order of the buddy to update.
 * @segment: Segment number.
 *
 * This function finds the first area of the ICM memory managed by this buddy.
 * It uses the data काष्ठाures of the buddy प्रणाली in order to find the first
 * area of मुक्त place, starting from the current order till the maximum order
 * in the प्रणाली.
 *
 * Return: 0 when segment is set, non-zero error status otherwise.
 *
 * The function वापसs the location (segment) in the whole buddy ICM memory
 * area - the index of the memory segment that is available क्रम use.
 */
पूर्णांक mlx5dr_buddy_alloc_mem(काष्ठा mlx5dr_icm_buddy_mem *buddy,
			   अचिन्हित पूर्णांक order,
			   अचिन्हित पूर्णांक *segment)
अणु
	अचिन्हित पूर्णांक seg, order_iter;
	पूर्णांक err;

	err = dr_buddy_find_मुक्त_seg(buddy, order, &seg, &order_iter);
	अगर (err)
		वापस err;

	biपंचांगap_clear(buddy->biपंचांगap[order_iter], seg, 1);
	--buddy->num_मुक्त[order_iter];

	/* If we found मुक्त memory in some order that is bigger than the
	 * required order, we need to split every order between the required
	 * order and the order that we found पूर्णांकo two parts, and mark accordingly.
	 */
	जबतक (order_iter > order) अणु
		--order_iter;
		seg <<= 1;
		biपंचांगap_set(buddy->biपंचांगap[order_iter], seg ^ 1, 1);
		++buddy->num_मुक्त[order_iter];
	पूर्ण

	seg <<= order;
	*segment = seg;

	वापस 0;
पूर्ण

व्योम mlx5dr_buddy_मुक्त_mem(काष्ठा mlx5dr_icm_buddy_mem *buddy,
			   अचिन्हित पूर्णांक seg, अचिन्हित पूर्णांक order)
अणु
	seg >>= order;

	/* Whenever a segment is मुक्त,
	 * the mem is added to the buddy that gave it.
	 */
	जबतक (test_bit(seg ^ 1, buddy->biपंचांगap[order])) अणु
		biपंचांगap_clear(buddy->biपंचांगap[order], seg ^ 1, 1);
		--buddy->num_मुक्त[order];
		seg >>= 1;
		++order;
	पूर्ण
	biपंचांगap_set(buddy->biपंचांगap[order], seg, 1);

	++buddy->num_मुक्त[order];
पूर्ण

