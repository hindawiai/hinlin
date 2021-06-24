<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_FBIO_H
#घोषणा _UAPI__LINUX_FBIO_H

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>

/* Constants used क्रम fbio SunOS compatibility */
/* (C) 1996 Miguel de Icaza */

/* Frame buffer types */
#घोषणा FBTYPE_NOTYPE           -1
#घोषणा FBTYPE_SUN1BW           0   /* mono */
#घोषणा FBTYPE_SUN1COLOR        1 
#घोषणा FBTYPE_SUN2BW           2 
#घोषणा FBTYPE_SUN2COLOR        3 
#घोषणा FBTYPE_SUN2GP           4 
#घोषणा FBTYPE_SUN5COLOR        5 
#घोषणा FBTYPE_SUN3COLOR        6 
#घोषणा FBTYPE_MEMCOLOR         7 
#घोषणा FBTYPE_SUN4COLOR        8 
 
#घोषणा FBTYPE_NOTSUN1          9 
#घोषणा FBTYPE_NOTSUN2          10
#घोषणा FBTYPE_NOTSUN3          11
 
#घोषणा FBTYPE_SUNFAST_COLOR    12  /* cg6 */
#घोषणा FBTYPE_SUNROP_COLOR     13
#घोषणा FBTYPE_SUNFB_VIDEO      14
#घोषणा FBTYPE_SUNGIFB          15
#घोषणा FBTYPE_SUNGPLAS         16
#घोषणा FBTYPE_SUNGP3           17
#घोषणा FBTYPE_SUNGT            18
#घोषणा FBTYPE_SUNLEO           19      /* zx Leo card */
#घोषणा FBTYPE_MDICOLOR         20      /* cg14 */
#घोषणा FBTYPE_TCXCOLOR		21	/* SUNW,tcx card */

#घोषणा FBTYPE_LASTPLUSONE      21	/* This is not last + 1 in fact... */

/* Does not seem to be listed in the Sun file either */
#घोषणा FBTYPE_CREATOR          22
#घोषणा FBTYPE_PCI_IGA1682	23
#घोषणा FBTYPE_P9100COLOR	24

#घोषणा FBTYPE_PCI_GENERIC	1000
#घोषणा FBTYPE_PCI_MACH64	1001

/* fbio ioctls */
/* Returned by FBIOGTYPE */
काष्ठा  fbtype अणु
        पूर्णांक     fb_type;        /* fb type, see above */
        पूर्णांक     fb_height;      /* pixels */
        पूर्णांक     fb_width;       /* pixels */
        पूर्णांक     fb_depth;
        पूर्णांक     fb_cmsize;      /* color map entries */
        पूर्णांक     fb_size;        /* fb size in bytes */
पूर्ण;
#घोषणा FBIOGTYPE _IOR('F', 0, काष्ठा fbtype)

काष्ठा  fbcmap अणु
        पूर्णांक             index;          /* first element (0 origin) */
        पूर्णांक             count;
        अचिन्हित अक्षर   __user *red;
        अचिन्हित अक्षर   __user *green;
        अचिन्हित अक्षर   __user *blue;
पूर्ण;

#अगर_अघोषित __KERNEL__
#घोषणा FBIOPUTCMAP _IOW('F', 3, काष्ठा fbcmap)
#घोषणा FBIOGETCMAP _IOW('F', 4, काष्ठा fbcmap)
#पूर्ण_अगर

/* # of device specअगरic values */
#घोषणा FB_ATTR_NDEVSPECIFIC    8
/* # of possible emulations */
#घोषणा FB_ATTR_NEMUTYPES       4
 
काष्ठा fbsattr अणु
        पूर्णांक     flags;
        पूर्णांक     emu_type;	/* -1 अगर none */
        पूर्णांक     dev_specअगरic[FB_ATTR_NDEVSPECIFIC];
पूर्ण;
 
काष्ठा fbgattr अणु
        पूर्णांक     real_type;	/* real frame buffer type */
        पूर्णांक     owner;		/* unknown */
        काष्ठा fbtype fbtype;	/* real frame buffer fbtype */
        काष्ठा fbsattr sattr;   
        पूर्णांक     emu_types[FB_ATTR_NEMUTYPES]; /* supported emulations */
पूर्ण;
#घोषणा FBIOSATTR  _IOW('F', 5, काष्ठा fbgattr) /* Unsupported: */
#घोषणा FBIOGATTR  _IOR('F', 6, काष्ठा fbgattr)	/* supported */

#घोषणा FBIOSVIDEO _IOW('F', 7, पूर्णांक)
#घोषणा FBIOGVIDEO _IOR('F', 8, पूर्णांक)

काष्ठा fbcursor अणु
        लघु set;              /* what to set, choose from the list above */
        लघु enable;           /* cursor on/off */
        काष्ठा fbcurpos pos;    /* cursor position */
        काष्ठा fbcurpos hot;    /* cursor hot spot */
        काष्ठा fbcmap cmap;     /* color map info */
        काष्ठा fbcurpos size;   /* cursor bit map size */
        अक्षर __user *image;     /* cursor image bits */
        अक्षर __user *mask;      /* cursor mask bits */
पूर्ण;

/* set/get cursor attributes/shape */
#घोषणा FBIOSCURSOR     _IOW('F', 24, काष्ठा fbcursor)
#घोषणा FBIOGCURSOR     _IOWR('F', 25, काष्ठा fbcursor)
 
/* set/get cursor position */
#घोषणा FBIOSCURPOS     _IOW('F', 26, काष्ठा fbcurpos)
#घोषणा FBIOGCURPOS     _IOW('F', 27, काष्ठा fbcurpos)
 
/* get max cursor size */
#घोषणा FBIOGCURMAX     _IOR('F', 28, काष्ठा fbcurpos)

/* wid manipulation */
काष्ठा fb_wid_alloc अणु
#घोषणा FB_WID_SHARED_8		0
#घोषणा FB_WID_SHARED_24	1
#घोषणा FB_WID_DBL_8		2
#घोषणा FB_WID_DBL_24		3
	__u32	wa_type;
	__s32	wa_index;	/* Set on वापस */
	__u32	wa_count;	
पूर्ण;
काष्ठा fb_wid_item अणु
	__u32	wi_type;
	__s32	wi_index;
	__u32	wi_attrs;
	__u32	wi_values[32];
पूर्ण;
काष्ठा fb_wid_list अणु
	__u32	wl_flags;
	__u32	wl_count;
	काष्ठा fb_wid_item	*wl_list;
पूर्ण;

#घोषणा FBIO_WID_ALLOC	_IOWR('F', 30, काष्ठा fb_wid_alloc)
#घोषणा FBIO_WID_FREE	_IOW('F', 31, काष्ठा fb_wid_alloc)
#घोषणा FBIO_WID_PUT	_IOW('F', 32, काष्ठा fb_wid_list)
#घोषणा FBIO_WID_GET	_IOWR('F', 33, काष्ठा fb_wid_list)

/* Creator ioctls */
#घोषणा FFB_IOCTL	('F'<<8)
#घोषणा FFB_SYS_INFO		(FFB_IOCTL|80)
#घोषणा FFB_CLUTREAD		(FFB_IOCTL|81)
#घोषणा FFB_CLUTPOST		(FFB_IOCTL|82)
#घोषणा FFB_SETDIAGMODE		(FFB_IOCTL|83)
#घोषणा FFB_GETMONITORID	(FFB_IOCTL|84)
#घोषणा FFB_GETVIDEOMODE	(FFB_IOCTL|85)
#घोषणा FFB_SETVIDEOMODE	(FFB_IOCTL|86)
#घोषणा FFB_SETSERVER		(FFB_IOCTL|87)
#घोषणा FFB_SETOVCTL		(FFB_IOCTL|88)
#घोषणा FFB_GETOVCTL		(FFB_IOCTL|89)
#घोषणा FFB_GETSAXNUM		(FFB_IOCTL|90)
#घोषणा FFB_FBDEBUG		(FFB_IOCTL|91)

/* Cg14 ioctls */
#घोषणा MDI_IOCTL          ('M'<<8)
#घोषणा MDI_RESET          (MDI_IOCTL|1)
#घोषणा MDI_GET_CFGINFO    (MDI_IOCTL|2)
#घोषणा MDI_SET_PIXELMODE  (MDI_IOCTL|3)
#    define MDI_32_PIX     32
#    define MDI_16_PIX     16
#    define MDI_8_PIX      8

काष्ठा mdi_cfginfo अणु
	पूर्णांक     mdi_ncluts;     /* Number of implemented CLUTs in this MDI */
        पूर्णांक     mdi_type;       /* FBTYPE name */
        पूर्णांक     mdi_height;     /* height */
        पूर्णांक     mdi_width;      /* width */
        पूर्णांक     mdi_size;       /* available ram */
        पूर्णांक     mdi_mode;       /* 8bpp, 16bpp or 32bpp */
        पूर्णांक     mdi_pixfreq;    /* pixel घड़ी (from PROM) */
पूर्ण;

/* SparcLinux specअगरic ioctl क्रम the MDI, should be replaced क्रम
 * the SET_XLUT/SET_CLUTn ioctls instead
 */
#घोषणा MDI_CLEAR_XLUT       (MDI_IOCTL|9)

/* leo & ffb ioctls */
काष्ठा fb_clut_alloc अणु
	__u32	clutid;	/* Set on वापस */
 	__u32	flag;
 	__u32	index;
पूर्ण;

काष्ठा fb_clut अणु
#घोषणा FB_CLUT_WAIT	0x00000001	/* Not yet implemented */
 	__u32	flag;
 	__u32	clutid;
 	__u32	offset;
 	__u32	count;
 	अक्षर *	red;
 	अक्षर *	green;
 	अक्षर *	blue;
पूर्ण;

काष्ठा fb_clut32 अणु
 	__u32	flag;
 	__u32	clutid;
 	__u32	offset;
 	__u32	count;
 	__u32	red;
 	__u32	green;
 	__u32	blue;
पूर्ण;

#घोषणा LEO_CLUTALLOC	_IOWR('L', 53, काष्ठा fb_clut_alloc)
#घोषणा LEO_CLUTFREE	_IOW('L', 54, काष्ठा fb_clut_alloc)
#घोषणा LEO_CLUTREAD	_IOW('L', 55, काष्ठा fb_clut)
#घोषणा LEO_CLUTPOST	_IOW('L', 56, काष्ठा fb_clut)
#घोषणा LEO_SETGAMMA	_IOW('L', 68, पूर्णांक) /* Not yet implemented */
#घोषणा LEO_GETGAMMA	_IOR('L', 69, पूर्णांक) /* Not yet implemented */


/* These are exported to userland क्रम applications to use */
/* Mappable offsets क्रम the cg14: control रेजिस्टरs */
#घोषणा MDI_सूचीECT_MAP 0x10000000
#घोषणा MDI_CTLREG_MAP 0x20000000
#घोषणा MDI_CURSOR_MAP 0x30000000
#घोषणा MDI_SHDW_VRT_MAP 0x40000000

/* Mappable offsets क्रम the cg14: frame buffer resolutions */
/* 32 bits */
#घोषणा MDI_CHUNKY_XBGR_MAP 0x50000000
#घोषणा MDI_CHUNKY_BGR_MAP 0x60000000

/* 16 bits */
#घोषणा MDI_PLANAR_X16_MAP 0x70000000
#घोषणा MDI_PLANAR_C16_MAP 0x80000000

/* 8 bit is करोne as CG3 MMAP offset */
/* 32 bits, planar */
#घोषणा MDI_PLANAR_X32_MAP 0x90000000
#घोषणा MDI_PLANAR_B32_MAP 0xa0000000
#घोषणा MDI_PLANAR_G32_MAP 0xb0000000
#घोषणा MDI_PLANAR_R32_MAP 0xc0000000

/* Mappable offsets on leo */
#घोषणा LEO_SS0_MAP            0x00000000
#घोषणा LEO_LC_SS0_USR_MAP     0x00800000
#घोषणा LEO_LD_SS0_MAP         0x00801000
#घोषणा LEO_LX_CURSOR_MAP      0x00802000
#घोषणा LEO_SS1_MAP            0x00803000
#घोषणा LEO_LC_SS1_USR_MAP     0x01003000
#घोषणा LEO_LD_SS1_MAP         0x01004000
#घोषणा LEO_UNK_MAP            0x01005000
#घोषणा LEO_LX_KRN_MAP         0x01006000
#घोषणा LEO_LC_SS0_KRN_MAP     0x01007000
#घोषणा LEO_LC_SS1_KRN_MAP     0x01008000
#घोषणा LEO_LD_GBL_MAP         0x01009000
#घोषणा LEO_UNK2_MAP           0x0100a000


#पूर्ण_अगर /* _UAPI__LINUX_FBIO_H */
