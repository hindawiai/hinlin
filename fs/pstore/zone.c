<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Provide a pstore पूर्णांकermediate backend, organized पूर्णांकo kernel memory
 * allocated zones that are then mapped and flushed पूर्णांकo a single
 * contiguous region on a storage backend of some kind (block, mtd, etc).
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mount.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/fs.h>
#समावेश <linux/pstore_zone.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/device.h>
#समावेश <linux/namei.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/uपन.स>
#समावेश <linux/ग_लिखोback.h>
#समावेश "internal.h"

/**
 * काष्ठा psz_buffer - header of zone to flush to storage
 *
 * @sig: signature to indicate header (PSZ_SIG xor PSZONE-type value)
 * @datalen: length of data in @data
 * @start: offset पूर्णांकo @data where the beginning of the stored bytes begin
 * @data: zone data.
 */
काष्ठा psz_buffer अणु
#घोषणा PSZ_SIG (0x43474244) /* DBGC */
	uपूर्णांक32_t sig;
	atomic_t datalen;
	atomic_t start;
	uपूर्णांक8_t data[];
पूर्ण;

/**
 * काष्ठा psz_kmsg_header - kmsg dump-specअगरic header to flush to storage
 *
 * @magic: magic num क्रम kmsg dump header
 * @समय: kmsg dump trigger समय
 * @compressed: whether conpressed
 * @counter: kmsg dump counter
 * @reason: the kmsg dump reason (e.g. oops, panic, etc)
 * @data: poपूर्णांकer to log data
 *
 * This is a sub-header क्रम a kmsg dump, trailing after &psz_buffer.
 */
काष्ठा psz_kmsg_header अणु
#घोषणा PSTORE_KMSG_HEADER_MAGIC 0x4dfc3ae5 /* Just a अक्रमom number */
	uपूर्णांक32_t magic;
	काष्ठा बारpec64 समय;
	bool compressed;
	uपूर्णांक32_t counter;
	क्रमागत kmsg_dump_reason reason;
	uपूर्णांक8_t data[];
पूर्ण;

/**
 * काष्ठा pstore_zone - single stored buffer
 *
 * @off: zone offset of storage
 * @type: front-end type क्रम this zone
 * @name: front-end name क्रम this zone
 * @buffer: poपूर्णांकer to data buffer managed by this zone
 * @oldbuf: poपूर्णांकer to old data buffer
 * @buffer_size: bytes in @buffer->data
 * @should_recover: whether this zone should recover from storage
 * @dirty: whether the data in @buffer dirty
 *
 * zone काष्ठाure in memory.
 */
काष्ठा pstore_zone अणु
	loff_t off;
	स्थिर अक्षर *name;
	क्रमागत pstore_type_id type;

	काष्ठा psz_buffer *buffer;
	काष्ठा psz_buffer *oldbuf;
	माप_प्रकार buffer_size;
	bool should_recover;
	atomic_t dirty;
पूर्ण;

/**
 * काष्ठा psz_context - all about running state of pstore/zone
 *
 * @kpszs: kmsg dump storage zones
 * @ppsz: pmsg storage zone
 * @cpsz: console storage zone
 * @fpszs: ftrace storage zones
 * @kmsg_max_cnt: max count of @kpszs
 * @kmsg_पढ़ो_cnt: counter of total पढ़ो kmsg dumps
 * @kmsg_ग_लिखो_cnt: counter of total kmsg dump ग_लिखोs
 * @pmsg_पढ़ो_cnt: counter of total पढ़ो pmsg zone
 * @console_पढ़ो_cnt: counter of total पढ़ो console zone
 * @ftrace_max_cnt: max count of @fpszs
 * @ftrace_पढ़ो_cnt: counter of max पढ़ो ftrace zone
 * @oops_counter: counter of oops dumps
 * @panic_counter: counter of panic dumps
 * @recovered: whether finished recovering data from storage
 * @on_panic: whether panic is happening
 * @pstore_zone_info_lock: lock to @pstore_zone_info
 * @pstore_zone_info: inक्रमmation from backend
 * @pstore: काष्ठाure क्रम pstore
 */
काष्ठा psz_context अणु
	काष्ठा pstore_zone **kpszs;
	काष्ठा pstore_zone *ppsz;
	काष्ठा pstore_zone *cpsz;
	काष्ठा pstore_zone **fpszs;
	अचिन्हित पूर्णांक kmsg_max_cnt;
	अचिन्हित पूर्णांक kmsg_पढ़ो_cnt;
	अचिन्हित पूर्णांक kmsg_ग_लिखो_cnt;
	अचिन्हित पूर्णांक pmsg_पढ़ो_cnt;
	अचिन्हित पूर्णांक console_पढ़ो_cnt;
	अचिन्हित पूर्णांक ftrace_max_cnt;
	अचिन्हित पूर्णांक ftrace_पढ़ो_cnt;
	/*
	 * These counters should be calculated during recovery.
	 * It records the oops/panic बार after crashes rather than boots.
	 */
	अचिन्हित पूर्णांक oops_counter;
	अचिन्हित पूर्णांक panic_counter;
	atomic_t recovered;
	atomic_t on_panic;

	/*
	 * pstore_zone_info_lock protects this entire काष्ठाure during calls
	 * to रेजिस्टर_pstore_zone()/unरेजिस्टर_pstore_zone().
	 */
	काष्ठा mutex pstore_zone_info_lock;
	काष्ठा pstore_zone_info *pstore_zone_info;
	काष्ठा pstore_info pstore;
पूर्ण;
अटल काष्ठा psz_context pstore_zone_cxt;

अटल व्योम psz_flush_all_dirty_zones(काष्ठा work_काष्ठा *);
अटल DECLARE_DELAYED_WORK(psz_cleaner, psz_flush_all_dirty_zones);

/**
 * क्रमागत psz_flush_mode - flush mode क्रम psz_zone_ग_लिखो()
 *
 * @FLUSH_NONE: करो not flush to storage but update data on memory
 * @FLUSH_PART: just flush part of data including meta data to storage
 * @FLUSH_META: just flush meta data of zone to storage
 * @FLUSH_ALL: flush all of zone
 */
क्रमागत psz_flush_mode अणु
	FLUSH_NONE = 0,
	FLUSH_PART,
	FLUSH_META,
	FLUSH_ALL,
पूर्ण;

अटल अंतरभूत पूर्णांक buffer_datalen(काष्ठा pstore_zone *zone)
अणु
	वापस atomic_पढ़ो(&zone->buffer->datalen);
पूर्ण

अटल अंतरभूत पूर्णांक buffer_start(काष्ठा pstore_zone *zone)
अणु
	वापस atomic_पढ़ो(&zone->buffer->start);
पूर्ण

अटल अंतरभूत bool is_on_panic(व्योम)
अणु
	वापस atomic_पढ़ो(&pstore_zone_cxt.on_panic);
पूर्ण

अटल sमाप_प्रकार psz_zone_पढ़ो_buffer(काष्ठा pstore_zone *zone, अक्षर *buf,
		माप_प्रकार len, अचिन्हित दीर्घ off)
अणु
	अगर (!buf || !zone || !zone->buffer)
		वापस -EINVAL;
	अगर (off > zone->buffer_size)
		वापस -EINVAL;
	len = min_t(माप_प्रकार, len, zone->buffer_size - off);
	स_नकल(buf, zone->buffer->data + off, len);
	वापस len;
पूर्ण

अटल पूर्णांक psz_zone_पढ़ो_oldbuf(काष्ठा pstore_zone *zone, अक्षर *buf,
		माप_प्रकार len, अचिन्हित दीर्घ off)
अणु
	अगर (!buf || !zone || !zone->oldbuf)
		वापस -EINVAL;
	अगर (off > zone->buffer_size)
		वापस -EINVAL;
	len = min_t(माप_प्रकार, len, zone->buffer_size - off);
	स_नकल(buf, zone->oldbuf->data + off, len);
	वापस 0;
पूर्ण

अटल पूर्णांक psz_zone_ग_लिखो(काष्ठा pstore_zone *zone,
		क्रमागत psz_flush_mode flush_mode, स्थिर अक्षर *buf,
		माप_प्रकार len, अचिन्हित दीर्घ off)
अणु
	काष्ठा pstore_zone_info *info = pstore_zone_cxt.pstore_zone_info;
	sमाप_प्रकार wcnt = 0;
	sमाप_प्रकार (*ग_लिखोop)(स्थिर अक्षर *buf, माप_प्रकार bytes, loff_t pos);
	माप_प्रकार wlen;

	अगर (off > zone->buffer_size)
		वापस -EINVAL;

	wlen = min_t(माप_प्रकार, len, zone->buffer_size - off);
	अगर (buf && wlen) अणु
		स_नकल(zone->buffer->data + off, buf, wlen);
		atomic_set(&zone->buffer->datalen, wlen + off);
	पूर्ण

	/* aव्योम to damage old records */
	अगर (!is_on_panic() && !atomic_पढ़ो(&pstore_zone_cxt.recovered))
		जाओ dirty;

	ग_लिखोop = is_on_panic() ? info->panic_ग_लिखो : info->ग_लिखो;
	अगर (!ग_लिखोop)
		जाओ dirty;

	चयन (flush_mode) अणु
	हाल FLUSH_NONE:
		अगर (unlikely(buf && wlen))
			जाओ dirty;
		वापस 0;
	हाल FLUSH_PART:
		wcnt = ग_लिखोop((स्थिर अक्षर *)zone->buffer->data + off, wlen,
				zone->off + माप(*zone->buffer) + off);
		अगर (wcnt != wlen)
			जाओ dirty;
		fallthrough;
	हाल FLUSH_META:
		wlen = माप(काष्ठा psz_buffer);
		wcnt = ग_लिखोop((स्थिर अक्षर *)zone->buffer, wlen, zone->off);
		अगर (wcnt != wlen)
			जाओ dirty;
		अवरोध;
	हाल FLUSH_ALL:
		wlen = zone->buffer_size + माप(*zone->buffer);
		wcnt = ग_लिखोop((स्थिर अक्षर *)zone->buffer, wlen, zone->off);
		अगर (wcnt != wlen)
			जाओ dirty;
		अवरोध;
	पूर्ण

	वापस 0;
dirty:
	/* no need to mark dirty अगर going to try next zone */
	अगर (wcnt == -ENOMSG)
		वापस -ENOMSG;
	atomic_set(&zone->dirty, true);
	/* flush dirty zones nicely */
	अगर (wcnt == -EBUSY && !is_on_panic())
		schedule_delayed_work(&psz_cleaner, msecs_to_jअगरfies(500));
	वापस -EBUSY;
पूर्ण

अटल पूर्णांक psz_flush_dirty_zone(काष्ठा pstore_zone *zone)
अणु
	पूर्णांक ret;

	अगर (unlikely(!zone))
		वापस -EINVAL;

	अगर (unlikely(!atomic_पढ़ो(&pstore_zone_cxt.recovered)))
		वापस -EBUSY;

	अगर (!atomic_xchg(&zone->dirty, false))
		वापस 0;

	ret = psz_zone_ग_लिखो(zone, FLUSH_ALL, शून्य, 0, 0);
	अगर (ret)
		atomic_set(&zone->dirty, true);
	वापस ret;
पूर्ण

अटल पूर्णांक psz_flush_dirty_zones(काष्ठा pstore_zone **zones, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक i, ret;
	काष्ठा pstore_zone *zone;

	अगर (!zones)
		वापस -EINVAL;

	क्रम (i = 0; i < cnt; i++) अणु
		zone = zones[i];
		अगर (!zone)
			वापस -EINVAL;
		ret = psz_flush_dirty_zone(zone);
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक psz_move_zone(काष्ठा pstore_zone *old, काष्ठा pstore_zone *new)
अणु
	स्थिर अक्षर *data = (स्थिर अक्षर *)old->buffer->data;
	पूर्णांक ret;

	ret = psz_zone_ग_लिखो(new, FLUSH_ALL, data, buffer_datalen(old), 0);
	अगर (ret) अणु
		atomic_set(&new->buffer->datalen, 0);
		atomic_set(&new->dirty, false);
		वापस ret;
	पूर्ण
	atomic_set(&old->buffer->datalen, 0);
	वापस 0;
पूर्ण

अटल व्योम psz_flush_all_dirty_zones(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा psz_context *cxt = &pstore_zone_cxt;
	पूर्णांक ret = 0;

	अगर (cxt->ppsz)
		ret |= psz_flush_dirty_zone(cxt->ppsz);
	अगर (cxt->cpsz)
		ret |= psz_flush_dirty_zone(cxt->cpsz);
	अगर (cxt->kpszs)
		ret |= psz_flush_dirty_zones(cxt->kpszs, cxt->kmsg_max_cnt);
	अगर (cxt->fpszs)
		ret |= psz_flush_dirty_zones(cxt->fpszs, cxt->ftrace_max_cnt);
	अगर (ret && cxt->pstore_zone_info)
		schedule_delayed_work(&psz_cleaner, msecs_to_jअगरfies(1000));
पूर्ण

अटल पूर्णांक psz_kmsg_recover_data(काष्ठा psz_context *cxt)
अणु
	काष्ठा pstore_zone_info *info = cxt->pstore_zone_info;
	काष्ठा pstore_zone *zone = शून्य;
	काष्ठा psz_buffer *buf;
	अचिन्हित दीर्घ i;
	sमाप_प्रकार rcnt;

	अगर (!info->पढ़ो)
		वापस -EINVAL;

	क्रम (i = 0; i < cxt->kmsg_max_cnt; i++) अणु
		zone = cxt->kpszs[i];
		अगर (unlikely(!zone))
			वापस -EINVAL;
		अगर (atomic_पढ़ो(&zone->dirty)) अणु
			अचिन्हित पूर्णांक wcnt = cxt->kmsg_ग_लिखो_cnt;
			काष्ठा pstore_zone *new = cxt->kpszs[wcnt];
			पूर्णांक ret;

			ret = psz_move_zone(zone, new);
			अगर (ret) अणु
				pr_err("move zone from %lu to %d failed\n",
						i, wcnt);
				वापस ret;
			पूर्ण
			cxt->kmsg_ग_लिखो_cnt = (wcnt + 1) % cxt->kmsg_max_cnt;
		पूर्ण
		अगर (!zone->should_recover)
			जारी;
		buf = zone->buffer;
		rcnt = info->पढ़ो((अक्षर *)buf, zone->buffer_size + माप(*buf),
				zone->off);
		अगर (rcnt != zone->buffer_size + माप(*buf))
			वापस (पूर्णांक)rcnt < 0 ? (पूर्णांक)rcnt : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक psz_kmsg_recover_meta(काष्ठा psz_context *cxt)
अणु
	काष्ठा pstore_zone_info *info = cxt->pstore_zone_info;
	काष्ठा pstore_zone *zone;
	माप_प्रकार rcnt, len;
	काष्ठा psz_buffer *buf;
	काष्ठा psz_kmsg_header *hdr;
	काष्ठा बारpec64 समय = अणु पूर्ण;
	अचिन्हित दीर्घ i;
	/*
	 * Recover may on panic, we can't allocate any memory by kदो_स्मृति.
	 * So, we use local array instead.
	 */
	अक्षर buffer_header[माप(*buf) + माप(*hdr)] = अणु0पूर्ण;

	अगर (!info->पढ़ो)
		वापस -EINVAL;

	len = माप(*buf) + माप(*hdr);
	buf = (काष्ठा psz_buffer *)buffer_header;
	क्रम (i = 0; i < cxt->kmsg_max_cnt; i++) अणु
		zone = cxt->kpszs[i];
		अगर (unlikely(!zone))
			वापस -EINVAL;

		rcnt = info->पढ़ो((अक्षर *)buf, len, zone->off);
		अगर (rcnt == -ENOMSG) अणु
			pr_debug("%s with id %lu may be broken, skip\n",
					zone->name, i);
			जारी;
		पूर्ण अन्यथा अगर (rcnt != len) अणु
			pr_err("read %s with id %lu failed\n", zone->name, i);
			वापस (पूर्णांक)rcnt < 0 ? (पूर्णांक)rcnt : -EIO;
		पूर्ण

		अगर (buf->sig != zone->buffer->sig) अणु
			pr_debug("no valid data in kmsg dump zone %lu\n", i);
			जारी;
		पूर्ण

		अगर (zone->buffer_size < atomic_पढ़ो(&buf->datalen)) अणु
			pr_info("found overtop zone: %s: id %lu, off %lld, size %zu\n",
					zone->name, i, zone->off,
					zone->buffer_size);
			जारी;
		पूर्ण

		hdr = (काष्ठा psz_kmsg_header *)buf->data;
		अगर (hdr->magic != PSTORE_KMSG_HEADER_MAGIC) अणु
			pr_info("found invalid zone: %s: id %lu, off %lld, size %zu\n",
					zone->name, i, zone->off,
					zone->buffer_size);
			जारी;
		पूर्ण

		/*
		 * we get the newest zone, and the next one must be the oldest
		 * or unused zone, because we करो ग_लिखो one by one like a circle.
		 */
		अगर (hdr->समय.tv_sec >= समय.tv_sec) अणु
			समय.tv_sec = hdr->समय.tv_sec;
			cxt->kmsg_ग_लिखो_cnt = (i + 1) % cxt->kmsg_max_cnt;
		पूर्ण

		अगर (hdr->reason == KMSG_DUMP_OOPS)
			cxt->oops_counter =
				max(cxt->oops_counter, hdr->counter);
		अन्यथा अगर (hdr->reason == KMSG_DUMP_PANIC)
			cxt->panic_counter =
				max(cxt->panic_counter, hdr->counter);

		अगर (!atomic_पढ़ो(&buf->datalen)) अणु
			pr_debug("found erased zone: %s: id %lu, off %lld, size %zu, datalen %d\n",
					zone->name, i, zone->off,
					zone->buffer_size,
					atomic_पढ़ो(&buf->datalen));
			जारी;
		पूर्ण

		अगर (!is_on_panic())
			zone->should_recover = true;
		pr_debug("found nice zone: %s: id %lu, off %lld, size %zu, datalen %d\n",
				zone->name, i, zone->off,
				zone->buffer_size, atomic_पढ़ो(&buf->datalen));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक psz_kmsg_recover(काष्ठा psz_context *cxt)
अणु
	पूर्णांक ret;

	अगर (!cxt->kpszs)
		वापस 0;

	ret = psz_kmsg_recover_meta(cxt);
	अगर (ret)
		जाओ recover_fail;

	ret = psz_kmsg_recover_data(cxt);
	अगर (ret)
		जाओ recover_fail;

	वापस 0;
recover_fail:
	pr_debug("psz_recover_kmsg failed\n");
	वापस ret;
पूर्ण

अटल पूर्णांक psz_recover_zone(काष्ठा psz_context *cxt, काष्ठा pstore_zone *zone)
अणु
	काष्ठा pstore_zone_info *info = cxt->pstore_zone_info;
	काष्ठा psz_buffer *oldbuf, पंचांगpbuf;
	पूर्णांक ret = 0;
	अक्षर *buf;
	sमाप_प्रकार rcnt, len, start, off;

	अगर (!zone || zone->oldbuf)
		वापस 0;

	अगर (is_on_panic()) अणु
		/* save data as much as possible */
		psz_flush_dirty_zone(zone);
		वापस 0;
	पूर्ण

	अगर (unlikely(!info->पढ़ो))
		वापस -EINVAL;

	len = माप(काष्ठा psz_buffer);
	rcnt = info->पढ़ो((अक्षर *)&पंचांगpbuf, len, zone->off);
	अगर (rcnt != len) अणु
		pr_debug("read zone %s failed\n", zone->name);
		वापस (पूर्णांक)rcnt < 0 ? (पूर्णांक)rcnt : -EIO;
	पूर्ण

	अगर (पंचांगpbuf.sig != zone->buffer->sig) अणु
		pr_debug("no valid data in zone %s\n", zone->name);
		वापस 0;
	पूर्ण

	अगर (zone->buffer_size < atomic_पढ़ो(&पंचांगpbuf.datalen) ||
		zone->buffer_size < atomic_पढ़ो(&पंचांगpbuf.start)) अणु
		pr_info("found overtop zone: %s: off %lld, size %zu\n",
				zone->name, zone->off, zone->buffer_size);
		/* just keep going */
		वापस 0;
	पूर्ण

	अगर (!atomic_पढ़ो(&पंचांगpbuf.datalen)) अणु
		pr_debug("found erased zone: %s: off %lld, size %zu, datalen %d\n",
				zone->name, zone->off, zone->buffer_size,
				atomic_पढ़ो(&पंचांगpbuf.datalen));
		वापस 0;
	पूर्ण

	pr_debug("found nice zone: %s: off %lld, size %zu, datalen %d\n",
			zone->name, zone->off, zone->buffer_size,
			atomic_पढ़ो(&पंचांगpbuf.datalen));

	len = atomic_पढ़ो(&पंचांगpbuf.datalen) + माप(*oldbuf);
	oldbuf = kzalloc(len, GFP_KERNEL);
	अगर (!oldbuf)
		वापस -ENOMEM;

	स_नकल(oldbuf, &पंचांगpbuf, माप(*oldbuf));
	buf = (अक्षर *)oldbuf + माप(*oldbuf);
	len = atomic_पढ़ो(&oldbuf->datalen);
	start = atomic_पढ़ो(&oldbuf->start);
	off = zone->off + माप(*oldbuf);

	/* get part of data */
	rcnt = info->पढ़ो(buf, len - start, off + start);
	अगर (rcnt != len - start) अणु
		pr_err("read zone %s failed\n", zone->name);
		ret = (पूर्णांक)rcnt < 0 ? (पूर्णांक)rcnt : -EIO;
		जाओ मुक्त_oldbuf;
	पूर्ण

	/* get the rest of data */
	rcnt = info->पढ़ो(buf + len - start, start, off);
	अगर (rcnt != start) अणु
		pr_err("read zone %s failed\n", zone->name);
		ret = (पूर्णांक)rcnt < 0 ? (पूर्णांक)rcnt : -EIO;
		जाओ मुक्त_oldbuf;
	पूर्ण

	zone->oldbuf = oldbuf;
	psz_flush_dirty_zone(zone);
	वापस 0;

मुक्त_oldbuf:
	kमुक्त(oldbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक psz_recover_zones(काष्ठा psz_context *cxt,
		काष्ठा pstore_zone **zones, अचिन्हित पूर्णांक cnt)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;
	काष्ठा pstore_zone *zone;

	अगर (!zones)
		वापस 0;

	क्रम (i = 0; i < cnt; i++) अणु
		zone = zones[i];
		अगर (unlikely(!zone))
			जारी;
		ret = psz_recover_zone(cxt, zone);
		अगर (ret)
			जाओ recover_fail;
	पूर्ण

	वापस 0;
recover_fail:
	pr_debug("recover %s[%u] failed\n", zone->name, i);
	वापस ret;
पूर्ण

/**
 * psz_recovery() - recover data from storage
 * @cxt: the context of pstore/zone
 *
 * recovery means पढ़ोing data back from storage after rebooting
 *
 * Return: 0 on success, others on failure.
 */
अटल अंतरभूत पूर्णांक psz_recovery(काष्ठा psz_context *cxt)
अणु
	पूर्णांक ret;

	अगर (atomic_पढ़ो(&cxt->recovered))
		वापस 0;

	ret = psz_kmsg_recover(cxt);
	अगर (ret)
		जाओ out;

	ret = psz_recover_zone(cxt, cxt->ppsz);
	अगर (ret)
		जाओ out;

	ret = psz_recover_zone(cxt, cxt->cpsz);
	अगर (ret)
		जाओ out;

	ret = psz_recover_zones(cxt, cxt->fpszs, cxt->ftrace_max_cnt);

out:
	अगर (unlikely(ret))
		pr_err("recover failed\n");
	अन्यथा अणु
		pr_debug("recover end!\n");
		atomic_set(&cxt->recovered, 1);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक psz_pstore_खोलो(काष्ठा pstore_info *psi)
अणु
	काष्ठा psz_context *cxt = psi->data;

	cxt->kmsg_पढ़ो_cnt = 0;
	cxt->pmsg_पढ़ो_cnt = 0;
	cxt->console_पढ़ो_cnt = 0;
	cxt->ftrace_पढ़ो_cnt = 0;
	वापस 0;
पूर्ण

अटल अंतरभूत bool psz_old_ok(काष्ठा pstore_zone *zone)
अणु
	अगर (zone && zone->oldbuf && atomic_पढ़ो(&zone->oldbuf->datalen))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत bool psz_ok(काष्ठा pstore_zone *zone)
अणु
	अगर (zone && zone->buffer && buffer_datalen(zone))
		वापस true;
	वापस false;
पूर्ण

अटल अंतरभूत पूर्णांक psz_kmsg_erase(काष्ठा psz_context *cxt,
		काष्ठा pstore_zone *zone, काष्ठा pstore_record *record)
अणु
	काष्ठा psz_buffer *buffer = zone->buffer;
	काष्ठा psz_kmsg_header *hdr =
		(काष्ठा psz_kmsg_header *)buffer->data;
	माप_प्रकार size;

	अगर (unlikely(!psz_ok(zone)))
		वापस 0;

	/* this zone is alपढ़ोy updated, no need to erase */
	अगर (record->count != hdr->counter)
		वापस 0;

	size = buffer_datalen(zone) + माप(*zone->buffer);
	atomic_set(&zone->buffer->datalen, 0);
	अगर (cxt->pstore_zone_info->erase)
		वापस cxt->pstore_zone_info->erase(size, zone->off);
	अन्यथा
		वापस psz_zone_ग_लिखो(zone, FLUSH_META, शून्य, 0, 0);
पूर्ण

अटल अंतरभूत पूर्णांक psz_record_erase(काष्ठा psz_context *cxt,
		काष्ठा pstore_zone *zone)
अणु
	अगर (unlikely(!psz_old_ok(zone)))
		वापस 0;

	kमुक्त(zone->oldbuf);
	zone->oldbuf = शून्य;
	/*
	 * अगर there are new data in zone buffer, that means the old data
	 * are alपढ़ोy invalid. It is no need to flush 0 (erase) to
	 * block device.
	 */
	अगर (!buffer_datalen(zone))
		वापस psz_zone_ग_लिखो(zone, FLUSH_META, शून्य, 0, 0);
	psz_flush_dirty_zone(zone);
	वापस 0;
पूर्ण

अटल पूर्णांक psz_pstore_erase(काष्ठा pstore_record *record)
अणु
	काष्ठा psz_context *cxt = record->psi->data;

	चयन (record->type) अणु
	हाल PSTORE_TYPE_DMESG:
		अगर (record->id >= cxt->kmsg_max_cnt)
			वापस -EINVAL;
		वापस psz_kmsg_erase(cxt, cxt->kpszs[record->id], record);
	हाल PSTORE_TYPE_PMSG:
		वापस psz_record_erase(cxt, cxt->ppsz);
	हाल PSTORE_TYPE_CONSOLE:
		वापस psz_record_erase(cxt, cxt->cpsz);
	हाल PSTORE_TYPE_FTRACE:
		अगर (record->id >= cxt->ftrace_max_cnt)
			वापस -EINVAL;
		वापस psz_record_erase(cxt, cxt->fpszs[record->id]);
	शेष: वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम psz_ग_लिखो_kmsg_hdr(काष्ठा pstore_zone *zone,
		काष्ठा pstore_record *record)
अणु
	काष्ठा psz_context *cxt = record->psi->data;
	काष्ठा psz_buffer *buffer = zone->buffer;
	काष्ठा psz_kmsg_header *hdr =
		(काष्ठा psz_kmsg_header *)buffer->data;

	hdr->magic = PSTORE_KMSG_HEADER_MAGIC;
	hdr->compressed = record->compressed;
	hdr->समय.tv_sec = record->समय.tv_sec;
	hdr->समय.tv_nsec = record->समय.tv_nsec;
	hdr->reason = record->reason;
	अगर (hdr->reason == KMSG_DUMP_OOPS)
		hdr->counter = ++cxt->oops_counter;
	अन्यथा अगर (hdr->reason == KMSG_DUMP_PANIC)
		hdr->counter = ++cxt->panic_counter;
	अन्यथा
		hdr->counter = 0;
पूर्ण

/*
 * In हाल zone is broken, which may occur to MTD device, we try each zones,
 * start at cxt->kmsg_ग_लिखो_cnt.
 */
अटल अंतरभूत पूर्णांक notrace psz_kmsg_ग_लिखो_record(काष्ठा psz_context *cxt,
		काष्ठा pstore_record *record)
अणु
	माप_प्रकार size, hlen;
	काष्ठा pstore_zone *zone;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < cxt->kmsg_max_cnt; i++) अणु
		अचिन्हित पूर्णांक zonक्रमागत, len;
		पूर्णांक ret;

		zonक्रमागत = (cxt->kmsg_ग_लिखो_cnt + i) % cxt->kmsg_max_cnt;
		zone = cxt->kpszs[zonक्रमागत];
		अगर (unlikely(!zone))
			वापस -ENOSPC;

		/* aव्योम destroying old data, allocate a new one */
		len = zone->buffer_size + माप(*zone->buffer);
		zone->oldbuf = zone->buffer;
		zone->buffer = kzalloc(len, GFP_KERNEL);
		अगर (!zone->buffer) अणु
			zone->buffer = zone->oldbuf;
			वापस -ENOMEM;
		पूर्ण
		zone->buffer->sig = zone->oldbuf->sig;

		pr_debug("write %s to zone id %d\n", zone->name, zonक्रमागत);
		psz_ग_लिखो_kmsg_hdr(zone, record);
		hlen = माप(काष्ठा psz_kmsg_header);
		size = min_t(माप_प्रकार, record->size, zone->buffer_size - hlen);
		ret = psz_zone_ग_लिखो(zone, FLUSH_ALL, record->buf, size, hlen);
		अगर (likely(!ret || ret != -ENOMSG)) अणु
			cxt->kmsg_ग_लिखो_cnt = zonक्रमागत + 1;
			cxt->kmsg_ग_लिखो_cnt %= cxt->kmsg_max_cnt;
			/* no need to try next zone, मुक्त last zone buffer */
			kमुक्त(zone->oldbuf);
			zone->oldbuf = शून्य;
			वापस ret;
		पूर्ण

		pr_debug("zone %u may be broken, try next dmesg zone\n",
				zonक्रमागत);
		kमुक्त(zone->buffer);
		zone->buffer = zone->oldbuf;
		zone->oldbuf = शून्य;
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल पूर्णांक notrace psz_kmsg_ग_लिखो(काष्ठा psz_context *cxt,
		काष्ठा pstore_record *record)
अणु
	पूर्णांक ret;

	/*
	 * Explicitly only take the first part of any new crash.
	 * If our buffer is larger than kmsg_bytes, this can never happen,
	 * and अगर our buffer is smaller than kmsg_bytes, we करोn't want the
	 * report split across multiple records.
	 */
	अगर (record->part != 1)
		वापस -ENOSPC;

	अगर (!cxt->kpszs)
		वापस -ENOSPC;

	ret = psz_kmsg_ग_लिखो_record(cxt, record);
	अगर (!ret && is_on_panic()) अणु
		/* ensure all data are flushed to storage when panic */
		pr_debug("try to flush other dirty zones\n");
		psz_flush_all_dirty_zones(शून्य);
	पूर्ण

	/* always वापस 0 as we had handled it on buffer */
	वापस 0;
पूर्ण

अटल पूर्णांक notrace psz_record_ग_लिखो(काष्ठा pstore_zone *zone,
		काष्ठा pstore_record *record)
अणु
	माप_प्रकार start, rem;
	bool is_full_data = false;
	अक्षर *buf;
	पूर्णांक cnt;

	अगर (!zone || !record)
		वापस -ENOSPC;

	अगर (atomic_पढ़ो(&zone->buffer->datalen) >= zone->buffer_size)
		is_full_data = true;

	cnt = record->size;
	buf = record->buf;
	अगर (unlikely(cnt > zone->buffer_size)) अणु
		buf += cnt - zone->buffer_size;
		cnt = zone->buffer_size;
	पूर्ण

	start = buffer_start(zone);
	rem = zone->buffer_size - start;
	अगर (unlikely(rem < cnt)) अणु
		psz_zone_ग_लिखो(zone, FLUSH_PART, buf, rem, start);
		buf += rem;
		cnt -= rem;
		start = 0;
		is_full_data = true;
	पूर्ण

	atomic_set(&zone->buffer->start, cnt + start);
	psz_zone_ग_लिखो(zone, FLUSH_PART, buf, cnt, start);

	/**
	 * psz_zone_ग_लिखो will set datalen as start + cnt.
	 * It work अगर actual data length lesser than buffer size.
	 * If data length greater than buffer size, pmsg will reग_लिखो to
	 * beginning of zone, which make buffer->datalen wrongly.
	 * So we should reset datalen as buffer size once actual data length
	 * greater than buffer size.
	 */
	अगर (is_full_data) अणु
		atomic_set(&zone->buffer->datalen, zone->buffer_size);
		psz_zone_ग_लिखो(zone, FLUSH_META, शून्य, 0, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक notrace psz_pstore_ग_लिखो(काष्ठा pstore_record *record)
अणु
	काष्ठा psz_context *cxt = record->psi->data;

	अगर (record->type == PSTORE_TYPE_DMESG &&
			record->reason == KMSG_DUMP_PANIC)
		atomic_set(&cxt->on_panic, 1);

	/*
	 * अगर on panic, करो not ग_लिखो except panic records
	 * Fix हाल that panic_ग_लिखो prपूर्णांकs log which wakes up console backend.
	 */
	अगर (is_on_panic() && record->type != PSTORE_TYPE_DMESG)
		वापस -EBUSY;

	चयन (record->type) अणु
	हाल PSTORE_TYPE_DMESG:
		वापस psz_kmsg_ग_लिखो(cxt, record);
	हाल PSTORE_TYPE_CONSOLE:
		वापस psz_record_ग_लिखो(cxt->cpsz, record);
	हाल PSTORE_TYPE_PMSG:
		वापस psz_record_ग_लिखो(cxt->ppsz, record);
	हाल PSTORE_TYPE_FTRACE: अणु
		पूर्णांक zonक्रमागत = smp_processor_id();

		अगर (!cxt->fpszs)
			वापस -ENOSPC;
		वापस psz_record_ग_लिखो(cxt->fpszs[zonक्रमागत], record);
	पूर्ण
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल काष्ठा pstore_zone *psz_पढ़ो_next_zone(काष्ठा psz_context *cxt)
अणु
	काष्ठा pstore_zone *zone = शून्य;

	जबतक (cxt->kmsg_पढ़ो_cnt < cxt->kmsg_max_cnt) अणु
		zone = cxt->kpszs[cxt->kmsg_पढ़ो_cnt++];
		अगर (psz_ok(zone))
			वापस zone;
	पूर्ण

	अगर (cxt->ftrace_पढ़ो_cnt < cxt->ftrace_max_cnt)
		/*
		 * No need psz_old_ok(). Let psz_ftrace_पढ़ो() करो so क्रम
		 * combination. psz_ftrace_पढ़ो() should traverse over
		 * all zones in हाल of some zone without data.
		 */
		वापस cxt->fpszs[cxt->ftrace_पढ़ो_cnt++];

	अगर (cxt->pmsg_पढ़ो_cnt == 0) अणु
		cxt->pmsg_पढ़ो_cnt++;
		zone = cxt->ppsz;
		अगर (psz_old_ok(zone))
			वापस zone;
	पूर्ण

	अगर (cxt->console_पढ़ो_cnt == 0) अणु
		cxt->console_पढ़ो_cnt++;
		zone = cxt->cpsz;
		अगर (psz_old_ok(zone))
			वापस zone;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक psz_kmsg_पढ़ो_hdr(काष्ठा pstore_zone *zone,
		काष्ठा pstore_record *record)
अणु
	काष्ठा psz_buffer *buffer = zone->buffer;
	काष्ठा psz_kmsg_header *hdr =
		(काष्ठा psz_kmsg_header *)buffer->data;

	अगर (hdr->magic != PSTORE_KMSG_HEADER_MAGIC)
		वापस -EINVAL;
	record->compressed = hdr->compressed;
	record->समय.tv_sec = hdr->समय.tv_sec;
	record->समय.tv_nsec = hdr->समय.tv_nsec;
	record->reason = hdr->reason;
	record->count = hdr->counter;
	वापस 0;
पूर्ण

अटल sमाप_प्रकार psz_kmsg_पढ़ो(काष्ठा pstore_zone *zone,
		काष्ठा pstore_record *record)
अणु
	sमाप_प्रकार size, hlen = 0;

	size = buffer_datalen(zone);
	/* Clear and skip this kmsg dump record अगर it has no valid header */
	अगर (psz_kmsg_पढ़ो_hdr(zone, record)) अणु
		atomic_set(&zone->buffer->datalen, 0);
		atomic_set(&zone->dirty, 0);
		वापस -ENOMSG;
	पूर्ण
	size -= माप(काष्ठा psz_kmsg_header);

	अगर (!record->compressed) अणु
		अक्षर *buf = kaप्र_लिखो(GFP_KERNEL, "%s: Total %d times\n",
				      kmsg_dump_reason_str(record->reason),
				      record->count);
		hlen = म_माप(buf);
		record->buf = kपुनः_स्मृति(buf, hlen + size, GFP_KERNEL);
		अगर (!record->buf) अणु
			kमुक्त(buf);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण अन्यथा अणु
		record->buf = kदो_स्मृति(size, GFP_KERNEL);
		अगर (!record->buf)
			वापस -ENOMEM;
	पूर्ण

	size = psz_zone_पढ़ो_buffer(zone, record->buf + hlen, size,
			माप(काष्ठा psz_kmsg_header));
	अगर (unlikely(size < 0)) अणु
		kमुक्त(record->buf);
		वापस -ENOMSG;
	पूर्ण

	वापस size + hlen;
पूर्ण

/* try to combine all ftrace zones */
अटल sमाप_प्रकार psz_ftrace_पढ़ो(काष्ठा pstore_zone *zone,
		काष्ठा pstore_record *record)
अणु
	काष्ठा psz_context *cxt;
	काष्ठा psz_buffer *buf;
	पूर्णांक ret;

	अगर (!zone || !record)
		वापस -ENOSPC;

	अगर (!psz_old_ok(zone))
		जाओ out;

	buf = (काष्ठा psz_buffer *)zone->oldbuf;
	अगर (!buf)
		वापस -ENOMSG;

	ret = pstore_ftrace_combine_log(&record->buf, &record->size,
			(अक्षर *)buf->data, atomic_पढ़ो(&buf->datalen));
	अगर (unlikely(ret))
		वापस ret;

out:
	cxt = record->psi->data;
	अगर (cxt->ftrace_पढ़ो_cnt < cxt->ftrace_max_cnt)
		/* then, पढ़ो next ftrace zone */
		वापस -ENOMSG;
	record->id = 0;
	वापस record->size ? record->size : -ENOMSG;
पूर्ण

अटल sमाप_प्रकार psz_record_पढ़ो(काष्ठा pstore_zone *zone,
		काष्ठा pstore_record *record)
अणु
	माप_प्रकार len;
	काष्ठा psz_buffer *buf;

	अगर (!zone || !record)
		वापस -ENOSPC;

	buf = (काष्ठा psz_buffer *)zone->oldbuf;
	अगर (!buf)
		वापस -ENOMSG;

	len = atomic_पढ़ो(&buf->datalen);
	record->buf = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!record->buf)
		वापस -ENOMEM;

	अगर (unlikely(psz_zone_पढ़ो_oldbuf(zone, record->buf, len, 0))) अणु
		kमुक्त(record->buf);
		वापस -ENOMSG;
	पूर्ण

	वापस len;
पूर्ण

अटल sमाप_प्रकार psz_pstore_पढ़ो(काष्ठा pstore_record *record)
अणु
	काष्ठा psz_context *cxt = record->psi->data;
	sमाप_प्रकार (*पढ़ोop)(काष्ठा pstore_zone *zone,
			काष्ठा pstore_record *record);
	काष्ठा pstore_zone *zone;
	sमाप_प्रकार ret;

	/* beक्रमe पढ़ो, we must recover from storage */
	ret = psz_recovery(cxt);
	अगर (ret)
		वापस ret;

next_zone:
	zone = psz_पढ़ो_next_zone(cxt);
	अगर (!zone)
		वापस 0;

	record->type = zone->type;
	चयन (record->type) अणु
	हाल PSTORE_TYPE_DMESG:
		पढ़ोop = psz_kmsg_पढ़ो;
		record->id = cxt->kmsg_पढ़ो_cnt - 1;
		अवरोध;
	हाल PSTORE_TYPE_FTRACE:
		पढ़ोop = psz_ftrace_पढ़ो;
		अवरोध;
	हाल PSTORE_TYPE_CONSOLE:
	हाल PSTORE_TYPE_PMSG:
		पढ़ोop = psz_record_पढ़ो;
		अवरोध;
	शेष:
		जाओ next_zone;
	पूर्ण

	ret = पढ़ोop(zone, record);
	अगर (ret == -ENOMSG)
		जाओ next_zone;
	वापस ret;
पूर्ण

अटल काष्ठा psz_context pstore_zone_cxt = अणु
	.pstore_zone_info_lock =
		__MUTEX_INITIALIZER(pstore_zone_cxt.pstore_zone_info_lock),
	.recovered = ATOMIC_INIT(0),
	.on_panic = ATOMIC_INIT(0),
	.pstore = अणु
		.owner = THIS_MODULE,
		.खोलो = psz_pstore_खोलो,
		.पढ़ो = psz_pstore_पढ़ो,
		.ग_लिखो = psz_pstore_ग_लिखो,
		.erase = psz_pstore_erase,
	पूर्ण,
पूर्ण;

अटल व्योम psz_मुक्त_zone(काष्ठा pstore_zone **pszone)
अणु
	काष्ठा pstore_zone *zone = *pszone;

	अगर (!zone)
		वापस;

	kमुक्त(zone->buffer);
	kमुक्त(zone);
	*pszone = शून्य;
पूर्ण

अटल व्योम psz_मुक्त_zones(काष्ठा pstore_zone ***pszones, अचिन्हित पूर्णांक *cnt)
अणु
	काष्ठा pstore_zone **zones = *pszones;

	अगर (!zones)
		वापस;

	जबतक (*cnt > 0) अणु
		(*cnt)--;
		psz_मुक्त_zone(&(zones[*cnt]));
	पूर्ण
	kमुक्त(zones);
	*pszones = शून्य;
पूर्ण

अटल व्योम psz_मुक्त_all_zones(काष्ठा psz_context *cxt)
अणु
	अगर (cxt->kpszs)
		psz_मुक्त_zones(&cxt->kpszs, &cxt->kmsg_max_cnt);
	अगर (cxt->ppsz)
		psz_मुक्त_zone(&cxt->ppsz);
	अगर (cxt->cpsz)
		psz_मुक्त_zone(&cxt->cpsz);
	अगर (cxt->fpszs)
		psz_मुक्त_zones(&cxt->fpszs, &cxt->ftrace_max_cnt);
पूर्ण

अटल काष्ठा pstore_zone *psz_init_zone(क्रमागत pstore_type_id type,
		loff_t *off, माप_प्रकार size)
अणु
	काष्ठा pstore_zone_info *info = pstore_zone_cxt.pstore_zone_info;
	काष्ठा pstore_zone *zone;
	स्थिर अक्षर *name = pstore_type_to_name(type);

	अगर (!size)
		वापस शून्य;

	अगर (*off + size > info->total_size) अणु
		pr_err("no room for %s (0x%zx@0x%llx over 0x%lx)\n",
			name, size, *off, info->total_size);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	zone = kzalloc(माप(काष्ठा pstore_zone), GFP_KERNEL);
	अगर (!zone)
		वापस ERR_PTR(-ENOMEM);

	zone->buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!zone->buffer) अणु
		kमुक्त(zone);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	स_रखो(zone->buffer, 0xFF, size);
	zone->off = *off;
	zone->name = name;
	zone->type = type;
	zone->buffer_size = size - माप(काष्ठा psz_buffer);
	zone->buffer->sig = type ^ PSZ_SIG;
	zone->oldbuf = शून्य;
	atomic_set(&zone->dirty, 0);
	atomic_set(&zone->buffer->datalen, 0);
	atomic_set(&zone->buffer->start, 0);

	*off += size;

	pr_debug("pszone %s: off 0x%llx, %zu header, %zu data\n", zone->name,
			zone->off, माप(*zone->buffer), zone->buffer_size);
	वापस zone;
पूर्ण

अटल काष्ठा pstore_zone **psz_init_zones(क्रमागत pstore_type_id type,
	loff_t *off, माप_प्रकार total_size, sमाप_प्रकार record_size,
	अचिन्हित पूर्णांक *cnt)
अणु
	काष्ठा pstore_zone_info *info = pstore_zone_cxt.pstore_zone_info;
	काष्ठा pstore_zone **zones, *zone;
	स्थिर अक्षर *name = pstore_type_to_name(type);
	पूर्णांक c, i;

	*cnt = 0;
	अगर (!total_size || !record_size)
		वापस शून्य;

	अगर (*off + total_size > info->total_size) अणु
		pr_err("no room for zones %s (0x%zx@0x%llx over 0x%lx)\n",
			name, total_size, *off, info->total_size);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	c = total_size / record_size;
	zones = kसुस्मृति(c, माप(*zones), GFP_KERNEL);
	अगर (!zones) अणु
		pr_err("allocate for zones %s failed\n", name);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	स_रखो(zones, 0, c * माप(*zones));

	क्रम (i = 0; i < c; i++) अणु
		zone = psz_init_zone(type, off, record_size);
		अगर (!zone || IS_ERR(zone)) अणु
			pr_err("initialize zones %s failed\n", name);
			psz_मुक्त_zones(&zones, &i);
			वापस (व्योम *)zone;
		पूर्ण
		zones[i] = zone;
	पूर्ण

	*cnt = c;
	वापस zones;
पूर्ण

अटल पूर्णांक psz_alloc_zones(काष्ठा psz_context *cxt)
अणु
	काष्ठा pstore_zone_info *info = cxt->pstore_zone_info;
	loff_t off = 0;
	पूर्णांक err;
	माप_प्रकार off_size = 0;

	off_size += info->pmsg_size;
	cxt->ppsz = psz_init_zone(PSTORE_TYPE_PMSG, &off, info->pmsg_size);
	अगर (IS_ERR(cxt->ppsz)) अणु
		err = PTR_ERR(cxt->ppsz);
		cxt->ppsz = शून्य;
		जाओ मुक्त_out;
	पूर्ण

	off_size += info->console_size;
	cxt->cpsz = psz_init_zone(PSTORE_TYPE_CONSOLE, &off,
			info->console_size);
	अगर (IS_ERR(cxt->cpsz)) अणु
		err = PTR_ERR(cxt->cpsz);
		cxt->cpsz = शून्य;
		जाओ मुक्त_out;
	पूर्ण

	off_size += info->ftrace_size;
	cxt->fpszs = psz_init_zones(PSTORE_TYPE_FTRACE, &off,
			info->ftrace_size,
			info->ftrace_size / nr_cpu_ids,
			&cxt->ftrace_max_cnt);
	अगर (IS_ERR(cxt->fpszs)) अणु
		err = PTR_ERR(cxt->fpszs);
		cxt->fpszs = शून्य;
		जाओ मुक्त_out;
	पूर्ण

	cxt->kpszs = psz_init_zones(PSTORE_TYPE_DMESG, &off,
			info->total_size - off_size,
			info->kmsg_size, &cxt->kmsg_max_cnt);
	अगर (IS_ERR(cxt->kpszs)) अणु
		err = PTR_ERR(cxt->kpszs);
		cxt->kpszs = शून्य;
		जाओ मुक्त_out;
	पूर्ण

	वापस 0;
मुक्त_out:
	psz_मुक्त_all_zones(cxt);
	वापस err;
पूर्ण

/**
 * रेजिस्टर_pstore_zone() - रेजिस्टर to pstore/zone
 *
 * @info: back-end driver inक्रमmation. See &काष्ठा pstore_zone_info.
 *
 * Only one back-end at one समय.
 *
 * Return: 0 on success, others on failure.
 */
पूर्णांक रेजिस्टर_pstore_zone(काष्ठा pstore_zone_info *info)
अणु
	पूर्णांक err = -EINVAL;
	काष्ठा psz_context *cxt = &pstore_zone_cxt;

	अगर (info->total_size < 4096) अणु
		pr_warn("total_size must be >= 4096\n");
		वापस -EINVAL;
	पूर्ण
	अगर (info->total_size > SZ_128M) अणु
		pr_warn("capping size to 128MiB\n");
		info->total_size = SZ_128M;
	पूर्ण

	अगर (!info->kmsg_size && !info->pmsg_size && !info->console_size &&
	    !info->ftrace_size) अणु
		pr_warn("at least one record size must be non-zero\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!info->name || !info->name[0])
		वापस -EINVAL;

#घोषणा check_size(name, size) अणु					\
		अगर (info->name > 0 && info->name < (size)) अणु		\
			pr_err(#name " must be over %d\n", (size));	\
			वापस -EINVAL;					\
		पूर्ण							\
		अगर (info->name & (size - 1)) अणु				\
			pr_err(#name " must be a multiple of %d\n",	\
					(size));			\
			वापस -EINVAL;					\
		पूर्ण							\
	पूर्ण

	check_size(total_size, 4096);
	check_size(kmsg_size, SECTOR_SIZE);
	check_size(pmsg_size, SECTOR_SIZE);
	check_size(console_size, SECTOR_SIZE);
	check_size(ftrace_size, SECTOR_SIZE);

#अघोषित check_size

	/*
	 * the @पढ़ो and @ग_लिखो must be applied.
	 * अगर no @पढ़ो, pstore may mount failed.
	 * अगर no @ग_लिखो, pstore करो not support to हटाओ record file.
	 */
	अगर (!info->पढ़ो || !info->ग_लिखो) अणु
		pr_err("no valid general read/write interface\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&cxt->pstore_zone_info_lock);
	अगर (cxt->pstore_zone_info) अणु
		pr_warn("'%s' already loaded: ignoring '%s'\n",
				cxt->pstore_zone_info->name, info->name);
		mutex_unlock(&cxt->pstore_zone_info_lock);
		वापस -EBUSY;
	पूर्ण
	cxt->pstore_zone_info = info;

	pr_debug("register %s with properties:\n", info->name);
	pr_debug("\ttotal size : %ld Bytes\n", info->total_size);
	pr_debug("\tkmsg size : %ld Bytes\n", info->kmsg_size);
	pr_debug("\tpmsg size : %ld Bytes\n", info->pmsg_size);
	pr_debug("\tconsole size : %ld Bytes\n", info->console_size);
	pr_debug("\tftrace size : %ld Bytes\n", info->ftrace_size);

	err = psz_alloc_zones(cxt);
	अगर (err) अणु
		pr_err("alloc zones failed\n");
		जाओ fail_out;
	पूर्ण

	अगर (info->kmsg_size) अणु
		cxt->pstore.bufsize = cxt->kpszs[0]->buffer_size -
			माप(काष्ठा psz_kmsg_header);
		cxt->pstore.buf = kzalloc(cxt->pstore.bufsize, GFP_KERNEL);
		अगर (!cxt->pstore.buf) अणु
			err = -ENOMEM;
			जाओ fail_मुक्त;
		पूर्ण
	पूर्ण
	cxt->pstore.data = cxt;

	pr_info("registered %s as backend for", info->name);
	cxt->pstore.max_reason = info->max_reason;
	cxt->pstore.name = info->name;
	अगर (info->kmsg_size) अणु
		cxt->pstore.flags |= PSTORE_FLAGS_DMESG;
		pr_cont(" kmsg(%s",
			kmsg_dump_reason_str(cxt->pstore.max_reason));
		अगर (cxt->pstore_zone_info->panic_ग_लिखो)
			pr_cont(",panic_write");
		pr_cont(")");
	पूर्ण
	अगर (info->pmsg_size) अणु
		cxt->pstore.flags |= PSTORE_FLAGS_PMSG;
		pr_cont(" pmsg");
	पूर्ण
	अगर (info->console_size) अणु
		cxt->pstore.flags |= PSTORE_FLAGS_CONSOLE;
		pr_cont(" console");
	पूर्ण
	अगर (info->ftrace_size) अणु
		cxt->pstore.flags |= PSTORE_FLAGS_FTRACE;
		pr_cont(" ftrace");
	पूर्ण
	pr_cont("\n");

	err = pstore_रेजिस्टर(&cxt->pstore);
	अगर (err) अणु
		pr_err("registering with pstore failed\n");
		जाओ fail_मुक्त;
	पूर्ण
	mutex_unlock(&pstore_zone_cxt.pstore_zone_info_lock);

	वापस 0;

fail_मुक्त:
	kमुक्त(cxt->pstore.buf);
	cxt->pstore.buf = शून्य;
	cxt->pstore.bufsize = 0;
	psz_मुक्त_all_zones(cxt);
fail_out:
	pstore_zone_cxt.pstore_zone_info = शून्य;
	mutex_unlock(&pstore_zone_cxt.pstore_zone_info_lock);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(रेजिस्टर_pstore_zone);

/**
 * unरेजिस्टर_pstore_zone() - unरेजिस्टर to pstore/zone
 *
 * @info: back-end driver inक्रमmation. See काष्ठा pstore_zone_info.
 */
व्योम unरेजिस्टर_pstore_zone(काष्ठा pstore_zone_info *info)
अणु
	काष्ठा psz_context *cxt = &pstore_zone_cxt;

	mutex_lock(&cxt->pstore_zone_info_lock);
	अगर (!cxt->pstore_zone_info) अणु
		mutex_unlock(&cxt->pstore_zone_info_lock);
		वापस;
	पूर्ण

	/* Stop incoming ग_लिखोs from pstore. */
	pstore_unरेजिस्टर(&cxt->pstore);

	/* Flush any pending ग_लिखोs. */
	psz_flush_all_dirty_zones(शून्य);
	flush_delayed_work(&psz_cleaner);

	/* Clean up allocations. */
	kमुक्त(cxt->pstore.buf);
	cxt->pstore.buf = शून्य;
	cxt->pstore.bufsize = 0;
	cxt->pstore_zone_info = शून्य;

	psz_मुक्त_all_zones(cxt);

	/* Clear counters and zone state. */
	cxt->oops_counter = 0;
	cxt->panic_counter = 0;
	atomic_set(&cxt->recovered, 0);
	atomic_set(&cxt->on_panic, 0);

	mutex_unlock(&cxt->pstore_zone_info_lock);
पूर्ण
EXPORT_SYMBOL_GPL(unरेजिस्टर_pstore_zone);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("WeiXiong Liao <liaoweixiong@allwinnertech.com>");
MODULE_AUTHOR("Kees Cook <keescook@chromium.org>");
MODULE_DESCRIPTION("Storage Manager for pstore/blk");
