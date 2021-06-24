<शैली गुरु>
/*
 * Copyright (C) 2014 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/clk.h>
#समावेश <linux/gfp.h>
#समावेश <linux/पन.स>
#समावेश <linux/input.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>

#घोषणा DEFAULT_CLK_HZ			31250
#घोषणा MAX_ROWS			8
#घोषणा MAX_COLS			8

/* Register/field definitions */
#घोषणा KPCR_OFFSET			0x00000080
#घोषणा KPCR_MODE			0x00000002
#घोषणा KPCR_MODE_SHIFT			1
#घोषणा KPCR_MODE_MASK			1
#घोषणा KPCR_ENABLE			0x00000001
#घोषणा KPCR_STATUSFILTERENABLE		0x00008000
#घोषणा KPCR_STATUSFILTERTYPE_SHIFT	12
#घोषणा KPCR_COLFILTERENABLE		0x00000800
#घोषणा KPCR_COLFILTERTYPE_SHIFT	8
#घोषणा KPCR_ROWWIDTH_SHIFT		20
#घोषणा KPCR_COLUMNWIDTH_SHIFT		16

#घोषणा KPIOR_OFFSET			0x00000084
#घोषणा KPIOR_ROWOCONTRL_SHIFT		24
#घोषणा KPIOR_ROWOCONTRL_MASK		0xFF000000
#घोषणा KPIOR_COLUMNOCONTRL_SHIFT	16
#घोषणा KPIOR_COLUMNOCONTRL_MASK	0x00FF0000
#घोषणा KPIOR_COLUMN_IO_DATA_SHIFT	0

#घोषणा KPEMR0_OFFSET			0x00000090
#घोषणा KPEMR1_OFFSET			0x00000094
#घोषणा KPEMR2_OFFSET			0x00000098
#घोषणा KPEMR3_OFFSET			0x0000009C
#घोषणा KPEMR_EDGETYPE_BOTH		3

#घोषणा KPSSR0_OFFSET			0x000000A0
#घोषणा KPSSR1_OFFSET			0x000000A4
#घोषणा KPSSRN_OFFSET(reg_n)		(KPSSR0_OFFSET + 4 * (reg_n))
#घोषणा KPIMR0_OFFSET			0x000000B0
#घोषणा KPIMR1_OFFSET			0x000000B4
#घोषणा KPICR0_OFFSET			0x000000B8
#घोषणा KPICR1_OFFSET			0x000000BC
#घोषणा KPICRN_OFFSET(reg_n)		(KPICR0_OFFSET + 4 * (reg_n))
#घोषणा KPISR0_OFFSET			0x000000C0
#घोषणा KPISR1_OFFSET			0x000000C4

#घोषणा KPCR_STATUSFILTERTYPE_MAX	7
#घोषणा KPCR_COLFILTERTYPE_MAX		7

/* Macros to determine the row/column from a bit that is set in SSR0/1. */
#घोषणा BIT_TO_ROW_SSRN(bit_nr, reg_n)	(((bit_nr) >> 3) + 4 * (reg_n))
#घोषणा BIT_TO_COL(bit_nr)		((bit_nr) % 8)

/* Structure representing various run-समय entities */
काष्ठा bcm_kp अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	काष्ठा clk *clk;
	काष्ठा input_dev *input_dev;
	अचिन्हित दीर्घ last_state[2];
	अचिन्हित पूर्णांक n_rows;
	अचिन्हित पूर्णांक n_cols;
	u32 kpcr;
	u32 kpior;
	u32 kpemr;
	u32 imr0_val;
	u32 imr1_val;
पूर्ण;

/*
 * Returns the keycode from the input device keymap given the row and
 * column.
 */
अटल पूर्णांक bcm_kp_get_keycode(काष्ठा bcm_kp *kp, पूर्णांक row, पूर्णांक col)
अणु
	अचिन्हित पूर्णांक row_shअगरt = get_count_order(kp->n_cols);
	अचिन्हित लघु *keymap = kp->input_dev->keycode;

	वापस keymap[MATRIX_SCAN_CODE(row, col, row_shअगरt)];
पूर्ण

अटल व्योम bcm_kp_report_keys(काष्ठा bcm_kp *kp, पूर्णांक reg_num, पूर्णांक pull_mode)
अणु
	अचिन्हित दीर्घ state, change;
	पूर्णांक bit_nr;
	पूर्णांक key_press;
	पूर्णांक row, col;
	अचिन्हित पूर्णांक keycode;

	/* Clear पूर्णांकerrupts */
	ग_लिखोl(0xFFFFFFFF, kp->base + KPICRN_OFFSET(reg_num));

	state = पढ़ोl(kp->base + KPSSRN_OFFSET(reg_num));
	change = kp->last_state[reg_num] ^ state;
	kp->last_state[reg_num] = state;

	क्रम_each_set_bit(bit_nr, &change, BITS_PER_LONG) अणु
		key_press = state & BIT(bit_nr);
		/* The meaning of SSR रेजिस्टर depends on pull mode. */
		key_press = pull_mode ? !key_press : key_press;
		row = BIT_TO_ROW_SSRN(bit_nr, reg_num);
		col = BIT_TO_COL(bit_nr);
		keycode = bcm_kp_get_keycode(kp, row, col);
		input_report_key(kp->input_dev, keycode, key_press);
	पूर्ण
पूर्ण

अटल irqवापस_t bcm_kp_isr_thपढ़ो(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा bcm_kp *kp = dev_id;
	पूर्णांक pull_mode = (kp->kpcr >> KPCR_MODE_SHIFT) & KPCR_MODE_MASK;
	पूर्णांक reg_num;

	क्रम (reg_num = 0; reg_num <= 1; reg_num++)
		bcm_kp_report_keys(kp, reg_num, pull_mode);

	input_sync(kp->input_dev);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक bcm_kp_start(काष्ठा bcm_kp *kp)
अणु
	पूर्णांक error;

	अगर (kp->clk) अणु
		error = clk_prepare_enable(kp->clk);
		अगर (error)
			वापस error;
	पूर्ण

	ग_लिखोl(kp->kpior, kp->base + KPIOR_OFFSET);

	ग_लिखोl(kp->imr0_val, kp->base + KPIMR0_OFFSET);
	ग_लिखोl(kp->imr1_val, kp->base + KPIMR1_OFFSET);

	ग_लिखोl(kp->kpemr, kp->base + KPEMR0_OFFSET);
	ग_लिखोl(kp->kpemr, kp->base + KPEMR1_OFFSET);
	ग_लिखोl(kp->kpemr, kp->base + KPEMR2_OFFSET);
	ग_लिखोl(kp->kpemr, kp->base + KPEMR3_OFFSET);

	ग_लिखोl(0xFFFFFFFF, kp->base + KPICR0_OFFSET);
	ग_लिखोl(0xFFFFFFFF, kp->base + KPICR1_OFFSET);

	kp->last_state[0] = पढ़ोl(kp->base + KPSSR0_OFFSET);
	kp->last_state[0] = पढ़ोl(kp->base + KPSSR1_OFFSET);

	ग_लिखोl(kp->kpcr | KPCR_ENABLE, kp->base + KPCR_OFFSET);

	वापस 0;
पूर्ण

अटल व्योम bcm_kp_stop(स्थिर काष्ठा bcm_kp *kp)
अणु
	u32 val;

	val = पढ़ोl(kp->base + KPCR_OFFSET);
	val &= ~KPCR_ENABLE;
	ग_लिखोl(0, kp->base + KPCR_OFFSET);
	ग_लिखोl(0, kp->base + KPIMR0_OFFSET);
	ग_लिखोl(0, kp->base + KPIMR1_OFFSET);
	ग_लिखोl(0xFFFFFFFF, kp->base + KPICR0_OFFSET);
	ग_लिखोl(0xFFFFFFFF, kp->base + KPICR1_OFFSET);

	अगर (kp->clk)
		clk_disable_unprepare(kp->clk);
पूर्ण

अटल पूर्णांक bcm_kp_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा bcm_kp *kp = input_get_drvdata(dev);

	वापस bcm_kp_start(kp);
पूर्ण

अटल व्योम bcm_kp_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा bcm_kp *kp = input_get_drvdata(dev);

	bcm_kp_stop(kp);
पूर्ण

अटल पूर्णांक bcm_kp_matrix_key_parse_dt(काष्ठा bcm_kp *kp)
अणु
	काष्ठा device *dev = kp->input_dev->dev.parent;
	काष्ठा device_node *np = dev->of_node;
	पूर्णांक error;
	अचिन्हित पूर्णांक dt_val;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक num_rows, col_mask, rows_set;

	/* Initialize the KPCR Keypad Configuration Register */
	kp->kpcr = KPCR_STATUSFILTERENABLE | KPCR_COLFILTERENABLE;

	error = matrix_keypad_parse_properties(dev, &kp->n_rows, &kp->n_cols);
	अगर (error) अणु
		dev_err(dev, "failed to parse kp params\n");
		वापस error;
	पूर्ण

	/* Set row width क्रम the ASIC block. */
	kp->kpcr |= (kp->n_rows - 1) << KPCR_ROWWIDTH_SHIFT;

	/* Set column width क्रम the ASIC block. */
	kp->kpcr |= (kp->n_cols - 1) << KPCR_COLUMNWIDTH_SHIFT;

	/* Configure the IMR रेजिस्टरs */

	/*
	 * IMR रेजिस्टरs contain पूर्णांकerrupt enable bits क्रम 8x8 matrix
	 * IMR0 रेजिस्टर क्रमmat: <row3> <row2> <row1> <row0>
	 * IMR1 रेजिस्टर क्रमmat: <row7> <row6> <row5> <row4>
	 */
	col_mask = (1 << (kp->n_cols)) - 1;
	num_rows = kp->n_rows;

	/* Set column bits in rows 0 to 3 in IMR0 */
	kp->imr0_val = col_mask;

	rows_set = 1;
	जबतक (--num_rows && rows_set++ < 4)
		kp->imr0_val |= kp->imr0_val << MAX_COLS;

	/* Set column bits in rows 4 to 7 in IMR1 */
	kp->imr1_val = 0;
	अगर (num_rows) अणु
		kp->imr1_val = col_mask;
		जबतक (--num_rows)
			kp->imr1_val |= kp->imr1_val << MAX_COLS;
	पूर्ण

	/* Initialize the KPEMR Keypress Edge Mode Registers */
	/* Trigger on both edges */
	kp->kpemr = 0;
	क्रम (i = 0; i <= 30; i += 2)
		kp->kpemr |= (KPEMR_EDGETYPE_BOTH << i);

	/*
	 * Obtain the Status filter debounce value and verअगरy against the
	 * possible values specअगरied in the DT binding.
	 */
	of_property_पढ़ो_u32(np, "status-debounce-filter-period", &dt_val);

	अगर (dt_val > KPCR_STATUSFILTERTYPE_MAX) अणु
		dev_err(dev, "Invalid Status filter debounce value %d\n",
			dt_val);
		वापस -EINVAL;
	पूर्ण

	kp->kpcr |= dt_val << KPCR_STATUSFILTERTYPE_SHIFT;

	/*
	 * Obtain the Column filter debounce value and verअगरy against the
	 * possible values specअगरied in the DT binding.
	 */
	of_property_पढ़ो_u32(np, "col-debounce-filter-period", &dt_val);

	अगर (dt_val > KPCR_COLFILTERTYPE_MAX) अणु
		dev_err(dev, "Invalid Column filter debounce value %d\n",
			dt_val);
		वापस -EINVAL;
	पूर्ण

	kp->kpcr |= dt_val << KPCR_COLFILTERTYPE_SHIFT;

	/*
	 * Determine between the row and column,
	 * which should be configured as output.
	 */
	अगर (of_property_पढ़ो_bool(np, "row-output-enabled")) अणु
		/*
		* Set RowOContrl or ColumnOContrl in KPIOR
		* to the number of pins to drive as outमाला_दो
		*/
		kp->kpior = ((1 << kp->n_rows) - 1) <<
				KPIOR_ROWOCONTRL_SHIFT;
	पूर्ण अन्यथा अणु
		kp->kpior = ((1 << kp->n_cols) - 1) <<
				KPIOR_COLUMNOCONTRL_SHIFT;
	पूर्ण

	/*
	 * Determine अगर the scan pull up needs to be enabled
	 */
	अगर (of_property_पढ़ो_bool(np, "pull-up-enabled"))
		kp->kpcr |= KPCR_MODE;

	dev_dbg(dev, "n_rows=%d n_col=%d kpcr=%x kpior=%x kpemr=%x\n",
		kp->n_rows, kp->n_cols,
		kp->kpcr, kp->kpior, kp->kpemr);

	वापस 0;
पूर्ण


अटल पूर्णांक bcm_kp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा bcm_kp *kp;
	काष्ठा input_dev *input_dev;
	काष्ठा resource *res;
	पूर्णांक error;

	kp = devm_kzalloc(&pdev->dev, माप(*kp), GFP_KERNEL);
	अगर (!kp)
		वापस -ENOMEM;

	input_dev = devm_input_allocate_device(&pdev->dev);
	अगर (!input_dev) अणु
		dev_err(&pdev->dev, "failed to allocate the input device\n");
		वापस -ENOMEM;
	पूर्ण

	__set_bit(EV_KEY, input_dev->evbit);

	/* Enable स्वतः repeat feature of Linux input subप्रणाली */
	अगर (of_property_पढ़ो_bool(pdev->dev.of_node, "autorepeat"))
		__set_bit(EV_REP, input_dev->evbit);

	input_dev->name = pdev->name;
	input_dev->phys = "keypad/input0";
	input_dev->dev.parent = &pdev->dev;
	input_dev->खोलो = bcm_kp_खोलो;
	input_dev->बंद = bcm_kp_बंद;

	input_dev->id.bustype = BUS_HOST;
	input_dev->id.venकरोr = 0x0001;
	input_dev->id.product = 0x0001;
	input_dev->id.version = 0x0100;

	input_set_drvdata(input_dev, kp);

	kp->input_dev = input_dev;

	error = bcm_kp_matrix_key_parse_dt(kp);
	अगर (error)
		वापस error;

	error = matrix_keypad_build_keymap(शून्य, शून्य,
					   kp->n_rows, kp->n_cols,
					   शून्य, input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to build keymap\n");
		वापस error;
	पूर्ण

	/* Get the KEYPAD base address */
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "Missing keypad base address resource\n");
		वापस -ENODEV;
	पूर्ण

	kp->base = devm_ioremap_resource(&pdev->dev, res);
	अगर (IS_ERR(kp->base))
		वापस PTR_ERR(kp->base);

	/* Enable घड़ी */
	kp->clk = devm_clk_get(&pdev->dev, "peri_clk");
	अगर (IS_ERR(kp->clk)) अणु
		error = PTR_ERR(kp->clk);
		अगर (error != -ENOENT) अणु
			अगर (error != -EPROBE_DEFER)
				dev_err(&pdev->dev, "Failed to get clock\n");
			वापस error;
		पूर्ण
		dev_dbg(&pdev->dev,
			"No clock specified. Assuming it's enabled\n");
		kp->clk = शून्य;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक desired_rate;
		दीर्घ actual_rate;

		error = of_property_पढ़ो_u32(pdev->dev.of_node,
					     "clock-frequency", &desired_rate);
		अगर (error < 0)
			desired_rate = DEFAULT_CLK_HZ;

		actual_rate = clk_round_rate(kp->clk, desired_rate);
		अगर (actual_rate <= 0)
			वापस -EINVAL;

		error = clk_set_rate(kp->clk, actual_rate);
		अगर (error)
			वापस error;

		error = clk_prepare_enable(kp->clk);
		अगर (error)
			वापस error;
	पूर्ण

	/* Put the kp पूर्णांकo a known sane state */
	bcm_kp_stop(kp);

	kp->irq = platक्रमm_get_irq(pdev, 0);
	अगर (kp->irq < 0)
		वापस -EINVAL;

	error = devm_request_thपढ़ोed_irq(&pdev->dev, kp->irq,
					  शून्य, bcm_kp_isr_thपढ़ो,
					  IRQF_ONESHOT, pdev->name, kp);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request IRQ\n");
		वापस error;
	पूर्ण

	error = input_रेजिस्टर_device(input_dev);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to register input device\n");
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id bcm_kp_of_match[] = अणु
	अणु .compatible = "brcm,bcm-keypad" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, bcm_kp_of_match);

अटल काष्ठा platक्रमm_driver bcm_kp_device_driver = अणु
	.probe		= bcm_kp_probe,
	.driver		= अणु
		.name	= "bcm-keypad",
		.of_match_table = of_match_ptr(bcm_kp_of_match),
	पूर्ण
पूर्ण;

module_platक्रमm_driver(bcm_kp_device_driver);

MODULE_AUTHOR("Broadcom Corporation");
MODULE_DESCRIPTION("BCM Keypad Driver");
MODULE_LICENSE("GPL v2");
