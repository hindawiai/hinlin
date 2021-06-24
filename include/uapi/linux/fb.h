<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_LINUX_FB_H
#घोषणा _UAPI_LINUX_FB_H

#समावेश <linux/types.h>
#समावेश <linux/i2c.h>

/* Definitions of frame buffers						*/

#घोषणा FB_MAX			32	/* sufficient क्रम now */

/* ioctls
   0x46 is 'F'								*/
#घोषणा FBIOGET_VSCREENINFO	0x4600
#घोषणा FBIOPUT_VSCREENINFO	0x4601
#घोषणा FBIOGET_FSCREENINFO	0x4602
#घोषणा FBIOGETCMAP		0x4604
#घोषणा FBIOPUTCMAP		0x4605
#घोषणा FBIOPAN_DISPLAY		0x4606
#अगर_अघोषित __KERNEL__
#घोषणा FBIO_CURSOR            _IOWR('F', 0x08, काष्ठा fb_cursor)
#पूर्ण_अगर
/* 0x4607-0x460B are defined below */
/* #घोषणा FBIOGET_MONITORSPEC	0x460C */
/* #घोषणा FBIOPUT_MONITORSPEC	0x460D */
/* #घोषणा FBIOSWITCH_MONIBIT	0x460E */
#घोषणा FBIOGET_CON2FBMAP	0x460F
#घोषणा FBIOPUT_CON2FBMAP	0x4610
#घोषणा FBIOBLANK		0x4611		/* arg: 0 or vesa level + 1 */
#घोषणा FBIOGET_VBLANK		_IOR('F', 0x12, काष्ठा fb_vblank)
#घोषणा FBIO_ALLOC              0x4613
#घोषणा FBIO_FREE               0x4614
#घोषणा FBIOGET_GLYPH           0x4615
#घोषणा FBIOGET_HWCINFO         0x4616
#घोषणा FBIOPUT_MODEINFO        0x4617
#घोषणा FBIOGET_DISPINFO        0x4618
#घोषणा FBIO_WAITFORVSYNC	_IOW('F', 0x20, __u32)

#घोषणा FB_TYPE_PACKED_PIXELS		0	/* Packed Pixels	*/
#घोषणा FB_TYPE_PLANES			1	/* Non पूर्णांकerleaved planes */
#घोषणा FB_TYPE_INTERLEAVED_PLANES	2	/* Interleaved planes	*/
#घोषणा FB_TYPE_TEXT			3	/* Text/attributes	*/
#घोषणा FB_TYPE_VGA_PLANES		4	/* EGA/VGA planes	*/
#घोषणा FB_TYPE_FOURCC			5	/* Type identअगरied by a V4L2 FOURCC */

#घोषणा FB_AUX_TEXT_MDA		0	/* Monochrome text */
#घोषणा FB_AUX_TEXT_CGA		1	/* CGA/EGA/VGA Color text */
#घोषणा FB_AUX_TEXT_S3_MMIO	2	/* S3 MMIO fasttext */
#घोषणा FB_AUX_TEXT_MGA_STEP16	3	/* MGA Millenium I: text, attr, 14 reserved bytes */
#घोषणा FB_AUX_TEXT_MGA_STEP8	4	/* other MGAs:      text, attr,  6 reserved bytes */
#घोषणा FB_AUX_TEXT_SVGA_GROUP	8	/* 8-15: SVGA tileblit compatible modes */
#घोषणा FB_AUX_TEXT_SVGA_MASK	7	/* lower three bits says step */
#घोषणा FB_AUX_TEXT_SVGA_STEP2	8	/* SVGA text mode:  text, attr */
#घोषणा FB_AUX_TEXT_SVGA_STEP4	9	/* SVGA text mode:  text, attr,  2 reserved bytes */
#घोषणा FB_AUX_TEXT_SVGA_STEP8	10	/* SVGA text mode:  text, attr,  6 reserved bytes */
#घोषणा FB_AUX_TEXT_SVGA_STEP16	11	/* SVGA text mode:  text, attr, 14 reserved bytes */
#घोषणा FB_AUX_TEXT_SVGA_LAST	15	/* reserved up to 15 */

#घोषणा FB_AUX_VGA_PLANES_VGA4		0	/* 16 color planes (EGA/VGA) */
#घोषणा FB_AUX_VGA_PLANES_CFB4		1	/* CFB4 in planes (VGA) */
#घोषणा FB_AUX_VGA_PLANES_CFB8		2	/* CFB8 in planes (VGA) */

#घोषणा FB_VISUAL_MONO01		0	/* Monochr. 1=Black 0=White */
#घोषणा FB_VISUAL_MONO10		1	/* Monochr. 1=White 0=Black */
#घोषणा FB_VISUAL_TRUECOLOR		2	/* True color	*/
#घोषणा FB_VISUAL_PSEUDOCOLOR		3	/* Pseuकरो color (like atari) */
#घोषणा FB_VISUAL_सूचीECTCOLOR		4	/* Direct color */
#घोषणा FB_VISUAL_STATIC_PSEUDOCOLOR	5	/* Pseuकरो color पढ़ोonly */
#घोषणा FB_VISUAL_FOURCC		6	/* Visual identअगरied by a V4L2 FOURCC */

#घोषणा FB_ACCEL_NONE		0	/* no hardware accelerator	*/
#घोषणा FB_ACCEL_ATARIBLITT	1	/* Atari Blitter		*/
#घोषणा FB_ACCEL_AMIGABLITT	2	/* Amiga Blitter                */
#घोषणा FB_ACCEL_S3_TRIO64	3	/* Cybervision64 (S3 Trio64)    */
#घोषणा FB_ACCEL_NCR_77C32BLT	4	/* RetinaZ3 (NCR 77C32BLT)      */
#घोषणा FB_ACCEL_S3_VIRGE	5	/* Cybervision64/3D (S3 ViRGE)	*/
#घोषणा FB_ACCEL_ATI_MACH64GX	6	/* ATI Mach 64GX family		*/
#घोषणा FB_ACCEL_DEC_TGA	7	/* DEC 21030 TGA		*/
#घोषणा FB_ACCEL_ATI_MACH64CT	8	/* ATI Mach 64CT family		*/
#घोषणा FB_ACCEL_ATI_MACH64VT	9	/* ATI Mach 64CT family VT class */
#घोषणा FB_ACCEL_ATI_MACH64GT	10	/* ATI Mach 64CT family GT class */
#घोषणा FB_ACCEL_SUN_CREATOR	11	/* Sun Creator/Creator3D	*/
#घोषणा FB_ACCEL_SUN_CGSIX	12	/* Sun cg6			*/
#घोषणा FB_ACCEL_SUN_LEO	13	/* Sun leo/zx			*/
#घोषणा FB_ACCEL_IMS_TWINTURBO	14	/* IMS Twin Turbo		*/
#घोषणा FB_ACCEL_3DLABS_PERMEDIA2 15	/* 3Dद_असल Permedia 2		*/
#घोषणा FB_ACCEL_MATROX_MGA2064W 16	/* Matrox MGA2064W (Millenium)	*/
#घोषणा FB_ACCEL_MATROX_MGA1064SG 17	/* Matrox MGA1064SG (Mystique)	*/
#घोषणा FB_ACCEL_MATROX_MGA2164W 18	/* Matrox MGA2164W (Millenium II) */
#घोषणा FB_ACCEL_MATROX_MGA2164W_AGP 19	/* Matrox MGA2164W (Millenium II) */
#घोषणा FB_ACCEL_MATROX_MGAG100	20	/* Matrox G100 (Productiva G100) */
#घोषणा FB_ACCEL_MATROX_MGAG200	21	/* Matrox G200 (Myst, Mill, ...) */
#घोषणा FB_ACCEL_SUN_CG14	22	/* Sun cgfourteen		 */
#घोषणा FB_ACCEL_SUN_BWTWO	23	/* Sun bwtwo			*/
#घोषणा FB_ACCEL_SUN_CGTHREE	24	/* Sun cgthree			*/
#घोषणा FB_ACCEL_SUN_TCX	25	/* Sun tcx			*/
#घोषणा FB_ACCEL_MATROX_MGAG400	26	/* Matrox G400			*/
#घोषणा FB_ACCEL_NV3		27	/* nVidia RIVA 128              */
#घोषणा FB_ACCEL_NV4		28	/* nVidia RIVA TNT		*/
#घोषणा FB_ACCEL_NV5		29	/* nVidia RIVA TNT2		*/
#घोषणा FB_ACCEL_CT_6555x	30	/* C&T 6555x			*/
#घोषणा FB_ACCEL_3DFX_BANSHEE	31	/* 3Dfx Banshee			*/
#घोषणा FB_ACCEL_ATI_RAGE128	32	/* ATI Rage128 family		*/
#घोषणा FB_ACCEL_IGS_CYBER2000	33	/* CyberPro 2000		*/
#घोषणा FB_ACCEL_IGS_CYBER2010	34	/* CyberPro 2010		*/
#घोषणा FB_ACCEL_IGS_CYBER5000	35	/* CyberPro 5000		*/
#घोषणा FB_ACCEL_SIS_GLAMOUR    36	/* SiS 300/630/540              */
#घोषणा FB_ACCEL_3DLABS_PERMEDIA3 37	/* 3Dद_असल Permedia 3		*/
#घोषणा FB_ACCEL_ATI_RADEON	38	/* ATI Radeon family		*/
#घोषणा FB_ACCEL_I810           39      /* Intel 810/815                */
#घोषणा FB_ACCEL_SIS_GLAMOUR_2  40	/* SiS 315, 650, 740		*/
#घोषणा FB_ACCEL_SIS_XABRE      41	/* SiS 330 ("Xabre")		*/
#घोषणा FB_ACCEL_I830           42      /* Intel 830M/845G/85x/865G     */
#घोषणा FB_ACCEL_NV_10          43      /* nVidia Arch 10               */
#घोषणा FB_ACCEL_NV_20          44      /* nVidia Arch 20               */
#घोषणा FB_ACCEL_NV_30          45      /* nVidia Arch 30               */
#घोषणा FB_ACCEL_NV_40          46      /* nVidia Arch 40               */
#घोषणा FB_ACCEL_XGI_VOLARI_V	47	/* XGI Volari V3XT, V5, V8      */
#घोषणा FB_ACCEL_XGI_VOLARI_Z	48	/* XGI Volari Z7                */
#घोषणा FB_ACCEL_OMAP1610	49	/* TI OMAP16xx                  */
#घोषणा FB_ACCEL_TRIDENT_TGUI	50	/* Trident TGUI			*/
#घोषणा FB_ACCEL_TRIDENT_3DIMAGE 51	/* Trident 3DImage		*/
#घोषणा FB_ACCEL_TRIDENT_BLADE3D 52	/* Trident Blade3D		*/
#घोषणा FB_ACCEL_TRIDENT_BLADEXP 53	/* Trident BladeXP		*/
#घोषणा FB_ACCEL_CIRRUS_ALPINE   53	/* Cirrus Logic 543x/544x/5480	*/
#घोषणा FB_ACCEL_NEOMAGIC_NM2070 90	/* NeoMagic NM2070              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2090 91	/* NeoMagic NM2090              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2093 92	/* NeoMagic NM2093              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2097 93	/* NeoMagic NM2097              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2160 94	/* NeoMagic NM2160              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2200 95	/* NeoMagic NM2200              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2230 96	/* NeoMagic NM2230              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2360 97	/* NeoMagic NM2360              */
#घोषणा FB_ACCEL_NEOMAGIC_NM2380 98	/* NeoMagic NM2380              */
#घोषणा FB_ACCEL_PXA3XX		 99	/* PXA3xx			*/

#घोषणा FB_ACCEL_SAVAGE4        0x80	/* S3 Savage4                   */
#घोषणा FB_ACCEL_SAVAGE3D       0x81	/* S3 Savage3D                  */
#घोषणा FB_ACCEL_SAVAGE3D_MV    0x82	/* S3 Savage3D-MV               */
#घोषणा FB_ACCEL_SAVAGE2000     0x83	/* S3 Savage2000                */
#घोषणा FB_ACCEL_SAVAGE_MX_MV   0x84	/* S3 Savage/MX-MV              */
#घोषणा FB_ACCEL_SAVAGE_MX      0x85	/* S3 Savage/MX                 */
#घोषणा FB_ACCEL_SAVAGE_IX_MV   0x86	/* S3 Savage/IX-MV              */
#घोषणा FB_ACCEL_SAVAGE_IX      0x87	/* S3 Savage/IX                 */
#घोषणा FB_ACCEL_PROSAVAGE_PM   0x88	/* S3 ProSavage PM133           */
#घोषणा FB_ACCEL_PROSAVAGE_KM   0x89	/* S3 ProSavage KM133           */
#घोषणा FB_ACCEL_S3TWISTER_P    0x8a	/* S3 Twister                   */
#घोषणा FB_ACCEL_S3TWISTER_K    0x8b	/* S3 TwisterK                  */
#घोषणा FB_ACCEL_SUPERSAVAGE    0x8c    /* S3 Supersavage               */
#घोषणा FB_ACCEL_PROSAVAGE_DDR  0x8d	/* S3 ProSavage DDR             */
#घोषणा FB_ACCEL_PROSAVAGE_DDRK 0x8e	/* S3 ProSavage DDR-K           */

#घोषणा FB_ACCEL_PUV3_UNIGFX	0xa0	/* PKUnity-v3 Unigfx		*/

#घोषणा FB_CAP_FOURCC		1	/* Device supports FOURCC-based क्रमmats */

काष्ठा fb_fix_screeninfo अणु
	अक्षर id[16];			/* identअगरication string eg "TT Builtin" */
	अचिन्हित दीर्घ smem_start;	/* Start of frame buffer mem */
					/* (physical address) */
	__u32 smem_len;			/* Length of frame buffer mem */
	__u32 type;			/* see FB_TYPE_*		*/
	__u32 type_aux;			/* Interleave क्रम पूर्णांकerleaved Planes */
	__u32 visual;			/* see FB_VISUAL_*		*/ 
	__u16 xpanstep;			/* zero अगर no hardware panning  */
	__u16 ypanstep;			/* zero अगर no hardware panning  */
	__u16 ywrapstep;		/* zero अगर no hardware ywrap    */
	__u32 line_length;		/* length of a line in bytes    */
	अचिन्हित दीर्घ mmio_start;	/* Start of Memory Mapped I/O   */
					/* (physical address) */
	__u32 mmio_len;			/* Length of Memory Mapped I/O  */
	__u32 accel;			/* Indicate to driver which	*/
					/*  specअगरic chip/card we have	*/
	__u16 capabilities;		/* see FB_CAP_*			*/
	__u16 reserved[2];		/* Reserved क्रम future compatibility */
पूर्ण;

/* Interpretation of offset क्रम color fields: All offsets are from the right,
 * inside a "pixel" value, which is exactly 'bits_per_pixel' wide (means: you
 * can use the offset as right argument to <<). A pixel afterwards is a bit
 * stream and is written to video memory as that unmodअगरied.
 *
 * For pseuकरोcolor: offset and length should be the same क्रम all color
 * components. Offset specअगरies the position of the least signअगरicant bit
 * of the pallette index in a pixel value. Length indicates the number
 * of available palette entries (i.e. # of entries = 1 << length).
 */
काष्ठा fb_bitfield अणु
	__u32 offset;			/* beginning of bitfield	*/
	__u32 length;			/* length of bitfield		*/
	__u32 msb_right;		/* != 0 : Most signअगरicant bit is */ 
					/* right */ 
पूर्ण;

#घोषणा FB_NONSTD_HAM		1	/* Hold-And-Modअगरy (HAM)        */
#घोषणा FB_NONSTD_REV_PIX_IN_B	2	/* order of pixels in each byte is reversed */

#घोषणा FB_ACTIVATE_NOW		0	/* set values immediately (or vbl)*/
#घोषणा FB_ACTIVATE_NXTOPEN	1	/* activate on next खोलो	*/
#घोषणा FB_ACTIVATE_TEST	2	/* करोn't set, round up impossible */
#घोषणा FB_ACTIVATE_MASK       15
					/* values			*/
#घोषणा FB_ACTIVATE_VBL	       16	/* activate values on next vbl  */
#घोषणा FB_CHANGE_CMAP_VBL     32	/* change colormap on vbl	*/
#घोषणा FB_ACTIVATE_ALL	       64	/* change all VCs on this fb	*/
#घोषणा FB_ACTIVATE_FORCE     128	/* क्रमce apply even when no change*/
#घोषणा FB_ACTIVATE_INV_MODE  256       /* invalidate videomode */
#घोषणा FB_ACTIVATE_KD_TEXT   512       /* क्रम KDSET vt ioctl */

#घोषणा FB_ACCELF_TEXT		1	/* (OBSOLETE) see fb_info.flags and vc_mode */

#घोषणा FB_SYNC_HOR_HIGH_ACT	1	/* horizontal sync high active	*/
#घोषणा FB_SYNC_VERT_HIGH_ACT	2	/* vertical sync high active	*/
#घोषणा FB_SYNC_EXT		4	/* बाह्यal sync		*/
#घोषणा FB_SYNC_COMP_HIGH_ACT	8	/* composite sync high active   */
#घोषणा FB_SYNC_BROADCAST	16	/* broadcast video timings      */
					/* vtotal = 144d/288n/576i => PAL  */
					/* vtotal = 121d/242n/484i => NTSC */
#घोषणा FB_SYNC_ON_GREEN	32	/* sync on green */

#घोषणा FB_VMODE_NONINTERLACED  0	/* non पूर्णांकerlaced */
#घोषणा FB_VMODE_INTERLACED	1	/* पूर्णांकerlaced	*/
#घोषणा FB_VMODE_DOUBLE		2	/* द्विगुन scan */
#घोषणा FB_VMODE_ODD_FLD_FIRST	4	/* पूर्णांकerlaced: top line first */
#घोषणा FB_VMODE_MASK		255

#घोषणा FB_VMODE_YWRAP		256	/* ywrap instead of panning     */
#घोषणा FB_VMODE_SMOOTH_XPAN	512	/* smooth xpan possible (पूर्णांकernally used) */
#घोषणा FB_VMODE_CONUPDATE	512	/* करोn't update x/yoffset	*/

/*
 * Display rotation support
 */
#घोषणा FB_ROTATE_UR      0
#घोषणा FB_ROTATE_CW      1
#घोषणा FB_ROTATE_UD      2
#घोषणा FB_ROTATE_CCW     3

#घोषणा PICOS2KHZ(a) (1000000000UL/(a))
#घोषणा KHZ2PICOS(a) (1000000000UL/(a))

काष्ठा fb_var_screeninfo अणु
	__u32 xres;			/* visible resolution		*/
	__u32 yres;
	__u32 xres_भव;		/* भव resolution		*/
	__u32 yres_भव;
	__u32 xoffset;			/* offset from भव to visible */
	__u32 yoffset;			/* resolution			*/

	__u32 bits_per_pixel;		/* guess what			*/
	__u32 grayscale;		/* 0 = color, 1 = grayscale,	*/
					/* >1 = FOURCC			*/
	काष्ठा fb_bitfield red;		/* bitfield in fb mem अगर true color, */
	काष्ठा fb_bitfield green;	/* अन्यथा only length is signअगरicant */
	काष्ठा fb_bitfield blue;
	काष्ठा fb_bitfield transp;	/* transparency			*/	

	__u32 nonstd;			/* != 0 Non standard pixel क्रमmat */

	__u32 activate;			/* see FB_ACTIVATE_*		*/

	__u32 height;			/* height of picture in mm    */
	__u32 width;			/* width of picture in mm     */

	__u32 accel_flags;		/* (OBSOLETE) see fb_info.flags */

	/* Timing: All values in pixघड़ीs, except pixघड़ी (of course) */
	__u32 pixघड़ी;			/* pixel घड़ी in ps (pico seconds) */
	__u32 left_margin;		/* समय from sync to picture	*/
	__u32 right_margin;		/* समय from picture to sync	*/
	__u32 upper_margin;		/* समय from sync to picture	*/
	__u32 lower_margin;
	__u32 hsync_len;		/* length of horizontal sync	*/
	__u32 vsync_len;		/* length of vertical sync	*/
	__u32 sync;			/* see FB_SYNC_*		*/
	__u32 vmode;			/* see FB_VMODE_*		*/
	__u32 rotate;			/* angle we rotate counter घड़ीwise */
	__u32 colorspace;		/* colorspace क्रम FOURCC-based modes */
	__u32 reserved[4];		/* Reserved क्रम future compatibility */
पूर्ण;

काष्ठा fb_cmap अणु
	__u32 start;			/* First entry	*/
	__u32 len;			/* Number of entries */
	__u16 *red;			/* Red values	*/
	__u16 *green;
	__u16 *blue;
	__u16 *transp;			/* transparency, can be शून्य */
पूर्ण;

काष्ठा fb_con2fbmap अणु
	__u32 console;
	__u32 framebuffer;
पूर्ण;

/* VESA Blanking Levels */
#घोषणा VESA_NO_BLANKING        0
#घोषणा VESA_VSYNC_SUSPEND      1
#घोषणा VESA_HSYNC_SUSPEND      2
#घोषणा VESA_POWERDOWN          3


क्रमागत अणु
	/* screen: unblanked, hsync: on,  vsync: on */
	FB_BLANK_UNBLANK       = VESA_NO_BLANKING,

	/* screen: blanked,   hsync: on,  vsync: on */
	FB_BLANK_NORMAL        = VESA_NO_BLANKING + 1,

	/* screen: blanked,   hsync: on,  vsync: off */
	FB_BLANK_VSYNC_SUSPEND = VESA_VSYNC_SUSPEND + 1,

	/* screen: blanked,   hsync: off, vsync: on */
	FB_BLANK_HSYNC_SUSPEND = VESA_HSYNC_SUSPEND + 1,

	/* screen: blanked,   hsync: off, vsync: off */
	FB_BLANK_POWERDOWN     = VESA_POWERDOWN + 1
पूर्ण;

#घोषणा FB_VBLANK_VBLANKING	0x001	/* currently in a vertical blank */
#घोषणा FB_VBLANK_HBLANKING	0x002	/* currently in a horizontal blank */
#घोषणा FB_VBLANK_HAVE_VBLANK	0x004	/* vertical blanks can be detected */
#घोषणा FB_VBLANK_HAVE_HBLANK	0x008	/* horizontal blanks can be detected */
#घोषणा FB_VBLANK_HAVE_COUNT	0x010	/* global retrace counter is available */
#घोषणा FB_VBLANK_HAVE_VCOUNT	0x020	/* the vcount field is valid */
#घोषणा FB_VBLANK_HAVE_HCOUNT	0x040	/* the hcount field is valid */
#घोषणा FB_VBLANK_VSYNCING	0x080	/* currently in a vsync */
#घोषणा FB_VBLANK_HAVE_VSYNC	0x100	/* verical syncs can be detected */

काष्ठा fb_vblank अणु
	__u32 flags;			/* FB_VBLANK flags */
	__u32 count;			/* counter of retraces since boot */
	__u32 vcount;			/* current scanline position */
	__u32 hcount;			/* current scanकरोt position */
	__u32 reserved[4];		/* reserved क्रम future compatibility */
पूर्ण;

/* Internal HW accel */
#घोषणा ROP_COPY 0
#घोषणा ROP_XOR  1

काष्ठा fb_copyarea अणु
	__u32 dx;
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 sx;
	__u32 sy;
पूर्ण;

काष्ठा fb_fillrect अणु
	__u32 dx;	/* screen-relative */
	__u32 dy;
	__u32 width;
	__u32 height;
	__u32 color;
	__u32 rop;
पूर्ण;

काष्ठा fb_image अणु
	__u32 dx;		/* Where to place image */
	__u32 dy;
	__u32 width;		/* Size of image */
	__u32 height;
	__u32 fg_color;		/* Only used when a mono biपंचांगap */
	__u32 bg_color;
	__u8  depth;		/* Depth of the image */
	स्थिर अक्षर *data;	/* Poपूर्णांकer to image data */
	काष्ठा fb_cmap cmap;	/* color map info */
पूर्ण;

/*
 * hardware cursor control
 */

#घोषणा FB_CUR_SETIMAGE 0x01
#घोषणा FB_CUR_SETPOS   0x02
#घोषणा FB_CUR_SETHOT   0x04
#घोषणा FB_CUR_SETCMAP  0x08
#घोषणा FB_CUR_SETSHAPE 0x10
#घोषणा FB_CUR_SETSIZE	0x20
#घोषणा FB_CUR_SETALL   0xFF

काष्ठा fbcurpos अणु
	__u16 x, y;
पूर्ण;

काष्ठा fb_cursor अणु
	__u16 set;		/* what to set */
	__u16 enable;		/* cursor on/off */
	__u16 rop;		/* bitop operation */
	स्थिर अक्षर *mask;	/* cursor mask bits */
	काष्ठा fbcurpos hot;	/* cursor hot spot */
	काष्ठा fb_image	image;	/* Cursor image */
पूर्ण;

/* Settings क्रम the generic backlight code */
#घोषणा FB_BACKLIGHT_LEVELS	128
#घोषणा FB_BACKLIGHT_MAX	0xFF


#पूर्ण_अगर /* _UAPI_LINUX_FB_H */
