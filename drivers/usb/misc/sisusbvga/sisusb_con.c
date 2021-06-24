<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * sisusb - usb kernel driver क्रम SiS315(E) based USB2VGA करोngles
 *
 * VGA text mode console part
 *
 * Copyright (C) 2005 by Thomas Winischhofer, Vienna, Austria
 *
 * If distributed as part of the Linux kernel, this code is licensed under the
 * terms of the GPL v2.
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary क्रमms, with or without
 * * modअगरication, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary क्रमm must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    करोcumentation and/or other materials provided with the distribution.
 * * 3) The name of the author may not be used to enकरोrse or promote products
 * *    derived from this software without specअगरic psisusbr written permission.
 * *
 * * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESSED OR
 * * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY सूचीECT, INसूचीECT,
 * * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Thomas Winischhofer <thomas@winischhofer.net>
 *
 * Portions based on vgacon.c which are
 *	Created 28 Sep 1997 by Geert Uytterhoeven
 *      Rewritten by Martin Mares <mj@ucw.cz>, July 1998
 *      based on code Copyright (C) 1991, 1992  Linus Torvalds
 *			    1995  Jay Estabrook
 *
 * A note on using in_atomic() in here: We can't handle console
 * calls from non-schedulable context due to our USB-dependend
 * nature. For now, this driver just ignores any calls अगर it
 * detects this state.
 *
 */

#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/fs.h>
#समावेश <linux/usb.h>
#समावेश <linux/tty.h>
#समावेश <linux/console.h>
#समावेश <linux/माला.स>
#समावेश <linux/kd.h>
#समावेश <linux/init.h>
#समावेश <linux/vt_kern.h>
#समावेश <linux/selection.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/kref.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "sisusb.h"
#समावेश "sisusb_init.h"

/* vc_data -> sisusb conversion table */
अटल काष्ठा sisusb_usb_data *mysisusbs[MAX_NR_CONSOLES];

/* Forward declaration */
अटल स्थिर काष्ठा consw sisusb_con;

अटल अंतरभूत व्योम
sisusbcon_स_रखोw(u16 *s, u16 c, अचिन्हित पूर्णांक count)
अणु
	स_रखो16(s, c, count / 2);
पूर्ण

अटल अंतरभूत व्योम
sisusb_initialize(काष्ठा sisusb_usb_data *sisusb)
अणु
	/* Reset cursor and start address */
	अगर (sisusb_setidxreg(sisusb, SISCR, 0x0c, 0x00))
		वापस;
	अगर (sisusb_setidxreg(sisusb, SISCR, 0x0d, 0x00))
		वापस;
	अगर (sisusb_setidxreg(sisusb, SISCR, 0x0e, 0x00))
		वापस;
	sisusb_setidxreg(sisusb, SISCR, 0x0f, 0x00);
पूर्ण

अटल अंतरभूत व्योम
sisusbcon_set_start_address(काष्ठा sisusb_usb_data *sisusb, काष्ठा vc_data *c)
अणु
	sisusb->cur_start_addr = (c->vc_visible_origin - sisusb->scrbuf) / 2;

	sisusb_setidxreg(sisusb, SISCR, 0x0c, (sisusb->cur_start_addr >> 8));
	sisusb_setidxreg(sisusb, SISCR, 0x0d, (sisusb->cur_start_addr & 0xff));
पूर्ण

व्योम
sisusb_set_cursor(काष्ठा sisusb_usb_data *sisusb, अचिन्हित पूर्णांक location)
अणु
	अगर (sisusb->sisusb_cursor_loc == location)
		वापस;

	sisusb->sisusb_cursor_loc = location;

	/* Hardware bug: Text cursor appears twice or not at all
	 * at some positions. Work around it with the cursor skew
	 * bits.
	 */

	अगर ((location & 0x0007) == 0x0007) अणु
		sisusb->bad_cursor_pos = 1;
		location--;
		अगर (sisusb_setidxreganकरोr(sisusb, SISCR, 0x0b, 0x1f, 0x20))
			वापस;
	पूर्ण अन्यथा अगर (sisusb->bad_cursor_pos) अणु
		अगर (sisusb_setidxregand(sisusb, SISCR, 0x0b, 0x1f))
			वापस;
		sisusb->bad_cursor_pos = 0;
	पूर्ण

	अगर (sisusb_setidxreg(sisusb, SISCR, 0x0e, (location >> 8)))
		वापस;
	sisusb_setidxreg(sisusb, SISCR, 0x0f, (location & 0xff));
पूर्ण

अटल अंतरभूत काष्ठा sisusb_usb_data *
sisusb_get_sisusb(अचिन्हित लघु console)
अणु
	वापस mysisusbs[console];
पूर्ण

अटल अंतरभूत पूर्णांक
sisusb_sisusb_valid(काष्ठा sisusb_usb_data *sisusb)
अणु
	अगर (!sisusb->present || !sisusb->पढ़ोy || !sisusb->sisusb_dev)
		वापस 0;

	वापस 1;
पूर्ण

अटल काष्ठा sisusb_usb_data *
sisusb_get_sisusb_lock_and_check(अचिन्हित लघु console)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	/* We can't handle console calls in non-schedulable
	 * context due to our locks and the USB transport.
	 * So we simply ignore them. This should only affect
	 * some calls to prपूर्णांकk.
	 */
	अगर (in_atomic())
		वापस शून्य;

	sisusb = sisusb_get_sisusb(console);
	अगर (!sisusb)
		वापस शून्य;

	mutex_lock(&sisusb->lock);

	अगर (!sisusb_sisusb_valid(sisusb) ||
	    !sisusb->havethisconsole[console]) अणु
		mutex_unlock(&sisusb->lock);
		वापस शून्य;
	पूर्ण

	वापस sisusb;
पूर्ण

अटल पूर्णांक
sisusb_is_inactive(काष्ठा vc_data *c, काष्ठा sisusb_usb_data *sisusb)
अणु
	अगर (sisusb->is_gfx ||
	    sisusb->texपंचांगodedestroyed ||
	    c->vc_mode != KD_TEXT)
		वापस 1;

	वापस 0;
पूर्ण

/* con_startup console पूर्णांकerface routine */
अटल स्थिर अक्षर *
sisusbcon_startup(व्योम)
अणु
	वापस "SISUSBCON";
पूर्ण

/* con_init console पूर्णांकerface routine */
अटल व्योम
sisusbcon_init(काष्ठा vc_data *c, पूर्णांक init)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक cols, rows;

	/* This is called by करो_take_over_console(),
	 * ie by us/under our control. It is
	 * only called after text mode and fonts
	 * are set up/restored.
	 */

	sisusb = sisusb_get_sisusb(c->vc_num);
	अगर (!sisusb)
		वापस;

	mutex_lock(&sisusb->lock);

	अगर (!sisusb_sisusb_valid(sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	c->vc_can_करो_color = 1;

	c->vc_complement_mask = 0x7700;

	c->vc_hi_font_mask = sisusb->current_font_512 ? 0x0800 : 0;

	sisusb->haveconsole = 1;

	sisusb->havethisconsole[c->vc_num] = 1;

	/* We only support 640x400 */
	c->vc_scan_lines = 400;

	c->vc_font.height = sisusb->current_font_height;

	/* We only support width = 8 */
	cols = 80;
	rows = c->vc_scan_lines / c->vc_font.height;

	/* Increment usage count क्रम our sisusb.
	 * Doing so saves us from upping/करोwning
	 * the disconnect semaphore; we can't
	 * lose our sisusb until this is unकरोne
	 * in con_deinit. For all other console
	 * पूर्णांकerface functions, it suffices to
	 * use sisusb->lock and करो a quick check
	 * of sisusb क्रम device disconnection.
	 */
	kref_get(&sisusb->kref);

	अगर (!*c->vc_uni_pagedir_loc)
		con_set_शेष_unimap(c);

	mutex_unlock(&sisusb->lock);

	अगर (init) अणु
		c->vc_cols = cols;
		c->vc_rows = rows;
	पूर्ण अन्यथा
		vc_resize(c, cols, rows);
पूर्ण

/* con_deinit console पूर्णांकerface routine */
अटल व्योम
sisusbcon_deinit(काष्ठा vc_data *c)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक i;

	/* This is called by करो_take_over_console()
	 * and others, ie not under our control.
	 */

	sisusb = sisusb_get_sisusb(c->vc_num);
	अगर (!sisusb)
		वापस;

	mutex_lock(&sisusb->lock);

	/* Clear ourselves in mysisusbs */
	mysisusbs[c->vc_num] = शून्य;

	sisusb->havethisconsole[c->vc_num] = 0;

	/* Free our font buffer अगर all consoles are gone */
	अगर (sisusb->font_backup) अणु
		क्रम(i = 0; i < MAX_NR_CONSOLES; i++) अणु
			अगर (sisusb->havethisconsole[c->vc_num])
				अवरोध;
		पूर्ण
		अगर (i == MAX_NR_CONSOLES) अणु
			vमुक्त(sisusb->font_backup);
			sisusb->font_backup = शून्य;
		पूर्ण
	पूर्ण

	mutex_unlock(&sisusb->lock);

	/* decrement the usage count on our sisusb */
	kref_put(&sisusb->kref, sisusb_delete);
पूर्ण

/* पूर्णांकerface routine */
अटल u8
sisusbcon_build_attr(काष्ठा vc_data *c, u8 color, क्रमागत vc_पूर्णांकensity पूर्णांकensity,
			    bool blink, bool underline, bool reverse,
			    bool unused)
अणु
	u8 attr = color;

	अगर (underline)
		attr = (attr & 0xf0) | c->vc_ulcolor;
	अन्यथा अगर (पूर्णांकensity == VCI_HALF_BRIGHT)
		attr = (attr & 0xf0) | c->vc_halfcolor;

	अगर (reverse)
		attr = ((attr) & 0x88) |
		       ((((attr) >> 4) |
		       ((attr) << 4)) & 0x77);

	अगर (blink)
		attr ^= 0x80;

	अगर (पूर्णांकensity == VCI_BOLD)
		attr ^= 0x08;

	वापस attr;
पूर्ण

/* Interface routine */
अटल व्योम
sisusbcon_invert_region(काष्ठा vc_data *vc, u16 *p, पूर्णांक count)
अणु
	/* Invert a region. This is called with a poपूर्णांकer
	 * to the console's पूर्णांकernal screen buffer. So we
	 * simply करो the inversion there and rely on
	 * a call to अ_दो(s) to update the real screen.
	 */

	जबतक (count--) अणु
		u16 a = *p;

		*p++ = ((a) & 0x88ff)        |
		       (((a) & 0x7000) >> 4) |
		       (((a) & 0x0700) << 4);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम *sisusb_vaddr(स्थिर काष्ठा sisusb_usb_data *sisusb,
		स्थिर काष्ठा vc_data *c, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	वापस (u16 *)c->vc_origin + y * sisusb->sisusb_num_columns + x;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ sisusb_haddr(स्थिर काष्ठा sisusb_usb_data *sisusb,
	      स्थिर काष्ठा vc_data *c, अचिन्हित पूर्णांक x, अचिन्हित पूर्णांक y)
अणु
	अचिन्हित दीर्घ offset = c->vc_origin - sisusb->scrbuf;

	/* 2 bytes per each अक्षरacter */
	offset += 2 * (y * sisusb->sisusb_num_columns + x);

	वापस sisusb->vrambase + offset;
पूर्ण

/* Interface routine */
अटल व्योम
sisusbcon_अ_दो(काष्ठा vc_data *c, पूर्णांक ch, पूर्णांक y, पूर्णांक x)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */
	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, x, y),
				sisusb_haddr(sisusb, c, x, y), 2);

	mutex_unlock(&sisusb->lock);
पूर्ण

/* Interface routine */
अटल व्योम
sisusbcon_अ_दोs(काष्ठा vc_data *c, स्थिर अचिन्हित लघु *s,
		         पूर्णांक count, पूर्णांक y, पूर्णांक x)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */

	/* Need to put the अक्षरacters पूर्णांकo the buffer ourselves,
	 * because the vt करोes this AFTER calling us.
	 */

	स_नकल(sisusb_vaddr(sisusb, c, x, y), s, count * 2);

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, x, y),
			sisusb_haddr(sisusb, c, x, y), count * 2);

	mutex_unlock(&sisusb->lock);
पूर्ण

/* Interface routine */
अटल व्योम
sisusbcon_clear(काष्ठा vc_data *c, पूर्णांक y, पूर्णांक x, पूर्णांक height, पूर्णांक width)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	u16 eattr = c->vc_video_erase_अक्षर;
	पूर्णांक i, length, cols;
	u16 *dest;

	अगर (width <= 0 || height <= 0)
		वापस;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */

	/* Need to clear buffer ourselves, because the vt करोes
	 * this AFTER calling us.
	 */

	dest = sisusb_vaddr(sisusb, c, x, y);

	cols = sisusb->sisusb_num_columns;

	अगर (width > cols)
		width = cols;

	अगर (x == 0 && width >= c->vc_cols) अणु

		sisusbcon_स_रखोw(dest, eattr, height * cols * 2);

	पूर्ण अन्यथा अणु

		क्रम (i = height; i > 0; i--, dest += cols)
			sisusbcon_स_रखोw(dest, eattr, width * 2);

	पूर्ण

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	length = ((height * cols) - x - (cols - width - x)) * 2;


	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, x, y),
			sisusb_haddr(sisusb, c, x, y), length);

	mutex_unlock(&sisusb->lock);
पूर्ण

/* पूर्णांकerface routine */
अटल पूर्णांक
sisusbcon_चयन(काष्ठा vc_data *c)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक length;

	/* Returnvalue 0 means we have fully restored screen,
	 *	and vt करोesn't need to call करो_update_region().
	 * Returnvalue != 0 naturally means the opposite.
	 */

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस 0;

	/* sisusb->lock is करोwn */

	/* Don't ग_लिखो to screen अगर in gfx mode */
	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस 0;
	पूर्ण

	/* That really should not happen. It would mean we are
	 * being called जबतक the vc is using its निजी buffer
	 * as origin.
	 */
	अगर (c->vc_origin == (अचिन्हित दीर्घ)c->vc_screenbuf) अणु
		mutex_unlock(&sisusb->lock);
		dev_dbg(&sisusb->sisusb_dev->dev, "ASSERT ORIGIN != SCREENBUF!\n");
		वापस 0;
	पूर्ण

	/* Check that we करोn't copy too much */
	length = min((पूर्णांक)c->vc_screenbuf_size,
			(पूर्णांक)(sisusb->scrbuf + sisusb->scrbuf_size - c->vc_origin));

	/* Restore the screen contents */
	स_नकल((u16 *)c->vc_origin, (u16 *)c->vc_screenbuf, length);

	sisusb_copy_memory(sisusb, (u8 *)c->vc_origin,
			sisusb_haddr(sisusb, c, 0, 0), length);

	mutex_unlock(&sisusb->lock);

	वापस 0;
पूर्ण

/* पूर्णांकerface routine */
अटल व्योम
sisusbcon_save_screen(काष्ठा vc_data *c)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक length;

	/* Save the current screen contents to vc's निजी
	 * buffer.
	 */

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	/* Check that we करोn't copy too much */
	length = min((पूर्णांक)c->vc_screenbuf_size,
			(पूर्णांक)(sisusb->scrbuf + sisusb->scrbuf_size - c->vc_origin));

	/* Save the screen contents to vc's निजी buffer */
	स_नकल((u16 *)c->vc_screenbuf, (u16 *)c->vc_origin, length);

	mutex_unlock(&sisusb->lock);
पूर्ण

/* पूर्णांकerface routine */
अटल व्योम
sisusbcon_set_palette(काष्ठा vc_data *c, स्थिर अचिन्हित अक्षर *table)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक i, j;

	/* Return value not used by vt */

	अगर (!con_is_visible(c))
		वापस;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	क्रम (i = j = 0; i < 16; i++) अणु
		अगर (sisusb_setreg(sisusb, SISCOLIDX, table[i]))
			अवरोध;
		अगर (sisusb_setreg(sisusb, SISCOLDATA, c->vc_palette[j++] >> 2))
			अवरोध;
		अगर (sisusb_setreg(sisusb, SISCOLDATA, c->vc_palette[j++] >> 2))
			अवरोध;
		अगर (sisusb_setreg(sisusb, SISCOLDATA, c->vc_palette[j++] >> 2))
			अवरोध;
	पूर्ण

	mutex_unlock(&sisusb->lock);
पूर्ण

/* पूर्णांकerface routine */
अटल पूर्णांक
sisusbcon_blank(काष्ठा vc_data *c, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	u8 sr1, cr17, pmreg, cr63;
	पूर्णांक ret = 0;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस 0;

	/* sisusb->lock is करोwn */

	अगर (mode_चयन)
		sisusb->is_gfx = blank ? 1 : 0;

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस 0;
	पूर्ण

	चयन (blank) अणु

	हाल 1:		/* Normal blanking: Clear screen */
	हाल -1:
		sisusbcon_स_रखोw((u16 *)c->vc_origin,
				c->vc_video_erase_अक्षर,
				c->vc_screenbuf_size);
		sisusb_copy_memory(sisusb, (u8 *)c->vc_origin,
				sisusb_haddr(sisusb, c, 0, 0),
				c->vc_screenbuf_size);
		sisusb->con_blanked = 1;
		ret = 1;
		अवरोध;

	शेष:	/* VESA blanking */
		चयन (blank) अणु
		हाल 0: /* Unblank */
			sr1   = 0x00;
			cr17  = 0x80;
			pmreg = 0x00;
			cr63  = 0x00;
			ret = 1;
			sisusb->con_blanked = 0;
			अवरोध;
		हाल VESA_VSYNC_SUSPEND + 1:
			sr1   = 0x20;
			cr17  = 0x80;
			pmreg = 0x80;
			cr63  = 0x40;
			अवरोध;
		हाल VESA_HSYNC_SUSPEND + 1:
			sr1   = 0x20;
			cr17  = 0x80;
			pmreg = 0x40;
			cr63  = 0x40;
			अवरोध;
		हाल VESA_POWERDOWN + 1:
			sr1   = 0x20;
			cr17  = 0x00;
			pmreg = 0xc0;
			cr63  = 0x40;
			अवरोध;
		शेष:
			mutex_unlock(&sisusb->lock);
			वापस -EINVAL;
		पूर्ण

		sisusb_setidxreganकरोr(sisusb, SISSR, 0x01, ~0x20, sr1);
		sisusb_setidxreganकरोr(sisusb, SISCR, 0x17, 0x7f, cr17);
		sisusb_setidxreganकरोr(sisusb, SISSR, 0x1f, 0x3f, pmreg);
		sisusb_setidxreganकरोr(sisusb, SISCR, 0x63, 0xbf, cr63);

	पूर्ण

	mutex_unlock(&sisusb->lock);

	वापस ret;
पूर्ण

/* पूर्णांकerface routine */
अटल व्योम
sisusbcon_scrolldelta(काष्ठा vc_data *c, पूर्णांक lines)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	vc_scrolldelta_helper(c, lines, sisusb->con_rolled_over,
			(व्योम *)sisusb->scrbuf, sisusb->scrbuf_size);

	sisusbcon_set_start_address(sisusb, c);

	mutex_unlock(&sisusb->lock);
पूर्ण

/* Interface routine */
अटल व्योम
sisusbcon_cursor(काष्ठा vc_data *c, पूर्णांक mode)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक from, to, baseline;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस;

	/* sisusb->lock is करोwn */

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	अगर (c->vc_origin != c->vc_visible_origin) अणु
		c->vc_visible_origin = c->vc_origin;
		sisusbcon_set_start_address(sisusb, c);
	पूर्ण

	अगर (mode == CM_ERASE) अणु
		sisusb_setidxregor(sisusb, SISCR, 0x0a, 0x20);
		sisusb->sisusb_cursor_माप_प्रकारo = -1;
		mutex_unlock(&sisusb->lock);
		वापस;
	पूर्ण

	sisusb_set_cursor(sisusb, (c->vc_pos - sisusb->scrbuf) / 2);

	baseline = c->vc_font.height - (c->vc_font.height < 10 ? 1 : 2);

	चयन (CUR_SIZE(c->vc_cursor_type)) अणु
		हाल CUR_BLOCK:		from = 1;
					to   = c->vc_font.height;
					अवरोध;
		हाल CUR_TWO_THIRDS:	from = c->vc_font.height / 3;
					to   = baseline;
					अवरोध;
		हाल CUR_LOWER_HALF:	from = c->vc_font.height / 2;
					to   = baseline;
					अवरोध;
		हाल CUR_LOWER_THIRD:	from = (c->vc_font.height * 2) / 3;
					to   = baseline;
					अवरोध;
		हाल CUR_NONE:		from = 31;
					to = 30;
					अवरोध;
		शेष:
		हाल CUR_UNDERLINE:	from = baseline - 1;
					to   = baseline;
					अवरोध;
	पूर्ण

	अगर (sisusb->sisusb_cursor_size_from != from ||
	    sisusb->sisusb_cursor_माप_प्रकारo != to) अणु

		sisusb_setidxreg(sisusb, SISCR, 0x0a, from);
		sisusb_setidxreganकरोr(sisusb, SISCR, 0x0b, 0xe0, to);

		sisusb->sisusb_cursor_size_from = from;
		sisusb->sisusb_cursor_माप_प्रकारo   = to;
	पूर्ण

	mutex_unlock(&sisusb->lock);
पूर्ण

अटल bool
sisusbcon_scroll_area(काष्ठा vc_data *c, काष्ठा sisusb_usb_data *sisusb,
		अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b, क्रमागत con_scroll dir,
		अचिन्हित पूर्णांक lines)
अणु
	पूर्णांक cols = sisusb->sisusb_num_columns;
	पूर्णांक length = ((b - t) * cols) * 2;
	u16 eattr = c->vc_video_erase_अक्षर;

	/* sisusb->lock is करोwn */

	/* Scroll an area which करोes not match the
	 * visible screen's dimensions. This needs
	 * to be करोne separately, as it करोes not
	 * use hardware panning.
	 */

	चयन (dir) अणु

		हाल SM_UP:
			स_हटाओ(sisusb_vaddr(sisusb, c, 0, t),
					   sisusb_vaddr(sisusb, c, 0, t + lines),
					   (b - t - lines) * cols * 2);
			sisusbcon_स_रखोw(sisusb_vaddr(sisusb, c, 0, b - lines),
					eattr, lines * cols * 2);
			अवरोध;

		हाल SM_DOWN:
			स_हटाओ(sisusb_vaddr(sisusb, c, 0, t + lines),
					   sisusb_vaddr(sisusb, c, 0, t),
					   (b - t - lines) * cols * 2);
			sisusbcon_स_रखोw(sisusb_vaddr(sisusb, c, 0, t), eattr,
					  lines * cols * 2);
			अवरोध;
	पूर्ण

	sisusb_copy_memory(sisusb, sisusb_vaddr(sisusb, c, 0, t),
			sisusb_haddr(sisusb, c, 0, t), length);

	mutex_unlock(&sisusb->lock);

	वापस true;
पूर्ण

/* Interface routine */
अटल bool
sisusbcon_scroll(काष्ठा vc_data *c, अचिन्हित पूर्णांक t, अचिन्हित पूर्णांक b,
		क्रमागत con_scroll dir, अचिन्हित पूर्णांक lines)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	u16 eattr = c->vc_video_erase_अक्षर;
	पूर्णांक copyall = 0;
	अचिन्हित दीर्घ olकरोrigin;
	अचिन्हित पूर्णांक delta = lines * c->vc_size_row;

	/* Returning != 0 means we have करोne the scrolling successfully.
	 * Returning 0 makes vt करो the scrolling on its own.
	 * Note that con_scroll is only called अगर the console is
	 * visible. In that हाल, the origin should be our buffer,
	 * not the vt's निजी one.
	 */

	अगर (!lines)
		वापस true;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस false;

	/* sisusb->lock is करोwn */

	अगर (sisusb_is_inactive(c, sisusb)) अणु
		mutex_unlock(&sisusb->lock);
		वापस false;
	पूर्ण

	/* Special हाल */
	अगर (t || b != c->vc_rows)
		वापस sisusbcon_scroll_area(c, sisusb, t, b, dir, lines);

	अगर (c->vc_origin != c->vc_visible_origin) अणु
		c->vc_visible_origin = c->vc_origin;
		sisusbcon_set_start_address(sisusb, c);
	पूर्ण

	/* limit amount to maximum realistic size */
	अगर (lines > c->vc_rows)
		lines = c->vc_rows;

	olकरोrigin = c->vc_origin;

	चयन (dir) अणु

	हाल SM_UP:

		अगर (c->vc_scr_end + delta >=
				sisusb->scrbuf + sisusb->scrbuf_size) अणु
			स_नकल((u16 *)sisusb->scrbuf,
					  (u16 *)(olकरोrigin + delta),
					  c->vc_screenbuf_size - delta);
			c->vc_origin = sisusb->scrbuf;
			sisusb->con_rolled_over = olकरोrigin - sisusb->scrbuf;
			copyall = 1;
		पूर्ण अन्यथा
			c->vc_origin += delta;

		sisusbcon_स_रखोw(
			(u16 *)(c->vc_origin + c->vc_screenbuf_size - delta),
					eattr, delta);

		अवरोध;

	हाल SM_DOWN:

		अगर (olकरोrigin - delta < sisusb->scrbuf) अणु
			स_हटाओ((व्योम *)sisusb->scrbuf + sisusb->scrbuf_size -
					c->vc_screenbuf_size + delta,
					(u16 *)olकरोrigin,
					c->vc_screenbuf_size - delta);
			c->vc_origin = sisusb->scrbuf +
					sisusb->scrbuf_size -
					c->vc_screenbuf_size;
			sisusb->con_rolled_over = 0;
			copyall = 1;
		पूर्ण अन्यथा
			c->vc_origin -= delta;

		c->vc_scr_end = c->vc_origin + c->vc_screenbuf_size;

		scr_स_रखोw((u16 *)(c->vc_origin), eattr, delta);

		अवरोध;
	पूर्ण

	अगर (copyall)
		sisusb_copy_memory(sisusb,
			(u8 *)c->vc_origin,
			sisusb_haddr(sisusb, c, 0, 0),
			c->vc_screenbuf_size);
	अन्यथा अगर (dir == SM_UP)
		sisusb_copy_memory(sisusb,
			(u8 *)c->vc_origin + c->vc_screenbuf_size - delta,
			sisusb_haddr(sisusb, c, 0, 0) +
					c->vc_screenbuf_size - delta,
			delta);
	अन्यथा
		sisusb_copy_memory(sisusb,
			(u8 *)c->vc_origin,
			sisusb_haddr(sisusb, c, 0, 0),
			delta);

	c->vc_scr_end = c->vc_origin + c->vc_screenbuf_size;
	c->vc_visible_origin = c->vc_origin;

	sisusbcon_set_start_address(sisusb, c);

	c->vc_pos = c->vc_pos - olकरोrigin + c->vc_origin;

	mutex_unlock(&sisusb->lock);

	वापस true;
पूर्ण

/* Interface routine */
अटल पूर्णांक
sisusbcon_set_origin(काष्ठा vc_data *c)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	/* Returning != 0 means we were successful.
	 * Returning 0 will vt make to use its own
	 *	screenbuffer as the origin.
	 */

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस 0;

	/* sisusb->lock is करोwn */

	अगर (sisusb_is_inactive(c, sisusb) || sisusb->con_blanked) अणु
		mutex_unlock(&sisusb->lock);
		वापस 0;
	पूर्ण

	c->vc_origin = c->vc_visible_origin = sisusb->scrbuf;

	sisusbcon_set_start_address(sisusb, c);

	sisusb->con_rolled_over = 0;

	mutex_unlock(&sisusb->lock);

	वापस true;
पूर्ण

/* Interface routine */
अटल पूर्णांक
sisusbcon_resize(काष्ठा vc_data *c, अचिन्हित पूर्णांक newcols, अचिन्हित पूर्णांक newrows,
		 अचिन्हित पूर्णांक user)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	पूर्णांक fh;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस -ENODEV;

	fh = sisusb->current_font_height;

	mutex_unlock(&sisusb->lock);

	/* We are quite unflexible as regards resizing. The vt code
	 * handles sizes where the line length isn't equal the pitch
	 * quite badly. As regards the rows, our panning tricks only
	 * work well अगर the number of rows equals the visible number
	 * of rows.
	 */

	अगर (newcols != 80 || c->vc_scan_lines / fh != newrows)
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक
sisusbcon_करो_font_op(काष्ठा sisusb_usb_data *sisusb, पूर्णांक set, पूर्णांक slot,
			u8 *arg, पूर्णांक cmapsz, पूर्णांक ch512, पूर्णांक करोrecalc,
			काष्ठा vc_data *c, पूर्णांक fh, पूर्णांक uplock)
अणु
	पूर्णांक font_select = 0x00, i, err = 0;
	u32 offset = 0;
	u8 dummy;

	/* sisusb->lock is करोwn */

	/*
	 * The शेष font is kept in slot 0.
	 * A user font is loaded in slot 2 (256 ch)
	 * or 2+3 (512 ch).
	 */

	अगर ((slot != 0 && slot != 2) || !fh) अणु
		अगर (uplock)
			mutex_unlock(&sisusb->lock);
		वापस -EINVAL;
	पूर्ण

	अगर (set)
		sisusb->font_slot = slot;

	/* Default font is always 256 */
	अगर (slot == 0)
		ch512 = 0;
	अन्यथा
		offset = 4 * cmapsz;

	font_select = (slot == 0) ? 0x00 : (ch512 ? 0x0e : 0x0a);

	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x01); /* Reset */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x02, 0x04); /* Write to plane 2 */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x04, 0x07); /* Memory mode a0-bf */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x03); /* Reset */

	अगर (err)
		जाओ font_op_error;

	err |= sisusb_setidxreg(sisusb, SISGR, 0x04, 0x03); /* Select plane पढ़ो 2 */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x05, 0x00); /* Disable odd/even */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x06, 0x00); /* Address range a0-bf */

	अगर (err)
		जाओ font_op_error;

	अगर (arg) अणु
		अगर (set)
			क्रम (i = 0; i < cmapsz; i++) अणु
				err |= sisusb_ग_लिखोb(sisusb,
					sisusb->vrambase + offset + i,
					arg[i]);
				अगर (err)
					अवरोध;
			पूर्ण
		अन्यथा
			क्रम (i = 0; i < cmapsz; i++) अणु
				err |= sisusb_पढ़ोb(sisusb,
					sisusb->vrambase + offset + i,
					&arg[i]);
				अगर (err)
					अवरोध;
			पूर्ण

		/*
		 * In 512-अक्षरacter mode, the अक्षरacter map is not contiguous अगर
		 * we want to reमुख्य EGA compatible -- which we करो
		 */

		अगर (ch512) अणु
			अगर (set)
				क्रम (i = 0; i < cmapsz; i++) अणु
					err |= sisusb_ग_लिखोb(sisusb,
						sisusb->vrambase + offset +
							(2 * cmapsz) + i,
						arg[cmapsz + i]);
					अगर (err)
						अवरोध;
				पूर्ण
			अन्यथा
				क्रम (i = 0; i < cmapsz; i++) अणु
					err |= sisusb_पढ़ोb(sisusb,
						sisusb->vrambase + offset +
							(2 * cmapsz) + i,
						&arg[cmapsz + i]);
					अगर (err)
						अवरोध;
				पूर्ण
		पूर्ण
	पूर्ण

	अगर (err)
		जाओ font_op_error;

	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x01); /* Reset */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x02, 0x03); /* Write to planes 0+1 */
	err |= sisusb_setidxreg(sisusb, SISSR, 0x04, 0x03); /* Memory mode a0-bf */
	अगर (set)
		sisusb_setidxreg(sisusb, SISSR, 0x03, font_select);
	err |= sisusb_setidxreg(sisusb, SISSR, 0x00, 0x03); /* Reset end */

	अगर (err)
		जाओ font_op_error;

	err |= sisusb_setidxreg(sisusb, SISGR, 0x04, 0x00); /* Select plane पढ़ो 0 */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x05, 0x10); /* Enable odd/even */
	err |= sisusb_setidxreg(sisusb, SISGR, 0x06, 0x06); /* Address range b8-bf */

	अगर (err)
		जाओ font_op_error;

	अगर ((set) && (ch512 != sisusb->current_font_512)) अणु

		/* Font is shared among all our consoles.
		 * And so is the hi_font_mask.
		 */
		क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
			काष्ठा vc_data *d = vc_cons[i].d;
			अगर (d && d->vc_sw == &sisusb_con)
				d->vc_hi_font_mask = ch512 ? 0x0800 : 0;
		पूर्ण

		sisusb->current_font_512 = ch512;

		/* color plane enable रेजिस्टर:
			256-अक्षर: enable पूर्णांकensity bit
			512-अक्षर: disable पूर्णांकensity bit */
		sisusb_getreg(sisusb, SISINPSTAT, &dummy);
		sisusb_setreg(sisusb, SISAR, 0x12);
		sisusb_setreg(sisusb, SISAR, ch512 ? 0x07 : 0x0f);

		sisusb_getreg(sisusb, SISINPSTAT, &dummy);
		sisusb_setreg(sisusb, SISAR, 0x20);
		sisusb_getreg(sisusb, SISINPSTAT, &dummy);
	पूर्ण

	अगर (करोrecalc) अणु

		/*
		 * Adjust the screen to fit a font of a certain height
		 */

		अचिन्हित अक्षर ovr, vde, fsr;
		पूर्णांक rows = 0, maxscan = 0;

		अगर (c) अणु

			/* Number of video rows */
			rows = c->vc_scan_lines / fh;
			/* Scan lines to actually display-1 */
			maxscan = rows * fh - 1;

			/*prपूर्णांकk(KERN_DEBUG "sisusb recalc rows %d maxscan %d fh %d sl %d\n",
				rows, maxscan, fh, c->vc_scan_lines);*/

			sisusb_getidxreg(sisusb, SISCR, 0x07, &ovr);
			vde = maxscan & 0xff;
			ovr = (ovr & 0xbd) |
			      ((maxscan & 0x100) >> 7) |
			      ((maxscan & 0x200) >> 3);
			sisusb_setidxreg(sisusb, SISCR, 0x07, ovr);
			sisusb_setidxreg(sisusb, SISCR, 0x12, vde);

		पूर्ण

		sisusb_getidxreg(sisusb, SISCR, 0x09, &fsr);
		fsr = (fsr & 0xe0) | (fh - 1);
		sisusb_setidxreg(sisusb, SISCR, 0x09, fsr);
		sisusb->current_font_height = fh;

		sisusb->sisusb_cursor_size_from = -1;
		sisusb->sisusb_cursor_माप_प्रकारo   = -1;

	पूर्ण

	अगर (uplock)
		mutex_unlock(&sisusb->lock);

	अगर (करोrecalc && c) अणु
		पूर्णांक rows = c->vc_scan_lines / fh;

		/* Now adjust our consoles' size */

		क्रम (i = 0; i < MAX_NR_CONSOLES; i++) अणु
			काष्ठा vc_data *vc = vc_cons[i].d;

			अगर (vc && vc->vc_sw == &sisusb_con) अणु
				अगर (con_is_visible(vc)) अणु
					vc->vc_sw->con_cursor(vc, CM_DRAW);
				पूर्ण
				vc->vc_font.height = fh;
				vc_resize(vc, 0, rows);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

font_op_error:
	अगर (uplock)
		mutex_unlock(&sisusb->lock);

	वापस -EIO;
पूर्ण

/* Interface routine */
अटल पूर्णांक
sisusbcon_font_set(काष्ठा vc_data *c, काष्ठा console_font *font,
		   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा sisusb_usb_data *sisusb;
	अचिन्हित अक्षरcount = font->अक्षरcount;

	अगर (font->width != 8 || (अक्षरcount != 256 && अक्षरcount != 512))
		वापस -EINVAL;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस -ENODEV;

	/* sisusb->lock is करोwn */

	/* Save the user-provided font पूर्णांकo a buffer. This
	 * is used क्रम restoring text mode after quitting
	 * from X and क्रम the con_getfont routine.
	 */
	अगर (sisusb->font_backup) अणु
		अगर (sisusb->font_backup_size < अक्षरcount) अणु
			vमुक्त(sisusb->font_backup);
			sisusb->font_backup = शून्य;
		पूर्ण
	पूर्ण

	अगर (!sisusb->font_backup)
		sisusb->font_backup = vदो_स्मृति(array_size(अक्षरcount, 32));

	अगर (sisusb->font_backup) अणु
		स_नकल(sisusb->font_backup, font->data, array_size(अक्षरcount, 32));
		sisusb->font_backup_size = अक्षरcount;
		sisusb->font_backup_height = font->height;
		sisusb->font_backup_512 = (अक्षरcount == 512) ? 1 : 0;
	पूर्ण

	/* करो_font_op ups sisusb->lock */

	वापस sisusbcon_करो_font_op(sisusb, 1, 2, font->data,
			8192, (अक्षरcount == 512),
			(!(flags & KD_FONT_FLAG_DONT_RECALC)) ? 1 : 0,
			c, font->height, 1);
पूर्ण

/* Interface routine */
अटल पूर्णांक
sisusbcon_font_get(काष्ठा vc_data *c, काष्ठा console_font *font)
अणु
	काष्ठा sisusb_usb_data *sisusb;

	sisusb = sisusb_get_sisusb_lock_and_check(c->vc_num);
	अगर (!sisusb)
		वापस -ENODEV;

	/* sisusb->lock is करोwn */

	font->width = 8;
	font->height = c->vc_font.height;
	font->अक्षरcount = 256;

	अगर (!font->data) अणु
		mutex_unlock(&sisusb->lock);
		वापस 0;
	पूर्ण

	अगर (!sisusb->font_backup) अणु
		mutex_unlock(&sisusb->lock);
		वापस -ENODEV;
	पूर्ण

	/* Copy 256 अक्षरs only, like vgacon */
	स_नकल(font->data, sisusb->font_backup, 256 * 32);

	mutex_unlock(&sisusb->lock);

	वापस 0;
पूर्ण

/*
 *  The console `चयन' काष्ठाure क्रम the sisusb console
 */

अटल स्थिर काष्ठा consw sisusb_con = अणु
	.owner =		THIS_MODULE,
	.con_startup =		sisusbcon_startup,
	.con_init =		sisusbcon_init,
	.con_deinit =		sisusbcon_deinit,
	.con_clear =		sisusbcon_clear,
	.con_अ_दो =		sisusbcon_अ_दो,
	.con_अ_दोs =		sisusbcon_अ_दोs,
	.con_cursor =		sisusbcon_cursor,
	.con_scroll =		sisusbcon_scroll,
	.con_चयन =		sisusbcon_चयन,
	.con_blank =		sisusbcon_blank,
	.con_font_set =		sisusbcon_font_set,
	.con_font_get =		sisusbcon_font_get,
	.con_set_palette =	sisusbcon_set_palette,
	.con_scrolldelta =	sisusbcon_scrolldelta,
	.con_build_attr =	sisusbcon_build_attr,
	.con_invert_region =	sisusbcon_invert_region,
	.con_set_origin =	sisusbcon_set_origin,
	.con_save_screen =	sisusbcon_save_screen,
	.con_resize =		sisusbcon_resize,
पूर्ण;

/* Our very own dummy console driver */

अटल स्थिर अक्षर *sisusbdummycon_startup(व्योम)
अणु
    वापस "SISUSBVGADUMMY";
पूर्ण

अटल व्योम sisusbdummycon_init(काष्ठा vc_data *vc, पूर्णांक init)
अणु
    vc->vc_can_करो_color = 1;
    अगर (init) अणु
	vc->vc_cols = 80;
	vc->vc_rows = 25;
    पूर्ण अन्यथा
	vc_resize(vc, 80, 25);
पूर्ण

अटल व्योम sisusbdummycon_deinit(काष्ठा vc_data *vc) अणु पूर्ण
अटल व्योम sisusbdummycon_clear(काष्ठा vc_data *vc, पूर्णांक sy, पूर्णांक sx,
				 पूर्णांक height, पूर्णांक width) अणु पूर्ण
अटल व्योम sisusbdummycon_अ_दो(काष्ठा vc_data *vc, पूर्णांक c, पूर्णांक ypos,
				पूर्णांक xpos) अणु पूर्ण
अटल व्योम sisusbdummycon_अ_दोs(काष्ठा vc_data *vc, स्थिर अचिन्हित लघु *s,
				 पूर्णांक count, पूर्णांक ypos, पूर्णांक xpos) अणु पूर्ण
अटल व्योम sisusbdummycon_cursor(काष्ठा vc_data *vc, पूर्णांक mode) अणु पूर्ण

अटल bool sisusbdummycon_scroll(काष्ठा vc_data *vc, अचिन्हित पूर्णांक top,
				  अचिन्हित पूर्णांक bottom, क्रमागत con_scroll dir,
				  अचिन्हित पूर्णांक lines)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक sisusbdummycon_चयन(काष्ठा vc_data *vc)
अणु
	वापस 0;
पूर्ण

अटल पूर्णांक sisusbdummycon_blank(काष्ठा vc_data *vc, पूर्णांक blank, पूर्णांक mode_चयन)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा consw sisusb_dummy_con = अणु
	.owner =		THIS_MODULE,
	.con_startup =		sisusbdummycon_startup,
	.con_init =		sisusbdummycon_init,
	.con_deinit =		sisusbdummycon_deinit,
	.con_clear =		sisusbdummycon_clear,
	.con_अ_दो =		sisusbdummycon_अ_दो,
	.con_अ_दोs =		sisusbdummycon_अ_दोs,
	.con_cursor =		sisusbdummycon_cursor,
	.con_scroll =		sisusbdummycon_scroll,
	.con_चयन =		sisusbdummycon_चयन,
	.con_blank =		sisusbdummycon_blank,
पूर्ण;

पूर्णांक
sisusb_console_init(काष्ठा sisusb_usb_data *sisusb, पूर्णांक first, पूर्णांक last)
अणु
	पूर्णांक i, ret;

	mutex_lock(&sisusb->lock);

	/* Erm.. that should not happen */
	अगर (sisusb->haveconsole || !sisusb->SiS_Pr) अणु
		mutex_unlock(&sisusb->lock);
		वापस 1;
	पूर्ण

	sisusb->con_first = first;
	sisusb->con_last  = last;

	अगर (first > last ||
	    first > MAX_NR_CONSOLES ||
	    last > MAX_NR_CONSOLES) अणु
		mutex_unlock(&sisusb->lock);
		वापस 1;
	पूर्ण

	/* If gfxcore not initialized or no consoles given, quit graciously */
	अगर (!sisusb->gfxinit || first < 1 || last < 1) अणु
		mutex_unlock(&sisusb->lock);
		वापस 0;
	पूर्ण

	sisusb->sisusb_cursor_loc       = -1;
	sisusb->sisusb_cursor_size_from = -1;
	sisusb->sisusb_cursor_माप_प्रकारo   = -1;

	/* Set up text mode (and upload  शेष font) */
	अगर (sisusb_reset_text_mode(sisusb, 1)) अणु
		mutex_unlock(&sisusb->lock);
		dev_err(&sisusb->sisusb_dev->dev, "Failed to set up text mode\n");
		वापस 1;
	पूर्ण

	/* Initialize some gfx रेजिस्टरs */
	sisusb_initialize(sisusb);

	क्रम (i = first - 1; i <= last - 1; i++) अणु
		/* Save sisusb क्रम our पूर्णांकerface routines */
		mysisusbs[i] = sisusb;
	पूर्ण

	/* Initial console setup */
	sisusb->sisusb_num_columns = 80;

	/* Use a 32K buffer (matches b8000-bffff area) */
	sisusb->scrbuf_size = 32 * 1024;

	/* Allocate screen buffer */
	अगर (!(sisusb->scrbuf = (अचिन्हित दीर्घ)vदो_स्मृति(sisusb->scrbuf_size))) अणु
		mutex_unlock(&sisusb->lock);
		dev_err(&sisusb->sisusb_dev->dev, "Failed to allocate screen buffer\n");
		वापस 1;
	पूर्ण

	mutex_unlock(&sisusb->lock);

	/* Now grab the desired console(s) */
	console_lock();
	ret = करो_take_over_console(&sisusb_con, first - 1, last - 1, 0);
	console_unlock();
	अगर (!ret)
		sisusb->haveconsole = 1;
	अन्यथा अणु
		क्रम (i = first - 1; i <= last - 1; i++)
			mysisusbs[i] = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

व्योम
sisusb_console_निकास(काष्ठा sisusb_usb_data *sisusb)
अणु
	पूर्णांक i;

	/* This is called अगर the device is disconnected
	 * and जबतक disconnect and lock semaphores
	 * are up. This should be save because we
	 * can't lose our sisusb any other way but by
	 * disconnection (and hence, the disconnect
	 * sema is क्रम protecting all other access
	 * functions from disconnection, not the
	 * other way round).
	 */

	/* Now what करो we करो in हाल of disconnection:
	 * One alternative would be to simply call
	 * give_up_console(). Nah, not a good idea.
	 * give_up_console() is obviously buggy as it
	 * only discards the consw poपूर्णांकer from the
	 * driver_map, but करोesn't adapt vc->vc_sw
	 * of the affected consoles. Hence, the next
	 * call to any of the console functions will
	 * eventually take a trip to oops county.
	 * Also, give_up_console क्रम some reason
	 * करोesn't decrement our module refcount.
	 * Instead, we चयन our consoles to a निजी
	 * dummy console. This, of course, keeps our
	 * refcount up as well, but it works perfectly.
	 */

	अगर (sisusb->haveconsole) अणु
		क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
			अगर (sisusb->havethisconsole[i]) अणु
				console_lock();
				करो_take_over_console(&sisusb_dummy_con, i, i, 0);
				console_unlock();
				/* At this poपूर्णांक, con_deinit क्रम all our
				 * consoles is executed by करो_take_over_console().
				 */
			पूर्ण
		sisusb->haveconsole = 0;
	पूर्ण

	vमुक्त((व्योम *)sisusb->scrbuf);
	sisusb->scrbuf = 0;

	vमुक्त(sisusb->font_backup);
	sisusb->font_backup = शून्य;
पूर्ण

व्योम __init sisusb_init_concode(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_NR_CONSOLES; i++)
		mysisusbs[i] = शून्य;
पूर्ण
