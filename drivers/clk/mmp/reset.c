<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/reset-controller.h>

#समावेश "reset.h"

#घोषणा rcdev_to_unit(rcdev) container_of(rcdev, काष्ठा mmp_clk_reset_unit, rcdev)

अटल पूर्णांक mmp_of_reset_xlate(काष्ठा reset_controller_dev *rcdev,
			  स्थिर काष्ठा of_phandle_args *reset_spec)
अणु
	काष्ठा mmp_clk_reset_unit *unit = rcdev_to_unit(rcdev);
	काष्ठा mmp_clk_reset_cell *cell;
	पूर्णांक i;

	अगर (WARN_ON(reset_spec->args_count != rcdev->of_reset_n_cells))
		वापस -EINVAL;

	क्रम (i = 0; i < rcdev->nr_resets; i++) अणु
		cell = &unit->cells[i];
		अगर (cell->clk_id == reset_spec->args[0])
			अवरोध;
	पूर्ण

	अगर (i == rcdev->nr_resets)
		वापस -EINVAL;

	वापस i;
पूर्ण

अटल पूर्णांक mmp_clk_reset_निश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा mmp_clk_reset_unit *unit = rcdev_to_unit(rcdev);
	काष्ठा mmp_clk_reset_cell *cell;
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	cell = &unit->cells[id];
	अगर (cell->lock)
		spin_lock_irqsave(cell->lock, flags);

	val = पढ़ोl(cell->reg);
	val |= cell->bits;
	ग_लिखोl(val, cell->reg);

	अगर (cell->lock)
		spin_unlock_irqrestore(cell->lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक mmp_clk_reset_deनिश्चित(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	काष्ठा mmp_clk_reset_unit *unit = rcdev_to_unit(rcdev);
	काष्ठा mmp_clk_reset_cell *cell;
	अचिन्हित दीर्घ flags = 0;
	u32 val;

	cell = &unit->cells[id];
	अगर (cell->lock)
		spin_lock_irqsave(cell->lock, flags);

	val = पढ़ोl(cell->reg);
	val &= ~cell->bits;
	ग_लिखोl(val, cell->reg);

	अगर (cell->lock)
		spin_unlock_irqrestore(cell->lock, flags);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा reset_control_ops mmp_clk_reset_ops = अणु
	.निश्चित		= mmp_clk_reset_निश्चित,
	.deनिश्चित	= mmp_clk_reset_deनिश्चित,
पूर्ण;

व्योम mmp_clk_reset_रेजिस्टर(काष्ठा device_node *np,
			काष्ठा mmp_clk_reset_cell *cells, पूर्णांक nr_resets)
अणु
	काष्ठा mmp_clk_reset_unit *unit;

	unit = kzalloc(माप(*unit), GFP_KERNEL);
	अगर (!unit)
		वापस;

	unit->cells = cells;
	unit->rcdev.of_reset_n_cells = 1;
	unit->rcdev.nr_resets = nr_resets;
	unit->rcdev.ops = &mmp_clk_reset_ops;
	unit->rcdev.of_node = np;
	unit->rcdev.of_xlate = mmp_of_reset_xlate;

	reset_controller_रेजिस्टर(&unit->rcdev);
पूर्ण
