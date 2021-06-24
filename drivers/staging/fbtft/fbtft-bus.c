<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/export.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gpio/consumer.h>
#समावेश <linux/spi/spi.h>
#समावेश "fbtft.h"

/*****************************************************************************
 *
 *   व्योम (*ग_लिखो_reg)(काष्ठा fbtft_par *par, पूर्णांक len, ...);
 *
 *****************************************************************************/

#घोषणा define_fbtft_ग_लिखो_reg(func, buffer_type, data_type, modअगरier)        \
व्योम func(काष्ठा fbtft_par *par, पूर्णांक len, ...)                                \
अणु                                                                             \
	बहु_सूची args;                                                         \
	पूर्णांक i, ret;                                                           \
	पूर्णांक offset = 0;                                                       \
	buffer_type *buf = (buffer_type *)par->buf;                           \
									      \
	अगर (unlikely(par->debug & DEBUG_WRITE_REGISTER)) अणु                    \
		बहु_शुरू(args, len);                                          \
		क्रम (i = 0; i < len; i++) अणु                                   \
			buf[i] = modअगरier((data_type)बहु_तर्क(args,             \
							    अचिन्हित पूर्णांक));   \
		पूर्ण                                                             \
		बहु_पूर्ण(args);                                                 \
		fbtft_par_dbg_hex(DEBUG_WRITE_REGISTER, par,                  \
				  par->info->device, buffer_type, buf, len,   \
				  "%s: ", __func__);                          \
	पूर्ण                                                                     \
									      \
	बहु_शुरू(args, len);                                                  \
									      \
	अगर (par->startbyte) अणु                                                 \
		*(u8 *)par->buf = par->startbyte;                             \
		buf = (buffer_type *)(par->buf + 1);                          \
		offset = 1;                                                   \
	पूर्ण                                                                     \
									      \
	*buf = modअगरier((data_type)बहु_तर्क(args, अचिन्हित पूर्णांक));               \
	ret = fbtft_ग_लिखो_buf_dc(par, par->buf, माप(data_type) + offset,   \
				 0);                                          \
	अगर (ret < 0)							      \
		जाओ out;						      \
	len--;                                                                \
									      \
	अगर (par->startbyte)                                                   \
		*(u8 *)par->buf = par->startbyte | 0x2;                       \
									      \
	अगर (len) अणु                                                            \
		i = len;                                                      \
		जबतक (i--)						      \
			*buf++ = modअगरier((data_type)बहु_तर्क(args,             \
							    अचिन्हित पूर्णांक));   \
		fbtft_ग_लिखो_buf_dc(par, par->buf,			      \
				   len * (माप(data_type) + offset), 1);    \
	पूर्ण                                                                     \
out:									      \
	बहु_पूर्ण(args);                                                         \
पूर्ण                                                                             \
EXPORT_SYMBOL(func);

define_fbtft_ग_लिखो_reg(fbtft_ग_लिखो_reg8_bus8, u8, u8, )
define_fbtft_ग_लिखो_reg(fbtft_ग_लिखो_reg16_bus8, __be16, u16, cpu_to_be16)
define_fbtft_ग_लिखो_reg(fbtft_ग_लिखो_reg16_bus16, u16, u16, )

व्योम fbtft_ग_लिखो_reg8_bus9(काष्ठा fbtft_par *par, पूर्णांक len, ...)
अणु
	बहु_सूची args;
	पूर्णांक i, ret;
	पूर्णांक pad = 0;
	u16 *buf = (u16 *)par->buf;

	अगर (unlikely(par->debug & DEBUG_WRITE_REGISTER)) अणु
		बहु_शुरू(args, len);
		क्रम (i = 0; i < len; i++)
			*(((u8 *)buf) + i) = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
		बहु_पूर्ण(args);
		fbtft_par_dbg_hex(DEBUG_WRITE_REGISTER, par,
				  par->info->device, u8, buf, len, "%s: ",
				  __func__);
	पूर्ण
	अगर (len <= 0)
		वापस;

	अगर (par->spi && (par->spi->bits_per_word == 8)) अणु
		/* we're emulating 9-bit, pad start of buffer with no-ops
		 * (assuming here that zero is a no-op)
		 */
		pad = (len % 4) ? 4 - (len % 4) : 0;
		क्रम (i = 0; i < pad; i++)
			*buf++ = 0x000;
	पूर्ण

	बहु_शुरू(args, len);
	*buf++ = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
	i = len - 1;
	जबतक (i--) अणु
		*buf = (u8)बहु_तर्क(args, अचिन्हित पूर्णांक);
		*buf++ |= 0x100; /* dc=1 */
	पूर्ण
	बहु_पूर्ण(args);
	ret = par->fbtftops.ग_लिखो(par, par->buf, (len + pad) * माप(u16));
	अगर (ret < 0) अणु
		dev_err(par->info->device,
			"write() failed and returned %d\n", ret);
		वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_reg8_bus9);

/*****************************************************************************
 *
 *   पूर्णांक (*ग_लिखो_vmem)(काष्ठा fbtft_par *par);
 *
 *****************************************************************************/

/* 16 bit pixel over 8-bit databus */
पूर्णांक fbtft_ग_लिखो_vmem16_bus8(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16;
	__be16 *txbuf16 = par->txbuf.buf;
	माप_प्रकार reमुख्य;
	माप_प्रकार to_copy;
	माप_प्रकार tx_array_size;
	पूर्णांक i;
	पूर्णांक ret = 0;
	माप_प्रकार startbyte_size = 0;

	fbtft_par_dbg(DEBUG_WRITE_VMEM, par, "%s(offset=%zu, len=%zu)\n",
		      __func__, offset, len);

	reमुख्य = len / 2;
	vmem16 = (u16 *)(par->info->screen_buffer + offset);

	अगर (par->gpio.dc)
		gpiod_set_value(par->gpio.dc, 1);

	/* non buffered ग_लिखो */
	अगर (!par->txbuf.buf)
		वापस par->fbtftops.ग_लिखो(par, vmem16, len);

	/* buffered ग_लिखो */
	tx_array_size = par->txbuf.len / 2;

	अगर (par->startbyte) अणु
		txbuf16 = par->txbuf.buf + 1;
		tx_array_size -= 2;
		*(u8 *)(par->txbuf.buf) = par->startbyte | 0x2;
		startbyte_size = 1;
	पूर्ण

	जबतक (reमुख्य) अणु
		to_copy = min(tx_array_size, reमुख्य);
		dev_dbg(par->info->device, "to_copy=%zu, remain=%zu\n",
			to_copy, reमुख्य - to_copy);

		क्रम (i = 0; i < to_copy; i++)
			txbuf16[i] = cpu_to_be16(vmem16[i]);

		vmem16 = vmem16 + to_copy;
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf,
						startbyte_size + to_copy * 2);
		अगर (ret < 0)
			वापस ret;
		reमुख्य -= to_copy;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_vmem16_bus8);

/* 16 bit pixel over 9-bit SPI bus: dc + high byte, dc + low byte */
पूर्णांक fbtft_ग_लिखो_vmem16_bus9(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u8 *vmem8;
	u16 *txbuf16 = par->txbuf.buf;
	माप_प्रकार reमुख्य;
	माप_प्रकार to_copy;
	माप_प्रकार tx_array_size;
	पूर्णांक i;
	पूर्णांक ret = 0;

	fbtft_par_dbg(DEBUG_WRITE_VMEM, par, "%s(offset=%zu, len=%zu)\n",
		      __func__, offset, len);

	अगर (!par->txbuf.buf) अणु
		dev_err(par->info->device, "%s: txbuf.buf is NULL\n", __func__);
		वापस -1;
	पूर्ण

	reमुख्य = len;
	vmem8 = par->info->screen_buffer + offset;

	tx_array_size = par->txbuf.len / 2;

	जबतक (reमुख्य) अणु
		to_copy = min(tx_array_size, reमुख्य);
		dev_dbg(par->info->device, "to_copy=%zu, remain=%zu\n",
			to_copy, reमुख्य - to_copy);

#अगर_घोषित __LITTLE_ENDIAN
		क्रम (i = 0; i < to_copy; i += 2) अणु
			txbuf16[i]     = 0x0100 | vmem8[i + 1];
			txbuf16[i + 1] = 0x0100 | vmem8[i];
		पूर्ण
#अन्यथा
		क्रम (i = 0; i < to_copy; i++)
			txbuf16[i]   = 0x0100 | vmem8[i];
#पूर्ण_अगर
		vmem8 = vmem8 + to_copy;
		ret = par->fbtftops.ग_लिखो(par, par->txbuf.buf, to_copy * 2);
		अगर (ret < 0)
			वापस ret;
		reमुख्य -= to_copy;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_vmem16_bus9);

पूर्णांक fbtft_ग_लिखो_vmem8_bus8(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	dev_err(par->info->device, "%s: function not implemented\n", __func__);
	वापस -1;
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_vmem8_bus8);

/* 16 bit pixel over 16-bit databus */
पूर्णांक fbtft_ग_लिखो_vmem16_bus16(काष्ठा fbtft_par *par, माप_प्रकार offset, माप_प्रकार len)
अणु
	u16 *vmem16;

	fbtft_par_dbg(DEBUG_WRITE_VMEM, par, "%s(offset=%zu, len=%zu)\n",
		      __func__, offset, len);

	vmem16 = (u16 *)(par->info->screen_buffer + offset);

	/* no need क्रम buffered ग_लिखो with 16-bit bus */
	वापस fbtft_ग_लिखो_buf_dc(par, vmem16, len, 1);
पूर्ण
EXPORT_SYMBOL(fbtft_ग_लिखो_vmem16_bus16);
