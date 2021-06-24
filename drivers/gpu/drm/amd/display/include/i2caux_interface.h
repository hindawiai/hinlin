<शैली गुरु>
/*
 * Copyright 2012-15 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#अगर_अघोषित __DAL_I2CAUX_INTERFACE_H__
#घोषणा __DAL_I2CAUX_INTERFACE_H__

#समावेश "dc_types.h"
#समावेश "gpio_service_interface.h"


#घोषणा DEFAULT_AUX_MAX_DATA_SIZE 16
#घोषणा AUX_MAX_DEFER_WRITE_RETRY 20

काष्ठा aux_payload अणु
	/* set following flag to पढ़ो/ग_लिखो I2C data,
	 * reset it to पढ़ो/ग_लिखो DPCD data */
	bool i2c_over_aux;
	/* set following flag to ग_लिखो data,
	 * reset it to पढ़ो data */
	bool ग_लिखो;
	bool mot;
	uपूर्णांक32_t address;
	uपूर्णांक32_t length;
	uपूर्णांक8_t *data;
	/*
	 * used to वापस the reply type of the transaction
	 * ignored अगर शून्य
	 */
	uपूर्णांक8_t *reply;
	/* expressed in milliseconds
	 * zero means "use default value"
	 */
	uपूर्णांक32_t defer_delay;
पूर्ण;

काष्ठा aux_command अणु
	काष्ठा aux_payload *payloads;
	uपूर्णांक8_t number_of_payloads;

	/* expressed in milliseconds
	 * zero means "use default value" */
	uपूर्णांक32_t defer_delay;

	/* zero means "use default value" */
	uपूर्णांक32_t max_defer_ग_लिखो_retry;

	क्रमागत i2c_mot_mode mot;
पूर्ण;

जोड़ aux_config अणु
	काष्ठा अणु
		uपूर्णांक32_t ALLOW_AUX_WHEN_HPD_LOW:1;
	पूर्ण bits;
	uपूर्णांक32_t raw;
पूर्ण;

#पूर्ण_अगर
