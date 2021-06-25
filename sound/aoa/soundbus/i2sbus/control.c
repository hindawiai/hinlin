<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * i2sbus driver -- bus control routines
 *
 * Copyright 2006 Johannes Berg <johannes@sipsolutions.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/pmac_pfunc.h>
#समावेश <यंत्र/keylargo.h>

#समावेश "i2sbus.h"

पूर्णांक i2sbus_control_init(काष्ठा macio_dev* dev, काष्ठा i2sbus_control **c)
अणु
	*c = kzalloc(माप(काष्ठा i2sbus_control), GFP_KERNEL);
	अगर (!*c)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&(*c)->list);

	(*c)->macio = dev->bus->chip;
	वापस 0;
पूर्ण

व्योम i2sbus_control_destroy(काष्ठा i2sbus_control *c)
अणु
	kमुक्त(c);
पूर्ण

/* this is serialised बाह्यally */
पूर्णांक i2sbus_control_add_dev(काष्ठा i2sbus_control *c,
			   काष्ठा i2sbus_dev *i2sdev)
अणु
	काष्ठा device_node *np;

	np = i2sdev->sound.ofdev.dev.of_node;
	i2sdev->enable = pmf_find_function(np, "enable");
	i2sdev->cell_enable = pmf_find_function(np, "cell-enable");
	i2sdev->घड़ी_enable = pmf_find_function(np, "clock-enable");
	i2sdev->cell_disable = pmf_find_function(np, "cell-disable");
	i2sdev->घड़ी_disable = pmf_find_function(np, "clock-disable");

	/* अगर the bus number is not 0 or 1 we असलolutely need to use
	 * the platक्रमm functions -- there's nothing in Darwin that
	 * would allow seeing a प्रणाली behind what the FCRs are then,
	 * and I करोn't want to go parsing a bunch of platक्रमm functions
	 * by hand to try finding a प्रणाली... */
	अगर (i2sdev->bus_number != 0 && i2sdev->bus_number != 1 &&
	    (!i2sdev->enable ||
	     !i2sdev->cell_enable || !i2sdev->घड़ी_enable ||
	     !i2sdev->cell_disable || !i2sdev->घड़ी_disable)) अणु
		pmf_put_function(i2sdev->enable);
		pmf_put_function(i2sdev->cell_enable);
		pmf_put_function(i2sdev->घड़ी_enable);
		pmf_put_function(i2sdev->cell_disable);
		pmf_put_function(i2sdev->घड़ी_disable);
		वापस -ENODEV;
	पूर्ण

	list_add(&i2sdev->item, &c->list);

	वापस 0;
पूर्ण

व्योम i2sbus_control_हटाओ_dev(काष्ठा i2sbus_control *c,
			       काष्ठा i2sbus_dev *i2sdev)
अणु
	/* this is serialised बाह्यally */
	list_del(&i2sdev->item);
	अगर (list_empty(&c->list))
		i2sbus_control_destroy(c);
पूर्ण

पूर्णांक i2sbus_control_enable(काष्ठा i2sbus_control *c,
			  काष्ठा i2sbus_dev *i2sdev)
अणु
	काष्ठा pmf_args args = अणु .count = 0 पूर्ण;
	काष्ठा macio_chip *macio = c->macio;

	अगर (i2sdev->enable)
		वापस pmf_call_one(i2sdev->enable, &args);

	अगर (macio == शून्य || macio->base == शून्य)
		वापस -ENODEV;

	चयन (i2sdev->bus_number) अणु
	हाल 0:
		/* these need to be locked or करोne through
		 * newly created feature calls! */
		MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_ENABLE);
		अवरोध;
	हाल 1:
		MACIO_BIS(KEYLARGO_FCR1, KL1_I2S1_ENABLE);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक i2sbus_control_cell(काष्ठा i2sbus_control *c,
			काष्ठा i2sbus_dev *i2sdev,
			पूर्णांक enable)
अणु
	काष्ठा pmf_args args = अणु .count = 0 पूर्ण;
	काष्ठा macio_chip *macio = c->macio;

	चयन (enable) अणु
	हाल 0:
		अगर (i2sdev->cell_disable)
			वापस pmf_call_one(i2sdev->cell_disable, &args);
		अवरोध;
	हाल 1:
		अगर (i2sdev->cell_enable)
			वापस pmf_call_one(i2sdev->cell_enable, &args);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "i2sbus: INVALID CELL ENABLE VALUE\n");
		वापस -ENODEV;
	पूर्ण

	अगर (macio == शून्य || macio->base == शून्य)
		वापस -ENODEV;

	चयन (i2sdev->bus_number) अणु
	हाल 0:
		अगर (enable)
			MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_CELL_ENABLE);
		अन्यथा
			MACIO_BIC(KEYLARGO_FCR1, KL1_I2S0_CELL_ENABLE);
		अवरोध;
	हाल 1:
		अगर (enable)
			MACIO_BIS(KEYLARGO_FCR1, KL1_I2S1_CELL_ENABLE);
		अन्यथा
			MACIO_BIC(KEYLARGO_FCR1, KL1_I2S1_CELL_ENABLE);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक i2sbus_control_घड़ी(काष्ठा i2sbus_control *c,
			 काष्ठा i2sbus_dev *i2sdev,
			 पूर्णांक enable)
अणु
	काष्ठा pmf_args args = अणु .count = 0 पूर्ण;
	काष्ठा macio_chip *macio = c->macio;

	चयन (enable) अणु
	हाल 0:
		अगर (i2sdev->घड़ी_disable)
			वापस pmf_call_one(i2sdev->घड़ी_disable, &args);
		अवरोध;
	हाल 1:
		अगर (i2sdev->घड़ी_enable)
			वापस pmf_call_one(i2sdev->घड़ी_enable, &args);
		अवरोध;
	शेष:
		prपूर्णांकk(KERN_ERR "i2sbus: INVALID CLOCK ENABLE VALUE\n");
		वापस -ENODEV;
	पूर्ण

	अगर (macio == शून्य || macio->base == शून्य)
		वापस -ENODEV;

	चयन (i2sdev->bus_number) अणु
	हाल 0:
		अगर (enable)
			MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_CLK_ENABLE_BIT);
		अन्यथा
			MACIO_BIC(KEYLARGO_FCR1, KL1_I2S0_CLK_ENABLE_BIT);
		अवरोध;
	हाल 1:
		अगर (enable)
			MACIO_BIS(KEYLARGO_FCR1, KL1_I2S1_CLK_ENABLE_BIT);
		अन्यथा
			MACIO_BIC(KEYLARGO_FCR1, KL1_I2S1_CLK_ENABLE_BIT);
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण
