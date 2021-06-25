<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/ceph/ceph_debug.h>

#समावेश <linux/backing-dev.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/ग_लिखोback.h>	/* generic_ग_लिखोpages */
#समावेश <linux/slab.h>
#समावेश <linux/pagevec.h>
#समावेश <linux/task_io_accounting_ops.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/iversion.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/netfs.h>

#समावेश "super.h"
#समावेश "mds_client.h"
#समावेश "cache.h"
#समावेश "metric.h"
#समावेश <linux/ceph/osd_client.h>
#समावेश <linux/ceph/striper.h>

/*
 * Ceph address space ops.
 *
 * There are a few funny things going on here.
 *
 * The page->निजी field is used to reference a काष्ठा
 * ceph_snap_context क्रम _every_ dirty page.  This indicates which
 * snapshot the page was logically dirtied in, and thus which snap
 * context needs to be associated with the osd ग_लिखो during ग_लिखोback.
 *
 * Similarly, काष्ठा ceph_inode_info मुख्यtains a set of counters to
 * count dirty pages on the inode.  In the असलence of snapshots,
 * i_wrbuffer_ref == i_wrbuffer_ref_head == the dirty page count.
 *
 * When a snapshot is taken (that is, when the client receives
 * notअगरication that a snapshot was taken), each inode with caps and
 * with dirty pages (dirty pages implies there is a cap) माला_लो a new
 * ceph_cap_snap in the i_cap_snaps list (which is sorted in ascending
 * order, new snaps go to the tail).  The i_wrbuffer_ref_head count is
 * moved to capsnap->dirty. (Unless a sync ग_लिखो is currently in
 * progress.  In that हाल, the capsnap is said to be "pending", new
 * ग_लिखोs cannot start, and the capsnap isn't "finalized" until the
 * ग_लिखो completes (or fails) and a final size/mसमय क्रम the inode क्रम
 * that snap can be settled upon.)  i_wrbuffer_ref_head is reset to 0.
 *
 * On ग_लिखोback, we must submit ग_लिखोs to the osd IN SNAP ORDER.  So,
 * we look क्रम the first capsnap in i_cap_snaps and ग_लिखो out pages in
 * that snap context _only_.  Then we move on to the next capsnap,
 * eventually reaching the "live" or "head" context (i.e., pages that
 * are not yet snapped) and are writing the most recently dirtied
 * pages.
 *
 * Invalidate and so क्रमth must take care to ensure the dirty page
 * accounting is preserved.
 */

#घोषणा CONGESTION_ON_THRESH(congestion_kb) (congestion_kb >> (PAGE_SHIFT-10))
#घोषणा CONGESTION_OFF_THRESH(congestion_kb)				\
	(CONGESTION_ON_THRESH(congestion_kb) -				\
	 (CONGESTION_ON_THRESH(congestion_kb) >> 2))

अटल पूर्णांक ceph_netfs_check_ग_लिखो_begin(काष्ठा file *file, loff_t pos, अचिन्हित पूर्णांक len,
					काष्ठा page *page, व्योम **_fsdata);

अटल अंतरभूत काष्ठा ceph_snap_context *page_snap_context(काष्ठा page *page)
अणु
	अगर (PagePrivate(page))
		वापस (व्योम *)page->निजी;
	वापस शून्य;
पूर्ण

/*
 * Dirty a page.  Optimistically adjust accounting, on the assumption
 * that we won't race with invalidate.  If we करो, पढ़ोjust.
 */
अटल पूर्णांक ceph_set_page_dirty(काष्ठा page *page)
अणु
	काष्ठा address_space *mapping = page->mapping;
	काष्ठा inode *inode;
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_snap_context *snapc;
	पूर्णांक ret;

	अगर (unlikely(!mapping))
		वापस !TestSetPageDirty(page);

	अगर (PageDirty(page)) अणु
		करोut("%p set_page_dirty %p idx %lu -- already dirty\n",
		     mapping->host, page, page->index);
		BUG_ON(!PagePrivate(page));
		वापस 0;
	पूर्ण

	inode = mapping->host;
	ci = ceph_inode(inode);

	/* dirty the head */
	spin_lock(&ci->i_ceph_lock);
	BUG_ON(ci->i_wr_ref == 0); // caller should hold Fw reference
	अगर (__ceph_have_pending_cap_snap(ci)) अणु
		काष्ठा ceph_cap_snap *capsnap =
				list_last_entry(&ci->i_cap_snaps,
						काष्ठा ceph_cap_snap,
						ci_item);
		snapc = ceph_get_snap_context(capsnap->context);
		capsnap->dirty_pages++;
	पूर्ण अन्यथा अणु
		BUG_ON(!ci->i_head_snapc);
		snapc = ceph_get_snap_context(ci->i_head_snapc);
		++ci->i_wrbuffer_ref_head;
	पूर्ण
	अगर (ci->i_wrbuffer_ref == 0)
		ihold(inode);
	++ci->i_wrbuffer_ref;
	करोut("%p set_page_dirty %p idx %lu head %d/%d -> %d/%d "
	     "snapc %p seq %lld (%d snaps)\n",
	     mapping->host, page, page->index,
	     ci->i_wrbuffer_ref-1, ci->i_wrbuffer_ref_head-1,
	     ci->i_wrbuffer_ref, ci->i_wrbuffer_ref_head,
	     snapc, snapc->seq, snapc->num_snaps);
	spin_unlock(&ci->i_ceph_lock);

	/*
	 * Reference snap context in page->निजी.  Also set
	 * PagePrivate so that we get invalidatepage callback.
	 */
	BUG_ON(PagePrivate(page));
	attach_page_निजी(page, snapc);

	ret = __set_page_dirty_nobuffers(page);
	WARN_ON(!PageLocked(page));
	WARN_ON(!page->mapping);

	वापस ret;
पूर्ण

/*
 * If we are truncating the full page (i.e. offset == 0), adjust the
 * dirty page counters appropriately.  Only called अगर there is निजी
 * data on the page.
 */
अटल व्योम ceph_invalidatepage(काष्ठा page *page, अचिन्हित पूर्णांक offset,
				अचिन्हित पूर्णांक length)
अणु
	काष्ठा inode *inode;
	काष्ठा ceph_inode_info *ci;
	काष्ठा ceph_snap_context *snapc;

	रुको_on_page_fscache(page);

	inode = page->mapping->host;
	ci = ceph_inode(inode);

	अगर (offset != 0 || length != thp_size(page)) अणु
		करोut("%p invalidatepage %p idx %lu partial dirty page %u~%u\n",
		     inode, page, page->index, offset, length);
		वापस;
	पूर्ण

	WARN_ON(!PageLocked(page));
	अगर (!PagePrivate(page))
		वापस;

	करोut("%p invalidatepage %p idx %lu full dirty page\n",
	     inode, page, page->index);

	snapc = detach_page_निजी(page);
	ceph_put_wrbuffer_cap_refs(ci, 1, snapc);
	ceph_put_snap_context(snapc);
पूर्ण

अटल पूर्णांक ceph_releasepage(काष्ठा page *page, gfp_t gfp)
अणु
	करोut("%p releasepage %p idx %lu (%sdirty)\n", page->mapping->host,
	     page, page->index, PageDirty(page) ? "" : "not ");

	अगर (PageFsCache(page)) अणु
		अगर (!(gfp & __GFP_सूचीECT_RECLAIM) || !(gfp & __GFP_FS))
			वापस 0;
		रुको_on_page_fscache(page);
	पूर्ण
	वापस !PagePrivate(page);
पूर्ण

अटल व्योम ceph_netfs_expand_पढ़ोahead(काष्ठा netfs_पढ़ो_request *rreq)
अणु
	काष्ठा inode *inode = rreq->mapping->host;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_file_layout *lo = &ci->i_layout;
	u32 blockoff;
	u64 blockno;

	/* Expand the start करोwnward */
	blockno = भाग_u64_rem(rreq->start, lo->stripe_unit, &blockoff);
	rreq->start = blockno * lo->stripe_unit;
	rreq->len += blockoff;

	/* Now, round up the length to the next block */
	rreq->len = roundup(rreq->len, lo->stripe_unit);
पूर्ण

अटल bool ceph_netfs_clamp_length(काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	काष्ठा inode *inode = subreq->rreq->mapping->host;
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	u64 objno, objoff;
	u32 xlen;

	/* Truncate the extent at the end of the current block */
	ceph_calc_file_object_mapping(&ci->i_layout, subreq->start, subreq->len,
				      &objno, &objoff, &xlen);
	subreq->len = min(xlen, fsc->mount_options->rsize);
	वापस true;
पूर्ण

अटल व्योम finish_netfs_पढ़ो(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(req->r_inode);
	काष्ठा ceph_osd_data *osd_data = osd_req_op_extent_osd_data(req, 0);
	काष्ठा netfs_पढ़ो_subrequest *subreq = req->r_priv;
	पूर्णांक num_pages;
	पूर्णांक err = req->r_result;

	ceph_update_पढ़ो_metrics(&fsc->mdsc->metric, req->r_start_latency,
				 req->r_end_latency, err);

	करोut("%s: result %d subreq->len=%zu i_size=%lld\n", __func__, req->r_result,
	     subreq->len, i_size_पढ़ो(req->r_inode));

	/* no object means success but no data */
	अगर (err == -ENOENT)
		err = 0;
	अन्यथा अगर (err == -EBLOCKLISTED)
		fsc->blocklisted = true;

	अगर (err >= 0 && err < subreq->len)
		__set_bit(NETFS_SREQ_CLEAR_TAIL, &subreq->flags);

	netfs_subreq_terminated(subreq, err, true);

	num_pages = calc_pages_क्रम(osd_data->alignment, osd_data->length);
	ceph_put_page_vector(osd_data->pages, num_pages, false);
	iput(req->r_inode);
पूर्ण

अटल व्योम ceph_netfs_issue_op(काष्ठा netfs_पढ़ो_subrequest *subreq)
अणु
	काष्ठा netfs_पढ़ो_request *rreq = subreq->rreq;
	काष्ठा inode *inode = rreq->mapping->host;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_osd_request *req;
	काष्ठा ceph_vino vino = ceph_vino(inode);
	काष्ठा iov_iter iter;
	काष्ठा page **pages;
	माप_प्रकार page_off;
	पूर्णांक err = 0;
	u64 len = subreq->len;

	req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout, vino, subreq->start, &len,
			0, 1, CEPH_OSD_OP_READ,
			CEPH_OSD_FLAG_READ | fsc->client->osdc.client->options->पढ़ो_from_replica,
			शून्य, ci->i_truncate_seq, ci->i_truncate_size, false);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		req = शून्य;
		जाओ out;
	पूर्ण

	करोut("%s: pos=%llu orig_len=%zu len=%llu\n", __func__, subreq->start, subreq->len, len);
	iov_iter_xarray(&iter, READ, &rreq->mapping->i_pages, subreq->start, len);
	err = iov_iter_get_pages_alloc(&iter, &pages, len, &page_off);
	अगर (err < 0) अणु
		करोut("%s: iov_ter_get_pages_alloc returned %d\n", __func__, err);
		जाओ out;
	पूर्ण

	/* should always give us a page-aligned पढ़ो */
	WARN_ON_ONCE(page_off);
	len = err;

	osd_req_op_extent_osd_data_pages(req, 0, pages, len, 0, false, false);
	req->r_callback = finish_netfs_पढ़ो;
	req->r_priv = subreq;
	req->r_inode = inode;
	ihold(inode);

	err = ceph_osdc_start_request(req->r_osdc, req, false);
	अगर (err)
		iput(inode);
out:
	ceph_osdc_put_request(req);
	अगर (err)
		netfs_subreq_terminated(subreq, err, false);
	करोut("%s: result %d\n", __func__, err);
पूर्ण

अटल व्योम ceph_init_rreq(काष्ठा netfs_पढ़ो_request *rreq, काष्ठा file *file)
अणु
पूर्ण

अटल व्योम ceph_पढ़ोahead_cleanup(काष्ठा address_space *mapping, व्योम *priv)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	पूर्णांक got = (uपूर्णांकptr_t)priv;

	अगर (got)
		ceph_put_cap_refs(ci, got);
पूर्ण

स्थिर काष्ठा netfs_पढ़ो_request_ops ceph_netfs_पढ़ो_ops = अणु
	.init_rreq		= ceph_init_rreq,
	.is_cache_enabled	= ceph_is_cache_enabled,
	.begin_cache_operation	= ceph_begin_cache_operation,
	.issue_op		= ceph_netfs_issue_op,
	.expand_पढ़ोahead	= ceph_netfs_expand_पढ़ोahead,
	.clamp_length		= ceph_netfs_clamp_length,
	.check_ग_लिखो_begin	= ceph_netfs_check_ग_लिखो_begin,
	.cleanup		= ceph_पढ़ोahead_cleanup,
पूर्ण;

/* पढ़ो a single page, without unlocking it. */
अटल पूर्णांक ceph_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_vino vino = ceph_vino(inode);
	u64 off = page_offset(page);
	u64 len = thp_size(page);

	अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE) अणु
		/*
		 * Uptodate अंतरभूत data should have been added
		 * पूर्णांकo page cache जबतक getting Fcr caps.
		 */
		अगर (off == 0) अणु
			unlock_page(page);
			वापस -EINVAL;
		पूर्ण
		zero_user_segment(page, 0, thp_size(page));
		SetPageUptodate(page);
		unlock_page(page);
		वापस 0;
	पूर्ण

	करोut("readpage ino %llx.%llx file %p off %llu len %llu page %p index %lu\n",
	     vino.ino, vino.snap, file, off, len, page, page->index);

	वापस netfs_पढ़ोpage(file, page, &ceph_netfs_पढ़ो_ops, शून्य);
पूर्ण

अटल व्योम ceph_पढ़ोahead(काष्ठा पढ़ोahead_control *ractl)
अणु
	काष्ठा inode *inode = file_inode(ractl->file);
	काष्ठा ceph_file_info *fi = ractl->file->निजी_data;
	काष्ठा ceph_rw_context *rw_ctx;
	पूर्णांक got = 0;
	पूर्णांक ret = 0;

	अगर (ceph_inode(inode)->i_अंतरभूत_version != CEPH_INLINE_NONE)
		वापस;

	rw_ctx = ceph_find_rw_context(fi);
	अगर (!rw_ctx) अणु
		/*
		 * पढ़ोahead callers करो not necessarily hold Fcb caps
		 * (e.g. fadvise, madvise).
		 */
		पूर्णांक want = CEPH_CAP_खाता_CACHE;

		ret = ceph_try_get_caps(inode, CEPH_CAP_खाता_RD, want, true, &got);
		अगर (ret < 0)
			करोut("start_read %p, error getting cap\n", inode);
		अन्यथा अगर (!(got & want))
			करोut("start_read %p, no cache cap\n", inode);

		अगर (ret <= 0)
			वापस;
	पूर्ण
	netfs_पढ़ोahead(ractl, &ceph_netfs_पढ़ो_ops, (व्योम *)(uपूर्णांकptr_t)got);
पूर्ण

काष्ठा ceph_ग_लिखोback_ctl
अणु
	loff_t i_size;
	u64 truncate_size;
	u32 truncate_seq;
	bool size_stable;
	bool head_snapc;
पूर्ण;

/*
 * Get ref क्रम the oldest snapc क्रम an inode with dirty data... that is, the
 * only snap context we are allowed to ग_लिखो back.
 */
अटल काष्ठा ceph_snap_context *
get_oldest_context(काष्ठा inode *inode, काष्ठा ceph_ग_लिखोback_ctl *ctl,
		   काष्ठा ceph_snap_context *page_snapc)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_snap_context *snapc = शून्य;
	काष्ठा ceph_cap_snap *capsnap = शून्य;

	spin_lock(&ci->i_ceph_lock);
	list_क्रम_each_entry(capsnap, &ci->i_cap_snaps, ci_item) अणु
		करोut(" cap_snap %p snapc %p has %d dirty pages\n", capsnap,
		     capsnap->context, capsnap->dirty_pages);
		अगर (!capsnap->dirty_pages)
			जारी;

		/* get i_size, truncate_अणुseq,sizeपूर्ण क्रम page_snapc? */
		अगर (snapc && capsnap->context != page_snapc)
			जारी;

		अगर (ctl) अणु
			अगर (capsnap->writing) अणु
				ctl->i_size = i_size_पढ़ो(inode);
				ctl->size_stable = false;
			पूर्ण अन्यथा अणु
				ctl->i_size = capsnap->size;
				ctl->size_stable = true;
			पूर्ण
			ctl->truncate_size = capsnap->truncate_size;
			ctl->truncate_seq = capsnap->truncate_seq;
			ctl->head_snapc = false;
		पूर्ण

		अगर (snapc)
			अवरोध;

		snapc = ceph_get_snap_context(capsnap->context);
		अगर (!page_snapc ||
		    page_snapc == snapc ||
		    page_snapc->seq > snapc->seq)
			अवरोध;
	पूर्ण
	अगर (!snapc && ci->i_wrbuffer_ref_head) अणु
		snapc = ceph_get_snap_context(ci->i_head_snapc);
		करोut(" head snapc %p has %d dirty pages\n",
		     snapc, ci->i_wrbuffer_ref_head);
		अगर (ctl) अणु
			ctl->i_size = i_size_पढ़ो(inode);
			ctl->truncate_size = ci->i_truncate_size;
			ctl->truncate_seq = ci->i_truncate_seq;
			ctl->size_stable = false;
			ctl->head_snapc = true;
		पूर्ण
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	वापस snapc;
पूर्ण

अटल u64 get_ग_लिखोpages_data_length(काष्ठा inode *inode,
				      काष्ठा page *page, u64 start)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_snap_context *snapc = page_snap_context(page);
	काष्ठा ceph_cap_snap *capsnap = शून्य;
	u64 end = i_size_पढ़ो(inode);

	अगर (snapc != ci->i_head_snapc) अणु
		bool found = false;
		spin_lock(&ci->i_ceph_lock);
		list_क्रम_each_entry(capsnap, &ci->i_cap_snaps, ci_item) अणु
			अगर (capsnap->context == snapc) अणु
				अगर (!capsnap->writing)
					end = capsnap->size;
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&ci->i_ceph_lock);
		WARN_ON(!found);
	पूर्ण
	अगर (end > page_offset(page) + thp_size(page))
		end = page_offset(page) + thp_size(page);
	वापस end > start ? end - start : 0;
पूर्ण

/*
 * Write a single page, but leave the page locked.
 *
 * If we get a ग_लिखो error, mark the mapping क्रम error, but still adjust the
 * dirty page accounting (i.e., page is no दीर्घer dirty).
 */
अटल पूर्णांक ग_लिखोpage_nounlock(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_snap_context *snapc, *oldest;
	loff_t page_off = page_offset(page);
	पूर्णांक err;
	loff_t len = thp_size(page);
	काष्ठा ceph_ग_लिखोback_ctl ceph_wbc;
	काष्ठा ceph_osd_client *osdc = &fsc->client->osdc;
	काष्ठा ceph_osd_request *req;

	करोut("writepage %p idx %lu\n", page, page->index);

	/* verअगरy this is a ग_लिखोable snap context */
	snapc = page_snap_context(page);
	अगर (!snapc) अणु
		करोut("writepage %p page %p not dirty?\n", inode, page);
		वापस 0;
	पूर्ण
	oldest = get_oldest_context(inode, &ceph_wbc, snapc);
	अगर (snapc->seq > oldest->seq) अणु
		करोut("writepage %p page %p snapc %p not writeable - noop\n",
		     inode, page, snapc);
		/* we should only noop अगर called by kswapd */
		WARN_ON(!(current->flags & PF_MEMALLOC));
		ceph_put_snap_context(oldest);
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		वापस 0;
	पूर्ण
	ceph_put_snap_context(oldest);

	/* is this a partial page at end of file? */
	अगर (page_off >= ceph_wbc.i_size) अणु
		करोut("%p page eof %llu\n", page, ceph_wbc.i_size);
		page->mapping->a_ops->invalidatepage(page, 0, thp_size(page));
		वापस 0;
	पूर्ण

	अगर (ceph_wbc.i_size < page_off + len)
		len = ceph_wbc.i_size - page_off;

	करोut("writepage %p page %p index %lu on %llu~%llu snapc %p seq %lld\n",
	     inode, page, page->index, page_off, len, snapc, snapc->seq);

	अगर (atomic_दीर्घ_inc_वापस(&fsc->ग_लिखोback_count) >
	    CONGESTION_ON_THRESH(fsc->mount_options->congestion_kb))
		set_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);

	set_page_ग_लिखोback(page);
	req = ceph_osdc_new_request(osdc, &ci->i_layout, ceph_vino(inode), page_off, &len, 0, 1,
				    CEPH_OSD_OP_WRITE, CEPH_OSD_FLAG_WRITE, snapc,
				    ceph_wbc.truncate_seq, ceph_wbc.truncate_size,
				    true);
	अगर (IS_ERR(req)) अणु
		redirty_page_क्रम_ग_लिखोpage(wbc, page);
		end_page_ग_लिखोback(page);
		वापस PTR_ERR(req);
	पूर्ण

	/* it may be a लघु ग_लिखो due to an object boundary */
	WARN_ON_ONCE(len > thp_size(page));
	osd_req_op_extent_osd_data_pages(req, 0, &page, len, 0, false, false);
	करोut("writepage %llu~%llu (%llu bytes)\n", page_off, len, len);

	req->r_mसमय = inode->i_mसमय;
	err = ceph_osdc_start_request(osdc, req, true);
	अगर (!err)
		err = ceph_osdc_रुको_request(osdc, req);

	ceph_update_ग_लिखो_metrics(&fsc->mdsc->metric, req->r_start_latency,
				  req->r_end_latency, err);

	ceph_osdc_put_request(req);
	अगर (err == 0)
		err = len;

	अगर (err < 0) अणु
		काष्ठा ग_लिखोback_control पंचांगp_wbc;
		अगर (!wbc)
			wbc = &पंचांगp_wbc;
		अगर (err == -ERESTARTSYS) अणु
			/* समाप्तed by SIGKILL */
			करोut("writepage interrupted page %p\n", page);
			redirty_page_क्रम_ग_लिखोpage(wbc, page);
			end_page_ग_लिखोback(page);
			वापस err;
		पूर्ण
		अगर (err == -EBLOCKLISTED)
			fsc->blocklisted = true;
		करोut("writepage setting page/mapping error %d %p\n",
		     err, page);
		mapping_set_error(&inode->i_data, err);
		wbc->pages_skipped++;
	पूर्ण अन्यथा अणु
		करोut("writepage cleaned page %p\n", page);
		err = 0;  /* vfs expects us to वापस 0 */
	पूर्ण
	oldest = detach_page_निजी(page);
	WARN_ON_ONCE(oldest != snapc);
	end_page_ग_लिखोback(page);
	ceph_put_wrbuffer_cap_refs(ci, 1, snapc);
	ceph_put_snap_context(snapc);  /* page's reference */

	अगर (atomic_दीर्घ_dec_वापस(&fsc->ग_लिखोback_count) <
	    CONGESTION_OFF_THRESH(fsc->mount_options->congestion_kb))
		clear_bdi_congested(inode_to_bdi(inode), BLK_RW_ASYNC);

	वापस err;
पूर्ण

अटल पूर्णांक ceph_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	पूर्णांक err;
	काष्ठा inode *inode = page->mapping->host;
	BUG_ON(!inode);
	ihold(inode);
	err = ग_लिखोpage_nounlock(page, wbc);
	अगर (err == -ERESTARTSYS) अणु
		/* direct memory reclaimer was समाप्तed by SIGKILL. वापस 0
		 * to prevent caller from setting mapping/page error */
		err = 0;
	पूर्ण
	unlock_page(page);
	iput(inode);
	वापस err;
पूर्ण

/*
 * async ग_लिखोback completion handler.
 *
 * If we get an error, set the mapping error bit, but not the inभागidual
 * page error bits.
 */
अटल व्योम ग_लिखोpages_finish(काष्ठा ceph_osd_request *req)
अणु
	काष्ठा inode *inode = req->r_inode;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_osd_data *osd_data;
	काष्ठा page *page;
	पूर्णांक num_pages, total_pages = 0;
	पूर्णांक i, j;
	पूर्णांक rc = req->r_result;
	काष्ठा ceph_snap_context *snapc = req->r_snapc;
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	bool हटाओ_page;

	करोut("writepages_finish %p rc %d\n", inode, rc);
	अगर (rc < 0) अणु
		mapping_set_error(mapping, rc);
		ceph_set_error_ग_लिखो(ci);
		अगर (rc == -EBLOCKLISTED)
			fsc->blocklisted = true;
	पूर्ण अन्यथा अणु
		ceph_clear_error_ग_लिखो(ci);
	पूर्ण

	ceph_update_ग_लिखो_metrics(&fsc->mdsc->metric, req->r_start_latency,
				  req->r_end_latency, rc);

	/*
	 * We lost the cache cap, need to truncate the page beक्रमe
	 * it is unlocked, otherwise we'd truncate it later in the
	 * page truncation thपढ़ो, possibly losing some data that
	 * raced its way in
	 */
	हटाओ_page = !(ceph_caps_issued(ci) &
			(CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO));

	/* clean all pages */
	क्रम (i = 0; i < req->r_num_ops; i++) अणु
		अगर (req->r_ops[i].op != CEPH_OSD_OP_WRITE)
			अवरोध;

		osd_data = osd_req_op_extent_osd_data(req, i);
		BUG_ON(osd_data->type != CEPH_OSD_DATA_TYPE_PAGES);
		num_pages = calc_pages_क्रम((u64)osd_data->alignment,
					   (u64)osd_data->length);
		total_pages += num_pages;
		क्रम (j = 0; j < num_pages; j++) अणु
			page = osd_data->pages[j];
			BUG_ON(!page);
			WARN_ON(!PageUptodate(page));

			अगर (atomic_दीर्घ_dec_वापस(&fsc->ग_लिखोback_count) <
			     CONGESTION_OFF_THRESH(
					fsc->mount_options->congestion_kb))
				clear_bdi_congested(inode_to_bdi(inode),
						    BLK_RW_ASYNC);

			ceph_put_snap_context(detach_page_निजी(page));
			end_page_ग_लिखोback(page);
			करोut("unlocking %p\n", page);

			अगर (हटाओ_page)
				generic_error_हटाओ_page(inode->i_mapping,
							  page);

			unlock_page(page);
		पूर्ण
		करोut("writepages_finish %p wrote %llu bytes cleaned %d pages\n",
		     inode, osd_data->length, rc >= 0 ? num_pages : 0);

		release_pages(osd_data->pages, num_pages);
	पूर्ण

	ceph_put_wrbuffer_cap_refs(ci, total_pages, snapc);

	osd_data = osd_req_op_extent_osd_data(req, 0);
	अगर (osd_data->pages_from_pool)
		mempool_मुक्त(osd_data->pages, ceph_wb_pagevec_pool);
	अन्यथा
		kमुक्त(osd_data->pages);
	ceph_osdc_put_request(req);
पूर्ण

/*
 * initiate async ग_लिखोback
 */
अटल पूर्णांक ceph_ग_लिखोpages_start(काष्ठा address_space *mapping,
				 काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा inode *inode = mapping->host;
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_vino vino = ceph_vino(inode);
	pgoff_t index, start_index, end = -1;
	काष्ठा ceph_snap_context *snapc = शून्य, *last_snapc = शून्य, *pgsnapc;
	काष्ठा pagevec pvec;
	पूर्णांक rc = 0;
	अचिन्हित पूर्णांक wsize = i_blocksize(inode);
	काष्ठा ceph_osd_request *req = शून्य;
	काष्ठा ceph_ग_लिखोback_ctl ceph_wbc;
	bool should_loop, range_whole = false;
	bool करोne = false;

	करोut("writepages_start %p (mode=%s)\n", inode,
	     wbc->sync_mode == WB_SYNC_NONE ? "NONE" :
	     (wbc->sync_mode == WB_SYNC_ALL ? "ALL" : "HOLD"));

	अगर (READ_ONCE(fsc->mount_state) >= CEPH_MOUNT_SHUTDOWN) अणु
		अगर (ci->i_wrbuffer_ref > 0) अणु
			pr_warn_ratelimited(
				"writepage_start %p %lld forced umount\n",
				inode, ceph_ino(inode));
		पूर्ण
		mapping_set_error(mapping, -EIO);
		वापस -EIO; /* we're in a forced umount, don't ग_लिखो! */
	पूर्ण
	अगर (fsc->mount_options->wsize < wsize)
		wsize = fsc->mount_options->wsize;

	pagevec_init(&pvec);

	start_index = wbc->range_cyclic ? mapping->ग_लिखोback_index : 0;
	index = start_index;

retry:
	/* find oldest snap context with dirty data */
	snapc = get_oldest_context(inode, &ceph_wbc, शून्य);
	अगर (!snapc) अणु
		/* hmm, why करोes ग_लिखोpages get called when there
		   is no dirty data? */
		करोut(" no snap context with dirty data?\n");
		जाओ out;
	पूर्ण
	करोut(" oldest snapc is %p seq %lld (%d snaps)\n",
	     snapc, snapc->seq, snapc->num_snaps);

	should_loop = false;
	अगर (ceph_wbc.head_snapc && snapc != last_snapc) अणु
		/* where to start/end? */
		अगर (wbc->range_cyclic) अणु
			index = start_index;
			end = -1;
			अगर (index > 0)
				should_loop = true;
			करोut(" cyclic, start at %lu\n", index);
		पूर्ण अन्यथा अणु
			index = wbc->range_start >> PAGE_SHIFT;
			end = wbc->range_end >> PAGE_SHIFT;
			अगर (wbc->range_start == 0 && wbc->range_end == Lदीर्घ_उच्च)
				range_whole = true;
			करोut(" not cyclic, %lu to %lu\n", index, end);
		पूर्ण
	पूर्ण अन्यथा अगर (!ceph_wbc.head_snapc) अणु
		/* Do not respect wbc->range_अणुstart,endपूर्ण. Dirty pages
		 * in that range can be associated with newer snapc.
		 * They are not ग_लिखोable until we ग_लिखो all dirty pages
		 * associated with 'snapc' get written */
		अगर (index > 0)
			should_loop = true;
		करोut(" non-head snapc, range whole\n");
	पूर्ण

	ceph_put_snap_context(last_snapc);
	last_snapc = snapc;

	जबतक (!करोne && index <= end) अणु
		पूर्णांक num_ops = 0, op_idx;
		अचिन्हित i, pvec_pages, max_pages, locked_pages = 0;
		काष्ठा page **pages = शून्य, **data_pages;
		काष्ठा page *page;
		pgoff_t strip_unit_end = 0;
		u64 offset = 0, len = 0;
		bool from_pool = false;

		max_pages = wsize >> PAGE_SHIFT;

get_more_pages:
		pvec_pages = pagevec_lookup_range_tag(&pvec, mapping, &index,
						end, PAGECACHE_TAG_सूचीTY);
		करोut("pagevec_lookup_range_tag got %d\n", pvec_pages);
		अगर (!pvec_pages && !locked_pages)
			अवरोध;
		क्रम (i = 0; i < pvec_pages && locked_pages < max_pages; i++) अणु
			page = pvec.pages[i];
			करोut("? %p idx %lu\n", page, page->index);
			अगर (locked_pages == 0)
				lock_page(page);  /* first page */
			अन्यथा अगर (!trylock_page(page))
				अवरोध;

			/* only dirty pages, or our accounting अवरोधs */
			अगर (unlikely(!PageDirty(page)) ||
			    unlikely(page->mapping != mapping)) अणु
				करोut("!dirty or !mapping %p\n", page);
				unlock_page(page);
				जारी;
			पूर्ण
			/* only अगर matching snap context */
			pgsnapc = page_snap_context(page);
			अगर (pgsnapc != snapc) अणु
				करोut("page snapc %p %lld != oldest %p %lld\n",
				     pgsnapc, pgsnapc->seq, snapc, snapc->seq);
				अगर (!should_loop &&
				    !ceph_wbc.head_snapc &&
				    wbc->sync_mode != WB_SYNC_NONE)
					should_loop = true;
				unlock_page(page);
				जारी;
			पूर्ण
			अगर (page_offset(page) >= ceph_wbc.i_size) अणु
				करोut("%p page eof %llu\n",
				     page, ceph_wbc.i_size);
				अगर ((ceph_wbc.size_stable ||
				    page_offset(page) >= i_size_पढ़ो(inode)) &&
				    clear_page_dirty_क्रम_io(page))
					mapping->a_ops->invalidatepage(page,
								0, thp_size(page));
				unlock_page(page);
				जारी;
			पूर्ण
			अगर (strip_unit_end && (page->index > strip_unit_end)) अणु
				करोut("end of strip unit %p\n", page);
				unlock_page(page);
				अवरोध;
			पूर्ण
			अगर (PageWriteback(page)) अणु
				अगर (wbc->sync_mode == WB_SYNC_NONE) अणु
					करोut("%p under writeback\n", page);
					unlock_page(page);
					जारी;
				पूर्ण
				करोut("waiting on writeback %p\n", page);
				रुको_on_page_ग_लिखोback(page);
			पूर्ण

			अगर (!clear_page_dirty_क्रम_io(page)) अणु
				करोut("%p !clear_page_dirty_for_io\n", page);
				unlock_page(page);
				जारी;
			पूर्ण

			/*
			 * We have something to ग_लिखो.  If this is
			 * the first locked page this समय through,
			 * calculate max possinle ग_लिखो size and
			 * allocate a page array
			 */
			अगर (locked_pages == 0) अणु
				u64 objnum;
				u64 objoff;
				u32 xlen;

				/* prepare async ग_लिखो request */
				offset = (u64)page_offset(page);
				ceph_calc_file_object_mapping(&ci->i_layout,
							      offset, wsize,
							      &objnum, &objoff,
							      &xlen);
				len = xlen;

				num_ops = 1;
				strip_unit_end = page->index +
					((len - 1) >> PAGE_SHIFT);

				BUG_ON(pages);
				max_pages = calc_pages_क्रम(0, (u64)len);
				pages = kदो_स्मृति_array(max_pages,
						      माप(*pages),
						      GFP_NOFS);
				अगर (!pages) अणु
					from_pool = true;
					pages = mempool_alloc(ceph_wb_pagevec_pool, GFP_NOFS);
					BUG_ON(!pages);
				पूर्ण

				len = 0;
			पूर्ण अन्यथा अगर (page->index !=
				   (offset + len) >> PAGE_SHIFT) अणु
				अगर (num_ops >= (from_pool ?  CEPH_OSD_SLAB_OPS :
							     CEPH_OSD_MAX_OPS)) अणु
					redirty_page_क्रम_ग_लिखोpage(wbc, page);
					unlock_page(page);
					अवरोध;
				पूर्ण

				num_ops++;
				offset = (u64)page_offset(page);
				len = 0;
			पूर्ण

			/* note position of first page in pvec */
			करोut("%p will write page %p idx %lu\n",
			     inode, page, page->index);

			अगर (atomic_दीर्घ_inc_वापस(&fsc->ग_लिखोback_count) >
			    CONGESTION_ON_THRESH(
				    fsc->mount_options->congestion_kb)) अणु
				set_bdi_congested(inode_to_bdi(inode),
						  BLK_RW_ASYNC);
			पूर्ण


			pages[locked_pages++] = page;
			pvec.pages[i] = शून्य;

			len += thp_size(page);
		पूर्ण

		/* did we get anything? */
		अगर (!locked_pages)
			जाओ release_pvec_pages;
		अगर (i) अणु
			अचिन्हित j, n = 0;
			/* shअगरt unused page to beginning of pvec */
			क्रम (j = 0; j < pvec_pages; j++) अणु
				अगर (!pvec.pages[j])
					जारी;
				अगर (n < j)
					pvec.pages[n] = pvec.pages[j];
				n++;
			पूर्ण
			pvec.nr = n;

			अगर (pvec_pages && i == pvec_pages &&
			    locked_pages < max_pages) अणु
				करोut("reached end pvec, trying for more\n");
				pagevec_release(&pvec);
				जाओ get_more_pages;
			पूर्ण
		पूर्ण

new_request:
		offset = page_offset(pages[0]);
		len = wsize;

		req = ceph_osdc_new_request(&fsc->client->osdc,
					&ci->i_layout, vino,
					offset, &len, 0, num_ops,
					CEPH_OSD_OP_WRITE, CEPH_OSD_FLAG_WRITE,
					snapc, ceph_wbc.truncate_seq,
					ceph_wbc.truncate_size, false);
		अगर (IS_ERR(req)) अणु
			req = ceph_osdc_new_request(&fsc->client->osdc,
						&ci->i_layout, vino,
						offset, &len, 0,
						min(num_ops,
						    CEPH_OSD_SLAB_OPS),
						CEPH_OSD_OP_WRITE,
						CEPH_OSD_FLAG_WRITE,
						snapc, ceph_wbc.truncate_seq,
						ceph_wbc.truncate_size, true);
			BUG_ON(IS_ERR(req));
		पूर्ण
		BUG_ON(len < page_offset(pages[locked_pages - 1]) +
			     thp_size(page) - offset);

		req->r_callback = ग_लिखोpages_finish;
		req->r_inode = inode;

		/* Format the osd request message and submit the ग_लिखो */
		len = 0;
		data_pages = pages;
		op_idx = 0;
		क्रम (i = 0; i < locked_pages; i++) अणु
			u64 cur_offset = page_offset(pages[i]);
			अगर (offset + len != cur_offset) अणु
				अगर (op_idx + 1 == req->r_num_ops)
					अवरोध;
				osd_req_op_extent_dup_last(req, op_idx,
							   cur_offset - offset);
				करोut("writepages got pages at %llu~%llu\n",
				     offset, len);
				osd_req_op_extent_osd_data_pages(req, op_idx,
							data_pages, len, 0,
							from_pool, false);
				osd_req_op_extent_update(req, op_idx, len);

				len = 0;
				offset = cur_offset; 
				data_pages = pages + i;
				op_idx++;
			पूर्ण

			set_page_ग_लिखोback(pages[i]);
			len += thp_size(page);
		पूर्ण

		अगर (ceph_wbc.size_stable) अणु
			len = min(len, ceph_wbc.i_size - offset);
		पूर्ण अन्यथा अगर (i == locked_pages) अणु
			/* ग_लिखोpages_finish() clears ग_लिखोback pages
			 * according to the data length, so make sure
			 * data length covers all locked pages */
			u64 min_len = len + 1 - thp_size(page);
			len = get_ग_लिखोpages_data_length(inode, pages[i - 1],
							 offset);
			len = max(len, min_len);
		पूर्ण
		करोut("writepages got pages at %llu~%llu\n", offset, len);

		osd_req_op_extent_osd_data_pages(req, op_idx, data_pages, len,
						 0, from_pool, false);
		osd_req_op_extent_update(req, op_idx, len);

		BUG_ON(op_idx + 1 != req->r_num_ops);

		from_pool = false;
		अगर (i < locked_pages) अणु
			BUG_ON(num_ops <= req->r_num_ops);
			num_ops -= req->r_num_ops;
			locked_pages -= i;

			/* allocate new pages array क्रम next request */
			data_pages = pages;
			pages = kदो_स्मृति_array(locked_pages, माप(*pages),
					      GFP_NOFS);
			अगर (!pages) अणु
				from_pool = true;
				pages = mempool_alloc(ceph_wb_pagevec_pool, GFP_NOFS);
				BUG_ON(!pages);
			पूर्ण
			स_नकल(pages, data_pages + i,
			       locked_pages * माप(*pages));
			स_रखो(data_pages + i, 0,
			       locked_pages * माप(*pages));
		पूर्ण अन्यथा अणु
			BUG_ON(num_ops != req->r_num_ops);
			index = pages[i - 1]->index + 1;
			/* request message now owns the pages array */
			pages = शून्य;
		पूर्ण

		req->r_mसमय = inode->i_mसमय;
		rc = ceph_osdc_start_request(&fsc->client->osdc, req, true);
		BUG_ON(rc);
		req = शून्य;

		wbc->nr_to_ग_लिखो -= i;
		अगर (pages)
			जाओ new_request;

		/*
		 * We stop writing back only अगर we are not करोing
		 * पूर्णांकegrity sync. In हाल of पूर्णांकegrity sync we have to
		 * keep going until we have written all the pages
		 * we tagged क्रम ग_लिखोback prior to entering this loop.
		 */
		अगर (wbc->nr_to_ग_लिखो <= 0 && wbc->sync_mode == WB_SYNC_NONE)
			करोne = true;

release_pvec_pages:
		करोut("pagevec_release on %d pages (%p)\n", (पूर्णांक)pvec.nr,
		     pvec.nr ? pvec.pages[0] : शून्य);
		pagevec_release(&pvec);
	पूर्ण

	अगर (should_loop && !करोne) अणु
		/* more to करो; loop back to beginning of file */
		करोut("writepages looping back to beginning of file\n");
		end = start_index - 1; /* OK even when start_index == 0 */

		/* to ग_लिखो dirty pages associated with next snapc,
		 * we need to रुको until current ग_लिखोs complete */
		अगर (wbc->sync_mode != WB_SYNC_NONE &&
		    start_index == 0 && /* all dirty pages were checked */
		    !ceph_wbc.head_snapc) अणु
			काष्ठा page *page;
			अचिन्हित i, nr;
			index = 0;
			जबतक ((index <= end) &&
			       (nr = pagevec_lookup_tag(&pvec, mapping, &index,
						PAGECACHE_TAG_WRITEBACK))) अणु
				क्रम (i = 0; i < nr; i++) अणु
					page = pvec.pages[i];
					अगर (page_snap_context(page) != snapc)
						जारी;
					रुको_on_page_ग_लिखोback(page);
				पूर्ण
				pagevec_release(&pvec);
				cond_resched();
			पूर्ण
		पूर्ण

		start_index = 0;
		index = 0;
		जाओ retry;
	पूर्ण

	अगर (wbc->range_cyclic || (range_whole && wbc->nr_to_ग_लिखो > 0))
		mapping->ग_लिखोback_index = index;

out:
	ceph_osdc_put_request(req);
	ceph_put_snap_context(last_snapc);
	करोut("writepages dend - startone, rc = %d\n", rc);
	वापस rc;
पूर्ण



/*
 * See अगर a given @snapc is either ग_लिखोable, or alपढ़ोy written.
 */
अटल पूर्णांक context_is_ग_लिखोable_or_written(काष्ठा inode *inode,
					   काष्ठा ceph_snap_context *snapc)
अणु
	काष्ठा ceph_snap_context *oldest = get_oldest_context(inode, शून्य, शून्य);
	पूर्णांक ret = !oldest || snapc->seq <= oldest->seq;

	ceph_put_snap_context(oldest);
	वापस ret;
पूर्ण

/**
 * ceph_find_incompatible - find an incompatible context and वापस it
 * @page: page being dirtied
 *
 * We are only allowed to ग_लिखो पूर्णांकo/dirty a page अगर the page is
 * clean, or alपढ़ोy dirty within the same snap context. Returns a
 * conflicting context अगर there is one, शून्य अगर there isn't, or a
 * negative error code on other errors.
 *
 * Must be called with page lock held.
 */
अटल काष्ठा ceph_snap_context *
ceph_find_incompatible(काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);

	अगर (READ_ONCE(fsc->mount_state) >= CEPH_MOUNT_SHUTDOWN) अणु
		करोut(" page %p forced umount\n", page);
		वापस ERR_PTR(-EIO);
	पूर्ण

	क्रम (;;) अणु
		काष्ठा ceph_snap_context *snapc, *oldest;

		रुको_on_page_ग_लिखोback(page);

		snapc = page_snap_context(page);
		अगर (!snapc || snapc == ci->i_head_snapc)
			अवरोध;

		/*
		 * this page is alपढ़ोy dirty in another (older) snap
		 * context!  is it ग_लिखोable now?
		 */
		oldest = get_oldest_context(inode, शून्य, शून्य);
		अगर (snapc->seq > oldest->seq) अणु
			/* not ग_लिखोable -- वापस it क्रम the caller to deal with */
			ceph_put_snap_context(oldest);
			करोut(" page %p snapc %p not current or oldest\n", page, snapc);
			वापस ceph_get_snap_context(snapc);
		पूर्ण
		ceph_put_snap_context(oldest);

		/* yay, ग_लिखोable, करो it now (without dropping page lock) */
		करोut(" page %p snapc %p not current, but oldest\n", page, snapc);
		अगर (clear_page_dirty_क्रम_io(page)) अणु
			पूर्णांक r = ग_लिखोpage_nounlock(page, शून्य);
			अगर (r < 0)
				वापस ERR_PTR(r);
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक ceph_netfs_check_ग_लिखो_begin(काष्ठा file *file, loff_t pos, अचिन्हित पूर्णांक len,
					काष्ठा page *page, व्योम **_fsdata)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_snap_context *snapc;

	snapc = ceph_find_incompatible(page);
	अगर (snapc) अणु
		पूर्णांक r;

		unlock_page(page);
		put_page(page);
		अगर (IS_ERR(snapc))
			वापस PTR_ERR(snapc);

		ceph_queue_ग_लिखोback(inode);
		r = रुको_event_समाप्तable(ci->i_cap_wq,
					context_is_ग_लिखोable_or_written(inode, snapc));
		ceph_put_snap_context(snapc);
		वापस r == 0 ? -EAGAIN : r;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * We are only allowed to ग_लिखो पूर्णांकo/dirty the page अगर the page is
 * clean, or alपढ़ोy dirty within the same snap context.
 */
अटल पूर्णांक ceph_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			    loff_t pos, अचिन्हित len, अचिन्हित flags,
			    काष्ठा page **pagep, व्योम **fsdata)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा page *page = शून्य;
	pgoff_t index = pos >> PAGE_SHIFT;
	पूर्णांक r;

	/*
	 * Uninlining should have alपढ़ोy been करोne and everything updated, EXCEPT
	 * क्रम अंतरभूत_version sent to the MDS.
	 */
	अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE) अणु
		page = grab_cache_page_ग_लिखो_begin(mapping, index, flags);
		अगर (!page)
			वापस -ENOMEM;

		/*
		 * The अंतरभूत_version on a new inode is set to 1. If that's the
		 * हाल, then the page is bअक्रम new and isn't yet Uptodate.
		 */
		r = 0;
		अगर (index == 0 && ci->i_अंतरभूत_version != 1) अणु
			अगर (!PageUptodate(page)) अणु
				WARN_ONCE(1, "ceph: write_begin called on still-inlined inode (inline_version %llu)!\n",
					  ci->i_अंतरभूत_version);
				r = -EINVAL;
			पूर्ण
			जाओ out;
		पूर्ण
		zero_user_segment(page, 0, thp_size(page));
		SetPageUptodate(page);
		जाओ out;
	पूर्ण

	r = netfs_ग_लिखो_begin(file, inode->i_mapping, pos, len, 0, &page, शून्य,
			      &ceph_netfs_पढ़ो_ops, शून्य);
out:
	अगर (r == 0)
		रुको_on_page_fscache(page);
	अगर (r < 0) अणु
		अगर (page)
			put_page(page);
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(!PageLocked(page));
		*pagep = page;
	पूर्ण
	वापस r;
पूर्ण

/*
 * we करोn't do anything in here that simple_write_end doesn't करो
 * except adjust dirty page accounting
 */
अटल पूर्णांक ceph_ग_लिखो_end(काष्ठा file *file, काष्ठा address_space *mapping,
			  loff_t pos, अचिन्हित len, अचिन्हित copied,
			  काष्ठा page *page, व्योम *fsdata)
अणु
	काष्ठा inode *inode = file_inode(file);
	bool check_cap = false;

	करोut("write_end file %p inode %p page %p %d~%d (%d)\n", file,
	     inode, page, (पूर्णांक)pos, (पूर्णांक)copied, (पूर्णांक)len);

	/* zero the stale part of the page अगर we did a लघु copy */
	अगर (!PageUptodate(page)) अणु
		अगर (copied < len) अणु
			copied = 0;
			जाओ out;
		पूर्ण
		SetPageUptodate(page);
	पूर्ण

	/* did file size increase? */
	अगर (pos+copied > i_size_पढ़ो(inode))
		check_cap = ceph_inode_set_size(inode, pos+copied);

	set_page_dirty(page);

out:
	unlock_page(page);
	put_page(page);

	अगर (check_cap)
		ceph_check_caps(ceph_inode(inode), CHECK_CAPS_AUTHONLY, शून्य);

	वापस copied;
पूर्ण

/*
 * we set .direct_IO to indicate direct io is supported, but since we
 * पूर्णांकercept O_सूचीECT पढ़ोs and ग_लिखोs early, this function should
 * never get called.
 */
अटल sमाप_प्रकार ceph_direct_io(काष्ठा kiocb *iocb, काष्ठा iov_iter *iter)
अणु
	WARN_ON(1);
	वापस -EINVAL;
पूर्ण

स्थिर काष्ठा address_space_operations ceph_aops = अणु
	.पढ़ोpage = ceph_पढ़ोpage,
	.पढ़ोahead = ceph_पढ़ोahead,
	.ग_लिखोpage = ceph_ग_लिखोpage,
	.ग_लिखोpages = ceph_ग_लिखोpages_start,
	.ग_लिखो_begin = ceph_ग_लिखो_begin,
	.ग_लिखो_end = ceph_ग_लिखो_end,
	.set_page_dirty = ceph_set_page_dirty,
	.invalidatepage = ceph_invalidatepage,
	.releasepage = ceph_releasepage,
	.direct_IO = ceph_direct_io,
पूर्ण;

अटल व्योम ceph_block_sigs(sigset_t *oldset)
अणु
	sigset_t mask;
	siginitsetinv(&mask, sigmask(SIGKILL));
	sigprocmask(SIG_BLOCK, &mask, oldset);
पूर्ण

अटल व्योम ceph_restore_sigs(sigset_t *oldset)
अणु
	sigprocmask(SIG_SETMASK, oldset, शून्य);
पूर्ण

/*
 * vm ops
 */
अटल vm_fault_t ceph_filemap_fault(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा inode *inode = file_inode(vma->vm_file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_file_info *fi = vma->vm_file->निजी_data;
	loff_t off = (loff_t)vmf->pgoff << PAGE_SHIFT;
	पूर्णांक want, got, err;
	sigset_t oldset;
	vm_fault_t ret = VM_FAULT_SIGBUS;

	ceph_block_sigs(&oldset);

	करोut("filemap_fault %p %llx.%llx %llu trying to get caps\n",
	     inode, ceph_vinop(inode), off);
	अगर (fi->भ_शेषe & CEPH_खाता_MODE_LAZY)
		want = CEPH_CAP_खाता_CACHE | CEPH_CAP_खाता_LAZYIO;
	अन्यथा
		want = CEPH_CAP_खाता_CACHE;

	got = 0;
	err = ceph_get_caps(vma->vm_file, CEPH_CAP_खाता_RD, want, -1, &got);
	अगर (err < 0)
		जाओ out_restore;

	करोut("filemap_fault %p %llu got cap refs on %s\n",
	     inode, off, ceph_cap_string(got));

	अगर ((got & (CEPH_CAP_खाता_CACHE | CEPH_CAP_खाता_LAZYIO)) ||
	    ci->i_अंतरभूत_version == CEPH_INLINE_NONE) अणु
		CEPH_DEFINE_RW_CONTEXT(rw_ctx, got);
		ceph_add_rw_context(fi, &rw_ctx);
		ret = filemap_fault(vmf);
		ceph_del_rw_context(fi, &rw_ctx);
		करोut("filemap_fault %p %llu drop cap refs %s ret %x\n",
		     inode, off, ceph_cap_string(got), ret);
	पूर्ण अन्यथा
		err = -EAGAIN;

	ceph_put_cap_refs(ci, got);

	अगर (err != -EAGAIN)
		जाओ out_restore;

	/* पढ़ो अंतरभूत data */
	अगर (off >= PAGE_SIZE) अणु
		/* करोes not support अंतरभूत data > PAGE_SIZE */
		ret = VM_FAULT_SIGBUS;
	पूर्ण अन्यथा अणु
		काष्ठा address_space *mapping = inode->i_mapping;
		काष्ठा page *page = find_or_create_page(mapping, 0,
						mapping_gfp_स्थिरraपूर्णांक(mapping,
						~__GFP_FS));
		अगर (!page) अणु
			ret = VM_FAULT_OOM;
			जाओ out_अंतरभूत;
		पूर्ण
		err = __ceph_करो_getattr(inode, page,
					 CEPH_STAT_CAP_INLINE_DATA, true);
		अगर (err < 0 || off >= i_size_पढ़ो(inode)) अणु
			unlock_page(page);
			put_page(page);
			ret = vmf_error(err);
			जाओ out_अंतरभूत;
		पूर्ण
		अगर (err < PAGE_SIZE)
			zero_user_segment(page, err, PAGE_SIZE);
		अन्यथा
			flush_dcache_page(page);
		SetPageUptodate(page);
		vmf->page = page;
		ret = VM_FAULT_MAJOR | VM_FAULT_LOCKED;
out_अंतरभूत:
		करोut("filemap_fault %p %llu read inline data ret %x\n",
		     inode, off, ret);
	पूर्ण
out_restore:
	ceph_restore_sigs(&oldset);
	अगर (err < 0)
		ret = vmf_error(err);

	वापस ret;
पूर्ण

अटल vm_fault_t ceph_page_mkग_लिखो(काष्ठा vm_fault *vmf)
अणु
	काष्ठा vm_area_काष्ठा *vma = vmf->vma;
	काष्ठा inode *inode = file_inode(vma->vm_file);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_file_info *fi = vma->vm_file->निजी_data;
	काष्ठा ceph_cap_flush *pपुनः_स्मृति_cf;
	काष्ठा page *page = vmf->page;
	loff_t off = page_offset(page);
	loff_t size = i_size_पढ़ो(inode);
	माप_प्रकार len;
	पूर्णांक want, got, err;
	sigset_t oldset;
	vm_fault_t ret = VM_FAULT_SIGBUS;

	pपुनः_स्मृति_cf = ceph_alloc_cap_flush();
	अगर (!pपुनः_स्मृति_cf)
		वापस VM_FAULT_OOM;

	sb_start_pagefault(inode->i_sb);
	ceph_block_sigs(&oldset);

	अगर (ci->i_अंतरभूत_version != CEPH_INLINE_NONE) अणु
		काष्ठा page *locked_page = शून्य;
		अगर (off == 0) अणु
			lock_page(page);
			locked_page = page;
		पूर्ण
		err = ceph_unअंतरभूत_data(vma->vm_file, locked_page);
		अगर (locked_page)
			unlock_page(locked_page);
		अगर (err < 0)
			जाओ out_मुक्त;
	पूर्ण

	अगर (off + thp_size(page) <= size)
		len = thp_size(page);
	अन्यथा
		len = offset_in_thp(page, size);

	करोut("page_mkwrite %p %llx.%llx %llu~%zd getting caps i_size %llu\n",
	     inode, ceph_vinop(inode), off, len, size);
	अगर (fi->भ_शेषe & CEPH_खाता_MODE_LAZY)
		want = CEPH_CAP_खाता_BUFFER | CEPH_CAP_खाता_LAZYIO;
	अन्यथा
		want = CEPH_CAP_खाता_BUFFER;

	got = 0;
	err = ceph_get_caps(vma->vm_file, CEPH_CAP_खाता_WR, want, off + len, &got);
	अगर (err < 0)
		जाओ out_मुक्त;

	करोut("page_mkwrite %p %llu~%zd got cap refs on %s\n",
	     inode, off, len, ceph_cap_string(got));

	/* Update समय beक्रमe taking page lock */
	file_update_समय(vma->vm_file);
	inode_inc_iversion_raw(inode);

	करो अणु
		काष्ठा ceph_snap_context *snapc;

		lock_page(page);

		अगर (page_mkग_लिखो_check_truncate(page, inode) < 0) अणु
			unlock_page(page);
			ret = VM_FAULT_NOPAGE;
			अवरोध;
		पूर्ण

		snapc = ceph_find_incompatible(page);
		अगर (!snapc) अणु
			/* success.  we'll keep the page locked. */
			set_page_dirty(page);
			ret = VM_FAULT_LOCKED;
			अवरोध;
		पूर्ण

		unlock_page(page);

		अगर (IS_ERR(snapc)) अणु
			ret = VM_FAULT_SIGBUS;
			अवरोध;
		पूर्ण

		ceph_queue_ग_लिखोback(inode);
		err = रुको_event_समाप्तable(ci->i_cap_wq,
				context_is_ग_लिखोable_or_written(inode, snapc));
		ceph_put_snap_context(snapc);
	पूर्ण जबतक (err == 0);

	अगर (ret == VM_FAULT_LOCKED ||
	    ci->i_अंतरभूत_version != CEPH_INLINE_NONE) अणु
		पूर्णांक dirty;
		spin_lock(&ci->i_ceph_lock);
		ci->i_अंतरभूत_version = CEPH_INLINE_NONE;
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_खाता_WR,
					       &pपुनः_स्मृति_cf);
		spin_unlock(&ci->i_ceph_lock);
		अगर (dirty)
			__mark_inode_dirty(inode, dirty);
	पूर्ण

	करोut("page_mkwrite %p %llu~%zd dropping cap refs on %s ret %x\n",
	     inode, off, len, ceph_cap_string(got), ret);
	ceph_put_cap_refs_async(ci, got);
out_मुक्त:
	ceph_restore_sigs(&oldset);
	sb_end_pagefault(inode->i_sb);
	ceph_मुक्त_cap_flush(pपुनः_स्मृति_cf);
	अगर (err < 0)
		ret = vmf_error(err);
	वापस ret;
पूर्ण

व्योम ceph_fill_अंतरभूत_data(काष्ठा inode *inode, काष्ठा page *locked_page,
			   अक्षर	*data, माप_प्रकार len)
अणु
	काष्ठा address_space *mapping = inode->i_mapping;
	काष्ठा page *page;

	अगर (locked_page) अणु
		page = locked_page;
	पूर्ण अन्यथा अणु
		अगर (i_size_पढ़ो(inode) == 0)
			वापस;
		page = find_or_create_page(mapping, 0,
					   mapping_gfp_स्थिरraपूर्णांक(mapping,
					   ~__GFP_FS));
		अगर (!page)
			वापस;
		अगर (PageUptodate(page)) अणु
			unlock_page(page);
			put_page(page);
			वापस;
		पूर्ण
	पूर्ण

	करोut("fill_inline_data %p %llx.%llx len %zu locked_page %p\n",
	     inode, ceph_vinop(inode), len, locked_page);

	अगर (len > 0) अणु
		व्योम *kaddr = kmap_atomic(page);
		स_नकल(kaddr, data, len);
		kunmap_atomic(kaddr);
	पूर्ण

	अगर (page != locked_page) अणु
		अगर (len < PAGE_SIZE)
			zero_user_segment(page, len, PAGE_SIZE);
		अन्यथा
			flush_dcache_page(page);

		SetPageUptodate(page);
		unlock_page(page);
		put_page(page);
	पूर्ण
पूर्ण

पूर्णांक ceph_unअंतरभूत_data(काष्ठा file *filp, काष्ठा page *locked_page)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(inode);
	काष्ठा ceph_osd_request *req;
	काष्ठा page *page = शून्य;
	u64 len, अंतरभूत_version;
	पूर्णांक err = 0;
	bool from_pagecache = false;

	spin_lock(&ci->i_ceph_lock);
	अंतरभूत_version = ci->i_अंतरभूत_version;
	spin_unlock(&ci->i_ceph_lock);

	करोut("uninline_data %p %llx.%llx inline_version %llu\n",
	     inode, ceph_vinop(inode), अंतरभूत_version);

	अगर (अंतरभूत_version == 1 || /* initial version, no data */
	    अंतरभूत_version == CEPH_INLINE_NONE)
		जाओ out;

	अगर (locked_page) अणु
		page = locked_page;
		WARN_ON(!PageUptodate(page));
	पूर्ण अन्यथा अगर (ceph_caps_issued(ci) &
		   (CEPH_CAP_खाता_CACHE|CEPH_CAP_खाता_LAZYIO)) अणु
		page = find_get_page(inode->i_mapping, 0);
		अगर (page) अणु
			अगर (PageUptodate(page)) अणु
				from_pagecache = true;
				lock_page(page);
			पूर्ण अन्यथा अणु
				put_page(page);
				page = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (page) अणु
		len = i_size_पढ़ो(inode);
		अगर (len > PAGE_SIZE)
			len = PAGE_SIZE;
	पूर्ण अन्यथा अणु
		page = __page_cache_alloc(GFP_NOFS);
		अगर (!page) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
		err = __ceph_करो_getattr(inode, page,
					CEPH_STAT_CAP_INLINE_DATA, true);
		अगर (err < 0) अणु
			/* no अंतरभूत data */
			अगर (err == -ENODATA)
				err = 0;
			जाओ out;
		पूर्ण
		len = err;
	पूर्ण

	req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout,
				    ceph_vino(inode), 0, &len, 0, 1,
				    CEPH_OSD_OP_CREATE, CEPH_OSD_FLAG_WRITE,
				    शून्य, 0, 0, false);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण

	req->r_mसमय = inode->i_mसमय;
	err = ceph_osdc_start_request(&fsc->client->osdc, req, false);
	अगर (!err)
		err = ceph_osdc_रुको_request(&fsc->client->osdc, req);
	ceph_osdc_put_request(req);
	अगर (err < 0)
		जाओ out;

	req = ceph_osdc_new_request(&fsc->client->osdc, &ci->i_layout,
				    ceph_vino(inode), 0, &len, 1, 3,
				    CEPH_OSD_OP_WRITE, CEPH_OSD_FLAG_WRITE,
				    शून्य, ci->i_truncate_seq,
				    ci->i_truncate_size, false);
	अगर (IS_ERR(req)) अणु
		err = PTR_ERR(req);
		जाओ out;
	पूर्ण

	osd_req_op_extent_osd_data_pages(req, 1, &page, len, 0, false, false);

	अणु
		__le64 xattr_buf = cpu_to_le64(अंतरभूत_version);
		err = osd_req_op_xattr_init(req, 0, CEPH_OSD_OP_CMPXATTR,
					    "inline_version", &xattr_buf,
					    माप(xattr_buf),
					    CEPH_OSD_CMPXATTR_OP_GT,
					    CEPH_OSD_CMPXATTR_MODE_U64);
		अगर (err)
			जाओ out_put;
	पूर्ण

	अणु
		अक्षर xattr_buf[32];
		पूर्णांक xattr_len = snम_लिखो(xattr_buf, माप(xattr_buf),
					 "%llu", अंतरभूत_version);
		err = osd_req_op_xattr_init(req, 2, CEPH_OSD_OP_SETXATTR,
					    "inline_version",
					    xattr_buf, xattr_len, 0, 0);
		अगर (err)
			जाओ out_put;
	पूर्ण

	req->r_mसमय = inode->i_mसमय;
	err = ceph_osdc_start_request(&fsc->client->osdc, req, false);
	अगर (!err)
		err = ceph_osdc_रुको_request(&fsc->client->osdc, req);

	ceph_update_ग_लिखो_metrics(&fsc->mdsc->metric, req->r_start_latency,
				  req->r_end_latency, err);

out_put:
	ceph_osdc_put_request(req);
	अगर (err == -ECANCELED)
		err = 0;
out:
	अगर (page && page != locked_page) अणु
		अगर (from_pagecache) अणु
			unlock_page(page);
			put_page(page);
		पूर्ण अन्यथा
			__मुक्त_pages(page, 0);
	पूर्ण

	करोut("uninline_data %p %llx.%llx inline_version %llu = %d\n",
	     inode, ceph_vinop(inode), अंतरभूत_version, err);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा ceph_vmops = अणु
	.fault		= ceph_filemap_fault,
	.page_mkग_लिखो	= ceph_page_mkग_लिखो,
पूर्ण;

पूर्णांक ceph_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा address_space *mapping = file->f_mapping;

	अगर (!mapping->a_ops->पढ़ोpage)
		वापस -ENOEXEC;
	file_accessed(file);
	vma->vm_ops = &ceph_vmops;
	वापस 0;
पूर्ण

क्रमागत अणु
	POOL_READ	= 1,
	POOL_WRITE	= 2,
पूर्ण;

अटल पूर्णांक __ceph_pool_perm_get(काष्ठा ceph_inode_info *ci,
				s64 pool, काष्ठा ceph_string *pool_ns)
अणु
	काष्ठा ceph_fs_client *fsc = ceph_inode_to_client(&ci->vfs_inode);
	काष्ठा ceph_mds_client *mdsc = fsc->mdsc;
	काष्ठा ceph_osd_request *rd_req = शून्य, *wr_req = शून्य;
	काष्ठा rb_node **p, *parent;
	काष्ठा ceph_pool_perm *perm;
	काष्ठा page **pages;
	माप_प्रकार pool_ns_len;
	पूर्णांक err = 0, err2 = 0, have = 0;

	करोwn_पढ़ो(&mdsc->pool_perm_rwsem);
	p = &mdsc->pool_perm_tree.rb_node;
	जबतक (*p) अणु
		perm = rb_entry(*p, काष्ठा ceph_pool_perm, node);
		अगर (pool < perm->pool)
			p = &(*p)->rb_left;
		अन्यथा अगर (pool > perm->pool)
			p = &(*p)->rb_right;
		अन्यथा अणु
			पूर्णांक ret = ceph_compare_string(pool_ns,
						perm->pool_ns,
						perm->pool_ns_len);
			अगर (ret < 0)
				p = &(*p)->rb_left;
			अन्यथा अगर (ret > 0)
				p = &(*p)->rb_right;
			अन्यथा अणु
				have = perm->perm;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	up_पढ़ो(&mdsc->pool_perm_rwsem);
	अगर (*p)
		जाओ out;

	अगर (pool_ns)
		करोut("__ceph_pool_perm_get pool %lld ns %.*s no perm cached\n",
		     pool, (पूर्णांक)pool_ns->len, pool_ns->str);
	अन्यथा
		करोut("__ceph_pool_perm_get pool %lld no perm cached\n", pool);

	करोwn_ग_लिखो(&mdsc->pool_perm_rwsem);
	p = &mdsc->pool_perm_tree.rb_node;
	parent = शून्य;
	जबतक (*p) अणु
		parent = *p;
		perm = rb_entry(parent, काष्ठा ceph_pool_perm, node);
		अगर (pool < perm->pool)
			p = &(*p)->rb_left;
		अन्यथा अगर (pool > perm->pool)
			p = &(*p)->rb_right;
		अन्यथा अणु
			पूर्णांक ret = ceph_compare_string(pool_ns,
						perm->pool_ns,
						perm->pool_ns_len);
			अगर (ret < 0)
				p = &(*p)->rb_left;
			अन्यथा अगर (ret > 0)
				p = &(*p)->rb_right;
			अन्यथा अणु
				have = perm->perm;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (*p) अणु
		up_ग_लिखो(&mdsc->pool_perm_rwsem);
		जाओ out;
	पूर्ण

	rd_req = ceph_osdc_alloc_request(&fsc->client->osdc, शून्य,
					 1, false, GFP_NOFS);
	अगर (!rd_req) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	rd_req->r_flags = CEPH_OSD_FLAG_READ;
	osd_req_op_init(rd_req, 0, CEPH_OSD_OP_STAT, 0);
	rd_req->r_base_oloc.pool = pool;
	अगर (pool_ns)
		rd_req->r_base_oloc.pool_ns = ceph_get_string(pool_ns);
	ceph_oid_म_लिखो(&rd_req->r_base_oid, "%llx.00000000", ci->i_vino.ino);

	err = ceph_osdc_alloc_messages(rd_req, GFP_NOFS);
	अगर (err)
		जाओ out_unlock;

	wr_req = ceph_osdc_alloc_request(&fsc->client->osdc, शून्य,
					 1, false, GFP_NOFS);
	अगर (!wr_req) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	wr_req->r_flags = CEPH_OSD_FLAG_WRITE;
	osd_req_op_init(wr_req, 0, CEPH_OSD_OP_CREATE, CEPH_OSD_OP_FLAG_EXCL);
	ceph_oloc_copy(&wr_req->r_base_oloc, &rd_req->r_base_oloc);
	ceph_oid_copy(&wr_req->r_base_oid, &rd_req->r_base_oid);

	err = ceph_osdc_alloc_messages(wr_req, GFP_NOFS);
	अगर (err)
		जाओ out_unlock;

	/* one page should be large enough क्रम STAT data */
	pages = ceph_alloc_page_vector(1, GFP_KERNEL);
	अगर (IS_ERR(pages)) अणु
		err = PTR_ERR(pages);
		जाओ out_unlock;
	पूर्ण

	osd_req_op_raw_data_in_pages(rd_req, 0, pages, PAGE_SIZE,
				     0, false, true);
	err = ceph_osdc_start_request(&fsc->client->osdc, rd_req, false);

	wr_req->r_mसमय = ci->vfs_inode.i_mसमय;
	err2 = ceph_osdc_start_request(&fsc->client->osdc, wr_req, false);

	अगर (!err)
		err = ceph_osdc_रुको_request(&fsc->client->osdc, rd_req);
	अगर (!err2)
		err2 = ceph_osdc_रुको_request(&fsc->client->osdc, wr_req);

	अगर (err >= 0 || err == -ENOENT)
		have |= POOL_READ;
	अन्यथा अगर (err != -EPERM) अणु
		अगर (err == -EBLOCKLISTED)
			fsc->blocklisted = true;
		जाओ out_unlock;
	पूर्ण

	अगर (err2 == 0 || err2 == -EEXIST)
		have |= POOL_WRITE;
	अन्यथा अगर (err2 != -EPERM) अणु
		अगर (err2 == -EBLOCKLISTED)
			fsc->blocklisted = true;
		err = err2;
		जाओ out_unlock;
	पूर्ण

	pool_ns_len = pool_ns ? pool_ns->len : 0;
	perm = kदो_स्मृति(माप(*perm) + pool_ns_len + 1, GFP_NOFS);
	अगर (!perm) अणु
		err = -ENOMEM;
		जाओ out_unlock;
	पूर्ण

	perm->pool = pool;
	perm->perm = have;
	perm->pool_ns_len = pool_ns_len;
	अगर (pool_ns_len > 0)
		स_नकल(perm->pool_ns, pool_ns->str, pool_ns_len);
	perm->pool_ns[pool_ns_len] = 0;

	rb_link_node(&perm->node, parent, p);
	rb_insert_color(&perm->node, &mdsc->pool_perm_tree);
	err = 0;
out_unlock:
	up_ग_लिखो(&mdsc->pool_perm_rwsem);

	ceph_osdc_put_request(rd_req);
	ceph_osdc_put_request(wr_req);
out:
	अगर (!err)
		err = have;
	अगर (pool_ns)
		करोut("__ceph_pool_perm_get pool %lld ns %.*s result = %d\n",
		     pool, (पूर्णांक)pool_ns->len, pool_ns->str, err);
	अन्यथा
		करोut("__ceph_pool_perm_get pool %lld result = %d\n", pool, err);
	वापस err;
पूर्ण

पूर्णांक ceph_pool_perm_check(काष्ठा inode *inode, पूर्णांक need)
अणु
	काष्ठा ceph_inode_info *ci = ceph_inode(inode);
	काष्ठा ceph_string *pool_ns;
	s64 pool;
	पूर्णांक ret, flags;

	/* Only need to करो this क्रम regular files */
	अगर (!S_ISREG(inode->i_mode))
		वापस 0;

	अगर (ci->i_vino.snap != CEPH_NOSNAP) अणु
		/*
		 * Pool permission check needs to ग_लिखो to the first object.
		 * But क्रम snapshot, head of the first object may have alपढ़ो
		 * been deleted. Skip check to aव्योम creating orphan object.
		 */
		वापस 0;
	पूर्ण

	अगर (ceph_test_mount_opt(ceph_inode_to_client(inode),
				NOPOOLPERM))
		वापस 0;

	spin_lock(&ci->i_ceph_lock);
	flags = ci->i_ceph_flags;
	pool = ci->i_layout.pool_id;
	spin_unlock(&ci->i_ceph_lock);
check:
	अगर (flags & CEPH_I_POOL_PERM) अणु
		अगर ((need & CEPH_CAP_खाता_RD) && !(flags & CEPH_I_POOL_RD)) अणु
			करोut("ceph_pool_perm_check pool %lld no read perm\n",
			     pool);
			वापस -EPERM;
		पूर्ण
		अगर ((need & CEPH_CAP_खाता_WR) && !(flags & CEPH_I_POOL_WR)) अणु
			करोut("ceph_pool_perm_check pool %lld no write perm\n",
			     pool);
			वापस -EPERM;
		पूर्ण
		वापस 0;
	पूर्ण

	pool_ns = ceph_try_get_string(ci->i_layout.pool_ns);
	ret = __ceph_pool_perm_get(ci, pool, pool_ns);
	ceph_put_string(pool_ns);
	अगर (ret < 0)
		वापस ret;

	flags = CEPH_I_POOL_PERM;
	अगर (ret & POOL_READ)
		flags |= CEPH_I_POOL_RD;
	अगर (ret & POOL_WRITE)
		flags |= CEPH_I_POOL_WR;

	spin_lock(&ci->i_ceph_lock);
	अगर (pool == ci->i_layout.pool_id &&
	    pool_ns == rcu_dereference_raw(ci->i_layout.pool_ns)) अणु
		ci->i_ceph_flags |= flags;
        पूर्ण अन्यथा अणु
		pool = ci->i_layout.pool_id;
		flags = ci->i_ceph_flags;
	पूर्ण
	spin_unlock(&ci->i_ceph_lock);
	जाओ check;
पूर्ण

व्योम ceph_pool_perm_destroy(काष्ठा ceph_mds_client *mdsc)
अणु
	काष्ठा ceph_pool_perm *perm;
	काष्ठा rb_node *n;

	जबतक (!RB_EMPTY_ROOT(&mdsc->pool_perm_tree)) अणु
		n = rb_first(&mdsc->pool_perm_tree);
		perm = rb_entry(n, काष्ठा ceph_pool_perm, node);
		rb_erase(n, &mdsc->pool_perm_tree);
		kमुक्त(perm);
	पूर्ण
पूर्ण
