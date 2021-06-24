<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Filename: ks0108.h
 *     Version: 0.1.0
 * Description: ks0108 LCD Controller driver header
 *
 *      Author: Copyright (C) Miguel Ojeda <ojeda@kernel.org>
 *        Date: 2006-10-31
 */

#अगर_अघोषित _KS0108_H_
#घोषणा _KS0108_H_

/* Write a byte to the data port */
बाह्य व्योम ks0108_ग_लिखोdata(अचिन्हित अक्षर byte);

/* Write a byte to the control port */
बाह्य व्योम ks0108_ग_लिखोcontrol(अचिन्हित अक्षर byte);

/* Set the controller's current display state (0..1) */
बाह्य व्योम ks0108_displaystate(अचिन्हित अक्षर state);

/* Set the controller's current startline (0..63) */
बाह्य व्योम ks0108_startline(अचिन्हित अक्षर startline);

/* Set the controller's current address (0..63) */
बाह्य व्योम ks0108_address(अचिन्हित अक्षर address);

/* Set the controller's current page (0..7) */
बाह्य व्योम ks0108_page(अचिन्हित अक्षर page);

/* Is the module inited? */
बाह्य अचिन्हित अक्षर ks0108_isinited(व्योम);

#पूर्ण_अगर /* _KS0108_H_ */
