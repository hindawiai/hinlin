<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_FB_H
#घोषणा _LINUX_FB_H

#समावेश <linux/kgdb.h>
#समावेश <uapi/linux/fb.h>

#घोषणा FBIO_CURSOR            _IOWR('F', 0x08, काष्ठा fb_cursor_user)

#समावेश <linux/fs.h>
#समावेश <linux/init.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/list.h>
#समावेश <linux/backlight.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

काष्ठा vm_area_काष्ठा;
काष्ठा fb_info;
काष्ठा device;
काष्ठा file;
काष्ठा videomode;
काष्ठा device_node;

/* Definitions below are used in the parsed monitor specs */
#घोषणा FB_DPMS_ACTIVE_OFF	1
#घोषणा FB_DPMS_SUSPEND		2
#घोषणा FB_DPMS_STANDBY		4

#घोषणा FB_DISP_DDI		1
#घोषणा FB_DISP_ANA_700_300	2
#घोषणा FB_DISP_ANA_714_286	4
#घोषणा FB_DISP_ANA_1000_400	8
#घोषणा FB_DISP_ANA_700_000	16

#घोषणा FB_DISP_MONO		32
#घोषणा FB_DISP_RGB		64
#घोषणा FB_DISP_MULTI		128
#घोषणा FB_DISP_UNKNOWN		256

#घोषणा FB_SIGNAL_NONE		0
#घोषणा FB_SIGNAL_BLANK_BLANK	1
#घोषणा FB_SIGNAL_SEPARATE	2
#घोषणा FB_SIGNAL_COMPOSITE	4
#घोषणा FB_SIGNAL_SYNC_ON_GREEN	8
#घोषणा FB_SIGNAL_SERRATION_ON	16

#घोषणा FB_MISC_PRIM_COLOR	1
#घोषणा FB_MISC_1ST_DETAIL	2	/* First Detailed Timing is preferred */
#घोषणा FB_MISC_HDMI		4
काष्ठा fb_chroma अणु
	__u32 redx;	/* in fraction of 1024 */
	__u32 greenx;
	__u32 bluex;
	__u32 whitex;
	__u32 redy;
	__u32 greeny;
	__u32 bluey;
	__u32 whitey;
पूर्ण;

काष्ठा fb_monspecs अणु
	काष्ठा fb_chroma chroma;
	काष्ठा fb_videomode *modedb;	/* mode database */
	__u8  manufacturer[4];		/* Manufacturer */
	__u8  monitor[14];		/* Monitor String */
	__u8  serial_no[14];		/* Serial Number */
	__u8  ascii[14];		/* ? */
	__u32 modedb_len;		/* mode database length */
	__u32 model;			/* Monitor Model */
	__u32 serial;			/* Serial Number - Integer */
	__u32 year;			/* Year manufactured */
	__u32 week;			/* Week Manufactured */
	__u32 hfmin;			/* hfreq lower limit (Hz) */
	__u32 hfmax;			/* hfreq upper limit (Hz) */
	__u32 dclkmin;			/* pixelघड़ी lower limit (Hz) */
	__u32 dclkmax;			/* pixelघड़ी upper limit (Hz) */
	__u16 input;			/* display type - see FB_DISP_* */
	__u16 dpms;			/* DPMS support - see FB_DPMS_ */
	__u16 संकेत;			/* Signal Type - see FB_SIGNAL_* */
	__u16 vfmin;			/* vfreq lower limit (Hz) */
	__u16 vfmax;			/* vfreq upper limit (Hz) */
	__u16 gamma;			/* Gamma - in fractions of 100 */
	__u16 gtf	: 1;		/* supports GTF */
	__u16 misc;			/* Misc flags - see FB_MISC_* */
	__u8  version;			/* EDID version... */
	__u8  revision;			/* ...and revision */
	__u8  max_x;			/* Maximum horizontal size (cm) */
	__u8  max_y;			/* Maximum vertical size (cm) */
पूर्ण;

काष्ठा fb_cmap_user अणु
	__u32 start;			/* First entry	*/
	__u32 len;			/* Number of entries */
	__u16 __user *red;		/* Red values	*/
	__u16 __user *green;
	__u16 __user *blue;
	__u16 __user *transp;		/* transparency, can be शून्य */
पूर्ण;

काष्ठा fb_image_user अणु
	__u32 dx;			/* Where to place image */
	__u32 dy;
	__u32 width;			/* Size of image */
	__u32 height;
	__u32 fg_color;			/* Only used when a mono biपंचांगap */
	__u32 bg_color;
	__u8  depth;			/* Depth of the image */
	स्थिर अक्षर __user *data;	/* Poपूर्णांकer to image data */
	काष्ठा fb_cmap_user cmap;	/* color map info */
पूर्ण;

काष्ठा fb_cursor_user अणु
	__u16 set;			/* what to set */
	__u16 enable;			/* cursor on/off */
	__u16 rop;			/* bitop operation */
	स्थिर अक्षर __user *mask;	/* cursor mask bits */
	काष्ठा fbcurpos hot;		/* cursor hot spot */
	काष्ठा fb_image_user image;	/* Cursor image */
पूर्ण;

/*
 * Register/unरेजिस्टर क्रम framebuffer events
 */

/*	The resolution of the passed in fb_info about to change */
#घोषणा FB_EVENT_MODE_CHANGE		0x01

#अगर_घोषित CONFIG_GUMSTIX_AM200EPD
/* only used by mach-pxa/am200epd.c */
#घोषणा FB_EVENT_FB_REGISTERED          0x05
#घोषणा FB_EVENT_FB_UNREGISTERED        0x06
#पूर्ण_अगर

/*      A display blank is requested       */
#घोषणा FB_EVENT_BLANK                  0x09

काष्ठा fb_event अणु
	काष्ठा fb_info *info;
	व्योम *data;
पूर्ण;

काष्ठा fb_blit_caps अणु
	u32 x;
	u32 y;
	u32 len;
	u32 flags;
पूर्ण;

#अगर_घोषित CONFIG_FB_NOTIFY
बाह्य पूर्णांक fb_रेजिस्टर_client(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक fb_unरेजिस्टर_client(काष्ठा notअगरier_block *nb);
बाह्य पूर्णांक fb_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v);
#अन्यथा
अटल अंतरभूत पूर्णांक fb_रेजिस्टर_client(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण;

अटल अंतरभूत पूर्णांक fb_unरेजिस्टर_client(काष्ठा notअगरier_block *nb)
अणु
	वापस 0;
पूर्ण;

अटल अंतरभूत पूर्णांक fb_notअगरier_call_chain(अचिन्हित दीर्घ val, व्योम *v)
अणु
	वापस 0;
पूर्ण;
#पूर्ण_अगर

/*
 * Pixmap काष्ठाure definition
 *
 * The purpose of this काष्ठाure is to translate data
 * from the hardware independent क्रमmat of fbdev to what
 * क्रमmat the hardware needs.
 */

#घोषणा FB_PIXMAP_DEFAULT 1     /* used पूर्णांकernally by fbcon */
#घोषणा FB_PIXMAP_SYSTEM  2     /* memory is in प्रणाली RAM  */
#घोषणा FB_PIXMAP_IO      4     /* memory is iomapped       */
#घोषणा FB_PIXMAP_SYNC    256   /* set अगर GPU can DMA       */

काष्ठा fb_pixmap अणु
	u8  *addr;		/* poपूर्णांकer to memory			*/
	u32 size;		/* size of buffer in bytes		*/
	u32 offset;		/* current offset to buffer		*/
	u32 buf_align;		/* byte alignment of each biपंचांगap	*/
	u32 scan_align;		/* alignment per scanline		*/
	u32 access_align;	/* alignment per पढ़ो/ग_लिखो (bits)	*/
	u32 flags;		/* see FB_PIXMAP_*			*/
	u32 blit_x;             /* supported bit block dimensions (1-32)*/
	u32 blit_y;             /* Format: blit_x = 1 << (width - 1)    */
	                        /*         blit_y = 1 << (height - 1)   */
	                        /* अगर 0, will be set to 0xffffffff (all)*/
	/* access methods */
	व्योम (*ग_लिखोio)(काष्ठा fb_info *info, व्योम __iomem *dst, व्योम *src, अचिन्हित पूर्णांक size);
	व्योम (*पढ़ोio) (काष्ठा fb_info *info, व्योम *dst, व्योम __iomem *src, अचिन्हित पूर्णांक size);
पूर्ण;

#अगर_घोषित CONFIG_FB_DEFERRED_IO
काष्ठा fb_deferred_io अणु
	/* delay between mkग_लिखो and deferred handler */
	अचिन्हित दीर्घ delay;
	काष्ठा mutex lock; /* mutex that protects the page list */
	काष्ठा list_head pagelist; /* list of touched pages */
	/* callback */
	व्योम (*first_io)(काष्ठा fb_info *info);
	व्योम (*deferred_io)(काष्ठा fb_info *info, काष्ठा list_head *pagelist);
पूर्ण;
#पूर्ण_अगर

/*
 * Frame buffer operations
 *
 * LOCKING NOTE: those functions must _ALL_ be called with the console
 * semaphore held, this is the only suitable locking mechanism we have
 * in 2.6. Some may be called at पूर्णांकerrupt समय at this poपूर्णांक though.
 *
 * The exception to this is the debug related hooks.  Putting the fb
 * पूर्णांकo a debug state (e.g. flipping to the kernel console) and restoring
 * it must be करोne in a lock-मुक्त manner, so low level drivers should
 * keep track of the initial console (अगर applicable) and may need to
 * perक्रमm direct, unlocked hardware ग_लिखोs in these hooks.
 */

काष्ठा fb_ops अणु
	/* खोलो/release and usage marking */
	काष्ठा module *owner;
	पूर्णांक (*fb_खोलो)(काष्ठा fb_info *info, पूर्णांक user);
	पूर्णांक (*fb_release)(काष्ठा fb_info *info, पूर्णांक user);

	/* For framebuffers with strange non linear layouts or that करो not
	 * work with normal memory mapped access
	 */
	sमाप_प्रकार (*fb_पढ़ो)(काष्ठा fb_info *info, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos);
	sमाप_प्रकार (*fb_ग_लिखो)(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos);

	/* checks var and eventually tweaks it to something supported,
	 * DO NOT MODIFY PAR */
	पूर्णांक (*fb_check_var)(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);

	/* set the video mode according to info->var */
	पूर्णांक (*fb_set_par)(काष्ठा fb_info *info);

	/* set color रेजिस्टर */
	पूर्णांक (*fb_setcolreg)(अचिन्हित regno, अचिन्हित red, अचिन्हित green,
			    अचिन्हित blue, अचिन्हित transp, काष्ठा fb_info *info);

	/* set color रेजिस्टरs in batch */
	पूर्णांक (*fb_setcmap)(काष्ठा fb_cmap *cmap, काष्ठा fb_info *info);

	/* blank display */
	पूर्णांक (*fb_blank)(पूर्णांक blank, काष्ठा fb_info *info);

	/* pan display */
	पूर्णांक (*fb_pan_display)(काष्ठा fb_var_screeninfo *var, काष्ठा fb_info *info);

	/* Draws a rectangle */
	व्योम (*fb_fillrect) (काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
	/* Copy data from area to another */
	व्योम (*fb_copyarea) (काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *region);
	/* Draws a image to the display */
	व्योम (*fb_imageblit) (काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);

	/* Draws cursor */
	पूर्णांक (*fb_cursor) (काष्ठा fb_info *info, काष्ठा fb_cursor *cursor);

	/* रुको क्रम blit idle, optional */
	पूर्णांक (*fb_sync)(काष्ठा fb_info *info);

	/* perक्रमm fb specअगरic ioctl (optional) */
	पूर्णांक (*fb_ioctl)(काष्ठा fb_info *info, अचिन्हित पूर्णांक cmd,
			अचिन्हित दीर्घ arg);

	/* Handle 32bit compat ioctl (optional) */
	पूर्णांक (*fb_compat_ioctl)(काष्ठा fb_info *info, अचिन्हित cmd,
			अचिन्हित दीर्घ arg);

	/* perक्रमm fb specअगरic mmap */
	पूर्णांक (*fb_mmap)(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);

	/* get capability given var */
	व्योम (*fb_get_caps)(काष्ठा fb_info *info, काष्ठा fb_blit_caps *caps,
			    काष्ठा fb_var_screeninfo *var);

	/* tearकरोwn any resources to करो with this framebuffer */
	व्योम (*fb_destroy)(काष्ठा fb_info *info);

	/* called at KDB enter and leave समय to prepare the console */
	पूर्णांक (*fb_debug_enter)(काष्ठा fb_info *info);
	पूर्णांक (*fb_debug_leave)(काष्ठा fb_info *info);
पूर्ण;

#अगर_घोषित CONFIG_FB_TILEBLITTING
#घोषणा FB_TILE_CURSOR_NONE        0
#घोषणा FB_TILE_CURSOR_UNDERLINE   1
#घोषणा FB_TILE_CURSOR_LOWER_THIRD 2
#घोषणा FB_TILE_CURSOR_LOWER_HALF  3
#घोषणा FB_TILE_CURSOR_TWO_THIRDS  4
#घोषणा FB_TILE_CURSOR_BLOCK       5

काष्ठा fb_tilemap अणु
	__u32 width;                /* width of each tile in pixels */
	__u32 height;               /* height of each tile in scanlines */
	__u32 depth;                /* color depth of each tile */
	__u32 length;               /* number of tiles in the map */
	स्थिर __u8 *data;           /* actual tile map: a biपंचांगap array, packed
				       to the nearest byte */
पूर्ण;

काष्ठा fb_tilerect अणु
	__u32 sx;                   /* origin in the x-axis */
	__u32 sy;                   /* origin in the y-axis */
	__u32 width;                /* number of tiles in the x-axis */
	__u32 height;               /* number of tiles in the y-axis */
	__u32 index;                /* what tile to use: index to tile map */
	__u32 fg;                   /* क्रमeground color */
	__u32 bg;                   /* background color */
	__u32 rop;                  /* raster operation */
पूर्ण;

काष्ठा fb_tilearea अणु
	__u32 sx;                   /* source origin in the x-axis */
	__u32 sy;                   /* source origin in the y-axis */
	__u32 dx;                   /* destination origin in the x-axis */
	__u32 dy;                   /* destination origin in the y-axis */
	__u32 width;                /* number of tiles in the x-axis */
	__u32 height;               /* number of tiles in the y-axis */
पूर्ण;

काष्ठा fb_tileblit अणु
	__u32 sx;                   /* origin in the x-axis */
	__u32 sy;                   /* origin in the y-axis */
	__u32 width;                /* number of tiles in the x-axis */
	__u32 height;               /* number of tiles in the y-axis */
	__u32 fg;                   /* क्रमeground color */
	__u32 bg;                   /* background color */
	__u32 length;               /* number of tiles to draw */
	__u32 *indices;             /* array of indices to tile map */
पूर्ण;

काष्ठा fb_tilecursor अणु
	__u32 sx;                   /* cursor position in the x-axis */
	__u32 sy;                   /* cursor position in the y-axis */
	__u32 mode;                 /* 0 = erase, 1 = draw */
	__u32 shape;                /* see FB_TILE_CURSOR_* */
	__u32 fg;                   /* क्रमeground color */
	__u32 bg;                   /* background color */
पूर्ण;

काष्ठा fb_tile_ops अणु
	/* set tile अक्षरacteristics */
	व्योम (*fb_settile)(काष्ठा fb_info *info, काष्ठा fb_tilemap *map);

	/* all dimensions from hereon are in terms of tiles */

	/* move a rectangular region of tiles from one area to another*/
	व्योम (*fb_tilecopy)(काष्ठा fb_info *info, काष्ठा fb_tilearea *area);
	/* fill a rectangular region with a tile */
	व्योम (*fb_tilefill)(काष्ठा fb_info *info, काष्ठा fb_tilerect *rect);
	/* copy an array of tiles */
	व्योम (*fb_tileblit)(काष्ठा fb_info *info, काष्ठा fb_tileblit *blit);
	/* cursor */
	व्योम (*fb_tilecursor)(काष्ठा fb_info *info,
			      काष्ठा fb_tilecursor *cursor);
	/* get maximum length of the tile map */
	पूर्णांक (*fb_get_tilemax)(काष्ठा fb_info *info);
पूर्ण;
#पूर्ण_अगर /* CONFIG_FB_TILEBLITTING */

/* FBINFO_* = fb_info.flags bit flags */
#घोषणा FBINFO_DEFAULT		0
#घोषणा FBINFO_HWACCEL_DISABLED	0x0002
	/* When FBINFO_HWACCEL_DISABLED is set:
	 *  Hardware acceleration is turned off.  Software implementations
	 *  of required functions (copyarea(), fillrect(), and imageblit())
	 *  takes over; acceleration engine should be in a quiescent state */

/* hपूर्णांकs */
#घोषणा FBINFO_VIRTFB		0x0004 /* FB is System RAM, not device. */
#घोषणा FBINFO_PARTIAL_PAN_OK	0x0040 /* otw use pan only क्रम द्विगुन-buffering */
#घोषणा FBINFO_READS_FAST	0x0080 /* soft-copy faster than rendering */

/* hardware supported ops */
/*  semantics: when a bit is set, it indicates that the operation is
 *   accelerated by hardware.
 *  required functions will still work even अगर the bit is not set.
 *  optional functions may not even exist अगर the flag bit is not set.
 */
#घोषणा FBINFO_HWACCEL_NONE		0x0000
#घोषणा FBINFO_HWACCEL_COPYAREA		0x0100 /* required */
#घोषणा FBINFO_HWACCEL_FILLRECT		0x0200 /* required */
#घोषणा FBINFO_HWACCEL_IMAGEBLIT	0x0400 /* required */
#घोषणा FBINFO_HWACCEL_ROTATE		0x0800 /* optional */
#घोषणा FBINFO_HWACCEL_XPAN		0x1000 /* optional */
#घोषणा FBINFO_HWACCEL_YPAN		0x2000 /* optional */
#घोषणा FBINFO_HWACCEL_YWRAP		0x4000 /* optional */

#घोषणा FBINFO_MISC_TILEBLITTING       0x20000 /* use tile blitting */

/* A driver may set this flag to indicate that it करोes want a set_par to be
 * called every समय when fbcon_चयन is executed. The advantage is that with
 * this flag set you can really be sure that set_par is always called beक्रमe
 * any of the functions dependent on the correct hardware state or altering
 * that state, even अगर you are using some broken X releases. The disadvantage
 * is that it पूर्णांकroduces unwanted delays to every console चयन अगर set_par
 * is slow. It is a good idea to try this flag in the drivers initialization
 * code whenever there is a bug report related to चयनing between X and the
 * framebuffer console.
 */
#घोषणा FBINFO_MISC_ALWAYS_SETPAR   0x40000

/* where the fb is a firmware driver, and can be replaced with a proper one */
#घोषणा FBINFO_MISC_FIRMWARE        0x80000
/*
 * Host and GPU endianness dअगरfer.
 */
#घोषणा FBINFO_FOREIGN_ENDIAN	0x100000
/*
 * Big endian math. This is the same flags as above, but with dअगरferent
 * meaning, it is set by the fb subप्रणाली depending FOREIGN_ENDIAN flag
 * and host endianness. Drivers should not use this flag.
 */
#घोषणा FBINFO_BE_MATH  0x100000
/*
 * Hide smem_start in the FBIOGET_FSCREENINFO IOCTL. This is used by modern DRM
 * drivers to stop userspace from trying to share buffers behind the kernel's
 * back. Instead dma-buf based buffer sharing should be used.
 */
#घोषणा FBINFO_HIDE_SMEM_START  0x200000


काष्ठा fb_info अणु
	atomic_t count;
	पूर्णांक node;
	पूर्णांक flags;
	/*
	 * -1 by शेष, set to a FB_ROTATE_* value by the driver, अगर it knows
	 * a lcd is not mounted upright and fbcon should rotate to compensate.
	 */
	पूर्णांक fbcon_rotate_hपूर्णांक;
	काष्ठा mutex lock;		/* Lock क्रम खोलो/release/ioctl funcs */
	काष्ठा mutex mm_lock;		/* Lock क्रम fb_mmap and smem_* fields */
	काष्ठा fb_var_screeninfo var;	/* Current var */
	काष्ठा fb_fix_screeninfo fix;	/* Current fix */
	काष्ठा fb_monspecs monspecs;	/* Current Monitor specs */
	काष्ठा work_काष्ठा queue;	/* Framebuffer event queue */
	काष्ठा fb_pixmap pixmap;	/* Image hardware mapper */
	काष्ठा fb_pixmap sprite;	/* Cursor hardware mapper */
	काष्ठा fb_cmap cmap;		/* Current cmap */
	काष्ठा list_head modelist;      /* mode list */
	काष्ठा fb_videomode *mode;	/* current mode */

#अगर IS_ENABLED(CONFIG_FB_BACKLIGHT)
	/* asचिन्हित backlight device */
	/* set beक्रमe framebuffer registration,
	   हटाओ after unरेजिस्टर */
	काष्ठा backlight_device *bl_dev;

	/* Backlight level curve */
	काष्ठा mutex bl_curve_mutex;
	u8 bl_curve[FB_BACKLIGHT_LEVELS];
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_DEFERRED_IO
	काष्ठा delayed_work deferred_work;
	काष्ठा fb_deferred_io *fbdefio;
#पूर्ण_अगर

	स्थिर काष्ठा fb_ops *fbops;
	काष्ठा device *device;		/* This is the parent */
	काष्ठा device *dev;		/* This is this fb device */
	पूर्णांक class_flag;                    /* निजी sysfs flags */
#अगर_घोषित CONFIG_FB_TILEBLITTING
	काष्ठा fb_tile_ops *tileops;    /* Tile Blitting */
#पूर्ण_अगर
	जोड़ अणु
		अक्षर __iomem *screen_base;	/* Virtual address */
		अक्षर *screen_buffer;
	पूर्ण;
	अचिन्हित दीर्घ screen_size;	/* Amount of ioremapped VRAM or 0 */
	व्योम *pseuकरो_palette;		/* Fake palette of 16 colors */
#घोषणा FBINFO_STATE_RUNNING	0
#घोषणा FBINFO_STATE_SUSPENDED	1
	u32 state;			/* Hardware state i.e suspend */
	व्योम *fbcon_par;                /* fbcon use-only निजी area */
	/* From here on everything is device dependent */
	व्योम *par;
	/* we need the PCI or similar aperture base/size not
	   smem_start/size as smem_start may just be an object
	   allocated inside the aperture so may not actually overlap */
	काष्ठा apertures_काष्ठा अणु
		अचिन्हित पूर्णांक count;
		काष्ठा aperture अणु
			resource_माप_प्रकार base;
			resource_माप_प्रकार size;
		पूर्ण ranges[0];
	पूर्ण *apertures;

	bool skip_vt_चयन; /* no VT चयन on suspend/resume required */
पूर्ण;

अटल अंतरभूत काष्ठा apertures_काष्ठा *alloc_apertures(अचिन्हित पूर्णांक max_num) अणु
	काष्ठा apertures_काष्ठा *a;

	a = kzalloc(काष्ठा_size(a, ranges, max_num), GFP_KERNEL);
	अगर (!a)
		वापस शून्य;
	a->count = max_num;
	वापस a;
पूर्ण

#घोषणा FBINFO_FLAG_DEFAULT	FBINFO_DEFAULT

/* This will go away
 * fbset currently hacks in FB_ACCELF_TEXT पूर्णांकo var.accel_flags
 * when it wants to turn the acceleration engine on.  This is
 * really a separate operation, and should be modअगरied via sysfs.
 *  But क्रम now, we leave it broken with the following define
 */
#घोषणा STUPID_ACCELF_TEXT_SHIT

// This will go away
#अगर defined(__sparc__)

/* We map all of our framebuffers such that big-endian accesses
 * are what we want, so the following is sufficient.
 */

// This will go away
#घोषणा fb_पढ़ोb sbus_पढ़ोb
#घोषणा fb_पढ़ोw sbus_पढ़ोw
#घोषणा fb_पढ़ोl sbus_पढ़ोl
#घोषणा fb_पढ़ोq sbus_पढ़ोq
#घोषणा fb_ग_लिखोb sbus_ग_लिखोb
#घोषणा fb_ग_लिखोw sbus_ग_लिखोw
#घोषणा fb_ग_लिखोl sbus_ग_लिखोl
#घोषणा fb_ग_लिखोq sbus_ग_लिखोq
#घोषणा fb_स_रखो sbus_स_रखो_io
#घोषणा fb_स_नकल_fromfb sbus_स_नकल_fromio
#घोषणा fb_स_नकल_tofb sbus_स_नकल_toio

#या_अगर defined(__i386__) || defined(__alpha__) || defined(__x86_64__) ||	\
	defined(__hppa__) || defined(__sh__) || defined(__घातerpc__) ||	\
	defined(__arm__) || defined(__aarch64__)

#घोषणा fb_पढ़ोb __raw_पढ़ोb
#घोषणा fb_पढ़ोw __raw_पढ़ोw
#घोषणा fb_पढ़ोl __raw_पढ़ोl
#घोषणा fb_पढ़ोq __raw_पढ़ोq
#घोषणा fb_ग_लिखोb __raw_ग_लिखोb
#घोषणा fb_ग_लिखोw __raw_ग_लिखोw
#घोषणा fb_ग_लिखोl __raw_ग_लिखोl
#घोषणा fb_ग_लिखोq __raw_ग_लिखोq
#घोषणा fb_स_रखो स_रखो_io
#घोषणा fb_स_नकल_fromfb स_नकल_fromio
#घोषणा fb_स_नकल_tofb स_नकल_toio

#अन्यथा

#घोषणा fb_पढ़ोb(addr) (*(अस्थिर u8 *) (addr))
#घोषणा fb_पढ़ोw(addr) (*(अस्थिर u16 *) (addr))
#घोषणा fb_पढ़ोl(addr) (*(अस्थिर u32 *) (addr))
#घोषणा fb_पढ़ोq(addr) (*(अस्थिर u64 *) (addr))
#घोषणा fb_ग_लिखोb(b,addr) (*(अस्थिर u8 *) (addr) = (b))
#घोषणा fb_ग_लिखोw(b,addr) (*(अस्थिर u16 *) (addr) = (b))
#घोषणा fb_ग_लिखोl(b,addr) (*(अस्थिर u32 *) (addr) = (b))
#घोषणा fb_ग_लिखोq(b,addr) (*(अस्थिर u64 *) (addr) = (b))
#घोषणा fb_स_रखो स_रखो
#घोषणा fb_स_नकल_fromfb स_नकल
#घोषणा fb_स_नकल_tofb स_नकल

#पूर्ण_अगर

#घोषणा FB_LEFT_POS(p, bpp)          (fb_be_math(p) ? (32 - (bpp)) : 0)
#घोषणा FB_SHIFT_HIGH(p, val, bits)  (fb_be_math(p) ? (val) >> (bits) : \
						      (val) << (bits))
#घोषणा FB_SHIFT_LOW(p, val, bits)   (fb_be_math(p) ? (val) << (bits) : \
						      (val) >> (bits))

    /*
     *  `Generic' versions of the frame buffer device operations
     */

बाह्य पूर्णांक fb_set_var(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var);
बाह्य पूर्णांक fb_pan_display(काष्ठा fb_info *info, काष्ठा fb_var_screeninfo *var);
बाह्य पूर्णांक fb_blank(काष्ठा fb_info *info, पूर्णांक blank);
बाह्य व्योम cfb_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम cfb_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);
बाह्य व्योम cfb_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);
/*
 * Drawing operations where framebuffer is in प्रणाली RAM
 */
बाह्य व्योम sys_fillrect(काष्ठा fb_info *info, स्थिर काष्ठा fb_fillrect *rect);
बाह्य व्योम sys_copyarea(काष्ठा fb_info *info, स्थिर काष्ठा fb_copyarea *area);
बाह्य व्योम sys_imageblit(काष्ठा fb_info *info, स्थिर काष्ठा fb_image *image);
बाह्य sमाप_प्रकार fb_sys_पढ़ो(काष्ठा fb_info *info, अक्षर __user *buf,
			   माप_प्रकार count, loff_t *ppos);
बाह्य sमाप_प्रकार fb_sys_ग_लिखो(काष्ठा fb_info *info, स्थिर अक्षर __user *buf,
			    माप_प्रकार count, loff_t *ppos);

/* drivers/video/fbmem.c */
बाह्य पूर्णांक रेजिस्टर_framebuffer(काष्ठा fb_info *fb_info);
बाह्य व्योम unरेजिस्टर_framebuffer(काष्ठा fb_info *fb_info);
बाह्य पूर्णांक हटाओ_conflicting_pci_framebuffers(काष्ठा pci_dev *pdev,
					       स्थिर अक्षर *name);
बाह्य पूर्णांक हटाओ_conflicting_framebuffers(काष्ठा apertures_काष्ठा *a,
					   स्थिर अक्षर *name, bool primary);
बाह्य पूर्णांक fb_prepare_logo(काष्ठा fb_info *fb_info, पूर्णांक rotate);
बाह्य पूर्णांक fb_show_logo(काष्ठा fb_info *fb_info, पूर्णांक rotate);
बाह्य अक्षर* fb_get_buffer_offset(काष्ठा fb_info *info, काष्ठा fb_pixmap *buf, u32 size);
बाह्य व्योम fb_pad_unaligned_buffer(u8 *dst, u32 d_pitch, u8 *src, u32 idx,
				u32 height, u32 shअगरt_high, u32 shअगरt_low, u32 mod);
बाह्य व्योम fb_pad_aligned_buffer(u8 *dst, u32 d_pitch, u8 *src, u32 s_pitch, u32 height);
बाह्य व्योम fb_set_suspend(काष्ठा fb_info *info, पूर्णांक state);
बाह्य पूर्णांक fb_get_color_depth(काष्ठा fb_var_screeninfo *var,
			      काष्ठा fb_fix_screeninfo *fix);
बाह्य पूर्णांक fb_get_options(स्थिर अक्षर *name, अक्षर **option);
बाह्य पूर्णांक fb_new_modelist(काष्ठा fb_info *info);

बाह्य काष्ठा fb_info *रेजिस्टरed_fb[FB_MAX];
बाह्य पूर्णांक num_रेजिस्टरed_fb;
बाह्य bool fb_center_logo;
बाह्य पूर्णांक fb_logo_count;
बाह्य काष्ठा class *fb_class;

#घोषणा क्रम_each_रेजिस्टरed_fb(i)		\
	क्रम (i = 0; i < FB_MAX; i++)		\
		अगर (!रेजिस्टरed_fb[i]) अणुपूर्ण अन्यथा

अटल अंतरभूत व्योम lock_fb_info(काष्ठा fb_info *info)
अणु
	mutex_lock(&info->lock);
पूर्ण

अटल अंतरभूत व्योम unlock_fb_info(काष्ठा fb_info *info)
अणु
	mutex_unlock(&info->lock);
पूर्ण

अटल अंतरभूत व्योम __fb_pad_aligned_buffer(u8 *dst, u32 d_pitch,
					   u8 *src, u32 s_pitch, u32 height)
अणु
	u32 i, j;

	d_pitch -= s_pitch;

	क्रम (i = height; i--; ) अणु
		/* s_pitch is a few bytes at the most, स_नकल is suboptimal */
		क्रम (j = 0; j < s_pitch; j++)
			*dst++ = *src++;
		dst += d_pitch;
	पूर्ण
पूर्ण

/* drivers/video/fb_defio.c */
पूर्णांक fb_deferred_io_mmap(काष्ठा fb_info *info, काष्ठा vm_area_काष्ठा *vma);
बाह्य व्योम fb_deferred_io_init(काष्ठा fb_info *info);
बाह्य व्योम fb_deferred_io_खोलो(काष्ठा fb_info *info,
				काष्ठा inode *inode,
				काष्ठा file *file);
बाह्य व्योम fb_deferred_io_cleanup(काष्ठा fb_info *info);
बाह्य पूर्णांक fb_deferred_io_fsync(काष्ठा file *file, loff_t start,
				loff_t end, पूर्णांक datasync);

अटल अंतरभूत bool fb_be_math(काष्ठा fb_info *info)
अणु
#अगर_घोषित CONFIG_FB_FOREIGN_ENDIAN
#अगर defined(CONFIG_FB_BOTH_ENDIAN)
	वापस info->flags & FBINFO_BE_MATH;
#या_अगर defined(CONFIG_FB_BIG_ENDIAN)
	वापस true;
#या_अगर defined(CONFIG_FB_LITTLE_ENDIAN)
	वापस false;
#पूर्ण_अगर /* CONFIG_FB_BOTH_ENDIAN */
#अन्यथा
#अगर_घोषित __BIG_ENDIAN
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर /* __BIG_ENDIAN */
#पूर्ण_अगर /* CONFIG_FB_FOREIGN_ENDIAN */
पूर्ण

/* drivers/video/fbsysfs.c */
बाह्य काष्ठा fb_info *framebuffer_alloc(माप_प्रकार size, काष्ठा device *dev);
बाह्य व्योम framebuffer_release(काष्ठा fb_info *info);
बाह्य पूर्णांक fb_init_device(काष्ठा fb_info *fb_info);
बाह्य व्योम fb_cleanup_device(काष्ठा fb_info *head);
बाह्य व्योम fb_bl_शेष_curve(काष्ठा fb_info *fb_info, u8 off, u8 min, u8 max);

/* drivers/video/fbmon.c */
#घोषणा FB_MAXTIMINGS		0
#घोषणा FB_VSYNCTIMINGS		1
#घोषणा FB_HSYNCTIMINGS		2
#घोषणा FB_DCLKTIMINGS		3
#घोषणा FB_IGNOREMON		0x100

#घोषणा FB_MODE_IS_UNKNOWN	0
#घोषणा FB_MODE_IS_DETAILED	1
#घोषणा FB_MODE_IS_STANDARD	2
#घोषणा FB_MODE_IS_VESA		4
#घोषणा FB_MODE_IS_CALCULATED	8
#घोषणा FB_MODE_IS_FIRST	16
#घोषणा FB_MODE_IS_FROM_VAR     32

बाह्य पूर्णांक fbmon_dpms(स्थिर काष्ठा fb_info *fb_info);
बाह्य पूर्णांक fb_get_mode(पूर्णांक flags, u32 val, काष्ठा fb_var_screeninfo *var,
		       काष्ठा fb_info *info);
बाह्य पूर्णांक fb_validate_mode(स्थिर काष्ठा fb_var_screeninfo *var,
			    काष्ठा fb_info *info);
बाह्य पूर्णांक fb_parse_edid(अचिन्हित अक्षर *edid, काष्ठा fb_var_screeninfo *var);
बाह्य स्थिर अचिन्हित अक्षर *fb_firmware_edid(काष्ठा device *device);
बाह्य व्योम fb_edid_to_monspecs(अचिन्हित अक्षर *edid,
				काष्ठा fb_monspecs *specs);
बाह्य व्योम fb_destroy_modedb(काष्ठा fb_videomode *modedb);
बाह्य पूर्णांक fb_find_mode_cvt(काष्ठा fb_videomode *mode, पूर्णांक margins, पूर्णांक rb);
बाह्य अचिन्हित अक्षर *fb_ddc_पढ़ो(काष्ठा i2c_adapter *adapter);

बाह्य पूर्णांक of_get_fb_videomode(काष्ठा device_node *np,
			       काष्ठा fb_videomode *fb,
			       पूर्णांक index);
बाह्य पूर्णांक fb_videomode_from_videomode(स्थिर काष्ठा videomode *vm,
				       काष्ठा fb_videomode *fbmode);

/* drivers/video/modedb.c */
#घोषणा VESA_MODEDB_SIZE 43
#घोषणा DMT_SIZE 0x50

बाह्य व्योम fb_var_to_videomode(काष्ठा fb_videomode *mode,
				स्थिर काष्ठा fb_var_screeninfo *var);
बाह्य व्योम fb_videomode_to_var(काष्ठा fb_var_screeninfo *var,
				स्थिर काष्ठा fb_videomode *mode);
बाह्य पूर्णांक fb_mode_is_equal(स्थिर काष्ठा fb_videomode *mode1,
			    स्थिर काष्ठा fb_videomode *mode2);
बाह्य पूर्णांक fb_add_videomode(स्थिर काष्ठा fb_videomode *mode,
			    काष्ठा list_head *head);
बाह्य व्योम fb_delete_videomode(स्थिर काष्ठा fb_videomode *mode,
				काष्ठा list_head *head);
बाह्य स्थिर काष्ठा fb_videomode *fb_match_mode(स्थिर काष्ठा fb_var_screeninfo *var,
						काष्ठा list_head *head);
बाह्य स्थिर काष्ठा fb_videomode *fb_find_best_mode(स्थिर काष्ठा fb_var_screeninfo *var,
						    काष्ठा list_head *head);
बाह्य स्थिर काष्ठा fb_videomode *fb_find_nearest_mode(स्थिर काष्ठा fb_videomode *mode,
						       काष्ठा list_head *head);
बाह्य व्योम fb_destroy_modelist(काष्ठा list_head *head);
बाह्य व्योम fb_videomode_to_modelist(स्थिर काष्ठा fb_videomode *modedb, पूर्णांक num,
				     काष्ठा list_head *head);
बाह्य स्थिर काष्ठा fb_videomode *fb_find_best_display(स्थिर काष्ठा fb_monspecs *specs,
						       काष्ठा list_head *head);

/* drivers/video/fbcmap.c */
बाह्य पूर्णांक fb_alloc_cmap(काष्ठा fb_cmap *cmap, पूर्णांक len, पूर्णांक transp);
बाह्य पूर्णांक fb_alloc_cmap_gfp(काष्ठा fb_cmap *cmap, पूर्णांक len, पूर्णांक transp, gfp_t flags);
बाह्य व्योम fb_dealloc_cmap(काष्ठा fb_cmap *cmap);
बाह्य पूर्णांक fb_copy_cmap(स्थिर काष्ठा fb_cmap *from, काष्ठा fb_cmap *to);
बाह्य पूर्णांक fb_cmap_to_user(स्थिर काष्ठा fb_cmap *from, काष्ठा fb_cmap_user *to);
बाह्य पूर्णांक fb_set_cmap(काष्ठा fb_cmap *cmap, काष्ठा fb_info *fb_info);
बाह्य पूर्णांक fb_set_user_cmap(काष्ठा fb_cmap_user *cmap, काष्ठा fb_info *fb_info);
बाह्य स्थिर काष्ठा fb_cmap *fb_शेष_cmap(पूर्णांक len);
बाह्य व्योम fb_invert_cmaps(व्योम);

काष्ठा fb_videomode अणु
	स्थिर अक्षर *name;	/* optional */
	u32 refresh;		/* optional */
	u32 xres;
	u32 yres;
	u32 pixघड़ी;
	u32 left_margin;
	u32 right_margin;
	u32 upper_margin;
	u32 lower_margin;
	u32 hsync_len;
	u32 vsync_len;
	u32 sync;
	u32 vmode;
	u32 flag;
पूर्ण;

काष्ठा dmt_videomode अणु
	u32 dmt_id;
	u32 std_2byte_code;
	u32 cvt_3byte_code;
	स्थिर काष्ठा fb_videomode *mode;
पूर्ण;

बाह्य स्थिर अक्षर *fb_mode_option;
बाह्य स्थिर काष्ठा fb_videomode vesa_modes[];
बाह्य स्थिर काष्ठा dmt_videomode dmt_modes[];

काष्ठा fb_modelist अणु
	काष्ठा list_head list;
	काष्ठा fb_videomode mode;
पूर्ण;

बाह्य पूर्णांक fb_find_mode(काष्ठा fb_var_screeninfo *var,
			काष्ठा fb_info *info, स्थिर अक्षर *mode_option,
			स्थिर काष्ठा fb_videomode *db,
			अचिन्हित पूर्णांक dbsize,
			स्थिर काष्ठा fb_videomode *शेष_mode,
			अचिन्हित पूर्णांक शेष_bpp);

/* Convenience logging macros */
#घोषणा fb_err(fb_info, fmt, ...)					\
	pr_err("fb%d: " fmt, (fb_info)->node, ##__VA_ARGS__)
#घोषणा fb_notice(info, fmt, ...)					\
	pr_notice("fb%d: " fmt, (fb_info)->node, ##__VA_ARGS__)
#घोषणा fb_warn(fb_info, fmt, ...)					\
	pr_warn("fb%d: " fmt, (fb_info)->node, ##__VA_ARGS__)
#घोषणा fb_info(fb_info, fmt, ...)					\
	pr_info("fb%d: " fmt, (fb_info)->node, ##__VA_ARGS__)
#घोषणा fb_dbg(fb_info, fmt, ...)					\
	pr_debug("fb%d: " fmt, (fb_info)->node, ##__VA_ARGS__)

#पूर्ण_अगर /* _LINUX_FB_H */
