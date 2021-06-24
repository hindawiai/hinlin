<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Definitions क्रम Freescale Coldfire QSPI module
 *
 * Copyright 2010 Steven King <sfking@fdwdc.com>
*/

#अगर_अघोषित mcfqspi_h
#घोषणा mcfqspi_h

/**
 * काष्ठा mcfqspi_cs_control - chip select control क्रम the coldfire qspi driver
 * @setup: setup the control; allocate gpio's, etc. May be शून्य.
 * @tearकरोwn: finish with the control; मुक्त gpio's, etc. May be शून्य.
 * @select: output the संकेतs to select the device.  Can not be शून्य.
 * @deselect: output the संकेतs to deselect the device. Can not be शून्य.
 *
 * The QSPI module has 4 hardware chip selects.  We करोn't use them.  Instead
 * platक्रमms are required to supply a mcfqspi_cs_control as a part of the
 * platक्रमm data क्रम each QSPI master controller.  Only the select and
 * deselect functions are required.
*/
काष्ठा mcfqspi_cs_control अणु
	पूर्णांक 	(*setup)(काष्ठा mcfqspi_cs_control *);
	व्योम	(*tearकरोwn)(काष्ठा mcfqspi_cs_control *);
	व्योम	(*select)(काष्ठा mcfqspi_cs_control *, u8, bool);
	व्योम	(*deselect)(काष्ठा mcfqspi_cs_control *, u8, bool);
पूर्ण;

/**
 * काष्ठा mcfqspi_platक्रमm_data - platक्रमm data क्रम the coldfire qspi driver
 * @bus_num: board specअगरic identअगरier क्रम this qspi driver.
 * @num_chipselects: number of chip selects supported by this qspi driver.
 * @cs_control: platक्रमm dependent chip select control.
*/
काष्ठा mcfqspi_platक्रमm_data अणु
	s16	bus_num;
	u16	num_chipselect;
	काष्ठा mcfqspi_cs_control *cs_control;
पूर्ण;

#पूर्ण_अगर /* mcfqspi_h */
