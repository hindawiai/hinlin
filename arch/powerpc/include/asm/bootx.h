<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file describes the काष्ठाure passed from the BootX application
 * (क्रम MacOS) when it is used to boot Linux.
 *
 * Written by Benjamin Herrenschmidt.
 */

#अगर_अघोषित __ASM_BOOTX_H__
#घोषणा __ASM_BOOTX_H__

#समावेश <uapi/यंत्र/bootx.h>

/* (*) The क्रमmat of the colormap is 256 * 3 * 2 bytes. Each color index
 * is represented by 3 लघु words containing a 16 bits (अचिन्हित) color
 * component. Later versions may contain the gamma table क्रम direct-color
 * devices here.
 */
#घोषणा BOOTX_COLORTABLE_SIZE    (256UL*3UL*2UL)

/* BootX passes the device-tree using a क्रमmat that comes from earlier
 * ppc32 kernels. This used to match what is in prom.h, but not anymore
 * so we now define it here
 */
काष्ठा bootx_dt_prop अणु
	u32	name;
	पूर्णांक	length;
	u32	value;
	u32	next;
पूर्ण;

काष्ठा bootx_dt_node अणु
	u32	unused0;
	u32	unused1;
	u32	phandle;	/* not really available */
	u32	unused2;
	u32	unused3;
	u32	unused4;
	u32	unused5;
	u32	full_name;
	u32	properties;
	u32	parent;
	u32	child;
	u32	sibling;
	u32	next;
	u32	allnext;
पूर्ण;

बाह्य व्योम bootx_init(अचिन्हित दीर्घ r4, अचिन्हित दीर्घ phys);

#पूर्ण_अगर
