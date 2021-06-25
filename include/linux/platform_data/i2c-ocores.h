<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * i2c-ocores.h - definitions क्रम the i2c-ocores पूर्णांकerface
 *
 * Peter Korsgaard <peter@korsgaard.com>
 */

#अगर_अघोषित _LINUX_I2C_OCORES_H
#घोषणा _LINUX_I2C_OCORES_H

काष्ठा ocores_i2c_platक्रमm_data अणु
	u32 reg_shअगरt; /* रेजिस्टर offset shअगरt value */
	u32 reg_io_width; /* रेजिस्टर io पढ़ो/ग_लिखो width */
	u32 घड़ी_khz; /* input घड़ी in kHz */
	u32 bus_khz; /* bus घड़ी in kHz */
	bool big_endian; /* रेजिस्टरs are big endian */
	u8 num_devices; /* number of devices in the devices list */
	काष्ठा i2c_board_info स्थिर *devices; /* devices connected to the bus */
पूर्ण;

#पूर्ण_अगर /* _LINUX_I2C_OCORES_H */
