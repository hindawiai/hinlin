<शैली गुरु>
/*
 * Copyright (c) 2014, Mellanox Technologies inc.  All rights reserved.
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

#समावेश <linux/pci.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/vport.h>
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"

अटल पूर्णांक sriov_restore_guids(काष्ठा mlx5_core_dev *dev, पूर्णांक vf)
अणु
	काष्ठा mlx5_core_sriov *sriov = &dev->priv.sriov;
	काष्ठा mlx5_hca_vport_context *in;
	पूर्णांक err = 0;

	/* Restore sriov guid and policy settings */
	अगर (sriov->vfs_ctx[vf].node_guid ||
	    sriov->vfs_ctx[vf].port_guid ||
	    sriov->vfs_ctx[vf].policy != MLX5_POLICY_INVALID) अणु
		in = kzalloc(माप(*in), GFP_KERNEL);
		अगर (!in)
			वापस -ENOMEM;

		in->node_guid = sriov->vfs_ctx[vf].node_guid;
		in->port_guid = sriov->vfs_ctx[vf].port_guid;
		in->policy = sriov->vfs_ctx[vf].policy;
		in->field_select =
			!!(in->port_guid) * MLX5_HCA_VPORT_SEL_PORT_GUID |
			!!(in->node_guid) * MLX5_HCA_VPORT_SEL_NODE_GUID |
			!!(in->policy) * MLX5_HCA_VPORT_SEL_STATE_POLICY;

		err = mlx5_core_modअगरy_hca_vport_context(dev, 1, 1, vf + 1, in);
		अगर (err)
			mlx5_core_warn(dev, "modify vport context failed, unable to restore VF %d settings\n", vf);

		kमुक्त(in);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mlx5_device_enable_sriov(काष्ठा mlx5_core_dev *dev, पूर्णांक num_vfs)
अणु
	काष्ठा mlx5_core_sriov *sriov = &dev->priv.sriov;
	पूर्णांक err, vf, num_msix_count;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		जाओ enable_vfs_hca;

	err = mlx5_eचयन_enable(dev->priv.eचयन, num_vfs);
	अगर (err) अणु
		mlx5_core_warn(dev,
			       "failed to enable eswitch SRIOV (%d)\n", err);
		वापस err;
	पूर्ण

enable_vfs_hca:
	num_msix_count = mlx5_get_शेष_msix_vec_count(dev, num_vfs);
	क्रम (vf = 0; vf < num_vfs; vf++) अणु
		err = mlx5_core_enable_hca(dev, vf + 1);
		अगर (err) अणु
			mlx5_core_warn(dev, "failed to enable VF %d (%d)\n", vf, err);
			जारी;
		पूर्ण

		err = mlx5_set_msix_vec_count(dev, vf + 1, num_msix_count);
		अगर (err) अणु
			mlx5_core_warn(dev,
				       "failed to set MSI-X vector counts VF %d, err %d\n",
				       vf, err);
			जारी;
		पूर्ण

		sriov->vfs_ctx[vf].enabled = 1;
		अगर (MLX5_CAP_GEN(dev, port_type) == MLX5_CAP_PORT_TYPE_IB) अणु
			err = sriov_restore_guids(dev, vf);
			अगर (err) अणु
				mlx5_core_warn(dev,
					       "failed to restore VF %d settings, err %d\n",
					       vf, err);
				जारी;
			पूर्ण
		पूर्ण
		mlx5_core_dbg(dev, "successfully enabled VF* %d\n", vf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
mlx5_device_disable_sriov(काष्ठा mlx5_core_dev *dev, पूर्णांक num_vfs, bool clear_vf)
अणु
	काष्ठा mlx5_core_sriov *sriov = &dev->priv.sriov;
	पूर्णांक err;
	पूर्णांक vf;

	क्रम (vf = num_vfs - 1; vf >= 0; vf--) अणु
		अगर (!sriov->vfs_ctx[vf].enabled)
			जारी;
		err = mlx5_core_disable_hca(dev, vf + 1);
		अगर (err) अणु
			mlx5_core_warn(dev, "failed to disable VF %d\n", vf);
			जारी;
		पूर्ण
		sriov->vfs_ctx[vf].enabled = 0;
	पूर्ण

	अगर (MLX5_ESWITCH_MANAGER(dev))
		mlx5_eचयन_disable(dev->priv.eचयन, clear_vf);

	अगर (mlx5_रुको_क्रम_pages(dev, &dev->priv.vfs_pages))
		mlx5_core_warn(dev, "timeout reclaiming VFs pages\n");
पूर्ण

अटल पूर्णांक mlx5_sriov_enable(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	पूर्णांक err;

	err = mlx5_device_enable_sriov(dev, num_vfs);
	अगर (err) अणु
		mlx5_core_warn(dev, "mlx5_device_enable_sriov failed : %d\n", err);
		वापस err;
	पूर्ण

	err = pci_enable_sriov(pdev, num_vfs);
	अगर (err) अणु
		mlx5_core_warn(dev, "pci_enable_sriov failed : %d\n", err);
		mlx5_device_disable_sriov(dev, num_vfs, true);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlx5_sriov_disable(काष्ठा pci_dev *pdev)
अणु
	काष्ठा mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	पूर्णांक num_vfs = pci_num_vf(dev->pdev);

	pci_disable_sriov(pdev);
	mlx5_device_disable_sriov(dev, num_vfs, true);
पूर्ण

पूर्णांक mlx5_core_sriov_configure(काष्ठा pci_dev *pdev, पूर्णांक num_vfs)
अणु
	काष्ठा mlx5_core_dev *dev  = pci_get_drvdata(pdev);
	काष्ठा mlx5_core_sriov *sriov = &dev->priv.sriov;
	पूर्णांक err = 0;

	mlx5_core_dbg(dev, "requested num_vfs %d\n", num_vfs);

	अगर (num_vfs)
		err = mlx5_sriov_enable(pdev, num_vfs);
	अन्यथा
		mlx5_sriov_disable(pdev);

	अगर (!err)
		sriov->num_vfs = num_vfs;
	वापस err ? err : num_vfs;
पूर्ण

पूर्णांक mlx5_core_sriov_set_msix_vec_count(काष्ठा pci_dev *vf, पूर्णांक msix_vec_count)
अणु
	काष्ठा pci_dev *pf = pci_physfn(vf);
	काष्ठा mlx5_core_sriov *sriov;
	काष्ठा mlx5_core_dev *dev;
	पूर्णांक num_vf_msix, id;

	dev = pci_get_drvdata(pf);
	num_vf_msix = MLX5_CAP_GEN_MAX(dev, num_total_dynamic_vf_msix);
	अगर (!num_vf_msix)
		वापस -EOPNOTSUPP;

	अगर (!msix_vec_count)
		msix_vec_count =
			mlx5_get_शेष_msix_vec_count(dev, pci_num_vf(pf));

	sriov = &dev->priv.sriov;

	/* Reversed translation of PCI VF function number to the पूर्णांकernal
	 * function_id, which exists in the name of virtfn symlink.
	 */
	क्रम (id = 0; id < pci_num_vf(pf); id++) अणु
		अगर (!sriov->vfs_ctx[id].enabled)
			जारी;

		अगर (vf->devfn == pci_iov_virtfn_devfn(pf, id))
			अवरोध;
	पूर्ण

	अगर (id == pci_num_vf(pf) || !sriov->vfs_ctx[id].enabled)
		वापस -EINVAL;

	वापस mlx5_set_msix_vec_count(dev, id + 1, msix_vec_count);
पूर्ण

पूर्णांक mlx5_sriov_attach(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_is_pf(dev) || !pci_num_vf(dev->pdev))
		वापस 0;

	/* If sriov VFs exist in PCI level, enable them in device level */
	वापस mlx5_device_enable_sriov(dev, pci_num_vf(dev->pdev));
पूर्ण

व्योम mlx5_sriov_detach(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_is_pf(dev))
		वापस;

	mlx5_device_disable_sriov(dev, pci_num_vf(dev->pdev), false);
पूर्ण

अटल u16 mlx5_get_max_vfs(काष्ठा mlx5_core_dev *dev)
अणु
	u16 host_total_vfs;
	स्थिर u32 *out;

	अगर (mlx5_core_is_ecpf_esw_manager(dev)) अणु
		out = mlx5_esw_query_functions(dev);

		/* Old FW करोesn't support getting total_vfs from esw func
		 * but supports getting it from pci_sriov.
		 */
		अगर (IS_ERR(out))
			जाओ करोne;
		host_total_vfs = MLX5_GET(query_esw_functions_out, out,
					  host_params_context.host_total_vfs);
		kvमुक्त(out);
		अगर (host_total_vfs)
			वापस host_total_vfs;
	पूर्ण

करोne:
	वापस pci_sriov_get_totalvfs(dev->pdev);
पूर्ण

पूर्णांक mlx5_sriov_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_sriov *sriov = &dev->priv.sriov;
	काष्ठा pci_dev *pdev = dev->pdev;
	पूर्णांक total_vfs;

	अगर (!mlx5_core_is_pf(dev))
		वापस 0;

	total_vfs = pci_sriov_get_totalvfs(pdev);
	sriov->max_vfs = mlx5_get_max_vfs(dev);
	sriov->num_vfs = pci_num_vf(pdev);
	sriov->vfs_ctx = kसुस्मृति(total_vfs, माप(*sriov->vfs_ctx), GFP_KERNEL);
	अगर (!sriov->vfs_ctx)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम mlx5_sriov_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_core_sriov *sriov = &dev->priv.sriov;

	अगर (!mlx5_core_is_pf(dev))
		वापस;

	kमुक्त(sriov->vfs_ctx);
पूर्ण
