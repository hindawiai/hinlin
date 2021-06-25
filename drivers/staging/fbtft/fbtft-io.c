<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश "fbtft.h"

पूर्णांक fbtft_ग_लिखो_spi(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा spi_transfer t = अणु
		.tx_buf = buf,
		.len = len,
	पूर्ण;
	काष्ठा spi_message m;

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
			  "%s(len=%zu): ", __func__, len);

	अगर (!par->spi) अणु
		dev_err(par->info->device,
			"%s: par->spi is unexpectedly NULL\n", __func__);
		वापस -1;
	पूर्ण

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	वापस spi_sync(par->spi, &m);
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_spi);

/**
 * fbtft_ग_लिखो_spi_emulate_9() - ग_लिखो SPI emulating 9-bit
 * @par: Driver data
 * @buf: Buffer to ग_लिखो
 * @len: Length of buffer (must be भागisible by 8)
 *
 * When 9-bit SPI is not available, this function can be used to emulate that.
 * par->extra must hold a transक्रमmation buffer used क्रम transfer.
 */
पूर्णांक fbtft_ग_लिखो_spi_emulate_9(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	u16 *src = buf;
	u8 *dst = par->extra;
	माप_प्रकार size = len / 2;
	माप_प्रकार added = 0;
	पूर्णांक bits, i, j;
	u64 val, dc, पंचांगp;

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
			  "%s(len=%zu): ", __func__, len);

	अगर (!par->extra) अणु
		dev_err(par->info->device, "%s: error: par->extra is NULL\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	अगर ((len % 8) != 0) अणु
		dev_err(par->info->device,
			"error: len=%zu must be divisible by 8\n", len);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; i += 8) अणु
		पंचांगp = 0;
		bits = 63;
		क्रम (j = 0; j < 7; j++) अणु
			dc = (*src & 0x0100) ? 1 : 0;
			val = *src & 0x00FF;
			पंचांगp |= dc << bits;
			bits -= 8;
			पंचांगp |= val << bits--;
			src++;
		पूर्ण
		पंचांगp |= ((*src & 0x0100) ? 1 : 0);
		*(__be64 *)dst = cpu_to_be64(पंचांगp);
		dst += 8;
		*dst++ = (u8)(*src++ & 0x00FF);
		added++;
	पूर्ण

	वापस spi_ग_लिखो(par->spi, par->extra, size + added);
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_spi_emulate_9);

पूर्णांक fbtft_पढ़ो_spi(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;
	u8 txbuf[32] = अणु 0, पूर्ण;
	काष्ठा spi_transfer	t = अणु
			.speed_hz = 2000000,
			.rx_buf		= buf,
			.len		= len,
		पूर्ण;
	काष्ठा spi_message	m;

	अगर (!par->spi) अणु
		dev_err(par->info->device,
			"%s: par->spi is unexpectedly NULL\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (par->startbyte) अणु
		अगर (len > 32) अणु
			dev_err(par->info->device,
				"len=%zu can't be larger than 32 when using 'startbyte'\n",
				len);
			वापस -EINVAL;
		पूर्ण
		txbuf[0] = par->startbyte | 0x3;
		t.tx_buf = txbuf;
		fbtft_par_dbg_hex(DEBUG_READ, par, par->info->device, u8,
				  txbuf, len, "%s(len=%zu) txbuf => ",
				  __func__, len);
	पूर्ण

	spi_message_init(&m);
	spi_message_add_tail(&t, &m);
	ret = spi_sync(par->spi, &m);
	fbtft_par_dbg_hex(DEBUG_READ, par, par->info->device, u8, buf, len,
			  "%s(len=%zu) buf <= ", __func__, len);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fbtft_पढ़ो_spi);

/*
 * Optimized use of gpiolib is twice as fast as no optimization
 * only one driver can use the optimized version at a समय
 */
पूर्णांक fbtft_ग_लिखो_gpio8_wr(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	u8 data;
	पूर्णांक i;
#अगर_अघोषित DO_NOT_OPTIMIZE_FBTFT_WRITE_GPIO
	अटल u8 prev_data;
#पूर्ण_अगर

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
			  "%s(len=%zu): ", __func__, len);

	जबतक (len--) अणु
		data = *(u8 *)buf;

		/* Start writing by pulling करोwn /WR */
		gpiod_set_value(par->gpio.wr, 0);

		/* Set data */
#अगर_अघोषित DO_NOT_OPTIMIZE_FBTFT_WRITE_GPIO
		अगर (data == prev_data) अणु
			gpiod_set_value(par->gpio.wr, 0); /* used as delay */
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 8; i++) अणु
				अगर ((data & 1) != (prev_data & 1))
					gpiod_set_value(par->gpio.db[i],
							data & 1);
				data >>= 1;
				prev_data >>= 1;
			पूर्ण
		पूर्ण
#अन्यथा
		क्रम (i = 0; i < 8; i++) अणु
			gpiod_set_value(par->gpio.db[i], data & 1);
			data >>= 1;
		पूर्ण
#पूर्ण_अगर

		/* Pullup /WR */
		gpiod_set_value(par->gpio.wr, 1);

#अगर_अघोषित DO_NOT_OPTIMIZE_FBTFT_WRITE_GPIO
		prev_data = *(u8 *)buf;
#पूर्ण_अगर
		buf++;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_gpio8_wr);

पूर्णांक fbtft_ग_लिखो_gpio16_wr(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	u16 data;
	पूर्णांक i;
#अगर_अघोषित DO_NOT_OPTIMIZE_FBTFT_WRITE_GPIO
	अटल u16 prev_data;
#पूर्ण_अगर

	fbtft_par_dbg_hex(DEBUG_WRITE, par, par->info->device, u8, buf, len,
			  "%s(len=%zu): ", __func__, len);

	जबतक (len) अणु
		data = *(u16 *)buf;

		/* Start writing by pulling करोwn /WR */
		gpiod_set_value(par->gpio.wr, 0);

		/* Set data */
#अगर_अघोषित DO_NOT_OPTIMIZE_FBTFT_WRITE_GPIO
		अगर (data == prev_data) अणु
			gpiod_set_value(par->gpio.wr, 0); /* used as delay */
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < 16; i++) अणु
				अगर ((data & 1) != (prev_data & 1))
					gpiod_set_value(par->gpio.db[i],
							data & 1);
				data >>= 1;
				prev_data >>= 1;
			पूर्ण
		पूर्ण
#अन्यथा
		क्रम (i = 0; i < 16; i++) अणु
			gpiod_set_value(par->gpio.db[i], data & 1);
			data >>= 1;
		पूर्ण
#पूर्ण_अगर

		/* Pullup /WR */
		gpiod_set_value(par->gpio.wr, 1);

#अगर_अघोषित DO_NOT_OPTIMIZE_FBTFT_WRITE_GPIO
		prev_data = *(u16 *)buf;
#पूर्ण_अगर
		buf += 2;
		len -= 2;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_gpio16_wr);

पूर्णांक fbtft_ग_लिखो_gpio16_wr_latched(काष्ठा fbtft_par *par, व्योम *buf, माप_प्रकार len)
अणु
	dev_err(par->info->device, "%s: function not implemented\n", __func__);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_gpio16_wr_latched);
