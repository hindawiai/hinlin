<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Common Definitions क्रम Janz MODULbus devices
 *
 * Copyright (c) 2010 Ira W. Snyder <iws@ovro.caltech.edu>
 */

#अगर_अघोषित JANZ_H
#घोषणा JANZ_H

काष्ठा janz_platक्रमm_data अणु
	/* MODULbus Module Number */
	अचिन्हित पूर्णांक modno;
पूर्ण;

/* PLX bridge chip onboard रेजिस्टरs */
काष्ठा janz_cmodio_onboard_regs अणु
	u8 unused1;

	/*
	 * Read access: पूर्णांकerrupt status
	 * Write access: पूर्णांकerrupt disable
	 */
	u8 पूर्णांक_disable;
	u8 unused2;

	/*
	 * Read access: MODULbus number (hex चयन)
	 * Write access: पूर्णांकerrupt enable
	 */
	u8 पूर्णांक_enable;
	u8 unused3;

	/* ग_लिखो-only */
	u8 reset_निश्चित;
	u8 unused4;

	/* ग_लिखो-only */
	u8 reset_deनिश्चित;
	u8 unused5;

	/* पढ़ो-ग_लिखो access to serial EEPROM */
	u8 eep;
	u8 unused6;

	/* ग_लिखो-only access to EEPROM chip select */
	u8 enid;
पूर्ण;

#पूर्ण_अगर /* JANZ_H */
