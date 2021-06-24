<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright तऊ 2017 Broadcom
 */

#समावेश <linux/seq_file.h>

#समावेश <drm/drm_debugfs.h>
#समावेश <drm/drm_file.h>

#समावेश "pl111_drm.h"

#घोषणा REGDEF(reg) अणु reg, #reg पूर्ण
अटल स्थिर काष्ठा अणु
	u32 reg;
	स्थिर अक्षर *name;
पूर्ण pl111_reg_defs[] = अणु
	REGDEF(CLCD_TIM0),
	REGDEF(CLCD_TIM1),
	REGDEF(CLCD_TIM2),
	REGDEF(CLCD_TIM3),
	REGDEF(CLCD_UBAS),
	REGDEF(CLCD_LBAS),
	REGDEF(CLCD_PL111_CNTL),
	REGDEF(CLCD_PL111_IENB),
	REGDEF(CLCD_PL111_RIS),
	REGDEF(CLCD_PL111_MIS),
	REGDEF(CLCD_PL111_ICR),
	REGDEF(CLCD_PL111_UCUR),
	REGDEF(CLCD_PL111_LCUR),
पूर्ण;

अटल पूर्णांक pl111_debugfs_regs(काष्ठा seq_file *m, व्योम *unused)
अणु
	काष्ठा drm_info_node *node = (काष्ठा drm_info_node *)m->निजी;
	काष्ठा drm_device *dev = node->minor->dev;
	काष्ठा pl111_drm_dev_निजी *priv = dev->dev_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(pl111_reg_defs); i++) अणु
		seq_म_लिखो(m, "%s (0x%04x): 0x%08x\n",
			   pl111_reg_defs[i].name, pl111_reg_defs[i].reg,
			   पढ़ोl(priv->regs + pl111_reg_defs[i].reg));
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_info_list pl111_debugfs_list[] = अणु
	अणु"regs", pl111_debugfs_regs, 0पूर्ण,
पूर्ण;

व्योम
pl111_debugfs_init(काष्ठा drm_minor *minor)
अणु
	drm_debugfs_create_files(pl111_debugfs_list,
				 ARRAY_SIZE(pl111_debugfs_list),
				 minor->debugfs_root, minor);
पूर्ण
