<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2018 Mellanox Technologies. All rights reserved */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/objagg.h>

काष्ठा tokey अणु
	अचिन्हित पूर्णांक id;
पूर्ण;

#घोषणा NUM_KEYS 32

अटल पूर्णांक key_id_index(अचिन्हित पूर्णांक key_id)
अणु
	अगर (key_id >= NUM_KEYS) अणु
		WARN_ON(1);
		वापस 0;
	पूर्ण
	वापस key_id;
पूर्ण

#घोषणा BUF_LEN 128

काष्ठा world अणु
	अचिन्हित पूर्णांक root_count;
	अचिन्हित पूर्णांक delta_count;
	अक्षर next_root_buf[BUF_LEN];
	काष्ठा objagg_obj *objagg_objs[NUM_KEYS];
	अचिन्हित पूर्णांक key_refs[NUM_KEYS];
पूर्ण;

काष्ठा root अणु
	काष्ठा tokey key;
	अक्षर buf[BUF_LEN];
पूर्ण;

काष्ठा delta अणु
	अचिन्हित पूर्णांक key_id_dअगरf;
पूर्ण;

अटल काष्ठा objagg_obj *world_obj_get(काष्ठा world *world,
					काष्ठा objagg *objagg,
					अचिन्हित पूर्णांक key_id)
अणु
	काष्ठा objagg_obj *objagg_obj;
	काष्ठा tokey key;
	पूर्णांक err;

	key.id = key_id;
	objagg_obj = objagg_obj_get(objagg, &key);
	अगर (IS_ERR(objagg_obj)) अणु
		pr_err("Key %u: Failed to get object.\n", key_id);
		वापस objagg_obj;
	पूर्ण
	अगर (!world->key_refs[key_id_index(key_id)]) अणु
		world->objagg_objs[key_id_index(key_id)] = objagg_obj;
	पूर्ण अन्यथा अगर (world->objagg_objs[key_id_index(key_id)] != objagg_obj) अणु
		pr_err("Key %u: God another object for the same key.\n",
		       key_id);
		err = -EINVAL;
		जाओ err_key_id_check;
	पूर्ण
	world->key_refs[key_id_index(key_id)]++;
	वापस objagg_obj;

err_key_id_check:
	objagg_obj_put(objagg, objagg_obj);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम world_obj_put(काष्ठा world *world, काष्ठा objagg *objagg,
			  अचिन्हित पूर्णांक key_id)
अणु
	काष्ठा objagg_obj *objagg_obj;

	अगर (!world->key_refs[key_id_index(key_id)])
		वापस;
	objagg_obj = world->objagg_objs[key_id_index(key_id)];
	objagg_obj_put(objagg, objagg_obj);
	world->key_refs[key_id_index(key_id)]--;
पूर्ण

#घोषणा MAX_KEY_ID_DIFF 5

अटल bool delta_check(व्योम *priv, स्थिर व्योम *parent_obj, स्थिर व्योम *obj)
अणु
	स्थिर काष्ठा tokey *parent_key = parent_obj;
	स्थिर काष्ठा tokey *key = obj;
	पूर्णांक dअगरf = key->id - parent_key->id;

	वापस dअगरf >= 0 && dअगरf <= MAX_KEY_ID_DIFF;
पूर्ण

अटल व्योम *delta_create(व्योम *priv, व्योम *parent_obj, व्योम *obj)
अणु
	काष्ठा tokey *parent_key = parent_obj;
	काष्ठा world *world = priv;
	काष्ठा tokey *key = obj;
	पूर्णांक dअगरf = key->id - parent_key->id;
	काष्ठा delta *delta;

	अगर (!delta_check(priv, parent_obj, obj))
		वापस ERR_PTR(-EINVAL);

	delta = kzalloc(माप(*delta), GFP_KERNEL);
	अगर (!delta)
		वापस ERR_PTR(-ENOMEM);
	delta->key_id_dअगरf = dअगरf;
	world->delta_count++;
	वापस delta;
पूर्ण

अटल व्योम delta_destroy(व्योम *priv, व्योम *delta_priv)
अणु
	काष्ठा delta *delta = delta_priv;
	काष्ठा world *world = priv;

	world->delta_count--;
	kमुक्त(delta);
पूर्ण

अटल व्योम *root_create(व्योम *priv, व्योम *obj, अचिन्हित पूर्णांक id)
अणु
	काष्ठा world *world = priv;
	काष्ठा tokey *key = obj;
	काष्ठा root *root;

	root = kzalloc(माप(*root), GFP_KERNEL);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);
	स_नकल(&root->key, key, माप(root->key));
	स_नकल(root->buf, world->next_root_buf, माप(root->buf));
	world->root_count++;
	वापस root;
पूर्ण

अटल व्योम root_destroy(व्योम *priv, व्योम *root_priv)
अणु
	काष्ठा root *root = root_priv;
	काष्ठा world *world = priv;

	world->root_count--;
	kमुक्त(root);
पूर्ण

अटल पूर्णांक test_nodelta_obj_get(काष्ठा world *world, काष्ठा objagg *objagg,
				अचिन्हित पूर्णांक key_id, bool should_create_root)
अणु
	अचिन्हित पूर्णांक orig_root_count = world->root_count;
	काष्ठा objagg_obj *objagg_obj;
	स्थिर काष्ठा root *root;
	पूर्णांक err;

	अगर (should_create_root)
		pअक्रमom_bytes(world->next_root_buf,
			      माप(world->next_root_buf));

	objagg_obj = world_obj_get(world, objagg, key_id);
	अगर (IS_ERR(objagg_obj)) अणु
		pr_err("Key %u: Failed to get object.\n", key_id);
		वापस PTR_ERR(objagg_obj);
	पूर्ण
	अगर (should_create_root) अणु
		अगर (world->root_count != orig_root_count + 1) अणु
			pr_err("Key %u: Root was not created\n", key_id);
			err = -EINVAL;
			जाओ err_check_root_count;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (world->root_count != orig_root_count) अणु
			pr_err("Key %u: Root was incorrectly created\n",
			       key_id);
			err = -EINVAL;
			जाओ err_check_root_count;
		पूर्ण
	पूर्ण
	root = objagg_obj_root_priv(objagg_obj);
	अगर (root->key.id != key_id) अणु
		pr_err("Key %u: Root has unexpected key id\n", key_id);
		err = -EINVAL;
		जाओ err_check_key_id;
	पूर्ण
	अगर (should_create_root &&
	    स_भेद(world->next_root_buf, root->buf, माप(root->buf))) अणु
		pr_err("Key %u: Buffer does not match the expected content\n",
		       key_id);
		err = -EINVAL;
		जाओ err_check_buf;
	पूर्ण
	वापस 0;

err_check_buf:
err_check_key_id:
err_check_root_count:
	objagg_obj_put(objagg, objagg_obj);
	वापस err;
पूर्ण

अटल पूर्णांक test_nodelta_obj_put(काष्ठा world *world, काष्ठा objagg *objagg,
				अचिन्हित पूर्णांक key_id, bool should_destroy_root)
अणु
	अचिन्हित पूर्णांक orig_root_count = world->root_count;

	world_obj_put(world, objagg, key_id);

	अगर (should_destroy_root) अणु
		अगर (world->root_count != orig_root_count - 1) अणु
			pr_err("Key %u: Root was not destroyed\n", key_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (world->root_count != orig_root_count) अणु
			pr_err("Key %u: Root was incorrectly destroyed\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_stats_zero(काष्ठा objagg *objagg)
अणु
	स्थिर काष्ठा objagg_stats *stats;
	पूर्णांक err = 0;

	stats = objagg_stats_get(objagg);
	अगर (IS_ERR(stats))
		वापस PTR_ERR(stats);

	अगर (stats->stats_info_count != 0) अणु
		pr_err("Stats: Object count is not zero while it should be\n");
		err = -EINVAL;
	पूर्ण

	objagg_stats_put(stats);
	वापस err;
पूर्ण

अटल पूर्णांक check_stats_nodelta(काष्ठा objagg *objagg)
अणु
	स्थिर काष्ठा objagg_stats *stats;
	पूर्णांक i;
	पूर्णांक err;

	stats = objagg_stats_get(objagg);
	अगर (IS_ERR(stats))
		वापस PTR_ERR(stats);

	अगर (stats->stats_info_count != NUM_KEYS) अणु
		pr_err("Stats: Unexpected object count (%u expected, %u returned)\n",
		       NUM_KEYS, stats->stats_info_count);
		err = -EINVAL;
		जाओ stats_put;
	पूर्ण

	क्रम (i = 0; i < stats->stats_info_count; i++) अणु
		अगर (stats->stats_info[i].stats.user_count != 2) अणु
			pr_err("Stats: incorrect user count\n");
			err = -EINVAL;
			जाओ stats_put;
		पूर्ण
		अगर (stats->stats_info[i].stats.delta_user_count != 2) अणु
			pr_err("Stats: incorrect delta user count\n");
			err = -EINVAL;
			जाओ stats_put;
		पूर्ण
	पूर्ण
	err = 0;

stats_put:
	objagg_stats_put(stats);
	वापस err;
पूर्ण

अटल bool delta_check_dummy(व्योम *priv, स्थिर व्योम *parent_obj,
			      स्थिर व्योम *obj)
अणु
	वापस false;
पूर्ण

अटल व्योम *delta_create_dummy(व्योम *priv, व्योम *parent_obj, व्योम *obj)
अणु
	वापस ERR_PTR(-EOPNOTSUPP);
पूर्ण

अटल व्योम delta_destroy_dummy(व्योम *priv, व्योम *delta_priv)
अणु
पूर्ण

अटल स्थिर काष्ठा objagg_ops nodelta_ops = अणु
	.obj_size = माप(काष्ठा tokey),
	.delta_check = delta_check_dummy,
	.delta_create = delta_create_dummy,
	.delta_destroy = delta_destroy_dummy,
	.root_create = root_create,
	.root_destroy = root_destroy,
पूर्ण;

अटल पूर्णांक test_nodelta(व्योम)
अणु
	काष्ठा world world = अणुपूर्ण;
	काष्ठा objagg *objagg;
	पूर्णांक i;
	पूर्णांक err;

	objagg = objagg_create(&nodelta_ops, शून्य, &world);
	अगर (IS_ERR(objagg))
		वापस PTR_ERR(objagg);

	err = check_stats_zero(objagg);
	अगर (err)
		जाओ err_stats_first_zero;

	/* First round of माला_लो, the root objects should be created */
	क्रम (i = 0; i < NUM_KEYS; i++) अणु
		err = test_nodelta_obj_get(&world, objagg, i, true);
		अगर (err)
			जाओ err_obj_first_get;
	पूर्ण

	/* Do the second round of माला_लो, all roots are alपढ़ोy created,
	 * make sure that no new root is created
	 */
	क्रम (i = 0; i < NUM_KEYS; i++) अणु
		err = test_nodelta_obj_get(&world, objagg, i, false);
		अगर (err)
			जाओ err_obj_second_get;
	पूर्ण

	err = check_stats_nodelta(objagg);
	अगर (err)
		जाओ err_stats_nodelta;

	क्रम (i = NUM_KEYS - 1; i >= 0; i--) अणु
		err = test_nodelta_obj_put(&world, objagg, i, false);
		अगर (err)
			जाओ err_obj_first_put;
	पूर्ण
	क्रम (i = NUM_KEYS - 1; i >= 0; i--) अणु
		err = test_nodelta_obj_put(&world, objagg, i, true);
		अगर (err)
			जाओ err_obj_second_put;
	पूर्ण

	err = check_stats_zero(objagg);
	अगर (err)
		जाओ err_stats_second_zero;

	objagg_destroy(objagg);
	वापस 0;

err_stats_nodelta:
err_obj_first_put:
err_obj_second_get:
	क्रम (i--; i >= 0; i--)
		world_obj_put(&world, objagg, i);

	i = NUM_KEYS;
err_obj_first_get:
err_obj_second_put:
	क्रम (i--; i >= 0; i--)
		world_obj_put(&world, objagg, i);
err_stats_first_zero:
err_stats_second_zero:
	objagg_destroy(objagg);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा objagg_ops delta_ops = अणु
	.obj_size = माप(काष्ठा tokey),
	.delta_check = delta_check,
	.delta_create = delta_create,
	.delta_destroy = delta_destroy,
	.root_create = root_create,
	.root_destroy = root_destroy,
पूर्ण;

क्रमागत action अणु
	ACTION_GET,
	ACTION_PUT,
पूर्ण;

क्रमागत expect_delta अणु
	EXPECT_DELTA_SAME,
	EXPECT_DELTA_INC,
	EXPECT_DELTA_DEC,
पूर्ण;

क्रमागत expect_root अणु
	EXPECT_ROOT_SAME,
	EXPECT_ROOT_INC,
	EXPECT_ROOT_DEC,
पूर्ण;

काष्ठा expect_stats_info अणु
	काष्ठा objagg_obj_stats stats;
	bool is_root;
	अचिन्हित पूर्णांक key_id;
पूर्ण;

काष्ठा expect_stats अणु
	अचिन्हित पूर्णांक info_count;
	काष्ठा expect_stats_info info[NUM_KEYS];
पूर्ण;

काष्ठा action_item अणु
	अचिन्हित पूर्णांक key_id;
	क्रमागत action action;
	क्रमागत expect_delta expect_delta;
	क्रमागत expect_root expect_root;
	काष्ठा expect_stats expect_stats;
पूर्ण;

#घोषणा EXPECT_STATS(count, ...)		\
अणु						\
	.info_count = count,			\
	.info = अणु __VA_ARGS__ पूर्ण			\
पूर्ण

#घोषणा ROOT(key_id, user_count, delta_user_count)	\
	अणुअणुuser_count, delta_user_countपूर्ण, true, key_idपूर्ण

#घोषणा DELTA(key_id, user_count)			\
	अणुअणुuser_count, user_countपूर्ण, false, key_idपूर्ण

अटल स्थिर काष्ठा action_item action_items[] = अणु
	अणु
		1, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_INC,
		EXPECT_STATS(1, ROOT(1, 1, 1)),
	पूर्ण,	/* r: 1			d: */
	अणु
		7, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_INC,
		EXPECT_STATS(2, ROOT(1, 1, 1), ROOT(7, 1, 1)),
	पूर्ण,	/* r: 1, 7		d: */
	अणु
		3, ACTION_GET, EXPECT_DELTA_INC, EXPECT_ROOT_SAME,
		EXPECT_STATS(3, ROOT(1, 1, 2), ROOT(7, 1, 1),
				DELTA(3, 1)),
	पूर्ण,	/* r: 1, 7		d: 3^1 */
	अणु
		5, ACTION_GET, EXPECT_DELTA_INC, EXPECT_ROOT_SAME,
		EXPECT_STATS(4, ROOT(1, 1, 3), ROOT(7, 1, 1),
				DELTA(3, 1), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 7		d: 3^1, 5^1 */
	अणु
		3, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(4, ROOT(1, 1, 4), ROOT(7, 1, 1),
				DELTA(3, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 7		d: 3^1, 3^1, 5^1 */
	अणु
		1, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(4, ROOT(1, 2, 5), ROOT(7, 1, 1),
				DELTA(3, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 1, 7		d: 3^1, 3^1, 5^1 */
	अणु
		30, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_INC,
		EXPECT_STATS(5, ROOT(1, 2, 5), ROOT(7, 1, 1), ROOT(30, 1, 1),
				DELTA(3, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 1, 7, 30	d: 3^1, 3^1, 5^1 */
	अणु
		8, ACTION_GET, EXPECT_DELTA_INC, EXPECT_ROOT_SAME,
		EXPECT_STATS(6, ROOT(1, 2, 5), ROOT(7, 1, 2), ROOT(30, 1, 1),
				DELTA(3, 2), DELTA(5, 1), DELTA(8, 1)),
	पूर्ण,	/* r: 1, 1, 7, 30	d: 3^1, 3^1, 5^1, 8^7 */
	अणु
		8, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(6, ROOT(1, 2, 5), ROOT(7, 1, 3), ROOT(30, 1, 1),
				DELTA(3, 2), DELTA(8, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 1, 7, 30	d: 3^1, 3^1, 5^1, 8^7, 8^7 */
	अणु
		3, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(6, ROOT(1, 2, 4), ROOT(7, 1, 3), ROOT(30, 1, 1),
				DELTA(8, 2), DELTA(3, 1), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 1, 7, 30	d: 3^1, 5^1, 8^7, 8^7 */
	अणु
		3, ACTION_PUT, EXPECT_DELTA_DEC, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(1, 2, 3), ROOT(7, 1, 3), ROOT(30, 1, 1),
				DELTA(8, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 1, 7, 30	d: 5^1, 8^7, 8^7 */
	अणु
		1, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(7, 1, 3), ROOT(1, 1, 2), ROOT(30, 1, 1),
				DELTA(8, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 1, 7, 30		d: 5^1, 8^7, 8^7 */
	अणु
		1, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(7, 1, 3), ROOT(30, 1, 1), ROOT(1, 0, 1),
				DELTA(8, 2), DELTA(5, 1)),
	पूर्ण,	/* r: 7, 30		d: 5^1, 8^7, 8^7 */
	अणु
		5, ACTION_PUT, EXPECT_DELTA_DEC, EXPECT_ROOT_DEC,
		EXPECT_STATS(3, ROOT(7, 1, 3), ROOT(30, 1, 1),
				DELTA(8, 2)),
	पूर्ण,	/* r: 7, 30		d: 8^7, 8^7 */
	अणु
		5, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_INC,
		EXPECT_STATS(4, ROOT(7, 1, 3), ROOT(30, 1, 1), ROOT(5, 1, 1),
				DELTA(8, 2)),
	पूर्ण,	/* r: 7, 30, 5		d: 8^7, 8^7 */
	अणु
		6, ACTION_GET, EXPECT_DELTA_INC, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(7, 1, 3), ROOT(5, 1, 2), ROOT(30, 1, 1),
				DELTA(8, 2), DELTA(6, 1)),
	पूर्ण,	/* r: 7, 30, 5		d: 8^7, 8^7, 6^5 */
	अणु
		8, ACTION_GET, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(7, 1, 4), ROOT(5, 1, 2), ROOT(30, 1, 1),
				DELTA(8, 3), DELTA(6, 1)),
	पूर्ण,	/* r: 7, 30, 5		d: 8^7, 8^7, 8^7, 6^5 */
	अणु
		8, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(7, 1, 3), ROOT(5, 1, 2), ROOT(30, 1, 1),
				DELTA(8, 2), DELTA(6, 1)),
	पूर्ण,	/* r: 7, 30, 5		d: 8^7, 8^7, 6^5 */
	अणु
		8, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(7, 1, 2), ROOT(5, 1, 2), ROOT(30, 1, 1),
				DELTA(8, 1), DELTA(6, 1)),
	पूर्ण,	/* r: 7, 30, 5		d: 8^7, 6^5 */
	अणु
		8, ACTION_PUT, EXPECT_DELTA_DEC, EXPECT_ROOT_SAME,
		EXPECT_STATS(4, ROOT(5, 1, 2), ROOT(7, 1, 1), ROOT(30, 1, 1),
				DELTA(6, 1)),
	पूर्ण,	/* r: 7, 30, 5		d: 6^5 */
	अणु
		8, ACTION_GET, EXPECT_DELTA_INC, EXPECT_ROOT_SAME,
		EXPECT_STATS(5, ROOT(5, 1, 3), ROOT(7, 1, 1), ROOT(30, 1, 1),
				DELTA(6, 1), DELTA(8, 1)),
	पूर्ण,	/* r: 7, 30, 5		d: 6^5, 8^5 */
	अणु
		7, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_DEC,
		EXPECT_STATS(4, ROOT(5, 1, 3), ROOT(30, 1, 1),
				DELTA(6, 1), DELTA(8, 1)),
	पूर्ण,	/* r: 30, 5		d: 6^5, 8^5 */
	अणु
		30, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_DEC,
		EXPECT_STATS(3, ROOT(5, 1, 3),
				DELTA(6, 1), DELTA(8, 1)),
	पूर्ण,	/* r: 5			d: 6^5, 8^5 */
	अणु
		5, ACTION_PUT, EXPECT_DELTA_SAME, EXPECT_ROOT_SAME,
		EXPECT_STATS(3, ROOT(5, 0, 2),
				DELTA(6, 1), DELTA(8, 1)),
	पूर्ण,	/* r:			d: 6^5, 8^5 */
	अणु
		6, ACTION_PUT, EXPECT_DELTA_DEC, EXPECT_ROOT_SAME,
		EXPECT_STATS(2, ROOT(5, 0, 1),
				DELTA(8, 1)),
	पूर्ण,	/* r:			d: 6^5 */
	अणु
		8, ACTION_PUT, EXPECT_DELTA_DEC, EXPECT_ROOT_DEC,
		EXPECT_STATS(0, ),
	पूर्ण,	/* r:			d: */
पूर्ण;

अटल पूर्णांक check_expect(काष्ठा world *world,
			स्थिर काष्ठा action_item *action_item,
			अचिन्हित पूर्णांक orig_delta_count,
			अचिन्हित पूर्णांक orig_root_count)
अणु
	अचिन्हित पूर्णांक key_id = action_item->key_id;

	चयन (action_item->expect_delta) अणु
	हाल EXPECT_DELTA_SAME:
		अगर (orig_delta_count != world->delta_count) अणु
			pr_err("Key %u: Delta count changed while expected to remain the same.\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल EXPECT_DELTA_INC:
		अगर (WARN_ON(action_item->action == ACTION_PUT))
			वापस -EINVAL;
		अगर (orig_delta_count + 1 != world->delta_count) अणु
			pr_err("Key %u: Delta count was not incremented.\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल EXPECT_DELTA_DEC:
		अगर (WARN_ON(action_item->action == ACTION_GET))
			वापस -EINVAL;
		अगर (orig_delta_count - 1 != world->delta_count) अणु
			pr_err("Key %u: Delta count was not decremented.\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	पूर्ण

	चयन (action_item->expect_root) अणु
	हाल EXPECT_ROOT_SAME:
		अगर (orig_root_count != world->root_count) अणु
			pr_err("Key %u: Root count changed while expected to remain the same.\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल EXPECT_ROOT_INC:
		अगर (WARN_ON(action_item->action == ACTION_PUT))
			वापस -EINVAL;
		अगर (orig_root_count + 1 != world->root_count) अणु
			pr_err("Key %u: Root count was not incremented.\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल EXPECT_ROOT_DEC:
		अगर (WARN_ON(action_item->action == ACTION_GET))
			वापस -EINVAL;
		अगर (orig_root_count - 1 != world->root_count) अणु
			pr_err("Key %u: Root count was not decremented.\n",
			       key_id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक obj_to_key_id(काष्ठा objagg_obj *objagg_obj)
अणु
	स्थिर काष्ठा tokey *root_key;
	स्थिर काष्ठा delta *delta;
	अचिन्हित पूर्णांक key_id;

	root_key = objagg_obj_root_priv(objagg_obj);
	key_id = root_key->id;
	delta = objagg_obj_delta_priv(objagg_obj);
	अगर (delta)
		key_id += delta->key_id_dअगरf;
	वापस key_id;
पूर्ण

अटल पूर्णांक
check_expect_stats_nums(स्थिर काष्ठा objagg_obj_stats_info *stats_info,
			स्थिर काष्ठा expect_stats_info *expect_stats_info,
			स्थिर अक्षर **errmsg)
अणु
	अगर (stats_info->is_root != expect_stats_info->is_root) अणु
		अगर (errmsg)
			*errmsg = "Incorrect root/delta indication";
		वापस -EINVAL;
	पूर्ण
	अगर (stats_info->stats.user_count !=
	    expect_stats_info->stats.user_count) अणु
		अगर (errmsg)
			*errmsg = "Incorrect user count";
		वापस -EINVAL;
	पूर्ण
	अगर (stats_info->stats.delta_user_count !=
	    expect_stats_info->stats.delta_user_count) अणु
		अगर (errmsg)
			*errmsg = "Incorrect delta user count";
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
check_expect_stats_key_id(स्थिर काष्ठा objagg_obj_stats_info *stats_info,
			  स्थिर काष्ठा expect_stats_info *expect_stats_info,
			  स्थिर अक्षर **errmsg)
अणु
	अगर (obj_to_key_id(stats_info->objagg_obj) !=
	    expect_stats_info->key_id) अणु
		अगर (errmsg)
			*errmsg = "incorrect key id";
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_expect_stats_neigh(स्थिर काष्ठा objagg_stats *stats,
				    स्थिर काष्ठा expect_stats *expect_stats,
				    पूर्णांक pos)
अणु
	पूर्णांक i;
	पूर्णांक err;

	क्रम (i = pos - 1; i >= 0; i--) अणु
		err = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[pos], शून्य);
		अगर (err)
			अवरोध;
		err = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[pos], शून्य);
		अगर (!err)
			वापस 0;
	पूर्ण
	क्रम (i = pos + 1; i < stats->stats_info_count; i++) अणु
		err = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[pos], शून्य);
		अगर (err)
			अवरोध;
		err = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[pos], शून्य);
		अगर (!err)
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक __check_expect_stats(स्थिर काष्ठा objagg_stats *stats,
				स्थिर काष्ठा expect_stats *expect_stats,
				स्थिर अक्षर **errmsg)
अणु
	पूर्णांक i;
	पूर्णांक err;

	अगर (stats->stats_info_count != expect_stats->info_count) अणु
		*errmsg = "Unexpected object count";
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < stats->stats_info_count; i++) अणु
		err = check_expect_stats_nums(&stats->stats_info[i],
					      &expect_stats->info[i], errmsg);
		अगर (err)
			वापस err;
		err = check_expect_stats_key_id(&stats->stats_info[i],
						&expect_stats->info[i], errmsg);
		अगर (err) अणु
			/* It is possible that one of the neighbor stats with
			 * same numbers have the correct key id, so check it
			 */
			err = check_expect_stats_neigh(stats, expect_stats, i);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_expect_stats(काष्ठा objagg *objagg,
			      स्थिर काष्ठा expect_stats *expect_stats,
			      स्थिर अक्षर **errmsg)
अणु
	स्थिर काष्ठा objagg_stats *stats;
	पूर्णांक err;

	stats = objagg_stats_get(objagg);
	अगर (IS_ERR(stats)) अणु
		*errmsg = "objagg_stats_get() failed.";
		वापस PTR_ERR(stats);
	पूर्ण
	err = __check_expect_stats(stats, expect_stats, errmsg);
	objagg_stats_put(stats);
	वापस err;
पूर्ण

अटल पूर्णांक test_delta_action_item(काष्ठा world *world,
				  काष्ठा objagg *objagg,
				  स्थिर काष्ठा action_item *action_item,
				  bool inverse)
अणु
	अचिन्हित पूर्णांक orig_delta_count = world->delta_count;
	अचिन्हित पूर्णांक orig_root_count = world->root_count;
	अचिन्हित पूर्णांक key_id = action_item->key_id;
	क्रमागत action action = action_item->action;
	काष्ठा objagg_obj *objagg_obj;
	स्थिर अक्षर *errmsg;
	पूर्णांक err;

	अगर (inverse)
		action = action == ACTION_GET ? ACTION_PUT : ACTION_GET;

	चयन (action) अणु
	हाल ACTION_GET:
		objagg_obj = world_obj_get(world, objagg, key_id);
		अगर (IS_ERR(objagg_obj))
			वापस PTR_ERR(objagg_obj);
		अवरोध;
	हाल ACTION_PUT:
		world_obj_put(world, objagg, key_id);
		अवरोध;
	पूर्ण

	अगर (inverse)
		वापस 0;
	err = check_expect(world, action_item,
			   orig_delta_count, orig_root_count);
	अगर (err)
		जाओ errout;

	err = check_expect_stats(objagg, &action_item->expect_stats, &errmsg);
	अगर (err) अणु
		pr_err("Key %u: Stats: %s\n", action_item->key_id, errmsg);
		जाओ errout;
	पूर्ण

	वापस 0;

errout:
	/* This can only happen when action is not inversed.
	 * So in हाल of an error, cleanup by करोing inverse action.
	 */
	test_delta_action_item(world, objagg, action_item, true);
	वापस err;
पूर्ण

अटल पूर्णांक test_delta(व्योम)
अणु
	काष्ठा world world = अणुपूर्ण;
	काष्ठा objagg *objagg;
	पूर्णांक i;
	पूर्णांक err;

	objagg = objagg_create(&delta_ops, शून्य, &world);
	अगर (IS_ERR(objagg))
		वापस PTR_ERR(objagg);

	क्रम (i = 0; i < ARRAY_SIZE(action_items); i++) अणु
		err = test_delta_action_item(&world, objagg,
					     &action_items[i], false);
		अगर (err)
			जाओ err_करो_action_item;
	पूर्ण

	objagg_destroy(objagg);
	वापस 0;

err_करो_action_item:
	क्रम (i--; i >= 0; i--)
		test_delta_action_item(&world, objagg, &action_items[i], true);

	objagg_destroy(objagg);
	वापस err;
पूर्ण

काष्ठा hपूर्णांकs_हाल अणु
	स्थिर अचिन्हित पूर्णांक *key_ids;
	माप_प्रकार key_ids_count;
	काष्ठा expect_stats expect_stats;
	काष्ठा expect_stats expect_stats_hपूर्णांकs;
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक hपूर्णांकs_हाल_key_ids[] = अणु
	1, 7, 3, 5, 3, 1, 30, 8, 8, 5, 6, 8,
पूर्ण;

अटल स्थिर काष्ठा hपूर्णांकs_हाल hपूर्णांकs_हाल = अणु
	.key_ids = hपूर्णांकs_हाल_key_ids,
	.key_ids_count = ARRAY_SIZE(hपूर्णांकs_हाल_key_ids),
	.expect_stats =
		EXPECT_STATS(7, ROOT(1, 2, 7), ROOT(7, 1, 4), ROOT(30, 1, 1),
				DELTA(8, 3), DELTA(3, 2),
				DELTA(5, 2), DELTA(6, 1)),
	.expect_stats_hपूर्णांकs =
		EXPECT_STATS(7, ROOT(3, 2, 9), ROOT(1, 2, 2), ROOT(30, 1, 1),
				DELTA(8, 3), DELTA(5, 2),
				DELTA(6, 1), DELTA(7, 1)),
पूर्ण;

अटल व्योम __pr_debug_stats(स्थिर काष्ठा objagg_stats *stats)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < stats->stats_info_count; i++)
		pr_debug("Stat index %d key %u: u %d, d %d, %s\n", i,
			 obj_to_key_id(stats->stats_info[i].objagg_obj),
			 stats->stats_info[i].stats.user_count,
			 stats->stats_info[i].stats.delta_user_count,
			 stats->stats_info[i].is_root ? "root" : "noroot");
पूर्ण

अटल व्योम pr_debug_stats(काष्ठा objagg *objagg)
अणु
	स्थिर काष्ठा objagg_stats *stats;

	stats = objagg_stats_get(objagg);
	अगर (IS_ERR(stats))
		वापस;
	__pr_debug_stats(stats);
	objagg_stats_put(stats);
पूर्ण

अटल व्योम pr_debug_hपूर्णांकs_stats(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs)
अणु
	स्थिर काष्ठा objagg_stats *stats;

	stats = objagg_hपूर्णांकs_stats_get(objagg_hपूर्णांकs);
	अगर (IS_ERR(stats))
		वापस;
	__pr_debug_stats(stats);
	objagg_stats_put(stats);
पूर्ण

अटल पूर्णांक check_expect_hपूर्णांकs_stats(काष्ठा objagg_hपूर्णांकs *objagg_hपूर्णांकs,
				    स्थिर काष्ठा expect_stats *expect_stats,
				    स्थिर अक्षर **errmsg)
अणु
	स्थिर काष्ठा objagg_stats *stats;
	पूर्णांक err;

	stats = objagg_hपूर्णांकs_stats_get(objagg_hपूर्णांकs);
	अगर (IS_ERR(stats))
		वापस PTR_ERR(stats);
	err = __check_expect_stats(stats, expect_stats, errmsg);
	objagg_stats_put(stats);
	वापस err;
पूर्ण

अटल पूर्णांक test_hपूर्णांकs_हाल(स्थिर काष्ठा hपूर्णांकs_हाल *hपूर्णांकs_हाल)
अणु
	काष्ठा objagg_obj *objagg_obj;
	काष्ठा objagg_hपूर्णांकs *hपूर्णांकs;
	काष्ठा world world2 = अणुपूर्ण;
	काष्ठा world world = अणुपूर्ण;
	काष्ठा objagg *objagg2;
	काष्ठा objagg *objagg;
	स्थिर अक्षर *errmsg;
	पूर्णांक i;
	पूर्णांक err;

	objagg = objagg_create(&delta_ops, शून्य, &world);
	अगर (IS_ERR(objagg))
		वापस PTR_ERR(objagg);

	क्रम (i = 0; i < hपूर्णांकs_हाल->key_ids_count; i++) अणु
		objagg_obj = world_obj_get(&world, objagg,
					   hपूर्णांकs_हाल->key_ids[i]);
		अगर (IS_ERR(objagg_obj)) अणु
			err = PTR_ERR(objagg_obj);
			जाओ err_world_obj_get;
		पूर्ण
	पूर्ण

	pr_debug_stats(objagg);
	err = check_expect_stats(objagg, &hपूर्णांकs_हाल->expect_stats, &errmsg);
	अगर (err) अणु
		pr_err("Stats: %s\n", errmsg);
		जाओ err_check_expect_stats;
	पूर्ण

	hपूर्णांकs = objagg_hपूर्णांकs_get(objagg, OBJAGG_OPT_ALGO_SIMPLE_GREEDY);
	अगर (IS_ERR(hपूर्णांकs)) अणु
		err = PTR_ERR(hपूर्णांकs);
		जाओ err_hपूर्णांकs_get;
	पूर्ण

	pr_debug_hपूर्णांकs_stats(hपूर्णांकs);
	err = check_expect_hपूर्णांकs_stats(hपूर्णांकs, &hपूर्णांकs_हाल->expect_stats_hपूर्णांकs,
				       &errmsg);
	अगर (err) अणु
		pr_err("Hints stats: %s\n", errmsg);
		जाओ err_check_expect_hपूर्णांकs_stats;
	पूर्ण

	objagg2 = objagg_create(&delta_ops, hपूर्णांकs, &world2);
	अगर (IS_ERR(objagg2))
		वापस PTR_ERR(objagg2);

	क्रम (i = 0; i < hपूर्णांकs_हाल->key_ids_count; i++) अणु
		objagg_obj = world_obj_get(&world2, objagg2,
					   hपूर्णांकs_हाल->key_ids[i]);
		अगर (IS_ERR(objagg_obj)) अणु
			err = PTR_ERR(objagg_obj);
			जाओ err_world2_obj_get;
		पूर्ण
	पूर्ण

	pr_debug_stats(objagg2);
	err = check_expect_stats(objagg2, &hपूर्णांकs_हाल->expect_stats_hपूर्णांकs,
				 &errmsg);
	अगर (err) अणु
		pr_err("Stats2: %s\n", errmsg);
		जाओ err_check_expect_stats2;
	पूर्ण

	err = 0;

err_check_expect_stats2:
err_world2_obj_get:
	क्रम (i--; i >= 0; i--)
		world_obj_put(&world2, objagg, hपूर्णांकs_हाल->key_ids[i]);
	i = hपूर्णांकs_हाल->key_ids_count;
	objagg_destroy(objagg2);
err_check_expect_hपूर्णांकs_stats:
	objagg_hपूर्णांकs_put(hपूर्णांकs);
err_hपूर्णांकs_get:
err_check_expect_stats:
err_world_obj_get:
	क्रम (i--; i >= 0; i--)
		world_obj_put(&world, objagg, hपूर्णांकs_हाल->key_ids[i]);

	objagg_destroy(objagg);
	वापस err;
पूर्ण
अटल पूर्णांक test_hपूर्णांकs(व्योम)
अणु
	वापस test_hपूर्णांकs_हाल(&hपूर्णांकs_हाल);
पूर्ण

अटल पूर्णांक __init test_objagg_init(व्योम)
अणु
	पूर्णांक err;

	err = test_nodelta();
	अगर (err)
		वापस err;
	err = test_delta();
	अगर (err)
		वापस err;
	वापस test_hपूर्णांकs();
पूर्ण

अटल व्योम __निकास test_objagg_निकास(व्योम)
अणु
पूर्ण

module_init(test_objagg_init);
module_निकास(test_objagg_निकास);
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Jiri Pirko <jiri@mellanox.com>");
MODULE_DESCRIPTION("Test module for objagg");
