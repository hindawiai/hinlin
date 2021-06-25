<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// regmap based irq_chip
//
// Copyright 2011 Wolfson Microelectronics plc
//
// Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>

#समावेश <linux/device.h>
#समावेश <linux/export.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/irqकरोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/regmap.h>
#समावेश <linux/slab.h>

#समावेश "internal.h"

काष्ठा regmap_irq_chip_data अणु
	काष्ठा mutex lock;
	काष्ठा irq_chip irq_chip;

	काष्ठा regmap *map;
	स्थिर काष्ठा regmap_irq_chip *chip;

	पूर्णांक irq_base;
	काष्ठा irq_करोमुख्य *करोमुख्य;

	पूर्णांक irq;
	पूर्णांक wake_count;

	व्योम *status_reg_buf;
	अचिन्हित पूर्णांक *मुख्य_status_buf;
	अचिन्हित पूर्णांक *status_buf;
	अचिन्हित पूर्णांक *mask_buf;
	अचिन्हित पूर्णांक *mask_buf_def;
	अचिन्हित पूर्णांक *wake_buf;
	अचिन्हित पूर्णांक *type_buf;
	अचिन्हित पूर्णांक *type_buf_def;
	अचिन्हित पूर्णांक **virt_buf;

	अचिन्हित पूर्णांक irq_reg_stride;
	अचिन्हित पूर्णांक type_reg_stride;

	bool clear_status:1;
पूर्ण;

अटल पूर्णांक sub_irq_reg(काष्ठा regmap_irq_chip_data *data,
		       अचिन्हित पूर्णांक base_reg, पूर्णांक i)
अणु
	स्थिर काष्ठा regmap_irq_chip *chip = data->chip;
	काष्ठा regmap *map = data->map;
	काष्ठा regmap_irq_sub_irq_map *subreg;
	अचिन्हित पूर्णांक offset;
	पूर्णांक reg = 0;

	अगर (!chip->sub_reg_offsets || !chip->not_fixed_stride) अणु
		/* Assume linear mapping */
		reg = base_reg + (i * map->reg_stride * data->irq_reg_stride);
	पूर्ण अन्यथा अणु
		subreg = &chip->sub_reg_offsets[i];
		offset = subreg->offset[0];
		reg = base_reg + offset;
	पूर्ण

	वापस reg;
पूर्ण

अटल अंतरभूत स्थिर
काष्ठा regmap_irq *irq_to_regmap_irq(काष्ठा regmap_irq_chip_data *data,
				     पूर्णांक irq)
अणु
	वापस &data->chip->irqs[irq];
पूर्ण

अटल व्योम regmap_irq_lock(काष्ठा irq_data *data)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);

	mutex_lock(&d->lock);
पूर्ण

अटल पूर्णांक regmap_irq_update_bits(काष्ठा regmap_irq_chip_data *d,
				  अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक mask,
				  अचिन्हित पूर्णांक val)
अणु
	अगर (d->chip->mask_ग_लिखोonly)
		वापस regmap_ग_लिखो_bits(d->map, reg, mask, val);
	अन्यथा
		वापस regmap_update_bits(d->map, reg, mask, val);
पूर्ण

अटल व्योम regmap_irq_sync_unlock(काष्ठा irq_data *data)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	काष्ठा regmap *map = d->map;
	पूर्णांक i, j, ret;
	u32 reg;
	u32 unmask_offset;
	u32 val;

	अगर (d->chip->runसमय_pm) अणु
		ret = pm_runसमय_get_sync(map->dev);
		अगर (ret < 0)
			dev_err(map->dev, "IRQ sync failed to resume: %d\n",
				ret);
	पूर्ण

	अगर (d->clear_status) अणु
		क्रम (i = 0; i < d->chip->num_regs; i++) अणु
			reg = sub_irq_reg(d, d->chip->status_base, i);

			ret = regmap_पढ़ो(map, reg, &val);
			अगर (ret)
				dev_err(d->map->dev,
					"Failed to clear the interrupt status bits\n");
		पूर्ण

		d->clear_status = false;
	पूर्ण

	/*
	 * If there's been a change in the mask ग_लिखो it back to the
	 * hardware.  We rely on the use of the regmap core cache to
	 * suppress poपूर्णांकless ग_लिखोs.
	 */
	क्रम (i = 0; i < d->chip->num_regs; i++) अणु
		अगर (!d->chip->mask_base)
			जारी;

		reg = sub_irq_reg(d, d->chip->mask_base, i);
		अगर (d->chip->mask_invert) अणु
			ret = regmap_irq_update_bits(d, reg,
					 d->mask_buf_def[i], ~d->mask_buf[i]);
		पूर्ण अन्यथा अगर (d->chip->unmask_base) अणु
			/* set mask with mask_base रेजिस्टर */
			ret = regmap_irq_update_bits(d, reg,
					d->mask_buf_def[i], ~d->mask_buf[i]);
			अगर (ret < 0)
				dev_err(d->map->dev,
					"Failed to sync unmasks in %x\n",
					reg);
			unmask_offset = d->chip->unmask_base -
							d->chip->mask_base;
			/* clear mask with unmask_base रेजिस्टर */
			ret = regmap_irq_update_bits(d,
					reg + unmask_offset,
					d->mask_buf_def[i],
					d->mask_buf[i]);
		पूर्ण अन्यथा अणु
			ret = regmap_irq_update_bits(d, reg,
					 d->mask_buf_def[i], d->mask_buf[i]);
		पूर्ण
		अगर (ret != 0)
			dev_err(d->map->dev, "Failed to sync masks in %x\n",
				reg);

		reg = sub_irq_reg(d, d->chip->wake_base, i);
		अगर (d->wake_buf) अणु
			अगर (d->chip->wake_invert)
				ret = regmap_irq_update_bits(d, reg,
							 d->mask_buf_def[i],
							 ~d->wake_buf[i]);
			अन्यथा
				ret = regmap_irq_update_bits(d, reg,
							 d->mask_buf_def[i],
							 d->wake_buf[i]);
			अगर (ret != 0)
				dev_err(d->map->dev,
					"Failed to sync wakes in %x: %d\n",
					reg, ret);
		पूर्ण

		अगर (!d->chip->init_ack_masked)
			जारी;
		/*
		 * Ack all the masked पूर्णांकerrupts unconditionally,
		 * OR अगर there is masked पूर्णांकerrupt which hasn't been Acked,
		 * it'll be ignored in irq handler, then may पूर्णांकroduce irq storm
		 */
		अगर (d->mask_buf[i] && (d->chip->ack_base || d->chip->use_ack)) अणु
			reg = sub_irq_reg(d, d->chip->ack_base, i);

			/* some chips ack by ग_लिखो 0 */
			अगर (d->chip->ack_invert)
				ret = regmap_ग_लिखो(map, reg, ~d->mask_buf[i]);
			अन्यथा
				ret = regmap_ग_लिखो(map, reg, d->mask_buf[i]);
			अगर (d->chip->clear_ack) अणु
				अगर (d->chip->ack_invert && !ret)
					ret = regmap_ग_लिखो(map, reg,
							   d->mask_buf[i]);
				अन्यथा अगर (!ret)
					ret = regmap_ग_लिखो(map, reg,
							   ~d->mask_buf[i]);
			पूर्ण
			अगर (ret != 0)
				dev_err(d->map->dev, "Failed to ack 0x%x: %d\n",
					reg, ret);
		पूर्ण
	पूर्ण

	/* Don't update the type bits if we're using mask bits क्रम irq type. */
	अगर (!d->chip->type_in_mask) अणु
		क्रम (i = 0; i < d->chip->num_type_reg; i++) अणु
			अगर (!d->type_buf_def[i])
				जारी;
			reg = sub_irq_reg(d, d->chip->type_base, i);
			अगर (d->chip->type_invert)
				ret = regmap_irq_update_bits(d, reg,
					d->type_buf_def[i], ~d->type_buf[i]);
			अन्यथा
				ret = regmap_irq_update_bits(d, reg,
					d->type_buf_def[i], d->type_buf[i]);
			अगर (ret != 0)
				dev_err(d->map->dev, "Failed to sync type in %x\n",
					reg);
		पूर्ण
	पूर्ण

	अगर (d->chip->num_virt_regs) अणु
		क्रम (i = 0; i < d->chip->num_virt_regs; i++) अणु
			क्रम (j = 0; j < d->chip->num_regs; j++) अणु
				reg = sub_irq_reg(d, d->chip->virt_reg_base[i],
						  j);
				ret = regmap_ग_लिखो(map, reg, d->virt_buf[i][j]);
				अगर (ret != 0)
					dev_err(d->map->dev,
						"Failed to write virt 0x%x: %d\n",
						reg, ret);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (d->chip->runसमय_pm)
		pm_runसमय_put(map->dev);

	/* If we've changed our wakeup count propagate it to the parent */
	अगर (d->wake_count < 0)
		क्रम (i = d->wake_count; i < 0; i++)
			irq_set_irq_wake(d->irq, 0);
	अन्यथा अगर (d->wake_count > 0)
		क्रम (i = 0; i < d->wake_count; i++)
			irq_set_irq_wake(d->irq, 1);

	d->wake_count = 0;

	mutex_unlock(&d->lock);
पूर्ण

अटल व्योम regmap_irq_enable(काष्ठा irq_data *data)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	काष्ठा regmap *map = d->map;
	स्थिर काष्ठा regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);
	अचिन्हित पूर्णांक mask, type;

	type = irq_data->type.type_falling_val | irq_data->type.type_rising_val;

	/*
	 * The type_in_mask flag means that the underlying hardware uses
	 * separate mask bits क्रम rising and falling edge पूर्णांकerrupts, but
	 * we want to make them पूर्णांकo a single भव पूर्णांकerrupt with
	 * configurable edge.
	 *
	 * If the पूर्णांकerrupt we're enabling defines the falling or rising
	 * masks then instead of using the regular mask bits क्रम this
	 * पूर्णांकerrupt, use the value previously written to the type buffer
	 * at the corresponding offset in regmap_irq_set_type().
	 */
	अगर (d->chip->type_in_mask && type)
		mask = d->type_buf[irq_data->reg_offset / map->reg_stride];
	अन्यथा
		mask = irq_data->mask;

	अगर (d->chip->clear_on_unmask)
		d->clear_status = true;

	d->mask_buf[irq_data->reg_offset / map->reg_stride] &= ~mask;
पूर्ण

अटल व्योम regmap_irq_disable(काष्ठा irq_data *data)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	काष्ठा regmap *map = d->map;
	स्थिर काष्ठा regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);

	d->mask_buf[irq_data->reg_offset / map->reg_stride] |= irq_data->mask;
पूर्ण

अटल पूर्णांक regmap_irq_set_type(काष्ठा irq_data *data, अचिन्हित पूर्णांक type)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	काष्ठा regmap *map = d->map;
	स्थिर काष्ठा regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);
	पूर्णांक reg;
	स्थिर काष्ठा regmap_irq_type *t = &irq_data->type;

	अगर ((t->types_supported & type) != type)
		वापस 0;

	reg = t->type_reg_offset / map->reg_stride;

	अगर (t->type_reg_mask)
		d->type_buf[reg] &= ~t->type_reg_mask;
	अन्यथा
		d->type_buf[reg] &= ~(t->type_falling_val |
				      t->type_rising_val |
				      t->type_level_low_val |
				      t->type_level_high_val);
	चयन (type) अणु
	हाल IRQ_TYPE_EDGE_FALLING:
		d->type_buf[reg] |= t->type_falling_val;
		अवरोध;

	हाल IRQ_TYPE_EDGE_RISING:
		d->type_buf[reg] |= t->type_rising_val;
		अवरोध;

	हाल IRQ_TYPE_EDGE_BOTH:
		d->type_buf[reg] |= (t->type_falling_val |
					t->type_rising_val);
		अवरोध;

	हाल IRQ_TYPE_LEVEL_HIGH:
		d->type_buf[reg] |= t->type_level_high_val;
		अवरोध;

	हाल IRQ_TYPE_LEVEL_LOW:
		d->type_buf[reg] |= t->type_level_low_val;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (d->chip->set_type_virt)
		वापस d->chip->set_type_virt(d->virt_buf, type, data->hwirq,
					      reg);

	वापस 0;
पूर्ण

अटल पूर्णांक regmap_irq_set_wake(काष्ठा irq_data *data, अचिन्हित पूर्णांक on)
अणु
	काष्ठा regmap_irq_chip_data *d = irq_data_get_irq_chip_data(data);
	काष्ठा regmap *map = d->map;
	स्थिर काष्ठा regmap_irq *irq_data = irq_to_regmap_irq(d, data->hwirq);

	अगर (on) अणु
		अगर (d->wake_buf)
			d->wake_buf[irq_data->reg_offset / map->reg_stride]
				&= ~irq_data->mask;
		d->wake_count++;
	पूर्ण अन्यथा अणु
		अगर (d->wake_buf)
			d->wake_buf[irq_data->reg_offset / map->reg_stride]
				|= irq_data->mask;
		d->wake_count--;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_chip regmap_irq_chip = अणु
	.irq_bus_lock		= regmap_irq_lock,
	.irq_bus_sync_unlock	= regmap_irq_sync_unlock,
	.irq_disable		= regmap_irq_disable,
	.irq_enable		= regmap_irq_enable,
	.irq_set_type		= regmap_irq_set_type,
	.irq_set_wake		= regmap_irq_set_wake,
पूर्ण;

अटल अंतरभूत पूर्णांक पढ़ो_sub_irq_data(काष्ठा regmap_irq_chip_data *data,
					   अचिन्हित पूर्णांक b)
अणु
	स्थिर काष्ठा regmap_irq_chip *chip = data->chip;
	काष्ठा regmap *map = data->map;
	काष्ठा regmap_irq_sub_irq_map *subreg;
	पूर्णांक i, ret = 0;

	अगर (!chip->sub_reg_offsets) अणु
		/* Assume linear mapping */
		ret = regmap_पढ़ो(map, chip->status_base +
				  (b * map->reg_stride * data->irq_reg_stride),
				   &data->status_buf[b]);
	पूर्ण अन्यथा अणु
		subreg = &chip->sub_reg_offsets[b];
		क्रम (i = 0; i < subreg->num_regs; i++) अणु
			अचिन्हित पूर्णांक offset = subreg->offset[i];

			अगर (chip->not_fixed_stride)
				ret = regmap_पढ़ो(map,
						chip->status_base + offset,
						&data->status_buf[b]);
			अन्यथा
				ret = regmap_पढ़ो(map,
						chip->status_base + offset,
						&data->status_buf[offset]);

			अगर (ret)
				अवरोध;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल irqवापस_t regmap_irq_thपढ़ो(पूर्णांक irq, व्योम *d)
अणु
	काष्ठा regmap_irq_chip_data *data = d;
	स्थिर काष्ठा regmap_irq_chip *chip = data->chip;
	काष्ठा regmap *map = data->map;
	पूर्णांक ret, i;
	bool handled = false;
	u32 reg;

	अगर (chip->handle_pre_irq)
		chip->handle_pre_irq(chip->irq_drv_data);

	अगर (chip->runसमय_pm) अणु
		ret = pm_runसमय_get_sync(map->dev);
		अगर (ret < 0) अणु
			dev_err(map->dev, "IRQ thread failed to resume: %d\n",
				ret);
			जाओ निकास;
		पूर्ण
	पूर्ण

	/*
	 * Read only रेजिस्टरs with active IRQs अगर the chip has 'मुख्य status
	 * रेजिस्टर'. Else पढ़ो in the statuses, using a single bulk पढ़ो अगर
	 * possible in order to reduce the I/O overheads.
	 */

	अगर (chip->num_मुख्य_regs) अणु
		अचिन्हित पूर्णांक max_मुख्य_bits;
		अचिन्हित दीर्घ size;

		size = chip->num_regs * माप(अचिन्हित पूर्णांक);

		max_मुख्य_bits = (chip->num_मुख्य_status_bits) ?
				 chip->num_मुख्य_status_bits : chip->num_regs;
		/* Clear the status buf as we करोn't पढ़ो all status regs */
		स_रखो(data->status_buf, 0, size);

		/* We could support bulk पढ़ो क्रम मुख्य status रेजिस्टरs
		 * but I करोn't expect to see devices with really many मुख्य
		 * status रेजिस्टरs so let's only support single पढ़ोs क्रम the
		 * sake of simplicity. and add bulk पढ़ोs only अगर needed
		 */
		क्रम (i = 0; i < chip->num_मुख्य_regs; i++) अणु
			ret = regmap_पढ़ो(map, chip->मुख्य_status +
				  (i * map->reg_stride
				   * data->irq_reg_stride),
				  &data->मुख्य_status_buf[i]);
			अगर (ret) अणु
				dev_err(map->dev,
					"Failed to read IRQ status %d\n",
					ret);
				जाओ निकास;
			पूर्ण
		पूर्ण

		/* Read sub रेजिस्टरs with active IRQs */
		क्रम (i = 0; i < chip->num_मुख्य_regs; i++) अणु
			अचिन्हित पूर्णांक b;
			स्थिर अचिन्हित दीर्घ mreg = data->मुख्य_status_buf[i];

			क्रम_each_set_bit(b, &mreg, map->क्रमmat.val_bytes * 8) अणु
				अगर (i * map->क्रमmat.val_bytes * 8 + b >
				    max_मुख्य_bits)
					अवरोध;
				ret = पढ़ो_sub_irq_data(data, b);

				अगर (ret != 0) अणु
					dev_err(map->dev,
						"Failed to read IRQ status %d\n",
						ret);
					जाओ निकास;
				पूर्ण
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अगर (!map->use_single_पढ़ो && map->reg_stride == 1 &&
		   data->irq_reg_stride == 1) अणु

		u8 *buf8 = data->status_reg_buf;
		u16 *buf16 = data->status_reg_buf;
		u32 *buf32 = data->status_reg_buf;

		BUG_ON(!data->status_reg_buf);

		ret = regmap_bulk_पढ़ो(map, chip->status_base,
				       data->status_reg_buf,
				       chip->num_regs);
		अगर (ret != 0) अणु
			dev_err(map->dev, "Failed to read IRQ status: %d\n",
				ret);
			जाओ निकास;
		पूर्ण

		क्रम (i = 0; i < data->chip->num_regs; i++) अणु
			चयन (map->क्रमmat.val_bytes) अणु
			हाल 1:
				data->status_buf[i] = buf8[i];
				अवरोध;
			हाल 2:
				data->status_buf[i] = buf16[i];
				अवरोध;
			हाल 4:
				data->status_buf[i] = buf32[i];
				अवरोध;
			शेष:
				BUG();
				जाओ निकास;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < data->chip->num_regs; i++) अणु
			अचिन्हित पूर्णांक reg = sub_irq_reg(data,
					data->chip->status_base, i);
			ret = regmap_पढ़ो(map, reg, &data->status_buf[i]);

			अगर (ret != 0) अणु
				dev_err(map->dev,
					"Failed to read IRQ status: %d\n",
					ret);
				जाओ निकास;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Ignore masked IRQs and ack अगर we need to; we ack early so
	 * there is no race between handling and acknowleding the
	 * पूर्णांकerrupt.  We assume that typically few of the पूर्णांकerrupts
	 * will fire simultaneously so करोn't worry about overhead from
	 * करोing a ग_लिखो per रेजिस्टर.
	 */
	क्रम (i = 0; i < data->chip->num_regs; i++) अणु
		data->status_buf[i] &= ~data->mask_buf[i];

		अगर (data->status_buf[i] && (chip->ack_base || chip->use_ack)) अणु
			reg = sub_irq_reg(data, data->chip->ack_base, i);

			अगर (chip->ack_invert)
				ret = regmap_ग_लिखो(map, reg,
						~data->status_buf[i]);
			अन्यथा
				ret = regmap_ग_लिखो(map, reg,
						data->status_buf[i]);
			अगर (chip->clear_ack) अणु
				अगर (chip->ack_invert && !ret)
					ret = regmap_ग_लिखो(map, reg,
							data->status_buf[i]);
				अन्यथा अगर (!ret)
					ret = regmap_ग_लिखो(map, reg,
							~data->status_buf[i]);
			पूर्ण
			अगर (ret != 0)
				dev_err(map->dev, "Failed to ack 0x%x: %d\n",
					reg, ret);
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < chip->num_irqs; i++) अणु
		अगर (data->status_buf[chip->irqs[i].reg_offset /
				     map->reg_stride] & chip->irqs[i].mask) अणु
			handle_nested_irq(irq_find_mapping(data->करोमुख्य, i));
			handled = true;
		पूर्ण
	पूर्ण

निकास:
	अगर (chip->runसमय_pm)
		pm_runसमय_put(map->dev);

	अगर (chip->handle_post_irq)
		chip->handle_post_irq(chip->irq_drv_data);

	अगर (handled)
		वापस IRQ_HANDLED;
	अन्यथा
		वापस IRQ_NONE;
पूर्ण

अटल पूर्णांक regmap_irq_map(काष्ठा irq_करोमुख्य *h, अचिन्हित पूर्णांक virq,
			  irq_hw_number_t hw)
अणु
	काष्ठा regmap_irq_chip_data *data = h->host_data;

	irq_set_chip_data(virq, data);
	irq_set_chip(virq, &data->irq_chip);
	irq_set_nested_thपढ़ो(virq, 1);
	irq_set_parent(virq, data->irq);
	irq_set_noprobe(virq);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा irq_करोमुख्य_ops regmap_करोमुख्य_ops = अणु
	.map	= regmap_irq_map,
	.xlate	= irq_करोमुख्य_xlate_onetwocell,
पूर्ण;

/**
 * regmap_add_irq_chip_fwnode() - Use standard regmap IRQ controller handling
 *
 * @fwnode: The firmware node where the IRQ करोमुख्य should be added to.
 * @map: The regmap क्रम the device.
 * @irq: The IRQ the device uses to संकेत पूर्णांकerrupts.
 * @irq_flags: The IRQF_ flags to use क्रम the primary पूर्णांकerrupt.
 * @irq_base: Allocate at specअगरic IRQ number अगर irq_base > 0.
 * @chip: Configuration क्रम the पूर्णांकerrupt controller.
 * @data: Runसमय data काष्ठाure क्रम the controller, allocated on success.
 *
 * Returns 0 on success or an त्रुटि_सं on failure.
 *
 * In order क्रम this to be efficient the chip really should use a
 * रेजिस्टर cache.  The chip driver is responsible क्रम restoring the
 * रेजिस्टर values used by the IRQ controller over suspend and resume.
 */
पूर्णांक regmap_add_irq_chip_fwnode(काष्ठा fwnode_handle *fwnode,
			       काष्ठा regmap *map, पूर्णांक irq,
			       पूर्णांक irq_flags, पूर्णांक irq_base,
			       स्थिर काष्ठा regmap_irq_chip *chip,
			       काष्ठा regmap_irq_chip_data **data)
अणु
	काष्ठा regmap_irq_chip_data *d;
	पूर्णांक i;
	पूर्णांक ret = -ENOMEM;
	पूर्णांक num_type_reg;
	u32 reg;
	u32 unmask_offset;

	अगर (chip->num_regs <= 0)
		वापस -EINVAL;

	अगर (chip->clear_on_unmask && (chip->ack_base || chip->use_ack))
		वापस -EINVAL;

	क्रम (i = 0; i < chip->num_irqs; i++) अणु
		अगर (chip->irqs[i].reg_offset % map->reg_stride)
			वापस -EINVAL;
		अगर (chip->irqs[i].reg_offset / map->reg_stride >=
		    chip->num_regs)
			वापस -EINVAL;
	पूर्ण

	अगर (chip->not_fixed_stride) अणु
		क्रम (i = 0; i < chip->num_regs; i++)
			अगर (chip->sub_reg_offsets[i].num_regs != 1)
				वापस -EINVAL;
	पूर्ण

	अगर (irq_base) अणु
		irq_base = irq_alloc_descs(irq_base, 0, chip->num_irqs, 0);
		अगर (irq_base < 0) अणु
			dev_warn(map->dev, "Failed to allocate IRQs: %d\n",
				 irq_base);
			वापस irq_base;
		पूर्ण
	पूर्ण

	d = kzalloc(माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	अगर (chip->num_मुख्य_regs) अणु
		d->मुख्य_status_buf = kसुस्मृति(chip->num_मुख्य_regs,
					     माप(अचिन्हित पूर्णांक),
					     GFP_KERNEL);

		अगर (!d->मुख्य_status_buf)
			जाओ err_alloc;
	पूर्ण

	d->status_buf = kसुस्मृति(chip->num_regs, माप(अचिन्हित पूर्णांक),
				GFP_KERNEL);
	अगर (!d->status_buf)
		जाओ err_alloc;

	d->mask_buf = kसुस्मृति(chip->num_regs, माप(अचिन्हित पूर्णांक),
			      GFP_KERNEL);
	अगर (!d->mask_buf)
		जाओ err_alloc;

	d->mask_buf_def = kसुस्मृति(chip->num_regs, माप(अचिन्हित पूर्णांक),
				  GFP_KERNEL);
	अगर (!d->mask_buf_def)
		जाओ err_alloc;

	अगर (chip->wake_base) अणु
		d->wake_buf = kसुस्मृति(chip->num_regs, माप(अचिन्हित पूर्णांक),
				      GFP_KERNEL);
		अगर (!d->wake_buf)
			जाओ err_alloc;
	पूर्ण

	num_type_reg = chip->type_in_mask ? chip->num_regs : chip->num_type_reg;
	अगर (num_type_reg) अणु
		d->type_buf_def = kसुस्मृति(num_type_reg,
					  माप(अचिन्हित पूर्णांक), GFP_KERNEL);
		अगर (!d->type_buf_def)
			जाओ err_alloc;

		d->type_buf = kसुस्मृति(num_type_reg, माप(अचिन्हित पूर्णांक),
				      GFP_KERNEL);
		अगर (!d->type_buf)
			जाओ err_alloc;
	पूर्ण

	अगर (chip->num_virt_regs) अणु
		/*
		 * Create virt_buf[chip->num_extra_config_regs][chip->num_regs]
		 */
		d->virt_buf = kसुस्मृति(chip->num_virt_regs, माप(*d->virt_buf),
				      GFP_KERNEL);
		अगर (!d->virt_buf)
			जाओ err_alloc;

		क्रम (i = 0; i < chip->num_virt_regs; i++) अणु
			d->virt_buf[i] = kसुस्मृति(chip->num_regs,
						 माप(अचिन्हित पूर्णांक),
						 GFP_KERNEL);
			अगर (!d->virt_buf[i])
				जाओ err_alloc;
		पूर्ण
	पूर्ण

	d->irq_chip = regmap_irq_chip;
	d->irq_chip.name = chip->name;
	d->irq = irq;
	d->map = map;
	d->chip = chip;
	d->irq_base = irq_base;

	अगर (chip->irq_reg_stride)
		d->irq_reg_stride = chip->irq_reg_stride;
	अन्यथा
		d->irq_reg_stride = 1;

	अगर (chip->type_reg_stride)
		d->type_reg_stride = chip->type_reg_stride;
	अन्यथा
		d->type_reg_stride = 1;

	अगर (!map->use_single_पढ़ो && map->reg_stride == 1 &&
	    d->irq_reg_stride == 1) अणु
		d->status_reg_buf = kदो_स्मृति_array(chip->num_regs,
						  map->क्रमmat.val_bytes,
						  GFP_KERNEL);
		अगर (!d->status_reg_buf)
			जाओ err_alloc;
	पूर्ण

	mutex_init(&d->lock);

	क्रम (i = 0; i < chip->num_irqs; i++)
		d->mask_buf_def[chip->irqs[i].reg_offset / map->reg_stride]
			|= chip->irqs[i].mask;

	/* Mask all the पूर्णांकerrupts by शेष */
	क्रम (i = 0; i < chip->num_regs; i++) अणु
		d->mask_buf[i] = d->mask_buf_def[i];
		अगर (!chip->mask_base)
			जारी;

		reg = sub_irq_reg(d, d->chip->mask_base, i);

		अगर (chip->mask_invert)
			ret = regmap_irq_update_bits(d, reg,
					 d->mask_buf[i], ~d->mask_buf[i]);
		अन्यथा अगर (d->chip->unmask_base) अणु
			unmask_offset = d->chip->unmask_base -
					d->chip->mask_base;
			ret = regmap_irq_update_bits(d,
					reg + unmask_offset,
					d->mask_buf[i],
					d->mask_buf[i]);
		पूर्ण अन्यथा
			ret = regmap_irq_update_bits(d, reg,
					 d->mask_buf[i], d->mask_buf[i]);
		अगर (ret != 0) अणु
			dev_err(map->dev, "Failed to set masks in 0x%x: %d\n",
				reg, ret);
			जाओ err_alloc;
		पूर्ण

		अगर (!chip->init_ack_masked)
			जारी;

		/* Ack masked but set पूर्णांकerrupts */
		reg = sub_irq_reg(d, d->chip->status_base, i);
		ret = regmap_पढ़ो(map, reg, &d->status_buf[i]);
		अगर (ret != 0) अणु
			dev_err(map->dev, "Failed to read IRQ status: %d\n",
				ret);
			जाओ err_alloc;
		पूर्ण

		अगर (d->status_buf[i] && (chip->ack_base || chip->use_ack)) अणु
			reg = sub_irq_reg(d, d->chip->ack_base, i);
			अगर (chip->ack_invert)
				ret = regmap_ग_लिखो(map, reg,
					~(d->status_buf[i] & d->mask_buf[i]));
			अन्यथा
				ret = regmap_ग_लिखो(map, reg,
					d->status_buf[i] & d->mask_buf[i]);
			अगर (chip->clear_ack) अणु
				अगर (chip->ack_invert && !ret)
					ret = regmap_ग_लिखो(map, reg,
						(d->status_buf[i] &
						 d->mask_buf[i]));
				अन्यथा अगर (!ret)
					ret = regmap_ग_लिखो(map, reg,
						~(d->status_buf[i] &
						  d->mask_buf[i]));
			पूर्ण
			अगर (ret != 0) अणु
				dev_err(map->dev, "Failed to ack 0x%x: %d\n",
					reg, ret);
				जाओ err_alloc;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Wake is disabled by शेष */
	अगर (d->wake_buf) अणु
		क्रम (i = 0; i < chip->num_regs; i++) अणु
			d->wake_buf[i] = d->mask_buf_def[i];
			reg = sub_irq_reg(d, d->chip->wake_base, i);

			अगर (chip->wake_invert)
				ret = regmap_irq_update_bits(d, reg,
							 d->mask_buf_def[i],
							 0);
			अन्यथा
				ret = regmap_irq_update_bits(d, reg,
							 d->mask_buf_def[i],
							 d->wake_buf[i]);
			अगर (ret != 0) अणु
				dev_err(map->dev, "Failed to set masks in 0x%x: %d\n",
					reg, ret);
				जाओ err_alloc;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (chip->num_type_reg && !chip->type_in_mask) अणु
		क्रम (i = 0; i < chip->num_type_reg; ++i) अणु
			reg = sub_irq_reg(d, d->chip->type_base, i);

			ret = regmap_पढ़ो(map, reg, &d->type_buf_def[i]);

			अगर (d->chip->type_invert)
				d->type_buf_def[i] = ~d->type_buf_def[i];

			अगर (ret) अणु
				dev_err(map->dev, "Failed to get type defaults at 0x%x: %d\n",
					reg, ret);
				जाओ err_alloc;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (irq_base)
		d->करोमुख्य = irq_करोमुख्य_create_legacy(fwnode, chip->num_irqs,
						     irq_base, 0,
						     &regmap_करोमुख्य_ops, d);
	अन्यथा
		d->करोमुख्य = irq_करोमुख्य_create_linear(fwnode, chip->num_irqs,
						     &regmap_करोमुख्य_ops, d);
	अगर (!d->करोमुख्य) अणु
		dev_err(map->dev, "Failed to create IRQ domain\n");
		ret = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	ret = request_thपढ़ोed_irq(irq, शून्य, regmap_irq_thपढ़ो,
				   irq_flags | IRQF_ONESHOT,
				   chip->name, d);
	अगर (ret != 0) अणु
		dev_err(map->dev, "Failed to request IRQ %d for %s: %d\n",
			irq, chip->name, ret);
		जाओ err_करोमुख्य;
	पूर्ण

	*data = d;

	वापस 0;

err_करोमुख्य:
	/* Should really dispose of the करोमुख्य but... */
err_alloc:
	kमुक्त(d->type_buf);
	kमुक्त(d->type_buf_def);
	kमुक्त(d->wake_buf);
	kमुक्त(d->mask_buf_def);
	kमुक्त(d->mask_buf);
	kमुक्त(d->status_buf);
	kमुक्त(d->status_reg_buf);
	अगर (d->virt_buf) अणु
		क्रम (i = 0; i < chip->num_virt_regs; i++)
			kमुक्त(d->virt_buf[i]);
		kमुक्त(d->virt_buf);
	पूर्ण
	kमुक्त(d);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_add_irq_chip_fwnode);

/**
 * regmap_add_irq_chip() - Use standard regmap IRQ controller handling
 *
 * @map: The regmap क्रम the device.
 * @irq: The IRQ the device uses to संकेत पूर्णांकerrupts.
 * @irq_flags: The IRQF_ flags to use क्रम the primary पूर्णांकerrupt.
 * @irq_base: Allocate at specअगरic IRQ number अगर irq_base > 0.
 * @chip: Configuration क्रम the पूर्णांकerrupt controller.
 * @data: Runसमय data काष्ठाure क्रम the controller, allocated on success.
 *
 * Returns 0 on success or an त्रुटि_सं on failure.
 *
 * This is the same as regmap_add_irq_chip_fwnode, except that the firmware
 * node of the regmap is used.
 */
पूर्णांक regmap_add_irq_chip(काष्ठा regmap *map, पूर्णांक irq, पूर्णांक irq_flags,
			पूर्णांक irq_base, स्थिर काष्ठा regmap_irq_chip *chip,
			काष्ठा regmap_irq_chip_data **data)
अणु
	वापस regmap_add_irq_chip_fwnode(dev_fwnode(map->dev), map, irq,
					  irq_flags, irq_base, chip, data);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_add_irq_chip);

/**
 * regmap_del_irq_chip() - Stop पूर्णांकerrupt handling क्रम a regmap IRQ chip
 *
 * @irq: Primary IRQ क्रम the device
 * @d: &regmap_irq_chip_data allocated by regmap_add_irq_chip()
 *
 * This function also disposes of all mapped IRQs on the chip.
 */
व्योम regmap_del_irq_chip(पूर्णांक irq, काष्ठा regmap_irq_chip_data *d)
अणु
	अचिन्हित पूर्णांक virq;
	पूर्णांक hwirq;

	अगर (!d)
		वापस;

	मुक्त_irq(irq, d);

	/* Dispose all भव irq from irq करोमुख्य beक्रमe removing it */
	क्रम (hwirq = 0; hwirq < d->chip->num_irqs; hwirq++) अणु
		/* Ignore hwirq अगर holes in the IRQ list */
		अगर (!d->chip->irqs[hwirq].mask)
			जारी;

		/*
		 * Find the भव irq of hwirq on chip and अगर it is
		 * there then dispose it
		 */
		virq = irq_find_mapping(d->करोमुख्य, hwirq);
		अगर (virq)
			irq_dispose_mapping(virq);
	पूर्ण

	irq_करोमुख्य_हटाओ(d->करोमुख्य);
	kमुक्त(d->type_buf);
	kमुक्त(d->type_buf_def);
	kमुक्त(d->wake_buf);
	kमुक्त(d->mask_buf_def);
	kमुक्त(d->mask_buf);
	kमुक्त(d->status_reg_buf);
	kमुक्त(d->status_buf);
	kमुक्त(d);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_del_irq_chip);

अटल व्योम devm_regmap_irq_chip_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा regmap_irq_chip_data *d = *(काष्ठा regmap_irq_chip_data **)res;

	regmap_del_irq_chip(d->irq, d);
पूर्ण

अटल पूर्णांक devm_regmap_irq_chip_match(काष्ठा device *dev, व्योम *res, व्योम *data)

अणु
	काष्ठा regmap_irq_chip_data **r = res;

	अगर (!r || !*r) अणु
		WARN_ON(!r || !*r);
		वापस 0;
	पूर्ण
	वापस *r == data;
पूर्ण

/**
 * devm_regmap_add_irq_chip_fwnode() - Resource managed regmap_add_irq_chip_fwnode()
 *
 * @dev: The device poपूर्णांकer on which irq_chip beदीर्घs to.
 * @fwnode: The firmware node where the IRQ करोमुख्य should be added to.
 * @map: The regmap क्रम the device.
 * @irq: The IRQ the device uses to संकेत पूर्णांकerrupts
 * @irq_flags: The IRQF_ flags to use क्रम the primary पूर्णांकerrupt.
 * @irq_base: Allocate at specअगरic IRQ number अगर irq_base > 0.
 * @chip: Configuration क्रम the पूर्णांकerrupt controller.
 * @data: Runसमय data काष्ठाure क्रम the controller, allocated on success
 *
 * Returns 0 on success or an त्रुटि_सं on failure.
 *
 * The &regmap_irq_chip_data will be स्वतःmatically released when the device is
 * unbound.
 */
पूर्णांक devm_regmap_add_irq_chip_fwnode(काष्ठा device *dev,
				    काष्ठा fwnode_handle *fwnode,
				    काष्ठा regmap *map, पूर्णांक irq,
				    पूर्णांक irq_flags, पूर्णांक irq_base,
				    स्थिर काष्ठा regmap_irq_chip *chip,
				    काष्ठा regmap_irq_chip_data **data)
अणु
	काष्ठा regmap_irq_chip_data **ptr, *d;
	पूर्णांक ret;

	ptr = devres_alloc(devm_regmap_irq_chip_release, माप(*ptr),
			   GFP_KERNEL);
	अगर (!ptr)
		वापस -ENOMEM;

	ret = regmap_add_irq_chip_fwnode(fwnode, map, irq, irq_flags, irq_base,
					 chip, &d);
	अगर (ret < 0) अणु
		devres_मुक्त(ptr);
		वापस ret;
	पूर्ण

	*ptr = d;
	devres_add(dev, ptr);
	*data = d;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_add_irq_chip_fwnode);

/**
 * devm_regmap_add_irq_chip() - Resource manager regmap_add_irq_chip()
 *
 * @dev: The device poपूर्णांकer on which irq_chip beदीर्घs to.
 * @map: The regmap क्रम the device.
 * @irq: The IRQ the device uses to संकेत पूर्णांकerrupts
 * @irq_flags: The IRQF_ flags to use क्रम the primary पूर्णांकerrupt.
 * @irq_base: Allocate at specअगरic IRQ number अगर irq_base > 0.
 * @chip: Configuration क्रम the पूर्णांकerrupt controller.
 * @data: Runसमय data काष्ठाure क्रम the controller, allocated on success
 *
 * Returns 0 on success or an त्रुटि_सं on failure.
 *
 * The &regmap_irq_chip_data will be स्वतःmatically released when the device is
 * unbound.
 */
पूर्णांक devm_regmap_add_irq_chip(काष्ठा device *dev, काष्ठा regmap *map, पूर्णांक irq,
			     पूर्णांक irq_flags, पूर्णांक irq_base,
			     स्थिर काष्ठा regmap_irq_chip *chip,
			     काष्ठा regmap_irq_chip_data **data)
अणु
	वापस devm_regmap_add_irq_chip_fwnode(dev, dev_fwnode(map->dev), map,
					       irq, irq_flags, irq_base, chip,
					       data);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_add_irq_chip);

/**
 * devm_regmap_del_irq_chip() - Resource managed regmap_del_irq_chip()
 *
 * @dev: Device क्रम which which resource was allocated.
 * @irq: Primary IRQ क्रम the device.
 * @data: &regmap_irq_chip_data allocated by regmap_add_irq_chip().
 *
 * A resource managed version of regmap_del_irq_chip().
 */
व्योम devm_regmap_del_irq_chip(काष्ठा device *dev, पूर्णांक irq,
			      काष्ठा regmap_irq_chip_data *data)
अणु
	पूर्णांक rc;

	WARN_ON(irq != data->irq);
	rc = devres_release(dev, devm_regmap_irq_chip_release,
			    devm_regmap_irq_chip_match, data);

	अगर (rc != 0)
		WARN_ON(rc);
पूर्ण
EXPORT_SYMBOL_GPL(devm_regmap_del_irq_chip);

/**
 * regmap_irq_chip_get_base() - Retrieve पूर्णांकerrupt base क्रम a regmap IRQ chip
 *
 * @data: regmap irq controller to operate on.
 *
 * Useful क्रम drivers to request their own IRQs.
 */
पूर्णांक regmap_irq_chip_get_base(काष्ठा regmap_irq_chip_data *data)
अणु
	WARN_ON(!data->irq_base);
	वापस data->irq_base;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_irq_chip_get_base);

/**
 * regmap_irq_get_virq() - Map an पूर्णांकerrupt on a chip to a भव IRQ
 *
 * @data: regmap irq controller to operate on.
 * @irq: index of the पूर्णांकerrupt requested in the chip IRQs.
 *
 * Useful क्रम drivers to request their own IRQs.
 */
पूर्णांक regmap_irq_get_virq(काष्ठा regmap_irq_chip_data *data, पूर्णांक irq)
अणु
	/* Handle holes in the IRQ list */
	अगर (!data->chip->irqs[irq].mask)
		वापस -EINVAL;

	वापस irq_create_mapping(data->करोमुख्य, irq);
पूर्ण
EXPORT_SYMBOL_GPL(regmap_irq_get_virq);

/**
 * regmap_irq_get_करोमुख्य() - Retrieve the irq_करोमुख्य क्रम the chip
 *
 * @data: regmap_irq controller to operate on.
 *
 * Useful क्रम drivers to request their own IRQs and क्रम पूर्णांकegration
 * with subप्रणालीs.  For ease of पूर्णांकegration शून्य is accepted as a
 * करोमुख्य, allowing devices to just call this even अगर no करोमुख्य is
 * allocated.
 */
काष्ठा irq_करोमुख्य *regmap_irq_get_करोमुख्य(काष्ठा regmap_irq_chip_data *data)
अणु
	अगर (data)
		वापस data->करोमुख्य;
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(regmap_irq_get_करोमुख्य);
