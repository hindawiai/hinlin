<शैली गुरु>
/*
 * drivers/video/fb_ddc.c - DDC/EDID पढ़ो support.
 *
 *  Copyright (C) 2006 Dennis Munsie <dmunsie@cecropia.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/fb.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/slab.h>

#समावेश "../edid.h"

#घोषणा DDC_ADDR	0x50

अटल अचिन्हित अक्षर *fb_करो_probe_ddc_edid(काष्ठा i2c_adapter *adapter)
अणु
	अचिन्हित अक्षर start = 0x0;
	अचिन्हित अक्षर *buf = kदो_स्मृति(EDID_LENGTH, GFP_KERNEL);
	काष्ठा i2c_msg msgs[] = अणु
		अणु
			.addr	= DDC_ADDR,
			.flags	= 0,
			.len	= 1,
			.buf	= &start,
		पूर्ण, अणु
			.addr	= DDC_ADDR,
			.flags	= I2C_M_RD,
			.len	= EDID_LENGTH,
			.buf	= buf,
		पूर्ण
	पूर्ण;

	अगर (!buf) अणु
		dev_warn(&adapter->dev, "unable to allocate memory for EDID "
			 "block.\n");
		वापस शून्य;
	पूर्ण

	अगर (i2c_transfer(adapter, msgs, 2) == 2)
		वापस buf;

	dev_warn(&adapter->dev, "unable to read EDID block.\n");
	kमुक्त(buf);
	वापस शून्य;
पूर्ण

अचिन्हित अक्षर *fb_ddc_पढ़ो(काष्ठा i2c_adapter *adapter)
अणु
	काष्ठा i2c_algo_bit_data *algo_data = adapter->algo_data;
	अचिन्हित अक्षर *edid = शून्य;
	पूर्णांक i, j;

	algo_data->setscl(algo_data->data, 1);

	क्रम (i = 0; i < 3; i++) अणु
		/* For some old monitors we need the
		 * following process to initialize/stop DDC
		 */
		algo_data->setsda(algo_data->data, 1);
		msleep(13);

		algo_data->setscl(algo_data->data, 1);
		अगर (algo_data->माला_लोcl) अणु
			क्रम (j = 0; j < 5; j++) अणु
				msleep(10);
				अगर (algo_data->माला_लोcl(algo_data->data))
					अवरोध;
			पूर्ण
			अगर (j == 5)
				जारी;
		पूर्ण अन्यथा अणु
			udelay(algo_data->udelay);
		पूर्ण

		algo_data->setsda(algo_data->data, 0);
		msleep(15);
		algo_data->setscl(algo_data->data, 0);
		msleep(15);
		algo_data->setsda(algo_data->data, 1);
		msleep(15);

		/* Do the real work */
		edid = fb_करो_probe_ddc_edid(adapter);
		algo_data->setsda(algo_data->data, 0);
		algo_data->setscl(algo_data->data, 0);
		msleep(15);

		algo_data->setscl(algo_data->data, 1);
		अगर (algo_data->माला_लोcl) अणु
			क्रम (j = 0; j < 10; j++) अणु
				msleep(10);
				अगर (algo_data->माला_लोcl(algo_data->data))
					अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			udelay(algo_data->udelay);
		पूर्ण

		algo_data->setsda(algo_data->data, 1);
		msleep(15);
		algo_data->setscl(algo_data->data, 0);
		algo_data->setsda(algo_data->data, 0);
		अगर (edid)
			अवरोध;
	पूर्ण
	/* Release the DDC lines when करोne or the Apple Cinema HD display
	 * will चयन off
	 */
	algo_data->setsda(algo_data->data, 1);
	algo_data->setscl(algo_data->data, 1);

	adapter->class |= I2C_CLASS_DDC;
	वापस edid;
पूर्ण

EXPORT_SYMBOL_GPL(fb_ddc_पढ़ो);

MODULE_AUTHOR("Dennis Munsie <dmunsie@cecropia.com>");
MODULE_DESCRIPTION("DDC/EDID reading support");
MODULE_LICENSE("GPL");
