<शैली गुरु>
/*
 * fbअगर.h -- Xen भव frame buffer device
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (C) 2005 Anthony Liguori <aliguori@us.ibm.com>
 * Copyright (C) 2006 Red Hat, Inc., Markus Armbruster <armbru@redhat.com>
 */

#अगर_अघोषित __XEN_PUBLIC_IO_FBIF_H__
#घोषणा __XEN_PUBLIC_IO_FBIF_H__

/* Out events (frontend -> backend) */

/*
 * Out events may be sent only when requested by backend, and receipt
 * of an unknown out event is an error.
 */

/* Event type 1 currently not used */
/*
 * Framebuffer update notअगरication event
 * Capable frontend sets feature-update in xenstore.
 * Backend requests it by setting request-update in xenstore.
 */
#घोषणा XENFB_TYPE_UPDATE 2

काष्ठा xenfb_update अणु
	uपूर्णांक8_t type;		/* XENFB_TYPE_UPDATE */
	पूर्णांक32_t x;		/* source x */
	पूर्णांक32_t y;		/* source y */
	पूर्णांक32_t width;		/* rect width */
	पूर्णांक32_t height;		/* rect height */
पूर्ण;

/*
 * Framebuffer resize notअगरication event
 * Capable backend sets feature-resize in xenstore.
 */
#घोषणा XENFB_TYPE_RESIZE 3

काष्ठा xenfb_resize अणु
	uपूर्णांक8_t type;		/* XENFB_TYPE_RESIZE */
	पूर्णांक32_t width;		/* width in pixels */
	पूर्णांक32_t height;		/* height in pixels */
	पूर्णांक32_t stride;		/* stride in bytes */
	पूर्णांक32_t depth;		/* depth in bits */
	पूर्णांक32_t offset;		/* start offset within framebuffer */
पूर्ण;

#घोषणा XENFB_OUT_EVENT_SIZE 40

जोड़ xenfb_out_event अणु
	uपूर्णांक8_t type;
	काष्ठा xenfb_update update;
	काष्ठा xenfb_resize resize;
	अक्षर pad[XENFB_OUT_EVENT_SIZE];
पूर्ण;

/* In events (backend -> frontend) */

/*
 * Frontends should ignore unknown in events.
 * No in events currently defined.
 */

#घोषणा XENFB_IN_EVENT_SIZE 40

जोड़ xenfb_in_event अणु
	uपूर्णांक8_t type;
	अक्षर pad[XENFB_IN_EVENT_SIZE];
पूर्ण;

/* shared page */

#घोषणा XENFB_IN_RING_SIZE 1024
#घोषणा XENFB_IN_RING_LEN (XENFB_IN_RING_SIZE / XENFB_IN_EVENT_SIZE)
#घोषणा XENFB_IN_RING_OFFS 1024
#घोषणा XENFB_IN_RING(page) \
	((जोड़ xenfb_in_event *)((अक्षर *)(page) + XENFB_IN_RING_OFFS))
#घोषणा XENFB_IN_RING_REF(page, idx) \
	(XENFB_IN_RING((page))[(idx) % XENFB_IN_RING_LEN])

#घोषणा XENFB_OUT_RING_SIZE 2048
#घोषणा XENFB_OUT_RING_LEN (XENFB_OUT_RING_SIZE / XENFB_OUT_EVENT_SIZE)
#घोषणा XENFB_OUT_RING_OFFS (XENFB_IN_RING_OFFS + XENFB_IN_RING_SIZE)
#घोषणा XENFB_OUT_RING(page) \
	((जोड़ xenfb_out_event *)((अक्षर *)(page) + XENFB_OUT_RING_OFFS))
#घोषणा XENFB_OUT_RING_REF(page, idx) \
	(XENFB_OUT_RING((page))[(idx) % XENFB_OUT_RING_LEN])

काष्ठा xenfb_page अणु
	uपूर्णांक32_t in_cons, in_prod;
	uपूर्णांक32_t out_cons, out_prod;

	पूर्णांक32_t width;          /* width of the framebuffer (in pixels) */
	पूर्णांक32_t height;         /* height of the framebuffer (in pixels) */
	uपूर्णांक32_t line_length;   /* length of a row of pixels (in bytes) */
	uपूर्णांक32_t mem_length;    /* length of the framebuffer (in bytes) */
	uपूर्णांक8_t depth;          /* depth of a pixel (in bits) */

	/*
	 * Framebuffer page directory
	 *
	 * Each directory page holds PAGE_SIZE / माप(*pd)
	 * framebuffer pages, and can thus map up to PAGE_SIZE *
	 * PAGE_SIZE / माप(*pd) bytes.  With PAGE_SIZE == 4096 and
	 * माप(अचिन्हित दीर्घ) == 4/8, that's 4 Megs 32 bit and 2
	 * Megs 64 bit.  256 directories give enough room क्रम a 512
	 * Meg framebuffer with a max resolution of 12,800x10,240.
	 * Should be enough क्रम a जबतक with room leftover क्रम
	 * expansion.
	 */
	अचिन्हित दीर्घ pd[256];
पूर्ण;

/*
 * Wart: xenkbd needs to know शेष resolution.  Put it here until a
 * better solution is found, but करोn't leak it to the backend.
 */
#अगर_घोषित __KERNEL__
#घोषणा XENFB_WIDTH 800
#घोषणा XENFB_HEIGHT 600
#घोषणा XENFB_DEPTH 32
#पूर्ण_अगर

#पूर्ण_अगर
