<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * eisa_eeprom.h - provide support क्रम EISA adapters in PA-RISC machines
 *
 * Copyright (c) 2001, 2002 Daniel Engstrom <5116@telia.com>
 */

#अगर_अघोषित ASM_EISA_EEPROM_H
#घोषणा ASM_EISA_EEPROM_H

बाह्य व्योम __iomem *eisa_eeprom_addr;

#घोषणा HPEE_MAX_LENGTH       0x2000	/* maximum eeprom length */

#घोषणा HPEE_SLOT_INFO(slot) (20+(48*slot))

काष्ठा eeprom_header 
अणु
   
	u_पूर्णांक32_t num_ग_लिखोs;       /* number of ग_लिखोs */
 	u_पूर्णांक8_t  flags;            /* flags, usage? */
	u_पूर्णांक8_t  ver_maj;
	u_पूर्णांक8_t  ver_min;
	u_पूर्णांक8_t  num_slots;        /* number of EISA slots in प्रणाली */
	u_पूर्णांक16_t csum;             /* checksum, I करोn't know how to calculate this */
	u_पूर्णांक8_t  pad[10];
पूर्ण __attribute__ ((packed));


काष्ठा eeprom_eisa_slot_info
अणु
	u_पूर्णांक32_t eisa_slot_id;
	u_पूर्णांक32_t config_data_offset;
	u_पूर्णांक32_t num_ग_लिखोs;
	u_पूर्णांक16_t csum;
	u_पूर्णांक16_t num_functions;
	u_पूर्णांक16_t config_data_length;
	
	/* bits 0..3 are the duplicate slot id */ 
#घोषणा HPEE_SLOT_INFO_EMBEDDED  0x10
#घोषणा HPEE_SLOT_INFO_VIRTUAL   0x20
#घोषणा HPEE_SLOT_INFO_NO_READID 0x40
#घोषणा HPEE_SLOT_INFO_DUPLICATE 0x80
	u_पूर्णांक8_t slot_info;
	
#घोषणा HPEE_SLOT_FEATURES_ENABLE         0x01
#घोषणा HPEE_SLOT_FEATURES_IOCHK          0x02
#घोषणा HPEE_SLOT_FEATURES_CFG_INCOMPLETE 0x80
	u_पूर्णांक8_t slot_features;
	
	u_पूर्णांक8_t  ver_min;
	u_पूर्णांक8_t  ver_maj;
	
#घोषणा HPEE_FUNCTION_INFO_HAVE_TYPE      0x01
#घोषणा HPEE_FUNCTION_INFO_HAVE_MEMORY    0x02
#घोषणा HPEE_FUNCTION_INFO_HAVE_IRQ       0x04
#घोषणा HPEE_FUNCTION_INFO_HAVE_DMA       0x08
#घोषणा HPEE_FUNCTION_INFO_HAVE_PORT      0x10
#घोषणा HPEE_FUNCTION_INFO_HAVE_PORT_INIT 0x20
/* I think there are two slighty dअगरferent 
 * versions of the function_info field 
 * one पूर्णांक the fixed header and one optional 
 * in the parsed slot data area */
#घोषणा HPEE_FUNCTION_INFO_HAVE_FUNCTION  0x01
#घोषणा HPEE_FUNCTION_INFO_F_DISABLED     0x80
#घोषणा HPEE_FUNCTION_INFO_CFG_FREE_FORM  0x40
	u_पूर्णांक8_t  function_info;

#घोषणा HPEE_FLAG_BOARD_IS_ISA		  0x01 /* flag and minor version क्रम isa board */
	u_पूर्णांक8_t  flags;
	u_पूर्णांक8_t  pad[24];
पूर्ण __attribute__ ((packed));


#घोषणा HPEE_MEMORY_MAX_ENT   9
/* memory descriptor: byte 0 */
#घोषणा HPEE_MEMORY_WRITABLE  0x01
#घोषणा HPEE_MEMORY_CACHABLE  0x02
#घोषणा HPEE_MEMORY_TYPE_MASK 0x18
#घोषणा HPEE_MEMORY_TYPE_SYS  0x00
#घोषणा HPEE_MEMORY_TYPE_EXP  0x08
#घोषणा HPEE_MEMORY_TYPE_VIR  0x10
#घोषणा HPEE_MEMORY_TYPE_OTH  0x18
#घोषणा HPEE_MEMORY_SHARED    0x20
#घोषणा HPEE_MEMORY_MORE      0x80

/* memory descriptor: byte 1 */
#घोषणा HPEE_MEMORY_WIDTH_MASK 0x03
#घोषणा HPEE_MEMORY_WIDTH_BYTE 0x00
#घोषणा HPEE_MEMORY_WIDTH_WORD 0x01
#घोषणा HPEE_MEMORY_WIDTH_DWORD 0x02
#घोषणा HPEE_MEMORY_DECODE_MASK 0x0c
#घोषणा HPEE_MEMORY_DECODE_20BITS 0x00
#घोषणा HPEE_MEMORY_DECODE_24BITS 0x04
#घोषणा HPEE_MEMORY_DECODE_32BITS 0x08
/* byte 2 and 3 are a 16bit LE value
 * containing the memory size in kilobytes */
/* byte 4,5,6 are a 24bit LE value
 * containing the memory base address */


#घोषणा HPEE_IRQ_MAX_ENT      7
/* Interrupt entry: byte 0 */
#घोषणा HPEE_IRQ_CHANNEL_MASK 0xf
#घोषणा HPEE_IRQ_TRIG_LEVEL   0x20
#घोषणा HPEE_IRQ_MORE         0x80
/* byte 1 seems to be unused */

#घोषणा HPEE_DMA_MAX_ENT     4

/* dma entry: byte 0 */
#घोषणा HPEE_DMA_CHANNEL_MASK 7
#घोषणा HPEE_DMA_SIZE_MASK	0xc
#घोषणा HPEE_DMA_SIZE_BYTE	0x0
#घोषणा HPEE_DMA_SIZE_WORD	0x4
#घोषणा HPEE_DMA_SIZE_DWORD	0x8
#घोषणा HPEE_DMA_SHARED      0x40
#घोषणा HPEE_DMA_MORE        0x80

/* dma entry: byte 1 */
#घोषणा HPEE_DMA_TIMING_MASK 0x30
#घोषणा HPEE_DMA_TIMING_ISA	0x0
#घोषणा HPEE_DMA_TIMING_TYPEA 0x10
#घोषणा HPEE_DMA_TIMING_TYPEB 0x20
#घोषणा HPEE_DMA_TIMING_TYPEC 0x30

#घोषणा HPEE_PORT_MAX_ENT 20
/* port entry byte 0 */
#घोषणा HPEE_PORT_SIZE_MASK 0x1f
#घोषणा HPEE_PORT_SHARED    0x40
#घोषणा HPEE_PORT_MORE      0x80
/* byte 1 and 2 is a 16bit LE value
 * containing the start port number */

#घोषणा HPEE_PORT_INIT_MAX_LEN     60 /* in bytes here */
/* port init entry byte 0 */
#घोषणा HPEE_PORT_INIT_WIDTH_MASK  0x3
#घोषणा HPEE_PORT_INIT_WIDTH_BYTE  0x0
#घोषणा HPEE_PORT_INIT_WIDTH_WORD  0x1
#घोषणा HPEE_PORT_INIT_WIDTH_DWORD 0x2
#घोषणा HPEE_PORT_INIT_MASK        0x4
#घोषणा HPEE_PORT_INIT_MORE        0x80

#घोषणा HPEE_SELECTION_MAX_ENT 26

#घोषणा HPEE_TYPE_MAX_LEN    80

#पूर्ण_अगर
