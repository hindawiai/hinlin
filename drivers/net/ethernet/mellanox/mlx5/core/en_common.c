<शैली गुरु>
/*
 * Copyright (c) 2016, Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश "en.h"

/* mlx5e global resources should be placed in this file.
 * Global resources are common to all the netdevices crated on the same nic.
 */

पूर्णांक mlx5e_create_tir(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5e_tir *tir, u32 *in)
अणु
	काष्ठा mlx5e_hw_objs *res = &mdev->mlx5e_res.hw_objs;
	पूर्णांक err;

	err = mlx5_core_create_tir(mdev, in, &tir->tirn);
	अगर (err)
		वापस err;

	mutex_lock(&res->td.list_lock);
	list_add(&tir->list, &res->td.tirs_list);
	mutex_unlock(&res->td.list_lock);

	वापस 0;
पूर्ण

व्योम mlx5e_destroy_tir(काष्ठा mlx5_core_dev *mdev,
		       काष्ठा mlx5e_tir *tir)
अणु
	काष्ठा mlx5e_hw_objs *res = &mdev->mlx5e_res.hw_objs;

	mutex_lock(&res->td.list_lock);
	mlx5_core_destroy_tir(mdev, tir->tirn);
	list_del(&tir->list);
	mutex_unlock(&res->td.list_lock);
पूर्ण

व्योम mlx5e_mkey_set_relaxed_ordering(काष्ठा mlx5_core_dev *mdev, व्योम *mkc)
अणु
	bool ro_pci_enable = pcie_relaxed_ordering_enabled(mdev->pdev);
	bool ro_ग_लिखो = MLX5_CAP_GEN(mdev, relaxed_ordering_ग_लिखो);
	bool ro_पढ़ो = MLX5_CAP_GEN(mdev, relaxed_ordering_पढ़ो);

	MLX5_SET(mkc, mkc, relaxed_ordering_पढ़ो, ro_pci_enable && ro_पढ़ो);
	MLX5_SET(mkc, mkc, relaxed_ordering_ग_लिखो, ro_pci_enable && ro_ग_लिखो);
पूर्ण

अटल पूर्णांक mlx5e_create_mkey(काष्ठा mlx5_core_dev *mdev, u32 pdn,
			     काष्ठा mlx5_core_mkey *mkey)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_mkey_in);
	व्योम *mkc;
	u32 *in;
	पूर्णांक err;

	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in)
		वापस -ENOMEM;

	mkc = MLX5_ADDR_OF(create_mkey_in, in, memory_key_mkey_entry);
	MLX5_SET(mkc, mkc, access_mode_1_0, MLX5_MKC_ACCESS_MODE_PA);
	MLX5_SET(mkc, mkc, lw, 1);
	MLX5_SET(mkc, mkc, lr, 1);
	mlx5e_mkey_set_relaxed_ordering(mdev, mkc);
	MLX5_SET(mkc, mkc, pd, pdn);
	MLX5_SET(mkc, mkc, length64, 1);
	MLX5_SET(mkc, mkc, qpn, 0xffffff);

	err = mlx5_core_create_mkey(mdev, mkey, in, inlen);

	kvमुक्त(in);
	वापस err;
पूर्ण

पूर्णांक mlx5e_create_mdev_resources(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5e_hw_objs *res = &mdev->mlx5e_res.hw_objs;
	पूर्णांक err;

	err = mlx5_core_alloc_pd(mdev, &res->pdn);
	अगर (err) अणु
		mlx5_core_err(mdev, "alloc pd failed, %d\n", err);
		वापस err;
	पूर्ण

	err = mlx5_core_alloc_transport_करोमुख्य(mdev, &res->td.tdn);
	अगर (err) अणु
		mlx5_core_err(mdev, "alloc td failed, %d\n", err);
		जाओ err_dealloc_pd;
	पूर्ण

	err = mlx5e_create_mkey(mdev, res->pdn, &res->mkey);
	अगर (err) अणु
		mlx5_core_err(mdev, "create mkey failed, %d\n", err);
		जाओ err_dealloc_transport_करोमुख्य;
	पूर्ण

	err = mlx5_alloc_bfreg(mdev, &res->bfreg, false, false);
	अगर (err) अणु
		mlx5_core_err(mdev, "alloc bfreg failed, %d\n", err);
		जाओ err_destroy_mkey;
	पूर्ण

	INIT_LIST_HEAD(&res->td.tirs_list);
	mutex_init(&res->td.list_lock);

	वापस 0;

err_destroy_mkey:
	mlx5_core_destroy_mkey(mdev, &res->mkey);
err_dealloc_transport_करोमुख्य:
	mlx5_core_dealloc_transport_करोमुख्य(mdev, res->td.tdn);
err_dealloc_pd:
	mlx5_core_dealloc_pd(mdev, res->pdn);
	वापस err;
पूर्ण

व्योम mlx5e_destroy_mdev_resources(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5e_hw_objs *res = &mdev->mlx5e_res.hw_objs;

	mlx5_मुक्त_bfreg(mdev, &res->bfreg);
	mlx5_core_destroy_mkey(mdev, &res->mkey);
	mlx5_core_dealloc_transport_करोमुख्य(mdev, res->td.tdn);
	mlx5_core_dealloc_pd(mdev, res->pdn);
	स_रखो(res, 0, माप(*res));
पूर्ण

पूर्णांक mlx5e_refresh_tirs(काष्ठा mlx5e_priv *priv, bool enable_uc_lb,
		       bool enable_mc_lb)
अणु
	काष्ठा mlx5_core_dev *mdev = priv->mdev;
	काष्ठा mlx5e_tir *tir;
	u8 lb_flags = 0;
	पूर्णांक err  = 0;
	u32 tirn = 0;
	पूर्णांक inlen;
	व्योम *in;

	inlen = MLX5_ST_SZ_BYTES(modअगरy_tir_in);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (enable_uc_lb)
		lb_flags = MLX5_TIRC_SELF_LB_BLOCK_BLOCK_UNICAST;

	अगर (enable_mc_lb)
		lb_flags |= MLX5_TIRC_SELF_LB_BLOCK_BLOCK_MULTICAST;

	अगर (lb_flags)
		MLX5_SET(modअगरy_tir_in, in, ctx.self_lb_block, lb_flags);

	MLX5_SET(modअगरy_tir_in, in, biपंचांगask.self_lb_en, 1);

	mutex_lock(&mdev->mlx5e_res.hw_objs.td.list_lock);
	list_क्रम_each_entry(tir, &mdev->mlx5e_res.hw_objs.td.tirs_list, list) अणु
		tirn = tir->tirn;
		err = mlx5_core_modअगरy_tir(mdev, tirn, in);
		अगर (err)
			जाओ out;
	पूर्ण

out:
	kvमुक्त(in);
	अगर (err)
		netdev_err(priv->netdev, "refresh tir(0x%x) failed, %d\n", tirn, err);
	mutex_unlock(&mdev->mlx5e_res.hw_objs.td.list_lock);

	वापस err;
पूर्ण
