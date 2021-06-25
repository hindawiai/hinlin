<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित	_SPARC_OPENPROMIO_H
#घोषणा	_SPARC_OPENPROMIO_H

#समावेश <linux/compiler.h>
#समावेश <linux/ioctl.h>

/*
 * SunOS and Solaris /dev/खोलोprom definitions. The ioctl values
 * were chosen to be exactly equal to the SunOS equivalents.
 */

काष्ठा खोलोpromio
अणु
	अचिन्हित पूर्णांक oprom_size;	/* Actual size of the oprom_array. */
	अक्षर	oprom_array[1];		/* Holds property names and values. */
पूर्ण;

#घोषणा	OPROMMAXPARAM	4096		/* Maximum size of oprom_array. */

#घोषणा	OPROMGETOPT		0x20004F01
#घोषणा	OPROMSETOPT		0x20004F02
#घोषणा	OPROMNXTOPT		0x20004F03
#घोषणा	OPROMSETOPT2		0x20004F04
#घोषणा	OPROMNEXT		0x20004F05
#घोषणा	OPROMCHILD		0x20004F06
#घोषणा	OPROMGETPROP		0x20004F07
#घोषणा	OPROMNXTPROP		0x20004F08
#घोषणा	OPROMU2P		0x20004F09
#घोषणा	OPROMGETCONS		0x20004F0A
#घोषणा	OPROMGETFBNAME		0x20004F0B
#घोषणा	OPROMGETBOOTARGS	0x20004F0C
/* Linux extensions */				/* Arguments in oprom_array: */
#घोषणा OPROMSETCUR		0x20004FF0	/* पूर्णांक node - Sets current node */
#घोषणा OPROMPCI2NODE		0x20004FF1	/* पूर्णांक pci_bus, pci_devfn - Sets current node to PCI device's node */
#घोषणा OPROMPATH2NODE		0x20004FF2	/* अक्षर path[] - Set current node from fully qualअगरied PROM path */

/*
 * Return values from OPROMGETCONS:
 */

#घोषणा OPROMCONS_NOT_WSCONS    0
#घोषणा OPROMCONS_STDIN_IS_KBD  0x1     /* मानक_निवेश device is kbd */
#घोषणा OPROMCONS_STDOUT_IS_FB  0x2     /* मानक_निकास is a framebuffer */
#घोषणा OPROMCONS_OPENPROM      0x4     /* supports खोलोboot */


/*
 *  NetBSD/OpenBSD /dev/खोलोprom definitions.
 */

काष्ठा opiocdesc
अणु
	पूर्णांक	op_nodeid;		/* PROM Node ID (value-result) */
	पूर्णांक	op_namelen;		/* Length of op_name. */
	अक्षर	__user *op_name;	/* Poपूर्णांकer to the property name. */
	पूर्णांक	op_buflen;		/* Length of op_buf (value-result) */
	अक्षर	__user *op_buf;		/* Poपूर्णांकer to buffer. */
पूर्ण;

#घोषणा	OPIOCGET	_IOWR('O', 1, काष्ठा opiocdesc)
#घोषणा	OPIOCSET	_IOW('O', 2, काष्ठा opiocdesc)
#घोषणा	OPIOCNEXTPROP	_IOWR('O', 3, काष्ठा opiocdesc)
#घोषणा	OPIOCGETOPTNODE	_IOR('O', 4, पूर्णांक)
#घोषणा	OPIOCGETNEXT	_IOWR('O', 5, पूर्णांक)
#घोषणा	OPIOCGETCHILD	_IOWR('O', 6, पूर्णांक)

#पूर्ण_अगर /* _SPARC_OPENPROMIO_H */

