<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (C) 2014-2018 Broadcom */

#समावेश <linux/circ_buf.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/seq_file.h>

#समावेश <drm/drm_debugfs.h>

#समावेश "v3d_drv.h"
#समावेश "v3d_regs.h"

#घोषणा REGDEF(reg) अणु reg, #reg पूर्ण
काष्ठा v3d_reg_def अणु
	u32 reg;
	स्थिर अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा v3d_reg_def v3d_hub_reg_defs[] = अणु
	REGDEF(V3D_HUB_AXICFG),
	REGDEF(V3D_HUB_UIFCFG),
	REGDEF(V3D_HUB_IDENT0),
	REGDEF(V3D_HUB_IDENT1),
	REGDEF(V3D_HUB_IDENT2),
	REGDEF(V3D_HUB_IDENT3),
	REGDEF(V3D_HUB_INT_STS),
	REGDEF(V3D_HUB_INT_MSK_STS),

	REGDEF(V3D_MMU_CTL),
	REGDEF(V3D_MMU_VIO_ADDR),
	REGDEF(V3D_MMU_VIO_ID),
	REGDEF(V3D_MMU_DEBUG_INFO),
पूर्ण;

अटल स्थिर काष्ठा v3d_reg_def v3d_gca_reg_defs[] = अणु
	REGDEF(V3D_GCA_SAFE_SHUTDOWN),
	REGDEF(V3D_GCA_SAFE_SHUTDOWN_ACK),
पूर्ण;

अटल स्थिर काष्ठा v3d_reg_def v3d_core_reg_defs[] = अणु
	REGDEF(V3D_CTL_IDENT0),
	REGDEF(V3D_CTL_IDENT1),
	REGDEF(V3D_CTL_IDENT2),
	REGDEF(V3D_CTL_MISCCFG),
	REGDEF(V3D_CTL_INT_STS),
	REGDEF(V3D_CTL_INT_MSK_STS),
	REGDEF(V3D_CLE_CT0CS),
	REGDEF(V3D_CLE_CT0CA),
	REGDEF(V3D_CLE_CT0EA),
	REGDEF(V3D_CLE_CT1CS),
	REGDEF(V3D_CLE_CT1CA),
	REGDEF(V3D_CLE_CT1EA),

	REGDEF(V3D_PTB_BPCA),
	REGDEF(V3D_PTB_BPCS),

	REGDEF(V3D_GMP_STATUS),
	REGDEF(V3D_GMP_CFG),
	REGDEF(V3D_GMP_VIO_ADDR),

	REGDEF(V3D_ERR_FDBGO),
	REGDEF(V3D_ERR_FDBGB),
	REGDEF(V3D_ERR_FDBGS),
	REGDEF(V3D_ERR_STAT),
पूर्ण;

अटल स्थिर काष्ठा v3d_reg_def v3d_csd_reg_defs[] = अणु
	REGDEF(V3D_CSD_STATUS),
	REGDEF(V3D_CSD_CURRENT_CFG0),
	REGDEF(V3D_CSD_CURRENT_CFG1),
	REGDEF(V3D_CSD_CURRENT_CFG2),
	REGDEF(V3D_CSD_CURRENT_CFG3),
	REGDEF(V3D_CSD_CURRENT_CFG4),
	REGDEF(V3D_CSD_CURRENT_CFG5),
	REGDEF(V3D_CSD_CURRENT_CFG6),
पूर्ण;

अटल पूर्णांक v3d_v3d_debugfs_regs(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	पूर्णांक i, core;

	क्रम (i = 0; i < ARRAY_SIZE(v3d_hub_reg_defs); i++) अणु
		seq_म_लिखो(m, "%s (0x%04x): 0x%08x\n",
			   v3d_hub_reg_defs[i].name, v3d_hub_reg_defs[i].reg,
			   V3D_READ(v3d_hub_reg_defs[i].reg));
	पूर्ण

	अगर (v3d->ver < 41) अणु
		क्रम (i = 0; i < ARRAY_SIZE(v3d_gca_reg_defs); i++) अणु
			seq_म_लिखो(m, "%s (0x%04x): 0x%08x\n",
				   v3d_gca_reg_defs[i].name,
				   v3d_gca_reg_defs[i].reg,
				   V3D_GCA_READ(v3d_gca_reg_defs[i].reg));
		पूर्ण
	पूर्ण

	क्रम (core = 0; core < v3d->cores; core++) अणु
		क्रम (i = 0; i < ARRAY_SIZE(v3d_core_reg_defs); i++) अणु
			seq_म_लिखो(m, "core %d %s (0x%04x): 0x%08x\n",
				   core,
				   v3d_core_reg_defs[i].name,
				   v3d_core_reg_defs[i].reg,
				   V3D_CORE_READ(core,
						 v3d_core_reg_defs[i].reg));
		पूर्ण

		अगर (v3d_has_csd(v3d)) अणु
			क्रम (i = 0; i < ARRAY_SIZE(v3d_csd_reg_defs); i++) अणु
				seq_म_लिखो(m, "core %d %s (0x%04x): 0x%08x\n",
					   core,
					   v3d_csd_reg_defs[i].name,
					   v3d_csd_reg_defs[i].reg,
					   V3D_CORE_READ(core,
							 v3d_csd_reg_defs[i].reg));
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक v3d_v3d_debugfs_ident(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	u32 ident0, ident1, ident2, ident3, cores;
	पूर्णांक ret, core;

	ret = pm_runसमय_get_sync(v3d->drm.dev);
	अगर (ret < 0)
		वापस ret;

	ident0 = V3D_READ(V3D_HUB_IDENT0);
	ident1 = V3D_READ(V3D_HUB_IDENT1);
	ident2 = V3D_READ(V3D_HUB_IDENT2);
	ident3 = V3D_READ(V3D_HUB_IDENT3);
	cores = V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_NCORES);

	seq_म_लिखो(m, "Revision:   %d.%d.%d.%d\n",
		   V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_TVER),
		   V3D_GET_FIELD(ident1, V3D_HUB_IDENT1_REV),
		   V3D_GET_FIELD(ident3, V3D_HUB_IDENT3_IPREV),
		   V3D_GET_FIELD(ident3, V3D_HUB_IDENT3_IPIDX));
	seq_म_लिखो(m, "MMU:        %s\n",
		   (ident2 & V3D_HUB_IDENT2_WITH_MMU) ? "yes" : "no");
	seq_म_लिखो(m, "TFU:        %s\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_TFU) ? "yes" : "no");
	seq_म_लिखो(m, "TSY:        %s\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_TSY) ? "yes" : "no");
	seq_म_लिखो(m, "MSO:        %s\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_MSO) ? "yes" : "no");
	seq_म_लिखो(m, "L3C:        %s (%dkb)\n",
		   (ident1 & V3D_HUB_IDENT1_WITH_L3C) ? "yes" : "no",
		   V3D_GET_FIELD(ident2, V3D_HUB_IDENT2_L3C_NKB));

	क्रम (core = 0; core < cores; core++) अणु
		u32 misccfg;
		u32 nslc, nपंचांगu, qups;

		ident0 = V3D_CORE_READ(core, V3D_CTL_IDENT0);
		ident1 = V3D_CORE_READ(core, V3D_CTL_IDENT1);
		ident2 = V3D_CORE_READ(core, V3D_CTL_IDENT2);
		misccfg = V3D_CORE_READ(core, V3D_CTL_MISCCFG);

		nslc = V3D_GET_FIELD(ident1, V3D_IDENT1_NSLC);
		nपंचांगu = V3D_GET_FIELD(ident1, V3D_IDENT1_NTMU);
		qups = V3D_GET_FIELD(ident1, V3D_IDENT1_QUPS);

		seq_म_लिखो(m, "Core %d:\n", core);
		seq_म_लिखो(m, "  Revision:     %d.%d\n",
			   V3D_GET_FIELD(ident0, V3D_IDENT0_VER),
			   V3D_GET_FIELD(ident1, V3D_IDENT1_REV));
		seq_म_लिखो(m, "  Slices:       %d\n", nslc);
		seq_म_लिखो(m, "  TMUs:         %d\n", nslc * nपंचांगu);
		seq_म_लिखो(m, "  QPUs:         %d\n", nslc * qups);
		seq_म_लिखो(m, "  Semaphores:   %d\n",
			   V3D_GET_FIELD(ident1, V3D_IDENT1_NSEM));
		seq_म_लिखो(m, "  BCG int:      %d\n",
			   (ident2 & V3D_IDENT2_BCG_INT) != 0);
		seq_म_लिखो(m, "  Override TMU: %d\n",
			   (misccfg & V3D_MISCCFG_OVRTMUOUT) != 0);
	पूर्ण

	pm_runसमय_mark_last_busy(v3d->drm.dev);
	pm_runसमय_put_स्वतःsuspend(v3d->drm.dev);

	वापस 0;
पूर्ण

अटल पूर्णांक v3d_debugfs_bo_stats(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);

	mutex_lock(&v3d->bo_lock);
	seq_म_लिखो(m, "allocated bos:          %d\n",
		   v3d->bo_stats.num_allocated);
	seq_म_लिखो(m, "allocated bo size (kb): %ld\n",
		   (दीर्घ)v3d->bo_stats.pages_allocated << (PAGE_SHIFT - 10));
	mutex_unlock(&v3d->bo_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक v3d_measure_घड़ी(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा v3d_dev *v3d = to_v3d_dev(dev);
	uपूर्णांक32_t cycles;
	पूर्णांक core = 0;
	पूर्णांक measure_ms = 1000;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(v3d->drm.dev);
	अगर (ret < 0)
		वापस ret;

	अगर (v3d->ver >= 40) अणु
		V3D_CORE_WRITE(core, V3D_V4_PCTR_0_SRC_0_3,
			       V3D_SET_FIELD(V3D_PCTR_CYCLE_COUNT,
					     V3D_PCTR_S0));
		V3D_CORE_WRITE(core, V3D_V4_PCTR_0_CLR, 1);
		V3D_CORE_WRITE(core, V3D_V4_PCTR_0_EN, 1);
	पूर्ण अन्यथा अणु
		V3D_CORE_WRITE(core, V3D_V3_PCTR_0_PCTRS0,
			       V3D_PCTR_CYCLE_COUNT);
		V3D_CORE_WRITE(core, V3D_V3_PCTR_0_CLR, 1);
		V3D_CORE_WRITE(core, V3D_V3_PCTR_0_EN,
			       V3D_V3_PCTR_0_EN_ENABLE |
			       1);
	पूर्ण
	msleep(measure_ms);
	cycles = V3D_CORE_READ(core, V3D_PCTR_0_PCTR0);

	seq_म_लिखो(m, "cycles: %d (%d.%d Mhz)\n",
		   cycles,
		   cycles / (measure_ms * 1000),
		   (cycles / (measure_ms * 100)) % 10);

	pm_runसमय_mark_last_busy(v3d->drm.dev);
	pm_runसमय_put_स्वतःsuspend(v3d->drm.dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list v3d_debugfs_list[] = अणु
	अणु"v3d_ident", v3d_v3d_debugfs_ident, 0पूर्ण,
	अणु"v3d_regs", v3d_v3d_debugfs_regs, 0पूर्ण,
	अणु"measure_clock", v3d_measure_घड़ी, 0पूर्ण,
	अणु"bo_stats", v3d_debugfs_bo_stats, 0पूर्ण,
पूर्ण;

व्योम
v3d_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(v3d_debugfs_list,
				 ARRAY_SIZE(v3d_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
