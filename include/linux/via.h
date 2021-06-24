<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Miscellaneous definitions क्रम VIA chipsets
   Currently used only by drivers/parport/parport_pc.c */

/* Values क्रम SuperIO function select configuration रेजिस्टर */
#घोषणा VIA_FUNCTION_PARPORT_SPP     0x00
#घोषणा VIA_FUNCTION_PARPORT_ECP     0x01
#घोषणा VIA_FUNCTION_PARPORT_EPP     0x02
#घोषणा VIA_FUNCTION_PARPORT_DISABLE 0x03
#घोषणा VIA_FUNCTION_PROBE           0xFF /* Special magic value to be used in code, not to be written पूर्णांकo chip */

/* Bits क्रम parallel port mode configuration रेजिस्टर */
#घोषणा VIA_PARPORT_ECPEPP 0X20
#घोषणा VIA_PARPORT_BIसूची  0x80

/* VIA configuration रेजिस्टरs */
#घोषणा VIA_CONFIG_INDEX 0x3F0
#घोषणा VIA_CONFIG_DATA  0x3F1

/* Mask क्रम parallel port IRQ bits (in ISA PnP IRQ routing रेजिस्टर 1) */
#घोषणा VIA_IRQCONTROL_PARALLEL 0xF0
/* Mask क्रम parallel port DMA bits (in ISA PnP DMA routing रेजिस्टर) */
#घोषणा VIA_DMACONTROL_PARALLEL 0x0C
