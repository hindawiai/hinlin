<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SN Platक्रमm GRU Driver
 *
 *            Dump GRU State
 *
 *  Copyright (c) 2008 Silicon Graphics, Inc.  All Rights Reserved.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <यंत्र/uv/uv_hub.h>

#समावेश <linux/nospec.h>

#समावेश "gru.h"
#समावेश "grutables.h"
#समावेश "gruhandles.h"
#समावेश "grulib.h"

#घोषणा CCH_LOCK_ATTEMPTS	10

अटल पूर्णांक gru_user_copy_handle(व्योम __user **dp, व्योम *s)
अणु
	अगर (copy_to_user(*dp, s, GRU_HANDLE_BYTES))
		वापस -1;
	*dp += GRU_HANDLE_BYTES;
	वापस 0;
पूर्ण

अटल पूर्णांक gru_dump_context_data(व्योम *grubase,
			काष्ठा gru_context_configuration_handle *cch,
			व्योम __user *ubuf, पूर्णांक ctxnum, पूर्णांक dsrcnt,
			पूर्णांक flush_cbrs)
अणु
	व्योम *cb, *cbe, *tfh, *gseg;
	पूर्णांक i, scr;

	gseg = grubase + ctxnum * GRU_GSEG_STRIDE;
	cb = gseg + GRU_CB_BASE;
	cbe = grubase + GRU_CBE_BASE;
	tfh = grubase + GRU_TFH_BASE;

	क्रम_each_cbr_in_allocation_map(i, &cch->cbr_allocation_map, scr) अणु
		अगर (flush_cbrs)
			gru_flush_cache(cb);
		अगर (gru_user_copy_handle(&ubuf, cb))
			जाओ fail;
		अगर (gru_user_copy_handle(&ubuf, tfh + i * GRU_HANDLE_STRIDE))
			जाओ fail;
		अगर (gru_user_copy_handle(&ubuf, cbe + i * GRU_HANDLE_STRIDE))
			जाओ fail;
		cb += GRU_HANDLE_STRIDE;
	पूर्ण
	अगर (dsrcnt)
		स_नकल(ubuf, gseg + GRU_DS_BASE, dsrcnt * GRU_HANDLE_STRIDE);
	वापस 0;

fail:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक gru_dump_tfm(काष्ठा gru_state *gru,
		व्योम __user *ubuf, व्योम __user *ubufend)
अणु
	काष्ठा gru_tlb_fault_map *tfm;
	पूर्णांक i;

	अगर (GRU_NUM_TFM * GRU_CACHE_LINE_BYTES > ubufend - ubuf)
		वापस -EFBIG;

	क्रम (i = 0; i < GRU_NUM_TFM; i++) अणु
		tfm = get_tfm(gru->gs_gru_base_vaddr, i);
		अगर (gru_user_copy_handle(&ubuf, tfm))
			जाओ fail;
	पूर्ण
	वापस GRU_NUM_TFM * GRU_CACHE_LINE_BYTES;

fail:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक gru_dump_tgh(काष्ठा gru_state *gru,
		व्योम __user *ubuf, व्योम __user *ubufend)
अणु
	काष्ठा gru_tlb_global_handle *tgh;
	पूर्णांक i;

	अगर (GRU_NUM_TGH * GRU_CACHE_LINE_BYTES > ubufend - ubuf)
		वापस -EFBIG;

	क्रम (i = 0; i < GRU_NUM_TGH; i++) अणु
		tgh = get_tgh(gru->gs_gru_base_vaddr, i);
		अगर (gru_user_copy_handle(&ubuf, tgh))
			जाओ fail;
	पूर्ण
	वापस GRU_NUM_TGH * GRU_CACHE_LINE_BYTES;

fail:
	वापस -EFAULT;
पूर्ण

अटल पूर्णांक gru_dump_context(काष्ठा gru_state *gru, पूर्णांक ctxnum,
		व्योम __user *ubuf, व्योम __user *ubufend, अक्षर data_opt,
		अक्षर lock_cch, अक्षर flush_cbrs)
अणु
	काष्ठा gru_dump_context_header hdr;
	काष्ठा gru_dump_context_header __user *uhdr = ubuf;
	काष्ठा gru_context_configuration_handle *cch, *ubufcch;
	काष्ठा gru_thपढ़ो_state *gts;
	पूर्णांक try, cch_locked, cbrcnt = 0, dsrcnt = 0, bytes = 0, ret = 0;
	व्योम *grubase;

	स_रखो(&hdr, 0, माप(hdr));
	grubase = gru->gs_gru_base_vaddr;
	cch = get_cch(grubase, ctxnum);
	क्रम (try = 0; try < CCH_LOCK_ATTEMPTS; try++) अणु
		cch_locked =  trylock_cch_handle(cch);
		अगर (cch_locked)
			अवरोध;
		msleep(1);
	पूर्ण

	ubuf += माप(hdr);
	ubufcch = ubuf;
	अगर (gru_user_copy_handle(&ubuf, cch)) अणु
		अगर (cch_locked)
			unlock_cch_handle(cch);
		वापस -EFAULT;
	पूर्ण
	अगर (cch_locked)
		ubufcch->delresp = 0;
	bytes = माप(hdr) + GRU_CACHE_LINE_BYTES;

	अगर (cch_locked || !lock_cch) अणु
		gts = gru->gs_gts[ctxnum];
		अगर (gts && gts->ts_vma) अणु
			hdr.pid = gts->ts_tgid_owner;
			hdr.vaddr = gts->ts_vma->vm_start;
		पूर्ण
		अगर (cch->state != CCHSTATE_INACTIVE) अणु
			cbrcnt = hweight64(cch->cbr_allocation_map) *
						GRU_CBR_AU_SIZE;
			dsrcnt = data_opt ? hweight32(cch->dsr_allocation_map) *
						GRU_DSR_AU_CL : 0;
		पूर्ण
		bytes += (3 * cbrcnt + dsrcnt) * GRU_CACHE_LINE_BYTES;
		अगर (bytes > ubufend - ubuf)
			ret = -EFBIG;
		अन्यथा
			ret = gru_dump_context_data(grubase, cch, ubuf, ctxnum,
							dsrcnt, flush_cbrs);
	पूर्ण
	अगर (cch_locked)
		unlock_cch_handle(cch);
	अगर (ret)
		वापस ret;

	hdr.magic = GRU_DUMP_MAGIC;
	hdr.gid = gru->gs_gid;
	hdr.ctxnum = ctxnum;
	hdr.cbrcnt = cbrcnt;
	hdr.dsrcnt = dsrcnt;
	hdr.cch_locked = cch_locked;
	अगर (copy_to_user(uhdr, &hdr, माप(hdr)))
		वापस -EFAULT;

	वापस bytes;
पूर्ण

पूर्णांक gru_dump_chiplet_request(अचिन्हित दीर्घ arg)
अणु
	काष्ठा gru_state *gru;
	काष्ठा gru_dump_chiplet_state_req req;
	व्योम __user *ubuf;
	व्योम __user *ubufend;
	पूर्णांक ctxnum, ret, cnt = 0;

	अगर (copy_from_user(&req, (व्योम __user *)arg, माप(req)))
		वापस -EFAULT;

	/* Currently, only dump by gid is implemented */
	अगर (req.gid >= gru_max_gids)
		वापस -EINVAL;
	req.gid = array_index_nospec(req.gid, gru_max_gids);

	gru = GID_TO_GRU(req.gid);
	ubuf = req.buf;
	ubufend = req.buf + req.buflen;

	ret = gru_dump_tfm(gru, ubuf, ubufend);
	अगर (ret < 0)
		जाओ fail;
	ubuf += ret;

	ret = gru_dump_tgh(gru, ubuf, ubufend);
	अगर (ret < 0)
		जाओ fail;
	ubuf += ret;

	क्रम (ctxnum = 0; ctxnum < GRU_NUM_CCH; ctxnum++) अणु
		अगर (req.ctxnum == ctxnum || req.ctxnum < 0) अणु
			ret = gru_dump_context(gru, ctxnum, ubuf, ubufend,
						req.data_opt, req.lock_cch,
						req.flush_cbrs);
			अगर (ret < 0)
				जाओ fail;
			ubuf += ret;
			cnt++;
		पूर्ण
	पूर्ण

	अगर (copy_to_user((व्योम __user *)arg, &req, माप(req)))
		वापस -EFAULT;
	वापस cnt;

fail:
	वापस ret;
पूर्ण
