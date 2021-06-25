<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_ASM_GENERIC_IOCTL_H
#घोषणा _UAPI_ASM_GENERIC_IOCTL_H

/* ioctl command encoding: 32 bits total, command in lower 16 bits,
 * size of the parameter काष्ठाure in the lower 14 bits of the
 * upper 16 bits.
 * Encoding the size of the parameter काष्ठाure in the ioctl request
 * is useful क्रम catching programs compiled with old versions
 * and to aव्योम overwriting user space outside the user buffer area.
 * The highest 2 bits are reserved क्रम indicating the ``access mode''.
 * NOTE: This limits the max parameter size to 16kB -1 !
 */

/*
 * The following is क्रम compatibility across the various Linux
 * platक्रमms.  The generic ioctl numbering scheme करोesn't really enक्रमce
 * a type field.  De facto, however, the top 8 bits of the lower 16
 * bits are indeed used as a type field, so we might just as well make
 * this explicit here.  Please be sure to use the decoding macros
 * below from now on.
 */
#घोषणा _IOC_NRBITS	8
#घोषणा _IOC_TYPEBITS	8

/*
 * Let any architecture override either of the following beक्रमe
 * including this file.
 */

#अगर_अघोषित _IOC_SIZEBITS
# define _IOC_SIZEBITS	14
#पूर्ण_अगर

#अगर_अघोषित _IOC_सूचीBITS
# define _IOC_सूचीBITS	2
#पूर्ण_अगर

#घोषणा _IOC_NRMASK	((1 << _IOC_NRBITS)-1)
#घोषणा _IOC_TYPEMASK	((1 << _IOC_TYPEBITS)-1)
#घोषणा _IOC_SIZEMASK	((1 << _IOC_SIZEBITS)-1)
#घोषणा _IOC_सूचीMASK	((1 << _IOC_सूचीBITS)-1)

#घोषणा _IOC_NRSHIFT	0
#घोषणा _IOC_TYPESHIFT	(_IOC_NRSHIFT+_IOC_NRBITS)
#घोषणा _IOC_SIZESHIFT	(_IOC_TYPESHIFT+_IOC_TYPEBITS)
#घोषणा _IOC_सूचीSHIFT	(_IOC_SIZESHIFT+_IOC_SIZEBITS)

/*
 * Direction bits, which any architecture can choose to override
 * beक्रमe including this file.
 *
 * NOTE: _IOC_WRITE means userland is writing and kernel is
 * पढ़ोing. _IOC_READ means userland is पढ़ोing and kernel is writing.
 */

#अगर_अघोषित _IOC_NONE
# define _IOC_NONE	0U
#पूर्ण_अगर

#अगर_अघोषित _IOC_WRITE
# define _IOC_WRITE	1U
#पूर्ण_अगर

#अगर_अघोषित _IOC_READ
# define _IOC_READ	2U
#पूर्ण_अगर

#घोषणा _IOC(dir,type,nr,size) \
	(((dir)  << _IOC_सूचीSHIFT) | \
	 ((type) << _IOC_TYPESHIFT) | \
	 ((nr)   << _IOC_NRSHIFT) | \
	 ((size) << _IOC_SIZESHIFT))

#अगर_अघोषित __KERNEL__
#घोषणा _IOC_TYPECHECK(t) (माप(t))
#पूर्ण_अगर

/*
 * Used to create numbers.
 *
 * NOTE: _IOW means userland is writing and kernel is पढ़ोing. _IOR
 * means userland is पढ़ोing and kernel is writing.
 */
#घोषणा _IO(type,nr)		_IOC(_IOC_NONE,(type),(nr),0)
#घोषणा _IOR(type,nr,size)	_IOC(_IOC_READ,(type),(nr),(_IOC_TYPECHECK(size)))
#घोषणा _IOW(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#घोषणा _IOWR(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),(_IOC_TYPECHECK(size)))
#घोषणा _IOR_BAD(type,nr,size)	_IOC(_IOC_READ,(type),(nr),माप(size))
#घोषणा _IOW_BAD(type,nr,size)	_IOC(_IOC_WRITE,(type),(nr),माप(size))
#घोषणा _IOWR_BAD(type,nr,size)	_IOC(_IOC_READ|_IOC_WRITE,(type),(nr),माप(size))

/* used to decode ioctl numbers.. */
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

#पूर्ण_अगर /* _UAPI_ASM_GENERIC_IOCTL_H */
