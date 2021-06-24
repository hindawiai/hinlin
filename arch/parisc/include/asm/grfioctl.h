<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*  Architecture specअगरic parts of HP's STI (framebuffer) driver.
 *  Structures are HP-UX compatible क्रम XFree86 usage.
 * 
 *    Linux/PA-RISC Project (http://www.parisc-linux.org/)
 *    Copyright (C) 2001 Helge Deller (deller a parisc-linux org)
 */

#अगर_अघोषित __ASM_PARISC_GRFIOCTL_H
#घोषणा __ASM_PARISC_GRFIOCTL_H

/* upper 32 bits of graphics id (HP/UX identअगरier) */

#घोषणा GRFGATOR		8
#घोषणा S9000_ID_S300		9
#घोषणा GRFBOBCAT		9
#घोषणा	GRFCATSEYE		9
#घोषणा S9000_ID_98720		10
#घोषणा GRFRBOX			10
#घोषणा S9000_ID_98550		11
#घोषणा GRFFIREEYE		11
#घोषणा S9000_ID_A1096A		12
#घोषणा GRFHYPERION		12
#घोषणा S9000_ID_FRI		13
#घोषणा S9000_ID_98730		14
#घोषणा GRFDAVINCI		14
#घोषणा S9000_ID_98705		0x26C08070	/* Tigershark */
#घोषणा S9000_ID_98736		0x26D148AB
#घोषणा S9000_ID_A1659A		0x26D1482A	/* CRX 8 plane color (=ELK) */
#घोषणा S9000_ID_ELK		S9000_ID_A1659A
#घोषणा S9000_ID_A1439A		0x26D148EE	/* CRX24 = CRX+ (24-plane color) */
#घोषणा S9000_ID_A1924A		0x26D1488C	/* GRX gray-scale */
#घोषणा S9000_ID_ELM		S9000_ID_A1924A
#घोषणा S9000_ID_98765		0x27480DEF
#घोषणा S9000_ID_ELK_768	0x27482101
#घोषणा S9000_ID_STINGER	0x27A4A402
#घोषणा S9000_ID_TIMBER		0x27F12392	/* Bushmaster (710) Graphics */
#घोषणा S9000_ID_TOMCAT		0x27FCCB6D	/* dual-headed ELK (Dual CRX) */
#घोषणा S9000_ID_ARTIST		0x2B4DED6D	/* Artist (Gecko/712 & 715) onboard Graphics */
#घोषणा S9000_ID_HCRX		0x2BCB015A	/* Hyperdrive/Hyperbowl (A4071A) Graphics */
#घोषणा CRX24_OVERLAY_PLANES	0x920825AA	/* Overlay planes on CRX24 */

#घोषणा CRT_ID_ELK_1024		S9000_ID_ELK_768 /* Elk 1024x768  CRX */
#घोषणा CRT_ID_ELK_1280		S9000_ID_A1659A	/* Elk 1280x1024 CRX */
#घोषणा CRT_ID_ELK_1024DB	0x27849CA5      /* Elk 1024x768 द्विगुन buffer */
#घोषणा CRT_ID_ELK_GS		S9000_ID_A1924A	/* Elk 1280x1024 GreyScale    */
#घोषणा CRT_ID_CRX24		S9000_ID_A1439A	/* Piranha */
#घोषणा CRT_ID_VISUALIZE_EG	0x2D08C0A7      /* Graffiti, A4450A (built-in B132+/B160L) */
#घोषणा CRT_ID_THUNDER		0x2F23E5FC      /* Thunder 1 VISUALIZE 48*/
#घोषणा CRT_ID_THUNDER2		0x2F8D570E      /* Thunder 2 VISUALIZE 48 XP*/
#घोषणा CRT_ID_HCRX		S9000_ID_HCRX	/* Hyperdrive HCRX */
#घोषणा CRT_ID_CRX48Z		S9000_ID_STINGER /* Stinger */
#घोषणा CRT_ID_DUAL_CRX		S9000_ID_TOMCAT	/* Tomcat */
#घोषणा CRT_ID_PVRX		S9000_ID_98705	/* Tigershark */
#घोषणा CRT_ID_TIMBER		S9000_ID_TIMBER	/* Timber (710 builtin) */
#घोषणा CRT_ID_TVRX		S9000_ID_98765	/* TVRX (gto/falcon) */
#घोषणा CRT_ID_ARTIST		S9000_ID_ARTIST	/* Artist */
#घोषणा CRT_ID_SUMMIT		0x2FC1066B      /* Summit FX2, FX4, FX6 ... */
#घोषणा CRT_ID_LEGO		0x35ACDA30	/* Lego FX5, FX10 ... */
#घोषणा CRT_ID_PINNACLE		0x35ACDA16	/* Pinnacle FXe */ 

/* काष्ठाure क्रम ioctl(GCDESCRIBE) */

#घोषणा gaddr_t अचिन्हित दीर्घ	/* FIXME: PA2.0 (64bit) portable ? */

काष्ठा	grf_fbinfo अणु
	अचिन्हित पूर्णांक	id;		/* upper 32 bits of graphics id */
	अचिन्हित पूर्णांक	mapsize;	/* mapped size of framebuffer */
	अचिन्हित पूर्णांक	dwidth, dlength;/* x and y sizes */
	अचिन्हित पूर्णांक	width, length;	/* total x and total y size */
	अचिन्हित पूर्णांक	xlen;		/* x pitch size */
	अचिन्हित पूर्णांक	bpp, bppu;	/* bits per pixel and used bpp */
	अचिन्हित पूर्णांक	npl, nplbytes;	/* # of planes and bytes per plane */
	अक्षर		name[32];	/* name of the device (from ROM) */
	अचिन्हित पूर्णांक	attr;		/* attributes */
	gaddr_t 	fbbase, regbase;/* framebuffer and रेजिस्टर base addr */
	gaddr_t		regions[6];	/* region bases */
पूर्ण;

#घोषणा	GCID		_IOR('G', 0, पूर्णांक)
#घोषणा	GCON		_IO('G', 1)
#घोषणा	GCOFF		_IO('G', 2)
#घोषणा	GCAON		_IO('G', 3)
#घोषणा	GCAOFF		_IO('G', 4)
#घोषणा	GCMAP		_IOWR('G', 5, पूर्णांक)
#घोषणा	GCUNMAP		_IOWR('G', 6, पूर्णांक)
#घोषणा	GCMAP_HPUX	_IO('G', 5)
#घोषणा	GCUNMAP_HPUX	_IO('G', 6)
#घोषणा	GCLOCK		_IO('G', 7)
#घोषणा	GCUNLOCK	_IO('G', 8)
#घोषणा	GCLOCK_MINIMUM	_IO('G', 9)
#घोषणा	GCUNLOCK_MINIMUM _IO('G', 10)
#घोषणा	GCSTATIC_CMAP	_IO('G', 11)
#घोषणा	GCVARIABLE_CMAP _IO('G', 12)
#घोषणा GCTERM		_IOWR('G',20,पूर्णांक)	/* multi-headed Tomcat */ 
#घोषणा GCDESCRIBE	_IOR('G', 21, काष्ठा grf_fbinfo)
#घोषणा GCFASTLOCK	_IO('G', 26)

#पूर्ण_अगर /* __ASM_PARISC_GRFIOCTL_H */

