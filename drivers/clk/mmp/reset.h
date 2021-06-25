<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_MMP_CLK_RESET_H
#घोषणा __MACH_MMP_CLK_RESET_H

#समावेश <linux/reset-controller.h>

#घोषणा MMP_RESET_INVERT	1

काष्ठा mmp_clk_reset_cell अणु
	अचिन्हित पूर्णांक clk_id;
	व्योम __iomem *reg;
	u32 bits;
	अचिन्हित पूर्णांक flags;
	spinlock_t *lock;
पूर्ण;

काष्ठा mmp_clk_reset_unit अणु
	काष्ठा reset_controller_dev rcdev;
	काष्ठा mmp_clk_reset_cell *cells;
पूर्ण;

#अगर_घोषित CONFIG_RESET_CONTROLLER
व्योम mmp_clk_reset_रेजिस्टर(काष्ठा device_node *np,
			काष्ठा mmp_clk_reset_cell *cells, पूर्णांक nr_resets);
#अन्यथा
अटल अंतरभूत व्योम mmp_clk_reset_रेजिस्टर(काष्ठा device_node *np,
			काष्ठा mmp_clk_reset_cell *cells, पूर्णांक nr_resets)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
