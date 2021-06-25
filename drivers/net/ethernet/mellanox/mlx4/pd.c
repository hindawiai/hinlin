<शैली गुरु>
/*
 * Copyright (c) 2006, 2007 Cisco Systems, Inc.  All rights reserved.
 * Copyright (c) 2005 Mellanox Technologies. All rights reserved.
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

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <linux/io-mapping.h>

#समावेश <यंत्र/page.h>

#समावेश "mlx4.h"
#समावेश "icm.h"

क्रमागत अणु
	MLX4_NUM_RESERVED_UARS = 8
पूर्ण;

पूर्णांक mlx4_pd_alloc(काष्ठा mlx4_dev *dev, u32 *pdn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	*pdn = mlx4_biपंचांगap_alloc(&priv->pd_biपंचांगap);
	अगर (*pdn == -1)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_pd_alloc);

व्योम mlx4_pd_मुक्त(काष्ठा mlx4_dev *dev, u32 pdn)
अणु
	mlx4_biपंचांगap_मुक्त(&mlx4_priv(dev)->pd_biपंचांगap, pdn, MLX4_USE_RR);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_pd_मुक्त);

पूर्णांक __mlx4_xrcd_alloc(काष्ठा mlx4_dev *dev, u32 *xrcdn)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	*xrcdn = mlx4_biपंचांगap_alloc(&priv->xrcd_biपंचांगap);
	अगर (*xrcdn == -1)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

पूर्णांक mlx4_xrcd_alloc(काष्ठा mlx4_dev *dev, u32 *xrcdn)
अणु
	u64 out_param;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		err = mlx4_cmd_imm(dev, 0, &out_param,
				   RES_XRCD, RES_OP_RESERVE,
				   MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (err)
			वापस err;

		*xrcdn = get_param_l(&out_param);
		वापस 0;
	पूर्ण
	वापस __mlx4_xrcd_alloc(dev, xrcdn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_xrcd_alloc);

व्योम __mlx4_xrcd_मुक्त(काष्ठा mlx4_dev *dev, u32 xrcdn)
अणु
	mlx4_biपंचांगap_मुक्त(&mlx4_priv(dev)->xrcd_biपंचांगap, xrcdn, MLX4_USE_RR);
पूर्ण

व्योम mlx4_xrcd_मुक्त(काष्ठा mlx4_dev *dev, u32 xrcdn)
अणु
	u64 in_param = 0;
	पूर्णांक err;

	अगर (mlx4_is_mfunc(dev)) अणु
		set_param_l(&in_param, xrcdn);
		err = mlx4_cmd(dev, in_param, RES_XRCD,
			       RES_OP_RESERVE, MLX4_CMD_FREE_RES,
			       MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		अगर (err)
			mlx4_warn(dev, "Failed to release xrcdn %d\n", xrcdn);
	पूर्ण अन्यथा
		__mlx4_xrcd_मुक्त(dev, xrcdn);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_xrcd_मुक्त);

पूर्णांक mlx4_init_pd_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस mlx4_biपंचांगap_init(&priv->pd_biपंचांगap, dev->caps.num_pds,
				(1 << NOT_MASKED_PD_BITS) - 1,
				 dev->caps.reserved_pds, 0);
पूर्ण

व्योम mlx4_cleanup_pd_table(काष्ठा mlx4_dev *dev)
अणु
	mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->pd_biपंचांगap);
पूर्ण

पूर्णांक mlx4_init_xrcd_table(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस mlx4_biपंचांगap_init(&priv->xrcd_biपंचांगap, (1 << 16),
				(1 << 16) - 1, dev->caps.reserved_xrcds + 1, 0);
पूर्ण

व्योम mlx4_cleanup_xrcd_table(काष्ठा mlx4_dev *dev)
अणु
	mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->xrcd_biपंचांगap);
पूर्ण

पूर्णांक mlx4_uar_alloc(काष्ठा mlx4_dev *dev, काष्ठा mlx4_uar *uar)
अणु
	पूर्णांक offset;

	uar->index = mlx4_biपंचांगap_alloc(&mlx4_priv(dev)->uar_table.biपंचांगap);
	अगर (uar->index == -1)
		वापस -ENOMEM;

	अगर (mlx4_is_slave(dev))
		offset = uar->index % ((पूर्णांक)pci_resource_len(dev->persist->pdev,
							     2) /
				       dev->caps.uar_page_size);
	अन्यथा
		offset = uar->index;
	uar->pfn = (pci_resource_start(dev->persist->pdev, 2) >> PAGE_SHIFT)
		    + offset;
	uar->map = शून्य;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_uar_alloc);

व्योम mlx4_uar_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_uar *uar)
अणु
	mlx4_biपंचांगap_मुक्त(&mlx4_priv(dev)->uar_table.biपंचांगap, uar->index, MLX4_USE_RR);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_uar_मुक्त);

पूर्णांक mlx4_bf_alloc(काष्ठा mlx4_dev *dev, काष्ठा mlx4_bf *bf, पूर्णांक node)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_uar *uar;
	पूर्णांक err = 0;
	पूर्णांक idx;

	अगर (!priv->bf_mapping)
		वापस -ENOMEM;

	mutex_lock(&priv->bf_mutex);
	अगर (!list_empty(&priv->bf_list))
		uar = list_entry(priv->bf_list.next, काष्ठा mlx4_uar, bf_list);
	अन्यथा अणु
		अगर (mlx4_biपंचांगap_avail(&priv->uar_table.biपंचांगap) < MLX4_NUM_RESERVED_UARS) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		uar = kदो_स्मृति_node(माप(*uar), GFP_KERNEL, node);
		अगर (!uar) अणु
			uar = kदो_स्मृति(माप(*uar), GFP_KERNEL);
			अगर (!uar) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण
		पूर्ण
		err = mlx4_uar_alloc(dev, uar);
		अगर (err)
			जाओ मुक्त_kदो_स्मृति;

		uar->map = ioremap(uar->pfn << PAGE_SHIFT, PAGE_SIZE);
		अगर (!uar->map) अणु
			err = -ENOMEM;
			जाओ मुक्त_uar;
		पूर्ण

		uar->bf_map = io_mapping_map_wc(priv->bf_mapping,
						uar->index << PAGE_SHIFT,
						PAGE_SIZE);
		अगर (!uar->bf_map) अणु
			err = -ENOMEM;
			जाओ unamp_uar;
		पूर्ण
		uar->मुक्त_bf_bmap = 0;
		list_add(&uar->bf_list, &priv->bf_list);
	पूर्ण

	idx = ffz(uar->मुक्त_bf_bmap);
	uar->मुक्त_bf_bmap |= 1 << idx;
	bf->uar = uar;
	bf->offset = 0;
	bf->buf_size = dev->caps.bf_reg_size / 2;
	bf->reg = uar->bf_map + idx * dev->caps.bf_reg_size;
	अगर (uar->मुक्त_bf_bmap == (1 << dev->caps.bf_regs_per_page) - 1)
		list_del_init(&uar->bf_list);

	जाओ out;

unamp_uar:
	bf->uar = शून्य;
	iounmap(uar->map);

मुक्त_uar:
	mlx4_uar_मुक्त(dev, uar);

मुक्त_kदो_स्मृति:
	kमुक्त(uar);

out:
	mutex_unlock(&priv->bf_mutex);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_bf_alloc);

व्योम mlx4_bf_मुक्त(काष्ठा mlx4_dev *dev, काष्ठा mlx4_bf *bf)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक idx;

	अगर (!bf->uar || !bf->uar->bf_map)
		वापस;

	mutex_lock(&priv->bf_mutex);
	idx = (bf->reg - bf->uar->bf_map) / dev->caps.bf_reg_size;
	bf->uar->मुक्त_bf_bmap &= ~(1 << idx);
	अगर (!bf->uar->मुक्त_bf_bmap) अणु
		अगर (!list_empty(&bf->uar->bf_list))
			list_del(&bf->uar->bf_list);

		io_mapping_unmap(bf->uar->bf_map);
		iounmap(bf->uar->map);
		mlx4_uar_मुक्त(dev, bf->uar);
		kमुक्त(bf->uar);
	पूर्ण अन्यथा अगर (list_empty(&bf->uar->bf_list))
		list_add(&bf->uar->bf_list, &priv->bf_list);

	mutex_unlock(&priv->bf_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(mlx4_bf_मुक्त);

पूर्णांक mlx4_init_uar_table(काष्ठा mlx4_dev *dev)
अणु
	पूर्णांक num_reserved_uar = mlx4_get_num_reserved_uar(dev);

	mlx4_dbg(dev, "uar_page_shift = %d", dev->uar_page_shअगरt);
	mlx4_dbg(dev, "Effective reserved_uars=%d", dev->caps.reserved_uars);

	अगर (dev->caps.num_uars <= num_reserved_uar) अणु
		mlx4_err(
			dev, "Only %d UAR pages (need more than %d)\n",
			dev->caps.num_uars, num_reserved_uar);
		mlx4_err(dev, "Increase firmware log2_uar_bar_megabytes?\n");
		वापस -ENODEV;
	पूर्ण

	वापस mlx4_biपंचांगap_init(&mlx4_priv(dev)->uar_table.biपंचांगap,
				dev->caps.num_uars, dev->caps.num_uars - 1,
				dev->caps.reserved_uars, 0);
पूर्ण

व्योम mlx4_cleanup_uar_table(काष्ठा mlx4_dev *dev)
अणु
	mlx4_biपंचांगap_cleanup(&mlx4_priv(dev)->uar_table.biपंचांगap);
पूर्ण
