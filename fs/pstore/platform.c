<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Persistent Storage - platक्रमm driver पूर्णांकerface parts.
 *
 * Copyright (C) 2007-2008 Google, Inc.
 * Copyright (C) 2010 Intel Corporation <tony.luck@पूर्णांकel.com>
 */

#घोषणा pr_fmt(fmt) "pstore: " fmt

#समावेश <linux/atomic.h>
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/console.h>
#समावेश <linux/module.h>
#समावेश <linux/pstore.h>
#अगर IS_ENABLED(CONFIG_PSTORE_LZO_COMPRESS)
#समावेश <linux/lzo.h>
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_LZ4_COMPRESS) || IS_ENABLED(CONFIG_PSTORE_LZ4HC_COMPRESS)
#समावेश <linux/lz4.h>
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_ZSTD_COMPRESS)
#समावेश <linux/zstd.h>
#पूर्ण_अगर
#समावेश <linux/crypto.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/workqueue.h>

#समावेश "internal.h"

/*
 * We defer making "oops" entries appear in pstore - see
 * whether the प्रणाली is actually still running well enough
 * to let someone see the entry
 */
अटल पूर्णांक pstore_update_ms = -1;
module_param_named(update_ms, pstore_update_ms, पूर्णांक, 0600);
MODULE_PARM_DESC(update_ms, "milliseconds before pstore updates its content "
		 "(default is -1, which means runtime updates are disabled; "
		 "enabling this option may not be safe; it may lead to further "
		 "corruption on Oopses)");

/* Names should be in the same order as the क्रमागत pstore_type_id */
अटल स्थिर अक्षर * स्थिर pstore_type_names[] = अणु
	"dmesg",
	"mce",
	"console",
	"ftrace",
	"rtas",
	"powerpc-ofw",
	"powerpc-common",
	"pmsg",
	"powerpc-opal",
पूर्ण;

अटल पूर्णांक pstore_new_entry;

अटल व्योम pstore_समयfunc(काष्ठा समयr_list *);
अटल DEFINE_TIMER(pstore_समयr, pstore_समयfunc);

अटल व्योम pstore_करोwork(काष्ठा work_काष्ठा *);
अटल DECLARE_WORK(pstore_work, pstore_करोwork);

/*
 * psinfo_lock protects "psinfo" during calls to
 * pstore_रेजिस्टर(), pstore_unरेजिस्टर(), and
 * the fileप्रणाली mount/unmount routines.
 */
अटल DEFINE_MUTEX(psinfo_lock);
काष्ठा pstore_info *psinfo;

अटल अक्षर *backend;
module_param(backend, अक्षरp, 0444);
MODULE_PARM_DESC(backend, "specific backend to use");

अटल अक्षर *compress =
#अगर_घोषित CONFIG_PSTORE_COMPRESS_DEFAULT
		CONFIG_PSTORE_COMPRESS_DEFAULT;
#अन्यथा
		शून्य;
#पूर्ण_अगर
module_param(compress, अक्षरp, 0444);
MODULE_PARM_DESC(compress, "compression to use");

/* Compression parameters */
अटल काष्ठा crypto_comp *tfm;

काष्ठा pstore_zbackend अणु
	पूर्णांक (*zbufsize)(माप_प्रकार size);
	स्थिर अक्षर *name;
पूर्ण;

अटल अक्षर *big_oops_buf;
अटल माप_प्रकार big_oops_buf_sz;

/* How much of the console log to snapshot */
अचिन्हित दीर्घ kmsg_bytes = CONFIG_PSTORE_DEFAULT_KMSG_BYTES;

व्योम pstore_set_kmsg_bytes(पूर्णांक bytes)
अणु
	kmsg_bytes = bytes;
पूर्ण

/* Tag each group of saved records with a sequence number */
अटल पूर्णांक	oopscount;

स्थिर अक्षर *pstore_type_to_name(क्रमागत pstore_type_id type)
अणु
	BUILD_BUG_ON(ARRAY_SIZE(pstore_type_names) != PSTORE_TYPE_MAX);

	अगर (WARN_ON_ONCE(type >= PSTORE_TYPE_MAX))
		वापस "unknown";

	वापस pstore_type_names[type];
पूर्ण
EXPORT_SYMBOL_GPL(pstore_type_to_name);

क्रमागत pstore_type_id pstore_name_to_type(स्थिर अक्षर *name)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < PSTORE_TYPE_MAX; i++) अणु
		अगर (!म_भेद(pstore_type_names[i], name))
			वापस i;
	पूर्ण

	वापस PSTORE_TYPE_MAX;
पूर्ण
EXPORT_SYMBOL_GPL(pstore_name_to_type);

अटल व्योम pstore_समयr_kick(व्योम)
अणु
	अगर (pstore_update_ms < 0)
		वापस;

	mod_समयr(&pstore_समयr, jअगरfies + msecs_to_jअगरfies(pstore_update_ms));
पूर्ण

/*
 * Should pstore_dump() रुको क्रम a concurrent pstore_dump()? If
 * not, the current pstore_dump() will report a failure to dump
 * and वापस.
 */
अटल bool pstore_cannot_रुको(क्रमागत kmsg_dump_reason reason)
अणु
	/* In NMI path, pstore shouldn't block regardless of reason. */
	अगर (in_nmi())
		वापस true;

	चयन (reason) अणु
	/* In panic हाल, other cpus are stopped by smp_send_stop(). */
	हाल KMSG_DUMP_PANIC:
	/* Emergency restart shouldn't be blocked. */
	हाल KMSG_DUMP_EMERG:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

#अगर IS_ENABLED(CONFIG_PSTORE_DEFLATE_COMPRESS)
अटल पूर्णांक zbufsize_deflate(माप_प्रकार size)
अणु
	माप_प्रकार cmpr;

	चयन (size) अणु
	/* buffer range क्रम efivars */
	हाल 1000 ... 2000:
		cmpr = 56;
		अवरोध;
	हाल 2001 ... 3000:
		cmpr = 54;
		अवरोध;
	हाल 3001 ... 3999:
		cmpr = 52;
		अवरोध;
	/* buffer range क्रम nvram, erst */
	हाल 4000 ... 10000:
		cmpr = 45;
		अवरोध;
	शेष:
		cmpr = 60;
		अवरोध;
	पूर्ण

	वापस (size * 100) / cmpr;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_PSTORE_LZO_COMPRESS)
अटल पूर्णांक zbufsize_lzo(माप_प्रकार size)
अणु
	वापस lzo1x_worst_compress(size);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_PSTORE_LZ4_COMPRESS) || IS_ENABLED(CONFIG_PSTORE_LZ4HC_COMPRESS)
अटल पूर्णांक zbufsize_lz4(माप_प्रकार size)
अणु
	वापस LZ4_compressBound(size);
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_PSTORE_842_COMPRESS)
अटल पूर्णांक zbufsize_842(माप_प्रकार size)
अणु
	वापस size;
पूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_PSTORE_ZSTD_COMPRESS)
अटल पूर्णांक zbufsize_zstd(माप_प्रकार size)
अणु
	वापस ZSTD_compressBound(size);
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pstore_zbackend *zbackend __ro_after_init;

अटल स्थिर काष्ठा pstore_zbackend zbackends[] = अणु
#अगर IS_ENABLED(CONFIG_PSTORE_DEFLATE_COMPRESS)
	अणु
		.zbufsize	= zbufsize_deflate,
		.name		= "deflate",
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_LZO_COMPRESS)
	अणु
		.zbufsize	= zbufsize_lzo,
		.name		= "lzo",
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_LZ4_COMPRESS)
	अणु
		.zbufsize	= zbufsize_lz4,
		.name		= "lz4",
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_LZ4HC_COMPRESS)
	अणु
		.zbufsize	= zbufsize_lz4,
		.name		= "lz4hc",
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_842_COMPRESS)
	अणु
		.zbufsize	= zbufsize_842,
		.name		= "842",
	पूर्ण,
#पूर्ण_अगर
#अगर IS_ENABLED(CONFIG_PSTORE_ZSTD_COMPRESS)
	अणु
		.zbufsize	= zbufsize_zstd,
		.name		= "zstd",
	पूर्ण,
#पूर्ण_अगर
	अणु पूर्ण
पूर्ण;

अटल पूर्णांक pstore_compress(स्थिर व्योम *in, व्योम *out,
			   अचिन्हित पूर्णांक inlen, अचिन्हित पूर्णांक outlen)
अणु
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_PSTORE_COMPRESS))
		वापस -EINVAL;

	ret = crypto_comp_compress(tfm, in, inlen, out, &outlen);
	अगर (ret) अणु
		pr_err("crypto_comp_compress failed, ret = %d!\n", ret);
		वापस ret;
	पूर्ण

	वापस outlen;
पूर्ण

अटल व्योम allocate_buf_क्रम_compression(व्योम)
अणु
	काष्ठा crypto_comp *ctx;
	पूर्णांक size;
	अक्षर *buf;

	/* Skip अगर not built-in or compression backend not selected yet. */
	अगर (!IS_ENABLED(CONFIG_PSTORE_COMPRESS) || !zbackend)
		वापस;

	/* Skip अगर no pstore backend yet or compression init alपढ़ोy करोne. */
	अगर (!psinfo || tfm)
		वापस;

	अगर (!crypto_has_comp(zbackend->name, 0, 0)) अणु
		pr_err("Unknown compression: %s\n", zbackend->name);
		वापस;
	पूर्ण

	size = zbackend->zbufsize(psinfo->bufsize);
	अगर (size <= 0) अणु
		pr_err("Invalid compression size for %s: %d\n",
		       zbackend->name, size);
		वापस;
	पूर्ण

	buf = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buf) अणु
		pr_err("Failed %d byte compression buffer allocation for: %s\n",
		       size, zbackend->name);
		वापस;
	पूर्ण

	ctx = crypto_alloc_comp(zbackend->name, 0, 0);
	अगर (IS_ERR_OR_शून्य(ctx)) अणु
		kमुक्त(buf);
		pr_err("crypto_alloc_comp('%s') failed: %ld\n", zbackend->name,
		       PTR_ERR(ctx));
		वापस;
	पूर्ण

	/* A non-शून्य big_oops_buf indicates compression is available. */
	tfm = ctx;
	big_oops_buf_sz = size;
	big_oops_buf = buf;

	pr_info("Using crash dump compression: %s\n", zbackend->name);
पूर्ण

अटल व्योम मुक्त_buf_क्रम_compression(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_PSTORE_COMPRESS) && tfm) अणु
		crypto_मुक्त_comp(tfm);
		tfm = शून्य;
	पूर्ण
	kमुक्त(big_oops_buf);
	big_oops_buf = शून्य;
	big_oops_buf_sz = 0;
पूर्ण

/*
 * Called when compression fails, since the prपूर्णांकk buffer
 * would be fetched क्रम compression calling it again when
 * compression fails would have moved the iterator of
 * prपूर्णांकk buffer which results in fetching old contents.
 * Copy the recent messages from big_oops_buf to psinfo->buf
 */
अटल माप_प्रकार copy_kmsg_to_buffer(पूर्णांक hsize, माप_प्रकार len)
अणु
	माप_प्रकार total_len;
	माप_प्रकार dअगरf;

	total_len = hsize + len;

	अगर (total_len > psinfo->bufsize) अणु
		dअगरf = total_len - psinfo->bufsize + hsize;
		स_नकल(psinfo->buf, big_oops_buf, hsize);
		स_नकल(psinfo->buf + hsize, big_oops_buf + dअगरf,
					psinfo->bufsize - hsize);
		total_len = psinfo->bufsize;
	पूर्ण अन्यथा
		स_नकल(psinfo->buf, big_oops_buf, total_len);

	वापस total_len;
पूर्ण

व्योम pstore_record_init(काष्ठा pstore_record *record,
			काष्ठा pstore_info *psinfo)
अणु
	स_रखो(record, 0, माप(*record));

	record->psi = psinfo;

	/* Report zeroed बारtamp अगर called beक्रमe समयkeeping has resumed. */
	record->समय = ns_to_बारpec64(kसमय_get_real_fast_ns());
पूर्ण

/*
 * callback from kmsg_dump. Save as much as we can (up to kmsg_bytes) from the
 * end of the buffer.
 */
अटल व्योम pstore_dump(काष्ठा kmsg_dumper *dumper,
			क्रमागत kmsg_dump_reason reason)
अणु
	काष्ठा kmsg_dump_iter iter;
	अचिन्हित दीर्घ	total = 0;
	स्थिर अक्षर	*why;
	अचिन्हित पूर्णांक	part = 1;
	पूर्णांक		ret;

	why = kmsg_dump_reason_str(reason);

	अगर (करोwn_trylock(&psinfo->buf_lock)) अणु
		/* Failed to acquire lock: give up अगर we cannot रुको. */
		अगर (pstore_cannot_रुको(reason)) अणु
			pr_err("dump skipped in %s path: may corrupt error record\n",
				in_nmi() ? "NMI" : why);
			वापस;
		पूर्ण
		अगर (करोwn_पूर्णांकerruptible(&psinfo->buf_lock)) अणु
			pr_err("could not grab semaphore?!\n");
			वापस;
		पूर्ण
	पूर्ण

	kmsg_dump_शुरुआत(&iter);

	oopscount++;
	जबतक (total < kmsg_bytes) अणु
		अक्षर *dst;
		माप_प्रकार dst_size;
		पूर्णांक header_size;
		पूर्णांक zipped_len = -1;
		माप_प्रकार dump_size;
		काष्ठा pstore_record record;

		pstore_record_init(&record, psinfo);
		record.type = PSTORE_TYPE_DMESG;
		record.count = oopscount;
		record.reason = reason;
		record.part = part;
		record.buf = psinfo->buf;

		अगर (big_oops_buf) अणु
			dst = big_oops_buf;
			dst_size = big_oops_buf_sz;
		पूर्ण अन्यथा अणु
			dst = psinfo->buf;
			dst_size = psinfo->bufsize;
		पूर्ण

		/* Write dump header. */
		header_size = snम_लिखो(dst, dst_size, "%s#%d Part%u\n", why,
				 oopscount, part);
		dst_size -= header_size;

		/* Write dump contents. */
		अगर (!kmsg_dump_get_buffer(&iter, true, dst + header_size,
					  dst_size, &dump_size))
			अवरोध;

		अगर (big_oops_buf) अणु
			zipped_len = pstore_compress(dst, psinfo->buf,
						header_size + dump_size,
						psinfo->bufsize);

			अगर (zipped_len > 0) अणु
				record.compressed = true;
				record.size = zipped_len;
			पूर्ण अन्यथा अणु
				record.size = copy_kmsg_to_buffer(header_size,
								  dump_size);
			पूर्ण
		पूर्ण अन्यथा अणु
			record.size = header_size + dump_size;
		पूर्ण

		ret = psinfo->ग_लिखो(&record);
		अगर (ret == 0 && reason == KMSG_DUMP_OOPS) अणु
			pstore_new_entry = 1;
			pstore_समयr_kick();
		पूर्ण

		total += record.size;
		part++;
	पूर्ण

	up(&psinfo->buf_lock);
पूर्ण

अटल काष्ठा kmsg_dumper pstore_dumper = अणु
	.dump = pstore_dump,
पूर्ण;

/*
 * Register with kmsg_dump to save last part of console log on panic.
 */
अटल व्योम pstore_रेजिस्टर_kmsg(व्योम)
अणु
	kmsg_dump_रेजिस्टर(&pstore_dumper);
पूर्ण

अटल व्योम pstore_unरेजिस्टर_kmsg(व्योम)
अणु
	kmsg_dump_unरेजिस्टर(&pstore_dumper);
पूर्ण

#अगर_घोषित CONFIG_PSTORE_CONSOLE
अटल व्योम pstore_console_ग_लिखो(काष्ठा console *con, स्थिर अक्षर *s, अचिन्हित c)
अणु
	काष्ठा pstore_record record;

	अगर (!c)
		वापस;

	pstore_record_init(&record, psinfo);
	record.type = PSTORE_TYPE_CONSOLE;

	record.buf = (अक्षर *)s;
	record.size = c;
	psinfo->ग_लिखो(&record);
पूर्ण

अटल काष्ठा console pstore_console = अणु
	.ग_लिखो	= pstore_console_ग_लिखो,
	.index	= -1,
पूर्ण;

अटल व्योम pstore_रेजिस्टर_console(व्योम)
अणु
	/* Show which backend is going to get console ग_लिखोs. */
	strscpy(pstore_console.name, psinfo->name,
		माप(pstore_console.name));
	/*
	 * Always initialize flags here since prior unरेजिस्टर_console()
	 * calls may have changed settings (specअगरically CON_ENABLED).
	 */
	pstore_console.flags = CON_PRINTBUFFER | CON_ENABLED | CON_ANYTIME;
	रेजिस्टर_console(&pstore_console);
पूर्ण

अटल व्योम pstore_unरेजिस्टर_console(व्योम)
अणु
	unरेजिस्टर_console(&pstore_console);
पूर्ण
#अन्यथा
अटल व्योम pstore_रेजिस्टर_console(व्योम) अणुपूर्ण
अटल व्योम pstore_unरेजिस्टर_console(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल पूर्णांक pstore_ग_लिखो_user_compat(काष्ठा pstore_record *record,
				    स्थिर अक्षर __user *buf)
अणु
	पूर्णांक ret = 0;

	अगर (record->buf)
		वापस -EINVAL;

	record->buf = memdup_user(buf, record->size);
	अगर (IS_ERR(record->buf)) अणु
		ret = PTR_ERR(record->buf);
		जाओ out;
	पूर्ण

	ret = record->psi->ग_लिखो(record);

	kमुक्त(record->buf);
out:
	record->buf = शून्य;

	वापस unlikely(ret < 0) ? ret : record->size;
पूर्ण

/*
 * platक्रमm specअगरic persistent storage driver रेजिस्टरs with
 * us here. If pstore is alपढ़ोy mounted, call the platक्रमm
 * पढ़ो function right away to populate the file प्रणाली. If not
 * then the pstore mount code will call us later to fill out
 * the file प्रणाली.
 */
पूर्णांक pstore_रेजिस्टर(काष्ठा pstore_info *psi)
अणु
	अगर (backend && म_भेद(backend, psi->name)) अणु
		pr_warn("ignoring unexpected backend '%s'\n", psi->name);
		वापस -EPERM;
	पूर्ण

	/* Sanity check flags. */
	अगर (!psi->flags) अणु
		pr_warn("backend '%s' must support at least one frontend\n",
			psi->name);
		वापस -EINVAL;
	पूर्ण

	/* Check क्रम required functions. */
	अगर (!psi->पढ़ो || !psi->ग_लिखो) अणु
		pr_warn("backend '%s' must implement read() and write()\n",
			psi->name);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&psinfo_lock);
	अगर (psinfo) अणु
		pr_warn("backend '%s' already loaded: ignoring '%s'\n",
			psinfo->name, psi->name);
		mutex_unlock(&psinfo_lock);
		वापस -EBUSY;
	पूर्ण

	अगर (!psi->ग_लिखो_user)
		psi->ग_लिखो_user = pstore_ग_लिखो_user_compat;
	psinfo = psi;
	mutex_init(&psinfo->पढ़ो_mutex);
	sema_init(&psinfo->buf_lock, 1);

	अगर (psi->flags & PSTORE_FLAGS_DMESG)
		allocate_buf_क्रम_compression();

	pstore_get_records(0);

	अगर (psi->flags & PSTORE_FLAGS_DMESG) अणु
		pstore_dumper.max_reason = psinfo->max_reason;
		pstore_रेजिस्टर_kmsg();
	पूर्ण
	अगर (psi->flags & PSTORE_FLAGS_CONSOLE)
		pstore_रेजिस्टर_console();
	अगर (psi->flags & PSTORE_FLAGS_FTRACE)
		pstore_रेजिस्टर_ftrace();
	अगर (psi->flags & PSTORE_FLAGS_PMSG)
		pstore_रेजिस्टर_pmsg();

	/* Start watching क्रम new records, अगर desired. */
	pstore_समयr_kick();

	/*
	 * Update the module parameter backend, so it is visible
	 * through /sys/module/pstore/parameters/backend
	 */
	backend = kstrdup(psi->name, GFP_KERNEL);

	pr_info("Registered %s as persistent store backend\n", psi->name);

	mutex_unlock(&psinfo_lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pstore_रेजिस्टर);

व्योम pstore_unरेजिस्टर(काष्ठा pstore_info *psi)
अणु
	/* It's okay to unरेजिस्टर nothing. */
	अगर (!psi)
		वापस;

	mutex_lock(&psinfo_lock);

	/* Only one backend can be रेजिस्टरed at a समय. */
	अगर (WARN_ON(psi != psinfo)) अणु
		mutex_unlock(&psinfo_lock);
		वापस;
	पूर्ण

	/* Unरेजिस्टर all callbacks. */
	अगर (psi->flags & PSTORE_FLAGS_PMSG)
		pstore_unरेजिस्टर_pmsg();
	अगर (psi->flags & PSTORE_FLAGS_FTRACE)
		pstore_unरेजिस्टर_ftrace();
	अगर (psi->flags & PSTORE_FLAGS_CONSOLE)
		pstore_unरेजिस्टर_console();
	अगर (psi->flags & PSTORE_FLAGS_DMESG)
		pstore_unरेजिस्टर_kmsg();

	/* Stop समयr and make sure all work has finished. */
	del_समयr_sync(&pstore_समयr);
	flush_work(&pstore_work);

	/* Remove all backend records from fileप्रणाली tree. */
	pstore_put_backend_records(psi);

	मुक्त_buf_क्रम_compression();

	psinfo = शून्य;
	kमुक्त(backend);
	backend = शून्य;
	mutex_unlock(&psinfo_lock);
पूर्ण
EXPORT_SYMBOL_GPL(pstore_unरेजिस्टर);

अटल व्योम decompress_record(काष्ठा pstore_record *record)
अणु
	पूर्णांक ret;
	पूर्णांक unzipped_len;
	अक्षर *unzipped, *workspace;

	अगर (!IS_ENABLED(CONFIG_PSTORE_COMPRESS) || !record->compressed)
		वापस;

	/* Only PSTORE_TYPE_DMESG support compression. */
	अगर (record->type != PSTORE_TYPE_DMESG) अणु
		pr_warn("ignored compressed record type %d\n", record->type);
		वापस;
	पूर्ण

	/* Missing compression buffer means compression was not initialized. */
	अगर (!big_oops_buf) अणु
		pr_warn("no decompression method initialized!\n");
		वापस;
	पूर्ण

	/* Allocate enough space to hold max decompression and ECC. */
	unzipped_len = big_oops_buf_sz;
	workspace = kदो_स्मृति(unzipped_len + record->ecc_notice_size,
			    GFP_KERNEL);
	अगर (!workspace)
		वापस;

	/* After decompression "unzipped_len" is almost certainly smaller. */
	ret = crypto_comp_decompress(tfm, record->buf, record->size,
					  workspace, &unzipped_len);
	अगर (ret) अणु
		pr_err("crypto_comp_decompress failed, ret = %d!\n", ret);
		kमुक्त(workspace);
		वापस;
	पूर्ण

	/* Append ECC notice to decompressed buffer. */
	स_नकल(workspace + unzipped_len, record->buf + record->size,
	       record->ecc_notice_size);

	/* Copy decompressed contents पूर्णांकo an minimum-sized allocation. */
	unzipped = kmemdup(workspace, unzipped_len + record->ecc_notice_size,
			   GFP_KERNEL);
	kमुक्त(workspace);
	अगर (!unzipped)
		वापस;

	/* Swap out compressed contents with decompressed contents. */
	kमुक्त(record->buf);
	record->buf = unzipped;
	record->size = unzipped_len;
	record->compressed = false;
पूर्ण

/*
 * Read all the records from one persistent store backend. Create
 * files in our fileप्रणाली.  Don't warn about -EEXIST errors
 * when we are re-scanning the backing store looking to add new
 * error records.
 */
व्योम pstore_get_backend_records(काष्ठा pstore_info *psi,
				काष्ठा dentry *root, पूर्णांक quiet)
अणु
	पूर्णांक failed = 0;
	अचिन्हित पूर्णांक stop_loop = 65536;

	अगर (!psi || !root)
		वापस;

	mutex_lock(&psi->पढ़ो_mutex);
	अगर (psi->खोलो && psi->खोलो(psi))
		जाओ out;

	/*
	 * Backend callback पढ़ो() allocates record.buf. decompress_record()
	 * may पुनः_स्मृतिate record.buf. On success, pstore_mkfile() will keep
	 * the record.buf, so मुक्त it only on failure.
	 */
	क्रम (; stop_loop; stop_loop--) अणु
		काष्ठा pstore_record *record;
		पूर्णांक rc;

		record = kzalloc(माप(*record), GFP_KERNEL);
		अगर (!record) अणु
			pr_err("out of memory creating record\n");
			अवरोध;
		पूर्ण
		pstore_record_init(record, psi);

		record->size = psi->पढ़ो(record);

		/* No more records left in backend? */
		अगर (record->size <= 0) अणु
			kमुक्त(record);
			अवरोध;
		पूर्ण

		decompress_record(record);
		rc = pstore_mkfile(root, record);
		अगर (rc) अणु
			/* pstore_mkfile() did not take record, so मुक्त it. */
			kमुक्त(record->buf);
			kमुक्त(record);
			अगर (rc != -EEXIST || !quiet)
				failed++;
		पूर्ण
	पूर्ण
	अगर (psi->बंद)
		psi->बंद(psi);
out:
	mutex_unlock(&psi->पढ़ो_mutex);

	अगर (failed)
		pr_warn("failed to create %d record(s) from '%s'\n",
			failed, psi->name);
	अगर (!stop_loop)
		pr_err("looping? Too many records seen from '%s'\n",
			psi->name);
पूर्ण

अटल व्योम pstore_करोwork(काष्ठा work_काष्ठा *work)
अणु
	pstore_get_records(1);
पूर्ण

अटल व्योम pstore_समयfunc(काष्ठा समयr_list *unused)
अणु
	अगर (pstore_new_entry) अणु
		pstore_new_entry = 0;
		schedule_work(&pstore_work);
	पूर्ण

	pstore_समयr_kick();
पूर्ण

अटल व्योम __init pstore_choose_compression(व्योम)
अणु
	स्थिर काष्ठा pstore_zbackend *step;

	अगर (!compress)
		वापस;

	क्रम (step = zbackends; step->name; step++) अणु
		अगर (!म_भेद(compress, step->name)) अणु
			zbackend = step;
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक __init pstore_init(व्योम)
अणु
	पूर्णांक ret;

	pstore_choose_compression();

	/*
	 * Check अगर any pstore backends रेजिस्टरed earlier but did not
	 * initialize compression because crypto was not पढ़ोy. If so,
	 * initialize compression now.
	 */
	allocate_buf_क्रम_compression();

	ret = pstore_init_fs();
	अगर (ret)
		मुक्त_buf_क्रम_compression();

	वापस ret;
पूर्ण
late_initcall(pstore_init);

अटल व्योम __निकास pstore_निकास(व्योम)
अणु
	pstore_निकास_fs();
पूर्ण
module_निकास(pstore_निकास)

MODULE_AUTHOR("Tony Luck <tony.luck@intel.com>");
MODULE_LICENSE("GPL");
