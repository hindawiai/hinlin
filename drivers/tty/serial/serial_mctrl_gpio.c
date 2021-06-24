<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Helpers क्रम controlling modem lines via GPIO
 *
 * Copyright (C) 2014 Paratronic S.A.
 */

#समावेश <linux/err.h>
#समावेश <linux/device.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/termios.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/module.h>
#समावेश <linux/property.h>

#समावेश "serial_mctrl_gpio.h"

काष्ठा mctrl_gpios अणु
	काष्ठा uart_port *port;
	काष्ठा gpio_desc *gpio[UART_GPIO_MAX];
	पूर्णांक irq[UART_GPIO_MAX];
	अचिन्हित पूर्णांक mctrl_prev;
	bool mctrl_on;
पूर्ण;

अटल स्थिर काष्ठा अणु
	स्थिर अक्षर *name;
	अचिन्हित पूर्णांक mctrl;
	क्रमागत gpiod_flags flags;
पूर्ण mctrl_gpios_desc[UART_GPIO_MAX] = अणु
	अणु "cts", TIOCM_CTS, GPIOD_IN, पूर्ण,
	अणु "dsr", TIOCM_DSR, GPIOD_IN, पूर्ण,
	अणु "dcd", TIOCM_CD,  GPIOD_IN, पूर्ण,
	अणु "rng", TIOCM_RNG, GPIOD_IN, पूर्ण,
	अणु "rts", TIOCM_RTS, GPIOD_OUT_LOW, पूर्ण,
	अणु "dtr", TIOCM_DTR, GPIOD_OUT_LOW, पूर्ण,
पूर्ण;

अटल bool mctrl_gpio_flags_is_dir_out(अचिन्हित पूर्णांक idx)
अणु
	वापस mctrl_gpios_desc[idx].flags & GPIOD_FLAGS_BIT_सूची_OUT;
पूर्ण

व्योम mctrl_gpio_set(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक mctrl)
अणु
	क्रमागत mctrl_gpio_idx i;
	काष्ठा gpio_desc *desc_array[UART_GPIO_MAX];
	DECLARE_BITMAP(values, UART_GPIO_MAX);
	अचिन्हित पूर्णांक count = 0;

	अगर (gpios == शून्य)
		वापस;

	क्रम (i = 0; i < UART_GPIO_MAX; i++)
		अगर (gpios->gpio[i] && mctrl_gpio_flags_is_dir_out(i)) अणु
			desc_array[count] = gpios->gpio[i];
			__assign_bit(count, values,
				     mctrl & mctrl_gpios_desc[i].mctrl);
			count++;
		पूर्ण
	gpiod_set_array_value(count, desc_array, शून्य, values);
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_set);

काष्ठा gpio_desc *mctrl_gpio_to_gpiod(काष्ठा mctrl_gpios *gpios,
				      क्रमागत mctrl_gpio_idx gidx)
अणु
	अगर (gpios == शून्य)
		वापस शून्य;

	वापस gpios->gpio[gidx];
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_to_gpiod);

अचिन्हित पूर्णांक mctrl_gpio_get(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक *mctrl)
अणु
	क्रमागत mctrl_gpio_idx i;

	अगर (gpios == शून्य)
		वापस *mctrl;

	क्रम (i = 0; i < UART_GPIO_MAX; i++) अणु
		अगर (gpios->gpio[i] && !mctrl_gpio_flags_is_dir_out(i)) अणु
			अगर (gpiod_get_value(gpios->gpio[i]))
				*mctrl |= mctrl_gpios_desc[i].mctrl;
			अन्यथा
				*mctrl &= ~mctrl_gpios_desc[i].mctrl;
		पूर्ण
	पूर्ण

	वापस *mctrl;
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_get);

अचिन्हित पूर्णांक
mctrl_gpio_get_outमाला_दो(काष्ठा mctrl_gpios *gpios, अचिन्हित पूर्णांक *mctrl)
अणु
	क्रमागत mctrl_gpio_idx i;

	अगर (gpios == शून्य)
		वापस *mctrl;

	क्रम (i = 0; i < UART_GPIO_MAX; i++) अणु
		अगर (gpios->gpio[i] && mctrl_gpio_flags_is_dir_out(i)) अणु
			अगर (gpiod_get_value(gpios->gpio[i]))
				*mctrl |= mctrl_gpios_desc[i].mctrl;
			अन्यथा
				*mctrl &= ~mctrl_gpios_desc[i].mctrl;
		पूर्ण
	पूर्ण

	वापस *mctrl;
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_get_outमाला_दो);

काष्ठा mctrl_gpios *mctrl_gpio_init_noस्वतः(काष्ठा device *dev, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा mctrl_gpios *gpios;
	क्रमागत mctrl_gpio_idx i;

	gpios = devm_kzalloc(dev, माप(*gpios), GFP_KERNEL);
	अगर (!gpios)
		वापस ERR_PTR(-ENOMEM);

	क्रम (i = 0; i < UART_GPIO_MAX; i++) अणु
		अक्षर *gpio_str;
		bool present;

		/* Check अगर GPIO property exists and जारी अगर not */
		gpio_str = kaप्र_लिखो(GFP_KERNEL, "%s-gpios",
				     mctrl_gpios_desc[i].name);
		अगर (!gpio_str)
			जारी;

		present = device_property_present(dev, gpio_str);
		kमुक्त(gpio_str);
		अगर (!present)
			जारी;

		gpios->gpio[i] =
			devm_gpiod_get_index_optional(dev,
						      mctrl_gpios_desc[i].name,
						      idx,
						      mctrl_gpios_desc[i].flags);

		अगर (IS_ERR(gpios->gpio[i]))
			वापस ERR_CAST(gpios->gpio[i]);
	पूर्ण

	वापस gpios;
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_init_noस्वतः);

#घोषणा MCTRL_ANY_DELTA (TIOCM_RI | TIOCM_DSR | TIOCM_CD | TIOCM_CTS)
अटल irqवापस_t mctrl_gpio_irq_handle(पूर्णांक irq, व्योम *context)
अणु
	काष्ठा mctrl_gpios *gpios = context;
	काष्ठा uart_port *port = gpios->port;
	u32 mctrl = gpios->mctrl_prev;
	u32 mctrl_dअगरf;
	अचिन्हित दीर्घ flags;

	mctrl_gpio_get(gpios, &mctrl);

	spin_lock_irqsave(&port->lock, flags);

	mctrl_dअगरf = mctrl ^ gpios->mctrl_prev;
	gpios->mctrl_prev = mctrl;

	अगर (mctrl_dअगरf & MCTRL_ANY_DELTA && port->state != शून्य) अणु
		अगर ((mctrl_dअगरf & mctrl) & TIOCM_RI)
			port->icount.rng++;

		अगर ((mctrl_dअगरf & mctrl) & TIOCM_DSR)
			port->icount.dsr++;

		अगर (mctrl_dअगरf & TIOCM_CD)
			uart_handle_dcd_change(port, mctrl & TIOCM_CD);

		अगर (mctrl_dअगरf & TIOCM_CTS)
			uart_handle_cts_change(port, mctrl & TIOCM_CTS);

		wake_up_पूर्णांकerruptible(&port->state->port.delta_msr_रुको);
	पूर्ण

	spin_unlock_irqrestore(&port->lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

काष्ठा mctrl_gpios *mctrl_gpio_init(काष्ठा uart_port *port, अचिन्हित पूर्णांक idx)
अणु
	काष्ठा mctrl_gpios *gpios;
	क्रमागत mctrl_gpio_idx i;

	gpios = mctrl_gpio_init_noस्वतः(port->dev, idx);
	अगर (IS_ERR(gpios))
		वापस gpios;

	gpios->port = port;

	क्रम (i = 0; i < UART_GPIO_MAX; ++i) अणु
		पूर्णांक ret;

		अगर (!gpios->gpio[i] || mctrl_gpio_flags_is_dir_out(i))
			जारी;

		ret = gpiod_to_irq(gpios->gpio[i]);
		अगर (ret < 0) अणु
			dev_err(port->dev,
				"failed to find corresponding irq for %s (idx=%d, err=%d)\n",
				mctrl_gpios_desc[i].name, idx, ret);
			वापस ERR_PTR(ret);
		पूर्ण
		gpios->irq[i] = ret;

		/* irqs should only be enabled in .enable_ms */
		irq_set_status_flags(gpios->irq[i], IRQ_NOAUTOEN);

		ret = devm_request_irq(port->dev, gpios->irq[i],
				       mctrl_gpio_irq_handle,
				       IRQ_TYPE_EDGE_BOTH, dev_name(port->dev),
				       gpios);
		अगर (ret) अणु
			/* alternatively implement polling */
			dev_err(port->dev,
				"failed to request irq for %s (idx=%d, err=%d)\n",
				mctrl_gpios_desc[i].name, idx, ret);
			वापस ERR_PTR(ret);
		पूर्ण
	पूर्ण

	वापस gpios;
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_init);

व्योम mctrl_gpio_मुक्त(काष्ठा device *dev, काष्ठा mctrl_gpios *gpios)
अणु
	क्रमागत mctrl_gpio_idx i;

	अगर (gpios == शून्य)
		वापस;

	क्रम (i = 0; i < UART_GPIO_MAX; i++) अणु
		अगर (gpios->irq[i])
			devm_मुक्त_irq(gpios->port->dev, gpios->irq[i], gpios);

		अगर (gpios->gpio[i])
			devm_gpiod_put(dev, gpios->gpio[i]);
	पूर्ण
	devm_kमुक्त(dev, gpios);
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_मुक्त);

व्योम mctrl_gpio_enable_ms(काष्ठा mctrl_gpios *gpios)
अणु
	क्रमागत mctrl_gpio_idx i;

	अगर (gpios == शून्य)
		वापस;

	/* .enable_ms may be called multiple बार */
	अगर (gpios->mctrl_on)
		वापस;

	gpios->mctrl_on = true;

	/* get initial status of modem lines GPIOs */
	mctrl_gpio_get(gpios, &gpios->mctrl_prev);

	क्रम (i = 0; i < UART_GPIO_MAX; ++i) अणु
		अगर (!gpios->irq[i])
			जारी;

		enable_irq(gpios->irq[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_enable_ms);

व्योम mctrl_gpio_disable_ms(काष्ठा mctrl_gpios *gpios)
अणु
	क्रमागत mctrl_gpio_idx i;

	अगर (gpios == शून्य)
		वापस;

	अगर (!gpios->mctrl_on)
		वापस;

	gpios->mctrl_on = false;

	क्रम (i = 0; i < UART_GPIO_MAX; ++i) अणु
		अगर (!gpios->irq[i])
			जारी;

		disable_irq(gpios->irq[i]);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(mctrl_gpio_disable_ms);

MODULE_LICENSE("GPL");
