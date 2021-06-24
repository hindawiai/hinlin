<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* ------------------------------------------------------------------------- */
/* adap-pcf.h i2c driver algorithms क्रम PCF8584 adapters                     */
/* ------------------------------------------------------------------------- */
/*   Copyright (C) 1995-97 Simon G. Vogl
                   1998-99 Hans Berglund

 */
/* ------------------------------------------------------------------------- */

/* With some changes from Kyथघsti Mथअlkki <kmalkki@cc.hut.fi> and even
   Froकरो Looijaard <froकरोl@dds.nl> */

#अगर_अघोषित _LINUX_I2C_ALGO_PCF_H
#घोषणा _LINUX_I2C_ALGO_PCF_H

काष्ठा i2c_algo_pcf_data अणु
	व्योम *data;		/* निजी data क्रम lolevel routines	*/
	व्योम (*setpcf) (व्योम *data, पूर्णांक ctl, पूर्णांक val);
	पूर्णांक  (*getpcf) (व्योम *data, पूर्णांक ctl);
	पूर्णांक  (*getown) (व्योम *data);
	पूर्णांक  (*अ_लोlock) (व्योम *data);
	व्योम (*रुकोक्रमpin) (व्योम *data);

	व्योम (*xfer_begin) (व्योम *data);
	व्योम (*xfer_end) (व्योम *data);

	/* Multi-master lost arbitration back-off delay (msecs)
	 * This should be set by the bus adapter or knowledgable client
	 * अगर bus is multi-mastered, अन्यथा zero
	 */
	अचिन्हित दीर्घ lab_mdelay;
पूर्ण;

पूर्णांक i2c_pcf_add_bus(काष्ठा i2c_adapter *);

#पूर्ण_अगर /* _LINUX_I2C_ALGO_PCF_H */
