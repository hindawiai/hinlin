<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Maximum size of each resync request */
#घोषणा RESYNC_BLOCK_SIZE (64*1024)
#घोषणा RESYNC_PAGES ((RESYNC_BLOCK_SIZE + PAGE_SIZE-1) / PAGE_SIZE)

/*
 * Number of guaranteed raid bios in हाल of extreme VM load:
 */
#घोषणा	NR_RAID_BIOS 256

/* when we get a पढ़ो error on a पढ़ो-only array, we redirect to another
 * device without failing the first device, or trying to over-ग_लिखो to
 * correct the पढ़ो error.  To keep track of bad blocks on a per-bio
 * level, we store IO_BLOCKED in the appropriate 'bios' poपूर्णांकer
 */
#घोषणा IO_BLOCKED ((काष्ठा bio *)1)
/* When we successfully ग_लिखो to a known bad-block, we need to हटाओ the
 * bad-block marking which must be करोne from process context.  So we record
 * the success by setting devs[n].bio to IO_MADE_GOOD
 */
#घोषणा IO_MADE_GOOD ((काष्ठा bio *)2)

#घोषणा BIO_SPECIAL(bio) ((अचिन्हित दीर्घ)bio <= 2)

/* When there are this many requests queue to be written by
 * the raid thपढ़ो, we become 'congested' to provide back-pressure
 * क्रम ग_लिखोback.
 */
अटल पूर्णांक max_queued_requests = 1024;

/* क्रम managing resync I/O pages */
काष्ठा resync_pages अणु
	व्योम		*raid_bio;
	काष्ठा page	*pages[RESYNC_PAGES];
पूर्ण;

अटल व्योम rbio_pool_मुक्त(व्योम *rbio, व्योम *data)
अणु
	kमुक्त(rbio);
पूर्ण

अटल अंतरभूत पूर्णांक resync_alloc_pages(काष्ठा resync_pages *rp,
				     gfp_t gfp_flags)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RESYNC_PAGES; i++) अणु
		rp->pages[i] = alloc_page(gfp_flags);
		अगर (!rp->pages[i])
			जाओ out_मुक्त;
	पूर्ण

	वापस 0;

out_मुक्त:
	जबतक (--i >= 0)
		put_page(rp->pages[i]);
	वापस -ENOMEM;
पूर्ण

अटल अंतरभूत व्योम resync_मुक्त_pages(काष्ठा resync_pages *rp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RESYNC_PAGES; i++)
		put_page(rp->pages[i]);
पूर्ण

अटल अंतरभूत व्योम resync_get_all_pages(काष्ठा resync_pages *rp)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RESYNC_PAGES; i++)
		get_page(rp->pages[i]);
पूर्ण

अटल अंतरभूत काष्ठा page *resync_fetch_page(काष्ठा resync_pages *rp,
					     अचिन्हित idx)
अणु
	अगर (WARN_ON_ONCE(idx >= RESYNC_PAGES))
		वापस शून्य;
	वापस rp->pages[idx];
पूर्ण

/*
 * 'strct resync_pages' stores actual pages used क्रम करोing the resync
 *  IO, and it is per-bio, so make .bi_निजी poपूर्णांकs to it.
 */
अटल अंतरभूत काष्ठा resync_pages *get_resync_pages(काष्ठा bio *bio)
अणु
	वापस bio->bi_निजी;
पूर्ण

/* generally called after bio_reset() क्रम reseting bvec */
अटल व्योम md_bio_reset_resync_pages(काष्ठा bio *bio, काष्ठा resync_pages *rp,
			       पूर्णांक size)
अणु
	पूर्णांक idx = 0;

	/* initialize bvec table again */
	करो अणु
		काष्ठा page *page = resync_fetch_page(rp, idx);
		पूर्णांक len = min_t(पूर्णांक, size, PAGE_SIZE);

		/*
		 * won't fail because the vec table is big
		 * enough to hold all these pages
		 */
		bio_add_page(bio, page, len, 0);
		size -= len;
	पूर्ण जबतक (idx++ < RESYNC_PAGES && size > 0);
पूर्ण
