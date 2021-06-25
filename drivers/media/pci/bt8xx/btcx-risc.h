<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
काष्ठा btcx_riscmem अणु
	अचिन्हित पूर्णांक   size;
	__le32         *cpu;
	__le32         *jmp;
	dma_addr_t     dma;
पूर्ण;

काष्ठा btcx_skiplist अणु
	पूर्णांक start;
	पूर्णांक end;
पूर्ण;

पूर्णांक  btcx_riscmem_alloc(काष्ठा pci_dev *pci,
			काष्ठा btcx_riscmem *risc,
			अचिन्हित पूर्णांक size);
व्योम btcx_riscmem_मुक्त(काष्ठा pci_dev *pci,
		       काष्ठा btcx_riscmem *risc);

पूर्णांक btcx_screen_clips(पूर्णांक swidth, पूर्णांक sheight, काष्ठा v4l2_rect *win,
		      काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक n);
पूर्णांक btcx_align(काष्ठा v4l2_rect *win, काष्ठा v4l2_clip *clips,
	       अचिन्हित पूर्णांक n, पूर्णांक mask);
व्योम btcx_sort_clips(काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक nclips);
व्योम btcx_calc_skips(पूर्णांक line, पूर्णांक width, पूर्णांक *maxy,
		     काष्ठा btcx_skiplist *skips, अचिन्हित पूर्णांक *nskips,
		     स्थिर काष्ठा v4l2_clip *clips, अचिन्हित पूर्णांक nclips);
