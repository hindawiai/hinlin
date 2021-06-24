<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * AD714X CapTouch Programmable Controller driver (bus पूर्णांकerfaces)
 *
 * Copyright 2009-2011 Analog Devices Inc.
 */

#अगर_अघोषित _AD714X_H_
#घोषणा _AD714X_H_

#समावेश <linux/types.h>

#घोषणा STAGE_NUM              12

काष्ठा device;
काष्ठा ad714x_platक्रमm_data;
काष्ठा ad714x_driver_data;
काष्ठा ad714x_chip;

प्रकार पूर्णांक (*ad714x_पढ़ो_t)(काष्ठा ad714x_chip *, अचिन्हित लघु, अचिन्हित लघु *, माप_प्रकार);
प्रकार पूर्णांक (*ad714x_ग_लिखो_t)(काष्ठा ad714x_chip *, अचिन्हित लघु, अचिन्हित लघु);

काष्ठा ad714x_chip अणु
	अचिन्हित लघु l_state;
	अचिन्हित लघु h_state;
	अचिन्हित लघु c_state;
	अचिन्हित लघु adc_reg[STAGE_NUM];
	अचिन्हित लघु amb_reg[STAGE_NUM];
	अचिन्हित लघु sensor_val[STAGE_NUM];

	काष्ठा ad714x_platक्रमm_data *hw;
	काष्ठा ad714x_driver_data *sw;

	पूर्णांक irq;
	काष्ठा device *dev;
	ad714x_पढ़ो_t पढ़ो;
	ad714x_ग_लिखो_t ग_लिखो;

	काष्ठा mutex mutex;

	अचिन्हित product;
	अचिन्हित version;

	__be16 xfer_buf[16] ____cacheline_aligned;

पूर्ण;

पूर्णांक ad714x_disable(काष्ठा ad714x_chip *ad714x);
पूर्णांक ad714x_enable(काष्ठा ad714x_chip *ad714x);
काष्ठा ad714x_chip *ad714x_probe(काष्ठा device *dev, u16 bus_type, पूर्णांक irq,
				 ad714x_पढ़ो_t पढ़ो, ad714x_ग_लिखो_t ग_लिखो);

#पूर्ण_अगर
