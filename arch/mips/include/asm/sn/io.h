<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2000, 2003 Ralf Baechle
 * Copyright (C) 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_SN_IO_H
#घोषणा _ASM_SN_IO_H

#अगर defined(CONFIG_SGI_IP27)
#समावेश <यंत्र/sn/sn0/hubपन.स>
#पूर्ण_अगर


#घोषणा IIO_ITTE_BASE		0x400160 /* base of translation table entries */
#घोषणा IIO_ITTE(bigwin)	(IIO_ITTE_BASE + 8*(bigwin))

#घोषणा IIO_ITTE_OFFSET_BITS	5	/* size of offset field */
#घोषणा IIO_ITTE_OFFSET_MASK	((1<<IIO_ITTE_OFFSET_BITS)-1)
#घोषणा IIO_ITTE_OFFSET_SHIFT	0

#घोषणा IIO_ITTE_WIDGET_BITS	4	/* size of widget field */
#घोषणा IIO_ITTE_WIDGET_MASK	((1<<IIO_ITTE_WIDGET_BITS)-1)
#घोषणा IIO_ITTE_WIDGET_SHIFT	8

#घोषणा IIO_ITTE_IOSP		1	/* I/O Space bit */
#घोषणा IIO_ITTE_IOSP_MASK	1
#घोषणा IIO_ITTE_IOSP_SHIFT	12
#घोषणा HUB_PIO_MAP_TO_MEM	0
#घोषणा HUB_PIO_MAP_TO_IO	1

#घोषणा IIO_ITTE_INVALID_WIDGET 3	/* an invalid widget  */

#घोषणा IIO_ITTE_PUT(nasid, bigwin, io_or_mem, widget, addr) \
	REMOTE_HUB_S((nasid), IIO_ITTE(bigwin), \
		(((((addr) >> BWIN_SIZE_BITS) & \
		   IIO_ITTE_OFFSET_MASK) << IIO_ITTE_OFFSET_SHIFT) | \
		(io_or_mem << IIO_ITTE_IOSP_SHIFT) | \
		(((widget) & IIO_ITTE_WIDGET_MASK) << IIO_ITTE_WIDGET_SHIFT)))

#घोषणा IIO_ITTE_DISABLE(nasid, bigwin) \
	IIO_ITTE_PUT((nasid), HUB_PIO_MAP_TO_MEM, \
		     (bigwin), IIO_ITTE_INVALID_WIDGET, 0)

#घोषणा IIO_ITTE_GET(nasid, bigwin) REMOTE_HUB_PTR((nasid), IIO_ITTE(bigwin))

/*
 * Macro which takes the widget number, and वापसs the
 * IO PRB address of that widget.
 * value _x is expected to be a widget number in the range
 * 0, 8 - 0xF
 */
#घोषणा IIO_IOPRB(_x)	(IIO_IOPRB_0 + ( ( (_x) < HUB_WIDGET_ID_MIN ? \
			(_x) : \
			(_x) - (HUB_WIDGET_ID_MIN-1)) << 3) )

#पूर्ण_अगर /* _ASM_SN_IO_H */
