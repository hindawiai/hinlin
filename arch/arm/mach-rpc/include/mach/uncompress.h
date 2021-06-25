<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/mach-rpc/include/mach/uncompress.h
 *
 *  Copyright (C) 1996 Russell King
 */
#घोषणा VIDMEM ((अक्षर *)SCREEN_START)
 
#समावेश <linux/पन.स>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/page.h>

पूर्णांक video_size_row;
अचिन्हित अक्षर bytes_per_अक्षर_h;
बाह्य अचिन्हित दीर्घ con_अक्षरconvtable[256];

काष्ठा param_काष्ठा अणु
	अचिन्हित दीर्घ page_size;
	अचिन्हित दीर्घ nr_pages;
	अचिन्हित दीर्घ ramdisk_size;
	अचिन्हित दीर्घ mountrootrकरोnly;
	अचिन्हित दीर्घ rootdev;
	अचिन्हित दीर्घ video_num_cols;
	अचिन्हित दीर्घ video_num_rows;
	अचिन्हित दीर्घ video_x;
	अचिन्हित दीर्घ video_y;
	अचिन्हित दीर्घ memc_control_reg;
	अचिन्हित अक्षर soundशेष;
	अचिन्हित अक्षर adfsdrives;
	अचिन्हित अक्षर bytes_per_अक्षर_h;
	अचिन्हित अक्षर bytes_per_अक्षर_v;
	अचिन्हित दीर्घ unused[256/4-11];
पूर्ण;

अटल स्थिर अचिन्हित दीर्घ palette_4[16] = अणु
	0x00000000,
	0x000000cc,
	0x0000cc00,             /* Green   */
	0x0000cccc,             /* Yellow  */
	0x00cc0000,             /* Blue    */
	0x00cc00cc,             /* Magenta */
	0x00cccc00,             /* Cyan    */
	0x00cccccc,             /* White   */
	0x00000000,
	0x000000ff,
	0x0000ff00,
	0x0000ffff,
	0x00ff0000,
	0x00ff00ff,
	0x00ffff00,
	0x00ffffff
पूर्ण;

#घोषणा palette_setpixel(p)	*(अचिन्हित दीर्घ *)(IO_START+0x00400000) = 0x10000000|((p) & 255)
#घोषणा palette_ग_लिखो(v)	*(अचिन्हित दीर्घ *)(IO_START+0x00400000) = 0x00000000|((v) & 0x00ffffff)

/*
 * params_phys is a linker defined symbol - see
 * arch/arm/boot/compressed/Makefile
 */
बाह्य __attribute__((pure)) काष्ठा param_काष्ठा *params(व्योम);
#घोषणा params (params())

#अगर_अघोषित STANDALONE_DEBUG 
अचिन्हित दीर्घ video_num_cols;
अचिन्हित दीर्घ video_num_rows;
अचिन्हित दीर्घ video_x;
अचिन्हित दीर्घ video_y;
अचिन्हित अक्षर bytes_per_अक्षर_v;
पूर्णांक white;

/*
 * This करोes not append a newline
 */
अटल अंतरभूत व्योम अ_दो(पूर्णांक c)
अणु
	बाह्य व्योम ll_ग_लिखो_अक्षर(अक्षर *, अक्षर c, अक्षर white);
	पूर्णांक x,y;
	अक्षर *ptr;

	x = video_x;
	y = video_y;

	अगर (c == '\n') अणु
		अगर (++y >= video_num_rows)
			y--;
	पूर्ण अन्यथा अगर (c == '\r') अणु
		x = 0;
	पूर्ण अन्यथा अणु
		ptr = VIDMEM + ((y*video_num_cols*bytes_per_अक्षर_v+x)*bytes_per_अक्षर_h);
		ll_ग_लिखो_अक्षर(ptr, c, white);
		अगर (++x >= video_num_cols) अणु
			x = 0;
			अगर ( ++y >= video_num_rows ) अणु
				y--;
			पूर्ण
		पूर्ण
	पूर्ण

	video_x = x;
	video_y = y;
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

/*
 * Setup क्रम decompression
 */
अटल व्योम arch_decomp_setup(व्योम)
अणु
	पूर्णांक i;
	काष्ठा tag *t = (काष्ठा tag *)params;
	अचिन्हित पूर्णांक nr_pages = 0, page_size = PAGE_SIZE;

	अगर (t->hdr.tag == ATAG_CORE) अणु
		क्रम (; t->hdr.size; t = tag_next(t)) अणु
			अगर (t->hdr.tag == ATAG_VIDEOTEXT) अणु
				video_num_rows = t->u.videotext.video_lines;
				video_num_cols = t->u.videotext.video_cols;
				video_x = t->u.videotext.x;
				video_y = t->u.videotext.y;
			पूर्ण अन्यथा अगर (t->hdr.tag == ATAG_VIDEOLFB) अणु
				bytes_per_अक्षर_h = t->u.videolfb.lfb_depth;
				bytes_per_अक्षर_v = 8;
			पूर्ण अन्यथा अगर (t->hdr.tag == ATAG_MEM) अणु
				page_size = PAGE_SIZE;
				nr_pages += (t->u.mem.size / PAGE_SIZE);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		nr_pages = params->nr_pages;
		page_size = params->page_size;
		video_num_rows = params->video_num_rows;
		video_num_cols = params->video_num_cols;
		video_x = params->video_x;
		video_y = params->video_y;
		bytes_per_अक्षर_h = params->bytes_per_अक्षर_h;
		bytes_per_अक्षर_v = params->bytes_per_अक्षर_v;
	पूर्ण

	video_size_row = video_num_cols * bytes_per_अक्षर_h;
	
	अगर (bytes_per_अक्षर_h == 4)
		क्रम (i = 0; i < 256; i++)
			con_अक्षरconvtable[i] =
				(i & 128 ? 1 << 0  : 0) |
				(i & 64  ? 1 << 4  : 0) |
				(i & 32  ? 1 << 8  : 0) |
				(i & 16  ? 1 << 12 : 0) |
				(i & 8   ? 1 << 16 : 0) |
				(i & 4   ? 1 << 20 : 0) |
				(i & 2   ? 1 << 24 : 0) |
				(i & 1   ? 1 << 28 : 0);
	अन्यथा
		क्रम (i = 0; i < 16; i++)
			con_अक्षरconvtable[i] =
				(i & 8   ? 1 << 0  : 0) |
				(i & 4   ? 1 << 8  : 0) |
				(i & 2   ? 1 << 16 : 0) |
				(i & 1   ? 1 << 24 : 0);


	palette_setpixel(0);
	अगर (bytes_per_अक्षर_h == 1) अणु
		palette_ग_लिखो (0);
		palette_ग_लिखो (0x00ffffff);
		क्रम (i = 2; i < 256; i++)
			palette_ग_लिखो (0);
		white = 1;
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < 256; i++)
			palette_ग_लिखो (i < 16 ? palette_4[i] : 0);
		white = 7;
	पूर्ण

	अगर (nr_pages * page_size < 4096*1024) error("<4M of mem\n");
पूर्ण
#पूर्ण_अगर
