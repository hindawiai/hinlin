<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Flex Timer Module Quadrature decoder
 *
 * This module implements a driver क्रम decoding the FTM quadrature
 * of ex. a LS1021A
 */

#समावेश <linux/fsl/fपंचांग.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/पन.स>
#समावेश <linux/mutex.h>
#समावेश <linux/counter.h>
#समावेश <linux/bitfield.h>

#घोषणा FTM_FIELD_UPDATE(fपंचांग, offset, mask, val)			\
	(अणु								\
		uपूर्णांक32_t flags;						\
		fपंचांग_पढ़ो(fपंचांग, offset, &flags);				\
		flags &= ~mask;						\
		flags |= FIELD_PREP(mask, val);				\
		fपंचांग_ग_लिखो(fपंचांग, offset, flags);				\
	पूर्ण)

काष्ठा fपंचांग_quaddec अणु
	काष्ठा counter_device counter;
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem *fपंचांग_base;
	bool big_endian;
	काष्ठा mutex fपंचांग_quaddec_mutex;
पूर्ण;

अटल व्योम fपंचांग_पढ़ो(काष्ठा fपंचांग_quaddec *fपंचांग, uपूर्णांक32_t offset, uपूर्णांक32_t *data)
अणु
	अगर (fपंचांग->big_endian)
		*data = ioपढ़ो32be(fपंचांग->fपंचांग_base + offset);
	अन्यथा
		*data = ioपढ़ो32(fपंचांग->fपंचांग_base + offset);
पूर्ण

अटल व्योम fपंचांग_ग_लिखो(काष्ठा fपंचांग_quaddec *fपंचांग, uपूर्णांक32_t offset, uपूर्णांक32_t data)
अणु
	अगर (fपंचांग->big_endian)
		ioग_लिखो32be(data, fपंचांग->fपंचांग_base + offset);
	अन्यथा
		ioग_लिखो32(data, fपंचांग->fपंचांग_base + offset);
पूर्ण

/* Hold mutex beक्रमe modअगरying ग_लिखो protection state */
अटल व्योम fपंचांग_clear_ग_लिखो_protection(काष्ठा fपंचांग_quaddec *fपंचांग)
अणु
	uपूर्णांक32_t flag;

	/* First see अगर it is enabled */
	fपंचांग_पढ़ो(fपंचांग, FTM_FMS, &flag);

	अगर (flag & FTM_FMS_WPEN)
		FTM_FIELD_UPDATE(fपंचांग, FTM_MODE, FTM_MODE_WPDIS, 1);
पूर्ण

अटल व्योम fपंचांग_set_ग_लिखो_protection(काष्ठा fपंचांग_quaddec *fपंचांग)
अणु
	FTM_FIELD_UPDATE(fपंचांग, FTM_FMS, FTM_FMS_WPEN, 1);
पूर्ण

अटल व्योम fपंचांग_reset_counter(काष्ठा fपंचांग_quaddec *fपंचांग)
अणु
	/* Reset hardware counter to CNTIN */
	fपंचांग_ग_लिखो(fपंचांग, FTM_CNT, 0x0);
पूर्ण

अटल व्योम fपंचांग_quaddec_init(काष्ठा fपंचांग_quaddec *fपंचांग)
अणु
	fपंचांग_clear_ग_लिखो_protection(fपंचांग);

	/*
	 * Do not ग_लिखो in the region from the CNTIN रेजिस्टर through the
	 * PWMLOAD रेजिस्टर when FTMEN = 0.
	 * Also reset other fields to zero
	 */
	fपंचांग_ग_लिखो(fपंचांग, FTM_MODE, FTM_MODE_FTMEN);
	fपंचांग_ग_लिखो(fपंचांग, FTM_CNTIN, 0x0000);
	fपंचांग_ग_लिखो(fपंचांग, FTM_MOD, 0xffff);
	fपंचांग_ग_लिखो(fपंचांग, FTM_CNT, 0x0);
	/* Set prescaler, reset other fields to zero */
	fपंचांग_ग_लिखो(fपंचांग, FTM_SC, FTM_SC_PS_1);

	/* Select quad mode, reset other fields to zero */
	fपंचांग_ग_लिखो(fपंचांग, FTM_QDCTRL, FTM_QDCTRL_QUADEN);

	/* Unused features and reset to शेष section */
	fपंचांग_ग_लिखो(fपंचांग, FTM_POL, 0x0);
	fपंचांग_ग_लिखो(fपंचांग, FTM_FLTCTRL, 0x0);
	fपंचांग_ग_लिखो(fपंचांग, FTM_SYNCONF, 0x0);
	fपंचांग_ग_लिखो(fपंचांग, FTM_SYNC, 0xffff);

	/* Lock the FTM */
	fपंचांग_set_ग_लिखो_protection(fपंचांग);
पूर्ण

अटल व्योम fपंचांग_quaddec_disable(व्योम *fपंचांग)
अणु
	काष्ठा fपंचांग_quaddec *fपंचांग_qua = fपंचांग;

	fपंचांग_clear_ग_लिखो_protection(fपंचांग_qua);
	fपंचांग_ग_लिखो(fपंचांग_qua, FTM_MODE, 0);
	fपंचांग_ग_लिखो(fपंचांग_qua, FTM_QDCTRL, 0);
	/*
	 * This is enough to disable the counter. No घड़ी has been
	 * selected by writing to FTM_SC in init()
	 */
	fपंचांग_set_ग_लिखो_protection(fपंचांग_qua);
पूर्ण

अटल पूर्णांक fपंचांग_quaddec_get_prescaler(काष्ठा counter_device *counter,
				     काष्ठा counter_count *count,
				     माप_प्रकार *cnt_mode)
अणु
	काष्ठा fपंचांग_quaddec *fपंचांग = counter->priv;
	uपूर्णांक32_t scflags;

	fपंचांग_पढ़ो(fपंचांग, FTM_SC, &scflags);

	*cnt_mode = FIELD_GET(FTM_SC_PS_MASK, scflags);

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_quaddec_set_prescaler(काष्ठा counter_device *counter,
				     काष्ठा counter_count *count,
				     माप_प्रकार cnt_mode)
अणु
	काष्ठा fपंचांग_quaddec *fपंचांग = counter->priv;

	mutex_lock(&fपंचांग->fपंचांग_quaddec_mutex);

	fपंचांग_clear_ग_लिखो_protection(fपंचांग);
	FTM_FIELD_UPDATE(fपंचांग, FTM_SC, FTM_SC_PS_MASK, cnt_mode);
	fपंचांग_set_ग_लिखो_protection(fपंचांग);

	/* Also resets the counter as it is undefined anyway now */
	fपंचांग_reset_counter(fपंचांग);

	mutex_unlock(&fपंचांग->fपंचांग_quaddec_mutex);
	वापस 0;
पूर्ण

अटल स्थिर अक्षर * स्थिर fपंचांग_quaddec_prescaler[] = अणु
	"1", "2", "4", "8", "16", "32", "64", "128"
पूर्ण;

अटल काष्ठा counter_count_क्रमागत_ext fपंचांग_quaddec_prescaler_क्रमागत = अणु
	.items = fपंचांग_quaddec_prescaler,
	.num_items = ARRAY_SIZE(fपंचांग_quaddec_prescaler),
	.get = fपंचांग_quaddec_get_prescaler,
	.set = fपंचांग_quaddec_set_prescaler
पूर्ण;

क्रमागत fपंचांग_quaddec_synapse_action अणु
	FTM_QUADDEC_SYNAPSE_ACTION_BOTH_EDGES,
पूर्ण;

अटल क्रमागत counter_synapse_action fपंचांग_quaddec_synapse_actions[] = अणु
	[FTM_QUADDEC_SYNAPSE_ACTION_BOTH_EDGES] =
	COUNTER_SYNAPSE_ACTION_BOTH_EDGES
पूर्ण;

क्रमागत fपंचांग_quaddec_count_function अणु
	FTM_QUADDEC_COUNT_ENCODER_MODE_1,
पूर्ण;

अटल स्थिर क्रमागत counter_count_function fपंचांग_quaddec_count_functions[] = अणु
	[FTM_QUADDEC_COUNT_ENCODER_MODE_1] =
	COUNTER_COUNT_FUNCTION_QUADRATURE_X4
पूर्ण;

अटल पूर्णांक fपंचांग_quaddec_count_पढ़ो(काष्ठा counter_device *counter,
				  काष्ठा counter_count *count,
				  अचिन्हित दीर्घ *val)
अणु
	काष्ठा fपंचांग_quaddec *स्थिर fपंचांग = counter->priv;
	uपूर्णांक32_t cntval;

	fपंचांग_पढ़ो(fपंचांग, FTM_CNT, &cntval);

	*val = cntval;

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_quaddec_count_ग_लिखो(काष्ठा counter_device *counter,
				   काष्ठा counter_count *count,
				   स्थिर अचिन्हित दीर्घ val)
अणु
	काष्ठा fपंचांग_quaddec *स्थिर fपंचांग = counter->priv;

	अगर (val != 0) अणु
		dev_warn(&fपंचांग->pdev->dev, "Can only accept '0' as new counter value\n");
		वापस -EINVAL;
	पूर्ण

	fपंचांग_reset_counter(fपंचांग);

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_quaddec_count_function_get(काष्ठा counter_device *counter,
					  काष्ठा counter_count *count,
					  माप_प्रकार *function)
अणु
	*function = FTM_QUADDEC_COUNT_ENCODER_MODE_1;

	वापस 0;
पूर्ण

अटल पूर्णांक fपंचांग_quaddec_action_get(काष्ठा counter_device *counter,
				  काष्ठा counter_count *count,
				  काष्ठा counter_synapse *synapse,
				  माप_प्रकार *action)
अणु
	*action = FTM_QUADDEC_SYNAPSE_ACTION_BOTH_EDGES;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा counter_ops fपंचांग_quaddec_cnt_ops = अणु
	.count_पढ़ो = fपंचांग_quaddec_count_पढ़ो,
	.count_ग_लिखो = fपंचांग_quaddec_count_ग_लिखो,
	.function_get = fपंचांग_quaddec_count_function_get,
	.action_get = fपंचांग_quaddec_action_get,
पूर्ण;

अटल काष्ठा counter_संकेत fपंचांग_quaddec_संकेतs[] = अणु
	अणु
		.id = 0,
		.name = "Channel 1 Phase A"
	पूर्ण,
	अणु
		.id = 1,
		.name = "Channel 1 Phase B"
	पूर्ण
पूर्ण;

अटल काष्ठा counter_synapse fपंचांग_quaddec_count_synapses[] = अणु
	अणु
		.actions_list = fपंचांग_quaddec_synapse_actions,
		.num_actions = ARRAY_SIZE(fपंचांग_quaddec_synapse_actions),
		.संकेत = &fपंचांग_quaddec_संकेतs[0]
	पूर्ण,
	अणु
		.actions_list = fपंचांग_quaddec_synapse_actions,
		.num_actions = ARRAY_SIZE(fपंचांग_quaddec_synapse_actions),
		.संकेत = &fपंचांग_quaddec_संकेतs[1]
	पूर्ण
पूर्ण;

अटल स्थिर काष्ठा counter_count_ext fपंचांग_quaddec_count_ext[] = अणु
	COUNTER_COUNT_ENUM("prescaler", &fपंचांग_quaddec_prescaler_क्रमागत),
	COUNTER_COUNT_ENUM_AVAILABLE("prescaler", &fपंचांग_quaddec_prescaler_क्रमागत),
पूर्ण;

अटल काष्ठा counter_count fपंचांग_quaddec_counts = अणु
	.id = 0,
	.name = "Channel 1 Count",
	.functions_list = fपंचांग_quaddec_count_functions,
	.num_functions = ARRAY_SIZE(fपंचांग_quaddec_count_functions),
	.synapses = fपंचांग_quaddec_count_synapses,
	.num_synapses = ARRAY_SIZE(fपंचांग_quaddec_count_synapses),
	.ext = fपंचांग_quaddec_count_ext,
	.num_ext = ARRAY_SIZE(fपंचांग_quaddec_count_ext)
पूर्ण;

अटल पूर्णांक fपंचांग_quaddec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा fपंचांग_quaddec *fपंचांग;

	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा resource *io;
	पूर्णांक ret;

	fपंचांग = devm_kzalloc(&pdev->dev, माप(*fपंचांग), GFP_KERNEL);
	अगर (!fपंचांग)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, fपंचांग);

	io = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!io) अणु
		dev_err(&pdev->dev, "Failed to get memory region\n");
		वापस -ENODEV;
	पूर्ण

	fपंचांग->pdev = pdev;
	fपंचांग->big_endian = of_property_पढ़ो_bool(node, "big-endian");
	fपंचांग->fपंचांग_base = devm_ioremap(&pdev->dev, io->start, resource_size(io));

	अगर (!fपंचांग->fपंचांग_base) अणु
		dev_err(&pdev->dev, "Failed to map memory region\n");
		वापस -EINVAL;
	पूर्ण
	fपंचांग->counter.name = dev_name(&pdev->dev);
	fपंचांग->counter.parent = &pdev->dev;
	fपंचांग->counter.ops = &fपंचांग_quaddec_cnt_ops;
	fपंचांग->counter.counts = &fपंचांग_quaddec_counts;
	fपंचांग->counter.num_counts = 1;
	fपंचांग->counter.संकेतs = fपंचांग_quaddec_संकेतs;
	fपंचांग->counter.num_संकेतs = ARRAY_SIZE(fपंचांग_quaddec_संकेतs);
	fपंचांग->counter.priv = fपंचांग;

	mutex_init(&fपंचांग->fपंचांग_quaddec_mutex);

	fपंचांग_quaddec_init(fपंचांग);

	ret = devm_add_action_or_reset(&pdev->dev, fपंचांग_quaddec_disable, fपंचांग);
	अगर (ret)
		वापस ret;

	ret = devm_counter_रेजिस्टर(&pdev->dev, &fपंचांग->counter);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id fपंचांग_quaddec_match[] = अणु
	अणु .compatible = "fsl,ftm-quaddec" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fपंचांग_quaddec_driver = अणु
	.driver = अणु
		.name = "ftm-quaddec",
		.of_match_table = fपंचांग_quaddec_match,
	पूर्ण,
	.probe = fपंचांग_quaddec_probe,
पूर्ण;

module_platक्रमm_driver(fपंचांग_quaddec_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kjeld Flarup <kfa@deif.com>");
MODULE_AUTHOR("Patrick Havelange <patrick.havelange@essensium.com>");
