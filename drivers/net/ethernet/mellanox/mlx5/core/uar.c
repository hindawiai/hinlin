<शैली गुरु>
/*
 * Copyright (c) 2013-2015, Mellanox Technologies. All rights reserved.
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

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/io-mapping.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"

पूर्णांक mlx5_cmd_alloc_uar(काष्ठा mlx5_core_dev *dev, u32 *uarn)
अणु
	u32 out[MLX5_ST_SZ_DW(alloc_uar_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(alloc_uar_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(alloc_uar_in, in, opcode, MLX5_CMD_OP_ALLOC_UAR);
	err = mlx5_cmd_exec_inout(dev, alloc_uar, in, out);
	अगर (!err)
		*uarn = MLX5_GET(alloc_uar_out, out, uar);
	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_alloc_uar);

पूर्णांक mlx5_cmd_मुक्त_uar(काष्ठा mlx5_core_dev *dev, u32 uarn)
अणु
	u32 in[MLX5_ST_SZ_DW(dealloc_uar_in)] = अणुपूर्ण;

	MLX5_SET(dealloc_uar_in, in, opcode, MLX5_CMD_OP_DEALLOC_UAR);
	MLX5_SET(dealloc_uar_in, in, uar, uarn);
	वापस mlx5_cmd_exec_in(dev, dealloc_uar, in);
पूर्ण
EXPORT_SYMBOL(mlx5_cmd_मुक्त_uar);

अटल पूर्णांक uars_per_sys_page(काष्ठा mlx5_core_dev *mdev)
अणु
	अगर (MLX5_CAP_GEN(mdev, uar_4k))
		वापस MLX5_CAP_GEN(mdev, num_of_uars_per_page);

	वापस 1;
पूर्ण

अटल u64 uar2pfn(काष्ठा mlx5_core_dev *mdev, u32 index)
अणु
	u32 प्रणाली_page_index;

	अगर (MLX5_CAP_GEN(mdev, uar_4k))
		प्रणाली_page_index = index >> (PAGE_SHIFT - MLX5_ADAPTER_PAGE_SHIFT);
	अन्यथा
		प्रणाली_page_index = index;

	वापस (mdev->bar_addr >> PAGE_SHIFT) + प्रणाली_page_index;
पूर्ण

अटल व्योम up_rel_func(काष्ठा kref *kref)
अणु
	काष्ठा mlx5_uars_page *up = container_of(kref, काष्ठा mlx5_uars_page, ref_count);

	list_del(&up->list);
	iounmap(up->map);
	अगर (mlx5_cmd_मुक्त_uar(up->mdev, up->index))
		mlx5_core_warn(up->mdev, "failed to free uar index %d\n", up->index);
	biपंचांगap_मुक्त(up->reg_biपंचांगap);
	biपंचांगap_मुक्त(up->fp_biपंचांगap);
	kमुक्त(up);
पूर्ण

अटल काष्ठा mlx5_uars_page *alloc_uars_page(काष्ठा mlx5_core_dev *mdev,
					      bool map_wc)
अणु
	काष्ठा mlx5_uars_page *up;
	पूर्णांक err = -ENOMEM;
	phys_addr_t pfn;
	पूर्णांक bfregs;
	पूर्णांक i;

	bfregs = uars_per_sys_page(mdev) * MLX5_BFREGS_PER_UAR;
	up = kzalloc(माप(*up), GFP_KERNEL);
	अगर (!up)
		वापस ERR_PTR(err);

	up->mdev = mdev;
	up->reg_biपंचांगap = biपंचांगap_zalloc(bfregs, GFP_KERNEL);
	अगर (!up->reg_biपंचांगap)
		जाओ error1;

	up->fp_biपंचांगap = biपंचांगap_zalloc(bfregs, GFP_KERNEL);
	अगर (!up->fp_biपंचांगap)
		जाओ error1;

	क्रम (i = 0; i < bfregs; i++)
		अगर ((i % MLX5_BFREGS_PER_UAR) < MLX5_NON_FP_BFREGS_PER_UAR)
			set_bit(i, up->reg_biपंचांगap);
		अन्यथा
			set_bit(i, up->fp_biपंचांगap);

	up->bfregs = bfregs;
	up->fp_avail = bfregs * MLX5_FP_BFREGS_PER_UAR / MLX5_BFREGS_PER_UAR;
	up->reg_avail = bfregs * MLX5_NON_FP_BFREGS_PER_UAR / MLX5_BFREGS_PER_UAR;

	err = mlx5_cmd_alloc_uar(mdev, &up->index);
	अगर (err) अणु
		mlx5_core_warn(mdev, "mlx5_cmd_alloc_uar() failed, %d\n", err);
		जाओ error1;
	पूर्ण

	pfn = uar2pfn(mdev, up->index);
	अगर (map_wc) अणु
		up->map = ioremap_wc(pfn << PAGE_SHIFT, PAGE_SIZE);
		अगर (!up->map) अणु
			err = -EAGAIN;
			जाओ error2;
		पूर्ण
	पूर्ण अन्यथा अणु
		up->map = ioremap(pfn << PAGE_SHIFT, PAGE_SIZE);
		अगर (!up->map) अणु
			err = -ENOMEM;
			जाओ error2;
		पूर्ण
	पूर्ण
	kref_init(&up->ref_count);
	mlx5_core_dbg(mdev, "allocated UAR page: index %d, total bfregs %d\n",
		      up->index, up->bfregs);
	वापस up;

error2:
	अगर (mlx5_cmd_मुक्त_uar(mdev, up->index))
		mlx5_core_warn(mdev, "failed to free uar index %d\n", up->index);
error1:
	biपंचांगap_मुक्त(up->fp_biपंचांगap);
	biपंचांगap_मुक्त(up->reg_biपंचांगap);
	kमुक्त(up);
	वापस ERR_PTR(err);
पूर्ण

काष्ठा mlx5_uars_page *mlx5_get_uars_page(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_uars_page *ret;

	mutex_lock(&mdev->priv.bfregs.reg_head.lock);
	अगर (!list_empty(&mdev->priv.bfregs.reg_head.list)) अणु
		ret = list_first_entry(&mdev->priv.bfregs.reg_head.list,
				       काष्ठा mlx5_uars_page, list);
		kref_get(&ret->ref_count);
		जाओ out;
	पूर्ण
	ret = alloc_uars_page(mdev, false);
	अगर (IS_ERR(ret))
		जाओ out;
	list_add(&ret->list, &mdev->priv.bfregs.reg_head.list);
out:
	mutex_unlock(&mdev->priv.bfregs.reg_head.lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(mlx5_get_uars_page);

व्योम mlx5_put_uars_page(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_uars_page *up)
अणु
	mutex_lock(&mdev->priv.bfregs.reg_head.lock);
	kref_put(&up->ref_count, up_rel_func);
	mutex_unlock(&mdev->priv.bfregs.reg_head.lock);
पूर्ण
EXPORT_SYMBOL(mlx5_put_uars_page);

अटल अचिन्हित दीर्घ map_offset(काष्ठा mlx5_core_dev *mdev, पूर्णांक dbi)
अणु
	/* वापस the offset in bytes from the start of the page to the
	 * blue flame area of the UAR
	 */
	वापस dbi / MLX5_BFREGS_PER_UAR * MLX5_ADAPTER_PAGE_SIZE +
	       (dbi % MLX5_BFREGS_PER_UAR) *
	       (1 << MLX5_CAP_GEN(mdev, log_bf_reg_size)) + MLX5_BF_OFFSET;
पूर्ण

अटल पूर्णांक alloc_bfreg(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_sq_bfreg *bfreg,
		       bool map_wc, bool fast_path)
अणु
	काष्ठा mlx5_bfreg_data *bfregs;
	काष्ठा mlx5_uars_page *up;
	काष्ठा list_head *head;
	अचिन्हित दीर्घ *biपंचांगap;
	अचिन्हित पूर्णांक *avail;
	काष्ठा mutex *lock;  /* poपूर्णांकer to right mutex */
	पूर्णांक dbi;

	bfregs = &mdev->priv.bfregs;
	अगर (map_wc) अणु
		head = &bfregs->wc_head.list;
		lock = &bfregs->wc_head.lock;
	पूर्ण अन्यथा अणु
		head = &bfregs->reg_head.list;
		lock = &bfregs->reg_head.lock;
	पूर्ण
	mutex_lock(lock);
	अगर (list_empty(head)) अणु
		up = alloc_uars_page(mdev, map_wc);
		अगर (IS_ERR(up)) अणु
			mutex_unlock(lock);
			वापस PTR_ERR(up);
		पूर्ण
		list_add(&up->list, head);
	पूर्ण अन्यथा अणु
		up = list_entry(head->next, काष्ठा mlx5_uars_page, list);
		kref_get(&up->ref_count);
	पूर्ण
	अगर (fast_path) अणु
		biपंचांगap = up->fp_biपंचांगap;
		avail = &up->fp_avail;
	पूर्ण अन्यथा अणु
		biपंचांगap = up->reg_biपंचांगap;
		avail = &up->reg_avail;
	पूर्ण
	dbi = find_first_bit(biपंचांगap, up->bfregs);
	clear_bit(dbi, biपंचांगap);
	(*avail)--;
	अगर (!(*avail))
		list_del(&up->list);

	bfreg->map = up->map + map_offset(mdev, dbi);
	bfreg->up = up;
	bfreg->wc = map_wc;
	bfreg->index = up->index + dbi / MLX5_BFREGS_PER_UAR;
	mutex_unlock(lock);

	वापस 0;
पूर्ण

पूर्णांक mlx5_alloc_bfreg(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_sq_bfreg *bfreg,
		     bool map_wc, bool fast_path)
अणु
	पूर्णांक err;

	err = alloc_bfreg(mdev, bfreg, map_wc, fast_path);
	अगर (!err)
		वापस 0;

	अगर (err == -EAGAIN && map_wc)
		वापस alloc_bfreg(mdev, bfreg, false, fast_path);

	वापस err;
पूर्ण
EXPORT_SYMBOL(mlx5_alloc_bfreg);

अटल अचिन्हित पूर्णांक addr_to_dbi_in_syspage(काष्ठा mlx5_core_dev *dev,
					   काष्ठा mlx5_uars_page *up,
					   काष्ठा mlx5_sq_bfreg *bfreg)
अणु
	अचिन्हित पूर्णांक uar_idx;
	अचिन्हित पूर्णांक bfreg_idx;
	अचिन्हित पूर्णांक bf_reg_size;

	bf_reg_size = 1 << MLX5_CAP_GEN(dev, log_bf_reg_size);

	uar_idx = (bfreg->map - up->map) >> MLX5_ADAPTER_PAGE_SHIFT;
	bfreg_idx = (((uपूर्णांकptr_t)bfreg->map % MLX5_ADAPTER_PAGE_SIZE) - MLX5_BF_OFFSET) / bf_reg_size;

	वापस uar_idx * MLX5_BFREGS_PER_UAR + bfreg_idx;
पूर्ण

व्योम mlx5_मुक्त_bfreg(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_sq_bfreg *bfreg)
अणु
	काष्ठा mlx5_bfreg_data *bfregs;
	काष्ठा mlx5_uars_page *up;
	काष्ठा mutex *lock; /* poपूर्णांकer to right mutex */
	अचिन्हित पूर्णांक dbi;
	bool fp;
	अचिन्हित पूर्णांक *avail;
	अचिन्हित दीर्घ *biपंचांगap;
	काष्ठा list_head *head;

	bfregs = &mdev->priv.bfregs;
	अगर (bfreg->wc) अणु
		head = &bfregs->wc_head.list;
		lock = &bfregs->wc_head.lock;
	पूर्ण अन्यथा अणु
		head = &bfregs->reg_head.list;
		lock = &bfregs->reg_head.lock;
	पूर्ण
	up = bfreg->up;
	dbi = addr_to_dbi_in_syspage(mdev, up, bfreg);
	fp = (dbi % MLX5_BFREGS_PER_UAR) >= MLX5_NON_FP_BFREGS_PER_UAR;
	अगर (fp) अणु
		avail = &up->fp_avail;
		biपंचांगap = up->fp_biपंचांगap;
	पूर्ण अन्यथा अणु
		avail = &up->reg_avail;
		biपंचांगap = up->reg_biपंचांगap;
	पूर्ण
	mutex_lock(lock);
	(*avail)++;
	set_bit(dbi, biपंचांगap);
	अगर (*avail == 1)
		list_add_tail(&up->list, head);

	kref_put(&up->ref_count, up_rel_func);
	mutex_unlock(lock);
पूर्ण
EXPORT_SYMBOL(mlx5_मुक्त_bfreg);
