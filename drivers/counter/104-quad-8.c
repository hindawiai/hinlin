<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Counter driver क्रम the ACCES 104-QUAD-8
 * Copyright (C) 2016 William Breathitt Gray
 *
 * This driver supports the ACCES 104-QUAD-8 and ACCES 104-QUAD-4.
 */
#समावेश <linux/bitops.h>
#समावेश <linux/counter.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/types.h>

#घोषणा QUAD8_EXTENT 32

अटल अचिन्हित पूर्णांक base[max_num_isa_dev(QUAD8_EXTENT)];
अटल अचिन्हित पूर्णांक num_quad8;
module_param_array(base, uपूर्णांक, &num_quad8, 0);
MODULE_PARM_DESC(base, "ACCES 104-QUAD-8 base addresses");

#घोषणा QUAD8_NUM_COUNTERS 8

/**
 * काष्ठा quad8 - device निजी data काष्ठाure
 * @counter:		instance of the counter_device
 * @fck_prescaler:	array of filter घड़ी prescaler configurations
 * @preset:		array of preset values
 * @count_mode:		array of count mode configurations
 * @quadrature_mode:	array of quadrature mode configurations
 * @quadrature_scale:	array of quadrature mode scale configurations
 * @ab_enable:		array of A and B inमाला_दो enable configurations
 * @preset_enable:	array of set_to_preset_on_index attribute configurations
 * @synchronous_mode:	array of index function synchronous mode configurations
 * @index_polarity:	array of index function polarity configurations
 * @cable_fault_enable:	dअगरferential encoder cable status enable configurations
 * @base:		base port address of the device
 */
काष्ठा quad8 अणु
	काष्ठा mutex lock;
	काष्ठा counter_device counter;
	अचिन्हित पूर्णांक fck_prescaler[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक preset[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक count_mode[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक quadrature_mode[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक quadrature_scale[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक ab_enable[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक preset_enable[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक synchronous_mode[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक index_polarity[QUAD8_NUM_COUNTERS];
	अचिन्हित पूर्णांक cable_fault_enable;
	अचिन्हित पूर्णांक base;
पूर्ण;

#घोषणा QUAD8_REG_CHAN_OP 0x11
#घोषणा QUAD8_REG_INDEX_INPUT_LEVELS 0x16
#घोषणा QUAD8_DIFF_ENCODER_CABLE_STATUS 0x17
/* Borrow Toggle flip-flop */
#घोषणा QUAD8_FLAG_BT BIT(0)
/* Carry Toggle flip-flop */
#घोषणा QUAD8_FLAG_CT BIT(1)
/* Error flag */
#घोषणा QUAD8_FLAG_E BIT(4)
/* Up/Down flag */
#घोषणा QUAD8_FLAG_UD BIT(5)
/* Reset and Load Signal Decoders */
#घोषणा QUAD8_CTR_RLD 0x00
/* Counter Mode Register */
#घोषणा QUAD8_CTR_CMR 0x20
/* Input / Output Control Register */
#घोषणा QUAD8_CTR_IOR 0x40
/* Index Control Register */
#घोषणा QUAD8_CTR_IDR 0x60
/* Reset Byte Poपूर्णांकer (three byte data poपूर्णांकer) */
#घोषणा QUAD8_RLD_RESET_BP 0x01
/* Reset Counter */
#घोषणा QUAD8_RLD_RESET_CNTR 0x02
/* Reset Borrow Toggle, Carry Toggle, Compare Toggle, and Sign flags */
#घोषणा QUAD8_RLD_RESET_FLAGS 0x04
/* Reset Error flag */
#घोषणा QUAD8_RLD_RESET_E 0x06
/* Preset Register to Counter */
#घोषणा QUAD8_RLD_PRESET_CNTR 0x08
/* Transfer Counter to Output Latch */
#घोषणा QUAD8_RLD_CNTR_OUT 0x10
/* Transfer Preset Register LSB to FCK Prescaler */
#घोषणा QUAD8_RLD_PRESET_PSC 0x18
#घोषणा QUAD8_CHAN_OP_ENABLE_COUNTERS 0x00
#घोषणा QUAD8_CHAN_OP_RESET_COUNTERS 0x01
#घोषणा QUAD8_CMR_QUADRATURE_X1 0x08
#घोषणा QUAD8_CMR_QUADRATURE_X2 0x10
#घोषणा QUAD8_CMR_QUADRATURE_X4 0x18

अटल पूर्णांक quad8_संकेत_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, क्रमागत counter_संकेत_value *val)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक state;

	/* Only Index संकेत levels can be पढ़ो */
	अगर (संकेत->id < 16)
		वापस -EINVAL;

	state = inb(priv->base + QUAD8_REG_INDEX_INPUT_LEVELS)
		& BIT(संकेत->id - 16);

	*val = (state) ? COUNTER_SIGNAL_HIGH : COUNTER_SIGNAL_LOW;

	वापस 0;
पूर्ण

अटल पूर्णांक quad8_count_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, अचिन्हित दीर्घ *val)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक base_offset = priv->base + 2 * count->id;
	अचिन्हित पूर्णांक flags;
	अचिन्हित पूर्णांक borrow;
	अचिन्हित पूर्णांक carry;
	पूर्णांक i;

	flags = inb(base_offset + 1);
	borrow = flags & QUAD8_FLAG_BT;
	carry = !!(flags & QUAD8_FLAG_CT);

	/* Borrow XOR Carry effectively द्विगुनs count range */
	*val = (अचिन्हित दीर्घ)(borrow ^ carry) << 24;

	mutex_lock(&priv->lock);

	/* Reset Byte Poपूर्णांकer; transfer Counter to Output Latch */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP | QUAD8_RLD_CNTR_OUT,
	     base_offset + 1);

	क्रम (i = 0; i < 3; i++)
		*val |= (अचिन्हित दीर्घ)inb(base_offset) << (8 * i);

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक quad8_count_ग_लिखो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, अचिन्हित दीर्घ val)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक base_offset = priv->base + 2 * count->id;
	पूर्णांक i;

	/* Only 24-bit values are supported */
	अगर (val > 0xFFFFFF)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	/* Reset Byte Poपूर्णांकer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Counter can only be set via Preset Register */
	क्रम (i = 0; i < 3; i++)
		outb(val >> (8 * i), base_offset);

	/* Transfer Preset Register to Counter */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_PRESET_CNTR, base_offset + 1);

	/* Reset Byte Poपूर्णांकer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Set Preset Register back to original value */
	val = priv->preset[count->id];
	क्रम (i = 0; i < 3; i++)
		outb(val >> (8 * i), base_offset);

	/* Reset Borrow, Carry, Compare, and Sign flags */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_FLAGS, base_offset + 1);
	/* Reset Error flag */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_E, base_offset + 1);

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

क्रमागत quad8_count_function अणु
	QUAD8_COUNT_FUNCTION_PULSE_सूचीECTION = 0,
	QUAD8_COUNT_FUNCTION_QUADRATURE_X1,
	QUAD8_COUNT_FUNCTION_QUADRATURE_X2,
	QUAD8_COUNT_FUNCTION_QUADRATURE_X4
पूर्ण;

अटल क्रमागत counter_count_function quad8_count_functions_list[] = अणु
	[QUAD8_COUNT_FUNCTION_PULSE_सूचीECTION] = COUNTER_COUNT_FUNCTION_PULSE_सूचीECTION,
	[QUAD8_COUNT_FUNCTION_QUADRATURE_X1] = COUNTER_COUNT_FUNCTION_QUADRATURE_X1_A,
	[QUAD8_COUNT_FUNCTION_QUADRATURE_X2] = COUNTER_COUNT_FUNCTION_QUADRATURE_X2_A,
	[QUAD8_COUNT_FUNCTION_QUADRATURE_X4] = COUNTER_COUNT_FUNCTION_QUADRATURE_X4
पूर्ण;

अटल पूर्णांक quad8_function_get(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, माप_प्रकार *function)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक id = count->id;

	mutex_lock(&priv->lock);

	अगर (priv->quadrature_mode[id])
		चयन (priv->quadrature_scale[id]) अणु
		हाल 0:
			*function = QUAD8_COUNT_FUNCTION_QUADRATURE_X1;
			अवरोध;
		हाल 1:
			*function = QUAD8_COUNT_FUNCTION_QUADRATURE_X2;
			अवरोध;
		हाल 2:
			*function = QUAD8_COUNT_FUNCTION_QUADRATURE_X4;
			अवरोध;
		पूर्ण
	अन्यथा
		*function = QUAD8_COUNT_FUNCTION_PULSE_सूचीECTION;

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक quad8_function_set(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, माप_प्रकार function)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक id = count->id;
	अचिन्हित पूर्णांक *स्थिर quadrature_mode = priv->quadrature_mode + id;
	अचिन्हित पूर्णांक *स्थिर scale = priv->quadrature_scale + id;
	अचिन्हित पूर्णांक *स्थिर synchronous_mode = priv->synchronous_mode + id;
	स्थिर पूर्णांक base_offset = priv->base + 2 * id + 1;
	अचिन्हित पूर्णांक mode_cfg;
	अचिन्हित पूर्णांक idr_cfg;

	mutex_lock(&priv->lock);

	mode_cfg = priv->count_mode[id] << 1;
	idr_cfg = priv->index_polarity[id] << 1;

	अगर (function == QUAD8_COUNT_FUNCTION_PULSE_सूचीECTION) अणु
		*quadrature_mode = 0;

		/* Quadrature scaling only available in quadrature mode */
		*scale = 0;

		/* Synchronous function not supported in non-quadrature mode */
		अगर (*synchronous_mode) अणु
			*synchronous_mode = 0;
			/* Disable synchronous function mode */
			outb(QUAD8_CTR_IDR | idr_cfg, base_offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		*quadrature_mode = 1;

		चयन (function) अणु
		हाल QUAD8_COUNT_FUNCTION_QUADRATURE_X1:
			*scale = 0;
			mode_cfg |= QUAD8_CMR_QUADRATURE_X1;
			अवरोध;
		हाल QUAD8_COUNT_FUNCTION_QUADRATURE_X2:
			*scale = 1;
			mode_cfg |= QUAD8_CMR_QUADRATURE_X2;
			अवरोध;
		हाल QUAD8_COUNT_FUNCTION_QUADRATURE_X4:
			*scale = 2;
			mode_cfg |= QUAD8_CMR_QUADRATURE_X4;
			अवरोध;
		पूर्ण
	पूर्ण

	/* Load mode configuration to Counter Mode Register */
	outb(QUAD8_CTR_CMR | mode_cfg, base_offset);

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल व्योम quad8_direction_get(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, क्रमागत counter_count_direction *direction)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक ud_flag;
	स्थिर अचिन्हित पूर्णांक flag_addr = priv->base + 2 * count->id + 1;

	/* U/D flag: nonzero = up, zero = करोwn */
	ud_flag = inb(flag_addr) & QUAD8_FLAG_UD;

	*direction = (ud_flag) ? COUNTER_COUNT_सूचीECTION_FORWARD :
		COUNTER_COUNT_सूचीECTION_BACKWARD;
पूर्ण

क्रमागत quad8_synapse_action अणु
	QUAD8_SYNAPSE_ACTION_NONE = 0,
	QUAD8_SYNAPSE_ACTION_RISING_EDGE,
	QUAD8_SYNAPSE_ACTION_FALLING_EDGE,
	QUAD8_SYNAPSE_ACTION_BOTH_EDGES
पूर्ण;

अटल क्रमागत counter_synapse_action quad8_index_actions_list[] = अणु
	[QUAD8_SYNAPSE_ACTION_NONE] = COUNTER_SYNAPSE_ACTION_NONE,
	[QUAD8_SYNAPSE_ACTION_RISING_EDGE] = COUNTER_SYNAPSE_ACTION_RISING_EDGE
पूर्ण;

अटल क्रमागत counter_synapse_action quad8_synapse_actions_list[] = अणु
	[QUAD8_SYNAPSE_ACTION_NONE] = COUNTER_SYNAPSE_ACTION_NONE,
	[QUAD8_SYNAPSE_ACTION_RISING_EDGE] = COUNTER_SYNAPSE_ACTION_RISING_EDGE,
	[QUAD8_SYNAPSE_ACTION_FALLING_EDGE] = COUNTER_SYNAPSE_ACTION_FALLING_EDGE,
	[QUAD8_SYNAPSE_ACTION_BOTH_EDGES] = COUNTER_SYNAPSE_ACTION_BOTH_EDGES
पूर्ण;

अटल पूर्णांक quad8_action_get(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, काष्ठा counter_synapse *synapse,
	माप_प्रकार *action)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	पूर्णांक err;
	माप_प्रकार function = 0;
	स्थिर माप_प्रकार संकेत_a_id = count->synapses[0].संकेत->id;
	क्रमागत counter_count_direction direction;

	/* Handle Index संकेतs */
	अगर (synapse->संकेत->id >= 16) अणु
		अगर (priv->preset_enable[count->id])
			*action = QUAD8_SYNAPSE_ACTION_RISING_EDGE;
		अन्यथा
			*action = QUAD8_SYNAPSE_ACTION_NONE;

		वापस 0;
	पूर्ण

	err = quad8_function_get(counter, count, &function);
	अगर (err)
		वापस err;

	/* Default action mode */
	*action = QUAD8_SYNAPSE_ACTION_NONE;

	/* Determine action mode based on current count function mode */
	चयन (function) अणु
	हाल QUAD8_COUNT_FUNCTION_PULSE_सूचीECTION:
		अगर (synapse->संकेत->id == संकेत_a_id)
			*action = QUAD8_SYNAPSE_ACTION_RISING_EDGE;
		अवरोध;
	हाल QUAD8_COUNT_FUNCTION_QUADRATURE_X1:
		अगर (synapse->संकेत->id == संकेत_a_id) अणु
			quad8_direction_get(counter, count, &direction);

			अगर (direction == COUNTER_COUNT_सूचीECTION_FORWARD)
				*action = QUAD8_SYNAPSE_ACTION_RISING_EDGE;
			अन्यथा
				*action = QUAD8_SYNAPSE_ACTION_FALLING_EDGE;
		पूर्ण
		अवरोध;
	हाल QUAD8_COUNT_FUNCTION_QUADRATURE_X2:
		अगर (synapse->संकेत->id == संकेत_a_id)
			*action = QUAD8_SYNAPSE_ACTION_BOTH_EDGES;
		अवरोध;
	हाल QUAD8_COUNT_FUNCTION_QUADRATURE_X4:
		*action = QUAD8_SYNAPSE_ACTION_BOTH_EDGES;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा counter_ops quad8_ops = अणु
	.संकेत_पढ़ो = quad8_संकेत_पढ़ो,
	.count_पढ़ो = quad8_count_पढ़ो,
	.count_ग_लिखो = quad8_count_ग_लिखो,
	.function_get = quad8_function_get,
	.function_set = quad8_function_set,
	.action_get = quad8_action_get
पूर्ण;

अटल स्थिर अक्षर *स्थिर quad8_index_polarity_modes[] = अणु
	"negative",
	"positive"
पूर्ण;

अटल पूर्णांक quad8_index_polarity_get(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, माप_प्रकार *index_polarity)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id - 16;

	*index_polarity = priv->index_polarity[channel_id];

	वापस 0;
पूर्ण

अटल पूर्णांक quad8_index_polarity_set(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, माप_प्रकार index_polarity)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id - 16;
	स्थिर पूर्णांक base_offset = priv->base + 2 * channel_id + 1;
	अचिन्हित पूर्णांक idr_cfg = index_polarity << 1;

	mutex_lock(&priv->lock);

	idr_cfg |= priv->synchronous_mode[channel_id];

	priv->index_polarity[channel_id] = index_polarity;

	/* Load Index Control configuration to Index Control Register */
	outb(QUAD8_CTR_IDR | idr_cfg, base_offset);

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल काष्ठा counter_संकेत_क्रमागत_ext quad8_index_pol_क्रमागत = अणु
	.items = quad8_index_polarity_modes,
	.num_items = ARRAY_SIZE(quad8_index_polarity_modes),
	.get = quad8_index_polarity_get,
	.set = quad8_index_polarity_set
पूर्ण;

अटल स्थिर अक्षर *स्थिर quad8_synchronous_modes[] = अणु
	"non-synchronous",
	"synchronous"
पूर्ण;

अटल पूर्णांक quad8_synchronous_mode_get(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, माप_प्रकार *synchronous_mode)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id - 16;

	*synchronous_mode = priv->synchronous_mode[channel_id];

	वापस 0;
पूर्ण

अटल पूर्णांक quad8_synchronous_mode_set(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, माप_प्रकार synchronous_mode)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id - 16;
	स्थिर पूर्णांक base_offset = priv->base + 2 * channel_id + 1;
	अचिन्हित पूर्णांक idr_cfg = synchronous_mode;

	mutex_lock(&priv->lock);

	idr_cfg |= priv->index_polarity[channel_id] << 1;

	/* Index function must be non-synchronous in non-quadrature mode */
	अगर (synchronous_mode && !priv->quadrature_mode[channel_id]) अणु
		mutex_unlock(&priv->lock);
		वापस -EINVAL;
	पूर्ण

	priv->synchronous_mode[channel_id] = synchronous_mode;

	/* Load Index Control configuration to Index Control Register */
	outb(QUAD8_CTR_IDR | idr_cfg, base_offset);

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल काष्ठा counter_संकेत_क्रमागत_ext quad8_syn_mode_क्रमागत = अणु
	.items = quad8_synchronous_modes,
	.num_items = ARRAY_SIZE(quad8_synchronous_modes),
	.get = quad8_synchronous_mode_get,
	.set = quad8_synchronous_mode_set
पूर्ण;

अटल sमाप_प्रकार quad8_count_न्यूनमान_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, अक्षर *buf)
अणु
	/* Only a न्यूनमान of 0 is supported */
	वापस प्र_लिखो(buf, "0\n");
पूर्ण

अटल पूर्णांक quad8_count_mode_get(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, माप_प्रकार *cnt_mode)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;

	/* Map 104-QUAD-8 count mode to Generic Counter count mode */
	चयन (priv->count_mode[count->id]) अणु
	हाल 0:
		*cnt_mode = COUNTER_COUNT_MODE_NORMAL;
		अवरोध;
	हाल 1:
		*cnt_mode = COUNTER_COUNT_MODE_RANGE_LIMIT;
		अवरोध;
	हाल 2:
		*cnt_mode = COUNTER_COUNT_MODE_NON_RECYCLE;
		अवरोध;
	हाल 3:
		*cnt_mode = COUNTER_COUNT_MODE_MODULO_N;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक quad8_count_mode_set(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, माप_प्रकार cnt_mode)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक mode_cfg;
	स्थिर पूर्णांक base_offset = priv->base + 2 * count->id + 1;

	/* Map Generic Counter count mode to 104-QUAD-8 count mode */
	चयन (cnt_mode) अणु
	हाल COUNTER_COUNT_MODE_NORMAL:
		cnt_mode = 0;
		अवरोध;
	हाल COUNTER_COUNT_MODE_RANGE_LIMIT:
		cnt_mode = 1;
		अवरोध;
	हाल COUNTER_COUNT_MODE_NON_RECYCLE:
		cnt_mode = 2;
		अवरोध;
	हाल COUNTER_COUNT_MODE_MODULO_N:
		cnt_mode = 3;
		अवरोध;
	पूर्ण

	mutex_lock(&priv->lock);

	priv->count_mode[count->id] = cnt_mode;

	/* Set count mode configuration value */
	mode_cfg = cnt_mode << 1;

	/* Add quadrature mode configuration */
	अगर (priv->quadrature_mode[count->id])
		mode_cfg |= (priv->quadrature_scale[count->id] + 1) << 3;

	/* Load mode configuration to Counter Mode Register */
	outb(QUAD8_CTR_CMR | mode_cfg, base_offset);

	mutex_unlock(&priv->lock);

	वापस 0;
पूर्ण

अटल काष्ठा counter_count_क्रमागत_ext quad8_cnt_mode_क्रमागत = अणु
	.items = counter_count_mode_str,
	.num_items = ARRAY_SIZE(counter_count_mode_str),
	.get = quad8_count_mode_get,
	.set = quad8_count_mode_set
पूर्ण;

अटल sमाप_प्रकार quad8_count_direction_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *priv, अक्षर *buf)
अणु
	क्रमागत counter_count_direction dir;

	quad8_direction_get(counter, count, &dir);

	वापस प्र_लिखो(buf, "%s\n", counter_count_direction_str[dir]);
पूर्ण

अटल sमाप_प्रकार quad8_count_enable_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, अक्षर *buf)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;

	वापस प्र_लिखो(buf, "%u\n", priv->ab_enable[count->id]);
पूर्ण

अटल sमाप_प्रकार quad8_count_enable_ग_लिखो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक base_offset = priv->base + 2 * count->id;
	पूर्णांक err;
	bool ab_enable;
	अचिन्हित पूर्णांक ior_cfg;

	err = kstrtobool(buf, &ab_enable);
	अगर (err)
		वापस err;

	mutex_lock(&priv->lock);

	priv->ab_enable[count->id] = ab_enable;

	ior_cfg = ab_enable | priv->preset_enable[count->id] << 1;

	/* Load I/O control configuration */
	outb(QUAD8_CTR_IOR | ior_cfg, base_offset + 1);

	mutex_unlock(&priv->lock);

	वापस len;
पूर्ण

अटल स्थिर अक्षर *स्थिर quad8_noise_error_states[] = अणु
	"No excessive noise is present at the count inputs",
	"Excessive noise is present at the count inputs"
पूर्ण;

अटल पूर्णांक quad8_error_noise_get(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, माप_प्रकार *noise_error)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक base_offset = priv->base + 2 * count->id + 1;

	*noise_error = !!(inb(base_offset) & QUAD8_FLAG_E);

	वापस 0;
पूर्ण

अटल काष्ठा counter_count_क्रमागत_ext quad8_error_noise_क्रमागत = अणु
	.items = quad8_noise_error_states,
	.num_items = ARRAY_SIZE(quad8_noise_error_states),
	.get = quad8_error_noise_get
पूर्ण;

अटल sमाप_प्रकार quad8_count_preset_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, अक्षर *buf)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;

	वापस प्र_लिखो(buf, "%u\n", priv->preset[count->id]);
पूर्ण

अटल व्योम quad8_preset_रेजिस्टर_set(काष्ठा quad8 *priv, पूर्णांक id,
				      अचिन्हित पूर्णांक preset)
अणु
	स्थिर अचिन्हित पूर्णांक base_offset = priv->base + 2 * id;
	पूर्णांक i;

	priv->preset[id] = preset;

	/* Reset Byte Poपूर्णांकer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Set Preset Register */
	क्रम (i = 0; i < 3; i++)
		outb(preset >> (8 * i), base_offset);
पूर्ण

अटल sमाप_प्रकार quad8_count_preset_ग_लिखो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक preset;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &preset);
	अगर (ret)
		वापस ret;

	/* Only 24-bit values are supported */
	अगर (preset > 0xFFFFFF)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	quad8_preset_रेजिस्टर_set(priv, count->id, preset);

	mutex_unlock(&priv->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार quad8_count_उच्चमानing_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;

	mutex_lock(&priv->lock);

	/* Range Limit and Modulo-N count modes use preset value as उच्चमानing */
	चयन (priv->count_mode[count->id]) अणु
	हाल 1:
	हाल 3:
		mutex_unlock(&priv->lock);
		वापस प्र_लिखो(buf, "%u\n", priv->preset[count->id]);
	पूर्ण

	mutex_unlock(&priv->lock);

	/* By शेष 0x1FFFFFF (25 bits अचिन्हित) is maximum count */
	वापस प्र_लिखो(buf, "33554431\n");
पूर्ण

अटल sमाप_प्रकार quad8_count_उच्चमानing_ग_लिखो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	अचिन्हित पूर्णांक उच्चमानing;
	पूर्णांक ret;

	ret = kstrtouपूर्णांक(buf, 0, &उच्चमानing);
	अगर (ret)
		वापस ret;

	/* Only 24-bit values are supported */
	अगर (उच्चमानing > 0xFFFFFF)
		वापस -EINVAL;

	mutex_lock(&priv->lock);

	/* Range Limit and Modulo-N count modes use preset value as उच्चमानing */
	चयन (priv->count_mode[count->id]) अणु
	हाल 1:
	हाल 3:
		quad8_preset_रेजिस्टर_set(priv, count->id, उच्चमानing);
		अवरोध;
	पूर्ण

	mutex_unlock(&priv->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार quad8_count_preset_enable_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, अक्षर *buf)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;

	वापस प्र_लिखो(buf, "%u\n", !priv->preset_enable[count->id]);
पूर्ण

अटल sमाप_प्रकार quad8_count_preset_enable_ग_लिखो(काष्ठा counter_device *counter,
	काष्ठा counter_count *count, व्योम *निजी, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर पूर्णांक base_offset = priv->base + 2 * count->id + 1;
	bool preset_enable;
	पूर्णांक ret;
	अचिन्हित पूर्णांक ior_cfg;

	ret = kstrtobool(buf, &preset_enable);
	अगर (ret)
		वापस ret;

	/* Preset enable is active low in Input/Output Control रेजिस्टर */
	preset_enable = !preset_enable;

	mutex_lock(&priv->lock);

	priv->preset_enable[count->id] = preset_enable;

	ior_cfg = priv->ab_enable[count->id] | (अचिन्हित पूर्णांक)preset_enable << 1;

	/* Load I/O control configuration to Input / Output Control Register */
	outb(QUAD8_CTR_IOR | ior_cfg, base_offset);

	mutex_unlock(&priv->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार quad8_संकेत_cable_fault_पढ़ो(काष्ठा counter_device *counter,
					     काष्ठा counter_संकेत *संकेत,
					     व्योम *निजी, अक्षर *buf)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id / 2;
	bool disabled;
	अचिन्हित पूर्णांक status;
	अचिन्हित पूर्णांक fault;

	mutex_lock(&priv->lock);

	disabled = !(priv->cable_fault_enable & BIT(channel_id));

	अगर (disabled) अणु
		mutex_unlock(&priv->lock);
		वापस -EINVAL;
	पूर्ण

	/* Logic 0 = cable fault */
	status = inb(priv->base + QUAD8_DIFF_ENCODER_CABLE_STATUS);

	mutex_unlock(&priv->lock);

	/* Mask respective channel and invert logic */
	fault = !(status & BIT(channel_id));

	वापस प्र_लिखो(buf, "%u\n", fault);
पूर्ण

अटल sमाप_प्रकार quad8_संकेत_cable_fault_enable_पढ़ो(
	काष्ठा counter_device *counter, काष्ठा counter_संकेत *संकेत,
	व्योम *निजी, अक्षर *buf)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id / 2;
	स्थिर अचिन्हित पूर्णांक enb = !!(priv->cable_fault_enable & BIT(channel_id));

	वापस प्र_लिखो(buf, "%u\n", enb);
पूर्ण

अटल sमाप_प्रकार quad8_संकेत_cable_fault_enable_ग_लिखो(
	काष्ठा counter_device *counter, काष्ठा counter_संकेत *संकेत,
	व्योम *निजी, स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id / 2;
	bool enable;
	पूर्णांक ret;
	अचिन्हित पूर्णांक cable_fault_enable;

	ret = kstrtobool(buf, &enable);
	अगर (ret)
		वापस ret;

	mutex_lock(&priv->lock);

	अगर (enable)
		priv->cable_fault_enable |= BIT(channel_id);
	अन्यथा
		priv->cable_fault_enable &= ~BIT(channel_id);

	/* Enable is active low in Dअगरferential Encoder Cable Status रेजिस्टर */
	cable_fault_enable = ~priv->cable_fault_enable;

	outb(cable_fault_enable, priv->base + QUAD8_DIFF_ENCODER_CABLE_STATUS);

	mutex_unlock(&priv->lock);

	वापस len;
पूर्ण

अटल sमाप_प्रकार quad8_संकेत_fck_prescaler_पढ़ो(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, व्योम *निजी, अक्षर *buf)
अणु
	स्थिर काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id / 2;

	वापस प्र_लिखो(buf, "%u\n", priv->fck_prescaler[channel_id]);
पूर्ण

अटल sमाप_प्रकार quad8_संकेत_fck_prescaler_ग_लिखो(काष्ठा counter_device *counter,
	काष्ठा counter_संकेत *संकेत, व्योम *निजी, स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	काष्ठा quad8 *स्थिर priv = counter->priv;
	स्थिर माप_प्रकार channel_id = संकेत->id / 2;
	स्थिर पूर्णांक base_offset = priv->base + 2 * channel_id;
	u8 prescaler;
	पूर्णांक ret;

	ret = kstrtou8(buf, 0, &prescaler);
	अगर (ret)
		वापस ret;

	mutex_lock(&priv->lock);

	priv->fck_prescaler[channel_id] = prescaler;

	/* Reset Byte Poपूर्णांकer */
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);

	/* Set filter घड़ी factor */
	outb(prescaler, base_offset);
	outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP | QUAD8_RLD_PRESET_PSC,
	     base_offset + 1);

	mutex_unlock(&priv->lock);

	वापस len;
पूर्ण

अटल स्थिर काष्ठा counter_संकेत_ext quad8_संकेत_ext[] = अणु
	अणु
		.name = "cable_fault",
		.पढ़ो = quad8_संकेत_cable_fault_पढ़ो
	पूर्ण,
	अणु
		.name = "cable_fault_enable",
		.पढ़ो = quad8_संकेत_cable_fault_enable_पढ़ो,
		.ग_लिखो = quad8_संकेत_cable_fault_enable_ग_लिखो
	पूर्ण,
	अणु
		.name = "filter_clock_prescaler",
		.पढ़ो = quad8_संकेत_fck_prescaler_पढ़ो,
		.ग_लिखो = quad8_संकेत_fck_prescaler_ग_लिखो
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा counter_संकेत_ext quad8_index_ext[] = अणु
	COUNTER_SIGNAL_ENUM("index_polarity", &quad8_index_pol_क्रमागत),
	COUNTER_SIGNAL_ENUM_AVAILABLE("index_polarity",	&quad8_index_pol_क्रमागत),
	COUNTER_SIGNAL_ENUM("synchronous_mode", &quad8_syn_mode_क्रमागत),
	COUNTER_SIGNAL_ENUM_AVAILABLE("synchronous_mode", &quad8_syn_mode_क्रमागत)
पूर्ण;

#घोषणा QUAD8_QUAD_SIGNAL(_id, _name) अणु		\
	.id = (_id),				\
	.name = (_name),			\
	.ext = quad8_संकेत_ext,		\
	.num_ext = ARRAY_SIZE(quad8_संकेत_ext)	\
पूर्ण

#घोषणा	QUAD8_INDEX_SIGNAL(_id, _name) अणु	\
	.id = (_id),				\
	.name = (_name),			\
	.ext = quad8_index_ext,			\
	.num_ext = ARRAY_SIZE(quad8_index_ext)	\
पूर्ण

अटल काष्ठा counter_संकेत quad8_संकेतs[] = अणु
	QUAD8_QUAD_SIGNAL(0, "Channel 1 Quadrature A"),
	QUAD8_QUAD_SIGNAL(1, "Channel 1 Quadrature B"),
	QUAD8_QUAD_SIGNAL(2, "Channel 2 Quadrature A"),
	QUAD8_QUAD_SIGNAL(3, "Channel 2 Quadrature B"),
	QUAD8_QUAD_SIGNAL(4, "Channel 3 Quadrature A"),
	QUAD8_QUAD_SIGNAL(5, "Channel 3 Quadrature B"),
	QUAD8_QUAD_SIGNAL(6, "Channel 4 Quadrature A"),
	QUAD8_QUAD_SIGNAL(7, "Channel 4 Quadrature B"),
	QUAD8_QUAD_SIGNAL(8, "Channel 5 Quadrature A"),
	QUAD8_QUAD_SIGNAL(9, "Channel 5 Quadrature B"),
	QUAD8_QUAD_SIGNAL(10, "Channel 6 Quadrature A"),
	QUAD8_QUAD_SIGNAL(11, "Channel 6 Quadrature B"),
	QUAD8_QUAD_SIGNAL(12, "Channel 7 Quadrature A"),
	QUAD8_QUAD_SIGNAL(13, "Channel 7 Quadrature B"),
	QUAD8_QUAD_SIGNAL(14, "Channel 8 Quadrature A"),
	QUAD8_QUAD_SIGNAL(15, "Channel 8 Quadrature B"),
	QUAD8_INDEX_SIGNAL(16, "Channel 1 Index"),
	QUAD8_INDEX_SIGNAL(17, "Channel 2 Index"),
	QUAD8_INDEX_SIGNAL(18, "Channel 3 Index"),
	QUAD8_INDEX_SIGNAL(19, "Channel 4 Index"),
	QUAD8_INDEX_SIGNAL(20, "Channel 5 Index"),
	QUAD8_INDEX_SIGNAL(21, "Channel 6 Index"),
	QUAD8_INDEX_SIGNAL(22, "Channel 7 Index"),
	QUAD8_INDEX_SIGNAL(23, "Channel 8 Index")
पूर्ण;

#घोषणा QUAD8_COUNT_SYNAPSES(_id) अणु					\
	अणु								\
		.actions_list = quad8_synapse_actions_list,		\
		.num_actions = ARRAY_SIZE(quad8_synapse_actions_list),	\
		.संकेत = quad8_संकेतs + 2 * (_id)			\
	पूर्ण,								\
	अणु								\
		.actions_list = quad8_synapse_actions_list,		\
		.num_actions = ARRAY_SIZE(quad8_synapse_actions_list),	\
		.संकेत = quad8_संकेतs + 2 * (_id) + 1			\
	पूर्ण,								\
	अणु								\
		.actions_list = quad8_index_actions_list,		\
		.num_actions = ARRAY_SIZE(quad8_index_actions_list),	\
		.संकेत = quad8_संकेतs + 2 * (_id) + 16		\
	पूर्ण								\
पूर्ण

अटल काष्ठा counter_synapse quad8_count_synapses[][3] = अणु
	QUAD8_COUNT_SYNAPSES(0), QUAD8_COUNT_SYNAPSES(1),
	QUAD8_COUNT_SYNAPSES(2), QUAD8_COUNT_SYNAPSES(3),
	QUAD8_COUNT_SYNAPSES(4), QUAD8_COUNT_SYNAPSES(5),
	QUAD8_COUNT_SYNAPSES(6), QUAD8_COUNT_SYNAPSES(7)
पूर्ण;

अटल स्थिर काष्ठा counter_count_ext quad8_count_ext[] = अणु
	अणु
		.name = "ceiling",
		.पढ़ो = quad8_count_उच्चमानing_पढ़ो,
		.ग_लिखो = quad8_count_उच्चमानing_ग_लिखो
	पूर्ण,
	अणु
		.name = "floor",
		.पढ़ो = quad8_count_न्यूनमान_पढ़ो
	पूर्ण,
	COUNTER_COUNT_ENUM("count_mode", &quad8_cnt_mode_क्रमागत),
	COUNTER_COUNT_ENUM_AVAILABLE("count_mode", &quad8_cnt_mode_क्रमागत),
	अणु
		.name = "direction",
		.पढ़ो = quad8_count_direction_पढ़ो
	पूर्ण,
	अणु
		.name = "enable",
		.पढ़ो = quad8_count_enable_पढ़ो,
		.ग_लिखो = quad8_count_enable_ग_लिखो
	पूर्ण,
	COUNTER_COUNT_ENUM("error_noise", &quad8_error_noise_क्रमागत),
	COUNTER_COUNT_ENUM_AVAILABLE("error_noise", &quad8_error_noise_क्रमागत),
	अणु
		.name = "preset",
		.पढ़ो = quad8_count_preset_पढ़ो,
		.ग_लिखो = quad8_count_preset_ग_लिखो
	पूर्ण,
	अणु
		.name = "preset_enable",
		.पढ़ो = quad8_count_preset_enable_पढ़ो,
		.ग_लिखो = quad8_count_preset_enable_ग_लिखो
	पूर्ण
पूर्ण;

#घोषणा QUAD8_COUNT(_id, _cntname) अणु					\
	.id = (_id),							\
	.name = (_cntname),						\
	.functions_list = quad8_count_functions_list,			\
	.num_functions = ARRAY_SIZE(quad8_count_functions_list),	\
	.synapses = quad8_count_synapses[(_id)],			\
	.num_synapses =	2,						\
	.ext = quad8_count_ext,						\
	.num_ext = ARRAY_SIZE(quad8_count_ext)				\
पूर्ण

अटल काष्ठा counter_count quad8_counts[] = अणु
	QUAD8_COUNT(0, "Channel 1 Count"),
	QUAD8_COUNT(1, "Channel 2 Count"),
	QUAD8_COUNT(2, "Channel 3 Count"),
	QUAD8_COUNT(3, "Channel 4 Count"),
	QUAD8_COUNT(4, "Channel 5 Count"),
	QUAD8_COUNT(5, "Channel 6 Count"),
	QUAD8_COUNT(6, "Channel 7 Count"),
	QUAD8_COUNT(7, "Channel 8 Count")
पूर्ण;

अटल पूर्णांक quad8_probe(काष्ठा device *dev, अचिन्हित पूर्णांक id)
अणु
	काष्ठा quad8 *priv;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक base_offset;

	अगर (!devm_request_region(dev, base[id], QUAD8_EXTENT, dev_name(dev))) अणु
		dev_err(dev, "Unable to lock port addresses (0x%X-0x%X)\n",
			base[id], base[id] + QUAD8_EXTENT);
		वापस -EBUSY;
	पूर्ण

	priv = devm_kzalloc(dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	/* Initialize Counter device and driver data */
	priv->counter.name = dev_name(dev);
	priv->counter.parent = dev;
	priv->counter.ops = &quad8_ops;
	priv->counter.counts = quad8_counts;
	priv->counter.num_counts = ARRAY_SIZE(quad8_counts);
	priv->counter.संकेतs = quad8_संकेतs;
	priv->counter.num_संकेतs = ARRAY_SIZE(quad8_संकेतs);
	priv->counter.priv = priv;
	priv->base = base[id];

	/* Initialize mutex */
	mutex_init(&priv->lock);

	/* Reset all counters and disable पूर्णांकerrupt function */
	outb(QUAD8_CHAN_OP_RESET_COUNTERS, base[id] + QUAD8_REG_CHAN_OP);
	/* Set initial configuration क्रम all counters */
	क्रम (i = 0; i < QUAD8_NUM_COUNTERS; i++) अणु
		base_offset = base[id] + 2 * i;
		/* Reset Byte Poपूर्णांकer */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);
		/* Reset filter घड़ी factor */
		outb(0, base_offset);
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP | QUAD8_RLD_PRESET_PSC,
		     base_offset + 1);
		/* Reset Byte Poपूर्णांकer */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_BP, base_offset + 1);
		/* Reset Preset Register */
		क्रम (j = 0; j < 3; j++)
			outb(0x00, base_offset);
		/* Reset Borrow, Carry, Compare, and Sign flags */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_FLAGS, base_offset + 1);
		/* Reset Error flag */
		outb(QUAD8_CTR_RLD | QUAD8_RLD_RESET_E, base_offset + 1);
		/* Binary encoding; Normal count; non-quadrature mode */
		outb(QUAD8_CTR_CMR, base_offset + 1);
		/* Disable A and B inमाला_दो; preset on index; FLG1 as Carry */
		outb(QUAD8_CTR_IOR, base_offset + 1);
		/* Disable index function; negative index polarity */
		outb(QUAD8_CTR_IDR, base_offset + 1);
	पूर्ण
	/* Disable Dअगरferential Encoder Cable Status क्रम all channels */
	outb(0xFF, base[id] + QUAD8_DIFF_ENCODER_CABLE_STATUS);
	/* Enable all counters */
	outb(QUAD8_CHAN_OP_ENABLE_COUNTERS, base[id] + QUAD8_REG_CHAN_OP);

	/* Register Counter device */
	वापस devm_counter_रेजिस्टर(dev, &priv->counter);
पूर्ण

अटल काष्ठा isa_driver quad8_driver = अणु
	.probe = quad8_probe,
	.driver = अणु
		.name = "104-quad-8"
	पूर्ण
पूर्ण;

module_isa_driver(quad8_driver, num_quad8);

MODULE_AUTHOR("William Breathitt Gray <vilhelm.gray@gmail.com>");
MODULE_DESCRIPTION("ACCES 104-QUAD-8 driver");
MODULE_LICENSE("GPL v2");
