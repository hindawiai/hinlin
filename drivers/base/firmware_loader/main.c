<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * मुख्य.c - Multi purpose firmware loading support
 *
 * Copyright (c) 2003 Manuel Estrada Sainz
 *
 * Please see Documentation/driver-api/firmware/ क्रम more inक्रमmation.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/capability.h>
#समावेश <linux/device.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/initrd.h>
#समावेश <linux/समयr.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/firmware.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/file.h>
#समावेश <linux/list.h>
#समावेश <linux/fs.h>
#समावेश <linux/async.h>
#समावेश <linux/pm.h>
#समावेश <linux/suspend.h>
#समावेश <linux/syscore_ops.h>
#समावेश <linux/reboot.h>
#समावेश <linux/security.h>
#समावेश <linux/xz.h>

#समावेश <generated/utsrelease.h>

#समावेश "../base.h"
#समावेश "firmware.h"
#समावेश "fallback.h"

MODULE_AUTHOR("Manuel Estrada Sainz");
MODULE_DESCRIPTION("Multi purpose firmware loading support");
MODULE_LICENSE("GPL");

काष्ठा firmware_cache अणु
	/* firmware_buf instance will be added पूर्णांकo the below list */
	spinlock_t lock;
	काष्ठा list_head head;
	पूर्णांक state;

#अगर_घोषित CONFIG_FW_CACHE
	/*
	 * Names of firmware images which have been cached successfully
	 * will be added पूर्णांकo the below list so that device uncache
	 * helper can trace which firmware images have been cached
	 * beक्रमe.
	 */
	spinlock_t name_lock;
	काष्ठा list_head fw_names;

	काष्ठा delayed_work work;

	काष्ठा notअगरier_block   pm_notअगरy;
#पूर्ण_अगर
पूर्ण;

काष्ठा fw_cache_entry अणु
	काष्ठा list_head list;
	स्थिर अक्षर *name;
पूर्ण;

काष्ठा fw_name_devm अणु
	अचिन्हित दीर्घ magic;
	स्थिर अक्षर *name;
पूर्ण;

अटल अंतरभूत काष्ठा fw_priv *to_fw_priv(काष्ठा kref *ref)
अणु
	वापस container_of(ref, काष्ठा fw_priv, ref);
पूर्ण

#घोषणा	FW_LOADER_NO_CACHE	0
#घोषणा	FW_LOADER_START_CACHE	1

/* fw_lock could be moved to 'struct fw_sysfs' but since it is just
 * guarding क्रम corner हालs a global lock should be OK */
DEFINE_MUTEX(fw_lock);

अटल काष्ठा firmware_cache fw_cache;

/* Builtin firmware support */

#अगर_घोषित CONFIG_FW_LOADER

बाह्य काष्ठा builtin_fw __start_builtin_fw[];
बाह्य काष्ठा builtin_fw __end_builtin_fw[];

अटल व्योम fw_copy_to_pपुनः_स्मृति_buf(काष्ठा firmware *fw,
				    व्योम *buf, माप_प्रकार size)
अणु
	अगर (!buf || size < fw->size)
		वापस;
	स_नकल(buf, fw->data, fw->size);
पूर्ण

अटल bool fw_get_builtin_firmware(काष्ठा firmware *fw, स्थिर अक्षर *name,
				    व्योम *buf, माप_प्रकार size)
अणु
	काष्ठा builtin_fw *b_fw;

	क्रम (b_fw = __start_builtin_fw; b_fw != __end_builtin_fw; b_fw++) अणु
		अगर (म_भेद(name, b_fw->name) == 0) अणु
			fw->size = b_fw->size;
			fw->data = b_fw->data;
			fw_copy_to_pपुनः_स्मृति_buf(fw, buf, size);

			वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool fw_is_builtin_firmware(स्थिर काष्ठा firmware *fw)
अणु
	काष्ठा builtin_fw *b_fw;

	क्रम (b_fw = __start_builtin_fw; b_fw != __end_builtin_fw; b_fw++)
		अगर (fw->data == b_fw->data)
			वापस true;

	वापस false;
पूर्ण

#अन्यथा /* Module हाल - no builtin firmware support */

अटल अंतरभूत bool fw_get_builtin_firmware(काष्ठा firmware *fw,
					   स्थिर अक्षर *name, व्योम *buf,
					   माप_प्रकार size)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool fw_is_builtin_firmware(स्थिर काष्ठा firmware *fw)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल व्योम fw_state_init(काष्ठा fw_priv *fw_priv)
अणु
	काष्ठा fw_state *fw_st = &fw_priv->fw_st;

	init_completion(&fw_st->completion);
	fw_st->status = FW_STATUS_UNKNOWN;
पूर्ण

अटल अंतरभूत पूर्णांक fw_state_रुको(काष्ठा fw_priv *fw_priv)
अणु
	वापस __fw_state_रुको_common(fw_priv, MAX_SCHEDULE_TIMEOUT);
पूर्ण

अटल पूर्णांक fw_cache_piggyback_on_request(स्थिर अक्षर *name);

अटल काष्ठा fw_priv *__allocate_fw_priv(स्थिर अक्षर *fw_name,
					  काष्ठा firmware_cache *fwc,
					  व्योम *dbuf,
					  माप_प्रकार size,
					  माप_प्रकार offset,
					  u32 opt_flags)
अणु
	काष्ठा fw_priv *fw_priv;

	/* For a partial पढ़ो, the buffer must be pपुनः_स्मृतिated. */
	अगर ((opt_flags & FW_OPT_PARTIAL) && !dbuf)
		वापस शून्य;

	/* Only partial पढ़ोs are allowed to use an offset. */
	अगर (offset != 0 && !(opt_flags & FW_OPT_PARTIAL))
		वापस शून्य;

	fw_priv = kzalloc(माप(*fw_priv), GFP_ATOMIC);
	अगर (!fw_priv)
		वापस शून्य;

	fw_priv->fw_name = kstrdup_स्थिर(fw_name, GFP_ATOMIC);
	अगर (!fw_priv->fw_name) अणु
		kमुक्त(fw_priv);
		वापस शून्य;
	पूर्ण

	kref_init(&fw_priv->ref);
	fw_priv->fwc = fwc;
	fw_priv->data = dbuf;
	fw_priv->allocated_size = size;
	fw_priv->offset = offset;
	fw_priv->opt_flags = opt_flags;
	fw_state_init(fw_priv);
#अगर_घोषित CONFIG_FW_LOADER_USER_HELPER
	INIT_LIST_HEAD(&fw_priv->pending_list);
#पूर्ण_अगर

	pr_debug("%s: fw-%s fw_priv=%p\n", __func__, fw_name, fw_priv);

	वापस fw_priv;
पूर्ण

अटल काष्ठा fw_priv *__lookup_fw_priv(स्थिर अक्षर *fw_name)
अणु
	काष्ठा fw_priv *पंचांगp;
	काष्ठा firmware_cache *fwc = &fw_cache;

	list_क्रम_each_entry(पंचांगp, &fwc->head, list)
		अगर (!म_भेद(पंचांगp->fw_name, fw_name))
			वापस पंचांगp;
	वापस शून्य;
पूर्ण

/* Returns 1 क्रम batching firmware requests with the same name */
अटल पूर्णांक alloc_lookup_fw_priv(स्थिर अक्षर *fw_name,
				काष्ठा firmware_cache *fwc,
				काष्ठा fw_priv **fw_priv,
				व्योम *dbuf,
				माप_प्रकार size,
				माप_प्रकार offset,
				u32 opt_flags)
अणु
	काष्ठा fw_priv *पंचांगp;

	spin_lock(&fwc->lock);
	/*
	 * Do not merge requests that are marked to be non-cached or
	 * are perक्रमming partial पढ़ोs.
	 */
	अगर (!(opt_flags & (FW_OPT_NOCACHE | FW_OPT_PARTIAL))) अणु
		पंचांगp = __lookup_fw_priv(fw_name);
		अगर (पंचांगp) अणु
			kref_get(&पंचांगp->ref);
			spin_unlock(&fwc->lock);
			*fw_priv = पंचांगp;
			pr_debug("batched request - sharing the same struct fw_priv and lookup for multiple requests\n");
			वापस 1;
		पूर्ण
	पूर्ण

	पंचांगp = __allocate_fw_priv(fw_name, fwc, dbuf, size, offset, opt_flags);
	अगर (पंचांगp) अणु
		INIT_LIST_HEAD(&पंचांगp->list);
		अगर (!(opt_flags & FW_OPT_NOCACHE))
			list_add(&पंचांगp->list, &fwc->head);
	पूर्ण
	spin_unlock(&fwc->lock);

	*fw_priv = पंचांगp;

	वापस पंचांगp ? 0 : -ENOMEM;
पूर्ण

अटल व्योम __मुक्त_fw_priv(काष्ठा kref *ref)
	__releases(&fwc->lock)
अणु
	काष्ठा fw_priv *fw_priv = to_fw_priv(ref);
	काष्ठा firmware_cache *fwc = fw_priv->fwc;

	pr_debug("%s: fw-%s fw_priv=%p data=%p size=%u\n",
		 __func__, fw_priv->fw_name, fw_priv, fw_priv->data,
		 (अचिन्हित पूर्णांक)fw_priv->size);

	list_del(&fw_priv->list);
	spin_unlock(&fwc->lock);

	अगर (fw_is_paged_buf(fw_priv))
		fw_मुक्त_paged_buf(fw_priv);
	अन्यथा अगर (!fw_priv->allocated_size)
		vमुक्त(fw_priv->data);

	kमुक्त_स्थिर(fw_priv->fw_name);
	kमुक्त(fw_priv);
पूर्ण

अटल व्योम मुक्त_fw_priv(काष्ठा fw_priv *fw_priv)
अणु
	काष्ठा firmware_cache *fwc = fw_priv->fwc;
	spin_lock(&fwc->lock);
	अगर (!kref_put(&fw_priv->ref, __मुक्त_fw_priv))
		spin_unlock(&fwc->lock);
पूर्ण

#अगर_घोषित CONFIG_FW_LOADER_PAGED_BUF
bool fw_is_paged_buf(काष्ठा fw_priv *fw_priv)
अणु
	वापस fw_priv->is_paged_buf;
पूर्ण

व्योम fw_मुक्त_paged_buf(काष्ठा fw_priv *fw_priv)
अणु
	पूर्णांक i;

	अगर (!fw_priv->pages)
		वापस;

	vunmap(fw_priv->data);

	क्रम (i = 0; i < fw_priv->nr_pages; i++)
		__मुक्त_page(fw_priv->pages[i]);
	kvमुक्त(fw_priv->pages);
	fw_priv->pages = शून्य;
	fw_priv->page_array_size = 0;
	fw_priv->nr_pages = 0;
पूर्ण

पूर्णांक fw_grow_paged_buf(काष्ठा fw_priv *fw_priv, पूर्णांक pages_needed)
अणु
	/* If the array of pages is too small, grow it */
	अगर (fw_priv->page_array_size < pages_needed) अणु
		पूर्णांक new_array_size = max(pages_needed,
					 fw_priv->page_array_size * 2);
		काष्ठा page **new_pages;

		new_pages = kvदो_स्मृति_array(new_array_size, माप(व्योम *),
					   GFP_KERNEL);
		अगर (!new_pages)
			वापस -ENOMEM;
		स_नकल(new_pages, fw_priv->pages,
		       fw_priv->page_array_size * माप(व्योम *));
		स_रखो(&new_pages[fw_priv->page_array_size], 0, माप(व्योम *) *
		       (new_array_size - fw_priv->page_array_size));
		kvमुक्त(fw_priv->pages);
		fw_priv->pages = new_pages;
		fw_priv->page_array_size = new_array_size;
	पूर्ण

	जबतक (fw_priv->nr_pages < pages_needed) अणु
		fw_priv->pages[fw_priv->nr_pages] =
			alloc_page(GFP_KERNEL | __GFP_HIGHMEM);

		अगर (!fw_priv->pages[fw_priv->nr_pages])
			वापस -ENOMEM;
		fw_priv->nr_pages++;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक fw_map_paged_buf(काष्ठा fw_priv *fw_priv)
अणु
	/* one pages buffer should be mapped/unmapped only once */
	अगर (!fw_priv->pages)
		वापस 0;

	vunmap(fw_priv->data);
	fw_priv->data = vmap(fw_priv->pages, fw_priv->nr_pages, 0,
			     PAGE_KERNEL_RO);
	अगर (!fw_priv->data)
		वापस -ENOMEM;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * XZ-compressed firmware support
 */
#अगर_घोषित CONFIG_FW_LOADER_COMPRESS
/* show an error and वापस the standard error code */
अटल पूर्णांक fw_decompress_xz_error(काष्ठा device *dev, क्रमागत xz_ret xz_ret)
अणु
	अगर (xz_ret != XZ_STREAM_END) अणु
		dev_warn(dev, "xz decompression failed (xz_ret=%d)\n", xz_ret);
		वापस xz_ret == XZ_MEM_ERROR ? -ENOMEM : -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* single-shot decompression onto the pre-allocated buffer */
अटल पूर्णांक fw_decompress_xz_single(काष्ठा device *dev, काष्ठा fw_priv *fw_priv,
				   माप_प्रकार in_size, स्थिर व्योम *in_buffer)
अणु
	काष्ठा xz_dec *xz_dec;
	काष्ठा xz_buf xz_buf;
	क्रमागत xz_ret xz_ret;

	xz_dec = xz_dec_init(XZ_SINGLE, (u32)-1);
	अगर (!xz_dec)
		वापस -ENOMEM;

	xz_buf.in_size = in_size;
	xz_buf.in = in_buffer;
	xz_buf.in_pos = 0;
	xz_buf.out_size = fw_priv->allocated_size;
	xz_buf.out = fw_priv->data;
	xz_buf.out_pos = 0;

	xz_ret = xz_dec_run(xz_dec, &xz_buf);
	xz_dec_end(xz_dec);

	fw_priv->size = xz_buf.out_pos;
	वापस fw_decompress_xz_error(dev, xz_ret);
पूर्ण

/* decompression on paged buffer and map it */
अटल पूर्णांक fw_decompress_xz_pages(काष्ठा device *dev, काष्ठा fw_priv *fw_priv,
				  माप_प्रकार in_size, स्थिर व्योम *in_buffer)
अणु
	काष्ठा xz_dec *xz_dec;
	काष्ठा xz_buf xz_buf;
	क्रमागत xz_ret xz_ret;
	काष्ठा page *page;
	पूर्णांक err = 0;

	xz_dec = xz_dec_init(XZ_DYNALLOC, (u32)-1);
	अगर (!xz_dec)
		वापस -ENOMEM;

	xz_buf.in_size = in_size;
	xz_buf.in = in_buffer;
	xz_buf.in_pos = 0;

	fw_priv->is_paged_buf = true;
	fw_priv->size = 0;
	करो अणु
		अगर (fw_grow_paged_buf(fw_priv, fw_priv->nr_pages + 1)) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		/* decompress onto the new allocated page */
		page = fw_priv->pages[fw_priv->nr_pages - 1];
		xz_buf.out = kmap(page);
		xz_buf.out_pos = 0;
		xz_buf.out_size = PAGE_SIZE;
		xz_ret = xz_dec_run(xz_dec, &xz_buf);
		kunmap(page);
		fw_priv->size += xz_buf.out_pos;
		/* partial decompression means either end or error */
		अगर (xz_buf.out_pos != PAGE_SIZE)
			अवरोध;
	पूर्ण जबतक (xz_ret == XZ_OK);

	err = fw_decompress_xz_error(dev, xz_ret);
	अगर (!err)
		err = fw_map_paged_buf(fw_priv);

 out:
	xz_dec_end(xz_dec);
	वापस err;
पूर्ण

अटल पूर्णांक fw_decompress_xz(काष्ठा device *dev, काष्ठा fw_priv *fw_priv,
			    माप_प्रकार in_size, स्थिर व्योम *in_buffer)
अणु
	/* अगर the buffer is pre-allocated, we can perक्रमm in single-shot mode */
	अगर (fw_priv->data)
		वापस fw_decompress_xz_single(dev, fw_priv, in_size, in_buffer);
	अन्यथा
		वापस fw_decompress_xz_pages(dev, fw_priv, in_size, in_buffer);
पूर्ण
#पूर्ण_अगर /* CONFIG_FW_LOADER_COMPRESS */

/* direct firmware loading support */
अटल अक्षर fw_path_para[256];
अटल स्थिर अक्षर * स्थिर fw_path[] = अणु
	fw_path_para,
	"/lib/firmware/updates/" UTS_RELEASE,
	"/lib/firmware/updates",
	"/lib/firmware/" UTS_RELEASE,
	"/lib/firmware"
पूर्ण;

/*
 * Typical usage is that passing 'firmware_class.path=$CUSTOMIZED_PATH'
 * from kernel command line because firmware_class is generally built in
 * kernel instead of module.
 */
module_param_string(path, fw_path_para, माप(fw_path_para), 0644);
MODULE_PARM_DESC(path, "customized firmware image search path with a higher priority than default path");

अटल पूर्णांक
fw_get_fileप्रणाली_firmware(काष्ठा device *device, काष्ठा fw_priv *fw_priv,
			   स्थिर अक्षर *suffix,
			   पूर्णांक (*decompress)(काष्ठा device *dev,
					     काष्ठा fw_priv *fw_priv,
					     माप_प्रकार in_size,
					     स्थिर व्योम *in_buffer))
अणु
	माप_प्रकार size;
	पूर्णांक i, len;
	पूर्णांक rc = -ENOENT;
	अक्षर *path;
	माप_प्रकार msize = पूर्णांक_उच्च;
	व्योम *buffer = शून्य;

	/* Alपढ़ोy populated data member means we're loading पूर्णांकo a buffer */
	अगर (!decompress && fw_priv->data) अणु
		buffer = fw_priv->data;
		msize = fw_priv->allocated_size;
	पूर्ण

	path = __getname();
	अगर (!path)
		वापस -ENOMEM;

	रुको_क्रम_initramfs();
	क्रम (i = 0; i < ARRAY_SIZE(fw_path); i++) अणु
		माप_प्रकार file_size = 0;
		माप_प्रकार *file_size_ptr = शून्य;

		/* skip the unset customized path */
		अगर (!fw_path[i][0])
			जारी;

		len = snम_लिखो(path, PATH_MAX, "%s/%s%s",
			       fw_path[i], fw_priv->fw_name, suffix);
		अगर (len >= PATH_MAX) अणु
			rc = -ENAMETOOLONG;
			अवरोध;
		पूर्ण

		fw_priv->size = 0;

		/*
		 * The total file size is only examined when करोing a partial
		 * पढ़ो; the "full read" हाल needs to fail अगर the whole
		 * firmware was not completely loaded.
		 */
		अगर ((fw_priv->opt_flags & FW_OPT_PARTIAL) && buffer)
			file_size_ptr = &file_size;

		/* load firmware files from the mount namespace of init */
		rc = kernel_पढ़ो_file_from_path_initns(path, fw_priv->offset,
						       &buffer, msize,
						       file_size_ptr,
						       READING_FIRMWARE);
		अगर (rc < 0) अणु
			अगर (rc != -ENOENT)
				dev_warn(device, "loading %s failed with error %d\n",
					 path, rc);
			अन्यथा
				dev_dbg(device, "loading %s failed for no such file or directory.\n",
					 path);
			जारी;
		पूर्ण
		size = rc;
		rc = 0;

		dev_dbg(device, "Loading firmware from %s\n", path);
		अगर (decompress) अणु
			dev_dbg(device, "f/w decompressing %s\n",
				fw_priv->fw_name);
			rc = decompress(device, fw_priv, size, buffer);
			/* discard the superfluous original content */
			vमुक्त(buffer);
			buffer = शून्य;
			अगर (rc) अणु
				fw_मुक्त_paged_buf(fw_priv);
				जारी;
			पूर्ण
		पूर्ण अन्यथा अणु
			dev_dbg(device, "direct-loading %s\n",
				fw_priv->fw_name);
			अगर (!fw_priv->data)
				fw_priv->data = buffer;
			fw_priv->size = size;
		पूर्ण
		fw_state_करोne(fw_priv);
		अवरोध;
	पूर्ण
	__putname(path);

	वापस rc;
पूर्ण

/* firmware holds the ownership of pages */
अटल व्योम firmware_मुक्त_data(स्थिर काष्ठा firmware *fw)
अणु
	/* Loaded directly? */
	अगर (!fw->priv) अणु
		vमुक्त(fw->data);
		वापस;
	पूर्ण
	मुक्त_fw_priv(fw->priv);
पूर्ण

/* store the pages buffer info firmware from buf */
अटल व्योम fw_set_page_data(काष्ठा fw_priv *fw_priv, काष्ठा firmware *fw)
अणु
	fw->priv = fw_priv;
	fw->size = fw_priv->size;
	fw->data = fw_priv->data;

	pr_debug("%s: fw-%s fw_priv=%p data=%p size=%u\n",
		 __func__, fw_priv->fw_name, fw_priv, fw_priv->data,
		 (अचिन्हित पूर्णांक)fw_priv->size);
पूर्ण

#अगर_घोषित CONFIG_FW_CACHE
अटल व्योम fw_name_devm_release(काष्ठा device *dev, व्योम *res)
अणु
	काष्ठा fw_name_devm *fwn = res;

	अगर (fwn->magic == (अचिन्हित दीर्घ)&fw_cache)
		pr_debug("%s: fw_name-%s devm-%p released\n",
				__func__, fwn->name, res);
	kमुक्त_स्थिर(fwn->name);
पूर्ण

अटल पूर्णांक fw_devm_match(काष्ठा device *dev, व्योम *res,
		व्योम *match_data)
अणु
	काष्ठा fw_name_devm *fwn = res;

	वापस (fwn->magic == (अचिन्हित दीर्घ)&fw_cache) &&
		!म_भेद(fwn->name, match_data);
पूर्ण

अटल काष्ठा fw_name_devm *fw_find_devm_name(काष्ठा device *dev,
		स्थिर अक्षर *name)
अणु
	काष्ठा fw_name_devm *fwn;

	fwn = devres_find(dev, fw_name_devm_release,
			  fw_devm_match, (व्योम *)name);
	वापस fwn;
पूर्ण

अटल bool fw_cache_is_setup(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा fw_name_devm *fwn;

	fwn = fw_find_devm_name(dev, name);
	अगर (fwn)
		वापस true;

	वापस false;
पूर्ण

/* add firmware name पूर्णांकo devres list */
अटल पूर्णांक fw_add_devm_name(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	काष्ठा fw_name_devm *fwn;

	अगर (fw_cache_is_setup(dev, name))
		वापस 0;

	fwn = devres_alloc(fw_name_devm_release, माप(काष्ठा fw_name_devm),
			   GFP_KERNEL);
	अगर (!fwn)
		वापस -ENOMEM;
	fwn->name = kstrdup_स्थिर(name, GFP_KERNEL);
	अगर (!fwn->name) अणु
		devres_मुक्त(fwn);
		वापस -ENOMEM;
	पूर्ण

	fwn->magic = (अचिन्हित दीर्घ)&fw_cache;
	devres_add(dev, fwn);

	वापस 0;
पूर्ण
#अन्यथा
अटल bool fw_cache_is_setup(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस false;
पूर्ण

अटल पूर्णांक fw_add_devm_name(काष्ठा device *dev, स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक assign_fw(काष्ठा firmware *fw, काष्ठा device *device)
अणु
	काष्ठा fw_priv *fw_priv = fw->priv;
	पूर्णांक ret;

	mutex_lock(&fw_lock);
	अगर (!fw_priv->size || fw_state_is_पातed(fw_priv)) अणु
		mutex_unlock(&fw_lock);
		वापस -ENOENT;
	पूर्ण

	/*
	 * add firmware name पूर्णांकo devres list so that we can स्वतः cache
	 * and uncache firmware क्रम device.
	 *
	 * device may has been deleted alपढ़ोy, but the problem
	 * should be fixed in devres or driver core.
	 */
	/* करोn't cache firmware handled without uevent */
	अगर (device && (fw_priv->opt_flags & FW_OPT_UEVENT) &&
	    !(fw_priv->opt_flags & FW_OPT_NOCACHE)) अणु
		ret = fw_add_devm_name(device, fw_priv->fw_name);
		अगर (ret) अणु
			mutex_unlock(&fw_lock);
			वापस ret;
		पूर्ण
	पूर्ण

	/*
	 * After caching firmware image is started, let it piggyback
	 * on request firmware.
	 */
	अगर (!(fw_priv->opt_flags & FW_OPT_NOCACHE) &&
	    fw_priv->fwc->state == FW_LOADER_START_CACHE) अणु
		अगर (fw_cache_piggyback_on_request(fw_priv->fw_name))
			kref_get(&fw_priv->ref);
	पूर्ण

	/* pass the pages buffer to driver at the last minute */
	fw_set_page_data(fw_priv, fw);
	mutex_unlock(&fw_lock);
	वापस 0;
पूर्ण

/* prepare firmware and firmware_buf काष्ठाs;
 * वापस 0 अगर a firmware is alपढ़ोy asचिन्हित, 1 अगर need to load one,
 * or a negative error code
 */
अटल पूर्णांक
_request_firmware_prepare(काष्ठा firmware **firmware_p, स्थिर अक्षर *name,
			  काष्ठा device *device, व्योम *dbuf, माप_प्रकार size,
			  माप_प्रकार offset, u32 opt_flags)
अणु
	काष्ठा firmware *firmware;
	काष्ठा fw_priv *fw_priv;
	पूर्णांक ret;

	*firmware_p = firmware = kzalloc(माप(*firmware), GFP_KERNEL);
	अगर (!firmware) अणु
		dev_err(device, "%s: kmalloc(struct firmware) failed\n",
			__func__);
		वापस -ENOMEM;
	पूर्ण

	अगर (fw_get_builtin_firmware(firmware, name, dbuf, size)) अणु
		dev_dbg(device, "using built-in %s\n", name);
		वापस 0; /* asचिन्हित */
	पूर्ण

	ret = alloc_lookup_fw_priv(name, &fw_cache, &fw_priv, dbuf, size,
				   offset, opt_flags);

	/*
	 * bind with 'priv' now to aव्योम warning in failure path
	 * of requesting firmware.
	 */
	firmware->priv = fw_priv;

	अगर (ret > 0) अणु
		ret = fw_state_रुको(fw_priv);
		अगर (!ret) अणु
			fw_set_page_data(fw_priv, firmware);
			वापस 0; /* asचिन्हित */
		पूर्ण
	पूर्ण

	अगर (ret < 0)
		वापस ret;
	वापस 1; /* need to load */
पूर्ण

/*
 * Batched requests need only one wake, we need to करो this step last due to the
 * fallback mechanism. The buf is रक्षित with kref_get(), and it won't be
 * released until the last user calls release_firmware().
 *
 * Failed batched requests are possible as well, in such हालs we just share
 * the काष्ठा fw_priv and won't release it until all requests are woken
 * and have gone through this same path.
 */
अटल व्योम fw_पात_batch_reqs(काष्ठा firmware *fw)
अणु
	काष्ठा fw_priv *fw_priv;

	/* Loaded directly? */
	अगर (!fw || !fw->priv)
		वापस;

	fw_priv = fw->priv;
	अगर (!fw_state_is_पातed(fw_priv))
		fw_state_पातed(fw_priv);
पूर्ण

/* called from request_firmware() and request_firmware_work_func() */
अटल पूर्णांक
_request_firmware(स्थिर काष्ठा firmware **firmware_p, स्थिर अक्षर *name,
		  काष्ठा device *device, व्योम *buf, माप_प्रकार size,
		  माप_प्रकार offset, u32 opt_flags)
अणु
	काष्ठा firmware *fw = शून्य;
	bool nondirect = false;
	पूर्णांक ret;

	अगर (!firmware_p)
		वापस -EINVAL;

	अगर (!name || name[0] == '\0') अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	ret = _request_firmware_prepare(&fw, name, device, buf, size,
					offset, opt_flags);
	अगर (ret <= 0) /* error or alपढ़ोy asचिन्हित */
		जाओ out;

	ret = fw_get_fileप्रणाली_firmware(device, fw->priv, "", शून्य);

	/* Only full पढ़ोs can support decompression, platक्रमm, and sysfs. */
	अगर (!(opt_flags & FW_OPT_PARTIAL))
		nondirect = true;

#अगर_घोषित CONFIG_FW_LOADER_COMPRESS
	अगर (ret == -ENOENT && nondirect)
		ret = fw_get_fileप्रणाली_firmware(device, fw->priv, ".xz",
						 fw_decompress_xz);
#पूर्ण_अगर
	अगर (ret == -ENOENT && nondirect)
		ret = firmware_fallback_platक्रमm(fw->priv);

	अगर (ret) अणु
		अगर (!(opt_flags & FW_OPT_NO_WARN))
			dev_warn(device,
				 "Direct firmware load for %s failed with error %d\n",
				 name, ret);
		अगर (nondirect)
			ret = firmware_fallback_sysfs(fw, name, device,
						      opt_flags, ret);
	पूर्ण अन्यथा
		ret = assign_fw(fw, device);

 out:
	अगर (ret < 0) अणु
		fw_पात_batch_reqs(fw);
		release_firmware(fw);
		fw = शून्य;
	पूर्ण

	*firmware_p = fw;
	वापस ret;
पूर्ण

/**
 * request_firmware() - send firmware request and रुको क्रम it
 * @firmware_p: poपूर्णांकer to firmware image
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded
 *
 *      @firmware_p will be used to वापस a firmware image by the name
 *      of @name क्रम device @device.
 *
 *      Should be called from user context where sleeping is allowed.
 *
 *      @name will be used as $FIRMWARE in the uevent environment and
 *      should be distinctive enough not to be confused with any other
 *      firmware image क्रम this or any other device.
 *
 *	Caller must hold the reference count of @device.
 *
 *	The function can be called safely inside device's suspend and
 *	resume callback.
 **/
पूर्णांक
request_firmware(स्थिर काष्ठा firmware **firmware_p, स्थिर अक्षर *name,
		 काष्ठा device *device)
अणु
	पूर्णांक ret;

	/* Need to pin this module until वापस */
	__module_get(THIS_MODULE);
	ret = _request_firmware(firmware_p, name, device, शून्य, 0, 0,
				FW_OPT_UEVENT);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(request_firmware);

/**
 * firmware_request_nowarn() - request क्रम an optional fw module
 * @firmware: poपूर्णांकer to firmware image
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded
 *
 * This function is similar in behaviour to request_firmware(), except it
 * करोesn't produce warning messages when the file is not found. The sysfs
 * fallback mechanism is enabled अगर direct fileप्रणाली lookup fails. However,
 * failures to find the firmware file with it are still suppressed. It is
 * thereक्रमe up to the driver to check क्रम the वापस value of this call and to
 * decide when to inक्रमm the users of errors.
 **/
पूर्णांक firmware_request_nowarn(स्थिर काष्ठा firmware **firmware, स्थिर अक्षर *name,
			    काष्ठा device *device)
अणु
	पूर्णांक ret;

	/* Need to pin this module until वापस */
	__module_get(THIS_MODULE);
	ret = _request_firmware(firmware, name, device, शून्य, 0, 0,
				FW_OPT_UEVENT | FW_OPT_NO_WARN);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(firmware_request_nowarn);

/**
 * request_firmware_direct() - load firmware directly without usermode helper
 * @firmware_p: poपूर्णांकer to firmware image
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded
 *
 * This function works pretty much like request_firmware(), but this करोesn't
 * fall back to usermode helper even अगर the firmware couldn't be loaded
 * directly from fs.  Hence it's useful क्रम loading optional firmwares, which
 * aren't always present, without extra दीर्घ समयouts of udev.
 **/
पूर्णांक request_firmware_direct(स्थिर काष्ठा firmware **firmware_p,
			    स्थिर अक्षर *name, काष्ठा device *device)
अणु
	पूर्णांक ret;

	__module_get(THIS_MODULE);
	ret = _request_firmware(firmware_p, name, device, शून्य, 0, 0,
				FW_OPT_UEVENT | FW_OPT_NO_WARN |
				FW_OPT_NOFALLBACK_SYSFS);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(request_firmware_direct);

/**
 * firmware_request_platक्रमm() - request firmware with platक्रमm-fw fallback
 * @firmware: poपूर्णांकer to firmware image
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded
 *
 * This function is similar in behaviour to request_firmware, except that अगर
 * direct fileप्रणाली lookup fails, it will fallback to looking क्रम a copy of the
 * requested firmware embedded in the platक्रमm's मुख्य (e.g. UEFI) firmware.
 **/
पूर्णांक firmware_request_platक्रमm(स्थिर काष्ठा firmware **firmware,
			      स्थिर अक्षर *name, काष्ठा device *device)
अणु
	पूर्णांक ret;

	/* Need to pin this module until वापस */
	__module_get(THIS_MODULE);
	ret = _request_firmware(firmware, name, device, शून्य, 0, 0,
				FW_OPT_UEVENT | FW_OPT_FALLBACK_PLATFORM);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(firmware_request_platक्रमm);

/**
 * firmware_request_cache() - cache firmware क्रम suspend so resume can use it
 * @name: name of firmware file
 * @device: device क्रम which firmware should be cached क्रम
 *
 * There are some devices with an optimization that enables the device to not
 * require loading firmware on प्रणाली reboot. This optimization may still
 * require the firmware present on resume from suspend. This routine can be
 * used to ensure the firmware is present on resume from suspend in these
 * situations. This helper is not compatible with drivers which use
 * request_firmware_पूर्णांकo_buf() or request_firmware_noरुको() with no uevent set.
 **/
पूर्णांक firmware_request_cache(काष्ठा device *device, स्थिर अक्षर *name)
अणु
	पूर्णांक ret;

	mutex_lock(&fw_lock);
	ret = fw_add_devm_name(device, name);
	mutex_unlock(&fw_lock);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(firmware_request_cache);

/**
 * request_firmware_पूर्णांकo_buf() - load firmware पूर्णांकo a previously allocated buffer
 * @firmware_p: poपूर्णांकer to firmware image
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded and DMA region allocated
 * @buf: address of buffer to load firmware पूर्णांकo
 * @size: size of buffer
 *
 * This function works pretty much like request_firmware(), but it करोesn't
 * allocate a buffer to hold the firmware data. Instead, the firmware
 * is loaded directly पूर्णांकo the buffer poपूर्णांकed to by @buf and the @firmware_p
 * data member is poपूर्णांकed at @buf.
 *
 * This function करोesn't cache firmware either.
 */
पूर्णांक
request_firmware_पूर्णांकo_buf(स्थिर काष्ठा firmware **firmware_p, स्थिर अक्षर *name,
			  काष्ठा device *device, व्योम *buf, माप_प्रकार size)
अणु
	पूर्णांक ret;

	अगर (fw_cache_is_setup(device, name))
		वापस -EOPNOTSUPP;

	__module_get(THIS_MODULE);
	ret = _request_firmware(firmware_p, name, device, buf, size, 0,
				FW_OPT_UEVENT | FW_OPT_NOCACHE);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(request_firmware_पूर्णांकo_buf);

/**
 * request_partial_firmware_पूर्णांकo_buf() - load partial firmware पूर्णांकo a previously allocated buffer
 * @firmware_p: poपूर्णांकer to firmware image
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded and DMA region allocated
 * @buf: address of buffer to load firmware पूर्णांकo
 * @size: size of buffer
 * @offset: offset पूर्णांकo file to पढ़ो
 *
 * This function works pretty much like request_firmware_पूर्णांकo_buf except
 * it allows a partial पढ़ो of the file.
 */
पूर्णांक
request_partial_firmware_पूर्णांकo_buf(स्थिर काष्ठा firmware **firmware_p,
				  स्थिर अक्षर *name, काष्ठा device *device,
				  व्योम *buf, माप_प्रकार size, माप_प्रकार offset)
अणु
	पूर्णांक ret;

	अगर (fw_cache_is_setup(device, name))
		वापस -EOPNOTSUPP;

	__module_get(THIS_MODULE);
	ret = _request_firmware(firmware_p, name, device, buf, size, offset,
				FW_OPT_UEVENT | FW_OPT_NOCACHE |
				FW_OPT_PARTIAL);
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(request_partial_firmware_पूर्णांकo_buf);

/**
 * release_firmware() - release the resource associated with a firmware image
 * @fw: firmware resource to release
 **/
व्योम release_firmware(स्थिर काष्ठा firmware *fw)
अणु
	अगर (fw) अणु
		अगर (!fw_is_builtin_firmware(fw))
			firmware_मुक्त_data(fw);
		kमुक्त(fw);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(release_firmware);

/* Async support */
काष्ठा firmware_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा module *module;
	स्थिर अक्षर *name;
	काष्ठा device *device;
	व्योम *context;
	व्योम (*cont)(स्थिर काष्ठा firmware *fw, व्योम *context);
	u32 opt_flags;
पूर्ण;

अटल व्योम request_firmware_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा firmware_work *fw_work;
	स्थिर काष्ठा firmware *fw;

	fw_work = container_of(work, काष्ठा firmware_work, work);

	_request_firmware(&fw, fw_work->name, fw_work->device, शून्य, 0, 0,
			  fw_work->opt_flags);
	fw_work->cont(fw, fw_work->context);
	put_device(fw_work->device); /* taken in request_firmware_noरुको() */

	module_put(fw_work->module);
	kमुक्त_स्थिर(fw_work->name);
	kमुक्त(fw_work);
पूर्ण

/**
 * request_firmware_noरुको() - asynchronous version of request_firmware
 * @module: module requesting the firmware
 * @uevent: sends uevent to copy the firmware image अगर this flag
 *	is non-zero अन्यथा the firmware copy must be करोne manually.
 * @name: name of firmware file
 * @device: device क्रम which firmware is being loaded
 * @gfp: allocation flags
 * @context: will be passed over to @cont, and
 *	@fw may be %शून्य अगर firmware request fails.
 * @cont: function will be called asynchronously when the firmware
 *	request is over.
 *
 *	Caller must hold the reference count of @device.
 *
 *	Asynchronous variant of request_firmware() क्रम user contexts:
 *		- sleep क्रम as small periods as possible since it may
 *		  increase kernel boot समय of built-in device drivers
 *		  requesting firmware in their ->probe() methods, अगर
 *		  @gfp is GFP_KERNEL.
 *
 *		- can't sleep at all अगर @gfp is GFP_ATOMIC.
 **/
पूर्णांक
request_firmware_noरुको(
	काष्ठा module *module, bool uevent,
	स्थिर अक्षर *name, काष्ठा device *device, gfp_t gfp, व्योम *context,
	व्योम (*cont)(स्थिर काष्ठा firmware *fw, व्योम *context))
अणु
	काष्ठा firmware_work *fw_work;

	fw_work = kzalloc(माप(काष्ठा firmware_work), gfp);
	अगर (!fw_work)
		वापस -ENOMEM;

	fw_work->module = module;
	fw_work->name = kstrdup_स्थिर(name, gfp);
	अगर (!fw_work->name) अणु
		kमुक्त(fw_work);
		वापस -ENOMEM;
	पूर्ण
	fw_work->device = device;
	fw_work->context = context;
	fw_work->cont = cont;
	fw_work->opt_flags = FW_OPT_NOWAIT |
		(uevent ? FW_OPT_UEVENT : FW_OPT_USERHELPER);

	अगर (!uevent && fw_cache_is_setup(device, name)) अणु
		kमुक्त_स्थिर(fw_work->name);
		kमुक्त(fw_work);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!try_module_get(module)) अणु
		kमुक्त_स्थिर(fw_work->name);
		kमुक्त(fw_work);
		वापस -EFAULT;
	पूर्ण

	get_device(fw_work->device);
	INIT_WORK(&fw_work->work, request_firmware_work_func);
	schedule_work(&fw_work->work);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(request_firmware_noरुको);

#अगर_घोषित CONFIG_FW_CACHE
अटल ASYNC_DOMAIN_EXCLUSIVE(fw_cache_करोमुख्य);

/**
 * cache_firmware() - cache one firmware image in kernel memory space
 * @fw_name: the firmware image name
 *
 * Cache firmware in kernel memory so that drivers can use it when
 * प्रणाली isn't पढ़ोy क्रम them to request firmware image from userspace.
 * Once it वापसs successfully, driver can use request_firmware or its
 * noरुको version to get the cached firmware without any पूर्णांकeracting
 * with userspace
 *
 * Return 0 अगर the firmware image has been cached successfully
 * Return !0 otherwise
 *
 */
अटल पूर्णांक cache_firmware(स्थिर अक्षर *fw_name)
अणु
	पूर्णांक ret;
	स्थिर काष्ठा firmware *fw;

	pr_debug("%s: %s\n", __func__, fw_name);

	ret = request_firmware(&fw, fw_name, शून्य);
	अगर (!ret)
		kमुक्त(fw);

	pr_debug("%s: %s ret=%d\n", __func__, fw_name, ret);

	वापस ret;
पूर्ण

अटल काष्ठा fw_priv *lookup_fw_priv(स्थिर अक्षर *fw_name)
अणु
	काष्ठा fw_priv *पंचांगp;
	काष्ठा firmware_cache *fwc = &fw_cache;

	spin_lock(&fwc->lock);
	पंचांगp = __lookup_fw_priv(fw_name);
	spin_unlock(&fwc->lock);

	वापस पंचांगp;
पूर्ण

/**
 * uncache_firmware() - हटाओ one cached firmware image
 * @fw_name: the firmware image name
 *
 * Uncache one firmware image which has been cached successfully
 * beक्रमe.
 *
 * Return 0 अगर the firmware cache has been हटाओd successfully
 * Return !0 otherwise
 *
 */
अटल पूर्णांक uncache_firmware(स्थिर अक्षर *fw_name)
अणु
	काष्ठा fw_priv *fw_priv;
	काष्ठा firmware fw;

	pr_debug("%s: %s\n", __func__, fw_name);

	अगर (fw_get_builtin_firmware(&fw, fw_name, शून्य, 0))
		वापस 0;

	fw_priv = lookup_fw_priv(fw_name);
	अगर (fw_priv) अणु
		मुक्त_fw_priv(fw_priv);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल काष्ठा fw_cache_entry *alloc_fw_cache_entry(स्थिर अक्षर *name)
अणु
	काष्ठा fw_cache_entry *fce;

	fce = kzalloc(माप(*fce), GFP_ATOMIC);
	अगर (!fce)
		जाओ निकास;

	fce->name = kstrdup_स्थिर(name, GFP_ATOMIC);
	अगर (!fce->name) अणु
		kमुक्त(fce);
		fce = शून्य;
		जाओ निकास;
	पूर्ण
निकास:
	वापस fce;
पूर्ण

अटल पूर्णांक __fw_entry_found(स्थिर अक्षर *name)
अणु
	काष्ठा firmware_cache *fwc = &fw_cache;
	काष्ठा fw_cache_entry *fce;

	list_क्रम_each_entry(fce, &fwc->fw_names, list) अणु
		अगर (!म_भेद(fce->name, name))
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक fw_cache_piggyback_on_request(स्थिर अक्षर *name)
अणु
	काष्ठा firmware_cache *fwc = &fw_cache;
	काष्ठा fw_cache_entry *fce;
	पूर्णांक ret = 0;

	spin_lock(&fwc->name_lock);
	अगर (__fw_entry_found(name))
		जाओ found;

	fce = alloc_fw_cache_entry(name);
	अगर (fce) अणु
		ret = 1;
		list_add(&fce->list, &fwc->fw_names);
		pr_debug("%s: fw: %s\n", __func__, name);
	पूर्ण
found:
	spin_unlock(&fwc->name_lock);
	वापस ret;
पूर्ण

अटल व्योम मुक्त_fw_cache_entry(काष्ठा fw_cache_entry *fce)
अणु
	kमुक्त_स्थिर(fce->name);
	kमुक्त(fce);
पूर्ण

अटल व्योम __async_dev_cache_fw_image(व्योम *fw_entry,
				       async_cookie_t cookie)
अणु
	काष्ठा fw_cache_entry *fce = fw_entry;
	काष्ठा firmware_cache *fwc = &fw_cache;
	पूर्णांक ret;

	ret = cache_firmware(fce->name);
	अगर (ret) अणु
		spin_lock(&fwc->name_lock);
		list_del(&fce->list);
		spin_unlock(&fwc->name_lock);

		मुक्त_fw_cache_entry(fce);
	पूर्ण
पूर्ण

/* called with dev->devres_lock held */
अटल व्योम dev_create_fw_entry(काष्ठा device *dev, व्योम *res,
				व्योम *data)
अणु
	काष्ठा fw_name_devm *fwn = res;
	स्थिर अक्षर *fw_name = fwn->name;
	काष्ठा list_head *head = data;
	काष्ठा fw_cache_entry *fce;

	fce = alloc_fw_cache_entry(fw_name);
	अगर (fce)
		list_add(&fce->list, head);
पूर्ण

अटल पूर्णांक devm_name_match(काष्ठा device *dev, व्योम *res,
			   व्योम *match_data)
अणु
	काष्ठा fw_name_devm *fwn = res;
	वापस (fwn->magic == (अचिन्हित दीर्घ)match_data);
पूर्ण

अटल व्योम dev_cache_fw_image(काष्ठा device *dev, व्योम *data)
अणु
	LIST_HEAD(toकरो);
	काष्ठा fw_cache_entry *fce;
	काष्ठा fw_cache_entry *fce_next;
	काष्ठा firmware_cache *fwc = &fw_cache;

	devres_क्रम_each_res(dev, fw_name_devm_release,
			    devm_name_match, &fw_cache,
			    dev_create_fw_entry, &toकरो);

	list_क्रम_each_entry_safe(fce, fce_next, &toकरो, list) अणु
		list_del(&fce->list);

		spin_lock(&fwc->name_lock);
		/* only one cache entry क्रम one firmware */
		अगर (!__fw_entry_found(fce->name)) अणु
			list_add(&fce->list, &fwc->fw_names);
		पूर्ण अन्यथा अणु
			मुक्त_fw_cache_entry(fce);
			fce = शून्य;
		पूर्ण
		spin_unlock(&fwc->name_lock);

		अगर (fce)
			async_schedule_करोमुख्य(__async_dev_cache_fw_image,
					      (व्योम *)fce,
					      &fw_cache_करोमुख्य);
	पूर्ण
पूर्ण

अटल व्योम __device_uncache_fw_images(व्योम)
अणु
	काष्ठा firmware_cache *fwc = &fw_cache;
	काष्ठा fw_cache_entry *fce;

	spin_lock(&fwc->name_lock);
	जबतक (!list_empty(&fwc->fw_names)) अणु
		fce = list_entry(fwc->fw_names.next,
				काष्ठा fw_cache_entry, list);
		list_del(&fce->list);
		spin_unlock(&fwc->name_lock);

		uncache_firmware(fce->name);
		मुक्त_fw_cache_entry(fce);

		spin_lock(&fwc->name_lock);
	पूर्ण
	spin_unlock(&fwc->name_lock);
पूर्ण

/**
 * device_cache_fw_images() - cache devices' firmware
 *
 * If one device called request_firmware or its noरुको version
 * successfully beक्रमe, the firmware names are recored पूर्णांकo the
 * device's devres link list, so device_cache_fw_images can call
 * cache_firmware() to cache these firmwares क्रम the device,
 * then the device driver can load its firmwares easily at
 * समय when प्रणाली is not पढ़ोy to complete loading firmware.
 */
अटल व्योम device_cache_fw_images(व्योम)
अणु
	काष्ठा firmware_cache *fwc = &fw_cache;
	DEFINE_WAIT(रुको);

	pr_debug("%s\n", __func__);

	/* cancel uncache work */
	cancel_delayed_work_sync(&fwc->work);

	fw_fallback_set_cache_समयout();

	mutex_lock(&fw_lock);
	fwc->state = FW_LOADER_START_CACHE;
	dpm_क्रम_each_dev(शून्य, dev_cache_fw_image);
	mutex_unlock(&fw_lock);

	/* रुको क्रम completion of caching firmware क्रम all devices */
	async_synchronize_full_करोमुख्य(&fw_cache_करोमुख्य);

	fw_fallback_set_शेष_समयout();
पूर्ण

/**
 * device_uncache_fw_images() - uncache devices' firmware
 *
 * uncache all firmwares which have been cached successfully
 * by device_uncache_fw_images earlier
 */
अटल व्योम device_uncache_fw_images(व्योम)
अणु
	pr_debug("%s\n", __func__);
	__device_uncache_fw_images();
पूर्ण

अटल व्योम device_uncache_fw_images_work(काष्ठा work_काष्ठा *work)
अणु
	device_uncache_fw_images();
पूर्ण

/**
 * device_uncache_fw_images_delay() - uncache devices firmwares
 * @delay: number of milliseconds to delay uncache device firmwares
 *
 * uncache all devices's firmwares which has been cached successfully
 * by device_cache_fw_images after @delay milliseconds.
 */
अटल व्योम device_uncache_fw_images_delay(अचिन्हित दीर्घ delay)
अणु
	queue_delayed_work(प्रणाली_घातer_efficient_wq, &fw_cache.work,
			   msecs_to_jअगरfies(delay));
पूर्ण

अटल पूर्णांक fw_pm_notअगरy(काष्ठा notअगरier_block *notअगरy_block,
			अचिन्हित दीर्घ mode, व्योम *unused)
अणु
	चयन (mode) अणु
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_SUSPEND_PREPARE:
	हाल PM_RESTORE_PREPARE:
		/*
		 * समाप्त pending fallback requests with a custom fallback
		 * to aव्योम stalling suspend.
		 */
		समाप्त_pending_fw_fallback_reqs(true);
		device_cache_fw_images();
		अवरोध;

	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
		/*
		 * In हाल that प्रणाली sleep failed and syscore_suspend is
		 * not called.
		 */
		mutex_lock(&fw_lock);
		fw_cache.state = FW_LOADER_NO_CACHE;
		mutex_unlock(&fw_lock);

		device_uncache_fw_images_delay(10 * MSEC_PER_SEC);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* stop caching firmware once syscore_suspend is reached */
अटल पूर्णांक fw_suspend(व्योम)
अणु
	fw_cache.state = FW_LOADER_NO_CACHE;
	वापस 0;
पूर्ण

अटल काष्ठा syscore_ops fw_syscore_ops = अणु
	.suspend = fw_suspend,
पूर्ण;

अटल पूर्णांक __init रेजिस्टर_fw_pm_ops(व्योम)
अणु
	पूर्णांक ret;

	spin_lock_init(&fw_cache.name_lock);
	INIT_LIST_HEAD(&fw_cache.fw_names);

	INIT_DELAYED_WORK(&fw_cache.work,
			  device_uncache_fw_images_work);

	fw_cache.pm_notअगरy.notअगरier_call = fw_pm_notअगरy;
	ret = रेजिस्टर_pm_notअगरier(&fw_cache.pm_notअगरy);
	अगर (ret)
		वापस ret;

	रेजिस्टर_syscore_ops(&fw_syscore_ops);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम unरेजिस्टर_fw_pm_ops(व्योम)
अणु
	unरेजिस्टर_syscore_ops(&fw_syscore_ops);
	unरेजिस्टर_pm_notअगरier(&fw_cache.pm_notअगरy);
पूर्ण
#अन्यथा
अटल पूर्णांक fw_cache_piggyback_on_request(स्थिर अक्षर *name)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत पूर्णांक रेजिस्टर_fw_pm_ops(व्योम)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम unरेजिस्टर_fw_pm_ops(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

अटल व्योम __init fw_cache_init(व्योम)
अणु
	spin_lock_init(&fw_cache.lock);
	INIT_LIST_HEAD(&fw_cache.head);
	fw_cache.state = FW_LOADER_NO_CACHE;
पूर्ण

अटल पूर्णांक fw_shutकरोwn_notअगरy(काष्ठा notअगरier_block *unused1,
			      अचिन्हित दीर्घ unused2, व्योम *unused3)
अणु
	/*
	 * Kill all pending fallback requests to aव्योम both stalling shutकरोwn,
	 * and aव्योम a deadlock with the usermode_lock.
	 */
	समाप्त_pending_fw_fallback_reqs(false);

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block fw_shutकरोwn_nb = अणु
	.notअगरier_call = fw_shutकरोwn_notअगरy,
पूर्ण;

अटल पूर्णांक __init firmware_class_init(व्योम)
अणु
	पूर्णांक ret;

	/* No need to unfold these on निकास */
	fw_cache_init();

	ret = रेजिस्टर_fw_pm_ops();
	अगर (ret)
		वापस ret;

	ret = रेजिस्टर_reboot_notअगरier(&fw_shutकरोwn_nb);
	अगर (ret)
		जाओ out;

	वापस रेजिस्टर_sysfs_loader();

out:
	unरेजिस्टर_fw_pm_ops();
	वापस ret;
पूर्ण

अटल व्योम __निकास firmware_class_निकास(व्योम)
अणु
	unरेजिस्टर_fw_pm_ops();
	unरेजिस्टर_reboot_notअगरier(&fw_shutकरोwn_nb);
	unरेजिस्टर_sysfs_loader();
पूर्ण

fs_initcall(firmware_class_init);
module_निकास(firmware_class_निकास);
