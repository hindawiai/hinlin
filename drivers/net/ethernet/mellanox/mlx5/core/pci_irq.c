<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2019 Mellanox Technologies. */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/module.h>
#समावेश <linux/mlx5/driver.h>
#समावेश "mlx5_core.h"
#अगर_घोषित CONFIG_RFS_ACCEL
#समावेश <linux/cpu_rmap.h>
#पूर्ण_अगर

#घोषणा MLX5_MAX_IRQ_NAME (32)

काष्ठा mlx5_irq अणु
	काष्ठा atomic_notअगरier_head nh;
	cpumask_var_t mask;
	अक्षर name[MLX5_MAX_IRQ_NAME];
पूर्ण;

काष्ठा mlx5_irq_table अणु
	काष्ठा mlx5_irq *irq;
	पूर्णांक nvec;
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा cpu_rmap *rmap;
#पूर्ण_अगर
पूर्ण;

पूर्णांक mlx5_irq_table_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_irq_table *irq_table;

	अगर (mlx5_core_is_sf(dev))
		वापस 0;

	irq_table = kvzalloc(माप(*irq_table), GFP_KERNEL);
	अगर (!irq_table)
		वापस -ENOMEM;

	dev->priv.irq_table = irq_table;
	वापस 0;
पूर्ण

व्योम mlx5_irq_table_cleanup(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (mlx5_core_is_sf(dev))
		वापस;

	kvमुक्त(dev->priv.irq_table);
पूर्ण

पूर्णांक mlx5_irq_get_num_comp(काष्ठा mlx5_irq_table *table)
अणु
	वापस table->nvec - MLX5_IRQ_VEC_COMP_BASE;
पूर्ण

अटल काष्ठा mlx5_irq *mlx5_irq_get(काष्ठा mlx5_core_dev *dev, पूर्णांक vecidx)
अणु
	काष्ठा mlx5_irq_table *irq_table = dev->priv.irq_table;

	वापस &irq_table->irq[vecidx];
पूर्ण

/**
 * mlx5_get_शेष_msix_vec_count - Get the शेष number of MSI-X vectors
 *                                   to be sचिन्हित to each VF.
 * @dev: PF to work on
 * @num_vfs: Number of enabled VFs
 */
पूर्णांक mlx5_get_शेष_msix_vec_count(काष्ठा mlx5_core_dev *dev, पूर्णांक num_vfs)
अणु
	पूर्णांक num_vf_msix, min_msix, max_msix;

	num_vf_msix = MLX5_CAP_GEN_MAX(dev, num_total_dynamic_vf_msix);
	अगर (!num_vf_msix)
		वापस 0;

	min_msix = MLX5_CAP_GEN(dev, min_dynamic_vf_msix_table_size);
	max_msix = MLX5_CAP_GEN(dev, max_dynamic_vf_msix_table_size);

	/* Limit maximum number of MSI-X vectors so the शेष configuration
	 * has some available in the pool. This will allow the user to increase
	 * the number of vectors in a VF without having to first size-करोwn other
	 * VFs.
	 */
	वापस max(min(num_vf_msix / num_vfs, max_msix / 2), min_msix);
पूर्ण

/**
 * mlx5_set_msix_vec_count - Set dynamically allocated MSI-X on the VF
 * @dev: PF to work on
 * @function_id: Internal PCI VF function IDd
 * @msix_vec_count: Number of MSI-X vectors to set
 */
पूर्णांक mlx5_set_msix_vec_count(काष्ठा mlx5_core_dev *dev, पूर्णांक function_id,
			    पूर्णांक msix_vec_count)
अणु
	पूर्णांक query_sz = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	पूर्णांक set_sz = MLX5_ST_SZ_BYTES(set_hca_cap_in);
	व्योम *hca_cap = शून्य, *query_cap = शून्य, *cap;
	पूर्णांक num_vf_msix, min_msix, max_msix;
	पूर्णांक ret;

	num_vf_msix = MLX5_CAP_GEN_MAX(dev, num_total_dynamic_vf_msix);
	अगर (!num_vf_msix)
		वापस 0;

	अगर (!MLX5_CAP_GEN(dev, vport_group_manager) || !mlx5_core_is_pf(dev))
		वापस -EOPNOTSUPP;

	min_msix = MLX5_CAP_GEN(dev, min_dynamic_vf_msix_table_size);
	max_msix = MLX5_CAP_GEN(dev, max_dynamic_vf_msix_table_size);

	अगर (msix_vec_count < min_msix)
		वापस -EINVAL;

	अगर (msix_vec_count > max_msix)
		वापस -EOVERFLOW;

	query_cap = kzalloc(query_sz, GFP_KERNEL);
	hca_cap = kzalloc(set_sz, GFP_KERNEL);
	अगर (!hca_cap || !query_cap) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = mlx5_vport_get_other_func_cap(dev, function_id, query_cap);
	अगर (ret)
		जाओ out;

	cap = MLX5_ADDR_OF(set_hca_cap_in, hca_cap, capability);
	स_नकल(cap, MLX5_ADDR_OF(query_hca_cap_out, query_cap, capability),
	       MLX5_UN_SZ_BYTES(hca_cap_जोड़));
	MLX5_SET(cmd_hca_cap, cap, dynamic_msix_table_size, msix_vec_count);

	MLX5_SET(set_hca_cap_in, hca_cap, opcode, MLX5_CMD_OP_SET_HCA_CAP);
	MLX5_SET(set_hca_cap_in, hca_cap, other_function, 1);
	MLX5_SET(set_hca_cap_in, hca_cap, function_id, function_id);

	MLX5_SET(set_hca_cap_in, hca_cap, op_mod,
		 MLX5_SET_HCA_CAP_OP_MOD_GENERAL_DEVICE << 1);
	ret = mlx5_cmd_exec_in(dev, set_hca_cap, hca_cap);
out:
	kमुक्त(hca_cap);
	kमुक्त(query_cap);
	वापस ret;
पूर्ण

पूर्णांक mlx5_irq_attach_nb(काष्ठा mlx5_irq_table *irq_table, पूर्णांक vecidx,
		       काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_irq *irq;

	irq = &irq_table->irq[vecidx];
	वापस atomic_notअगरier_chain_रेजिस्टर(&irq->nh, nb);
पूर्ण

पूर्णांक mlx5_irq_detach_nb(काष्ठा mlx5_irq_table *irq_table, पूर्णांक vecidx,
		       काष्ठा notअगरier_block *nb)
अणु
	काष्ठा mlx5_irq *irq;

	irq = &irq_table->irq[vecidx];
	वापस atomic_notअगरier_chain_unरेजिस्टर(&irq->nh, nb);
पूर्ण

अटल irqवापस_t mlx5_irq_पूर्णांक_handler(पूर्णांक irq, व्योम *nh)
अणु
	atomic_notअगरier_call_chain(nh, 0, शून्य);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम irq_set_name(अक्षर *name, पूर्णांक vecidx)
अणु
	अगर (vecidx == 0) अणु
		snम_लिखो(name, MLX5_MAX_IRQ_NAME, "mlx5_async");
		वापस;
	पूर्ण

	snम_लिखो(name, MLX5_MAX_IRQ_NAME, "mlx5_comp%d",
		 vecidx - MLX5_IRQ_VEC_COMP_BASE);
पूर्ण

अटल पूर्णांक request_irqs(काष्ठा mlx5_core_dev *dev, पूर्णांक nvec)
अणु
	अक्षर name[MLX5_MAX_IRQ_NAME];
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < nvec; i++) अणु
		काष्ठा mlx5_irq *irq = mlx5_irq_get(dev, i);
		पूर्णांक irqn = pci_irq_vector(dev->pdev, i);

		irq_set_name(name, i);
		ATOMIC_INIT_NOTIFIER_HEAD(&irq->nh);
		snम_लिखो(irq->name, MLX5_MAX_IRQ_NAME,
			 "%s@pci:%s", name, pci_name(dev->pdev));
		err = request_irq(irqn, mlx5_irq_पूर्णांक_handler, 0, irq->name,
				  &irq->nh);
		अगर (err) अणु
			mlx5_core_err(dev, "Failed to request irq\n");
			जाओ err_request_irq;
		पूर्ण
	पूर्ण
	वापस 0;

err_request_irq:
	जबतक (i--) अणु
		काष्ठा mlx5_irq *irq = mlx5_irq_get(dev, i);
		पूर्णांक irqn = pci_irq_vector(dev->pdev, i);

		मुक्त_irq(irqn, &irq->nh);
	पूर्ण
	वापस  err;
पूर्ण

अटल व्योम irq_clear_rmap(काष्ठा mlx5_core_dev *dev)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा mlx5_irq_table *irq_table = dev->priv.irq_table;

	मुक्त_irq_cpu_rmap(irq_table->rmap);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक irq_set_rmap(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक err = 0;
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा mlx5_irq_table *irq_table = mdev->priv.irq_table;
	पूर्णांक num_affinity_vec;
	पूर्णांक vecidx;

	num_affinity_vec = mlx5_irq_get_num_comp(irq_table);
	irq_table->rmap = alloc_irq_cpu_rmap(num_affinity_vec);
	अगर (!irq_table->rmap) अणु
		err = -ENOMEM;
		mlx5_core_err(mdev, "Failed to allocate cpu_rmap. err %d", err);
		जाओ err_out;
	पूर्ण

	vecidx = MLX5_IRQ_VEC_COMP_BASE;
	क्रम (; vecidx < irq_table->nvec; vecidx++) अणु
		err = irq_cpu_rmap_add(irq_table->rmap,
				       pci_irq_vector(mdev->pdev, vecidx));
		अगर (err) अणु
			mlx5_core_err(mdev, "irq_cpu_rmap_add failed. err %d",
				      err);
			जाओ err_irq_cpu_rmap_add;
		पूर्ण
	पूर्ण
	वापस 0;

err_irq_cpu_rmap_add:
	irq_clear_rmap(mdev);
err_out:
#पूर्ण_अगर
	वापस err;
पूर्ण

/* Completion IRQ vectors */

अटल पूर्णांक set_comp_irq_affinity_hपूर्णांक(काष्ठा mlx5_core_dev *mdev, पूर्णांक i)
अणु
	पूर्णांक vecidx = MLX5_IRQ_VEC_COMP_BASE + i;
	काष्ठा mlx5_irq *irq;
	पूर्णांक irqn;

	irq = mlx5_irq_get(mdev, vecidx);
	irqn = pci_irq_vector(mdev->pdev, vecidx);
	अगर (!zalloc_cpumask_var(&irq->mask, GFP_KERNEL)) अणु
		mlx5_core_warn(mdev, "zalloc_cpumask_var failed");
		वापस -ENOMEM;
	पूर्ण

	cpumask_set_cpu(cpumask_local_spपढ़ो(i, mdev->priv.numa_node),
			irq->mask);
	अगर (IS_ENABLED(CONFIG_SMP) &&
	    irq_set_affinity_hपूर्णांक(irqn, irq->mask))
		mlx5_core_warn(mdev, "irq_set_affinity_hint failed, irq 0x%.4x",
			       irqn);

	वापस 0;
पूर्ण

अटल व्योम clear_comp_irq_affinity_hपूर्णांक(काष्ठा mlx5_core_dev *mdev, पूर्णांक i)
अणु
	पूर्णांक vecidx = MLX5_IRQ_VEC_COMP_BASE + i;
	काष्ठा mlx5_irq *irq;
	पूर्णांक irqn;

	irq = mlx5_irq_get(mdev, vecidx);
	irqn = pci_irq_vector(mdev->pdev, vecidx);
	irq_set_affinity_hपूर्णांक(irqn, शून्य);
	मुक्त_cpumask_var(irq->mask);
पूर्ण

अटल पूर्णांक set_comp_irq_affinity_hपूर्णांकs(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक nvec = mlx5_irq_get_num_comp(mdev->priv.irq_table);
	पूर्णांक err;
	पूर्णांक i;

	क्रम (i = 0; i < nvec; i++) अणु
		err = set_comp_irq_affinity_hपूर्णांक(mdev, i);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	क्रम (i--; i >= 0; i--)
		clear_comp_irq_affinity_hपूर्णांक(mdev, i);

	वापस err;
पूर्ण

अटल व्योम clear_comp_irqs_affinity_hपूर्णांकs(काष्ठा mlx5_core_dev *mdev)
अणु
	पूर्णांक nvec = mlx5_irq_get_num_comp(mdev->priv.irq_table);
	पूर्णांक i;

	क्रम (i = 0; i < nvec; i++)
		clear_comp_irq_affinity_hपूर्णांक(mdev, i);
पूर्ण

काष्ठा cpumask *
mlx5_irq_get_affinity_mask(काष्ठा mlx5_irq_table *irq_table, पूर्णांक vecidx)
अणु
	वापस irq_table->irq[vecidx].mask;
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
काष्ठा cpu_rmap *mlx5_irq_get_rmap(काष्ठा mlx5_irq_table *irq_table)
अणु
	वापस irq_table->rmap;
पूर्ण
#पूर्ण_अगर

अटल व्योम unrequest_irqs(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_irq_table *table = dev->priv.irq_table;
	पूर्णांक i;

	क्रम (i = 0; i < table->nvec; i++)
		मुक्त_irq(pci_irq_vector(dev->pdev, i),
			 &mlx5_irq_get(dev, i)->nh);
पूर्ण

पूर्णांक mlx5_irq_table_create(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_priv *priv = &dev->priv;
	काष्ठा mlx5_irq_table *table = priv->irq_table;
	पूर्णांक num_eqs = MLX5_CAP_GEN(dev, max_num_eqs) ?
		      MLX5_CAP_GEN(dev, max_num_eqs) :
		      1 << MLX5_CAP_GEN(dev, log_max_eq);
	पूर्णांक nvec;
	पूर्णांक err;

	अगर (mlx5_core_is_sf(dev))
		वापस 0;

	nvec = MLX5_CAP_GEN(dev, num_ports) * num_online_cpus() +
	       MLX5_IRQ_VEC_COMP_BASE;
	nvec = min_t(पूर्णांक, nvec, num_eqs);
	अगर (nvec <= MLX5_IRQ_VEC_COMP_BASE)
		वापस -ENOMEM;

	table->irq = kसुस्मृति(nvec, माप(*table->irq), GFP_KERNEL);
	अगर (!table->irq)
		वापस -ENOMEM;

	nvec = pci_alloc_irq_vectors(dev->pdev, MLX5_IRQ_VEC_COMP_BASE + 1,
				     nvec, PCI_IRQ_MSIX);
	अगर (nvec < 0) अणु
		err = nvec;
		जाओ err_मुक्त_irq;
	पूर्ण

	table->nvec = nvec;

	err = irq_set_rmap(dev);
	अगर (err)
		जाओ err_set_rmap;

	err = request_irqs(dev, nvec);
	अगर (err)
		जाओ err_request_irqs;

	err = set_comp_irq_affinity_hपूर्णांकs(dev);
	अगर (err) अणु
		mlx5_core_err(dev, "Failed to alloc affinity hint cpumask\n");
		जाओ err_set_affinity;
	पूर्ण

	वापस 0;

err_set_affinity:
	unrequest_irqs(dev);
err_request_irqs:
	irq_clear_rmap(dev);
err_set_rmap:
	pci_मुक्त_irq_vectors(dev->pdev);
err_मुक्त_irq:
	kमुक्त(table->irq);
	वापस err;
पूर्ण

व्योम mlx5_irq_table_destroy(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_irq_table *table = dev->priv.irq_table;
	पूर्णांक i;

	अगर (mlx5_core_is_sf(dev))
		वापस;

	/* मुक्त_irq requires that affinity and rmap will be cleared
	 * beक्रमe calling it. This is why there is asymmetry with set_rmap
	 * which should be called after alloc_irq but beक्रमe request_irq.
	 */
	irq_clear_rmap(dev);
	clear_comp_irqs_affinity_hपूर्णांकs(dev);
	क्रम (i = 0; i < table->nvec; i++)
		मुक्त_irq(pci_irq_vector(dev->pdev, i),
			 &mlx5_irq_get(dev, i)->nh);
	pci_मुक्त_irq_vectors(dev->pdev);
	kमुक्त(table->irq);
पूर्ण

काष्ठा mlx5_irq_table *mlx5_irq_table_get(काष्ठा mlx5_core_dev *dev)
अणु
#अगर_घोषित CONFIG_MLX5_SF
	अगर (mlx5_core_is_sf(dev))
		वापस dev->priv.parent_mdev->priv.irq_table;
#पूर्ण_अगर
	वापस dev->priv.irq_table;
पूर्ण
