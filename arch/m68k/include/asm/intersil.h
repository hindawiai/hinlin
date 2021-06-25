<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SUN3_INTERSIL_H
#घोषणा _SUN3_INTERSIL_H
/* bits 0 and 1 */
#घोषणा INTERSIL_FREQ_32K        0x00
#घोषणा INTERSIL_FREQ_1M         0x01
#घोषणा INTERSIL_FREQ_2M         0x02
#घोषणा INTERSIL_FREQ_4M         0x03

/* bit 2 */
#घोषणा INTERSIL_12H_MODE   0x00
#घोषणा INTERSIL_24H_MODE   0x04

/* bit 3 */
#घोषणा INTERSIL_STOP            0x00
#घोषणा INTERSIL_RUN             0x08

/* bit 4 */
#घोषणा INTERSIL_INT_ENABLE     0x10
#घोषणा INTERSIL_INT_DISABLE    0x00

/* bit 5 */
#घोषणा INTERSIL_MODE_NORMAL     0x00
#घोषणा INTERSIL_MODE_TEST       0x20

#घोषणा INTERSIL_HZ_100_MASK	 0x02

काष्ठा पूर्णांकersil_dt अणु
	अचिन्हित अक्षर	csec;
	अचिन्हित अक्षर	hour;
	अचिन्हित अक्षर	minute;
	अचिन्हित अक्षर	second;
	अचिन्हित अक्षर	month;
	अचिन्हित अक्षर	day;
	अचिन्हित अक्षर	year;
	अचिन्हित अक्षर	weekday;
पूर्ण;

काष्ठा पूर्णांकersil_7170 अणु
	काष्ठा पूर्णांकersil_dt counter;
	काष्ठा पूर्णांकersil_dt alarm;
	अचिन्हित अक्षर	पूर्णांक_reg;
	अचिन्हित अक्षर	cmd_reg;
पूर्ण;

बाह्य अस्थिर अक्षर* घड़ी_va;
#घोषणा पूर्णांकersil_घड़ी ((अस्थिर काष्ठा पूर्णांकersil_7170 *) घड़ी_va)
#घोषणा पूर्णांकersil_clear() (व्योम)पूर्णांकersil_घड़ी->पूर्णांक_reg
#पूर्ण_अगर
