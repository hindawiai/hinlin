<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995 - 1998 by Andreas Busse and Ralf Baechle
 */
#अगर_अघोषित __ASM_JAZZ_H
#घोषणा __ASM_JAZZ_H

/*
 * The addresses below are भव address. The mappings are
 * created on startup via wired entries in the tlb. The Mips
 * Magnum R3000 and R4000 machines are similar in many aspects,
 * but many hardware रेजिस्टर are accessible at 0xb9000000 in
 * instead of 0xe0000000.
 */

#घोषणा JAZZ_LOCAL_IO_SPACE	0xe0000000

/*
 * Revision numbers in PICA_ASIC_REVISION
 *
 * 0xf0000000 - Rev1
 * 0xf0000001 - Rev2
 * 0xf0000002 - Rev3
 */
#घोषणा PICA_ASIC_REVISION	0xe0000008

/*
 * The segments of the seven segment LED are mapped
 * to the control bits as follows:
 *
 *	   (7)
 *	---------
 *	|	|
 *  (2) |	| (6)
 *	|  (1)	|
 *	---------
 *	|	|
 *  (3) |	| (5)
 *	|  (4)	|
 *	--------- . (0)
 */
#घोषणा PICA_LED		0xe000f000

/*
 * Some अक्षरacters क्रम the LED control रेजिस्टरs
 * The original Mips machines seem to have a LED display
 * with पूर्णांकegrated decoder जबतक the Acer machines can
 * control each of the seven segments and the करोt independently.
 * It's only a toy, anyway...
 */
#घोषणा LED_DOT			0x01
#घोषणा LED_SPACE		0x00
#घोषणा LED_0			0xfc
#घोषणा LED_1			0x60
#घोषणा LED_2			0xda
#घोषणा LED_3			0xf2
#घोषणा LED_4			0x66
#घोषणा LED_5			0xb6
#घोषणा LED_6			0xbe
#घोषणा LED_7			0xe0
#घोषणा LED_8			0xfe
#घोषणा LED_9			0xf6
#घोषणा LED_A			0xee
#घोषणा LED_b			0x3e
#घोषणा LED_C			0x9c
#घोषणा LED_d			0x7a
#घोषणा LED_E			0x9e
#घोषणा LED_F			0x8e

#अगर_अघोषित __ASSEMBLY__

अटल __अंतरभूत__ व्योम pica_set_led(अचिन्हित पूर्णांक bits)
अणु
	अस्थिर अचिन्हित पूर्णांक *led_रेजिस्टर = (अचिन्हित पूर्णांक *) PICA_LED;

	*led_रेजिस्टर = bits;
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * Base address of the Sonic Ethernet adapter in Jazz machines.
 */
#घोषणा JAZZ_ETHERNET_BASE  0xe0001000

/*
 * Base address of the 53C94 SCSI hostadapter in Jazz machines.
 */
#घोषणा JAZZ_SCSI_BASE		0xe0002000

/*
 * i8042 keyboard controller क्रम JAZZ and PICA chipsets.
 * This address is just a guess and seems to dअगरfer from
 * other mips machines such as RC3xxx...
 */
#घोषणा JAZZ_KEYBOARD_ADDRESS	0xe0005000
#घोषणा JAZZ_KEYBOARD_DATA	0xe0005000
#घोषणा JAZZ_KEYBOARD_COMMAND	0xe0005001

#अगर_अघोषित __ASSEMBLY__

प्रकार काष्ठा अणु
	अचिन्हित अक्षर data;
	अचिन्हित अक्षर command;
पूर्ण jazz_keyboard_hardware;

#घोषणा jazz_kh ((keyboard_hardware *) JAZZ_KEYBOARD_ADDRESS)

प्रकार काष्ठा अणु
	अचिन्हित अक्षर pad0[3];
	अचिन्हित अक्षर data;
	अचिन्हित अक्षर pad1[3];
	अचिन्हित अक्षर command;
पूर्ण mips_keyboard_hardware;

/*
 * For now. Needs to be changed क्रम RC3xxx support. See below.
 */
#घोषणा keyboard_hardware	jazz_keyboard_hardware

#पूर्ण_अगर /* !__ASSEMBLY__ */

/*
 * i8042 keyboard controller क्रम most other Mips machines.
 */
#घोषणा MIPS_KEYBOARD_ADDRESS	0xb9005000
#घोषणा MIPS_KEYBOARD_DATA	0xb9005003
#घोषणा MIPS_KEYBOARD_COMMAND	0xb9005007

/*
 * Serial and parallel ports (WD 16C552) on the Mips JAZZ
 */
#घोषणा JAZZ_SERIAL1_BASE	(अचिन्हित पूर्णांक)0xe0006000
#घोषणा JAZZ_SERIAL2_BASE	(अचिन्हित पूर्णांक)0xe0007000
#घोषणा JAZZ_PARALLEL_BASE	(अचिन्हित पूर्णांक)0xe0008000

/*
 * Dummy Device Address. Used in jazzdma.c
 */
#घोषणा JAZZ_DUMMY_DEVICE	0xe000d000

/*
 * JAZZ समयr रेजिस्टरs and पूर्णांकerrupt no.
 * Note that the hardware समयr पूर्णांकerrupt is actually on
 * cpu level 6, but to keep compatibility with PC stuff
 * it is remapped to vector 0. See arch/mips/kernel/entry.S.
 */
#घोषणा JAZZ_TIMER_INTERVAL	0xe0000228
#घोषणा JAZZ_TIMER_REGISTER	0xe0000230

/*
 * DRAM configuration रेजिस्टर
 */
#अगर_अघोषित __ASSEMBLY__
#अगर_घोषित __MIPSEL__
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक bank2 : 3;
	अचिन्हित पूर्णांक bank1 : 3;
	अचिन्हित पूर्णांक mem_bus_width : 1;
	अचिन्हित पूर्णांक reserved2 : 1;
	अचिन्हित पूर्णांक page_mode : 1;
	अचिन्हित पूर्णांक reserved1 : 23;
पूर्ण dram_configuration;
#अन्यथा /* defined (__MIPSEB__) */
प्रकार काष्ठा अणु
	अचिन्हित पूर्णांक reserved1 : 23;
	अचिन्हित पूर्णांक page_mode : 1;
	अचिन्हित पूर्णांक reserved2 : 1;
	अचिन्हित पूर्णांक mem_bus_width : 1;
	अचिन्हित पूर्णांक bank1 : 3;
	अचिन्हित पूर्णांक bank2 : 3;
पूर्ण dram_configuration;
#पूर्ण_अगर
#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा PICA_DRAM_CONFIG	0xe00fffe0

/*
 * JAZZ पूर्णांकerrupt control रेजिस्टरs
 */
#घोषणा JAZZ_IO_IRQ_SOURCE	0xe0010000
#घोषणा JAZZ_IO_IRQ_ENABLE	0xe0010002

/*
 * JAZZ Interrupt Level definitions
 *
 * This is somewhat broken.  For reasons which nobody can remember anymore
 * we remap the Jazz पूर्णांकerrupts to the usual ISA style पूर्णांकerrupt numbers.
 */
#घोषणा JAZZ_IRQ_START		24
#घोषणा JAZZ_IRQ_END		(24 + 9)
#घोषणा JAZZ_PARALLEL_IRQ	(JAZZ_IRQ_START + 0)
#घोषणा JAZZ_FLOPPY_IRQ		(JAZZ_IRQ_START + 1)
#घोषणा JAZZ_SOUND_IRQ		(JAZZ_IRQ_START + 2)
#घोषणा JAZZ_VIDEO_IRQ		(JAZZ_IRQ_START + 3)
#घोषणा JAZZ_ETHERNET_IRQ	(JAZZ_IRQ_START + 4)
#घोषणा JAZZ_SCSI_IRQ		(JAZZ_IRQ_START + 5)
#घोषणा JAZZ_KEYBOARD_IRQ	(JAZZ_IRQ_START + 6)
#घोषणा JAZZ_MOUSE_IRQ		(JAZZ_IRQ_START + 7)
#घोषणा JAZZ_SERIAL1_IRQ	(JAZZ_IRQ_START + 8)
#घोषणा JAZZ_SERIAL2_IRQ	(JAZZ_IRQ_START + 9)

#घोषणा JAZZ_TIMER_IRQ		(MIPS_CPU_IRQ_BASE+6)


/*
 * JAZZ DMA Channels
 * Note: Channels 4...7 are not used with respect to the Acer PICA-61
 * chipset which करोes not provide these DMA channels.
 */
#घोषणा JAZZ_SCSI_DMA		0	       /* SCSI */
#घोषणा JAZZ_FLOPPY_DMA		1	       /* FLOPPY */
#घोषणा JAZZ_AUDIOL_DMA		2	       /* AUDIO L */
#घोषणा JAZZ_AUDIOR_DMA		3	       /* AUDIO R */

/*
 * JAZZ R4030 MCT_ADR chip (DMA controller)
 * Note: Virtual Addresses !
 */
#घोषणा JAZZ_R4030_CONFIG	0xE0000000	/* R4030 config रेजिस्टर */
#घोषणा JAZZ_R4030_REVISION	0xE0000008	/* same as PICA_ASIC_REVISION */
#घोषणा JAZZ_R4030_INV_ADDR	0xE0000010	/* Invalid Address रेजिस्टर */

#घोषणा JAZZ_R4030_TRSTBL_BASE	0xE0000018	/* Translation Table Base */
#घोषणा JAZZ_R4030_TRSTBL_LIM	0xE0000020	/* Translation Table Limit */
#घोषणा JAZZ_R4030_TRSTBL_INV	0xE0000028	/* Translation Table Invalidate */

#घोषणा JAZZ_R4030_CACHE_MTNC	0xE0000030	/* Cache Maपूर्णांकenance */
#घोषणा JAZZ_R4030_R_FAIL_ADDR	0xE0000038	/* Remote Failed Address */
#घोषणा JAZZ_R4030_M_FAIL_ADDR	0xE0000040	/* Memory Failed Address */

#घोषणा JAZZ_R4030_CACHE_PTAG	0xE0000048	/* I/O Cache Physical Tag */
#घोषणा JAZZ_R4030_CACHE_LTAG	0xE0000050	/* I/O Cache Logical Tag */
#घोषणा JAZZ_R4030_CACHE_BMASK	0xE0000058	/* I/O Cache Byte Mask */
#घोषणा JAZZ_R4030_CACHE_BWIN	0xE0000060	/* I/O Cache Buffer Winकरोw */

/*
 * Remote Speed Registers.
 *
 *  0: मुक्त,	  1: Ethernet,	2: SCSI,      3: Floppy,
 *  4: RTC,	  5: Kb./Mouse	6: serial 1,  7: serial 2,
 *  8: parallel,  9: NVRAM,    10: CPU,	     11: PROM,
 * 12: reserved, 13: मुक्त,     14: 7seg LED, 15: ???
 */
#घोषणा JAZZ_R4030_REM_SPEED	0xE0000070	/* 16 Remote Speed Registers */
						/* 0xE0000070,78,80... 0xE00000E8 */
#घोषणा JAZZ_R4030_IRQ_ENABLE	0xE00000E8	/* Internal Interrupt Enable */
#घोषणा JAZZ_R4030_INVAL_ADDR	0xE0000010	/* Invalid address Register */
#घोषणा JAZZ_R4030_IRQ_SOURCE	0xE0000200	/* Interrupt Source Register */
#घोषणा JAZZ_R4030_I386_ERROR	0xE0000208	/* i386/EISA Bus Error */

/*
 * Virtual (E)ISA controller address
 */
#घोषणा JAZZ_EISA_IRQ_ACK	0xE0000238	/* EISA पूर्णांकerrupt acknowledge */

/*
 * Access the R4030 DMA and I/O Controller
 */
#अगर_अघोषित __ASSEMBLY__

अटल अंतरभूत व्योम r4030_delay(व्योम)
अणु
__यंत्र__ __अस्थिर__(
	".set\tnoreorder\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	"nop\n\t"
	".set\treorder");
पूर्ण

अटल अंतरभूत अचिन्हित लघु r4030_पढ़ो_reg16(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित लघु ret = *((अस्थिर अचिन्हित लघु *)addr);
	r4030_delay();
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक r4030_पढ़ो_reg32(अचिन्हित दीर्घ addr)
अणु
	अचिन्हित पूर्णांक ret = *((अस्थिर अचिन्हित पूर्णांक *)addr);
	r4030_delay();
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम r4030_ग_लिखो_reg16(अचिन्हित दीर्घ addr, अचिन्हित val)
अणु
	*((अस्थिर अचिन्हित लघु *)addr) = val;
	r4030_delay();
पूर्ण

अटल अंतरभूत व्योम r4030_ग_लिखो_reg32(अचिन्हित दीर्घ addr, अचिन्हित val)
अणु
	*((अस्थिर अचिन्हित पूर्णांक *)addr) = val;
	r4030_delay();
पूर्ण

#पूर्ण_अगर /* !__ASSEMBLY__ */

#घोषणा JAZZ_FDC_BASE	0xe0003000
#घोषणा JAZZ_RTC_BASE	0xe0004000
#घोषणा JAZZ_PORT_BASE	0xe2000000

#घोषणा JAZZ_EISA_BASE	0xe3000000

#पूर्ण_अगर /* __ASM_JAZZ_H */
