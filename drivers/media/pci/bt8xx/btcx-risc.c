<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

    btcx-risc.c

    bt848/bt878/cx2388x risc code generator.

    (c) 2000-03 Gerd Knorr <kraxel@bytesex.org> [SuSE Lअसल]


*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/page.h>

#समावेश "btcx-risc.h"

अटल अचिन्हित पूर्णांक btcx_debug;
module_param(btcx_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(btcx_debug,"debug messages, default is 0 (no)");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु				\
	अगर (btcx_debug)						\
		prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt),		\
		       __func__, ##arg);			\
पूर्ण जबतक (0)


/* ---------------------------------------------------------- */
/* allocate/मुक्त risc memory                                  */

अटल पूर्णांक memcnt;

व्योम btcx_riscmem_मुक्त(काष्ठा pci_dev *pci,
		       काष्ठा btcx_riscmem *risc)
अणु
	अगर (शून्य == risc->cpu)
		वापस;

	memcnt--;
	dprपूर्णांकk("btcx: riscmem free [%d] dma=%lx\n",
		memcnt, (अचिन्हित दीर्घ)risc->dma);

	dma_मुक्त_coherent(&pci->dev, risc->size, risc->cpu, risc->dma);
	स_रखो(risc,0,माप(*risc));
पूर्ण

पूर्णांक btcx_riscmem_alloc(काष्ठा pci_dev *pci,
		       काष्ठा btcx_riscmem *risc,
		       अचिन्हित पूर्णांक size)
अणु
	__le32 *cpu;
	dma_addr_t dma = 0;

	अगर (शून्य != risc->cpu && risc->size < size)
		btcx_riscmem_मुक्त(pci,risc);
	अगर (शून्य == risc->cpu) अणु
		cpu = dma_alloc_coherent(&pci->dev, size, &dma, GFP_KERNEL);
		अगर (शून्य == cpu)
			वापस -ENOMEM;
		risc->cpu  = cpu;
		risc->dma  = dma;
		risc->size = size;

		memcnt++;
		dprपूर्णांकk("btcx: riscmem alloc [%d] dma=%lx cpu=%p size=%d\n",
			memcnt, (अचिन्हित दीर्घ)dma, cpu, size);
	पूर्ण
	वापस 0;
पूर्ण

/* ---------------------------------------------------------- */
/* screen overlay helpers                                     */

पूर्णांक
btcx_screen_clips(पूर्णांक swidth, पूर्णांक sheight, काष्ठा v4l2_rect *win,
		  काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक n)
अणु
	अगर (win->left < 0) अणु
		/* left */
		clips[n].c.left = 0;
		clips[n].c.top = 0;
		clips[n].c.width  = -win->left;
		clips[n].c.height = win->height;
		n++;
	पूर्ण
	अगर (win->left + win->width > swidth) अणु
		/* right */
		clips[n].c.left   = swidth - win->left;
		clips[n].c.top    = 0;
		clips[n].c.width  = win->width - clips[n].c.left;
		clips[n].c.height = win->height;
		n++;
	पूर्ण
	अगर (win->top < 0) अणु
		/* top */
		clips[n].c.left = 0;
		clips[n].c.top = 0;
		clips[n].c.width  = win->width;
		clips[n].c.height = -win->top;
		n++;
	पूर्ण
	अगर (win->top + win->height > sheight) अणु
		/* bottom */
		clips[n].c.left = 0;
		clips[n].c.top = sheight - win->top;
		clips[n].c.width  = win->width;
		clips[n].c.height = win->height - clips[n].c.top;
		n++;
	पूर्ण
	वापस n;
पूर्ण

पूर्णांक
btcx_align(काष्ठा v4l2_rect *win, काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक n, पूर्णांक mask)
अणु
	s32 nx,nw,dx;
	अचिन्हित पूर्णांक i;

	/* fixup winकरोw */
	nx = (win->left + mask) & ~mask;
	nw = (win->width) & ~mask;
	अगर (nx + nw > win->left + win->width)
		nw -= mask+1;
	dx = nx - win->left;
	win->left  = nx;
	win->width = nw;
	dprपूर्णांकk("btcx: window align %dx%d+%d+%d [dx=%d]\n",
	       win->width, win->height, win->left, win->top, dx);

	/* fixup clips */
	क्रम (i = 0; i < n; i++) अणु
		nx = (clips[i].c.left-dx) & ~mask;
		nw = (clips[i].c.width) & ~mask;
		अगर (nx + nw < clips[i].c.left-dx + clips[i].c.width)
			nw += mask+1;
		clips[i].c.left  = nx;
		clips[i].c.width = nw;
		dprपूर्णांकk("btcx:   clip align %dx%d+%d+%d\n",
		       clips[i].c.width, clips[i].c.height,
		       clips[i].c.left, clips[i].c.top);
	पूर्ण
	वापस 0;
पूर्ण

व्योम
btcx_sort_clips(काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक nclips)
अणु
	पूर्णांक i,j,n;

	अगर (nclips < 2)
		वापस;
	क्रम (i = nclips-2; i >= 0; i--) अणु
		क्रम (n = 0, j = 0; j <= i; j++) अणु
			अगर (clips[j].c.left > clips[j+1].c.left) अणु
				swap(clips[j], clips[j + 1]);
				n++;
			पूर्ण
		पूर्ण
		अगर (0 == n)
			अवरोध;
	पूर्ण
पूर्ण

व्योम
btcx_calc_skips(पूर्णांक line, पूर्णांक width, पूर्णांक *maxy,
		काष्ठा btcx_skiplist *skips, अचिन्हित पूर्णांक *nskips,
		स्थिर काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक nclips)
अणु
	अचिन्हित पूर्णांक clip,skip;
	पूर्णांक end, maxline;

	skip=0;
	maxline = 9999;
	क्रम (clip = 0; clip < nclips; clip++) अणु

		/* sanity checks */
		अगर (clips[clip].c.left + clips[clip].c.width <= 0)
			जारी;
		अगर (clips[clip].c.left > (चिन्हित)width)
			अवरोध;

		/* vertical range */
		अगर (line > clips[clip].c.top+clips[clip].c.height-1)
			जारी;
		अगर (line < clips[clip].c.top) अणु
			अगर (maxline > clips[clip].c.top-1)
				maxline = clips[clip].c.top-1;
			जारी;
		पूर्ण
		अगर (maxline > clips[clip].c.top+clips[clip].c.height-1)
			maxline = clips[clip].c.top+clips[clip].c.height-1;

		/* horizontal range */
		अगर (0 == skip || clips[clip].c.left > skips[skip-1].end) अणु
			/* new one */
			skips[skip].start = clips[clip].c.left;
			अगर (skips[skip].start < 0)
				skips[skip].start = 0;
			skips[skip].end = clips[clip].c.left + clips[clip].c.width;
			अगर (skips[skip].end > width)
				skips[skip].end = width;
			skip++;
		पूर्ण अन्यथा अणु
			/* overlaps -- expand last one */
			end = clips[clip].c.left + clips[clip].c.width;
			अगर (skips[skip-1].end < end)
				skips[skip-1].end = end;
			अगर (skips[skip-1].end > width)
				skips[skip-1].end = width;
		पूर्ण
	पूर्ण
	*nskips = skip;
	*maxy = maxline;

	अगर (btcx_debug) अणु
		dprपूर्णांकk("btcx: skips line %d-%d:", line, maxline);
		क्रम (skip = 0; skip < *nskips; skip++) अणु
			pr_cont(" %d-%d", skips[skip].start, skips[skip].end);
		पूर्ण
		pr_cont("\n");
	पूर्ण
पूर्ण
