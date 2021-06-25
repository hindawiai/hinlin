<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Setup क्रम the SMSC FDC37C93xAPM
 *
 * Copyright (C) 2003 Sean McGoogan (Sean.McGoogan@superh.com)
 * Copyright (C) 2003, 2004 SuperH, Inc.
 * Copyright (C) 2004, 2005 Paul Mundt
 *
 * SuperH SH4-202 MicroDev board support.
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पन.स>
#समावेश <linux/err.h>
#समावेश <mach/microdev.h>

#घोषणा SMSC_CONFIG_PORT_ADDR	 (0x3F0)
#घोषणा SMSC_INDEX_PORT_ADDR	 SMSC_CONFIG_PORT_ADDR
#घोषणा SMSC_DATA_PORT_ADDR	 (SMSC_INDEX_PORT_ADDR + 1)

#घोषणा SMSC_ENTER_CONFIG_KEY	 0x55
#घोषणा SMSC_EXIT_CONFIG_KEY	 0xaa

#घोषणा SMCS_LOGICAL_DEV_INDEX	 0x07	/* Logical Device Number */
#घोषणा SMSC_DEVICE_ID_INDEX	 0x20	/* Device ID */
#घोषणा SMSC_DEVICE_REV_INDEX	 0x21	/* Device Revision */
#घोषणा SMSC_ACTIVATE_INDEX	 0x30	/* Activate */
#घोषणा SMSC_PRIMARY_BASE_INDEX	 0x60	/* Primary Base Address */
#घोषणा SMSC_SECONDARY_BASE_INDEX 0x62	/* Secondary Base Address */
#घोषणा SMSC_PRIMARY_INT_INDEX	 0x70	/* Primary Interrupt Select */
#घोषणा SMSC_SECONDARY_INT_INDEX 0x72	/* Secondary Interrupt Select */
#घोषणा SMSC_HDCS0_INDEX	 0xf0	/* HDCS0 Address Decoder */
#घोषणा SMSC_HDCS1_INDEX	 0xf1	/* HDCS1 Address Decoder */

#घोषणा SMSC_IDE1_DEVICE	1	/* IDE #1 logical device */
#घोषणा SMSC_IDE2_DEVICE	2	/* IDE #2 logical device */
#घोषणा SMSC_PARALLEL_DEVICE	3	/* Parallel Port logical device */
#घोषणा SMSC_SERIAL1_DEVICE	4	/* Serial #1 logical device */
#घोषणा SMSC_SERIAL2_DEVICE	5	/* Serial #2 logical device */
#घोषणा SMSC_KEYBOARD_DEVICE	7	/* Keyboard logical device */
#घोषणा SMSC_CONFIG_REGISTERS	8	/* Configuration Registers (Aux I/O) */

#घोषणा SMSC_READ_INDEXED(index) (अणु \
	outb((index), SMSC_INDEX_PORT_ADDR); \
	inb(SMSC_DATA_PORT_ADDR); पूर्ण)
#घोषणा SMSC_WRITE_INDEXED(val, index) (अणु \
	outb((index), SMSC_INDEX_PORT_ADDR); \
	outb((val),   SMSC_DATA_PORT_ADDR); पूर्ण)

#घोषणा	IDE1_PRIMARY_BASE	0x01f0	/* Task File Registe base क्रम IDE #1 */
#घोषणा	IDE1_SECONDARY_BASE	0x03f6	/* Miscellaneous AT रेजिस्टरs क्रम IDE #1 */
#घोषणा	IDE2_PRIMARY_BASE	0x0170	/* Task File Registe base क्रम IDE #2 */
#घोषणा	IDE2_SECONDARY_BASE	0x0376	/* Miscellaneous AT रेजिस्टरs क्रम IDE #2 */

#घोषणा SERIAL1_PRIMARY_BASE	0x03f8
#घोषणा SERIAL2_PRIMARY_BASE	0x02f8

#घोषणा	MSB(x)		( (x) >> 8 )
#घोषणा	LSB(x)		( (x) & 0xff )

	/* General-Purpose base address on CPU-board FPGA */
#घोषणा	MICRODEV_FPGA_GP_BASE		0xa6100000ul

अटल पूर्णांक __init smsc_superio_setup(व्योम)
अणु

	अचिन्हित अक्षर devid, devrev;

		/* Initially the chip is in run state */
		/* Put it पूर्णांकo configuration state */
	outb(SMSC_ENTER_CONFIG_KEY, SMSC_CONFIG_PORT_ADDR);

		/* Read device ID info */
	devid  = SMSC_READ_INDEXED(SMSC_DEVICE_ID_INDEX);
	devrev = SMSC_READ_INDEXED(SMSC_DEVICE_REV_INDEX);

	अगर ((devid == 0x30) && (devrev == 0x01))
		prपूर्णांकk("SMSC FDC37C93xAPM SuperIO device detected\n");
	अन्यथा
		वापस -ENODEV;

		/* Select the keyboard device */
	SMSC_WRITE_INDEXED(SMSC_KEYBOARD_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/* enable it */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/* enable the पूर्णांकerrupts */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_KEYBOARD, SMSC_PRIMARY_INT_INDEX);
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_MOUSE, SMSC_SECONDARY_INT_INDEX);

		/* Select the Serial #1 device */
	SMSC_WRITE_INDEXED(SMSC_SERIAL1_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/* enable it */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/* program with port addresses */
	SMSC_WRITE_INDEXED(MSB(SERIAL1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(SERIAL1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(0x00, SMSC_HDCS0_INDEX);
		/* enable the पूर्णांकerrupts */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_SERIAL1, SMSC_PRIMARY_INT_INDEX);

		/* Select the Serial #2 device */
	SMSC_WRITE_INDEXED(SMSC_SERIAL2_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/* enable it */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/* program with port addresses */
	SMSC_WRITE_INDEXED(MSB(SERIAL2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(SERIAL2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(0x00, SMSC_HDCS0_INDEX);
		/* enable the पूर्णांकerrupts */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_SERIAL2, SMSC_PRIMARY_INT_INDEX);

		/* Select the IDE#1 device */
	SMSC_WRITE_INDEXED(SMSC_IDE1_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/* enable it */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/* program with port addresses */
	SMSC_WRITE_INDEXED(MSB(IDE1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE1_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(MSB(IDE1_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE1_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(0x0c, SMSC_HDCS0_INDEX);
	SMSC_WRITE_INDEXED(0x00, SMSC_HDCS1_INDEX);
		/* select the पूर्णांकerrupt */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_IDE1, SMSC_PRIMARY_INT_INDEX);

		/* Select the IDE#2 device */
	SMSC_WRITE_INDEXED(SMSC_IDE2_DEVICE, SMCS_LOGICAL_DEV_INDEX);
		/* enable it */
	SMSC_WRITE_INDEXED(1, SMSC_ACTIVATE_INDEX);
		/* program with port addresses */
	SMSC_WRITE_INDEXED(MSB(IDE2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE2_PRIMARY_BASE), SMSC_PRIMARY_BASE_INDEX+1);
	SMSC_WRITE_INDEXED(MSB(IDE2_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+0);
	SMSC_WRITE_INDEXED(LSB(IDE2_SECONDARY_BASE), SMSC_SECONDARY_BASE_INDEX+1);
		/* select the पूर्णांकerrupt */
	SMSC_WRITE_INDEXED(MICRODEV_FPGA_IRQ_IDE2, SMSC_PRIMARY_INT_INDEX);

		/* Select the configuration रेजिस्टरs */
	SMSC_WRITE_INDEXED(SMSC_CONFIG_REGISTERS, SMCS_LOGICAL_DEV_INDEX);
		/* enable the appropriate GPIO pins क्रम IDE functionality:
		 * bit[0]   In/Out		1==input;  0==output
		 * bit[1]   Polarity		1==invert; 0==no invert
		 * bit[2]   Int Enb #1		1==Enable Combined IRQ #1; 0==disable
		 * bit[3:4] Function Select	00==original; 01==Alternate Function #1
		 */
	SMSC_WRITE_INDEXED(0x00, 0xc2);	/* GP42 = nIDE1_OE */
	SMSC_WRITE_INDEXED(0x01, 0xc5);	/* GP45 = IDE1_IRQ */
	SMSC_WRITE_INDEXED(0x00, 0xc6);	/* GP46 = nIOROP */
	SMSC_WRITE_INDEXED(0x00, 0xc7);	/* GP47 = nIOWOP */
	SMSC_WRITE_INDEXED(0x08, 0xe8);	/* GP20 = nIDE2_OE */

		/* Exit the configuration state */
	outb(SMSC_EXIT_CONFIG_KEY, SMSC_CONFIG_PORT_ADDR);

	वापस 0;
पूर्ण
device_initcall(smsc_superio_setup);
