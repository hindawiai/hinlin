<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *    Filename: cfag12864b.h
 *     Version: 0.1.0
 * Description: cfag12864b LCD driver header
 *
 *      Author: Copyright (C) Miguel Ojeda <ojeda@kernel.org>
 *        Date: 2006-10-12
 */

#अगर_अघोषित _CFAG12864B_H_
#घोषणा _CFAG12864B_H_

#घोषणा CFAG12864B_WIDTH	(128)
#घोषणा CFAG12864B_HEIGHT	(64)
#घोषणा CFAG12864B_CONTROLLERS	(2)
#घोषणा CFAG12864B_PAGES	(8)
#घोषणा CFAG12864B_ADDRESSES	(64)
#घोषणा CFAG12864B_SIZE		((CFAG12864B_CONTROLLERS) * \
				(CFAG12864B_PAGES) * \
				(CFAG12864B_ADDRESSES))

/*
 * The driver will blit this buffer to the LCD
 *
 * Its size is CFAG12864B_SIZE.
 */
बाह्य अचिन्हित अक्षर * cfag12864b_buffer;

/*
 * Get the refresh rate of the LCD
 *
 * Returns the refresh rate (hertz).
 */
बाह्य अचिन्हित पूर्णांक cfag12864b_getrate(व्योम);

/*
 * Enable refreshing
 *
 * Returns 0 अगर successful (anyone was using it),
 * or != 0 अगर failed (someone is using it).
 */
बाह्य अचिन्हित अक्षर cfag12864b_enable(व्योम);

/*
 * Disable refreshing
 *
 * You should call this only when you finish using the LCD.
 */
बाह्य व्योम cfag12864b_disable(व्योम);

/*
 * Is enabled refreshing? (is anyone using the module?)
 *
 * Returns 0 अगर refreshing is not enabled (anyone is using it),
 * or != 0 अगर refreshing is enabled (someone is using it).
 *
 * Useful क्रम buffer पढ़ो-only modules.
 */
बाह्य अचिन्हित अक्षर cfag12864b_isenabled(व्योम);

/*
 * Is the module inited?
 */
बाह्य अचिन्हित अक्षर cfag12864b_isinited(व्योम);

#पूर्ण_अगर /* _CFAG12864B_H_ */

