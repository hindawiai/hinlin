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

#समावेश <linux/highस्मृति.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/xarray.h>
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"

क्रमागत अणु
	MLX5_PAGES_CANT_GIVE	= 0,
	MLX5_PAGES_GIVE		= 1,
	MLX5_PAGES_TAKE		= 2
पूर्ण;

काष्ठा mlx5_pages_req अणु
	काष्ठा mlx5_core_dev *dev;
	u16	func_id;
	u8	ec_function;
	s32	npages;
	काष्ठा work_काष्ठा work;
	u8	release_all;
पूर्ण;

काष्ठा fw_page अणु
	काष्ठा rb_node		rb_node;
	u64			addr;
	काष्ठा page	       *page;
	u32			function;
	अचिन्हित दीर्घ		biपंचांगask;
	काष्ठा list_head	list;
	अचिन्हित पूर्णांक मुक्त_count;
पूर्ण;

क्रमागत अणु
	MAX_RECLAIM_TIME_MSECS	= 5000,
	MAX_RECLAIM_VFS_PAGES_TIME_MSECS = 2 * 1000 * 60,
पूर्ण;

क्रमागत अणु
	MLX5_MAX_RECLAIM_TIME_MILI	= 5000,
	MLX5_NUM_4K_IN_PAGE		= PAGE_SIZE / MLX5_ADAPTER_PAGE_SIZE,
पूर्ण;

अटल u32 get_function(u16 func_id, bool ec_function)
अणु
	वापस (u32)func_id | (ec_function << 16);
पूर्ण

अटल काष्ठा rb_root *page_root_per_function(काष्ठा mlx5_core_dev *dev, u32 function)
अणु
	काष्ठा rb_root *root;
	पूर्णांक err;

	root = xa_load(&dev->priv.page_root_xa, function);
	अगर (root)
		वापस root;

	root = kzalloc(माप(*root), GFP_KERNEL);
	अगर (!root)
		वापस ERR_PTR(-ENOMEM);

	err = xa_insert(&dev->priv.page_root_xa, function, root, GFP_KERNEL);
	अगर (err) अणु
		kमुक्त(root);
		वापस ERR_PTR(err);
	पूर्ण

	*root = RB_ROOT;

	वापस root;
पूर्ण

अटल पूर्णांक insert_page(काष्ठा mlx5_core_dev *dev, u64 addr, काष्ठा page *page, u32 function)
अणु
	काष्ठा rb_node *parent = शून्य;
	काष्ठा rb_root *root;
	काष्ठा rb_node **new;
	काष्ठा fw_page *nfp;
	काष्ठा fw_page *tfp;
	पूर्णांक i;

	root = page_root_per_function(dev, function);
	अगर (IS_ERR(root))
		वापस PTR_ERR(root);

	new = &root->rb_node;

	जबतक (*new) अणु
		parent = *new;
		tfp = rb_entry(parent, काष्ठा fw_page, rb_node);
		अगर (tfp->addr < addr)
			new = &parent->rb_left;
		अन्यथा अगर (tfp->addr > addr)
			new = &parent->rb_right;
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	nfp = kzalloc(माप(*nfp), GFP_KERNEL);
	अगर (!nfp)
		वापस -ENOMEM;

	nfp->addr = addr;
	nfp->page = page;
	nfp->function = function;
	nfp->मुक्त_count = MLX5_NUM_4K_IN_PAGE;
	क्रम (i = 0; i < MLX5_NUM_4K_IN_PAGE; i++)
		set_bit(i, &nfp->biपंचांगask);

	rb_link_node(&nfp->rb_node, parent, new);
	rb_insert_color(&nfp->rb_node, root);
	list_add(&nfp->list, &dev->priv.मुक्त_list);

	वापस 0;
पूर्ण

अटल काष्ठा fw_page *find_fw_page(काष्ठा mlx5_core_dev *dev, u64 addr,
				    u32 function)
अणु
	काष्ठा fw_page *result = शून्य;
	काष्ठा rb_root *root;
	काष्ठा rb_node *पंचांगp;
	काष्ठा fw_page *tfp;

	root = xa_load(&dev->priv.page_root_xa, function);
	अगर (WARN_ON_ONCE(!root))
		वापस शून्य;

	पंचांगp = root->rb_node;

	जबतक (पंचांगp) अणु
		tfp = rb_entry(पंचांगp, काष्ठा fw_page, rb_node);
		अगर (tfp->addr < addr) अणु
			पंचांगp = पंचांगp->rb_left;
		पूर्ण अन्यथा अगर (tfp->addr > addr) अणु
			पंचांगp = पंचांगp->rb_right;
		पूर्ण अन्यथा अणु
			result = tfp;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक mlx5_cmd_query_pages(काष्ठा mlx5_core_dev *dev, u16 *func_id,
				s32 *npages, पूर्णांक boot)
अणु
	u32 out[MLX5_ST_SZ_DW(query_pages_out)] = अणुपूर्ण;
	u32 in[MLX5_ST_SZ_DW(query_pages_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(query_pages_in, in, opcode, MLX5_CMD_OP_QUERY_PAGES);
	MLX5_SET(query_pages_in, in, op_mod, boot ?
		 MLX5_QUERY_PAGES_IN_OP_MOD_BOOT_PAGES :
		 MLX5_QUERY_PAGES_IN_OP_MOD_INIT_PAGES);
	MLX5_SET(query_pages_in, in, embedded_cpu_function, mlx5_core_is_ecpf(dev));

	err = mlx5_cmd_exec_inout(dev, query_pages, in, out);
	अगर (err)
		वापस err;

	*npages = MLX5_GET(query_pages_out, out, num_pages);
	*func_id = MLX5_GET(query_pages_out, out, function_id);

	वापस err;
पूर्ण

अटल पूर्णांक alloc_4k(काष्ठा mlx5_core_dev *dev, u64 *addr, u32 function)
अणु
	काष्ठा fw_page *fp = शून्य;
	काष्ठा fw_page *iter;
	अचिन्हित n;

	list_क्रम_each_entry(iter, &dev->priv.मुक्त_list, list) अणु
		अगर (iter->function != function)
			जारी;
		fp = iter;
	पूर्ण

	अगर (list_empty(&dev->priv.मुक्त_list) || !fp)
		वापस -ENOMEM;

	n = find_first_bit(&fp->biपंचांगask, 8 * माप(fp->biपंचांगask));
	अगर (n >= MLX5_NUM_4K_IN_PAGE) अणु
		mlx5_core_warn(dev, "alloc 4k bug\n");
		वापस -ENOENT;
	पूर्ण
	clear_bit(n, &fp->biपंचांगask);
	fp->मुक्त_count--;
	अगर (!fp->मुक्त_count)
		list_del(&fp->list);

	*addr = fp->addr + n * MLX5_ADAPTER_PAGE_SIZE;

	वापस 0;
पूर्ण

#घोषणा MLX5_U64_4K_PAGE_MASK ((~(u64)0U) << PAGE_SHIFT)

अटल व्योम मुक्त_fwp(काष्ठा mlx5_core_dev *dev, काष्ठा fw_page *fwp,
		     bool in_मुक्त_list)
अणु
	काष्ठा rb_root *root;

	root = xa_load(&dev->priv.page_root_xa, fwp->function);
	अगर (WARN_ON_ONCE(!root))
		वापस;

	rb_erase(&fwp->rb_node, root);
	अगर (in_मुक्त_list)
		list_del(&fwp->list);
	dma_unmap_page(mlx5_core_dma_dev(dev), fwp->addr & MLX5_U64_4K_PAGE_MASK,
		       PAGE_SIZE, DMA_BIसूचीECTIONAL);
	__मुक्त_page(fwp->page);
	kमुक्त(fwp);
पूर्ण

अटल व्योम मुक्त_4k(काष्ठा mlx5_core_dev *dev, u64 addr, u32 function)
अणु
	काष्ठा fw_page *fwp;
	पूर्णांक n;

	fwp = find_fw_page(dev, addr & MLX5_U64_4K_PAGE_MASK, function);
	अगर (!fwp) अणु
		mlx5_core_warn_rl(dev, "page not found\n");
		वापस;
	पूर्ण
	n = (addr & ~MLX5_U64_4K_PAGE_MASK) >> MLX5_ADAPTER_PAGE_SHIFT;
	fwp->मुक्त_count++;
	set_bit(n, &fwp->biपंचांगask);
	अगर (fwp->मुक्त_count == MLX5_NUM_4K_IN_PAGE)
		मुक्त_fwp(dev, fwp, fwp->मुक्त_count != 1);
	अन्यथा अगर (fwp->मुक्त_count == 1)
		list_add(&fwp->list, &dev->priv.मुक्त_list);
पूर्ण

अटल पूर्णांक alloc_प्रणाली_page(काष्ठा mlx5_core_dev *dev, u32 function)
अणु
	काष्ठा device *device = mlx5_core_dma_dev(dev);
	पूर्णांक nid = dev_to_node(device);
	काष्ठा page *page;
	u64 zero_addr = 1;
	u64 addr;
	पूर्णांक err;

	page = alloc_pages_node(nid, GFP_HIGHUSER, 0);
	अगर (!page) अणु
		mlx5_core_warn(dev, "failed to allocate page\n");
		वापस -ENOMEM;
	पूर्ण
map:
	addr = dma_map_page(device, page, 0, PAGE_SIZE, DMA_BIसूचीECTIONAL);
	अगर (dma_mapping_error(device, addr)) अणु
		mlx5_core_warn(dev, "failed dma mapping page\n");
		err = -ENOMEM;
		जाओ err_mapping;
	पूर्ण

	/* Firmware करोesn't support page with physical address 0 */
	अगर (addr == 0) अणु
		zero_addr = addr;
		जाओ map;
	पूर्ण

	err = insert_page(dev, addr, page, function);
	अगर (err) अणु
		mlx5_core_err(dev, "failed to track allocated page\n");
		dma_unmap_page(device, addr, PAGE_SIZE, DMA_BIसूचीECTIONAL);
	पूर्ण

err_mapping:
	अगर (err)
		__मुक्त_page(page);

	अगर (zero_addr == 0)
		dma_unmap_page(device, zero_addr, PAGE_SIZE,
			       DMA_BIसूचीECTIONAL);

	वापस err;
पूर्ण

अटल व्योम page_notअगरy_fail(काष्ठा mlx5_core_dev *dev, u16 func_id,
			     bool ec_function)
अणु
	u32 in[MLX5_ST_SZ_DW(manage_pages_in)] = अणुपूर्ण;
	पूर्णांक err;

	MLX5_SET(manage_pages_in, in, opcode, MLX5_CMD_OP_MANAGE_PAGES);
	MLX5_SET(manage_pages_in, in, op_mod, MLX5_PAGES_CANT_GIVE);
	MLX5_SET(manage_pages_in, in, function_id, func_id);
	MLX5_SET(manage_pages_in, in, embedded_cpu_function, ec_function);

	err = mlx5_cmd_exec_in(dev, manage_pages, in);
	अगर (err)
		mlx5_core_warn(dev, "page notify failed func_id(%d) err(%d)\n",
			       func_id, err);
पूर्ण

अटल पूर्णांक give_pages(काष्ठा mlx5_core_dev *dev, u16 func_id, पूर्णांक npages,
		      पूर्णांक notअगरy_fail, bool ec_function)
अणु
	u32 function = get_function(func_id, ec_function);
	u32 out[MLX5_ST_SZ_DW(manage_pages_out)] = अणु0पूर्ण;
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(manage_pages_in);
	u64 addr;
	पूर्णांक err;
	u32 *in;
	पूर्णांक i;

	inlen += npages * MLX5_FLD_SZ_BYTES(manage_pages_in, pas[0]);
	in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!in) अणु
		err = -ENOMEM;
		mlx5_core_warn(dev, "vzalloc failed %d\n", inlen);
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < npages; i++) अणु
retry:
		err = alloc_4k(dev, &addr, function);
		अगर (err) अणु
			अगर (err == -ENOMEM)
				err = alloc_प्रणाली_page(dev, function);
			अगर (err)
				जाओ out_4k;

			जाओ retry;
		पूर्ण
		MLX5_ARRAY_SET64(manage_pages_in, in, pas, i, addr);
	पूर्ण

	MLX5_SET(manage_pages_in, in, opcode, MLX5_CMD_OP_MANAGE_PAGES);
	MLX5_SET(manage_pages_in, in, op_mod, MLX5_PAGES_GIVE);
	MLX5_SET(manage_pages_in, in, function_id, func_id);
	MLX5_SET(manage_pages_in, in, input_num_entries, npages);
	MLX5_SET(manage_pages_in, in, embedded_cpu_function, ec_function);

	err = mlx5_cmd_exec(dev, in, inlen, out, माप(out));
	अगर (err) अणु
		mlx5_core_warn(dev, "func_id 0x%x, npages %d, err %d\n",
			       func_id, npages, err);
		जाओ out_4k;
	पूर्ण

	dev->priv.fw_pages += npages;
	अगर (func_id)
		dev->priv.vfs_pages += npages;
	अन्यथा अगर (mlx5_core_is_ecpf(dev) && !ec_function)
		dev->priv.host_pf_pages += npages;

	mlx5_core_dbg(dev, "npages %d, ec_function %d, func_id 0x%x, err %d\n",
		      npages, ec_function, func_id, err);

	kvमुक्त(in);
	वापस 0;

out_4k:
	क्रम (i--; i >= 0; i--)
		मुक्त_4k(dev, MLX5_GET64(manage_pages_in, in, pas[i]), function);
out_मुक्त:
	kvमुक्त(in);
	अगर (notअगरy_fail)
		page_notअगरy_fail(dev, func_id, ec_function);
	वापस err;
पूर्ण

अटल व्योम release_all_pages(काष्ठा mlx5_core_dev *dev, u16 func_id,
			      bool ec_function)
अणु
	u32 function = get_function(func_id, ec_function);
	काष्ठा rb_root *root;
	काष्ठा rb_node *p;
	पूर्णांक npages = 0;

	root = xa_load(&dev->priv.page_root_xa, function);
	अगर (WARN_ON_ONCE(!root))
		वापस;

	p = rb_first(root);
	जबतक (p) अणु
		काष्ठा fw_page *fwp = rb_entry(p, काष्ठा fw_page, rb_node);

		p = rb_next(p);
		npages += (MLX5_NUM_4K_IN_PAGE - fwp->मुक्त_count);
		मुक्त_fwp(dev, fwp, fwp->मुक्त_count);
	पूर्ण

	dev->priv.fw_pages -= npages;
	अगर (func_id)
		dev->priv.vfs_pages -= npages;
	अन्यथा अगर (mlx5_core_is_ecpf(dev) && !ec_function)
		dev->priv.host_pf_pages -= npages;

	mlx5_core_dbg(dev, "npages %d, ec_function %d, func_id 0x%x\n",
		      npages, ec_function, func_id);
पूर्ण

अटल u32 fwp_fill_manage_pages_out(काष्ठा fw_page *fwp, u32 *out, u32 index,
				     u32 npages)
अणु
	u32 pages_set = 0;
	अचिन्हित पूर्णांक n;

	क्रम_each_clear_bit(n, &fwp->biपंचांगask, MLX5_NUM_4K_IN_PAGE) अणु
		MLX5_ARRAY_SET64(manage_pages_out, out, pas, index + pages_set,
				 fwp->addr + (n * MLX5_ADAPTER_PAGE_SIZE));
		pages_set++;

		अगर (!--npages)
			अवरोध;
	पूर्ण

	वापस pages_set;
पूर्ण

अटल पूर्णांक reclaim_pages_cmd(काष्ठा mlx5_core_dev *dev,
			     u32 *in, पूर्णांक in_size, u32 *out, पूर्णांक out_size)
अणु
	काष्ठा rb_root *root;
	काष्ठा fw_page *fwp;
	काष्ठा rb_node *p;
	bool ec_function;
	u32 func_id;
	u32 npages;
	u32 i = 0;

	अगर (!mlx5_cmd_is_करोwn(dev))
		वापस mlx5_cmd_exec(dev, in, in_size, out, out_size);

	/* No hard feelings, we want our pages back! */
	npages = MLX5_GET(manage_pages_in, in, input_num_entries);
	func_id = MLX5_GET(manage_pages_in, in, function_id);
	ec_function = MLX5_GET(manage_pages_in, in, embedded_cpu_function);

	root = xa_load(&dev->priv.page_root_xa, get_function(func_id, ec_function));
	अगर (WARN_ON_ONCE(!root))
		वापस -EEXIST;

	p = rb_first(root);
	जबतक (p && i < npages) अणु
		fwp = rb_entry(p, काष्ठा fw_page, rb_node);
		p = rb_next(p);

		i += fwp_fill_manage_pages_out(fwp, out, i, npages - i);
	पूर्ण

	MLX5_SET(manage_pages_out, out, output_num_entries, i);
	वापस 0;
पूर्ण

अटल पूर्णांक reclaim_pages(काष्ठा mlx5_core_dev *dev, u16 func_id, पूर्णांक npages,
			 पूर्णांक *nclaimed, bool ec_function)
अणु
	u32 function = get_function(func_id, ec_function);
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(manage_pages_out);
	u32 in[MLX5_ST_SZ_DW(manage_pages_in)] = अणुपूर्ण;
	पूर्णांक num_claimed;
	u32 *out;
	पूर्णांक err;
	पूर्णांक i;

	अगर (nclaimed)
		*nclaimed = 0;

	outlen += npages * MLX5_FLD_SZ_BYTES(manage_pages_out, pas[0]);
	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(manage_pages_in, in, opcode, MLX5_CMD_OP_MANAGE_PAGES);
	MLX5_SET(manage_pages_in, in, op_mod, MLX5_PAGES_TAKE);
	MLX5_SET(manage_pages_in, in, function_id, func_id);
	MLX5_SET(manage_pages_in, in, input_num_entries, npages);
	MLX5_SET(manage_pages_in, in, embedded_cpu_function, ec_function);

	mlx5_core_dbg(dev, "func 0x%x, npages %d, outlen %d\n",
		      func_id, npages, outlen);
	err = reclaim_pages_cmd(dev, in, माप(in), out, outlen);
	अगर (err) अणु
		mlx5_core_err(dev, "failed reclaiming pages: err %d\n", err);
		जाओ out_मुक्त;
	पूर्ण

	num_claimed = MLX5_GET(manage_pages_out, out, output_num_entries);
	अगर (num_claimed > npages) अणु
		mlx5_core_warn(dev, "fw returned %d, driver asked %d => corruption\n",
			       num_claimed, npages);
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	क्रम (i = 0; i < num_claimed; i++)
		मुक्त_4k(dev, MLX5_GET64(manage_pages_out, out, pas[i]), function);

	अगर (nclaimed)
		*nclaimed = num_claimed;

	dev->priv.fw_pages -= num_claimed;
	अगर (func_id)
		dev->priv.vfs_pages -= num_claimed;
	अन्यथा अगर (mlx5_core_is_ecpf(dev) && !ec_function)
		dev->priv.host_pf_pages -= num_claimed;

out_मुक्त:
	kvमुक्त(out);
	वापस err;
पूर्ण

अटल व्योम pages_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_pages_req *req = container_of(work, काष्ठा mlx5_pages_req, work);
	काष्ठा mlx5_core_dev *dev = req->dev;
	पूर्णांक err = 0;

	अगर (req->release_all)
		release_all_pages(dev, req->func_id, req->ec_function);
	अन्यथा अगर (req->npages < 0)
		err = reclaim_pages(dev, req->func_id, -1 * req->npages, शून्य,
				    req->ec_function);
	अन्यथा अगर (req->npages > 0)
		err = give_pages(dev, req->func_id, req->npages, 1, req->ec_function);

	अगर (err)
		mlx5_core_warn(dev, "%s fail %d\n",
			       req->npages < 0 ? "reclaim" : "give", err);

	kमुक्त(req);
पूर्ण

क्रमागत अणु
	EC_FUNCTION_MASK = 0x8000,
	RELEASE_ALL_PAGES_MASK = 0x4000,
पूर्ण;

अटल पूर्णांक req_pages_handler(काष्ठा notअगरier_block *nb,
			     अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_pages_req *req;
	काष्ठा mlx5_core_dev *dev;
	काष्ठा mlx5_priv *priv;
	काष्ठा mlx5_eqe *eqe;
	bool ec_function;
	bool release_all;
	u16 func_id;
	s32 npages;

	priv = mlx5_nb_cof(nb, काष्ठा mlx5_priv, pg_nb);
	dev  = container_of(priv, काष्ठा mlx5_core_dev, priv);
	eqe  = data;

	func_id = be16_to_cpu(eqe->data.req_pages.func_id);
	npages  = be32_to_cpu(eqe->data.req_pages.num_pages);
	ec_function = be16_to_cpu(eqe->data.req_pages.ec_function) & EC_FUNCTION_MASK;
	release_all = be16_to_cpu(eqe->data.req_pages.ec_function) &
		      RELEASE_ALL_PAGES_MASK;
	mlx5_core_dbg(dev, "page request for func 0x%x, npages %d, release_all %d\n",
		      func_id, npages, release_all);
	req = kzalloc(माप(*req), GFP_ATOMIC);
	अगर (!req) अणु
		mlx5_core_warn(dev, "failed to allocate pages request\n");
		वापस NOTIFY_DONE;
	पूर्ण

	req->dev = dev;
	req->func_id = func_id;
	req->npages = npages;
	req->ec_function = ec_function;
	req->release_all = release_all;
	INIT_WORK(&req->work, pages_work_handler);
	queue_work(dev->priv.pg_wq, &req->work);
	वापस NOTIFY_OK;
पूर्ण

पूर्णांक mlx5_satisfy_startup_pages(काष्ठा mlx5_core_dev *dev, पूर्णांक boot)
अणु
	u16 func_id;
	s32 npages;
	पूर्णांक err;

	err = mlx5_cmd_query_pages(dev, &func_id, &npages, boot);
	अगर (err)
		वापस err;

	mlx5_core_dbg(dev, "requested %d %s pages for func_id 0x%x\n",
		      npages, boot ? "boot" : "init", func_id);

	वापस give_pages(dev, func_id, npages, 0, mlx5_core_is_ecpf(dev));
पूर्ण

क्रमागत अणु
	MLX5_BLKS_FOR_RECLAIM_PAGES = 12
पूर्ण;

अटल पूर्णांक optimal_reclaimed_pages(व्योम)
अणु
	काष्ठा mlx5_cmd_prot_block *block;
	काष्ठा mlx5_cmd_layout *lay;
	पूर्णांक ret;

	ret = (माप(lay->out) + MLX5_BLKS_FOR_RECLAIM_PAGES * माप(block->data) -
	       MLX5_ST_SZ_BYTES(manage_pages_out)) /
	       MLX5_FLD_SZ_BYTES(manage_pages_out, pas[0]);

	वापस ret;
पूर्ण

अटल पूर्णांक mlx5_reclaim_root_pages(काष्ठा mlx5_core_dev *dev,
				   काष्ठा rb_root *root, u16 func_id)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(MAX_RECLAIM_TIME_MSECS);

	जबतक (!RB_EMPTY_ROOT(root)) अणु
		पूर्णांक nclaimed;
		पूर्णांक err;

		err = reclaim_pages(dev, func_id, optimal_reclaimed_pages(),
				    &nclaimed, mlx5_core_is_ecpf(dev));
		अगर (err) अणु
			mlx5_core_warn(dev, "failed reclaiming pages (%d) for func id 0x%x\n",
				       err, func_id);
			वापस err;
		पूर्ण

		अगर (nclaimed)
			end = jअगरfies + msecs_to_jअगरfies(MAX_RECLAIM_TIME_MSECS);

		अगर (समय_after(jअगरfies, end)) अणु
			mlx5_core_warn(dev, "FW did not return all pages. giving up...\n");
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_reclaim_startup_pages(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा rb_root *root;
	अचिन्हित दीर्घ id;
	व्योम *entry;

	xa_क्रम_each(&dev->priv.page_root_xa, id, entry) अणु
		root = entry;
		mlx5_reclaim_root_pages(dev, root, id);
		xa_erase(&dev->priv.page_root_xa, id);
		kमुक्त(root);
	पूर्ण

	WARN_ON(!xa_empty(&dev->priv.page_root_xa));

	WARN(dev->priv.fw_pages,
	     "FW pages counter is %d after reclaiming all pages\n",
	     dev->priv.fw_pages);
	WARN(dev->priv.vfs_pages,
	     "VFs FW pages counter is %d after reclaiming all pages\n",
	     dev->priv.vfs_pages);
	WARN(dev->priv.host_pf_pages,
	     "External host PF FW pages counter is %d after reclaiming all pages\n",
	     dev->priv.host_pf_pages);

	वापस 0;
पूर्ण

पूर्णांक mlx5_pagealloc_init(काष्ठा mlx5_core_dev *dev)
अणु
	INIT_LIST_HEAD(&dev->priv.मुक्त_list);
	dev->priv.pg_wq = create_singlethपढ़ो_workqueue("mlx5_page_allocator");
	अगर (!dev->priv.pg_wq)
		वापस -ENOMEM;

	xa_init(&dev->priv.page_root_xa);

	वापस 0;
पूर्ण

व्योम mlx5_pagealloc_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	xa_destroy(&dev->priv.page_root_xa);
	destroy_workqueue(dev->priv.pg_wq);
पूर्ण

व्योम mlx5_pagealloc_start(काष्ठा mlx5_core_dev *dev)
अणु
	MLX5_NB_INIT(&dev->priv.pg_nb, req_pages_handler, PAGE_REQUEST);
	mlx5_eq_notअगरier_रेजिस्टर(dev, &dev->priv.pg_nb);
पूर्ण

व्योम mlx5_pagealloc_stop(काष्ठा mlx5_core_dev *dev)
अणु
	mlx5_eq_notअगरier_unरेजिस्टर(dev, &dev->priv.pg_nb);
	flush_workqueue(dev->priv.pg_wq);
पूर्ण

पूर्णांक mlx5_रुको_क्रम_pages(काष्ठा mlx5_core_dev *dev, पूर्णांक *pages)
अणु
	अचिन्हित दीर्घ end = jअगरfies + msecs_to_jअगरfies(MAX_RECLAIM_VFS_PAGES_TIME_MSECS);
	पूर्णांक prev_pages = *pages;

	/* In हाल of पूर्णांकernal error we will मुक्त the pages manually later */
	अगर (dev->state == MLX5_DEVICE_STATE_INTERNAL_ERROR) अणु
		mlx5_core_warn(dev, "Skipping wait for vf pages stage");
		वापस 0;
	पूर्ण

	mlx5_core_dbg(dev, "Waiting for %d pages\n", prev_pages);
	जबतक (*pages) अणु
		अगर (समय_after(jअगरfies, end)) अणु
			mlx5_core_warn(dev, "aborting while there are %d pending pages\n", *pages);
			वापस -ETIMEDOUT;
		पूर्ण
		अगर (*pages < prev_pages) अणु
			end = jअगरfies + msecs_to_jअगरfies(MAX_RECLAIM_VFS_PAGES_TIME_MSECS);
			prev_pages = *pages;
		पूर्ण
		msleep(50);
	पूर्ण

	mlx5_core_dbg(dev, "All pages received\n");
	वापस 0;
पूर्ण
