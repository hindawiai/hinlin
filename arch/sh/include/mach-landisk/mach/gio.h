<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_SH_LANDISK_GIO_H
#घोषणा __ASM_SH_LANDISK_GIO_H

#समावेश <linux/ioctl.h>

/* version */
#घोषणा VERSION_STR	"1.00"

/* Driver name */
#घोषणा GIO_DRIVER_NAME		"/dev/giodrv"

/* Use 'k' as magic number */
#घोषणा GIODRV_IOC_MAGIC  'k'

#घोषणा GIODRV_IOCRESET    _IO(GIODRV_IOC_MAGIC, 0)
/*
 * S means "Set" through a ptr,
 * T means "Tell" directly
 * G means "Get" (to a poपूर्णांकed var)
 * Q means "Query", response is on the वापस value
 * X means "eXchange": G and S atomically
 * H means "sHift": T and Q atomically
 */
#घोषणा GIODRV_IOCSGIODATA1   _IOW(GIODRV_IOC_MAGIC,  1, अचिन्हित अक्षर *)
#घोषणा GIODRV_IOCGGIODATA1   _IOR(GIODRV_IOC_MAGIC,  2, अचिन्हित अक्षर *)
#घोषणा GIODRV_IOCSGIODATA2   _IOW(GIODRV_IOC_MAGIC,  3, अचिन्हित लघु *)
#घोषणा GIODRV_IOCGGIODATA2   _IOR(GIODRV_IOC_MAGIC,  4, अचिन्हित लघु *)
#घोषणा GIODRV_IOCSGIODATA4   _IOW(GIODRV_IOC_MAGIC,  5, अचिन्हित दीर्घ *)
#घोषणा GIODRV_IOCGGIODATA4   _IOR(GIODRV_IOC_MAGIC,  6, अचिन्हित दीर्घ *)
#घोषणा GIODRV_IOCSGIOSETADDR _IOW(GIODRV_IOC_MAGIC,  7, अचिन्हित दीर्घ *)
#घोषणा GIODRV_IOCHARDRESET   _IO(GIODRV_IOC_MAGIC, 8) /* debugging tool */
#घोषणा GIODRV_IOC_MAXNR 8

#घोषणा GIO_READ 0x00000000
#घोषणा GIO_WRITE 0x00000001

#पूर्ण_अगर /* __ASM_SH_LANDISK_GIO_H  */
