<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * include/linux/mfd/wm831x/gpपन.स -- GPIO क्रम WM831x
 *
 * Copyright 2009 Wolfson Microelectronics PLC.
 *
 * Author: Mark Brown <broonie@खोलोsource.wolfsonmicro.com>
 */

#अगर_अघोषित __MFD_WM831X_GPIO_H__
#घोषणा __MFD_WM831X_GPIO_H__

/*
 * R16440-16455 (0x4038-0x4047) - GPIOx Control
 */
#घोषणा WM831X_GPN_सूची                          0x8000  /* GPN_सूची */
#घोषणा WM831X_GPN_सूची_MASK                     0x8000  /* GPN_सूची */
#घोषणा WM831X_GPN_सूची_SHIFT                        15  /* GPN_सूची */
#घोषणा WM831X_GPN_सूची_WIDTH                         1  /* GPN_सूची */
#घोषणा WM831X_GPN_PULL_MASK                    0x6000  /* GPN_PULL - [14:13] */
#घोषणा WM831X_GPN_PULL_SHIFT                       13  /* GPN_PULL - [14:13] */
#घोषणा WM831X_GPN_PULL_WIDTH                        2  /* GPN_PULL - [14:13] */
#घोषणा WM831X_GPN_INT_MODE                     0x1000  /* GPN_INT_MODE */
#घोषणा WM831X_GPN_INT_MODE_MASK                0x1000  /* GPN_INT_MODE */
#घोषणा WM831X_GPN_INT_MODE_SHIFT                   12  /* GPN_INT_MODE */
#घोषणा WM831X_GPN_INT_MODE_WIDTH                    1  /* GPN_INT_MODE */
#घोषणा WM831X_GPN_PWR_DOM                      0x0800  /* GPN_PWR_DOM */
#घोषणा WM831X_GPN_PWR_DOM_MASK                 0x0800  /* GPN_PWR_DOM */
#घोषणा WM831X_GPN_PWR_DOM_SHIFT                    11  /* GPN_PWR_DOM */
#घोषणा WM831X_GPN_PWR_DOM_WIDTH                     1  /* GPN_PWR_DOM */
#घोषणा WM831X_GPN_POL                          0x0400  /* GPN_POL */
#घोषणा WM831X_GPN_POL_MASK                     0x0400  /* GPN_POL */
#घोषणा WM831X_GPN_POL_SHIFT                        10  /* GPN_POL */
#घोषणा WM831X_GPN_POL_WIDTH                         1  /* GPN_POL */
#घोषणा WM831X_GPN_OD                           0x0200  /* GPN_OD */
#घोषणा WM831X_GPN_OD_MASK                      0x0200  /* GPN_OD */
#घोषणा WM831X_GPN_OD_SHIFT                          9  /* GPN_OD */
#घोषणा WM831X_GPN_OD_WIDTH                          1  /* GPN_OD */
#घोषणा WM831X_GPN_ENA                          0x0080  /* GPN_ENA */
#घोषणा WM831X_GPN_ENA_MASK                     0x0080  /* GPN_ENA */
#घोषणा WM831X_GPN_ENA_SHIFT                         7  /* GPN_ENA */
#घोषणा WM831X_GPN_ENA_WIDTH                         1  /* GPN_ENA */
#घोषणा WM831X_GPN_TRI                          0x0080  /* GPN_TRI */
#घोषणा WM831X_GPN_TRI_MASK                     0x0080  /* GPN_TRI */
#घोषणा WM831X_GPN_TRI_SHIFT                         7  /* GPN_TRI */
#घोषणा WM831X_GPN_TRI_WIDTH                         1  /* GPN_TRI */
#घोषणा WM831X_GPN_FN_MASK                      0x000F  /* GPN_FN - [3:0] */
#घोषणा WM831X_GPN_FN_SHIFT                          0  /* GPN_FN - [3:0] */
#घोषणा WM831X_GPN_FN_WIDTH                          4  /* GPN_FN - [3:0] */

#घोषणा WM831X_GPIO_PULL_NONE (0 << WM831X_GPN_PULL_SHIFT)
#घोषणा WM831X_GPIO_PULL_DOWN (1 << WM831X_GPN_PULL_SHIFT)
#घोषणा WM831X_GPIO_PULL_UP   (2 << WM831X_GPN_PULL_SHIFT)
#पूर्ण_अगर
