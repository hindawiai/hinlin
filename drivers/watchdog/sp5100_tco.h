<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	sp5100_tco:	TCO समयr driver क्रम sp5100 chipsets.
 *
 *	(c) Copyright 2009 Google Inc., All Rights Reserved.
 *
 *	TCO समयr driver क्रम sp5100 chipsets
 */

#समावेश <linux/bitops.h>

/*
 * Some address definitions क्रम the Watchकरोg
 */
#घोषणा SP5100_WDT_MEM_MAP_SIZE		0x08
#घोषणा SP5100_WDT_CONTROL(base)	((base) + 0x00) /* Watchकरोg Control */
#घोषणा SP5100_WDT_COUNT(base)		((base) + 0x04) /* Watchकरोg Count */

#घोषणा SP5100_WDT_START_STOP_BIT	BIT(0)
#घोषणा SP5100_WDT_FIRED		BIT(1)
#घोषणा SP5100_WDT_ACTION_RESET		BIT(2)
#घोषणा SP5100_WDT_DISABLED		BIT(3)
#घोषणा SP5100_WDT_TRIGGER_BIT		BIT(7)

#घोषणा SP5100_PM_IOPORTS_SIZE		0x02

/*
 * These two IO रेजिस्टरs are hardcoded and there करोesn't seem to be a way to
 * पढ़ो them from a रेजिस्टर.
 */

/*  For SP5100/SB7x0/SB8x0 chipset */
#घोषणा SP5100_IO_PM_INDEX_REG		0xCD6
#घोषणा SP5100_IO_PM_DATA_REG		0xCD7

/* For SP5100/SB7x0 chipset */
#घोषणा SP5100_SB_RESOURCE_MMIO_BASE	0x9C

#घोषणा SP5100_PM_WATCHDOG_CONTROL	0x69
#घोषणा SP5100_PM_WATCHDOG_BASE		0x6C

#घोषणा SP5100_PCI_WATCHDOG_MISC_REG	0x41
#घोषणा SP5100_PCI_WATCHDOG_DECODE_EN	BIT(3)

#घोषणा SP5100_PM_WATCHDOG_DISABLE	((u8)BIT(0))
#घोषणा SP5100_PM_WATCHDOG_SECOND_RES	GENMASK(2, 1)

#घोषणा SP5100_DEVNAME			"SP5100 TCO"

/*  For SB8x0(or later) chipset */
#घोषणा SB800_PM_ACPI_MMIO_EN		0x24
#घोषणा SB800_PM_WATCHDOG_CONTROL	0x48
#घोषणा SB800_PM_WATCHDOG_BASE		0x48
#घोषणा SB800_PM_WATCHDOG_CONFIG	0x4C

#घोषणा SB800_PCI_WATCHDOG_DECODE_EN	BIT(0)
#घोषणा SB800_PM_WATCHDOG_DISABLE	((u8)BIT(1))
#घोषणा SB800_PM_WATCHDOG_SECOND_RES	GENMASK(1, 0)
#घोषणा SB800_ACPI_MMIO_DECODE_EN	BIT(0)
#घोषणा SB800_ACPI_MMIO_SEL		BIT(1)

#घोषणा SB800_PM_WDT_MMIO_OFFSET	0xB00

#घोषणा SB800_DEVNAME			"SB800 TCO"

/* For recent chips with embedded FCH (rev 40+) */

#घोषणा EFCH_PM_DECODEEN		0x00

#घोषणा EFCH_PM_DECODEEN_WDT_TMREN	BIT(7)


#घोषणा EFCH_PM_DECODEEN3		0x03
#घोषणा EFCH_PM_DECODEEN_SECOND_RES	GENMASK(1, 0)
#घोषणा EFCH_PM_WATCHDOG_DISABLE	((u8)GENMASK(3, 2))

/* WDT MMIO अगर enabled with PM00_DECODEEN_WDT_TMREN */
#घोषणा EFCH_PM_WDT_ADDR		0xfeb00000

#घोषणा EFCH_PM_ISACONTROL		0x04

#घोषणा EFCH_PM_ISACONTROL_MMIOEN	BIT(1)

#घोषणा EFCH_PM_ACPI_MMIO_ADDR		0xfed80000
#घोषणा EFCH_PM_ACPI_MMIO_WDT_OFFSET	0x00000b00
