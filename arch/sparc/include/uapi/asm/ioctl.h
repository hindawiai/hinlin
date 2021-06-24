<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _SPARC_IOCTL_H
#घोषणा _SPARC_IOCTL_H

/*
 * Our सूची and SIZE overlap in order to simulteneously provide
 * a non-zero _IOC_NONE (क्रम binary compatibility) and
 * 14 bits of size as on i386. Here's the layout:
 *
 *   0xE0000000   सूची
 *   0x80000000     सूची = WRITE
 *   0x40000000     सूची = READ
 *   0x20000000     सूची = NONE
 *   0x3FFF0000   SIZE (overlaps NONE bit)
 *   0x0000FF00   TYPE
 *   0x000000FF   NR (CMD)
 */

#घोषणा _IOC_NRBITS      8
#घोषणा _IOC_TYPEBITS    8
#घोषणा _IOC_SIZEBITS   13	/* Actually 14, see below. */
#घोषणा _IOC_सूचीBITS     3

#घोषणा _IOC_NRMASK      ((1 << _IOC_NRBITS)-1)
#घोषणा _IOC_TYPEMASK    ((1 << _IOC_TYPEBITS)-1)
#घोषणा _IOC_SIZEMASK    ((1 << _IOC_SIZEBITS)-1)
#घोषणा _IOC_XSIZEMASK   ((1 << (_IOC_SIZEBITS+1))-1)
#घोषणा _IOC_सूचीMASK     ((1 << _IOC_सूचीBITS)-1)

#घोषणा _IOC_NRSHIFT     0
#घोषणा _IOC_TYPESHIFT   (_IOC_NRSHIFT + _IOC_NRBITS)
#घोषणा _IOC_SIZESHIFT   (_IOC_TYPESHIFT + _IOC_TYPEBITS)
#घोषणा _IOC_सूचीSHIFT    (_IOC_SIZESHIFT + _IOC_SIZEBITS)

#घोषणा _IOC_NONE        1U
#घोषणा _IOC_READ        2U
#घोषणा _IOC_WRITE       4U

#घोषणा _IOC(dir,type,nr,size) \
        (((dir)  << _IOC_सूचीSHIFT) | \
         ((type) << _IOC_TYPESHIFT) | \
         ((nr)   << _IOC_NRSHIFT) | \
         ((size) << _IOC_SIZESHIFT))

#घोषणा _IO(type,nr)        _IOC(_IOC_NONE,(type),(nr),0)
#घोषणा _IOR(type,nr,size)  _IOC(_IOC_READ,(type),(nr),माप(size))
#घोषणा _IOW(type,nr,size)  _IOC(_IOC_WRITE,(type),(nr),माप(size))
#घोषणा _IOWR(type,nr,size) _IOC(_IOC_READ|_IOC_WRITE,(type),(nr),माप(size))

/* Used to decode ioctl numbers in drivers despite the leading underscore... */
#घोषणा _IOC_सूची(nr)    \
 ( (((((nr) >> _IOC_सूचीSHIFT) & _IOC_सूचीMASK) & (_IOC_WRITE|_IOC_READ)) != 0)?   \
                            (((nr) >> _IOC_सूचीSHIFT) & (_IOC_WRITE|_IOC_READ)):  \
                            (((nr) >> _IOC_सूचीSHIFT) & _IOC_सूचीMASK) )
#घोषणा _IOC_TYPE(nr)       (((nr) >> _IOC_TYPESHIFT) & _IOC_TYPEMASK)
#घोषणा _IOC_NR(nr)         (((nr) >> _IOC_NRSHIFT) & _IOC_NRMASK)
#घोषणा _IOC_SIZE(nr)   \
 ((((((nr) >> _IOC_सूचीSHIFT) & _IOC_सूचीMASK) & (_IOC_WRITE|_IOC_READ)) == 0)?    \
                         0: (((nr) >> _IOC_SIZESHIFT) & _IOC_XSIZEMASK))

/* ...and क्रम the PCMCIA and sound. */
#घोषणा IOC_IN          (_IOC_WRITE << _IOC_सूचीSHIFT)
#घोषणा IOC_OUT         (_IOC_READ << _IOC_सूचीSHIFT)
#घोषणा IOC_INOUT       ((_IOC_WRITE|_IOC_READ) << _IOC_सूचीSHIFT)
#घोषणा IOCSIZE_MASK    (_IOC_XSIZEMASK << _IOC_SIZESHIFT)
#घोषणा IOCSIZE_SHIFT   (_IOC_SIZESHIFT)

#पूर्ण_अगर /* !(_SPARC_IOCTL_H) */
