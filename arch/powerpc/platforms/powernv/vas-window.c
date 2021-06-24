<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright 2016-17 IBM Corp.
 */

#घोषणा pr_fmt(fmt) "vas: " fmt

#समावेश <linux/types.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>
#समावेश <linux/log2.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/cred.h>
#समावेश <linux/sched/mm.h>
#समावेश <linux/mmu_context.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश "vas.h"
#समावेश "copy-paste.h"

#घोषणा CREATE_TRACE_POINTS
#समावेश "vas-trace.h"

/*
 * Compute the paste address region क्रम the winकरोw @winकरोw using the
 * ->paste_base_addr and ->paste_win_id_shअगरt we got from device tree.
 */
व्योम vas_win_paste_addr(काष्ठा vas_winकरोw *winकरोw, u64 *addr, पूर्णांक *len)
अणु
	पूर्णांक winid;
	u64 base, shअगरt;

	base = winकरोw->vinst->paste_base_addr;
	shअगरt = winकरोw->vinst->paste_win_id_shअगरt;
	winid = winकरोw->winid;

	*addr  = base + (winid << shअगरt);
	अगर (len)
		*len = PAGE_SIZE;

	pr_debug("Txwin #%d: Paste addr 0x%llx\n", winid, *addr);
पूर्ण

अटल अंतरभूत व्योम get_hvwc_mmio_bar(काष्ठा vas_winकरोw *winकरोw,
			u64 *start, पूर्णांक *len)
अणु
	u64 pbaddr;

	pbaddr = winकरोw->vinst->hvwc_bar_start;
	*start = pbaddr + winकरोw->winid * VAS_HVWC_SIZE;
	*len = VAS_HVWC_SIZE;
पूर्ण

अटल अंतरभूत व्योम get_uwc_mmio_bar(काष्ठा vas_winकरोw *winकरोw,
			u64 *start, पूर्णांक *len)
अणु
	u64 pbaddr;

	pbaddr = winकरोw->vinst->uwc_bar_start;
	*start = pbaddr + winकरोw->winid * VAS_UWC_SIZE;
	*len = VAS_UWC_SIZE;
पूर्ण

/*
 * Map the paste bus address of the given send winकरोw पूर्णांकo kernel address
 * space. Unlike MMIO regions (map_mmio_region() below), paste region must
 * be mapped cache-able and is only applicable to send winकरोws.
 */
अटल व्योम *map_paste_region(काष्ठा vas_winकरोw *txwin)
अणु
	पूर्णांक len;
	व्योम *map;
	अक्षर *name;
	u64 start;

	name = kaप्र_लिखो(GFP_KERNEL, "window-v%d-w%d", txwin->vinst->vas_id,
				txwin->winid);
	अगर (!name)
		जाओ मुक्त_name;

	txwin->paste_addr_name = name;
	vas_win_paste_addr(txwin, &start, &len);

	अगर (!request_mem_region(start, len, name)) अणु
		pr_devel("%s(): request_mem_region(0x%llx, %d) failed\n",
				__func__, start, len);
		जाओ मुक्त_name;
	पूर्ण

	map = ioremap_cache(start, len);
	अगर (!map) अणु
		pr_devel("%s(): ioremap_cache(0x%llx, %d) failed\n", __func__,
				start, len);
		जाओ मुक्त_name;
	पूर्ण

	pr_devel("Mapped paste addr 0x%llx to kaddr 0x%p\n", start, map);
	वापस map;

मुक्त_name:
	kमुक्त(name);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम *map_mmio_region(अक्षर *name, u64 start, पूर्णांक len)
अणु
	व्योम *map;

	अगर (!request_mem_region(start, len, name)) अणु
		pr_devel("%s(): request_mem_region(0x%llx, %d) failed\n",
				__func__, start, len);
		वापस शून्य;
	पूर्ण

	map = ioremap(start, len);
	अगर (!map) अणु
		pr_devel("%s(): ioremap(0x%llx, %d) failed\n", __func__, start,
				len);
		वापस शून्य;
	पूर्ण

	वापस map;
पूर्ण

अटल व्योम unmap_region(व्योम *addr, u64 start, पूर्णांक len)
अणु
	iounmap(addr);
	release_mem_region((phys_addr_t)start, len);
पूर्ण

/*
 * Unmap the paste address region क्रम a winकरोw.
 */
अटल व्योम unmap_paste_region(काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक len;
	u64 busaddr_start;

	अगर (winकरोw->paste_kaddr) अणु
		vas_win_paste_addr(winकरोw, &busaddr_start, &len);
		unmap_region(winकरोw->paste_kaddr, busaddr_start, len);
		winकरोw->paste_kaddr = शून्य;
		kमुक्त(winकरोw->paste_addr_name);
		winकरोw->paste_addr_name = शून्य;
	पूर्ण
पूर्ण

/*
 * Unmap the MMIO regions क्रम a winकरोw. Hold the vas_mutex so we करोn't
 * unmap when the winकरोw's debugfs dir is in use. This serializes बंद
 * of a winकरोw even on another VAS instance but since its not a critical
 * path, just minimize the समय we hold the mutex क्रम now. We can add
 * a per-instance mutex later अगर necessary.
 */
अटल व्योम unmap_winctx_mmio_bars(काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक len;
	व्योम *uwc_map;
	व्योम *hvwc_map;
	u64 busaddr_start;

	mutex_lock(&vas_mutex);

	hvwc_map = winकरोw->hvwc_map;
	winकरोw->hvwc_map = शून्य;

	uwc_map = winकरोw->uwc_map;
	winकरोw->uwc_map = शून्य;

	mutex_unlock(&vas_mutex);

	अगर (hvwc_map) अणु
		get_hvwc_mmio_bar(winकरोw, &busaddr_start, &len);
		unmap_region(hvwc_map, busaddr_start, len);
	पूर्ण

	अगर (uwc_map) अणु
		get_uwc_mmio_bar(winकरोw, &busaddr_start, &len);
		unmap_region(uwc_map, busaddr_start, len);
	पूर्ण
पूर्ण

/*
 * Find the Hypervisor Winकरोw Context (HVWC) MMIO Base Address Region and the
 * OS/User Winकरोw Context (UWC) MMIO Base Address Region क्रम the given winकरोw.
 * Map these bus addresses and save the mapped kernel addresses in @winकरोw.
 */
अटल पूर्णांक map_winctx_mmio_bars(काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक len;
	u64 start;

	get_hvwc_mmio_bar(winकरोw, &start, &len);
	winकरोw->hvwc_map = map_mmio_region("HVWCM_Window", start, len);

	get_uwc_mmio_bar(winकरोw, &start, &len);
	winकरोw->uwc_map = map_mmio_region("UWCM_Window", start, len);

	अगर (!winकरोw->hvwc_map || !winकरोw->uwc_map) अणु
		unmap_winctx_mmio_bars(winकरोw);
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Reset all valid रेजिस्टरs in the HV and OS/User Winकरोw Contexts क्रम
 * the winकरोw identअगरied by @winकरोw.
 *
 * NOTE: We cannot really use a क्रम loop to reset winकरोw context. Not all
 *	 offsets in a winकरोw context are valid रेजिस्टरs and the valid
 *	 रेजिस्टरs are not sequential. And, we can only ग_लिखो to offsets
 *	 with valid रेजिस्टरs.
 */
अटल व्योम reset_winकरोw_regs(काष्ठा vas_winकरोw *winकरोw)
अणु
	ग_लिखो_hvwc_reg(winकरोw, VREG(LPID), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(PID), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(XLATE_MSR), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(XLATE_LPCR), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(XLATE_CTL), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(AMR), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(SEIDR), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(FAULT_TX_WIN), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(OSU_INTR_SRC_RA), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(HV_INTR_SRC_RA), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(PSWID), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LFIFO_BAR), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LDATA_STAMP_CTL), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LDMA_CACHE_CTL), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LRFIFO_PUSH), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(CURR_MSG_COUNT), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_AFTER_COUNT), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LRX_WCRED), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LRX_WCRED_ADDER), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(TX_WCRED), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(TX_WCRED_ADDER), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LFIFO_SIZE), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(WINCTL), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(WIN_STATUS), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(WIN_CTX_CACHING_CTL), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(TX_RSVD_BUF_COUNT), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LRFIFO_WIN_PTR), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_CTL), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_PID), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_LPID), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_TID), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_SCOPE), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(NX_UTIL_ADDER), 0ULL);

	/* Skip पढ़ो-only रेजिस्टरs: NX_UTIL and NX_UTIL_SE */

	/*
	 * The send and receive winकरोw credit adder रेजिस्टरs are also
	 * accessible from HVWC and have been initialized above. We करोn't
	 * need to initialize from the OS/User Winकरोw Context, so skip
	 * following calls:
	 *
	 *	ग_लिखो_uwc_reg(winकरोw, VREG(TX_WCRED_ADDER), 0ULL);
	 *	ग_लिखो_uwc_reg(winकरोw, VREG(LRX_WCRED_ADDER), 0ULL);
	 */
पूर्ण

/*
 * Initialize winकरोw context रेजिस्टरs related to Address Translation.
 * These रेजिस्टरs are common to send/receive winकरोws although they
 * dअगरfer क्रम user/kernel winकरोws. As we resolve the TODOs we may
 * want to add fields to vas_winctx and move the initialization to
 * init_vas_winctx_regs().
 */
अटल व्योम init_xlate_regs(काष्ठा vas_winकरोw *winकरोw, bool user_win)
अणु
	u64 lpcr, val;

	/*
	 * MSR_TA, MSR_US are false क्रम both kernel and user.
	 * MSR_DR and MSR_PR are false क्रम kernel.
	 */
	val = 0ULL;
	val = SET_FIELD(VAS_XLATE_MSR_HV, val, 1);
	val = SET_FIELD(VAS_XLATE_MSR_SF, val, 1);
	अगर (user_win) अणु
		val = SET_FIELD(VAS_XLATE_MSR_DR, val, 1);
		val = SET_FIELD(VAS_XLATE_MSR_PR, val, 1);
	पूर्ण
	ग_लिखो_hvwc_reg(winकरोw, VREG(XLATE_MSR), val);

	lpcr = mfspr(SPRN_LPCR);
	val = 0ULL;
	/*
	 * NOTE: From Section 5.7.8.1 Segment Lookaside Buffer of the
	 *	 Power ISA, v3.0B, Page size encoding is 0 = 4KB, 5 = 64KB.
	 *
	 * NOTE: From Section 1.3.1, Address Translation Context of the
	 *	 Nest MMU Workbook, LPCR_SC should be 0 क्रम Power9.
	 */
	val = SET_FIELD(VAS_XLATE_LPCR_PAGE_SIZE, val, 5);
	val = SET_FIELD(VAS_XLATE_LPCR_ISL, val, lpcr & LPCR_ISL);
	val = SET_FIELD(VAS_XLATE_LPCR_TC, val, lpcr & LPCR_TC);
	val = SET_FIELD(VAS_XLATE_LPCR_SC, val, 0);
	ग_लिखो_hvwc_reg(winकरोw, VREG(XLATE_LPCR), val);

	/*
	 * Section 1.3.1 (Address translation Context) of NMMU workbook.
	 *	0b00	Hashed Page Table mode
	 *	0b01	Reserved
	 *	0b10	Radix on HPT
	 *	0b11	Radix on Radix
	 */
	val = 0ULL;
	val = SET_FIELD(VAS_XLATE_MODE, val, radix_enabled() ? 3 : 2);
	ग_लिखो_hvwc_reg(winकरोw, VREG(XLATE_CTL), val);

	/*
	 * TODO: Can we mfspr(AMR) even क्रम user winकरोws?
	 */
	val = 0ULL;
	val = SET_FIELD(VAS_AMR, val, mfspr(SPRN_AMR));
	ग_लिखो_hvwc_reg(winकरोw, VREG(AMR), val);

	val = 0ULL;
	val = SET_FIELD(VAS_SEIDR, val, 0);
	ग_लिखो_hvwc_reg(winकरोw, VREG(SEIDR), val);
पूर्ण

/*
 * Initialize Reserved Send Buffer Count क्रम the send winकरोw. It involves
 * writing to the रेजिस्टर, पढ़ोing it back to confirm that the hardware
 * has enough buffers to reserve. See section 1.3.1.2.1 of VAS workbook.
 *
 * Since we can only make a best-efक्रमt attempt to fulfill the request,
 * we करोn't वापस any errors अगर we cannot.
 *
 * TODO: Reserved (aka dedicated) send buffers are not supported yet.
 */
अटल व्योम init_rsvd_tx_buf_count(काष्ठा vas_winकरोw *txwin,
				काष्ठा vas_winctx *winctx)
अणु
	ग_लिखो_hvwc_reg(txwin, VREG(TX_RSVD_BUF_COUNT), 0ULL);
पूर्ण

/*
 * init_winctx_regs()
 *	Initialize winकरोw context रेजिस्टरs क्रम a receive winकरोw.
 *	Except क्रम caching control and marking winकरोw खोलो, the रेजिस्टरs
 *	are initialized in the order listed in Section 3.1.4 (Winकरोw Context
 *	Cache Register Details) of the VAS workbook although they करोn't need
 *	to be.
 *
 * Design note: For NX receive winकरोws, NX allocates the FIFO buffer in OPAL
 *	(so that it can get a large contiguous area) and passes that buffer
 *	to kernel via device tree. We now ग_लिखो that buffer address to the
 *	FIFO BAR. Would it make sense to करो this all in OPAL? i.e have OPAL
 *	ग_लिखो the per-chip RX FIFO addresses to the winकरोws during boot-up
 *	as a one-समय task? That could work क्रम NX but what about other
 *	receivers?  Let the receivers tell us the rx-fअगरo buffers क्रम now.
 */
अटल व्योम init_winctx_regs(काष्ठा vas_winकरोw *winकरोw,
			     काष्ठा vas_winctx *winctx)
अणु
	u64 val;
	पूर्णांक fअगरo_size;

	reset_winकरोw_regs(winकरोw);

	val = 0ULL;
	val = SET_FIELD(VAS_LPID, val, winctx->lpid);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LPID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_PID_ID, val, winctx->pidr);
	ग_लिखो_hvwc_reg(winकरोw, VREG(PID), val);

	init_xlate_regs(winकरोw, winctx->user_win);

	val = 0ULL;
	val = SET_FIELD(VAS_FAULT_TX_WIN, val, winctx->fault_win_id);
	ग_लिखो_hvwc_reg(winकरोw, VREG(FAULT_TX_WIN), val);

	/* In PowerNV, पूर्णांकerrupts go to HV. */
	ग_लिखो_hvwc_reg(winकरोw, VREG(OSU_INTR_SRC_RA), 0ULL);

	val = 0ULL;
	val = SET_FIELD(VAS_HV_INTR_SRC_RA, val, winctx->irq_port);
	ग_लिखो_hvwc_reg(winकरोw, VREG(HV_INTR_SRC_RA), val);

	val = 0ULL;
	val = SET_FIELD(VAS_PSWID_EA_HANDLE, val, winctx->pswid);
	ग_लिखो_hvwc_reg(winकरोw, VREG(PSWID), val);

	ग_लिखो_hvwc_reg(winकरोw, VREG(SPARE1), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(SPARE2), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(SPARE3), 0ULL);

	/*
	 * NOTE: VAS expects the FIFO address to be copied पूर्णांकo the LFIFO_BAR
	 *	 रेजिस्टर as is - करो NOT shअगरt the address पूर्णांकo VAS_LFIFO_BAR
	 *	 bit fields! Ok to set the page migration select fields -
	 *	 VAS ignores the lower 10+ bits in the address anyway, because
	 *	 the minimum FIFO size is 1K?
	 *
	 * See also: Design note in function header.
	 */
	val = __pa(winctx->rx_fअगरo);
	val = SET_FIELD(VAS_PAGE_MIGRATION_SELECT, val, 0);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LFIFO_BAR), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LDATA_STAMP, val, winctx->data_stamp);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LDATA_STAMP_CTL), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LDMA_TYPE, val, winctx->dma_type);
	val = SET_FIELD(VAS_LDMA_FIFO_DISABLE, val, winctx->fअगरo_disable);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LDMA_CACHE_CTL), val);

	ग_लिखो_hvwc_reg(winकरोw, VREG(LRFIFO_PUSH), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(CURR_MSG_COUNT), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_AFTER_COUNT), 0ULL);

	val = 0ULL;
	val = SET_FIELD(VAS_LRX_WCRED, val, winctx->wcreds_max);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LRX_WCRED), val);

	val = 0ULL;
	val = SET_FIELD(VAS_TX_WCRED, val, winctx->wcreds_max);
	ग_लिखो_hvwc_reg(winकरोw, VREG(TX_WCRED), val);

	ग_लिखो_hvwc_reg(winकरोw, VREG(LRX_WCRED_ADDER), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(TX_WCRED_ADDER), 0ULL);

	fअगरo_size = winctx->rx_fअगरo_size / 1024;

	val = 0ULL;
	val = SET_FIELD(VAS_LFIFO_SIZE, val, ilog2(fअगरo_size));
	ग_लिखो_hvwc_reg(winकरोw, VREG(LFIFO_SIZE), val);

	/* Update winकरोw control and caching control रेजिस्टरs last so
	 * we mark the winकरोw खोलो only after fully initializing it and
	 * pushing context to cache.
	 */

	ग_लिखो_hvwc_reg(winकरोw, VREG(WIN_STATUS), 0ULL);

	init_rsvd_tx_buf_count(winकरोw, winctx);

	/* क्रम a send winकरोw, poपूर्णांक to the matching receive winकरोw */
	val = 0ULL;
	val = SET_FIELD(VAS_LRX_WIN_ID, val, winctx->rx_win_id);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LRFIFO_WIN_PTR), val);

	ग_लिखो_hvwc_reg(winकरोw, VREG(SPARE4), 0ULL);

	val = 0ULL;
	val = SET_FIELD(VAS_NOTIFY_DISABLE, val, winctx->notअगरy_disable);
	val = SET_FIELD(VAS_INTR_DISABLE, val, winctx->पूर्णांकr_disable);
	val = SET_FIELD(VAS_NOTIFY_EARLY, val, winctx->notअगरy_early);
	val = SET_FIELD(VAS_NOTIFY_OSU_INTR, val, winctx->notअगरy_os_पूर्णांकr_reg);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_CTL), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_PID, val, winctx->lnotअगरy_pid);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_PID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_LPID, val, winctx->lnotअगरy_lpid);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_LPID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_TID, val, winctx->lnotअगरy_tid);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_TID), val);

	val = 0ULL;
	val = SET_FIELD(VAS_LNOTIFY_MIN_SCOPE, val, winctx->min_scope);
	val = SET_FIELD(VAS_LNOTIFY_MAX_SCOPE, val, winctx->max_scope);
	ग_लिखो_hvwc_reg(winकरोw, VREG(LNOTIFY_SCOPE), val);

	/* Skip पढ़ो-only रेजिस्टरs NX_UTIL and NX_UTIL_SE */

	ग_लिखो_hvwc_reg(winकरोw, VREG(SPARE5), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(NX_UTIL_ADDER), 0ULL);
	ग_लिखो_hvwc_reg(winकरोw, VREG(SPARE6), 0ULL);

	/* Finally, push winकरोw context to memory and... */
	val = 0ULL;
	val = SET_FIELD(VAS_PUSH_TO_MEM, val, 1);
	ग_लिखो_hvwc_reg(winकरोw, VREG(WIN_CTX_CACHING_CTL), val);

	/* ... mark the winकरोw खोलो क्रम business */
	val = 0ULL;
	val = SET_FIELD(VAS_WINCTL_REJ_NO_CREDIT, val, winctx->rej_no_credit);
	val = SET_FIELD(VAS_WINCTL_PIN, val, winctx->pin_win);
	val = SET_FIELD(VAS_WINCTL_TX_WCRED_MODE, val, winctx->tx_wcred_mode);
	val = SET_FIELD(VAS_WINCTL_RX_WCRED_MODE, val, winctx->rx_wcred_mode);
	val = SET_FIELD(VAS_WINCTL_TX_WORD_MODE, val, winctx->tx_word_mode);
	val = SET_FIELD(VAS_WINCTL_RX_WORD_MODE, val, winctx->rx_word_mode);
	val = SET_FIELD(VAS_WINCTL_FAULT_WIN, val, winctx->fault_win);
	val = SET_FIELD(VAS_WINCTL_NX_WIN, val, winctx->nx_win);
	val = SET_FIELD(VAS_WINCTL_OPEN, val, 1);
	ग_लिखो_hvwc_reg(winकरोw, VREG(WINCTL), val);
पूर्ण

अटल व्योम vas_release_winकरोw_id(काष्ठा ida *ida, पूर्णांक winid)
अणु
	ida_मुक्त(ida, winid);
पूर्ण

अटल पूर्णांक vas_assign_winकरोw_id(काष्ठा ida *ida)
अणु
	पूर्णांक winid = ida_alloc_max(ida, VAS_WINDOWS_PER_CHIP - 1, GFP_KERNEL);

	अगर (winid == -ENOSPC) अणु
		pr_err("Too many (%d) open windows\n", VAS_WINDOWS_PER_CHIP);
		वापस -EAGAIN;
	पूर्ण

	वापस winid;
पूर्ण

अटल व्योम vas_winकरोw_मुक्त(काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक winid = winकरोw->winid;
	काष्ठा vas_instance *vinst = winकरोw->vinst;

	unmap_winctx_mmio_bars(winकरोw);

	vas_winकरोw_मुक्त_dbgdir(winकरोw);

	kमुक्त(winकरोw);

	vas_release_winकरोw_id(&vinst->ida, winid);
पूर्ण

अटल काष्ठा vas_winकरोw *vas_winकरोw_alloc(काष्ठा vas_instance *vinst)
अणु
	पूर्णांक winid;
	काष्ठा vas_winकरोw *winकरोw;

	winid = vas_assign_winकरोw_id(&vinst->ida);
	अगर (winid < 0)
		वापस ERR_PTR(winid);

	winकरोw = kzalloc(माप(*winकरोw), GFP_KERNEL);
	अगर (!winकरोw)
		जाओ out_मुक्त;

	winकरोw->vinst = vinst;
	winकरोw->winid = winid;

	अगर (map_winctx_mmio_bars(winकरोw))
		जाओ out_मुक्त;

	vas_winकरोw_init_dbgdir(winकरोw);

	वापस winकरोw;

out_मुक्त:
	kमुक्त(winकरोw);
	vas_release_winकरोw_id(&vinst->ida, winid);
	वापस ERR_PTR(-ENOMEM);
पूर्ण

अटल व्योम put_rx_win(काष्ठा vas_winकरोw *rxwin)
अणु
	/* Better not be a send winकरोw! */
	WARN_ON_ONCE(rxwin->tx_win);

	atomic_dec(&rxwin->num_txwins);
पूर्ण

/*
 * Find the user space receive winकरोw given the @pswid.
 *      - We must have a valid vasid and it must beदीर्घ to this instance.
 *        (so both send and receive winकरोws are on the same VAS instance)
 *      - The winकरोw must refer to an OPEN, FTW, RECEIVE winकरोw.
 *
 * NOTE: We access ->winकरोws[] table and assume that vinst->mutex is held.
 */
अटल काष्ठा vas_winकरोw *get_user_rxwin(काष्ठा vas_instance *vinst, u32 pswid)
अणु
	पूर्णांक vasid, winid;
	काष्ठा vas_winकरोw *rxwin;

	decode_pswid(pswid, &vasid, &winid);

	अगर (vinst->vas_id != vasid)
		वापस ERR_PTR(-EINVAL);

	rxwin = vinst->winकरोws[winid];

	अगर (!rxwin || rxwin->tx_win || rxwin->cop != VAS_COP_TYPE_FTW)
		वापस ERR_PTR(-EINVAL);

	वापस rxwin;
पूर्ण

/*
 * Get the VAS receive winकरोw associated with NX engine identअगरied
 * by @cop and अगर applicable, @pswid.
 *
 * See also function header of set_vinst_win().
 */
अटल काष्ठा vas_winकरोw *get_vinst_rxwin(काष्ठा vas_instance *vinst,
			क्रमागत vas_cop_type cop, u32 pswid)
अणु
	काष्ठा vas_winकरोw *rxwin;

	mutex_lock(&vinst->mutex);

	अगर (cop == VAS_COP_TYPE_FTW)
		rxwin = get_user_rxwin(vinst, pswid);
	अन्यथा
		rxwin = vinst->rxwin[cop] ?: ERR_PTR(-EINVAL);

	अगर (!IS_ERR(rxwin))
		atomic_inc(&rxwin->num_txwins);

	mutex_unlock(&vinst->mutex);

	वापस rxwin;
पूर्ण

/*
 * We have two tables of winकरोws in a VAS instance. The first one,
 * ->winकरोws[], contains all the winकरोws in the instance and allows
 * looking up a winकरोw by its id. It is used to look up send winकरोws
 * during fault handling and receive winकरोws when pairing user space
 * send/receive winकरोws.
 *
 * The second table, ->rxwin[], contains receive winकरोws that are
 * associated with NX engines. This table has VAS_COP_TYPE_MAX
 * entries and is used to look up a receive winकरोw by its
 * coprocessor type.
 *
 * Here, we save @winकरोw in the ->winकरोws[] table. If it is a receive
 * winकरोw, we also save the winकरोw in the ->rxwin[] table.
 */
अटल व्योम set_vinst_win(काष्ठा vas_instance *vinst,
			काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक id = winकरोw->winid;

	mutex_lock(&vinst->mutex);

	/*
	 * There should only be one receive winकरोw क्रम a coprocessor type
	 * unless its a user (FTW) winकरोw.
	 */
	अगर (!winकरोw->user_win && !winकरोw->tx_win) अणु
		WARN_ON_ONCE(vinst->rxwin[winकरोw->cop]);
		vinst->rxwin[winकरोw->cop] = winकरोw;
	पूर्ण

	WARN_ON_ONCE(vinst->winकरोws[id] != शून्य);
	vinst->winकरोws[id] = winकरोw;

	mutex_unlock(&vinst->mutex);
पूर्ण

/*
 * Clear this winकरोw from the table(s) of winकरोws क्रम this VAS instance.
 * See also function header of set_vinst_win().
 */
अटल व्योम clear_vinst_win(काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक id = winकरोw->winid;
	काष्ठा vas_instance *vinst = winकरोw->vinst;

	mutex_lock(&vinst->mutex);

	अगर (!winकरोw->user_win && !winकरोw->tx_win) अणु
		WARN_ON_ONCE(!vinst->rxwin[winकरोw->cop]);
		vinst->rxwin[winकरोw->cop] = शून्य;
	पूर्ण

	WARN_ON_ONCE(vinst->winकरोws[id] != winकरोw);
	vinst->winकरोws[id] = शून्य;

	mutex_unlock(&vinst->mutex);
पूर्ण

अटल व्योम init_winctx_क्रम_rxwin(काष्ठा vas_winकरोw *rxwin,
			काष्ठा vas_rx_win_attr *rxattr,
			काष्ठा vas_winctx *winctx)
अणु
	/*
	 * We first zero (स_रखो()) all fields and only set non-zero fields.
	 * Following fields are 0/false but maybe deserve a comment:
	 *
	 *	->notअगरy_os_पूर्णांकr_reg	In घातerNV, send पूर्णांकrs to HV
	 *	->notअगरy_disable	False क्रम NX winकरोws
	 *	->पूर्णांकr_disable		False क्रम Fault Winकरोws
	 *	->xtra_ग_लिखो		False क्रम NX winकरोws
	 *	->notअगरy_early		NA क्रम NX winकरोws
	 *	->rsvd_txbuf_count	NA क्रम Rx winकरोws
	 *	->lpid, ->pid, ->tid	NA क्रम Rx winकरोws
	 */

	स_रखो(winctx, 0, माप(काष्ठा vas_winctx));

	winctx->rx_fअगरo = rxattr->rx_fअगरo;
	winctx->rx_fअगरo_size = rxattr->rx_fअगरo_size;
	winctx->wcreds_max = rxwin->wcreds_max;
	winctx->pin_win = rxattr->pin_win;

	winctx->nx_win = rxattr->nx_win;
	winctx->fault_win = rxattr->fault_win;
	winctx->user_win = rxattr->user_win;
	winctx->rej_no_credit = rxattr->rej_no_credit;
	winctx->rx_word_mode = rxattr->rx_win_ord_mode;
	winctx->tx_word_mode = rxattr->tx_win_ord_mode;
	winctx->rx_wcred_mode = rxattr->rx_wcred_mode;
	winctx->tx_wcred_mode = rxattr->tx_wcred_mode;
	winctx->notअगरy_early = rxattr->notअगरy_early;

	अगर (winctx->nx_win) अणु
		winctx->data_stamp = true;
		winctx->पूर्णांकr_disable = true;
		winctx->pin_win = true;

		WARN_ON_ONCE(winctx->fault_win);
		WARN_ON_ONCE(!winctx->rx_word_mode);
		WARN_ON_ONCE(!winctx->tx_word_mode);
		WARN_ON_ONCE(winctx->notअगरy_after_count);
	पूर्ण अन्यथा अगर (winctx->fault_win) अणु
		winctx->notअगरy_disable = true;
	पूर्ण अन्यथा अगर (winctx->user_win) अणु
		/*
		 * Section 1.8.1 Low Latency Core-Core Wake up of
		 * the VAS workbook:
		 *
		 *      - disable credit checks ([tr]x_wcred_mode = false)
		 *      - disable FIFO ग_लिखोs
		 *      - enable ASB_Notअगरy, disable पूर्णांकerrupt
		 */
		winctx->fअगरo_disable = true;
		winctx->पूर्णांकr_disable = true;
		winctx->rx_fअगरo = शून्य;
	पूर्ण

	winctx->lnotअगरy_lpid = rxattr->lnotअगरy_lpid;
	winctx->lnotअगरy_pid = rxattr->lnotअगरy_pid;
	winctx->lnotअगरy_tid = rxattr->lnotअगरy_tid;
	winctx->pswid = rxattr->pswid;
	winctx->dma_type = VAS_DMA_TYPE_INJECT;
	winctx->tc_mode = rxattr->tc_mode;

	winctx->min_scope = VAS_SCOPE_LOCAL;
	winctx->max_scope = VAS_SCOPE_VECTORED_GROUP;
	अगर (rxwin->vinst->virq)
		winctx->irq_port = rxwin->vinst->irq_port;
पूर्ण

अटल bool rx_win_args_valid(क्रमागत vas_cop_type cop,
			काष्ठा vas_rx_win_attr *attr)
अणु
	pr_debug("Rxattr: fault %d, notify %d, intr %d, early %d, fifo %d\n",
			attr->fault_win, attr->notअगरy_disable,
			attr->पूर्णांकr_disable, attr->notअगरy_early,
			attr->rx_fअगरo_size);

	अगर (cop >= VAS_COP_TYPE_MAX)
		वापस false;

	अगर (cop != VAS_COP_TYPE_FTW &&
				attr->rx_fअगरo_size < VAS_RX_FIFO_SIZE_MIN)
		वापस false;

	अगर (attr->rx_fअगरo_size > VAS_RX_FIFO_SIZE_MAX)
		वापस false;

	अगर (!attr->wcreds_max)
		वापस false;

	अगर (attr->nx_win) अणु
		/* cannot be fault or user winकरोw अगर it is nx */
		अगर (attr->fault_win || attr->user_win)
			वापस false;
		/*
		 * Section 3.1.4.32: NX Winकरोws must not disable notअगरication,
		 *	and must not enable पूर्णांकerrupts or early notअगरication.
		 */
		अगर (attr->notअगरy_disable || !attr->पूर्णांकr_disable ||
				attr->notअगरy_early)
			वापस false;
	पूर्ण अन्यथा अगर (attr->fault_win) अणु
		/* cannot be both fault and user winकरोw */
		अगर (attr->user_win)
			वापस false;

		/*
		 * Section 3.1.4.32: Fault winकरोws must disable notअगरication
		 *	but not पूर्णांकerrupts.
		 */
		अगर (!attr->notअगरy_disable || attr->पूर्णांकr_disable)
			वापस false;

	पूर्ण अन्यथा अगर (attr->user_win) अणु
		/*
		 * User receive winकरोws are only क्रम fast-thपढ़ो-wakeup
		 * (FTW). They करोn't need a FIFO and must disable पूर्णांकerrupts
		 */
		अगर (attr->rx_fअगरo || attr->rx_fअगरo_size || !attr->पूर्णांकr_disable)
			वापस false;
	पूर्ण अन्यथा अणु
		/* Rx winकरोw must be one of NX or Fault or User winकरोw. */
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

व्योम vas_init_rx_win_attr(काष्ठा vas_rx_win_attr *rxattr, क्रमागत vas_cop_type cop)
अणु
	स_रखो(rxattr, 0, माप(*rxattr));

	अगर (cop == VAS_COP_TYPE_842 || cop == VAS_COP_TYPE_842_HIPRI ||
		cop == VAS_COP_TYPE_GZIP || cop == VAS_COP_TYPE_GZIP_HIPRI) अणु
		rxattr->pin_win = true;
		rxattr->nx_win = true;
		rxattr->fault_win = false;
		rxattr->पूर्णांकr_disable = true;
		rxattr->rx_wcred_mode = true;
		rxattr->tx_wcred_mode = true;
		rxattr->rx_win_ord_mode = true;
		rxattr->tx_win_ord_mode = true;
	पूर्ण अन्यथा अगर (cop == VAS_COP_TYPE_FAULT) अणु
		rxattr->pin_win = true;
		rxattr->fault_win = true;
		rxattr->notअगरy_disable = true;
		rxattr->rx_wcred_mode = true;
		rxattr->rx_win_ord_mode = true;
		rxattr->rej_no_credit = true;
		rxattr->tc_mode = VAS_THRESH_DISABLED;
	पूर्ण अन्यथा अगर (cop == VAS_COP_TYPE_FTW) अणु
		rxattr->user_win = true;
		rxattr->पूर्णांकr_disable = true;

		/*
		 * As noted in the VAS Workbook we disable credit checks.
		 * If we enable credit checks in the future, we must also
		 * implement a mechanism to वापस the user credits or new
		 * paste operations will fail.
		 */
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vas_init_rx_win_attr);

काष्ठा vas_winकरोw *vas_rx_win_खोलो(पूर्णांक vasid, क्रमागत vas_cop_type cop,
			काष्ठा vas_rx_win_attr *rxattr)
अणु
	काष्ठा vas_winकरोw *rxwin;
	काष्ठा vas_winctx winctx;
	काष्ठा vas_instance *vinst;

	trace_vas_rx_win_खोलो(current, vasid, cop, rxattr);

	अगर (!rx_win_args_valid(cop, rxattr))
		वापस ERR_PTR(-EINVAL);

	vinst = find_vas_instance(vasid);
	अगर (!vinst) अणु
		pr_devel("vasid %d not found!\n", vasid);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	pr_devel("Found instance %d\n", vasid);

	rxwin = vas_winकरोw_alloc(vinst);
	अगर (IS_ERR(rxwin)) अणु
		pr_devel("Unable to allocate memory for Rx window\n");
		वापस rxwin;
	पूर्ण

	rxwin->tx_win = false;
	rxwin->nx_win = rxattr->nx_win;
	rxwin->user_win = rxattr->user_win;
	rxwin->cop = cop;
	rxwin->wcreds_max = rxattr->wcreds_max;

	init_winctx_क्रम_rxwin(rxwin, rxattr, &winctx);
	init_winctx_regs(rxwin, &winctx);

	set_vinst_win(vinst, rxwin);

	वापस rxwin;
पूर्ण
EXPORT_SYMBOL_GPL(vas_rx_win_खोलो);

व्योम vas_init_tx_win_attr(काष्ठा vas_tx_win_attr *txattr, क्रमागत vas_cop_type cop)
अणु
	स_रखो(txattr, 0, माप(*txattr));

	अगर (cop == VAS_COP_TYPE_842 || cop == VAS_COP_TYPE_842_HIPRI ||
		cop == VAS_COP_TYPE_GZIP || cop == VAS_COP_TYPE_GZIP_HIPRI) अणु
		txattr->rej_no_credit = false;
		txattr->rx_wcred_mode = true;
		txattr->tx_wcred_mode = true;
		txattr->rx_win_ord_mode = true;
		txattr->tx_win_ord_mode = true;
	पूर्ण अन्यथा अगर (cop == VAS_COP_TYPE_FTW) अणु
		txattr->user_win = true;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(vas_init_tx_win_attr);

अटल व्योम init_winctx_क्रम_txwin(काष्ठा vas_winकरोw *txwin,
			काष्ठा vas_tx_win_attr *txattr,
			काष्ठा vas_winctx *winctx)
अणु
	/*
	 * We first zero all fields and only set non-zero ones. Following
	 * are some fields set to 0/false क्रम the stated reason:
	 *
	 *	->notअगरy_os_पूर्णांकr_reg	In घातernv, send पूर्णांकrs to HV
	 *	->rsvd_txbuf_count	Not supported yet.
	 *	->notअगरy_disable	False क्रम NX winकरोws
	 *	->xtra_ग_लिखो		False क्रम NX winकरोws
	 *	->notअगरy_early		NA क्रम NX winकरोws
	 *	->lnotअगरy_lpid		NA क्रम Tx winकरोws
	 *	->lnotअगरy_pid		NA क्रम Tx winकरोws
	 *	->lnotअगरy_tid		NA क्रम Tx winकरोws
	 *	->tx_win_cred_mode	Ignore क्रम now क्रम NX winकरोws
	 *	->rx_win_cred_mode	Ignore क्रम now क्रम NX winकरोws
	 */
	स_रखो(winctx, 0, माप(काष्ठा vas_winctx));

	winctx->wcreds_max = txwin->wcreds_max;

	winctx->user_win = txattr->user_win;
	winctx->nx_win = txwin->rxwin->nx_win;
	winctx->pin_win = txattr->pin_win;
	winctx->rej_no_credit = txattr->rej_no_credit;
	winctx->rsvd_txbuf_enable = txattr->rsvd_txbuf_enable;

	winctx->rx_wcred_mode = txattr->rx_wcred_mode;
	winctx->tx_wcred_mode = txattr->tx_wcred_mode;
	winctx->rx_word_mode = txattr->rx_win_ord_mode;
	winctx->tx_word_mode = txattr->tx_win_ord_mode;
	winctx->rsvd_txbuf_count = txattr->rsvd_txbuf_count;

	winctx->पूर्णांकr_disable = true;
	अगर (winctx->nx_win)
		winctx->data_stamp = true;

	winctx->lpid = txattr->lpid;
	winctx->pidr = txattr->pidr;
	winctx->rx_win_id = txwin->rxwin->winid;
	/*
	 * IRQ and fault winकरोw setup is successful. Set fault winकरोw
	 * क्रम the send winकरोw so that पढ़ोy to handle faults.
	 */
	अगर (txwin->vinst->virq)
		winctx->fault_win_id = txwin->vinst->fault_win->winid;

	winctx->dma_type = VAS_DMA_TYPE_INJECT;
	winctx->tc_mode = txattr->tc_mode;
	winctx->min_scope = VAS_SCOPE_LOCAL;
	winctx->max_scope = VAS_SCOPE_VECTORED_GROUP;
	अगर (txwin->vinst->virq)
		winctx->irq_port = txwin->vinst->irq_port;

	winctx->pswid = txattr->pswid ? txattr->pswid :
			encode_pswid(txwin->vinst->vas_id, txwin->winid);
पूर्ण

अटल bool tx_win_args_valid(क्रमागत vas_cop_type cop,
			काष्ठा vas_tx_win_attr *attr)
अणु
	अगर (attr->tc_mode != VAS_THRESH_DISABLED)
		वापस false;

	अगर (cop > VAS_COP_TYPE_MAX)
		वापस false;

	अगर (attr->wcreds_max > VAS_TX_WCREDS_MAX)
		वापस false;

	अगर (attr->user_win) अणु
		अगर (attr->rsvd_txbuf_count)
			वापस false;

		अगर (cop != VAS_COP_TYPE_FTW && cop != VAS_COP_TYPE_GZIP &&
			cop != VAS_COP_TYPE_GZIP_HIPRI)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

काष्ठा vas_winकरोw *vas_tx_win_खोलो(पूर्णांक vasid, क्रमागत vas_cop_type cop,
			काष्ठा vas_tx_win_attr *attr)
अणु
	पूर्णांक rc;
	काष्ठा vas_winकरोw *txwin;
	काष्ठा vas_winकरोw *rxwin;
	काष्ठा vas_winctx winctx;
	काष्ठा vas_instance *vinst;

	trace_vas_tx_win_खोलो(current, vasid, cop, attr);

	अगर (!tx_win_args_valid(cop, attr))
		वापस ERR_PTR(-EINVAL);

	/*
	 * If caller did not specअगरy a vasid but specअगरied the PSWID of a
	 * receive winकरोw (applicable only to FTW winकरोws), use the vasid
	 * from that receive winकरोw.
	 */
	अगर (vasid == -1 && attr->pswid)
		decode_pswid(attr->pswid, &vasid, शून्य);

	vinst = find_vas_instance(vasid);
	अगर (!vinst) अणु
		pr_devel("vasid %d not found!\n", vasid);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rxwin = get_vinst_rxwin(vinst, cop, attr->pswid);
	अगर (IS_ERR(rxwin)) अणु
		pr_devel("No RxWin for vasid %d, cop %d\n", vasid, cop);
		वापस rxwin;
	पूर्ण

	txwin = vas_winकरोw_alloc(vinst);
	अगर (IS_ERR(txwin)) अणु
		rc = PTR_ERR(txwin);
		जाओ put_rxwin;
	पूर्ण

	txwin->cop = cop;
	txwin->tx_win = 1;
	txwin->rxwin = rxwin;
	txwin->nx_win = txwin->rxwin->nx_win;
	txwin->user_win = attr->user_win;
	txwin->wcreds_max = attr->wcreds_max ?: VAS_WCREDS_DEFAULT;

	init_winctx_क्रम_txwin(txwin, attr, &winctx);

	init_winctx_regs(txwin, &winctx);

	/*
	 * If its a kernel send winकरोw, map the winकरोw address पूर्णांकo the
	 * kernel's address space. For user winकरोws, user must issue an
	 * mmap() to map the winकरोw पूर्णांकo their address space.
	 *
	 * NOTE: If kernel ever resubmits a user CRB after handling a page
	 *	 fault, we will need to map this पूर्णांकo kernel as well.
	 */
	अगर (!txwin->user_win) अणु
		txwin->paste_kaddr = map_paste_region(txwin);
		अगर (IS_ERR(txwin->paste_kaddr)) अणु
			rc = PTR_ERR(txwin->paste_kaddr);
			जाओ मुक्त_winकरोw;
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Interrupt hanlder or fault winकरोw setup failed. Means
		 * NX can not generate fault क्रम page fault. So not
		 * खोलोing क्रम user space tx winकरोw.
		 */
		अगर (!vinst->virq) अणु
			rc = -ENODEV;
			जाओ मुक्त_winकरोw;
		पूर्ण

		/*
		 * Winकरोw खोलोed by a child thपढ़ो may not be बंदd when
		 * it निकासs. So take reference to its pid and release it
		 * when the winकरोw is मुक्त by parent thपढ़ो.
		 * Acquire a reference to the task's pid to make sure
		 * pid will not be re-used - needed only क्रम multithपढ़ो
		 * applications.
		 */
		txwin->pid = get_task_pid(current, PIDTYPE_PID);
		/*
		 * Acquire a reference to the task's mm.
		 */
		txwin->mm = get_task_mm(current);

		अगर (!txwin->mm) अणु
			put_pid(txwin->pid);
			pr_err("VAS: pid(%d): mm_struct is not found\n",
					current->pid);
			rc = -EPERM;
			जाओ मुक्त_winकरोw;
		पूर्ण

		mmgrab(txwin->mm);
		mmput(txwin->mm);
		mm_context_add_vas_winकरोw(txwin->mm);
		/*
		 * Process बंदs winकरोw during निकास. In the हाल of
		 * multithपढ़ो application, the child thपढ़ो can खोलो
		 * winकरोw and can निकास without closing it. Expects parent
		 * thपढ़ो to use and बंद the winकरोw. So करो not need
		 * to take pid reference क्रम parent thपढ़ो.
		 */
		txwin->tgid = find_get_pid(task_tgid_vnr(current));
		/*
		 * Even a process that has no क्रमeign real address mapping can
		 * use an unpaired COPY inकाष्ठाion (to no real effect). Issue
		 * CP_ABORT to clear any pending COPY and prevent a covert
		 * channel.
		 *
		 * __चयन_to() will issue CP_ABORT on future context चयनes
		 * अगर process / thपढ़ो has any खोलो VAS winकरोw (Use
		 * current->mm->context.vas_winकरोws).
		 */
		यंत्र अस्थिर(PPC_CP_ABORT);
	पूर्ण

	set_vinst_win(vinst, txwin);

	वापस txwin;

मुक्त_winकरोw:
	vas_winकरोw_मुक्त(txwin);

put_rxwin:
	put_rx_win(rxwin);
	वापस ERR_PTR(rc);

पूर्ण
EXPORT_SYMBOL_GPL(vas_tx_win_खोलो);

पूर्णांक vas_copy_crb(व्योम *crb, पूर्णांक offset)
अणु
	वापस vas_copy(crb, offset);
पूर्ण
EXPORT_SYMBOL_GPL(vas_copy_crb);

#घोषणा RMA_LSMP_REPORT_ENABLE PPC_BIT(53)
पूर्णांक vas_paste_crb(काष्ठा vas_winकरोw *txwin, पूर्णांक offset, bool re)
अणु
	पूर्णांक rc;
	व्योम *addr;
	uपूर्णांक64_t val;

	trace_vas_paste_crb(current, txwin);

	/*
	 * Only NX winकरोws are supported क्रम now and hardware assumes
	 * report-enable flag is set क्रम NX winकरोws. Ensure software
	 * complies too.
	 */
	WARN_ON_ONCE(txwin->nx_win && !re);

	addr = txwin->paste_kaddr;
	अगर (re) अणु
		/*
		 * Set the REPORT_ENABLE bit (equivalent to writing
		 * to 1K offset of the paste address)
		 */
		val = SET_FIELD(RMA_LSMP_REPORT_ENABLE, 0ULL, 1);
		addr += val;
	पूर्ण

	/*
	 * Map the raw CR value from vas_paste() to an error code (there
	 * is just pass or fail क्रम now though).
	 */
	rc = vas_paste(addr, offset);
	अगर (rc == 2)
		rc = 0;
	अन्यथा
		rc = -EINVAL;

	pr_debug("Txwin #%d: Msg count %llu\n", txwin->winid,
			पढ़ो_hvwc_reg(txwin, VREG(LRFIFO_PUSH)));

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(vas_paste_crb);

/*
 * If credit checking is enabled क्रम this winकरोw, poll क्रम the वापस
 * of winकरोw credits (i.e क्रम NX engines to process any outstanding CRBs).
 * Since NX-842 रुकोs क्रम the CRBs to be processed beक्रमe closing the
 * winकरोw, we should not have to रुको क्रम too दीर्घ.
 *
 * TODO: We retry in 10ms पूर्णांकervals now. We could/should probably peek at
 *	the VAS_LRFIFO_PUSH_OFFSET रेजिस्टर to get an estimate of pending
 *	CRBs on the FIFO and compute the delay dynamically on each retry.
 *	But that is not really needed until we support NX-GZIP access from
 *	user space. (NX-842 driver रुकोs क्रम CSB and Fast thपढ़ो-wakeup
 *	करोesn't use credit checking).
 */
अटल व्योम poll_winकरोw_credits(काष्ठा vas_winकरोw *winकरोw)
अणु
	u64 val;
	पूर्णांक creds, mode;
	पूर्णांक count = 0;

	val = पढ़ो_hvwc_reg(winकरोw, VREG(WINCTL));
	अगर (winकरोw->tx_win)
		mode = GET_FIELD(VAS_WINCTL_TX_WCRED_MODE, val);
	अन्यथा
		mode = GET_FIELD(VAS_WINCTL_RX_WCRED_MODE, val);

	अगर (!mode)
		वापस;
retry:
	अगर (winकरोw->tx_win) अणु
		val = पढ़ो_hvwc_reg(winकरोw, VREG(TX_WCRED));
		creds = GET_FIELD(VAS_TX_WCRED, val);
	पूर्ण अन्यथा अणु
		val = पढ़ो_hvwc_reg(winकरोw, VREG(LRX_WCRED));
		creds = GET_FIELD(VAS_LRX_WCRED, val);
	पूर्ण

	/*
	 * Takes around few milliseconds to complete all pending requests
	 * and वापस credits.
	 * TODO: Scan fault FIFO and invalidate CRBs poपूर्णांकs to this winकरोw
	 *       and issue CRB Kill to stop all pending requests. Need only
	 *       अगर there is a bug in NX or fault handling in kernel.
	 */
	अगर (creds < winकरोw->wcreds_max) अणु
		val = 0;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(10));
		count++;
		/*
		 * Process can not बंद send winकरोw until all credits are
		 * वापसed.
		 */
		अगर (!(count % 1000))
			pr_warn_ratelimited("VAS: pid %d stuck. Waiting for credits returned for Window(%d). creds %d, Retries %d\n",
				vas_winकरोw_pid(winकरोw), winकरोw->winid,
				creds, count);

		जाओ retry;
	पूर्ण
पूर्ण

/*
 * Wait क्रम the winकरोw to go to "not-busy" state. It should only take a
 * लघु समय to queue a CRB, so winकरोw should not be busy क्रम too दीर्घ.
 * Trying 5ms पूर्णांकervals.
 */
अटल व्योम poll_winकरोw_busy_state(काष्ठा vas_winकरोw *winकरोw)
अणु
	पूर्णांक busy;
	u64 val;
	पूर्णांक count = 0;

retry:
	val = पढ़ो_hvwc_reg(winकरोw, VREG(WIN_STATUS));
	busy = GET_FIELD(VAS_WIN_BUSY, val);
	अगर (busy) अणु
		val = 0;
		set_current_state(TASK_UNINTERRUPTIBLE);
		schedule_समयout(msecs_to_jअगरfies(10));
		count++;
		/*
		 * Takes around few milliseconds to process all pending
		 * requests.
		 */
		अगर (!(count % 1000))
			pr_warn_ratelimited("VAS: pid %d stuck. Window (ID=%d) is in busy state. Retries %d\n",
				vas_winकरोw_pid(winकरोw), winकरोw->winid, count);

		जाओ retry;
	पूर्ण
पूर्ण

/*
 * Have the hardware cast a winकरोw out of cache and रुको क्रम it to
 * be completed.
 *
 * NOTE: It can take a relatively दीर्घ समय to cast the winकरोw context
 *	out of the cache. It is not strictly necessary to cast out अगर:
 *
 *	- we clear the "Pin Window" bit (so hardware is मुक्त to evict)
 *
 *	- we re-initialize the winकरोw context when it is reasचिन्हित.
 *
 *	We करो the क्रमmer in vas_win_बंद() and latter in vas_win_खोलो().
 *	So, ignoring the cast-out क्रम now. We can add it as needed. If
 *	casting out becomes necessary we should consider offloading the
 *	job to a worker thपढ़ो, so the winकरोw बंद can proceed quickly.
 */
अटल व्योम poll_winकरोw_castout(काष्ठा vas_winकरोw *winकरोw)
अणु
	/* stub क्रम now */
पूर्ण

/*
 * Unpin and बंद a winकरोw so no new requests are accepted and the
 * hardware can evict this winकरोw from cache अगर necessary.
 */
अटल व्योम unpin_बंद_winकरोw(काष्ठा vas_winकरोw *winकरोw)
अणु
	u64 val;

	val = पढ़ो_hvwc_reg(winकरोw, VREG(WINCTL));
	val = SET_FIELD(VAS_WINCTL_PIN, val, 0);
	val = SET_FIELD(VAS_WINCTL_OPEN, val, 0);
	ग_लिखो_hvwc_reg(winकरोw, VREG(WINCTL), val);
पूर्ण

/*
 * Close a winकरोw.
 *
 * See Section 1.12.1 of VAS workbook v1.05 क्रम details on closing winकरोw:
 *	- Disable new paste operations (unmap paste address)
 *	- Poll क्रम the "Window Busy" bit to be cleared
 *	- Clear the Open/Enable bit क्रम the Winकरोw.
 *	- Poll क्रम वापस of winकरोw Credits (implies FIFO empty क्रम Rx win?)
 *	- Unpin and cast winकरोw context out of cache
 *
 * Besides the hardware, kernel has some bookkeeping of course.
 */
पूर्णांक vas_win_बंद(काष्ठा vas_winकरोw *winकरोw)
अणु
	अगर (!winकरोw)
		वापस 0;

	अगर (!winकरोw->tx_win && atomic_पढ़ो(&winकरोw->num_txwins) != 0) अणु
		pr_devel("Attempting to close an active Rx window!\n");
		WARN_ON_ONCE(1);
		वापस -EBUSY;
	पूर्ण

	unmap_paste_region(winकरोw);

	poll_winकरोw_busy_state(winकरोw);

	unpin_बंद_winकरोw(winकरोw);

	poll_winकरोw_credits(winकरोw);

	clear_vinst_win(winकरोw);

	poll_winकरोw_castout(winकरोw);

	/* अगर send winकरोw, drop reference to matching receive winकरोw */
	अगर (winकरोw->tx_win) अणु
		अगर (winकरोw->user_win) अणु
			/* Drop references to pid and mm */
			put_pid(winकरोw->pid);
			अगर (winकरोw->mm) अणु
				mm_context_हटाओ_vas_winकरोw(winकरोw->mm);
				mmdrop(winकरोw->mm);
			पूर्ण
		पूर्ण
		put_rx_win(winकरोw->rxwin);
	पूर्ण

	vas_winकरोw_मुक्त(winकरोw);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(vas_win_बंद);

/*
 * Return credit क्रम the given winकरोw.
 * Send winकरोws and fault winकरोw uses credit mechanism as follows:
 *
 * Send winकरोws:
 * - The शेष number of credits available क्रम each send winकरोw is
 *   1024. It means 1024 requests can be issued asynchronously at the
 *   same समय. If the credit is not available, that request will be
 *   वापसed with RMA_Busy.
 * - One credit is taken when NX request is issued.
 * - This credit is वापसed after NX processed that request.
 * - If NX encounters translation error, kernel will वापस the
 *   credit on the specअगरic send winकरोw after processing the fault CRB.
 *
 * Fault winकरोw:
 * - The total number credits available is FIFO_SIZE/CRB_SIZE.
 *   Means 4MB/128 in the current implementation. If credit is not
 *   available, RMA_Reject is वापसed.
 * - A credit is taken when NX pastes CRB in fault FIFO.
 * - The kernel with वापस credit on fault winकरोw after पढ़ोing entry
 *   from fault FIFO.
 */
व्योम vas_वापस_credit(काष्ठा vas_winकरोw *winकरोw, bool tx)
अणु
	uपूर्णांक64_t val;

	val = 0ULL;
	अगर (tx) अणु /* send winकरोw */
		val = SET_FIELD(VAS_TX_WCRED, val, 1);
		ग_लिखो_hvwc_reg(winकरोw, VREG(TX_WCRED_ADDER), val);
	पूर्ण अन्यथा अणु
		val = SET_FIELD(VAS_LRX_WCRED, val, 1);
		ग_लिखो_hvwc_reg(winकरोw, VREG(LRX_WCRED_ADDER), val);
	पूर्ण
पूर्ण

काष्ठा vas_winकरोw *vas_pswid_to_winकरोw(काष्ठा vas_instance *vinst,
		uपूर्णांक32_t pswid)
अणु
	काष्ठा vas_winकरोw *winकरोw;
	पूर्णांक winid;

	अगर (!pswid) अणु
		pr_devel("%s: called for pswid 0!\n", __func__);
		वापस ERR_PTR(-ESRCH);
	पूर्ण

	decode_pswid(pswid, शून्य, &winid);

	अगर (winid >= VAS_WINDOWS_PER_CHIP)
		वापस ERR_PTR(-ESRCH);

	/*
	 * If application बंदs the winकरोw beक्रमe the hardware
	 * वापसs the fault CRB, we should रुको in vas_win_बंद()
	 * क्रम the pending requests. so the winकरोw must be active
	 * and the process alive.
	 *
	 * If its a kernel process, we should not get any faults and
	 * should not get here.
	 */
	winकरोw = vinst->winकरोws[winid];

	अगर (!winकरोw) अणु
		pr_err("PSWID decode: Could not find window for winid %d pswid %d vinst 0x%p\n",
			winid, pswid, vinst);
		वापस शून्य;
	पूर्ण

	/*
	 * Do some sanity checks on the decoded winकरोw.  Winकरोw should be
	 * NX GZIP user send winकरोw. FTW winकरोws should not incur faults
	 * since their CRBs are ignored (not queued on FIFO or processed
	 * by NX).
	 */
	अगर (!winकरोw->tx_win || !winकरोw->user_win || !winकरोw->nx_win ||
			winकरोw->cop == VAS_COP_TYPE_FAULT ||
			winकरोw->cop == VAS_COP_TYPE_FTW) अणु
		pr_err("PSWID decode: id %d, tx %d, user %d, nx %d, cop %d\n",
			winid, winकरोw->tx_win, winकरोw->user_win,
			winकरोw->nx_win, winकरोw->cop);
		WARN_ON(1);
	पूर्ण

	वापस winकरोw;
पूर्ण
