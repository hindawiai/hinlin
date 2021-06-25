<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Q40 master Chip Control
 * RTC stuff merged क्रम compactness.
*/

#अगर_अघोषित _Q40_MASTER_H
#घोषणा _Q40_MASTER_H

#समावेश <यंत्र/raw_पन.स>
#समावेश <यंत्र/kmap.h>

#घोषणा q40_master_addr 0xff000000

#घोषणा IIRQ_REG            0x0       /* पूर्णांकernal IRQ reg */
#घोषणा EIRQ_REG            0x4       /* बाह्यal ... */
#घोषणा KEYCODE_REG         0x1c      /* value of received scancode  */
#घोषणा DISPLAY_CONTROL_REG 0x18
#घोषणा FRAME_CLEAR_REG     0x24
#घोषणा LED_REG             0x30

#घोषणा Q40_LED_ON()        master_outb(1,LED_REG)
#घोषणा Q40_LED_OFF()       master_outb(0,LED_REG)

#घोषणा INTERRUPT_REG       IIRQ_REG  /* "native" पूर्णांकs */
#घोषणा KEY_IRQ_ENABLE_REG  0x08      /**/
#घोषणा KEYBOARD_UNLOCK_REG 0x20      /* clear kb पूर्णांक */

#घोषणा SAMPLE_ENABLE_REG   0x14      /* generate SAMPLE पूर्णांकs */
#घोषणा SAMPLE_RATE_REG     0x2c
#घोषणा SAMPLE_CLEAR_REG    0x28
#घोषणा SAMPLE_LOW          0x00
#घोषणा SAMPLE_HIGH         0x01

#घोषणा FRAME_RATE_REG       0x38      /* generate FRAME पूर्णांकs at 200 HZ rate */

#अगर 0
#घोषणा SER_ENABLE_REG      0x0c      /* allow serial पूर्णांकs to be generated */
#पूर्ण_अगर
#घोषणा EXT_ENABLE_REG      0x10      /* ... rest of the ISA पूर्णांकs ... */


#घोषणा master_inb(_reg_)      in_8((अचिन्हित अक्षर *)q40_master_addr+_reg_)
#घोषणा master_outb(_b_,_reg_)  out_8((अचिन्हित अक्षर *)q40_master_addr+_reg_,_b_)

/* RTC defines */

#घोषणा Q40_RTC_BASE	    (0xff021ffc)

#घोषणा Q40_RTC_YEAR        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE+0))
#घोषणा Q40_RTC_MNTH        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-4))
#घोषणा Q40_RTC_DATE        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-8))
#घोषणा Q40_RTC_DOW         (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-12))
#घोषणा Q40_RTC_HOUR        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-16))
#घोषणा Q40_RTC_MINS        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-20))
#घोषणा Q40_RTC_SECS        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-24))
#घोषणा Q40_RTC_CTRL        (*(अस्थिर अचिन्हित अक्षर *)(Q40_RTC_BASE-28))

/* some control bits */
#घोषणा Q40_RTC_READ   64  /* prepare क्रम पढ़ोing */
#घोषणा Q40_RTC_WRITE  128

/* define some Q40 specअगरic पूर्णांकs */
#समावेश <यंत्र/q40पूर्णांकs.h>

/* misc defs */
#घोषणा DAC_LEFT  ((अचिन्हित अक्षर *)0xff008000)
#घोषणा DAC_RIGHT ((अचिन्हित अक्षर *)0xff008004)

#पूर्ण_अगर /* _Q40_MASTER_H */
