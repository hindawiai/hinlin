<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2014 The Linux Foundation. All rights reserved.
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/component.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <drm/drm_irq.h>

#समावेश "vc4_drv.h"
#समावेश "vc4_regs.h"

अटल स्थिर काष्ठा debugfs_reg32 v3d_regs[] = अणु
	VC4_REG32(V3D_IDENT0),
	VC4_REG32(V3D_IDENT1),
	VC4_REG32(V3D_IDENT2),
	VC4_REG32(V3D_SCRATCH),
	VC4_REG32(V3D_L2CACTL),
	VC4_REG32(V3D_SLCACTL),
	VC4_REG32(V3D_INTCTL),
	VC4_REG32(V3D_INTENA),
	VC4_REG32(V3D_INTDIS),
	VC4_REG32(V3D_CT0CS),
	VC4_REG32(V3D_CT1CS),
	VC4_REG32(V3D_CT0EA),
	VC4_REG32(V3D_CT1EA),
	VC4_REG32(V3D_CT0CA),
	VC4_REG32(V3D_CT1CA),
	VC4_REG32(V3D_CT00RA0),
	VC4_REG32(V3D_CT01RA0),
	VC4_REG32(V3D_CT0LC),
	VC4_REG32(V3D_CT1LC),
	VC4_REG32(V3D_CT0PC),
	VC4_REG32(V3D_CT1PC),
	VC4_REG32(V3D_PCS),
	VC4_REG32(V3D_BFC),
	VC4_REG32(V3D_RFC),
	VC4_REG32(V3D_BPCA),
	VC4_REG32(V3D_BPCS),
	VC4_REG32(V3D_BPOA),
	VC4_REG32(V3D_BPOS),
	VC4_REG32(V3D_BXCF),
	VC4_REG32(V3D_SQRSV0),
	VC4_REG32(V3D_SQRSV1),
	VC4_REG32(V3D_SQCNTL),
	VC4_REG32(V3D_SRQPC),
	VC4_REG32(V3D_SRQUA),
	VC4_REG32(V3D_SRQUL),
	VC4_REG32(V3D_SRQCS),
	VC4_REG32(V3D_VPACNTL),
	VC4_REG32(V3D_VPMBASE),
	VC4_REG32(V3D_PCTRC),
	VC4_REG32(V3D_PCTRE),
	VC4_REG32(V3D_PCTR(0)),
	VC4_REG32(V3D_PCTRS(0)),
	VC4_REG32(V3D_PCTR(1)),
	VC4_REG32(V3D_PCTRS(1)),
	VC4_REG32(V3D_PCTR(2)),
	VC4_REG32(V3D_PCTRS(2)),
	VC4_REG32(V3D_PCTR(3)),
	VC4_REG32(V3D_PCTRS(3)),
	VC4_REG32(V3D_PCTR(4)),
	VC4_REG32(V3D_PCTRS(4)),
	VC4_REG32(V3D_PCTR(5)),
	VC4_REG32(V3D_PCTRS(5)),
	VC4_REG32(V3D_PCTR(6)),
	VC4_REG32(V3D_PCTRS(6)),
	VC4_REG32(V3D_PCTR(7)),
	VC4_REG32(V3D_PCTRS(7)),
	VC4_REG32(V3D_PCTR(8)),
	VC4_REG32(V3D_PCTRS(8)),
	VC4_REG32(V3D_PCTR(9)),
	VC4_REG32(V3D_PCTRS(9)),
	VC4_REG32(V3D_PCTR(10)),
	VC4_REG32(V3D_PCTRS(10)),
	VC4_REG32(V3D_PCTR(11)),
	VC4_REG32(V3D_PCTRS(11)),
	VC4_REG32(V3D_PCTR(12)),
	VC4_REG32(V3D_PCTRS(12)),
	VC4_REG32(V3D_PCTR(13)),
	VC4_REG32(V3D_PCTRS(13)),
	VC4_REG32(V3D_PCTR(14)),
	VC4_REG32(V3D_PCTRS(14)),
	VC4_REG32(V3D_PCTR(15)),
	VC4_REG32(V3D_PCTRS(15)),
	VC4_REG32(V3D_DBGE),
	VC4_REG32(V3D_FDBGO),
	VC4_REG32(V3D_FDBGB),
	VC4_REG32(V3D_FDBGR),
	VC4_REG32(V3D_FDBGS),
	VC4_REG32(V3D_ERRSTAT),
पूर्ण;

अटल पूर्णांक vc4_v3d_debugfs_ident(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);
	पूर्णांक ret = vc4_v3d_pm_get(vc4);

	अगर (ret == 0) अणु
		uपूर्णांक32_t ident1 = V3D_READ(V3D_IDENT1);
		uपूर्णांक32_t nslc = VC4_GET_FIELD(ident1, V3D_IDENT1_NSLC);
		uपूर्णांक32_t tups = VC4_GET_FIELD(ident1, V3D_IDENT1_TUPS);
		uपूर्णांक32_t qups = VC4_GET_FIELD(ident1, V3D_IDENT1_QUPS);

		seq_म_लिखो(m, "Revision:   %d\n",
			   VC4_GET_FIELD(ident1, V3D_IDENT1_REV));
		seq_म_लिखो(m, "Slices:     %d\n", nslc);
		seq_म_लिखो(m, "TMUs:       %d\n", nslc * tups);
		seq_म_लिखो(m, "QPUs:       %d\n", nslc * qups);
		seq_म_लिखो(m, "Semaphores: %d\n",
			   VC4_GET_FIELD(ident1, V3D_IDENT1_NSEM));
		vc4_v3d_pm_put(vc4);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Wraps pm_runसमय_get_sync() in a refcount, so that we can reliably
 * get the pm_runसमय refcount to 0 in vc4_reset().
 */
पूर्णांक
vc4_v3d_pm_get(काष्ठा vc4_dev *vc4)
अणु
	mutex_lock(&vc4->घातer_lock);
	अगर (vc4->घातer_refcount++ == 0) अणु
		पूर्णांक ret = pm_runसमय_get_sync(&vc4->v3d->pdev->dev);

		अगर (ret < 0) अणु
			vc4->घातer_refcount--;
			mutex_unlock(&vc4->घातer_lock);
			वापस ret;
		पूर्ण
	पूर्ण
	mutex_unlock(&vc4->घातer_lock);

	वापस 0;
पूर्ण

व्योम
vc4_v3d_pm_put(काष्ठा vc4_dev *vc4)
अणु
	mutex_lock(&vc4->घातer_lock);
	अगर (--vc4->घातer_refcount == 0) अणु
		pm_runसमय_mark_last_busy(&vc4->v3d->pdev->dev);
		pm_runसमय_put_स्वतःsuspend(&vc4->v3d->pdev->dev);
	पूर्ण
	mutex_unlock(&vc4->घातer_lock);
पूर्ण

अटल व्योम vc4_v3d_init_hw(काष्ठा drm_device *dev)
अणु
	काष्ठा vc4_dev *vc4 = to_vc4_dev(dev);

	/* Take all the memory that would have been reserved क्रम user
	 * QPU programs, since we करोn't have an पूर्णांकerface क्रम running
	 * them, anyway.
	 */
	V3D_WRITE(V3D_VPMBASE, 0);
पूर्ण

पूर्णांक vc4_v3d_get_bin_slot(काष्ठा vc4_dev *vc4)
अणु
	काष्ठा drm_device *dev = &vc4->base;
	अचिन्हित दीर्घ irqflags;
	पूर्णांक slot;
	uपूर्णांक64_t seqno = 0;
	काष्ठा vc4_exec_info *exec;

try_again:
	spin_lock_irqsave(&vc4->job_lock, irqflags);
	slot = ffs(~vc4->bin_alloc_used);
	अगर (slot != 0) अणु
		/* Switch from ffs() bit index to a 0-based index. */
		slot--;
		vc4->bin_alloc_used |= BIT(slot);
		spin_unlock_irqrestore(&vc4->job_lock, irqflags);
		वापस slot;
	पूर्ण

	/* Couldn't find an खोलो slot.  Wait क्रम render to complete
	 * and try again.
	 */
	exec = vc4_last_render_job(vc4);
	अगर (exec)
		seqno = exec->seqno;
	spin_unlock_irqrestore(&vc4->job_lock, irqflags);

	अगर (seqno) अणु
		पूर्णांक ret = vc4_रुको_क्रम_seqno(dev, seqno, ~0ull, true);

		अगर (ret == 0)
			जाओ try_again;

		वापस ret;
	पूर्ण

	वापस -ENOMEM;
पूर्ण

/*
 * bin_bo_alloc() - allocates the memory that will be used क्रम
 * tile binning.
 *
 * The binner has a limitation that the addresses in the tile state
 * buffer that poपूर्णांक पूर्णांकo the tile alloc buffer or binner overflow
 * memory only have 28 bits (256MB), and the top 4 on the bus क्रम
 * tile alloc references end up coming from the tile state buffer's
 * address.
 *
 * To work around this, we allocate a single large buffer जबतक V3D is
 * in use, make sure that it has the top 4 bits स्थिरant across its
 * entire extent, and then put the tile state, tile alloc, and binner
 * overflow memory inside that buffer.
 *
 * This creates a limitation where we may not be able to execute a job
 * अगर it करोesn't fit within the buffer that we allocated up front.
 * However, it turns out that 16MB is "enough for anybody", and
 * real-world applications run पूर्णांकo allocation failures from the
 * overall CMA pool beक्रमe they make scenes complicated enough to run
 * out of bin space.
 */
अटल पूर्णांक bin_bo_alloc(काष्ठा vc4_dev *vc4)
अणु
	काष्ठा vc4_v3d *v3d = vc4->v3d;
	uपूर्णांक32_t size = 16 * 1024 * 1024;
	पूर्णांक ret = 0;
	काष्ठा list_head list;

	अगर (!v3d)
		वापस -ENODEV;

	/* We may need to try allocating more than once to get a BO
	 * that करोesn't cross 256MB.  Track the ones we've allocated
	 * that failed so far, so that we can मुक्त them when we've got
	 * one that succeeded (अगर we मुक्तd them right away, our next
	 * allocation would probably be the same chunk of memory).
	 */
	INIT_LIST_HEAD(&list);

	जबतक (true) अणु
		काष्ठा vc4_bo *bo = vc4_bo_create(&vc4->base, size, true,
						  VC4_BO_TYPE_BIN);

		अगर (IS_ERR(bo)) अणु
			ret = PTR_ERR(bo);

			dev_err(&v3d->pdev->dev,
				"Failed to allocate memory for tile binning: "
				"%d. You may need to enable CMA or give it "
				"more memory.",
				ret);
			अवरोध;
		पूर्ण

		/* Check अगर this BO won't trigger the addressing bug. */
		अगर ((bo->base.paddr & 0xf0000000) ==
		    ((bo->base.paddr + bo->base.base.size - 1) & 0xf0000000)) अणु
			vc4->bin_bo = bo;

			/* Set up क्रम allocating 512KB chunks of
			 * binner memory.  The biggest allocation we
			 * need to करो is क्रम the initial tile alloc +
			 * tile state buffer.  We can render to a
			 * maximum of ((2048*2048) / (32*32) = 4096
			 * tiles in a frame (until we करो भग्नing
			 * poपूर्णांक rendering, at which poपूर्णांक it would be
			 * 8192).  Tile state is 48b/tile (rounded to
			 * a page), and tile alloc is 32b/tile
			 * (rounded to a page), plus a page of extra,
			 * क्रम a total of 320kb क्रम our worst-हाल.
			 * We choose 512kb so that it भागides evenly
			 * पूर्णांकo our 16MB, and the rest of the 512kb
			 * will be used as storage क्रम the overflow
			 * from the initial 32b CL per bin.
			 */
			vc4->bin_alloc_size = 512 * 1024;
			vc4->bin_alloc_used = 0;
			vc4->bin_alloc_overflow = 0;
			WARN_ON_ONCE(माप(vc4->bin_alloc_used) * 8 !=
				     bo->base.base.size / vc4->bin_alloc_size);

			kref_init(&vc4->bin_bo_kref);

			/* Enable the out-of-memory पूर्णांकerrupt to set our
			 * newly-allocated binner BO, potentially from an
			 * alपढ़ोy-pending-but-masked पूर्णांकerrupt.
			 */
			V3D_WRITE(V3D_INTENA, V3D_INT_OUTOMEM);

			अवरोध;
		पूर्ण

		/* Put it on the list to मुक्त later, and try again. */
		list_add(&bo->unref_head, &list);
	पूर्ण

	/* Free all the BOs we allocated but didn't choose. */
	जबतक (!list_empty(&list)) अणु
		काष्ठा vc4_bo *bo = list_last_entry(&list,
						    काष्ठा vc4_bo, unref_head);

		list_del(&bo->unref_head);
		drm_gem_object_put(&bo->base.base);
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक vc4_v3d_bin_bo_get(काष्ठा vc4_dev *vc4, bool *used)
अणु
	पूर्णांक ret = 0;

	mutex_lock(&vc4->bin_bo_lock);

	अगर (used && *used)
		जाओ complete;

	अगर (vc4->bin_bo)
		kref_get(&vc4->bin_bo_kref);
	अन्यथा
		ret = bin_bo_alloc(vc4);

	अगर (ret == 0 && used)
		*used = true;

complete:
	mutex_unlock(&vc4->bin_bo_lock);

	वापस ret;
पूर्ण

अटल व्योम bin_bo_release(काष्ठा kref *ref)
अणु
	काष्ठा vc4_dev *vc4 = container_of(ref, काष्ठा vc4_dev, bin_bo_kref);

	अगर (WARN_ON_ONCE(!vc4->bin_bo))
		वापस;

	drm_gem_object_put(&vc4->bin_bo->base.base);
	vc4->bin_bo = शून्य;
पूर्ण

व्योम vc4_v3d_bin_bo_put(काष्ठा vc4_dev *vc4)
अणु
	mutex_lock(&vc4->bin_bo_lock);
	kref_put(&vc4->bin_bo_kref, bin_bo_release);
	mutex_unlock(&vc4->bin_bo_lock);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक vc4_v3d_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा vc4_v3d *v3d = dev_get_drvdata(dev);
	काष्ठा vc4_dev *vc4 = v3d->vc4;

	vc4_irq_uninstall(&vc4->base);

	clk_disable_unprepare(v3d->clk);

	वापस 0;
पूर्ण

अटल पूर्णांक vc4_v3d_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा vc4_v3d *v3d = dev_get_drvdata(dev);
	काष्ठा vc4_dev *vc4 = v3d->vc4;
	पूर्णांक ret;

	ret = clk_prepare_enable(v3d->clk);
	अगर (ret != 0)
		वापस ret;

	vc4_v3d_init_hw(&vc4->base);

	/* We disabled the IRQ as part of vc4_irq_uninstall in suspend. */
	enable_irq(vc4->base.irq);
	vc4_irq_postinstall(&vc4->base);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक vc4_v3d_bind(काष्ठा device *dev, काष्ठा device *master, व्योम *data)
अणु
	काष्ठा platक्रमm_device *pdev = to_platक्रमm_device(dev);
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);
	काष्ठा vc4_v3d *v3d = शून्य;
	पूर्णांक ret;

	v3d = devm_kzalloc(&pdev->dev, माप(*v3d), GFP_KERNEL);
	अगर (!v3d)
		वापस -ENOMEM;

	dev_set_drvdata(dev, v3d);

	v3d->pdev = pdev;

	v3d->regs = vc4_ioremap_regs(pdev, 0);
	अगर (IS_ERR(v3d->regs))
		वापस PTR_ERR(v3d->regs);
	v3d->regset.base = v3d->regs;
	v3d->regset.regs = v3d_regs;
	v3d->regset.nregs = ARRAY_SIZE(v3d_regs);

	vc4->v3d = v3d;
	v3d->vc4 = vc4;

	v3d->clk = devm_clk_get(dev, शून्य);
	अगर (IS_ERR(v3d->clk)) अणु
		पूर्णांक ret = PTR_ERR(v3d->clk);

		अगर (ret == -ENOENT) अणु
			/* bcm2835 didn't have a घड़ी reference in the DT. */
			ret = 0;
			v3d->clk = शून्य;
		पूर्ण अन्यथा अणु
			अगर (ret != -EPROBE_DEFER)
				dev_err(dev, "Failed to get V3D clock: %d\n",
					ret);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (V3D_READ(V3D_IDENT0) != V3D_EXPECTED_IDENT0) अणु
		DRM_ERROR("V3D_IDENT0 read 0x%08x instead of 0x%08x\n",
			  V3D_READ(V3D_IDENT0), V3D_EXPECTED_IDENT0);
		वापस -EINVAL;
	पूर्ण

	ret = clk_prepare_enable(v3d->clk);
	अगर (ret != 0)
		वापस ret;

	/* Reset the binner overflow address/size at setup, to be sure
	 * we करोn't reuse an old one.
	 */
	V3D_WRITE(V3D_BPOA, 0);
	V3D_WRITE(V3D_BPOS, 0);

	vc4_v3d_init_hw(drm);

	ret = drm_irq_install(drm, platक्रमm_get_irq(pdev, 0));
	अगर (ret) अणु
		DRM_ERROR("Failed to install IRQ handler\n");
		वापस ret;
	पूर्ण

	pm_runसमय_set_active(dev);
	pm_runसमय_use_स्वतःsuspend(dev);
	pm_runसमय_set_स्वतःsuspend_delay(dev, 40); /* a little over 2 frames. */
	pm_runसमय_enable(dev);

	vc4_debugfs_add_file(drm, "v3d_ident", vc4_v3d_debugfs_ident, शून्य);
	vc4_debugfs_add_regset32(drm, "v3d_regs", &v3d->regset);

	वापस 0;
पूर्ण

अटल व्योम vc4_v3d_unbind(काष्ठा device *dev, काष्ठा device *master,
			   व्योम *data)
अणु
	काष्ठा drm_device *drm = dev_get_drvdata(master);
	काष्ठा vc4_dev *vc4 = to_vc4_dev(drm);

	pm_runसमय_disable(dev);

	drm_irq_uninstall(drm);

	/* Disable the binner's overflow memory address, so the next
	 * driver probe (अगर any) करोesn't try to reuse our old
	 * allocation.
	 */
	V3D_WRITE(V3D_BPOA, 0);
	V3D_WRITE(V3D_BPOS, 0);

	vc4->v3d = शून्य;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vc4_v3d_pm_ops = अणु
	SET_RUNTIME_PM_OPS(vc4_v3d_runसमय_suspend, vc4_v3d_runसमय_resume, शून्य)
पूर्ण;

अटल स्थिर काष्ठा component_ops vc4_v3d_ops = अणु
	.bind   = vc4_v3d_bind,
	.unbind = vc4_v3d_unbind,
पूर्ण;

अटल पूर्णांक vc4_v3d_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस component_add(&pdev->dev, &vc4_v3d_ops);
पूर्ण

अटल पूर्णांक vc4_v3d_dev_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	component_del(&pdev->dev, &vc4_v3d_ops);
	वापस 0;
पूर्ण

स्थिर काष्ठा of_device_id vc4_v3d_dt_match[] = अणु
	अणु .compatible = "brcm,bcm2835-v3d" पूर्ण,
	अणु .compatible = "brcm,cygnus-v3d" पूर्ण,
	अणु .compatible = "brcm,vc4-v3d" पूर्ण,
	अणुपूर्ण
पूर्ण;

काष्ठा platक्रमm_driver vc4_v3d_driver = अणु
	.probe = vc4_v3d_dev_probe,
	.हटाओ = vc4_v3d_dev_हटाओ,
	.driver = अणु
		.name = "vc4_v3d",
		.of_match_table = vc4_v3d_dt_match,
		.pm = &vc4_v3d_pm_ops,
	पूर्ण,
पूर्ण;
