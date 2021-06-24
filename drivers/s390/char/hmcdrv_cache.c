<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    SE/HMC Drive (Read) Cache Functions
 *
 *    Copyright IBM Corp. 2013
 *    Author(s): Ralf Hoppe (rhoppe@de.ibm.com)
 *
 */

#घोषणा KMSG_COMPONENT "hmcdrv"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/jअगरfies.h>

#समावेश "hmcdrv_ftp.h"
#समावेश "hmcdrv_cache.h"

#घोषणा HMCDRV_CACHE_TIMEOUT		30 /* aging समयout in seconds */

/**
 * काष्ठा hmcdrv_cache_entry - file cache (only used on पढ़ो/dir)
 * @id: FTP command ID
 * @content: kernel-space buffer, 4k aligned
 * @len: size of @content cache (0 अगर caching disabled)
 * @ofs: start of content within file (-1 अगर no cached content)
 * @fname: file name
 * @fsize: file size
 * @समयout: cache समयout in jअगरfies
 *
 * Notice that the first three members (id, fname, fsize) are cached on all
 * पढ़ो/dir requests. But content is cached only under some preconditions.
 * Uncached content is संकेतled by a negative value of @ofs.
 */
काष्ठा hmcdrv_cache_entry अणु
	क्रमागत hmcdrv_ftp_cmdid id;
	अक्षर fname[HMCDRV_FTP_FIDENT_MAX];
	माप_प्रकार fsize;
	loff_t ofs;
	अचिन्हित दीर्घ समयout;
	व्योम *content;
	माप_प्रकार len;
पूर्ण;

अटल पूर्णांक hmcdrv_cache_order; /* cache allocated page order */

अटल काष्ठा hmcdrv_cache_entry hmcdrv_cache_file = अणु
	.fsize = SIZE_MAX,
	.ofs = -1,
	.len = 0,
	.fname = अणु'\0'पूर्ण
पूर्ण;

/**
 * hmcdrv_cache_get() - looks क्रम file data/content in पढ़ो cache
 * @ftp: poपूर्णांकer to FTP command specअगरication
 *
 * Return: number of bytes पढ़ो from cache or a negative number अगर nothing
 * in content cache (क्रम the file/cmd specअगरied in @ftp)
 */
अटल sमाप_प्रकार hmcdrv_cache_get(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp)
अणु
	loff_t pos; /* position in cache (चिन्हित) */
	sमाप_प्रकार len;

	अगर ((ftp->id != hmcdrv_cache_file.id) ||
	    म_भेद(hmcdrv_cache_file.fname, ftp->fname))
		वापस -1;

	अगर (ftp->ofs >= hmcdrv_cache_file.fsize) /* खातापूर्ण ? */
		वापस 0;

	अगर ((hmcdrv_cache_file.ofs < 0) || /* has content? */
	    समय_after(jअगरfies, hmcdrv_cache_file.समयout))
		वापस -1;

	/* there seems to be cached content - calculate the maximum number
	 * of bytes that can be वापसed (regarding file size and offset)
	 */
	len = hmcdrv_cache_file.fsize - ftp->ofs;

	अगर (len > ftp->len)
		len = ftp->len;

	/* check अगर the requested chunk falls पूर्णांकo our cache (which starts
	 * at offset 'hmcdrv_cache_file.ofs' in the file of पूर्णांकerest)
	 */
	pos = ftp->ofs - hmcdrv_cache_file.ofs;

	अगर ((pos >= 0) &&
	    ((pos + len) <= hmcdrv_cache_file.len)) अणु

		स_नकल(ftp->buf,
		       hmcdrv_cache_file.content + pos,
		       len);
		pr_debug("using cached content of '%s', returning %zd/%zd bytes\n",
			 hmcdrv_cache_file.fname, len,
			 hmcdrv_cache_file.fsize);

		वापस len;
	पूर्ण

	वापस -1;
पूर्ण

/**
 * hmcdrv_cache_करो() - करो a HMC drive CD/DVD transfer with cache update
 * @ftp: poपूर्णांकer to FTP command specअगरication
 * @func: FTP transfer function to be used
 *
 * Return: number of bytes पढ़ो/written or a (negative) error code
 */
अटल sमाप_प्रकार hmcdrv_cache_करो(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp,
			       hmcdrv_cache_ftpfunc func)
अणु
	sमाप_प्रकार len;

	/* only cache content अगर the पढ़ो/dir cache really exists
	 * (hmcdrv_cache_file.len > 0), is large enough to handle the
	 * request (hmcdrv_cache_file.len >= ftp->len) and there is a need
	 * to करो so (ftp->len > 0)
	 */
	अगर ((ftp->len > 0) && (hmcdrv_cache_file.len >= ftp->len)) अणु

		/* because the cache is not located at ftp->buf, we have to
		 * assemble a new HMC drive FTP cmd specअगरication (poपूर्णांकing
		 * to our cache, and using the increased size)
		 */
		काष्ठा hmcdrv_ftp_cmdspec cftp = *ftp; /* make a copy */
		cftp.buf = hmcdrv_cache_file.content;  /* and update */
		cftp.len = hmcdrv_cache_file.len;      /* buffer data */

		len = func(&cftp, &hmcdrv_cache_file.fsize); /* now करो */

		अगर (len > 0) अणु
			pr_debug("caching %zd bytes content for '%s'\n",
				 len, ftp->fname);

			अगर (len > ftp->len)
				len = ftp->len;

			hmcdrv_cache_file.ofs = ftp->ofs;
			hmcdrv_cache_file.समयout = jअगरfies +
				HMCDRV_CACHE_TIMEOUT * HZ;
			स_नकल(ftp->buf, hmcdrv_cache_file.content, len);
		पूर्ण
	पूर्ण अन्यथा अणु
		len = func(ftp, &hmcdrv_cache_file.fsize);
		hmcdrv_cache_file.ofs = -1; /* invalidate content */
	पूर्ण

	अगर (len > 0) अणु
		/* cache some file info (FTP command, file name and file
		 * size) unconditionally
		 */
		strlcpy(hmcdrv_cache_file.fname, ftp->fname,
			HMCDRV_FTP_FIDENT_MAX);
		hmcdrv_cache_file.id = ftp->id;
		pr_debug("caching cmd %d, file size %zu for '%s'\n",
			 ftp->id, hmcdrv_cache_file.fsize, ftp->fname);
	पूर्ण

	वापस len;
पूर्ण

/**
 * hmcdrv_cache_cmd() - perक्रमm a cached HMC drive CD/DVD transfer
 * @ftp: poपूर्णांकer to FTP command specअगरication
 * @func: FTP transfer function to be used
 *
 * Attention: Notice that this function is not reentrant - so the caller
 * must ensure exclusive execution.
 *
 * Return: number of bytes पढ़ो/written or a (negative) error code
 */
sमाप_प्रकार hmcdrv_cache_cmd(स्थिर काष्ठा hmcdrv_ftp_cmdspec *ftp,
			 hmcdrv_cache_ftpfunc func)
अणु
	sमाप_प्रकार len;

	अगर ((ftp->id == HMCDRV_FTP_सूची) || /* पढ़ो cache */
	    (ftp->id == HMCDRV_FTP_NLIST) ||
	    (ftp->id == HMCDRV_FTP_GET)) अणु

		len = hmcdrv_cache_get(ftp);

		अगर (len >= 0) /* got it from cache ? */
			वापस len; /* yes */

		len = hmcdrv_cache_करो(ftp, func);

		अगर (len >= 0)
			वापस len;

	पूर्ण अन्यथा अणु
		len = func(ftp, शून्य); /* simply करो original command */
	पूर्ण

	/* invalidate the (पढ़ो) cache in हाल there was a ग_लिखो operation
	 * or an error on पढ़ो/dir
	 */
	hmcdrv_cache_file.id = HMCDRV_FTP_NOOP;
	hmcdrv_cache_file.fsize = Lदीर्घ_उच्च;
	hmcdrv_cache_file.ofs = -1;

	वापस len;
पूर्ण

/**
 * hmcdrv_cache_startup() - startup of HMC drive cache
 * @cachesize: cache size
 *
 * Return: 0 on success, अन्यथा a (negative) error code
 */
पूर्णांक hmcdrv_cache_startup(माप_प्रकार cachesize)
अणु
	अगर (cachesize > 0) अणु /* perक्रमm caching ? */
		hmcdrv_cache_order = get_order(cachesize);
		hmcdrv_cache_file.content =
			(व्योम *) __get_मुक्त_pages(GFP_KERNEL | GFP_DMA,
						  hmcdrv_cache_order);

		अगर (!hmcdrv_cache_file.content) अणु
			pr_err("Allocating the requested cache size of %zu bytes failed\n",
			       cachesize);
			वापस -ENOMEM;
		पूर्ण

		pr_debug("content cache enabled, size is %zu bytes\n",
			 cachesize);
	पूर्ण

	hmcdrv_cache_file.len = cachesize;
	वापस 0;
पूर्ण

/**
 * hmcdrv_cache_shutकरोwn() - shutकरोwn of HMC drive cache
 */
व्योम hmcdrv_cache_shutकरोwn(व्योम)
अणु
	अगर (hmcdrv_cache_file.content) अणु
		मुक्त_pages((अचिन्हित दीर्घ) hmcdrv_cache_file.content,
			   hmcdrv_cache_order);
		hmcdrv_cache_file.content = शून्य;
	पूर्ण

	hmcdrv_cache_file.id = HMCDRV_FTP_NOOP;
	hmcdrv_cache_file.fsize = Lदीर्घ_उच्च;
	hmcdrv_cache_file.ofs = -1;
	hmcdrv_cache_file.len = 0; /* no cache */
पूर्ण
