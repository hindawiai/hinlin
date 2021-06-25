<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ALPHA_IOCTL_H
#घोषणा _ALPHA_IOCTL_H

/*
 * The original linux ioctl numbering scheme was just a general
 * "anything goes" setup, where more or less अक्रमom numbers were
 * asचिन्हित.  Sorry, I was clueless when I started out on this.
 *
 * On the alpha, we'll try to clean it up a bit, using a more sane
 * ioctl numbering, and also trying to be compatible with OSF/1 in
 * the process. I'd like to clean it up क्रम the i386 as well, but
 * it's so painful recognizing both the new and the old numbers..
 */

#घोषणा _IOC_NRBITS	8
#घोषणा _IOC_TYPEBITS	8
#घोषणा _IOC_SIZEBITS	13
#घोषणा _IOC_सूचीBITS	3

#घोषणा _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#घोषणा _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#घोषणा _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#घोषणा _IOC_सूचीMASK	((1 << _IOC_सूचीBITS)-1)

#घोषणा _IOC_NRSHIFT	0
#घोषणा _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#घोषणा _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#घोषणा _IOC_सूचीSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

/*
 * Direction bits _IOC_NONE could be 0, but OSF/1 gives it a bit.
 * And this turns out useful to catch old ioctl numbers in header
 * files क्रम us.
 */
#घोषणा _IOC_NONE	1U
#घोषणा _IOC_READ	2U
#घोषणा _IOC_WRITE	4U

#घोषणा _IOC(dir,type,nr,size)			\
	((अचिन्हित पूर्णांक)				\
	 (((dir)  << _IOC_सूचीSHIFT) |		\
	  ((type) << _IOC_TYPESHIFT) |		\
	  ((nr)   << _IOC_NRSHIFT) |		\
	  ((size) << _IOC_SIZESHIFT)))

/* used to create numbers */
#घोषणा _IO(type,nr)		_IOC(_IOC_NONE,(type),(nr),0)
#घोषणा _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),माप(size))
#घोषणा _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),माप(size))
#घोषणा _IOWR(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),माप(size))

/* used to decode them.. */
#घोषणा _IOC_सूची(nr)		(((nr) >> _IOC_सूचीSHIFT) & _IOC_सूचीMASK)
#घोषणा _IOC_TYPE(nr)		(((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#घोषणा _IOC_NR(nr)		(((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#घोषणा _IOC_SIZE(nr)		(((nr) >> _IOC_SIZESHIFT) & _IOC_SIZEMASK)

/* ...and क्रम the drivers/sound files... */

#घोषणा IOC_IN		(_IOC_WRITE << _IOC_सूचीSHIFT)
#घोषणा IOC_OUT		(_IOC_READ << _IOC_सूचीSHIFT)
#घोषणा IOC_INOUT	((_IOC_WRITE|_IOC_READ) << _IOC_सूचीSHIFT)
#घोषणा IOCSIZE_MASK	(_IOC_SIZEMASK << _IOC_SIZESHIFT)
#घोषणा IOCSIZE_SHIFT	(_IOC_SIZESHIFT)

#पूर्ण_अगर /* _ALPHA_IOCTL_H */
